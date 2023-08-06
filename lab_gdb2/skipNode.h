/**
 * @file skipNode.h
 * Doubly Linked Skip List (lab_gdb2), Skip List's Node header file

 * @author Arman Tajback - Created
 * @author Jordi Paris Ferrer & Arman Tajback - Modified
 * @date (created) Fall 2016
 * @date (modified) Spring 2017
 * @date (modified) Fall 2017
 */

// You shouldn't need to modify this file

#ifndef SKIPNODE_H_
#define SKIPNODE_H_

#include <map>
#include <stdio.h>
#include <vector>
#include "cs225/HSLAPixel.h"
using namespace std;
using namespace cs225;

// forward declare this
class SkipPointer;

/**
 * A node of our SkipList class, with layers of next and prev pointers.
 */
class SkipNode 
{

    public:

        /**
         * Default constructs a SkipNode. Initializes the node to height one, with both pointers set to NULL.
         */   
        SkipNode();


        /**
         * Constructs a SkipNode with the given parameters
         * Do not edit this function!
         *
         * @param key The key to associate with this Node
         * @param value The pixel value to associate with this node
         * @param height The height of this node; aka how many layers of forward and prev pointers it has
         */
        SkipNode(int key, HSLAPixel value,
                int height); 


        /**
         * Copy constructor for a SkipNode.
         * Do not edit this function!
         *
         * @param other the SkipNode to copy into this one
         */
        SkipNode(const SkipNode &other); // leave iff statements wrong

        /**
         * The key of this node
         */
        int key;

        /**
         * The current value stored in this node
         */
        HSLAPixel value;

        /**
         * A vector containing each level of next and previous pointers.
         */
        vector<SkipPointer > nodePointers;
};

/**
 * A helper class that allows us to easily use next and prev pointers
 */
class SkipPointer
{
    public:
        SkipNode* next;
        SkipNode* prev;

        SkipPointer() : next(NULL), prev(NULL) {}
        SkipPointer(SkipNode* n, SkipNode* p) : next(n), prev(p) {}
};

#endif
