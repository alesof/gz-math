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

%module diffdriveodometry
%{
#include <chrono>
#include <memory>
#include <ignition/math/DiffDriveOdometry.hh>
#include <ignition/math/Angle.hh>
#include <ignition/math/Export.hh>
#include <ignition/math/config.hh>
%}

namespace ignition
{
  namespace math
  {
    class DiffDriveOdometry
    {
      public: explicit DiffDriveOdometry(size_t _windowSize = 10);

      public: ~DiffDriveOdometry();

      public: void Init(const std::chrono::steady_clock::time_point &_time);

      public: bool Initialized() const;

      public: bool Update(const ignition::math::Angle &_leftPos, const ignition::math::Angle &_rightPos,
                          const std::chrono::steady_clock::time_point &_time);

      public: const ignition::math::Angle &Heading() const;

      public: double X() const;

      public: double Y() const;

      public: double LinearVelocity() const;

      public: const ignition::math::Angle &AngularVelocity() const;

      public: void SetWheelParams(double _wheelSeparation,
                      double _leftWheelRadius, double _rightWheelRadius);

      public: void SetVelocityRollingWindowSize(size_t _size);
    };
  }
}