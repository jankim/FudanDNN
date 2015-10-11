FudanDNN: a detachable neural network framework with easy-to-use GUI
====================================================================

1. Copyright
------------

Jiangtao Feng<br />
Shangtong Zhang<br />
Siyan Li<br />
Xiaoqing Zheng

2. License
----------

FudanDNN is provided without any warranty of fitness for any purpose.  You
can redistribute the library and/or modify it under the terms of GPL license.

3. Build
--------

Dependency: 

cmake > 2.8<br />
boost > 1.55<br />
OpenCL 1.2(optional)<br />
ViennalCL 1.7(optional)<br />

Build:

cd FudanDNN<br />
mkdir build<br />
cd build

--use makefile<br />
cmake ../<br />
make

--use other available IDE, such as Xcode<br />
cmake -G Xcode ../

use cmake -h to get information about your IDE

cmake -DGPU=OpenCL (use OpenCL backends, default is CPU backends)


