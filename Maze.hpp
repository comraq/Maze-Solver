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

const int BLUE = 0;
const int GREEN = 1;
const int RED = 2;

const int NUM_ADJACENT = 4;

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
    
    const string MAZEPATH = "Mazes/";

    bool isEmpty();
    string getName();
    void setName(string);

    void solve();
    void save();
    void save(string);
    void save(int);
    void save(string, int);

  private:
    Mat sourceImage, processedImage;
    string name;
    int srcRows, srcCols, prcRows, prcCols, offsetRow, offsetCol, exitRow, exitCol;

    void convert();
    void findTopLeft(Mat, int&, int&);
    void findBottomRight(Mat, int&, int&);
    void findEntrance(int&, int&);
    void getAdjacent(int, int, int[]);
    void traceSolution(int, int, int);
    void colourSource(int, int, int);
};

#endif
