/*
 * Copyright (C) 2016 Open Source Robotics Foundation
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

#include <gtest/gtest.h>
#include "gz/math/Vector3.hh"
#include "gz/math/MovingWindowFilter.hh"

using namespace gz;

/////////////////////////////////////////////////
TEST(MovingWindowFilterTest, SetWindowSize)
{
  math::MovingWindowFilter<int> filterInt;

  EXPECT_EQ(filterInt.WindowSize(), 4u);
  EXPECT_FALSE(filterInt.WindowFilled());

  filterInt.SetWindowSize(10);
  EXPECT_EQ(filterInt.WindowSize(), 10u);
  EXPECT_FALSE(filterInt.WindowFilled());
}

/////////////////////////////////////////////////
TEST(MovingWindowFilterTest, FilterIntegral)
{
  math::MovingWindowFilter<int> mwf;

  mwf.SetWindowSize(2);
  mwf.Update(1);
  mwf.Update(1);
  EXPECT_EQ(1, mwf.Value());

  // Integer cast
  mwf.Update(1);
  mwf.Update(2);
  EXPECT_EQ(1, mwf.Value());
}

/////////////////////////////////////////////////
TEST(MovingWindowFilterTest, FilterIntegralVector)
{
  math::MovingWindowFilter<math::Vector3i> mwf;

  mwf.SetWindowSize(2);
  mwf.Update({1, 1, 1});
  mwf.Update({1, 1, 1});
  EXPECT_EQ(math::Vector3i(1, 1, 1), mwf.Value());

  // Integer cast
  mwf.Update({1, 1, 1});
  mwf.Update({2, 2, 2});
  EXPECT_EQ(math::Vector3i(1, 1, 1), mwf.Value());
}

/////////////////////////////////////////////////
TEST(MovingWindowFilterTest, FilterFloatVector)
{
  math::MovingWindowFilter<math::Vector3f> mwf;

  mwf.SetWindowSize(2);
  mwf.Update({1, 1, 1});
  mwf.Update({1, 1, 1});
  EXPECT_EQ(math::Vector3f(1, 1, 1), mwf.Value());

  mwf.Update({1, 1, 1});
  mwf.Update({2, 2, 2});
  EXPECT_EQ(math::Vector3f(1.5, 1.5, 1.5), mwf.Value());
}

/////////////////////////////////////////////////
TEST(MovingWindowFilterTest, FilterSomething)
{
  math::MovingWindowFilter<double> doubleMWF;
  math::MovingWindowFilter<double> doubleMWF2;
  math::MovingWindowFilter<gz::math::Vector3d> vectorMWF;

  doubleMWF.SetWindowSize(10);
  doubleMWF2.SetWindowSize(2);
  vectorMWF.SetWindowSize(40);

  for (unsigned int i = 0; i < 20; ++i)
  {
    doubleMWF.Update(static_cast<double>(i));
    doubleMWF2.Update(static_cast<double>(i));
    gz::math::Vector3d v(1.0*static_cast<double>(i),
        2.0*static_cast<double>(i),
        3.0*static_cast<double>(i));
    vectorMWF.Update(v);
  }

  double sum = 0;
  for (unsigned int i = 20-10; i < 20; ++i)
    sum += static_cast<double>(i);
  EXPECT_DOUBLE_EQ(doubleMWF.Value(), sum/10.0);
  EXPECT_DOUBLE_EQ(doubleMWF2.Value(), (18.0+19.0)/2.0);

  gz::math::Vector3d vsum;
  for (unsigned int i = 0; i < 20; ++i)
    vsum += gz::math::Vector3d(1.0*static_cast<double>(i),
        2.0*static_cast<double>(i),
        3.0*static_cast<double>(i));
  EXPECT_EQ(vectorMWF.Value(), vsum / 20.0);
}
