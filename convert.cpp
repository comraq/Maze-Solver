#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>

using namespace std;
 
const string MAZEPATH = "Mazes/";

int main() {
  cout << MAZEPATH + "SampleMaze1.jpg" << endl;

  string imagePathS = MAZEPATH + "SampleMaze1.jpg";
  char *imagePathC = new char[imagePathS.length() + 1];
  strcpy(imagePathC, imagePathS.c_str());

  cv::Mat sourceImage = cv::imread(imagePathC);
  if (sourceImage.empty()) {
    return -1;
  }

  cv::Mat bwImage;
  cv::cvtColor(sourceImage, bwImage, CV_BGR2GRAY);

  return 0;
}
