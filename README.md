# SpoutControls
SpoutControls is a programmer aid that can be used to develop a controlled Spout Sender with C++ or Processing that will react to user controls specific to the application by using a "Spout controller".

The Sender does not require a GUI interface that could interfere with the graphics to be shared, or require third party communication to be set up between controller and sender.

The Sender establishes the controls that the controller will use and the updates local variables when the controller has changed any controls. This can be done using only four functions.

Controllers are a Freeframe plugin which is itself a Spout Receiver, and a stand-alone executable. The controllers adapt their user interface to that required by the Sender.

Example controlled Senders for Openframeworks, Cinder and Processing can be used a guide for developing others.

Credit to Eric Medine who came up with the idea.

