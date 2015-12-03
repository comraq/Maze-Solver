#include <iostream>

#include "convert.hpp"

int main() {
  string mazeName = "SampleMaze1.png";

  Mat mazeImage = convert(mazeName);
  if (mazeImage.empty()) {
    cout << "Image not found!";
    return -1;
  }

  return 0;
}