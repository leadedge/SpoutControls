/*

	Spout - Sender controller example

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

*/
#pragma once

#include "ofMain.h"
#include "..\..\..\SpoutSDK\Spout.h"		 // Spout SDK
#include "..\..\..\SpoutSDK\SpoutControls.h" // SpoutControls

class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void exit(); 

		bool InitGLtexture(GLuint &texID, unsigned int width, unsigned int height);

		SpoutSender *spoutsender;		// A sender object
		char sendername[256];			// Shared memory name
		GLuint sendertexture;			// Local OpenGL texture used for sharing
		bool bInitialized;				// Initialization result
		bool bMemoryShare;				// Texture share compatibility
		ofImage myTextureImage;			// Texture image for the 3D demo
		unsigned int g_Width, g_Height;	// Global width and height
		ofTrueTypeFont	verdana;
		

		// - - - - - - - - - - - - - - - - - - - - - - - - -
		// SpoutControls
		//
		SpoutControls spoutcontrols;	// SpoutControls object
		vector<control> myControls;		// Vector of controls to be used
		void UpdateControlParameters();	// Control update function

		float m_RotX, m_RotY;	// Local variables to control cube rotation
		float m_RotationSpeed;	// Control variable to control rotation speed
		bool m_bRotate;			// Control flag to start and stop rotation
		string m_UserText;		// Control text to be displayed on the sender output

		// - - - - - - - - - - - - - - - - - - - - - - - - -

};
