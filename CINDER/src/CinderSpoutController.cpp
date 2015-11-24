/*
				
		Basic Spout sender for Cinder

		Search for "SPOUT" to see what is required
		Uses the Spout SDK

		Based on the RotatingBox CINDER example without much modification
		Nothing fancy about this, just the basics.

		Search for "SPOUT" to see what is required

	==========================================================================
	Copyright (C) 2014 Lynn Jarvis.

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
	==========================================================================

	11.05.14 - used updated Spout Dll with host fbo option and rgba
	04.06.14 - updated Spout dll 04/06 - host fbo option removed
	11.07.14 - changed to Spout SDK instead of the dll
	29.09.14 - updated to revised SDK
	12.10.14 - recompiled for release
	03.01.15 - SDK recompile
	04.02.15 - SDK recompile for default DX9 (see SpoutGLDXinterop.h)
	14.02.15 - SDK recompile for default DX11 and auto compatibility detection (see SpoutGLDXinterop.cpp)
	21.05.15 - Added optional SetDX9 call
			 - Recompiled for both DX9 and DX11 for new installer
	26.05.15 - Recompile for revised SpoutPanel registry write of sender name
	22.07.05 - Included CreateControl functions
	25.09.15 - Updated for 2.005 memoryshare

*/
#include "cinder/app/AppBasic.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Camera.h"
#include <vector>

// -------- SPOUT -------------
#include "..\..\..\SpoutSDK\Spout.h"		 // Spout SDK
#include "..\..\..\SpoutSDK\SpoutControls.h" // SpoutControls
// ----------------------------

using namespace ci;
using namespace ci::app;

class SpoutBoxApp : public AppBasic {

  public:

	void setup();
	void update();
	void draw();

	// still using the cam vars from the cinder demo
	CameraPersp	mCam;
	gl::Texture	cubeTexture;
	Matrix44f	mCubeRotation;

	// -------- SPOUT -------------
	SpoutSender spoutsender;					// Create a Spout sender object
	void prepareSettings(Settings *settings);
	void shutdown();
	bool bInitialized;							// true if a sender initializes OK
	bool bMemoryShare;                          // True for memoryshare moded
	unsigned int g_Width, g_Height;				// size of the texture being sent out
	char SenderName[256];						// sender name 
	gl::Texture spoutTexture;					// Local Cinder texture used for sharing
	// ----------------------------

	// ------------ SpoutControls ----------------
	//
	SpoutControls spoutcontrols;	// a SpoutControls object
	vector<control> myControls;		// Vector of controls to be used
	void UpdateControlParameters();	// Local control update function

	bool m_bRotate;			// Local flag
	float m_Rotation;		// Rotation amount typically 0-1 but can be scaled as per example 0 - 4
	float m_RotationSpeed;	// Local  variable
	string m_UserText;		// Local text
	// -------------------------------------------

};

// -------- SPOUT -------------
void SpoutBoxApp::prepareSettings(Settings *settings)
{
		g_Width  = 640;
		g_Height = 512;
		settings->setTitle("CinderSpoutSender");
		settings->setWindowSize( g_Width, g_Height );
		settings->setFullScreen( false );
		settings->setResizable( false ); // keep the screen size constant for a sender
		settings->setFrameRate( 60.0f );
}
// ----------------------------


void SpoutBoxApp::setup()
{

	// load an image to texture the demo cube with
	cubeTexture = loadImage( "../data/SpoutLogoMarble3.bmp" );
	
	mCam.lookAt( Vec3f( 3, 2, -3 ), Vec3f::zero() );
	mCubeRotation.setToIdentity();
	glEnable( GL_TEXTURE_2D );
	gl::enableDepthRead();
	gl::enableDepthWrite();	

	// -------- SPOUT -------------
	// Set up the texture we will use to send out
	// We grab the screen so it has to be the same size
	spoutTexture =  gl::Texture(g_Width, g_Height);
	strcpy_s(SenderName, "CINDER Spout SDK Sender"); // we have to set a sender name first

	// Initialize a sender
	bInitialized = spoutsender.CreateSender(SenderName, g_Width, g_Height);
	// Detect texture share compatibility for status display
	bMemoryShare = spoutsender.GetMemoryShareMode();
	// ----------------------------

	// ------------ SpoutControls ----------------
	// 
	// Controls vary cube rotation and speed
	// Defaults should be the same as when creating the controls below.
	//
	m_bRotate = true;
	m_RotationSpeed = 0.5f; // Rotation amount min-max
	m_UserText = "";

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

	// "OpenControls" creates a control file with the same name as the sender
	// and the control information is wrtitten to it.

	// The sender also writes the sender name to the registry
	// for the controller to access. The controller can then use this name
	// to create a memory map and update it as the controls are changed.
	
	// The sender also creates a mailslot to check for controller messages
	// The controller updates the controls and sends a message when they change.
	// The sender checks for a message and updates it's control variables.

	spoutcontrols.OpenControls(SenderName);
	// -------------------------------------------

}

