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

Once EAT has been launched, you can open a video (by clicking on _Open Video_) or a set
of images (by clicking on _Open Folder_). 

Then, you can annotate an _Abnormal Event_ by clicking on _Start Event_ and ending to annotate it
by clicking on _Stop Event_.
If you need to delete an annotation in a frame, you can click on _Cancel Event_.

Furthermore, you can save the annotated events (by clicking on _Save XML_) or load an existing
XML file (by clicking on _Load XML_).

The XML file must have the following format:

```xml
<?xml version="1.0" encoding="utf-8"?>
<dataset>
	<frame number="8">
		ABNORMAL
	</frame>
	<frame number="9">
		ABNORMAL
	</frame>
	....
</dataset>
```
