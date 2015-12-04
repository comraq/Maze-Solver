#include "Maze.hpp"

Maze::Maze(string name) {
  this->name = name;
  sourceImage = imread(MAZEPATH + name);
  convert();
  prcRows = processedImage.rows;
  prcCols = processedImage.cols;
}

bool Maze::isEmpty() {
  return sourceImage.empty();
}

void Maze::convert() {
  Mat temp;
  cvtColor(sourceImage, temp, CV_BGR2GRAY); //Convert original image to grayscale
  threshold(temp, temp, 127, 255, CV_THRESH_BINARY); //Convert grayscale to binary

  int endRow, endCol;
  findTopLeft(temp, offsetRow, offsetCol);
  findBottomRight(temp, endRow, endCol);
  temp = temp(Range(offsetRow, endRow + 1), Range(offsetCol, endCol + 1)); //Cropping the image, removing excess borders around the maze
  temp.copyTo(processedImage);
}

void Maze::findTopLeft(Mat image, int& row, int& col) {
  int pixel;
  for (int r = 0; r < image.rows; ++r) {
    for (int c = 0; c < image.cols; ++c) {
      pixel = (int)image.data[image.cols * r + c];
      if (!pixel) {
        //Pixel intensity is 0 indicating a black pixel
        row = r;
        col = c;
        return;
      }
    }
  }
}

void Maze::findBottomRight(Mat image, int& row, int& col) {
  int pixel;
  for (int r = image.rows - 1; r >= 0; --r) {
    for (int c = image.cols - 1; c >= 0; --c) {
      pixel = (int)image.data[image.cols * r + c];
      if (!pixel) {
        //Pixel intensity is 0 indicating a black pixel
        row = r;
        col = c;
        return;
      }
    }
  }
}

void Maze::save() {
  imwrite(MAZEPATH + "Solved" + name, processedImage);
}

void Maze::setName(string name) {
  this->name = name;
}

string Maze::getName() {
  return name;
}

void Maze::solve() {
  queue<pair<int, int>> pixelQueue;
  int row, col;
  int adjacent[NUM_ADJACENT];
  pair<int, int> pixel;
  findEntrance(pixel);
  if (pixel.first == -1) {
    cout << "Maze entrance not found in top row or left column!" << endl;
    return;
  }
  pixelQueue.push(pixel);
  processedImage.data[prcCols*(pixel.first) + pixel.second] = VISITED + START;
  while (!pixelQueue.empty()) {
    pixel = pixelQueue.front();
    pixelQueue.pop();
    row = pixel.first;
    col = pixel.second;

    if (row == prcRows - 1 || col == prcCols - 1) {
      traceSolution(row, col);
      return;
    }

    getAdjacent(row, col, adjacent);
    if (adjacent[ABOVE] == AVAILABLE) {
      pixelQueue.push(make_pair(row - 1, col));
      processedImage.data[prcCols*(row - 1) + col] = VISITED + BELOW;
    }
    if (adjacent[BELOW] == AVAILABLE) {
      pixelQueue.push(make_pair(row + 1, col));
      processedImage.data[prcCols*(row + 1) + col] = VISITED + ABOVE;
    }
    if (adjacent[LEFT] == AVAILABLE) {
      pixelQueue.push(make_pair(row, col - 1));
      processedImage.data[prcCols*row + (col - 1)] = VISITED + RIGHT;
    }
    if (adjacent[RIGHT] == AVAILABLE) {
      pixelQueue.push(make_pair(row, col + 1));
      processedImage.data[prcCols*row + (col + 1)] = VISITED + LEFT;
    }
  }
}

void Maze::findEntrance(pair<int, int>& pixel) {
  int data;
  for (int c = 0; c < prcCols; ++c) {
    data = (int)processedImage.data[c];
    if (data == AVAILABLE) {
      //Entrance found in top row
      pixel = make_pair(0, c);
      return;
    }
  }
  for (int r = 0; r < prcRows; ++r) {
    data = (int)processedImage.data[prcCols * r];
    if (data == AVAILABLE) {
      //Entrance found in left col
      pixel = make_pair(r, 0);
      return;
    }
  }
  pixel = make_pair(-1, -1);
  return;
}

void Maze::getAdjacent(int row, int col, int adjacent[]) {
  adjacent[ABOVE] = (row > 0) ? (int)processedImage.data[prcCols * (row - 1) + col] : WALL;
  adjacent[BELOW] = (row < prcRows - 1) ? (int)processedImage.data[prcCols * (row + 1) + col] : WALL;
  adjacent[LEFT] = (col > 0) ? (int)processedImage.data[prcCols * row + (col - 1)] : WALL;
  adjacent[RIGHT] = (col < prcCols - 1) ? (int)processedImage.data[prcCols * row + (col + 1)] : WALL;
}

void Maze::traceSolution(int row, int col) {
  //Tail recursive versions of this method will lead to stack overflow
  int prev;
  do {
    prev = (int)processedImage.data[prcCols*row + col] - VISITED;
    processedImage.data[prcCols*row + col] = SOLUTION;
    if (prev == ABOVE) {
      --row;
    } else if (prev == BELOW) {
      ++row;
    } else if (prev == LEFT) {
      --col;
    } else if (prev == RIGHT) {
      ++col;
    }
  } while (prev != START);
}

Maze::~Maze() {
  //Nothing extra to cleanup
}