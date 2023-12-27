/**
 * @file main.cpp
 * This file contains code for output testing of the
 *  BinaryTree::isBalanced() method.
 * @author Volodymyr Kindratenko
 * @date March 2018
 */

#include <algorithm>
#include <iostream>
#include "binarytree.h"
#include "random.h"

using namespace std;
using namespace util;

template <typename T>
void printTreeInfo(const BinaryTree<T>& tree, const string& name,
                   const string& description);

int main(int argc, char** argv)
{
    // Seed the random generator 
    srandom(124);

    // Make a random sorted tree with nodes for 1 through 10
    BinaryTree<int> myTree1;
    for (int i = 1; i <= 10; i++)
        myTree1.insert(random()%100, true);

    // Print the tree
    printTreeInfo(myTree1, "Tree", "random sorted tree");

    cout << "1st smallest is " << myTree1.kthSmallest(1) << endl;
    cout << "2nd smallest is " << myTree1.kthSmallest(2) << endl;
    cout << "3rd smallest is " << myTree1.kthSmallest(3) << endl;
    cout << "5th smallest is " << myTree1.kthSmallest(5) << endl;
    cout << "9th smallest is " << myTree1.kthSmallest(9) << endl;
    cout << "10th smallest is " << myTree1.kthSmallest(10) << endl;

    cout << endl << endl;

    // Seed the random generator 
    srandom(7955);

    // Make a random sorted tree with nodes for 1 through 10
    BinaryTree<int> myTree2;
    for (int i = 1; i <= 10; i++)
        myTree2.insert(random()%100, true);

    // Print the tree
    printTreeInfo(myTree2, "Tree", "random sorted tree");

    cout << "1st smallest is " << myTree2.kthSmallest(1) << endl;
    cout << "2nd smallest is " << myTree2.kthSmallest(2) << endl;
    cout << "3rd smallest is " << myTree2.kthSmallest(3) << endl;
    cout << "5th smallest is " << myTree2.kthSmallest(5) << endl;
    cout << "9th smallest is " << myTree2.kthSmallest(9) << endl;
    cout << "10th smallest is " << myTree2.kthSmallest(10) << endl;

    return 0;
}

void output_header(string name, string desc)
{
    const string bar(79, '~');
    cout << bar << endl;
    cout << name;
    cout << " - " << desc << endl;
    cout << bar << endl;
}

template <typename T>
void printTreeInfo(const BinaryTree<T>& tree, const string& name,
                   const string& description)
{
    output_header(name, description);
    cout << "height: " << tree.height() << endl;
    cout << "is BST: " << ((tree.isOrdered()) ? "true" : "false") << endl;
    tree.print();
    cout << endl << endl;
}
