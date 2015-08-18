/*

	Spout OpenFrameworks controlled Sender example

	1) Build and run this example
	2) Start a Spout controller

	Revisions :

	22.07.15 - VS2010 example project
	27.07.15 - Added SpoutControls "OpenSpoutController"

	=========================================================================
	Copyright (C) 2015 Lynn Jarvis.

	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
	=========================================================================
*/
#include "testApp.h"
#include "resource.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofBackground(10, 100, 140);
    ofSetVerticalSync(true);							// lock to monitor
	ofEnableNormalizedTexCoords();						// explicitly normalize tex coords for ofBox

	bInitialized	= false;							// Spout sender initialization
	g_Width			= 640;								// set starting global width and height for the sender
	g_Height		= 480;
	
	strcpy_s(sendername, "Spout Sender Control");		// Set the sender name
	ofSetWindowTitle(sendername);						// show it on the title bar
	ofSetWindowShape(g_Width, g_Height);				// Set the window size
	
	// Set the window icon from resources
	SetClassLong(WindowFromDC(wglGetCurrentDC()), GCL_HICON, (LONG)LoadIconA(GetModuleHandle(NULL), MAKEINTRESOURCEA(IDI_ICON1)));

    // 3D drawing setup for a sender
	glEnable(GL_DEPTH_TEST);							// enable depth comparisons and update the depth buffer
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	ofDisableArbTex();									// needed for textures to work
	
	myTextureImage.loadImage("SpoutBox1.png");			// Load a texture image for the demo
	myTextureImage.mirror(false, true);					// correct orientation

	// Font setup
	verdana.loadFont("verdana.ttf", 24, true, true);
	verdana.setLineHeight(34.0f);
	verdana.setLetterSpacing(1.035);

	// Spout sender setup
	spoutsender = new SpoutSender;						// Create a new Spout sender
	sendertexture = 0;									// Initially there is no local OpenGL texture ID
	InitGLtexture(sendertexture, g_Width, g_Height);	// Create an OpenGL texture for data transfers

	//
	// - - - - - - - - - SpoutControls - - - - - - - - - -
	//

	// Local control variables that vary cube rotation and speed
	m_bRotate = true;
	m_RotationSpeed = 0.5;
	m_UserText = "";
	m_RotX = 0;
	m_RotY = 0;

	//
	// Create the controls that will be used by the controller
	//
	// Types are :
	//		"event"		Button
	//		"bool"		Checkbox
	//		"float"		Slider control
	//		"text"		Text entry
	//
	// Default values can be optionally included
	// Float controls can be set up with a range from Minimum to Maximum
	//
	// Options are :
	//
	//	Create a control
	//	bool CreateControl(string name, string type);
	//
	//	Create a float or bool control with a default value
	//	bool CreateControl(string name, string type, float value);
	//
	//	Create a text control with a default string
	//	bool CreateControl(string name, string type, string text);
	//
	//	Create a float control with maximum, minimum and default values
	//	bool CreateControl(string name, string type, float minimum, float maximum, float value);
	//

	spoutcontrols.CreateControl("User text", "text", "Spout sender control");
	spoutcontrols.CreateControl("Rotate", "bool", 1);
	spoutcontrols.CreateControl("Speed", "float", 0.0, 4.0, 0.5);

	// The sender now initializes a name and writes this to the registry
	// for the controller to access. The controller can then use this name
	// to create a memory map and update it as the controls are changed.
	
	// The sender also creates a mailslot to check for controller messages
	// The controller updates the controls and sends a message when they change.
	// The sender checks for a message and updates it's control variables.

	spoutcontrols.OpenControls(sendername);

	// Optionally open the SpoutController executable program
	// if the application is not going to be controlled using
	// the Freeframe plugin "SpoutController.dll".
	// Space bar to bring it back if closed or minimized
	spoutcontrols.OpenSpoutController();

	// - - - - - - - - - - - - - - - - - - - - - - - - -


} // end setup

