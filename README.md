# SpoutControls
“SpoutControls” is a programmer aid that can be used to develop a controlled Spout Sender with C++ or Processing that will react to user controls specific to the application by using a “Spout Controller”.

The Sender then does not require a GUI interface that could interfere with the graphics to be shared, or require third party communication to be set up between controller and sender. You build the controls into the sender application and the controllers adapt the user interface to them.

Controllers include a Freeframe plugin which is itself a Spout Receiver, so you can control your Sender application directly within a Freeframe host such as Resolume, Magic or Isadora without jumping back and forth between the host and your app to change settings.

The Sender establishes the controls that the controller will use and the updates local variables when the controller has changed any controls. This can be done using only four functions. Example controlled Senders for Openframeworks, Cinder and Processing can be used a guide for developing others.

Credit to Eric Medine - http://ericmedine.com/ - who came up with the idea.

SpoutControls is licenced using the GNU Lesser General Public License.

