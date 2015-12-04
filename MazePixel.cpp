#include "MazePixel.hpp"

MazePixel::MazePixel(int row, int col) {
  this->row = row;
  this->col = col;
  prevPixel = NULL;
}

MazePixel::MazePixel(int row, int col, MazePixel* prevPixel) {
  this->row = row;
  this->col = col;
  this->prevPixel = prevPixel;
}

void MazePixel::setRowCol(int row, int col) {
  this->row = row;
  this->col = col;
}

void MazePixel::setPrevPixel(MazePixel* prevPixel) {
  this->prevPixel = prevPixel;
}

int MazePixel::getRow() {
  return row;
}

int MazePixel::getCol() {
  return col;
}

MazePixel* MazePixel::getPrevPixel() {
  return prevPixel;
}

MazePixel::~MazePixel() {
  //No extra clean-up necessary
}