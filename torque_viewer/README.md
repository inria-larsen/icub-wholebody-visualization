# torque_viewer
![screenshot](https://raw.githubusercontent.com/inria-larsen/icub-wholebody-visualization/master/torque_viewer/res/Screenshot_20170301_160242.png)

## Dependencies

build dependencies:

* yarp
* qt

run dependencies:

* icub with running wholebodydynamicstree

It has only been tested on linux so far (ubuntu 14.04 and ubuntu 16.04 known to
work).

## Build

Nothing special:

```
mkdir build
cd build
cmake ../
make 
```

(no make install for now)

## Usage

* launch wholebodydynamicstree
* run `torque_viewer --autoconnect`, see `torque_viewer --help` for additional
  parameters.
