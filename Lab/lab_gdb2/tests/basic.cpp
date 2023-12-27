#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "catchlib.h"

#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"

#include "../skipList.h"
#include "../skipNode.h"

int probability = 50;
int maxLevel = 50;

void assertEqual(vector<int> a, vector<int> b, bool rev = false)
{
    REQUIRE(a.size() == b.size());

    for(size_t i = 0; i < a.size(); i++)
        REQUIRE(a[i] == b[i]);
}

void removeSentinels(vector<int> & a)
{
    a.erase(a.begin());
    a.pop_back();
}
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//////////////////////// Start of Tests ////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

TEST_CASE("Tests search() with a single node -- existent", "[weight=5]")
{
    SkipList list(probability, maxLevel);
    int key = 7;

    HSLAPixel c(137, 137, 137);
    list.insert(key, c);

    HSLAPixel ret = list.search(7);

    REQUIRE(ret == c);
}

TEST_CASE("Tests search() with a single node -- non-existent", "[weight=5]")
{
    SkipList list(probability, maxLevel);
    int key = 7;

    HSLAPixel c(137, 137, 137);
    list.insert(key, c);

    HSLAPixel ret = list.search(5);

    REQUIRE(ret == HSLAPixel(0, 0, 0, 50));
}

TEST_CASE("Tests search() with several nodes -- existent", "[weight=10]")
{
    SkipList list(probability, maxLevel);
    int key = 7;

    HSLAPixel c(137, 137, 137);
    for(int i = 1; i < 100; i += 2)
    {
        if(i == 7)
            list.insert(i, HSLAPixel(42, 42, 42));
        else
            list.insert(i, c);
    }

    HSLAPixel ret = list.search(7);

    REQUIRE(ret == HSLAPixel(42, 42, 42));
}

TEST_CASE("Tests inserting ascending values", "[weight=5]")
{
    SkipList list(probability, maxLevel);
    vector<int> soln;

    HSLAPixel c(137, 137, 137);
    for(int i = 1; i < 999; i += 3)
    {
        list.insert(i, c);

        soln.push_back(i);
    }

    // get the traverse map
    vector<int> check = list.traverse();
    removeSentinels(check);

    // compare to solution
    assertEqual(check, soln);
}


TEST_CASE("Tests inserting ascending values (reversed check)", "[weight=5]")
{
    SkipList list(probability, maxLevel);
    vector<int> soln;

    HSLAPixel c(137, 137, 137);
    for(int i = 1; i < 999; i += 3)
    {
        list.insert(i, c);

        soln.push_back(i);
    }

    // get the traverse map
    vector<int> check = list.traverseReverse();
    removeSentinels(check);

    // compare to solution
    assertEqual(check, soln);
}

TEST_CASE("Tests inserting random values", "[weight=10]")
{
    SkipList list(probability, maxLevel);
    vector<int> soln;
    vector<int> keys;

    HSLAPixel c(137, 137, 137);
    for(int i = 1; i < 999; i += 3)
    {
        keys.push_back(i);
        soln.push_back(i);
    }

    random_shuffle(keys.begin(), keys.end());

    for(int k : keys)
        list.insert(k, c);

    // get the backwards traverse map
    vector<int> check = list.traverseReverse();
    removeSentinels(check);

    // compare to solution
    assertEqual(check, soln, true);
}

TEST_CASE("Tests removing nodes (easy)", "[weight=5]")
{
    SkipList list(probability, maxLevel);

    vector<int> soln;

    HSLAPixel c(137, 137, 137);
    for(int i = 1; i <= 10; i++)
    {
        if(i != 7)
        {
            list.insert(i, c);
            if(i != 3)
                soln.push_back(i);
        }
    }

    bool ret1 = list.remove(3);
    bool ret2 = list.remove(7);

    //list.printKeys();
    //list.printKeysReverse();

    REQUIRE(ret1 == true);
    REQUIRE(ret2 == false);

    // get traverse map
    vector<int> check = list.traverse();
    removeSentinels(check);

    // compare to solution
    assertEqual(check, soln);

    check = list.traverseReverse();
    removeSentinels(check);
    assertEqual(check, soln, true);
}

TEST_CASE("Tests constructors - 1", "[weight=2]")
{
    SkipList list (1337, HSLAPixel(137, 0.137, 0.137));
    list.insert(42, HSLAPixel(42, 0.42, 0.42));
    list.insert(9999, HSLAPixel(99, 0.99, 0.99));

    vector<int> soln;
    
    soln.push_back(42);
    soln.push_back(1337);
    soln.push_back(9999);

    vector<int> check = list.traverse();
    removeSentinels(check);
    assertEqual(check, soln);

    check = list.traverseReverse();
    removeSentinels(check);
    assertEqual(check, soln, true);
}

TEST_CASE("Tests constructors - 2", "[weight=2]")
{
    SkipList * list = new SkipList(probability, maxLevel);

    list->insert(42, HSLAPixel(42, 0.42, 0.42));

    delete list;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
///////////////////////// End of Tests /////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    srand(time(NULL));

    // put our beloved quotes
    print_quote("tests/quotes.txt");

    print_valgrind();

    int result = Catch::Session().run(argc, argv);

    return (result < 0xFF ? result : 0xFF);
}
