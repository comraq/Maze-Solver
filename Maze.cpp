#include "Maze.hpp"

/* Constructor and Destructor */

Maze::Maze(string name) {
  this->name = name;
  sourceImage = imread(MAZEPATH + name);
  srcRows = sourceImage.rows;
  srcCols = sourceImage.cols;
  convert();
  prcRows = processedImage.rows;
  prcCols = processedImage.cols;
  exitRow = -1;
  exitCol = -1;
}

Maze::~Maze() {
  //Nothing extra to cleanup
}

/* Public methods */

bool Maze::isEmpty() {
  return sourceImage.empty();
}

string Maze::getName() {
  return name;
}

void Maze::setName(string name) {
  this->name = name;
}

void Maze::solve() {
  queue<pair<int, int>> pixelQueue;
  int row, col;
  int adjacent[NUM_ADJACENT];
  pair<int, int> pixel;
  findEntrance(pixel.first, pixel.second);
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
      exitRow = row;
      exitCol = col;
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

void Maze::save() {
  save(name, RED);
}

void Maze::save(string name) {
  save(name, RED);
}

void Maze::save(int colour) {
  save(name, colour);
}

void Maze::save(string name, int colour) {
  if (exitRow == -1) {
    cout << "Maze not yet solved!" << endl;
  } else {
    traceSolution(exitRow, exitCol, colour);
    imwrite(MAZEPATH + "Solved" + name, sourceImage);
  }
}

/* Below are private methods */

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


void Maze::findEntrance(int& row, int& col) {
  int data;
  for (int c = 0; c < prcCols; ++c) {
    data = (int)processedImage.data[c];
    if (data == AVAILABLE) {
      //Entrance found in top row
      row = 0;
      col = c;
      return;
    }
  }
  for (int r = 0; r < prcRows; ++r) {
    data = (int)processedImage.data[prcCols * r];
    if (data == AVAILABLE) {
      //Entrance found in left col
      row = r;
      col = 0;
      return;
    }
  }
  row = -1;
  col = -1;
  return;
}

void Maze::getAdjacent(int row, int col, int adjacent[]) {
  adjacent[ABOVE] = (row > 0) ? (int)processedImage.data[prcCols * (row - 1) + col] : WALL;
  adjacent[BELOW] = (row < prcRows - 1) ? (int)processedImage.data[prcCols * (row + 1) + col] : WALL;
  adjacent[LEFT] = (col > 0) ? (int)processedImage.data[prcCols * row + (col - 1)] : WALL;
  adjacent[RIGHT] = (col < prcCols - 1) ? (int)processedImage.data[prcCols * row + (col + 1)] : WALL;
}

void Maze::traceSolution(int row, int col, int colour) {
  //Tail recursive versions of this method will lead to stack overflow
  int prev;
  do {
    prev = (int)processedImage.data[prcCols*row + col] - VISITED;
    colourSource(row, col, colour, prev);
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

void Maze::colourSource(int row, int col, int colour, int prev) {
  int r = row - SOLUTION_WIDTH + 1;
  int c = col - SOLUTION_WIDTH + 1;
  if (prev == ABOVE || prev == BELOW) {
    for (int j = 1; j <= SOLUTION_WIDTH; ++j) {
      if ((int)processedImage.data[prcCols*row + (col - j)] == WALL) {
        c = col - j + 1;
        break;
      } 
    }
    for (int j = 0; j < SOLUTION_WIDTH; ++j) {
      if ((int)processedImage.data[prcCols*row + (c + j)] == WALL) {
        break;
      }
      for (int i = 0; i < 3; ++i) {
        sourceImage.data[srcCols*(row + offsetRow) * 3 + (c + offsetCol + j) * 3 + i] = (i == colour) ? 255 : 0;
      }
    }
  } else if (prev == LEFT || prev == RIGHT) {
    for (int j = 1; j <= SOLUTION_WIDTH; ++j) {
      if ((int)processedImage.data[prcCols*(row - j) + col] == WALL) {
        r = row - j + 1;
        break;
      }
    }
    for (int j = 0; j < SOLUTION_WIDTH; ++j) {
      if ((int)processedImage.data[prcCols*(r + j) + col] == WALL) {
        break;
      }
      for (int i = 0; i < 3; ++i) {
        sourceImage.data[srcCols*(r + offsetRow + j) * 3 + (col + offsetCol) * 3 + i] = (i == colour) ? 255 : 0;
      }
    }
  } else {
    for (int i = 0; i < 3; ++i) {
      sourceImage.data[srcCols*(row + offsetRow) * 3 + (col + offsetCol) * 3 + i] = (i == colour) ? 255 : 0;
    }
  }
}
