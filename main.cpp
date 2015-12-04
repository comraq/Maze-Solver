#include <iostream>
#include <queue>
#include <utility>

#include "Convert.hpp"

const int SOLUTION = 100;
const int VISITED = 200;
//const int WALL = 0;
const int AVAILABLE = 255;

const int ABOVE = 1;
const int BELOW = 2;
const int LEFT = 3;
const int RIGHT = 4;

const int NUM_ADJACENT = 4;

void findEntrance(Mat, pair<int, int>&);
void getAdjacent(Mat, int, int, int[]);
void traceSolution(Mat, int, int);

int main() {
  string mazeName = "SampleMaze4.png";

  Mat maze = convert(mazeName);
  if (maze.empty()) {
    cout << "Image not found!";
    return -1;
  }
  
  queue<pair<int, int>> pixelQueue;
  int row, col;
  int adjacent[NUM_ADJACENT];
  pair<int, int> pixel;
  findEntrance(maze, pixel);
  if (pixel.first == -1) {
    cout << "Maze entrance not found in top row or left column!" << endl;
    return -1;
  }
  pixelQueue.push(pixel); 
  maze.data[maze.cols*(pixel.first) + pixel.second] = VISITED;
  while (!pixelQueue.empty()) {
    pixel = pixelQueue.front();
    pixelQueue.pop();
    row = pixel.first;
    col = pixel.second;

    if (row == maze.rows - 1 || col == maze.cols - 1) {
      break;
    }

    getAdjacent(maze, row, col, adjacent);
    if (adjacent[0] == AVAILABLE) {
      pixelQueue.push(make_pair(row - 1, col));
      maze.data[maze.cols*(row - 1) + col] = VISITED + BELOW;
    }
    if (adjacent[1] == AVAILABLE) {
      pixelQueue.push(make_pair(row + 1, col));
      maze.data[maze.cols*(row + 1) + col] = VISITED + ABOVE;
    }
    if (adjacent[2] == AVAILABLE) {
      pixelQueue.push(make_pair(row, col - 1));
      maze.data[maze.cols*row + (col - 1)] = VISITED + RIGHT;
    }
    if (adjacent[3] == AVAILABLE) {
      pixelQueue.push(make_pair(row, col + 1)); 
      maze.data[maze.cols*row + (col + 1)] = VISITED + LEFT;
    }
  }

  traceSolution(maze, row, col);
  cv::imwrite(MAZEPATH + "Cropped" + mazeName, maze);
  return 0;
}

void findEntrance(Mat maze, pair<int, int>& pixel) {
  int data;
  for (int c = 0; c < maze.cols; ++c) {
    data = (int)maze.data[c];
    if (data == AVAILABLE) {
      //Entrance found in top row
      pixel = make_pair(0, c);
      return;
    }
  }
  for (int r = 0; r < maze.rows; ++r) {
    data = (int)maze.data[maze.cols * r];
    if (data == AVAILABLE) {
      //Entrance found in left col
      pixel = make_pair(r, 0);
      return;
    }
  }
  pixel = make_pair(-1, -1);
  return;
}

void getAdjacent(Mat maze, int row, int col, int adjacent[]) {
  adjacent[0] = (row > 0)? (int)maze.data[maze.cols * (row - 1) + col] : 0;
  adjacent[1] = (row < maze.rows - 1)? (int)maze.data[maze.cols * (row + 1) + col] : 0;
  adjacent[2] = (col > 0)? (int)maze.data[maze.cols * row + (col - 1)] : 0;
  adjacent[3] = (col < maze.cols - 1)? (int)maze.data[maze.cols * row + (col + 1)] : 0;
}

void traceSolution(Mat maze, int row, int col) {
  //Tail recursive versions of this method will lead to stack overflow
  int prev;
  do {
    prev = (int)maze.data[maze.cols*row + col] - VISITED;
    maze.data[maze.cols*row + col] = SOLUTION;
    if (prev == ABOVE) {
      --row;
    } else if (prev == BELOW) {
      ++row;
    } else if (prev == LEFT) {
      --col;
    } else if (prev == RIGHT) {
      ++col;
    }
  } while (prev != 0);
}