// -------- SPOUT -------------
void SpoutBoxApp::shutdown()
{
	spoutsender.ReleaseSender();

	// ------------ SpoutControls ----------------
	// This app Opened the control communication so has to close it
	spoutcontrols.CloseControls();
	// -------------------------------------------

}
// ----------------------------


void SpoutBoxApp::update()
{

	// ------------ SpoutControls ----------------
	// The controller creates controls when this sender is running
	// and updates them when the user changes a control,
	// so just check them here before drawing
	if(spoutcontrols.CheckControls(myControls))
		UpdateControlParameters();

	// Rotation speed - scale to radians
	float fSpeed = m_RotationSpeed*0.0126f;

	// Rotate the cube by radians around an arbitrary axis
	if(m_bRotate)
		mCubeRotation.rotate( Vec3f( 1, 1, 1 ), fSpeed );
	// -------------------------------------------

	mCam.setPerspective( 60, getWindowAspectRatio(), 1, 1000 );
	gl::setMatrices( mCam );


}

void SpoutBoxApp::draw()
{
	
	char txt[256];

	// gl::clear( Color( 0.39f, 0.025f, 0.0f ) ); // red/brown
	gl::clear( Color( 0.05f, 0.10f, 0.30f ) ); // dark blue
	
	if( ! cubeTexture )
		return;

	cubeTexture.bind();
	glPushMatrix();
		gl::multModelView( mCubeRotation );
		gl::drawCube( Vec3f::zero(), Vec3f( 2.5f, 2.5f, 2.5f ) );
	glPopMatrix();
	cubeTexture.unbind();

	// ------------ SpoutControls ----------------
	// User text from the controller
	if(!m_UserText.empty()) {
		gl::setMatricesWindow( getWindowSize() );
		gl::enableAlphaBlending();
		if(bMemoryShare)
			gl::drawString( m_UserText.c_str(), Vec2f( toPixels( 20 ), toPixels( 70 ) ), Color( 1, 1, 1 ), Font( "Verdana", toPixels( 48 ) ) );
		else
			gl::drawString( m_UserText.c_str(), Vec2f( toPixels( 20 ), toPixels( 50 ) ), Color( 1, 1, 1 ), Font( "Verdana", toPixels( 48 ) ) );
		gl::disableAlphaBlending();
	}
	// -------------------------------------------


	// -------- SPOUT -------------
	if(bInitialized) {

		// Grab the screen (current read buffer) into the local spout texture
		spoutTexture.bind();
		glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, g_Width, g_Height);
		spoutTexture.unbind();

		// Send the texture for all receivers to use
		// NOTE : if SendTexture is called with a framebuffer object bound,
		// include the FBO id as an argument so that the binding is restored afterwards
		// because Spout uses an fbo for intermediate rendering
		spoutsender.SendTexture(spoutTexture.getId(), spoutTexture.getTarget(), g_Width, g_Height);

	}

	// Show the user what it is sending
	sprintf_s(txt, "Controlled sender [%s]", SenderName);
	gl::setMatricesWindow( getWindowSize() );
	gl::enableAlphaBlending();
	gl::drawString( txt, Vec2f( toPixels( 20 ), toPixels( 20 ) ), Color( 1, 1, 1 ), Font( "Verdana", toPixels( 24 ) ) );

	if(bMemoryShare) {
		sprintf_s(txt, "Memoryshare mode");
		gl::drawString( txt, Vec2f( toPixels( 20 ), toPixels( 40 ) ), Color( 1, 1, 1 ), Font( "Verdana", toPixels( 24 ) ) );
	}

	sprintf_s(txt, "fps : %2.2d", (int)getAverageFps());
	gl::drawString( txt, Vec2f(getWindowWidth() - toPixels( 100 ), toPixels( 20 ) ), Color( 1, 1, 1 ), Font( "Verdana", toPixels( 24 ) ) );
	gl::disableAlphaBlending();
	// ----------------------------

}

//
// - - - - - - - - - SpoutControls - - - - - - - - - -
//
void SpoutBoxApp::UpdateControlParameters()
{
	// Control names and types must match those in the controls definition file
	// The control names are case sensitive
	for(UINT i=0; i<myControls.size(); i++) {
		if(myControls.at(i).name == "User text")
			m_UserText = myControls.at(i).text;
		if(myControls.at(i).name == "Speed")
			m_RotationSpeed = myControls.at(i).value;
		if(myControls.at(i).name == "Rotate")
			m_bRotate = ((int)myControls.at(i).value == 1);
	}
}



CINDER_APP_BASIC( SpoutBoxApp, RendererGl )
