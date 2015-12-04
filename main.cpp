#include <iostream>
#include <queue>
#include <utility>

#include "Convert.hpp"
#include "MazePixel.hpp"

const int DEADEND = 100;
const int VISITED = 200;
//const int WALL = 0;
const int AVAILABLE = 255;

MazePixel* findEntrance(Mat);
void getAdjacent(Mat, int, int, int[]);

int main() {
  string mazeName = "SampleMaze1.png";

  Mat maze = convert(mazeName);
  if (maze.empty()) {
    cout << "Image not found!";
    return -1;
  }
  
  queue<MazePixel*> pixelQueue;
  int row, col, queueSize;
  int adjacent[4];
  MazePixel* pixel = findEntrance(maze);
  if (!pixel) {
    cout << "Maze entrance not found in top row or left column!" << endl;
    return -1;
  }
  pixelQueue.push(pixel); 
  maze.data[maze.cols*pixel->getRow()+ pixel->getCol()] = VISITED;
  while (!pixelQueue.empty()) {
    pixel = pixelQueue.front();
    pixelQueue.pop();
    row = pixel->getRow();
    col = pixel->getCol();

    if (row == maze.rows - 1) {
      break;
    }

    //queueSize = pixelQueue.size();
    
    getAdjacent(maze, row, col, adjacent);
    if (adjacent[0] == AVAILABLE) {
      pixelQueue.push(new MazePixel(row - 1, col, pixel));
      maze.data[maze.cols*(row - 1) + col] = VISITED;
    }
    if (adjacent[1] == AVAILABLE) {
      pixelQueue.push(new MazePixel(row + 1, col, pixel));
      maze.data[maze.cols*(row + 1) + col] = VISITED;
    }
    if (adjacent[2] == AVAILABLE) {
      pixelQueue.push(new MazePixel(row, col - 1, pixel));
      maze.data[maze.cols*row + (col - 1)] = VISITED;
    }
    if (adjacent[3] == AVAILABLE) {
      pixelQueue.push(new MazePixel(row, col + 1, pixel));
      maze.data[maze.cols*row + (col + 1)] = VISITED;
    }

    /*if (queueSize == pixelQueue.size()) {
      markDead(maze, pixel);
    }*/
    delete pixel;
  }

  cv::imwrite(MAZEPATH + "Cropped" + mazeName, maze);
  return 0;
}

/*void markDead(Mat maze, MazePixel* pixel) {
  int row = pixel->getRow();
  int col = pixel->getCol();
  int prevRow = pixel->getPrevRow();
  int prevCol = pixel->getPrevCol();
  maze.data[maze.cols*row + col] = DEADEND;
  getAdjacent(pixel, above, below, left, right);
}*/

void getAdjacent(Mat maze, int row, int col, int adjacent[]) {
  adjacent[0] = (row > 0)? (int)maze.data[maze.cols * (row - 1) + col] : 0;
  adjacent[1] = (row < maze.rows - 1)? (int)maze.data[maze.cols * (row + 1) + col] : 0;
  adjacent[2] = (col > 0)? (int)maze.data[maze.cols * row + (col - 1)] : 0;
  adjacent[3] = (col < maze.cols - 1)? (int)maze.data[maze.cols * row + (col + 1)] : 0;
}

MazePixel* findEntrance(Mat maze) {
  int data;
  for (int c = 0; c < maze.cols; ++c) {
    data = (int)maze.data[c];
    if (data == AVAILABLE) {
      //Entrance found in top row
      return new MazePixel(0, c);
    }
  }
  for (int r = 0; r < maze.rows; ++r) {
    data = (int)maze.data[maze.cols * r];
    if (data == AVAILABLE) {
      //Entrance found in left col
      return new MazePixel(r, 0);
    }
  }
  return NULL;
}