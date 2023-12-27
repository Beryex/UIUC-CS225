/* Your code here! */
/**
 * @file dsets.cpp
 * Implementation of DisjointSets 
 * 
 */

#include "dsets.h"

DisjointSets::DisjointSets(){
    // nothing here
}

DisjointSets::DisjointSets(const DisjointSets& other){
    elems_.assign(other.elems_.begin(), other.elems_.end());
}

const DisjointSets& DisjointSets::operator=(const DisjointSets& rhs){
    elems_.assign(rhs.elems_.begin(), rhs.elems_.end());
    return *this;
}

DisjointSets::~DisjointSets(){
    elems_.clear();
}

void DisjointSets::addelements(int num){
    for(int i = 0; i < num; i++){
        elems_.push_back(-1);
    }
}

int DisjointSets::find(int elem){
    // check stop condition
    if(elems_[elem] < 0) return elem;
    int ret = find(elems_[elem]);
    // compress path
    elems_[elem] = ret;
    return ret;
}

void DisjointSets::setunion(int a, int b){
    if(a < 0 || b < 0){
        return;
    }
    int root1 = find(a);
    int root2 = find(b);
    // do nothing if same root
    if(root1 == root2) return;
    int newSize = elems_[root1] + elems_[root2];

    // union by size
    if(elems_[root1] <= elems_[root2]){
        elems_[root2] = root1;
        elems_[root1] = newSize;
    } else {
        elems_[root1] = root2;
        elems_[root2] = newSize;
    }
}

int DisjointSets::size(int elem){
    return -elems_[find(elem)];
}
