# Copyright (C) 2021 Open Source Robotics Foundation
#
# Licensed under the Apache License, Version 2.0 (the "License")
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#       http:#www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Modify the PYTHONPATH environment variable to include the gz math
# library install path. For example, if you install to /usr:
#
# $ export PYTHONPATH=/usr/lib/python:$PYTHONPATH
#
# You can plot the data generated by this program by following these
# steps.
#
# 1. Run this program and save the output to a file:
#     python3 gauss_markov_process_example.py > plot.data
#
# 2. Use gnuplot to create a plot:
#     gnuplot -e 'set terminal jpeg; plot "plot.data" with lines' > out.jpg
import datetime
from gz.math8 import GaussMarkovProcess

# Create the process with:
#   * Start value of 20.2
#   * Theta (rate at which the process should approach the mean) of 0.1
#   * Mu (mean value) 0.
#   * Sigma (volatility) of 0.5.
gmp = GaussMarkovProcess(20.2, 0.1, 0, 0.5);

dt = datetime.timedelta(milliseconds=100)

# This process should decrease toward the mean value of 0.
# With noise of 0.5, the process will walk a bit.
for i in range(1000):
    value = gmp.update(dt);
    print(value);
