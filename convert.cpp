#include "Convert.hpp"

Mat convert(String mazeName) {
  string imagePath = MAZEPATH + mazeName;

  Mat sourceImage = imread(imagePath);
  if (sourceImage.empty()) {
    return sourceImage;
  }

  Mat bwImage, binImage, cropRef, cropImage;
  cvtColor(sourceImage, bwImage, CV_BGR2GRAY); //Convert original image to grayscale
  threshold(bwImage, binImage, 127, 255, CV_THRESH_BINARY); //Convert grayscale to binary

  int startRow, startCol, endRow, endCol;
  findTopLeft(binImage, startRow, startCol);
  findBottomRight(binImage, endRow, endCol);
  cropRef = binImage(Range(startRow, endRow + 1), Range(startCol, endCol + 1)); //Cropping the image, removing excess borders around the maze
  cropRef.copyTo(cropImage);

  //Saving the intermediate images
  imwrite(MAZEPATH + "Binary" + mazeName, binImage);
  imwrite(MAZEPATH + "Cropped" + mazeName, cropImage);

  return cropImage;
}

void findTopLeft(Mat image, int& row, int& col) {
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

void findBottomRight(Mat image, int& row, int& col) {
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
