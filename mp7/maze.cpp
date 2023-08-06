/* Your code here! */
/**
 * @file maze.cpp
 * Implementation of SquareMaze
 * 
 */

#include "maze.h"

SquareMaze::SquareMaze(){
    /* nothing here to initialize */
}

void SquareMaze::makeMaze(int width, int height){
    /* use functions from random library to create random number */
    srand((unsigned)time(NULL));
    random_device seed;
    mt19937 engine(seed());
    uniform_int_distribution<int> distrib(0, 1);

    /* update private attributes */
    width_ = width;
    height_ = height;
    DisjointSets elems_;
    elems_.addelements(width * height);
    wall_.clear();
    for(int i = 0; i < width * height; i++){
        wall_[i] = pair<bool, bool>(true, true);
    }

    /* deleting the wall randomly except the broader and make no cycle */
    // choose the cell with index 0 as the base cell set
    while(elems_.size(0) < width * height){
        // select random cell to delete wall except the right bottom corner one
        int random_index = rand() % (width * height - 1);
        // find it's bottom and right adjacent cell
        int dir;
        int adjacent_index;
        if((random_index + 1) % width == 0){
            dir = 1;
            adjacent_index = random_index + width;
        } else if(random_index >= width * (height - 1)){
            dir = 0;
            adjacent_index = random_index + 1;
        } else {
            if(distrib(engine) % 2 == 1){
                dir = 1;
                adjacent_index = random_index + width;
            } else {
                dir = 0;
                adjacent_index = random_index + 1;
            }
        }
        // delete wall between them only when they are not in the same set
        if(elems_.find(random_index) != elems_.find(adjacent_index)){
            elems_.setunion(random_index, adjacent_index);
            if(dir == 0) wall_[random_index].first = false;
            if(dir == 1) wall_[random_index].second = false;
        }
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const{
    /* check boundary first and then wall*/
    if(dir == 0){
        if(x < width_ - 1 && wall_.at(x + y * width_).first == false) return true;
        return false;
    }
    if(dir == 1){
        if(y < height_  - 1 && wall_.at(x + y * width_).second == false) return true;
        return false;
    }
    if(dir == 2){
        if(x > 0 && wall_.at(x - 1 + y * width_).first == false) return true;
        return false;
    }
    if(dir == 3){
        if(y > 0 && wall_.at(x + (y-1) * width_).second == false) return true;
        return false;
    }
    return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
    /* modify the wall value */
    if(dir == 0) wall_.at(x + y * width_).first = exists;
    if(dir == 1) wall_.at(x + y * width_).second = exists;
}

vector<int> SquareMaze::solveMaze(){
    /* check special case */
    if(height_ == 1){
        vector<int> result;
        result.resize(width_ - 1, 0);
        return result;
    }
    
    vector<int> result;
    vector<int> path;
    vector<bool> mark;
    int curBest = -1;
    mark.resize(width_ * height_, false);
    mark[0] = true;

    /* use DFS to find the path with largers length */
    solve_DFS(path, result, mark, curBest, 0, 0, 0);

    return result;
}

void SquareMaze::solve_DFS(vector<int>& path, vector<int>& result, vector<bool>& mark, int& curBest, int curL, int x, int y){
    /* check and update value if get the bottom most line */
    if(y == height_ - 1){
        if(curL >= curBest){
            curBest = curL;
            result.assign(path.begin(), path.end());
        }
    }

    /* find other possible paths */
    if(canTravel(x, y, 0) && mark[x + 1 + y * width_] == false){
        path.push_back(0);
        mark[x + 1 + y * width_] = true;
        solve_DFS(path, result, mark, curBest, curL + 1, x + 1, y);
        path.erase(path.end() - 1);
    }
    if(canTravel(x, y, 1) && mark[x + (y + 1) * width_] == false){
        path.push_back(1);
        mark[x + (y + 1) * width_] = true;
        solve_DFS(path, result, mark, curBest, curL + 1, x, y + 1);
        path.erase(path.end() - 1);
    }
    if(canTravel(x, y, 2) && mark[x - 1 + y * width_] == false){
        path.push_back(2);
        mark[x - 1 + y * width_] = true;
        solve_DFS(path, result, mark, curBest, curL + 1, x - 1, y);
        path.erase(path.end() - 1);
    }
    if(canTravel(x, y, 3) && mark[x + (y - 1) * width_] == false){
        path.push_back(3);
        mark[x + (y - 1) * width_] = true;
        solve_DFS(path, result, mark, curBest, curL + 1, x, y - 1);
        path.erase(path.end() - 1);
    }
}

PNG* SquareMaze::drawMaze() const{
    PNG* ret = new PNG(width_ * 10 + 1, height_ * 10 + 1);

    /* Blaken the entire topmost row and left most column of pixels except for entrance */
    for(int i = 10; i < ret->width(); i++){
        ret->getPixel(i, 0)->l = 0; 
    }
    for(int i = 0; i < ret->height(); i++){
        ret->getPixel(0, i)->l = 0;
    }

    /* draw each cell */
    for(const pair<int, pair<bool, bool>> cell : wall_){
        int x = cell.first % width_;
        int y = (cell.first - x) / width_;
        if(cell.second.first){
            for(int i = 0; i <=  10; i++){
                ret->getPixel((x + 1) * 10, y * 10 + i)->l = 0;
            }
        }
        if(cell.second.second){
            for(int i = 0; i <= 10; i++){
                ret->getPixel(x * 10 + i, (y + 1) * 10)->l = 0;
            }
        }
    }

    return ret;
}

PNG* SquareMaze::drawMazeWithSolution(){
    PNG* ret = drawMaze();
    vector<int> path = solveMaze();
    
    /* start at (5, 5) */
    pair<int, int> start = pair<int, int>(5, 5);
    ret->getPixel(start.first, start.second)->h = 0;
    ret->getPixel(start.first, start.second)->s = 1;
    ret->getPixel(start.first, start.second)->l = 0.5;
    ret->getPixel(start.first, start.second)->a = 1;

    /* move according to path */
    for(const int& step : path){
        if(step == 0){
            for(int i = 1; i <= 10; i++){
                ret->getPixel(start.first + i, start.second)->h = 0;
                ret->getPixel(start.first + i, start.second)->s = 1;
                ret->getPixel(start.first + i, start.second)->l = 0.5;
                ret->getPixel(start.first + i, start.second)->a = 1;
            }
            start.first += 10;
            continue;
        }
        if(step == 1){
            for(int i = 1; i <= 10; i++){
                ret->getPixel(start.first, start.second + i)->h = 0;
                ret->getPixel(start.first, start.second + i)->s = 1;
                ret->getPixel(start.first, start.second + i)->l = 0.5;
                ret->getPixel(start.first, start.second + i)->a = 1;
            }
            start.second += 10;
            continue;
        }
        if(step == 2){
            for(int i = 1; i <= 10; i++){
                ret->getPixel(start.first - i, start.second)->h = 0;
                ret->getPixel(start.first - i, start.second)->s = 1;
                ret->getPixel(start.first - i, start.second)->l = 0.5;
                ret->getPixel(start.first - i, start.second)->a = 1;
            }
            start.first -= 10;
            continue;
        }
        if(step == 3){
            for(int i = 1; i <= 10; i++){
                ret->getPixel(start.first, start.second - i)->h = 0;
                ret->getPixel(start.first, start.second - i)->s = 1;
                ret->getPixel(start.first, start.second - i)->l = 0.5;
                ret->getPixel(start.first, start.second - i)->a = 1;
            }
            start.second -= 10;
            continue;
        }
    }

    /* draw the exit */
    for(int i = 1; i <= 9; i++){
        *ret->getPixel(start.first - 5 + i, start.second + 5) = HSLAPixel();
    }

    return ret;
}