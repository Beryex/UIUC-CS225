/* Your code here! */
/**
 * @file dsets.h
 * DisjointSets implementation using path compression and union-by-size
 * 
 */
#ifndef DSETS_H
#define DSETS_H

#include <vector>

using::std::vector;

/**
 * DisjointSets implementation using path compression and union-by-size
*/
class DisjointSets
{
    public:
    /* Default constructor*/
    DisjointSets();
    
    /* Copy constructor*/
    DisjointSets(const DisjointSets& other);

    /* Assignment operator for DisjointSets*/
    const DisjointSets& operator=(const DisjointSets& rhs);

    /* Destructor*/
    ~DisjointSets();

    /* Creates n unconnected root nodes at the end of the vector*/
    void addelements(int num);

    /* find the elemnt's index and compress paths*/
    int find(int elem);

    /* union two sets using union-by-size*/
    void setunion(int a, int b);

    /* return the size of the set that includes elem*/
    int size(int elem);

    private:
    /* vector that stores all the element*/
    vector<int> elems_;
};

#endif /* DSETS_H */