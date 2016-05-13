//
//  CirclesLinesDemo
//

// IMPORT THE SPOUT LIBRARY
import spout.*;

// DECLARE A SPOUT OBJECT
Spout spout;

// CONTROL ARRAYS
String[] controlName;
int[] controlType;
float[] controlValue;
String[] controlText;

// SPOUT SENDER NAME
String sendername;

/// circle objects
BasicCircle tCirc;
BasicCircle nextCirc;
BasicCircle nextRCirc;
int circSize = 15;
int numCircles = 15;
int maxCircles = 200;
ArrayList <BasicCircle> CircleArray = new ArrayList();

/// line toggle
boolean showLine = true;

int tWidth = 800;
int tHeight = 600;

void setup() {

  colorMode(RGB);
  size(800, 600, P3D);
  background(0);
  smooth();

  // CREATE A NEW SPOUT OBJECT
  spout = new Spout(this);

  // CREATE A SPOUT SENDER
  // Must use the same name as the sketch
  sendername = "CirclesLinesDemo";
  spout.createSender(sendername, width, height);

  // CREATE CONTROL ARRAYS
  controlName = new String[20];
  controlType = new int[20];
  controlValue = new float[20];
  controlText = new String[20];

  // CREATE CONTROLS TO BE USED
  spout.createSpoutControl("Show Lines", "bool", 1);
  spout.createSpoutControl("Number Circles", "float", 0, 200, 15);
  
  // OPEN THE CONTROLS FOR THE CONTROLLER
  // Must use the same name as the sketch and sender
  spout.openSpoutControls(sendername);

  /// create all circles
  for (int i=0; i< numCircles; i++) {
    float zx = random(0, 800);
    float zy = random(0, 600);
    /// initialize a new circle from our 
    /// BasicCircle class and add it to our ArrayList
    BasicCircle tCirc = new BasicCircle(zx, zy, 15);
    CircleArray.add(tCirc);
  }
}


void draw() {

  background(0);

  // CHECK FOR UPDATED CONTROLS FROM THE CONTROLLER
  int nControls = spout.checkSpoutControls(controlName, controlType, controlValue, controlText);
  if (nControls > 0) {
    // For all controls
    for (int i = 0; i < nControls; i++) {
      // Check each control by name
      
      if (controlName[i].equals("Number Circles")) {
        int newNum = int(controlValue[i]);
        updateNumberCircles(newNum);
      }
      
      if (controlName[i].equals("Show Lines")) {
        showLine = (boolean)(controlValue[i] == 1);
      }
      
    }
  }
  
  // this function draws the circles
  drawCircles();
  if (showLine) {
    drawLines();
  }

  // SEND THE TEXTURE OF THE DRAWING SURFACE
  // Sends at the size of the window
  spout.sendTexture();
  
}


// The sender opens the control communication,
// so must also close it.
void exit() {
  spout.closeSpoutControls();
}


///// DRAW ALL CIRCLES //////////////////////
void drawCircles() {
  
  for (int i = 0; i<CircleArray.size(); i++) {
    tCirc = CircleArray.get(i);
    tCirc.update();
  }
  
}

///// DRAW ALL LINES ///////////////////////
void drawLines() {

  for (int i = 0; i<CircleArray.size(); i++) {
    /// get a circle
    tCirc = CircleArray.get(i);
    int nxtId = 0;
    // get every other circle
    for (int j = 0; j< CircleArray.size(); j++) {
      nextCirc = CircleArray.get(j);
      stroke(255);
      strokeWeight(1);
      /// draw a line between tCirc and nextCirc
      line(tCirc.tPos.x, tCirc.tPos.y, nextCirc.tPos.x, nextCirc.tPos.y);
    }
  }
  
}

//////// UPDATE NUMBER OF CIRCLES ///////////////////////
void updateNumberCircles(int tNum){
   
    // if the new number is bigger
    // than the current number of
    // circles in our array
    // then add them
    if(tNum > CircleArray.size()){
      for(int i=0; i<tNum; i++){
          float zx = random(0, tWidth);
          float zy = random(0, tHeight);
          BasicCircle tCirc = new BasicCircle(zx, zy, circSize);
          CircleArray.add(tCirc);
        }
    }
    
    // if not then remove the last 
    // item in the array
    if(tNum < CircleArray.size()){
        for(int i=CircleArray.size(); i>tNum; i--){
           CircleArray.remove(CircleArray.size() - 1);
        }
    }
}