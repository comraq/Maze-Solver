#ifndef _MAZE_HPP
#define _MAZE_HPP

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>
#include <iostream>
#include <queue>
#include <utility>

using namespace std;
using namespace cv;

class Maze {
  public:
    Maze(string);
    ~Maze();

    const int WALL = 0;
    const int AVAILABLE = 255;
    const int VISITED = 200;
    const int SOLUTION = 100;

    const int START = -1;
    const int ABOVE = 0;
    const int BELOW = 1;
    const int LEFT = 2;
    const int RIGHT = 3;

    static const int NUM_ADJACENT = 4;

    const string MAZEPATH = "Mazes/";

    bool isEmpty();
    string getName();

    void solve();
    void save();
    void setName(string);

  private:
    Mat sourceImage, processedImage;
    string name;
    int prcRows, prcCols, offsetRow, offsetCol;

    void convert();
    void findEntrance(pair<int, int>&);
    void getAdjacent(int, int, int[]);
    void traceSolution(int, int);
    void findTopLeft(Mat, int&, int&);
    void findBottomRight(Mat, int&, int&);
};

#endif
