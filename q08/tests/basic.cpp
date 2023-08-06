#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "../avltree.h"
#include <vector>
#include <iostream>
#include <sstream>

#include "catchlib.h"

using namespace std;


// compare the two streams for equality
bool tree_equals_output(stringstream & s, string filename)
{
    ifstream file(filename);
    string soln_s;
    string out_s;

    while(getline(file, soln_s))
    {
        if(!getline(s, out_s))
            return false;

        if(out_s.compare(soln_s) != 0)
            return false;
    }
    if(getline(s, soln_s))
        return false;

    return true;
}


TEST_CASE("Test Empty Left", "[weight=5]") {

    AVLTree<int, int> t1;
    AVLTree<int, int> t2;
    for (int r : {1, 4, 5, -1}) t2.insert(r,r);

    //t1.print();

    t1.join(t2);

    //t1.print();

    vector<int> solnTraversal = { -1, 1, 4, 5 };
    vector<int> inorderTraversal = t1.getInorderTraversal();

    stringstream str;
    t1.print(str, false);

    REQUIRE(solnTraversal == inorderTraversal);

    REQUIRE(tree_equals_output(str, "test_empty_left.out") == true);
}


TEST_CASE("Test Empty Right", "[weight=5]") {

    AVLTree<int, int> t1;
    AVLTree<int, int> t2;
    for (int r : {1, 4, 5, -1}) t2.insert(r,r);

    //t2.print();

    t2.join(t1);

    //t2.print();

    vector<int> solnTraversal = { -1, 1, 4, 5 };
    vector<int> inorderTraversal = t2.getInorderTraversal();

    stringstream str;
    t2.print(str, false);

    REQUIRE(solnTraversal == inorderTraversal);
    if(solnTraversal == inorderTraversal) std::cout << "right!!!" << std::endl;

    REQUIRE(tree_equals_output(str, "test_empty_left.out") == true);
}


TEST_CASE("Test No Rotation 1", "[weight=5]") {

    AVLTree<int, int> t1;
    for (int r : {3, 4, 2, 1}) t1.insert(r,r);

    //t1.print();

    AVLTree<int, int> t2;
    t2.insert(10,10);

    //t2.print();

    t1.join(t2);

    //t1.print();

    vector<int> solnTraversal = { 1, 2, 3, 4, 10 };
    vector<int> inorderTraversal = t1.getInorderTraversal();

    stringstream str;
    t1.print(str, false);

    REQUIRE(solnTraversal == inorderTraversal);

    REQUIRE(tree_equals_output(str, "test_no_rotation_1.out") == true);
}

TEST_CASE("Test No Rotation 2", "[weight=5]") {

    AVLTree<int, int> t1;
    for (int r : {1, 2, 3, 4, 5, 6, 7}) t1.insert(r,r);
    t1.remove(7);    

    //t1.print();

    AVLTree<int, int> t2;
    for (int r : {10, 9, 11}) t2.insert(r,r);

    //t2.print();

    t1.join(t2);

    //t1.print();

    vector<int> solnTraversal = {1, 2, 3, 4, 5, 6, 9, 10, 11};
    vector<int> inorderTraversal = t1.getInorderTraversal();

    stringstream str;
    t1.print(str, false);

    REQUIRE(solnTraversal == inorderTraversal);

    REQUIRE(tree_equals_output(str, "test_no_rotation_2.out") == true);
}


TEST_CASE("Test LR Rotation", "[weight=10]") {

    AVLTree<int, int> t1;
    for (int r : {3, 4, 2, 1}) t1.insert(r,r);

    //t1.print();

    AVLTree<int, int> t2;
    for (int r : {10, 9, 11}) t2.insert(r,r);

    //t2.print();

    t1.join(t2);

    //t1.print();

    vector<int> solnTraversal { 1, 2, 3, 4, 9, 10, 11 };
    vector<int> inorderTraversal = t1.getInorderTraversal();

    stringstream str;
    t1.print(str, false);

    REQUIRE(solnTraversal == inorderTraversal);

    REQUIRE(tree_equals_output(str, "test_rl_rotation.out") == true);
}

TEST_CASE("Test Rotate", "[weight=10][valgrind]") {

    AVLTree<int, string> t1;
    vector< pair<int, string> > elems1 = {
        { 1, "" }, { 2, "" }, { 3, "" }
    };
    for (auto p : elems1) t1.insert(p.first, p.second);

    //t1.print();

    AVLTree<int, string> t2;
    vector< pair<int, string> > elems2 = {
        { 55, "" }, { 45, "" }, { 12, "" }, { 34, "" },
        { 56, "" }, { 46, "" }, { 13, "" }, { 35, "" },
        { 57, "" }, { 47, "" }, { 14, "" }, { 36, "" },
        { 58, "" }, { 48, "" }, { 15, "" }, { 37, "" }
    };
    for (auto p : elems2) t2.insert(p.first, p.second);

    //t2.print();

    t1.join(t2);

    //t1.print();

    vector<int> inorderTraversal = t1.getInorderTraversal();

    stringstream str;
    t1.print(str, false);

    vector<int> solnTraversal = {1, 2, 3, 12, 13, 14, 15, 34, 35, 36, 37, 45, 46, 47, 48, 55, 56, 57, 58};

    REQUIRE(solnTraversal == inorderTraversal);
    REQUIRE(tree_equals_output(str, "test_many_rotations.out") == true);
}

int main(int argc, char* argv[])
{
    srand(time(NULL));

    print_valgrind();

    chdir("tests");

    int result = Catch::Session().run(argc, argv);

    return (result < 0xFF ? result : 0xFF);
}
