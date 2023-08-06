/**
 * CS 225 e08
 * @file main.cpp
 * @author NEW
 */

#include <iostream>
#include <sstream>
#include <string>
#include "avltree.h"
#include "coloredout.h"

using namespace std;

void printHeader(const string& headline)
{
    cout << string(64, colored_out::BORDER_CHAR) << endl;
    colored_out::output_bold(headline);
    cout << endl << string(64, colored_out::BORDER_CHAR) << endl;
}

void printBefore()
{
    cout << "~";
    colored_out::output_bold("Before");
    cout << "~" << endl;
}

void printAfter(int inserted)
{
    cout << endl << "~";
    colored_out::output_bold("After insert(");
    colored_out::output_bold(inserted);
    colored_out::output_bold(")");
    cout << "~" << endl;
}

void printEnd()
{
    cout << endl << endl;
}

template <class K, class V>
AVLTree<K, V> *makeLeftTree()
{
    AVLTree<int, int> *tree=new AVLTree<int, int>;
    printHeader("Left Tree");
    tree->insert(3, 3);
    tree->insert(0, 0);
    tree->insert(8, 8);
    tree->insert(6, 6);
    tree->insert(5, 5);
    tree->print();
    printEnd();
    return tree;
}


template <class K, class V>
AVLTree<K, V> *makeRightTree()
{
    AVLTree<int, int> *tree=new AVLTree<int, int>;
    printHeader("Right Tree");
    tree->insert(30, 30);
    tree->insert(10, 10);
    tree->insert(80, 80);
    tree->insert(60, 60);
    tree->insert(50, 50);
    tree->print();
    printEnd();
    return tree;
}


int main(int argc, char** argv)
{
    // Set up Colored Output (if 'color' parameter passed)
    bool is_colored
        = (argc > 1 && tolower(argv[1][0]) == 'c') && isatty(STDOUT_FILENO);
    colored_out coloroutput;
    if (is_colored) {
        coloroutput.set_expected_file("soln_testavl.out");
        int status = coloroutput.start();
        if (status < 0)
            return 0;
    }

    AVLTree<int, int> t1;
    printHeader("Left Tree");
    srandom(2365);
    for (int key = 0; key < 7; key++) {
	int val = random() % 100;
	t1.insert(val, val);
    }
    t1.print();
    printEnd();

    AVLTree<int, int> t2;
    printHeader("Right Tree");
    srandom(9845);
    for (int key = 0; key < 7; key++) {
	int val = random() % 100 + 101;
	t2.insert(val, val);
    }
    t2.print();
    printEnd();

    t1.join(t2);
    printHeader("Joined Tree");
    t1.print();
    printEnd();

    return 0;
}
