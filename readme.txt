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

  o Copy to the plugin folder of the host application
  o Seen by the host as a source plugin
  o Start the sender to be controlled
  o Activate the plugin


-----------------------------
"OPENFRAMEWORKS"

An example controlled sender application developed using using C++.

All the dependent dlls and data folder have to be with the executable.

Run "ofSpoutController.exe"

It will respond to the "SpoutController.dll" Freeframe plugin or
the "SpoutController.exe" dialog controls.

This is a Spout sender so if you open any receiver you will see the changes in it as well.


-----------------------------
"CINDER"

Cinder equivalent to the openframeworks example.


-----------------------------
"PROCESSING"

Win32
x64

A controlled Spout Sender sketch including a controller dll and supporting pde files.

1) Run the "SpoutSenderControl" sketch
2) Run a freeframe host and activate the "SpoutController.dll" plugin
3) The sketch will respond to changes of the freeframe dll controls.

Operates in the same way as for the Openframeworks example. Examine the sketch source for details.



-----------------------------
"SOURCE"

SpoutControls.h
SpoutControls.cpp

These files are required for development with C++
but not for Processing because the controller functions are included in JSpout.dll.



-----------------------------
Credit to Eric Medine (http://ericmedine.com/) who came up with the idea.


