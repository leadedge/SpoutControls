-----------------------------
"SPOUTCONTROLLER"

A stand-alone controller program.

This is not a Spout Receiver, so a separate receiver is needed
to see the resulting image of the controlled sender.

 o Start the sender to be controlled
 o Run the program


-----------------------------
"FREEFRAMEGL"

SpoutController.dll

A 32-bit freeframe dll controller as well as a Spout Receiver 

Refer to the SpoutControls documentation for folder requirements.

-----------------------------
"OPENFRAMEWORKS"

An example controlled sender application developed using using C++.

All the dependent dlls and data folder have to be with the executable.

Run "ofSpoutSenderControl.exe"

It will respond to the the "SpoutController.exe" dialog controls.

This is a Spout sender so if you open any receiver you will see the changes in it as well.


-----------------------------
"CINDER"

Cinder equivalent to the openframeworks example.


-----------------------------
"PROCESSING"

The SpoutController FreeFrame plugin can be used to control any Spout sender. 
This includes senders created with Processing.

The "SpoutBox" folder is an example of how a Spout sender sketch can be used.

See the SpoutControls documentation for further information.


-----------------------------
"SOURCE"

SpoutControls.h
SpoutControls.cpp

These files are required for development with C++
but not for Processing because the controller functions are included in JSpout.dll.



-----------------------------
Credit to Eric Medine (http://ericmedine.com/) who came up with the idea.


