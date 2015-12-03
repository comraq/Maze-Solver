#include <iostream>
#include <queue>
#include <utility>

#include "convert.hpp"

const int VISITED = 100;
const int AVAILABLE = 255;

int findEntrance(Mat);

int main() {
  string mazeName = "SampleMaze2.png";

  Mat maze = convert(mazeName);
  if (maze.empty()) {
    cout << "Image not found!";
    return -1;
  }

  pair<int, int> start, pixel;
  start = make_pair(0, findEntrance(maze));
  queue<pair<int, int>> pixelQ;
  pixelQ.push(make_pair(start.first, start.second));
  while (!pixelQ.empty()) {
    pixel = pixelQ.front();
    pixelQ.pop();
    maze.data[maze.cols*pixel.first + pixel.second] = VISITED;

    cout << "Row: "<< pixel.first << " Col: " << pixel.second << endl;

    if (pixel.first == maze.cols -1) {
      break;
    }

    if ((pixel.first > 0) && ((int)maze.data[maze.cols*(pixel.first-1) + pixel.second] == AVAILABLE)) {
      pixelQ.push(make_pair(pixel.first - 1, pixel.second));
    }
    if ((pixel.first < maze.rows - 1) && ((int)maze.data[maze.cols*(pixel.first + 1) + pixel.second] == AVAILABLE)) {
      pixelQ.push(make_pair(pixel.first + 1, pixel.second));
    }
    if ((pixel.second > 0) && ((int)maze.data[maze.cols*pixel.first + (pixel.second - 1)] == AVAILABLE)) {
      pixelQ.push(make_pair(pixel.first, pixel.second - 1));
    }
    if ((pixel.second < maze.cols - 1) && ((int)maze.data[maze.cols*pixel.first + (pixel.second + 1)] == AVAILABLE)) {
      pixelQ.push(make_pair(pixel.first, pixel.second + 1));
    }
  }
  
  imwrite(MAZEPATH + "Cropped" + mazeName, maze);

  //cout << "startCol: " << startCol << endl;

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