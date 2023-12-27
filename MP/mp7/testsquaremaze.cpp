/**
 * @file testsquaremaze.cpp
 * Performs basic tests of SquareMaze.
 * @date April 2007
 * @author Jonathan Ray
 */

#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    SquareMaze m;
    SquareMaze check;
    SquareMaze my;
    m.makeMaze(50, 50);
    my.makeMaze(2, 2);
    check.makeMaze(50,50);
    PNG* check_1 = check.drawMaze();
    check_1->writeToFile("check1.png");
    delete check_1;
    for(int x = 0; x < 50; x++){
        for(int y = 0; y < 50; y++){
            check.setWall(x, y, 0, !m.canTravel(x,y,0));
            check.setWall(x, y, 1, !m.canTravel(x,y,1));
        }
    }
    std::cout << "MakeMaze complete" << std::endl;

    PNG* unsolved = m.drawMaze();
    PNG* my_unsolved = my.drawMaze();
    PNG* check_2 = check.drawMaze();
    unsolved->writeToFile("unsolved.png");
    my_unsolved->writeToFile("my_unsolved.png");
    check_2->writeToFile("check2.png");
    delete unsolved;
    delete my_unsolved;
    delete check_2;
    std::cout << "drawMaze complete" << std::endl;

    std::vector<int> sol = m.solveMaze();
    std::vector<int> my_sol = my.solveMaze();
    std::cout << "solveMaze complete" << std::endl;

    PNG* solved = m.drawMazeWithSolution();
    PNG* my_solved = my.drawMazeWithSolution();
    solved->writeToFile("solved.png");
    my_solved->writeToFile("my_solved.png");
    delete solved;
    delete my_solved;
    std::cout << "drawMazeWithSolution complete" << std::endl; 

    return 0;
}
