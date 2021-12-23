/*
 * Copyright (C) 2021 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#ifndef IGNITION_MATH_PYTHON__FILTER_HH_
#define IGNITION_MATH_PYTHON__FILTER_HH_

#include <string>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include <ignition/math/Filter.hh>
#include <ignition/math/Quaternion.hh>
#include <ignition/math/Vector3.hh>

namespace py = pybind11;

namespace ignition
{
namespace math
{
namespace python
{
template<typename T>
class FilterTrampoline : public Filter<T> {
public:
    // Inherit the constructors
    // using Filter<double>::Filter<double>;
    FilterTrampoline() : Filter<T>() {}

    // Trampoline (need one for each virtual function)
    void Set(const T &_val) override
    {
        PYBIND11_OVERLOAD_PURE(
            void, // Return type (ret_type)
            Filter<T>,      // Parent class (cname)
            Set,          // Name of function in C++ (must match Python name) (fn)
            _val      // Argument(s) (...)
        );
    }
    // Trampoline (need one for each virtual function)
    void Fc(double _fc, double _fs) override
    {
        PYBIND11_OVERLOAD_PURE(
            void, // Return type (ret_type)
            Filter<T>,      // Parent class (cname)
            Fc,          // Name of function in C++ (must match Python name) (fn)
            _fc, _fs      // Argument(s) (...)
        );
    }
    // Trampoline (need one for each virtual function)
    const T &Value() const override
    {
        PYBIND11_OVERLOAD_PURE(
            const T&, // Return type (ret_type)
            Filter<T>,      // Parent class (cname)
            Value          // Name of function in C++ (must match Python name) (fn)
                       // Argument(s) (...)
        );
    }
};

/// Define a pybind11 wrapper for an ignition::math::Filter
/**
 * \param[in] module a pybind11 module to add the definition to
 */
template<typename T>
void defineMathFilter(py::module &m, const std::string &typestr)
{
  using Class = ignition::math::Filter<T>;
  std::string pyclass_name = typestr;
  py::class_<Class, FilterTrampoline<T>>(m,
                    pyclass_name.c_str(),
                    py::buffer_protocol(),
                    py::dynamic_attr())
    .def(py::init<>())
    .def("set",
         &Class::Set,
         "Set the output of the filter.")
    .def("fc",
         &Class::Fc,
         "Set the cutoff frequency and sample rate.")
    .def("value",
         &Class::Value,
         "Get the output of the filter.");
}

template<typename T>
class OnePoleTrampoline : public OnePole<T> {
public:
  OnePoleTrampoline() : OnePole<T>() {}
  OnePoleTrampoline(double _fc, double _fs) : OnePole<T>(_fc, _fs) {}

  // Trampoline (need one for each virtual function)
  void Fc(double _fc, double _fs) override
  {
      PYBIND11_OVERLOAD_PURE(
          void, // Return type (ret_type)
          OnePole<T>,      // Parent class (cname)
          Fc,          // Name of function in C++ (must match Python name) (fn)
          _fc,          // Argument(s) (...)
          _fs
      );
  }
};

/// Define a pybind11 wrapper for an ignition::math::OnePole
/**
 * \param[in] module a pybind11 module to add the definition to
 */
template<typename T>
void defineMathOnePole(py::module &m, const std::string &typestr)
{
  using Class = ignition::math::OnePole<T>;
  std::string pyclass_name = typestr;
  py::class_<Class, OnePoleTrampoline<T>>(m,
                    pyclass_name.c_str(),
                    py::buffer_protocol(),
                    py::dynamic_attr())
    .def(py::init<>())
    .def(py::init<double, double>())
    .def("set",
         &Class::Set,
         "Set the output of the filter.")
    .def("value",
         &Class::Value,
         "Get the output of the filter.")
    .def("fc",
         &Class::Fc,
         "Set the cutoff frequency and sample rate.")
    .def("process",
         &Class::Process,
         "Update the filter's output.");
}

// class OnePoleQuaternionTrampoline : public OnePole<ignition::math::Quaterniond> {
// public:
//   OnePoleQuaternionTrampoline() : OnePole<ignition::math::Quaterniond>() {};
//   OnePoleQuaternionTrampoline(double _fc, double _fs)
//     : OnePole<ignition::math::Quaterniond>(_fc, _fs) {};
// };

/// Define a pybind11 wrapper for an ignition::math::OnePole
/**
 * \param[in] module a pybind11 module to add the definition to
 */
