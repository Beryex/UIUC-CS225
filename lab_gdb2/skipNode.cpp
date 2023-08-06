/**
 * @file skipNode.cpp
 * Doubly Linked Skip List (lab_gdb2), the Skip List's Node implementation
 *
 * @author Arman Tajback - Created
 * @author Jordi Paris Ferrer & Arman Tajback - Modified
 * @date (created) Fall 2016
 * @date (modified) Spring 2017
 * @date (modified) Fall 2017
 */

#include "skipNode.h"

/**
 * Default constructs a SkipNode. Initializes the node to height one, with both pointers set to NULL.
 * Do not edit this function!
 */
SkipNode::SkipNode() 
{
    nodePointers.push_back(SkipPointer());
}


/**
 * Constructs a SkipNode with the given parameters
 * Do not edit this function!
 *
 * @param key The key to associate with this Node
 * @param value The pixel value to associate with this node
 * @param height The height of this node; aka how many layers of forward and prev pointers it has
 */
SkipNode::SkipNode(int key, HSLAPixel value, int height) 
{
    this->key = key;
    this->value = value;

    for (int i = 0; i < height; i++) 
    {
        nodePointers.push_back(SkipPointer());
    }
}

/**
 * Copy constructor for a SkipNode.
 * Do not edit this function!
 *
 * @param other the SkipNode to copy into this one
 */
SkipNode::SkipNode(const SkipNode &other) 
{   
    this->key = other.key;
    this->value = other.value;
    this-> nodePointers = other.nodePointers;
}

