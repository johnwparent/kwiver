// This file is part of KWIVER, and is distributed under the
// OSI-approved BSD 3-Clause License. See top-level LICENSE file or
// https://github.com/Kitware/kwiver/blob/master/LICENSE for details.

#include <python/kwiver/vital/algo/trampoline/image_filter_trampoline.txx>
#include <python/kwiver/vital/algo/image_filter.h>

#include <pybind11/pybind11.h>

namespace kwiver {
namespace vital  {
namespace python {
namespace py = pybind11;

void image_filter(py::module &m)
{
  py::class_< kwiver::vital::algo::image_filter,
              std::shared_ptr<kwiver::vital::algo::image_filter>,
              kwiver::vital::algorithm_def<kwiver::vital::algo::image_filter>,
              image_filter_trampoline<> >(m, "ImageFilter")
    .def(py::init())
    .def_static("static_type_name",
                &kwiver::vital::algo::image_filter::static_type_name)
    .def("filter", &kwiver::vital::algo::image_filter::filter);
}
}
}
}
