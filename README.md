# Event Annotation Tool
The Event Annotation Tool (EAT) is an instrument for annotating normal and abnormal events in videos and images.

![Event Annotation Tool](/images/eat.png)

## Requirements

EAT requires the following packeges to build:

* OpenCV (< 3.0)
* Boost
* Qt4

## How to build

EAT works under Linux and Mac Os environments. We recommend a so-called out of source build 
which can be achieved by the following command sequence:

* mkdir build
* cd build
* cmake ../
* make -j\<number-of-cores+1\>

## How to use

Once the build phase has been successfully, you can use EAT by launching the _eventannotation_
file, located in the _bin_ folder.
