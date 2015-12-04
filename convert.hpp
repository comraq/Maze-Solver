#ifndef _CONVERT_HPP
#define _CONVERT_HPP

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>

using namespace std;
using namespace cv;

const string MAZEPATH = "Mazes/";

Mat convert(String);
void findTopLeft(Mat, int&, int&);
void findBottomRight(Mat, int&, int&);

#endif
