#include <iostream>

#include "convert.hpp"

int findEntrance(Mat);

int main() {
  string mazeName = "SampleMaze2.png";

  Mat maze = convert(mazeName);
  if (maze.empty()) {
    cout << "Image not found!";
    return -1;
  }

  int startRow = 0;
  int startCol = findEntrance(maze);

  return 0;
}

int findEntrance(Mat maze) {
  int pixel;
  for (int c = 0; c < maze.cols; ++c) {
    pixel = (int)maze.data[c];
    if (pixel > 0) {
      //Pixel intensity non-zero indicating white pixel
      return c;
    }
  }
}