//--------------------------------------------------------------
void testApp::update() {

	//
	// - - - - - - - - - SpoutControls - - - - - - - - - -
	//
	// Check for a message from the controller 
	// and update local control variables for any change.
	if(spoutcontrols.CheckControls(myControls))
		UpdateControlParameters();

}

//--------------------------------------------------------------
void testApp::draw(){

	char str[256];
	ofSetColor(255);
	int index = -1;

	// A render window must be available for Spout initialization and might not be
	// available in "update" so do it now when there is definitely a render window.

	// Initialize a sender
	if(!bInitialized)
		bInitialized = spoutsender->CreateSender(sendername, g_Width, g_Height);

	// - - - - - - - - - - - - - - - - - - - - - - - - -
	// Draw 3D graphics demo - this could be anything
	// - - - - - - - - - - - - - - - - - - - - - - - - -
	ofPushMatrix();
	glTranslatef((float)ofGetWidth()/2.0, (float)ofGetHeight()/2.0, 0); // centre
	ofRotateY(m_RotY); // rotate - must be float
	ofRotateX(m_RotX);

	myTextureImage.getTextureReference().bind(); // bind our texture
	ofBox(0.4*(float)ofGetHeight()); // Draw the graphic
	ofPopMatrix();

	//
	// - - - - - - - - - SpoutControls - - - - - - - - - -
	//
	sprintf_s(str, "%s", m_UserText.c_str()); // Show plugin text
	verdana.drawString(str, 20, 50);
	
	if(m_bRotate) {
		m_RotY+=m_RotationSpeed;
		m_RotX+=m_RotationSpeed;
	}
	// - - - - - - - - - - - - - - - - - - - - - - - - -

	if(bInitialized) {

		// Grab the screen into the local spout texture
		glBindTexture(GL_TEXTURE_2D, sendertexture); 
		glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, g_Width, g_Height);
		glBindTexture(GL_TEXTURE_2D, 0); 

		// Send the texture out for all receivers to use
		spoutsender->SendTexture(sendertexture, GL_TEXTURE_2D, g_Width, g_Height);

		// Show what it is sending
		ofSetColor(255); 
		sprintf_s(str, "Sending as : [%s]", sendername);
		ofDrawBitmapString(str, 20, 20);

		// Show fps
		sprintf_s(str, "fps: %3.3d", (int)ofGetFrameRate());
		ofDrawBitmapString(str, ofGetWidth()-120, 20);

	}

}


//--------------------------------------------------------------
void testApp::exit() { 

	// Release the sender
	spoutsender->ReleaseSender(); 

	// At program termination, clean up everything
	delete spoutsender;
	spoutsender = NULL;

	//
	// - - - - - - - - - SpoutControls - - - - - - - - - -
	//
	// The sender initializes the communication with the controller so must also close it 
	spoutcontrols.CloseControls();

}

//
// - - - - - - - - - SpoutControls - - - - - - - - - -
//
void testApp::UpdateControlParameters()
{

	//
	// Control names and types match those of the controls originally created
	// Names are case sensitive
	//
	// For simple applications, all controls can be updated.
	// For situations that require action only when a parameter changes, check for change here.
	// For example :
	//		test a button for value 1
	//		test text input or a float value for change if it activates some function
	// 
	for(int i=0; i<myControls.size(); i++) {
		if(myControls.at(i).name == "User text")
			m_UserText = myControls.at(i).text;
		if(myControls.at(i).name == "Speed")
			m_RotationSpeed = myControls.at(i).value;
		if(myControls.at(i).name == "Rotate")
			m_bRotate = ((int)myControls.at(i).value == 1);
	}
}


bool testApp::InitGLtexture(GLuint &texID, unsigned int width, unsigned int height)
{

	if(texID != 0) glDeleteTextures(1, &texID);

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0,  GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
	// Space bar to bring back SpoutController
	if(key == 32) {
		spoutcontrols.OpenSpoutController();
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