void defineMathOnePoleQuaternion(py::module &m, const std::string &typestr)
{
  using Class = ignition::math::OnePoleQuaternion;
  std::string pyclass_name = typestr;
  py::class_<Class>(m,
                    pyclass_name.c_str(),
                    py::buffer_protocol(),
                    py::dynamic_attr())
    .def(py::init<>())
    .def(py::init<double, double>())
    .def("set",
         &Class::Set,
         "Set the output of the filter.")
    .def("value",
         &Class::Value,
         "Get the output of the filter.")
    .def("fc",
         &Class::Fc,
         "Set the cutoff frequency and sample rate.")
    .def("process",
         &Class::Process,
         "Update the filter's output.");
}

/// Define a pybind11 wrapper for an ignition::math::OnePole
/**
 * \param[in] module a pybind11 module to add the definition to
 */
void defineMathOnePoleVector3(py::module &m, const std::string &typestr)
{
  using Class = ignition::math::OnePoleVector3;
  std::string pyclass_name = typestr;
  py::class_<Class>(m,
                    pyclass_name.c_str(),
                    py::buffer_protocol(),
                    py::dynamic_attr())
    .def(py::init<>())
    .def(py::init<double, double>())
    .def("set",
         &Class::Set,
         "Set the output of the filter.")
    .def("value",
         &Class::
         Value,
         "Get the output of the filter.")
    .def("fc",
         &Class::Fc,
         "Set the cutoff frequency and sample rate.")
    .def("process",
         &Class::Process,
         "Update the filter's output.");
}

template<typename T>
class BiQuadTrampoline : public BiQuad<T>
{
public:
  BiQuadTrampoline() : BiQuad<T>() {};
  BiQuadTrampoline(double _fc, double _fs) : BiQuad<T>(_fc, _fs) {};

  // Trampoline (need one for each virtual function)
  void Fc(double _fc, double _fs) override
  {
      PYBIND11_OVERLOAD_PURE(
          void, // Return type (ret_type)
          Filter<T>,      // Parent class (cname)
          Fc,          // Name of function in C++ (must match Python name) (fn)
          _fc, _fs      // Argument(s) (...)
      );
  }
  // Trampoline (need one for each virtual function)
  void Set(const T &_val) override
  {
      PYBIND11_OVERLOAD_PURE(
          void, // Return type (ret_type)
          Filter<T>,      // Parent class (cname)
          Set,          // Name of function in C++ (must match Python name) (fn)
          _val      // Argument(s) (...)
      );
  }
  // Trampoline (need one for each virtual function)
  const T& Process(const T &_x) override
  {
      PYBIND11_OVERLOAD_PURE(
          const T&, // Return type (ret_type)
          Filter<T>,      // Parent class (cname)
          Process,          // Name of function in C++ (must match Python name) (fn)
          _x      // Argument(s) (...)
      );
  }
};

/// Define a pybind11 wrapper for an ignition::math::OnePole
/**
 * \param[in] module a pybind11 module to add the definition to
 */
template<typename T>
void defineMathBiQuad(py::module &m, const std::string &typestr)
{
  using Class = ignition::math::BiQuad<T>;
  std::string pyclass_name = typestr;
  py::class_<Class, BiQuadTrampoline<T>>(m,
                    pyclass_name.c_str(),
                    py::buffer_protocol(),
                    py::dynamic_attr())
    .def(py::init<>())
    .def(py::init<double, double>())
    .def("set",
         &Class::Set,
         "Set the output of the filter.")
    .def("fc",
          py::overload_cast<double, double>(&Class::Fc),
         "Set the cutoff frequency and sample rate.")
    .def("value",
         &Class::Value,
         "Get the output of the filter.")
    .def("fc",
         py::overload_cast<double, double, double>(&Class::Fc),
         "Set the cutoff frequency, sample rate and Q coefficient.")
    .def("process",
         &Class::Process,
         "Update the filter's output.");
}

/// Define a pybind11 wrapper for an ignition::math::OnePole
/**
 * \param[in] module a pybind11 module to add the definition to
 */
void defineMathBiQuadVector3(py::module &m, const std::string &typestr)
{
  using Class = ignition::math::BiQuadVector3;
  std::string pyclass_name = typestr;
  py::class_<Class>(m,
                    pyclass_name.c_str(),
                    py::buffer_protocol(),
                    py::dynamic_attr())
    .def(py::init<>())
    .def(py::init<double, double>())
    .def("set",
         &Class::Set,
         "Set the output of the filter.")
    .def("fc",
          py::overload_cast<double, double>(&Class::Fc),
         "Set the cutoff frequency and sample rate.")
    .def("value",
         &Class::Value,
         "Get the output of the filter.")
    .def("fc",
         py::overload_cast<double, double, double>(&Class::Fc),
         "Set the cutoff frequency, sample rate and Q coefficient.")
    .def("process",
         &Class::Process,
         "Update the filter's output.");
}
}  // namespace python
}  // namespace gazebo
}  // namespace ignition

#endif  // IGNITION_MATH_PYTHON__FILTER_HH_