# SpoutControls
“SpoutControls” is a C++ class and Processing library that a programmer can use to develop a controlled Spout Sender that will react to controls specific to the application.

The Freeframe SpoutController plugin is a Spout Receiver which adapts it’s user interface within the host to that required by the Sender. Then you control the Sender from within the host program and forget about the sender app itself.

The Sender then does not require a GUI interface that could interfere with the graphics to be shared, or require third party communication to be set up between controller and sender. The Sender establishes the controls that the controller will use and the updates local variables when the controller has changed any controls. This can be done using only four functions.

Example controlled Senders for Openframeworks, Cinder and Processing can be used a guide for developing others.

Credit to Eric Medine - http://tentonraygun.com/ - who came up with the idea.

Demo video by Eric is here : https://vimeo.com/136557785

SpoutControls is licenced using the GNU Lesser General Public License.

