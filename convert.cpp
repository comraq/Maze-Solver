#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

const string MAZEPATH = "Mazes/";

int* findStart(cv::Mat);
int* findEnd(cv::Mat);

int main() {
	string mazeName = "SampleMaze1.png";

  string imagePathS = MAZEPATH + mazeName;

  cv::Mat sourceImage = cv::imread(imagePathS);
  if (sourceImage.empty()) {
    return -1;
  }

  cv::Mat bwImage;
  cv::Mat binImage;
  cvtColor(sourceImage, bwImage, CV_BGR2GRAY);
  cv::threshold(bwImage, binImage, 127, 255, CV_THRESH_BINARY);
  //cv::threshold(bwImage, binImage, 0, 255, CV_THRESH_TOZERO);

  //Saving the converted Binary image
  cv::imwrite(MAZEPATH + "Binary" + mazeName, binImage);

  int* temp = findStart(binImage);
  int startRow = temp[0];
  int startCol = temp[1];
  temp = findEnd(binImage);
  int endRow = temp[0];
  int endCol = temp[1];

  cv::Mat cropped = binImage(cv::Range(startRow, endRow+1), cv::Range(startCol, endCol+3));
  cv::imwrite(MAZEPATH + "Cropped" + mazeName, cropped);

  return 0;
}

int* findStart(cv::Mat image) {
  int r, g, b;
  int start[2];
  for (int i = 0; i < image.cols; i++) {
    for (int j = 0; j < image.rows; j++) {
      r = (int)image.data[image.cols * j + i];
      g = (int)image.data[image.cols * j + i + 1];
      b = (int)image.data[image.cols * j + i + 2];
      if (!r && !g && !b) {
        //RGB values are (0, 0, 0) indicating a black pixel
        start[0] = j;
        start[1] = i;
        return start;
      }
    }
  }
}

int* findEnd(cv::Mat image) {
  int r, g, b;
  int end[2]; 
  for (int i = image.cols - 1; i > 0; i--) {
    for (int j = image.rows - 1; j > 0; j--) {
      r = (int)image.data[image.cols * j + i];
      g = (int)image.data[image.cols * j + i + 1];
      b = (int)image.data[image.cols * j + i + 2];
      if (!r && !g && !b) {
        //RGB values are (0, 0, 0) indicating a black pixel
        end[0] = j;
        end[1] = i;
        return end;
      }
    }
  }
}
