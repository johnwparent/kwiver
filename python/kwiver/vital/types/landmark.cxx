/*ckwg +29
 * Copyright 2017-2020 by Kitware, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  * Neither name of Kitware, Inc. nor the names of any contributors may be used
 *    to endorse or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <vital/types/landmark.h>
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <vital/util/demangle.h>

#include <string>


namespace py = pybind11;
namespace kv = kwiver::vital;
using namespace kwiver::vital;

template <typename T>
void reg_landmark(py::module &m, std::string &&type_str)
{
  using Class =  kv::landmark_< T >;
  std::string py_class_name = std::string("Landmark") + type_str;
  py::class_< Class, kv::landmark, std::shared_ptr< Class >  >(m, py_class_name.c_str())
  .def(py::init())
  .def(py::init< Eigen::Matrix< T, 3, 1 > const&, T >(), py::arg("loc"), py::arg("scale") = 1 )
  .def(py::init< kv::landmark const& >())
  .def_property_readonly("data_type", ([](Class const &self)
  {
    return demangle( self.data_type().name() );
  }))
  .def_property("loc", &Class::get_loc, &Class::set_loc)
  .def_property("scale", &Class::get_scale, &Class::set_scale)
  .def_property("normal", &Class::get_normal, &Class::set_normal)
  .def_property("covariance", &Class::get_covar, &Class::set_covar)
  .def_property("color", &Class::get_color, &Class::set_color)
  .def_property("observations", &Class::get_observations, &Class::set_observations)
  .def_property("cos_obs_angle", &Class::get_cos_obs_angle, &Class::set_cos_observation_angle)
  ;

}

PYBIND11_MODULE(landmark, m)
{
  py::class_<kv::landmark, std::shared_ptr< kv::landmark > >(m, "Landmark")
  .def("data_type",     &kv::landmark::data_type)
  .def("loc",           &kv::landmark::loc)
  .def("scale",         &kv::landmark::scale)
  .def("normal",        &kv::landmark::normal)
  .def("covar",         &kv::landmark::covar)
  .def("color",         &kv::landmark::color)
  .def("observations",   &kv::landmark::observations)
  .def("cos_obs_angle",  &kv::landmark::cos_obs_angle)
  ;

  reg_landmark<double>(m, "D");
  reg_landmark<float>(m, "F");
}
