#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>
#include <iostream>

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
  cvtColor(sourceImage, bwImage, CV_BGR2GRAY);

  cv::imwrite(MAZEPATH + "Gray" + mazeName, bwImage);

  return 0;
}
