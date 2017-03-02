# torque_viewer
![screenshot](https://raw.githubusercontent.com/inria-larsen/icub-wholebody-visualization/master/torque_viewer/res/Screenshot_20170301_160242.png)

## dependancies

build dependancies:
* yarp
* qt

run dependancies:
* icub with running wholebodydynamicstree

It has only been tested on linux so far (ubuntu 14.04 and ubuntu 16.04 known to
work).

## installation

Nothing special:
```
mkdir build
cd build
cmake ../
make 
make install
```

## usage

* launch wholebodydynamicstree
* run `torque_viewer --autoconnect`, see `torque_viewer --help` for additional
  parameters.
