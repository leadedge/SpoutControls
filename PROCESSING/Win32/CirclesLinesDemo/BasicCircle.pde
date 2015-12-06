class BasicCircle {
 
  float tSize;
  PVector tPos = new PVector();
 
 
  float wander_theta;
  float wander_radius;
 
  // bigger = more edgier, hectic
  float max_wander_offset = 0.1;
  // bigger = faster turns
  float max_wander_radius = 2.5; //// seems to do nothing
 
  BasicCircle(float x, float y, float size) {
 
 
    tPos.x = x;
    tPos.y = y;
    tSize = size;
 
    wander_theta = random(TWO_PI);
    wander_radius = random(max_wander_radius);
  }
 
  void update() {
    float wander_offset = random(-max_wander_offset, max_wander_offset);
    wander_theta += wander_offset;
    checkBoundaries();
    tPos.x += cos(wander_theta);
    tPos.y += sin(wander_theta);
 
    fill(color(255, 255, 255, 125));
    ellipse(tPos.x, tPos.y, tSize, tSize);
  }
 
  void checkBoundaries() {
    if (tPos.x > 800) {
      tPos.x = 0; 
    }
    if (tPos.y > 600) {
      tPos.y = 0; 
    }
    if (tPos.x < 0) {
      tPos.x = 800;
    }
    if (tPos.y < 0) {
      tPos.y = 600;
    }
  }
 
  //// end class
}
