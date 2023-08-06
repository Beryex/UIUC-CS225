/**
 * Created: SP23
 *      quiz #06
 *
 * Modified:
 *      By: Volodymyr Kindratenko
 */
 #define CATCH_CONFIG_RUNNER
 #include "catch.hpp"
 #include "catchlib.h"

 #include <unistd.h>
 #include <iostream>
 #include <algorithm>
 #include <ctype.h>
 #include <vector>
 #include "../binarytree.h"


 using namespace std;
 using namespace util;


TEST_CASE("test_balanced", "[weight=10]"){
  vector<int> nodes;
	nodes.push_back(58); //         58
	nodes.push_back(35); //
	nodes.push_back(72); //    35        72
	nodes.push_back(10); //
	nodes.push_back(40); //  10  40    61  80
	nodes.push_back(61); //
	nodes.push_back(80); // 0 19            93
	nodes.push_back(93); //
	nodes.push_back(0); //
	nodes.push_back(19); //

  BinaryTree<int> tree;
  for(size_t i = 0; i < nodes.size(); i++)
    tree.insert(nodes[i], true);

  REQUIRE(tree.kthSmallest(1) == 0);
  REQUIRE(tree.kthSmallest(3) == 19);
  REQUIRE(tree.kthSmallest(6) == 58);
  REQUIRE(tree.kthSmallest(9) == 80);
}

TEST_CASE("test_unbalanced", "[weight=10]"){
  vector<int> nodes;
	nodes.push_back(58); //         58
	nodes.push_back(35); //
	nodes.push_back(72); //    35        72
	nodes.push_back(10); //
	nodes.push_back(40); //  10  40    61  80
	nodes.push_back(61); //
	nodes.push_back(80); // 0 19            93
	nodes.push_back(93); //
	nodes.push_back(0); //                    95
	nodes.push_back(19); //
	nodes.push_back(95); //

  BinaryTree<int> tree;
  for(size_t i = 0; i < nodes.size(); i++)
    tree.insert(nodes[i], true);

  REQUIRE(tree.kthSmallest(1) == 0);
  REQUIRE(tree.kthSmallest(2) == 10);
  REQUIRE(tree.kthSmallest(5) == 40);
  REQUIRE(tree.kthSmallest(11) == 95);
}

TEST_CASE("boundary situation","[weight=10]"){
	vector<int> nodes;
	nodes.push_back(58); //         58
	nodes.push_back(35); //
	nodes.push_back(72); //    35        72
	nodes.push_back(10); //
	nodes.push_back(40); //  10  40    61  80
	nodes.push_back(61); //
	nodes.push_back(80); // 0 19            93
	nodes.push_back(93); //
	nodes.push_back(0); //
	nodes.push_back(19); //

	BinaryTree<int> tree;
  	for(size_t i = 0; i < nodes.size(); i++)
    	tree.insert(nodes[i], true);
	
	REQUIRE(tree.kthSmallest(-1) == INT_MIN);
	REQUIRE(tree.kthSmallest(20) == INT_MIN);
}

int main(int argc, char* argv[])
 {
    int result = Catch::Session().run(argc, argv);

    return (result < 0xFF ? result : 0xFF);
 }
