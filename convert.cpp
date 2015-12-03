#include "convert.hpp"

Mat convert(String mazeName) {
  string imagePath = MAZEPATH + mazeName;

  Mat sourceImage = imread(imagePath);
  if (sourceImage.empty()) {
    return sourceImage;
  }

  Mat bwImage;
  Mat binImage;
  Mat cropImage;
  cvtColor(sourceImage, bwImage, CV_BGR2GRAY); //Convert original image to grayscale
  threshold(bwImage, binImage, 127, 255, CV_THRESH_BINARY); //Convert grayscale to binary

  int startRow, startCol, endRow, endCol;
  findStart(binImage, &startRow, &startCol);
  findEnd(binImage, &endRow, &endCol);
  cropImage = binImage(Range(startRow, endRow + 1), Range(startCol, endCol + 3)); //Cropping the image, removing excess borders around the maze

  //Saving the intermediate images
  imwrite(MAZEPATH + "Binary" + mazeName, binImage);
  imwrite(MAZEPATH + "Cropped" + mazeName, cropImage);

  return cropImage;
}

void findStart(Mat image, int* row, int* col) {
  int r, g, b;
  for (int i = 0; i < image.cols; i++) {
    for (int j = 0; j < image.rows; j++) {
      r = (int)image.data[image.cols * j + i];
      g = (int)image.data[image.cols * j + i + 1];
      b = (int)image.data[image.cols * j + i + 2];
      if (!r && !g && !b) {
        //RGB values are (0, 0, 0) indicating a black pixel
        *row = j;
        *col = i;
        return;
      }
    }
  }
}

void findEnd(Mat image, int* row, int* col) {
  int r, g, b;
  int end[2]; 
  for (int i = image.cols - 1; i > 0; i--) {
    for (int j = image.rows - 1; j > 0; j--) {
      r = (int)image.data[image.cols * j + i];
      g = (int)image.data[image.cols * j + i + 1];
      b = (int)image.data[image.cols * j + i + 2];
      if (!r && !g && !b) {
        //RGB values are (0, 0, 0) indicating a black pixel
        *row = j;
        *col = i;
        return;
      }
    }
  }
}
