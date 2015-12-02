#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

const string MAZEPATH = "Mazes/";

int main() {
	string mazeName = "SampleMaze3.png";

  string imagePathS = MAZEPATH + mazeName;

  cv::Mat sourceImage = cv::imread(imagePathS);
  if (sourceImage.empty()) {
    return -1;
  }

  cv::Mat bwImage;
  cv::Mat binImage;
  cvtColor(sourceImage, bwImage, CV_BGR2GRAY);
  cv::threshold(bwImage, binImage, 254, 255, CV_THRESH_BINARY);

  //Saving the converted GrayScale and Binary images
  cv::imwrite(MAZEPATH + "Gray" + mazeName, bwImage);
  cv::imwrite(MAZEPATH + "Binary" + mazeName, binImage);

  fstream binImageText;
  string outPath = MAZEPATH + "Binary" + mazeName.substr(0, mazeName.length() - 4) + "Text.txt";
  binImageText.open(outPath.c_str(), fstream::out);

  unsigned char *input = (unsigned char*)(binImage.data);

  int i, j;
  for (int i = 0; i < binImage.cols; i++) {
    for (int j = 0; j < binImage.rows; j++) {
      binImageText << (int)input[binImage.cols * j + i] << " ";
      binImageText << (int)input[binImage.cols * j + i + 1] << " ";
      binImageText << (int)input[binImage.cols * j + i + 2] << "\n";
    }
  }

  binImageText.close();

  return 0;
}
