#include "Maze.hpp"

int main() {
  string mazeName = "SampleMaze1.png";

  Maze* maze = new Maze(mazeName);
  if(maze->isEmpty()) {
    cout << "Image not found!";
    return -1;
  }

  maze->solve();
  maze->save();
  return 0;
}
