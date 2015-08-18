#include "testApp.h"
#include "ofAppGlutWindow.h"

//--------------------------------------------------------------
// to change options for console window (Visual Studio)
//
// Properties > Linker > System > Subsystem
//
// for console : Windows (/SUBSYSTEM:CONSOLE)
//
// for Window : Windows (/SUBSYSTEM:WINDOWS)
//
// Click APPLY (important) and OK. Then make changes to Main as below
//--------------------------------------------------------------

// for default console
// int main() {
//
// for window without console
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	ofAppGlutWindow window; // create a window
	ofSetupOpenGL(&window, 256, 256, OF_WINDOW);

	ofRunApp(new testApp()); // start the app

}
