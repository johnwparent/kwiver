from __future__ import print_function
from __future__ import division
from __future__ import absolute_import

import torch
import torch.utils.data as data
import torch.nn as nn
from torchvision import models, transforms, datasets

from PIL import Image as pilImage

from kwiver.arrows.pytorch.parse_gpu_list import get_device
from vital.types import BoundingBox

class alexnetDataLoader(data.Dataset):# This is the same as the siamese one it was based on
    def __init__(self, bbox_list, transform, frame_img, in_size):
        self._frame_img = pilImage.new( "RGB", frame_img.size )
        self._frame_img.paste( frame_img )
        self._transform = transform
        self._bbox_list = bbox_list
        self._in_size = in_size

    def __getitem__(self, index):
        bb = self._bbox_list[index].bounding_box()

        # unwrap
        min_x = float( bb.min_x() )
        min_y = float( bb.min_y() )
        max_x = float( bb.max_x() )
        max_y = float( bb.max_y() )

        c_x = ( min_x + max_x ) / 2
        c_y = ( min_y + max_y ) / 2

        padding = 1.12 * max( max_x - min_x, max_y - min_y ) / 2

        # crop a square image
        im = self._frame_img.crop(
            (
                c_x - padding,
                c_y - padding,
                c_x + padding,
                c_y + padding
            )
        )

        im = im.resize((self._in_size, self._in_size), pilImage.BILINEAR)
        im.convert('RGB')

        if self._transform is not None:
            im = self._transform(im)

        return im

    def __len__(self):
        return self._bbox_list.size()


class pytorch_alexnet_f_extractor(object):
    """
    Obtain the appearance features from a trained pytorch alexnet
    model
    """

    def __init__(self, alexnet_model_path, img_size, batch_size, GPU_list=None):
        self._device, use_gpu_flag = get_device(GPU_list)

        # load the alexnet model. Maybe this shouldn't be hardcoded?
        self._alexnet_model = models.alexnet()
        print( alexnet_model_path )
        weights = torch.load( alexnet_model_path )

        self._alexnet_model.load_state_dict( weights )
        new_classifier = nn.Sequential(*list(self._alexnet_model.classifier.children())[:-1])
        self._alexnet_model.classifier = new_classifier

        self._alexnet_model.train( False ) # is this the same as eval() ?
        self._alexnet_model.to(self._device) # move the model to the GPU

        self._transform = transforms.Compose([
            transforms.Scale(img_size),
            transforms.ToTensor(),
            transforms.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])
        ])
        self._img_size = img_size
        self._b_size = batch_size

    @property
    def frame(self):
        return self._frame

    @frame.setter
    def frame(self, val):
        self._frame = val

    def __call__(self, bbox_list, MOT_flag):
        return self._obtain_feature(bbox_list, MOT_flag)

    def _obtain_feature(self, bbox_list, MOT_flag):
        kwargs = {'num_workers': 0, 'pin_memory': True}
        bbox_loader_class = alexnetDataLoader(bbox_list, self._transform, self._frame, self._img_size)
        bbox_loader = torch.utils.data.DataLoader(bbox_loader_class, batch_size=self._b_size, shuffle=False, **kwargs)

        torch.set_grad_enabled(False)
        for idx, imgs in enumerate(bbox_loader):
            v_imgs = imgs.to(self._device)
            output = self._alexnet_model(v_imgs)

            if idx == 0:
                app_features = output.data
            else:
                app_features = torch.cat((app_features, output.data), dim=0)

        return app_features.cpu()