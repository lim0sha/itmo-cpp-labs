#include "RubicsCube.h"

int main() {
  RubicsCube RC = RubicsCube();
  GlMonitor *viewer = createOpenglViewer();
  viewer->init();
  viewer->init_cube(RC);
  viewer->run();
  return 0;
}