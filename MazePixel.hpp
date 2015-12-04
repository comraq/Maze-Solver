#ifndef _MAZEPIXEL_HPP
#define _MAZEPIXEL_HPP

#include <cstdlib>

class MazePixel{
  public:
    MazePixel(int, int);
    MazePixel(int, int, MazePixel*);
    ~MazePixel();

    int getRow();
    int getCol();
    MazePixel* getPrevPixel();
    
    void setRowCol(int, int);
    void setPrevPixel(MazePixel*);

  private:
    int row, col;
    MazePixel* prevPixel;
};
#endif
