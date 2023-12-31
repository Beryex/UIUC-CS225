/* Your code here! */
/**
 * @file maze.h
 * Each SquareMaze object represents a randomly-generated square maze and its solution
 * 
 */

#ifndef MAZE_H
#define MAZE_H

#include <map>
#include <random>
#include <stdlib.h>
#include <time.h>
#include "cs225/PNG.h"
#include "dsets.h"

using namespace cs225;
using namespace std;

/**
 *  Each SquareMaze object represents a randomly-generated square maze and its solution
 *  "square maze" mean a maze in which each cell is a square
 */

class SquareMaze
{
    public:
    /**
     * @brief Default constructor
     * 
     */
    SquareMaze();

    /**
     * @brief Makes a new SquareMaze of the given height and width
     * 
     * @param width The width of the SquareMaze (number of cells)
     * @param height The height of the SquareMaze (number of cells)
     */
    void makeMaze(int width, int height);

    /**
     * @brief Determine whether it is possible to travel 
     * in the given direction from the square at coordinates (x,y)
     * 
     * @param x The x coordinate of the current cell
     * @param y The y coordinate of the current cell
     * @param dir The desired direction to move from the current cell
     *          dir = 0 represents a rightward step (+1 to the x coordinate)
     *          dir = 1 represents a downward step (+1 to the y coordinate)
     *          dir = 2 represents a leftward step (-1 to the x coordinate)
     *          dir = 3 represents an upward step (-1 to the y coordinate)
     * 
     * @return A bool value indecates whether can travel in the specified direction
     */
    bool canTravel(int x, int y, int dir) const;

    /**
     * @brief Sets whether or not the specified wall exists
     * 
     * @param x The x coordinate of the current cell
     * @param y The y coordinate of the current cell
     * @param dir Either 0 (right) or 1 (down), which specifies which wall to set
     * @param exists Indicates whether set the wall to exist successfully
     */
    void setWall(int x, int y, int dir, bool exists);

    /**
     * @brief Solves this SquareMaze
     * 
     * @return a vector of directions taken to solve the maze
     */
    vector<int> solveMaze();

    /**
     * @brief Draws the maze without the solution
     * 
     * @return a PNG of the unsolved Square Maze
     */
    PNG* drawMaze() const;

    /**
     * @brief This function calls drawMaze, then solveMaze; 
     *        it modifies the PNG from drawMaze to show the solution vector and the exit
     * 
     * @return a PNG of the solved SquareMaze
     */
    PNG* drawMazeWithSolution();

    private:
    int width_;
    int height_;
    // first in pair means right edge, second means bottom edge
    map<int, pair<bool, bool>> wall_;

    /**
     * @brief helper recursive function using DFS for solveMaze
     * 
     * @param path the input vector that stores the current dealing path's each step dir
     * @param result the input vector that stores the longest path's each step dir
     * @param mark the input vector that mark whether a cell has been visited
     * @param curBest the current longest path's length
     * @param curL the current path's length
     * @param x the current cell's x index
     * @param y the current cell's y index
     */
    void solve_DFS(vector<int>& path, vector<int>& result, vector<bool>& mark, int& curBest, int curL, int x, int y);
};

#endif /* MAZE_H*/