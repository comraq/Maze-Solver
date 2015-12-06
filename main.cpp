#include "Maze.hpp"

/* This program parses a black/white image of a maze and saves a copy of the the solved maze with one of the following three colours:
 * - BLUE / GREEN / RED
 * The image file which this programs looks for is located in the path 'Mazes/' with the file name specified by the string mazeName.
 */

int main() {
  string mazeName = "SampleMaze4.png"; //This specifies the file name

  Maze* maze = new Maze(mazeName);
  if(maze->isEmpty()) {
    cout << "Image not found!";
    return -1;
  }

  maze->solve();
  maze->save(RED); //This saves the the solved maze with the solution path highlighted in the colour specified
  delete maze;
  return 0;
}
