#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>

using namespace std;
 
const string MAZEPATH = "Mazes/";

int main() {
  cout << MAZEPATH + "SampleMaze1.jpg" << endl;

  ifstream image;
  ifstream image2;
  ofstream binaryImage;
  ofstream binaryImage2;

  string imagePathS = MAZEPATH + "SampleMaze1.jpg"; 
  char *imagePathC = new char[imagePathS.length() + 1];
  strcpy(imagePathC, imagePathS.c_str());

  image.open(imagePathC, fstream::in);
  image2.open("Mazes/SampleMaze2.png", fstream::in);

  if (!image || !image2) {
    cout << "Error opening image" << endl;
    return -1;
  }

  binaryImage.open("abcTestBinary.txt", fstream::out);
  binaryImage2.open("abcTestBinary2.txt", fstream::out);
  while(image.good()) {
    int c = abs((unsigned int) image.get());
    if (!image) {
      break;
    }
    binaryImage << c;
    binaryImage << " ";
  }

  while(image2.good()) {
    int c = abs((unsigned int) image2.get());
    if (!image2) {
      break;
    }
    binaryImage2 << c;
    binaryImage2 << " ";
  }
  
  image.close();
  image2.close();
  binaryImage.close();
  binaryImage2.close();
  return 0;
}
