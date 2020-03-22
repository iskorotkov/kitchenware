#define BOOST_TEST_MODULE ContainerTests
#include <boost/test/unit_test.hpp>

#include "binary_tree.h"

BOOST_AUTO_TEST_SUITE(TreeTests)

BOOST_AUTO_TEST_CASE(SimpleAdding)
{
    containers::binary_tree<int, int> tree;
    tree.add(1);
    BOOST_CHECK(tree.exists(1));
    tree.add(2);
    BOOST_CHECK(tree.exists(2));
    BOOST_CHECK(!tree.exists(4));
}

BOOST_AUTO_TEST_CASE(RemoveRootLeftLeaf)
{
    containers::binary_tree<int, int> tree;
    tree.add(1);
    tree.add(0);
    tree.remove(0);
    BOOST_TEST_CHECK(!tree.exists(0));
    BOOST_TEST_CHECK(tree.exists(1));
    BOOST_TEST_CHECK(!tree.exists(2));
}

BOOST_AUTO_TEST_CASE(RemoveRootRightLeaf)
{
    containers::binary_tree<int, int> tree;
    tree.add(1);
    tree.add(2);
    tree.remove(2);
    BOOST_TEST_CHECK(!tree.exists(0));
    BOOST_TEST_CHECK(tree.exists(1));
    BOOST_TEST_CHECK(!tree.exists(2));
}

BOOST_AUTO_TEST_CASE(RemoveRootInOneNodeTree)
{
    containers::binary_tree<int, int> tree;
    tree.add(1);
    tree.remove(1);
    BOOST_TEST_CHECK(!tree.exists(0));
    BOOST_TEST_CHECK(!tree.exists(1));
    BOOST_TEST_CHECK(!tree.exists(2));
}

BOOST_AUTO_TEST_CASE(RemoveRootWithLeftLeaf)
{
    containers::binary_tree<int, int> tree;
    tree.add(1);
    tree.add(0);
    tree.remove(1);
    BOOST_TEST_CHECK(!tree.exists(-1));
    BOOST_TEST_CHECK(tree.exists(0));
    BOOST_TEST_CHECK(!tree.exists(1));
}

BOOST_AUTO_TEST_CASE(RemoveRootWithRightLeaf)
{
    containers::binary_tree<int, int> tree;
    tree.add(1);
    tree.add(2);
    tree.remove(1);
    BOOST_TEST_CHECK(!tree.exists(1));
    BOOST_TEST_CHECK(tree.exists(2));
    BOOST_TEST_CHECK(!tree.exists(3));
}

BOOST_AUTO_TEST_CASE(SymmetricHierarchy)
{
    containers::binary_tree<int, int> tree;
    tree.add(50);
    tree.add(40);
    tree.add(30);
    tree.add(35);
    tree.add(45);
    tree.add(25);
    tree.add(55);
    BOOST_TEST_CHECK(tree.exists(25));
    BOOST_TEST_CHECK(tree.exists(30));
    BOOST_TEST_CHECK(tree.exists(35));
    BOOST_TEST_CHECK(tree.exists(40));
    BOOST_TEST_CHECK(tree.exists(45));
    BOOST_TEST_CHECK(tree.exists(50));
    BOOST_TEST_CHECK(tree.exists(55));

    tree.remove(30);
    BOOST_TEST_CHECK(tree.exists(25));
    BOOST_TEST_CHECK(!tree.exists(30));
    BOOST_TEST_CHECK(tree.exists(35));
    BOOST_TEST_CHECK(tree.exists(40));
    BOOST_TEST_CHECK(tree.exists(45));
    BOOST_TEST_CHECK(tree.exists(50));
    BOOST_TEST_CHECK(tree.exists(55));

    tree.remove(35);
    BOOST_TEST_CHECK(tree.exists(25));
    BOOST_TEST_CHECK(!tree.exists(30));
    BOOST_TEST_CHECK(!tree.exists(35));
    BOOST_TEST_CHECK(tree.exists(40));
    BOOST_TEST_CHECK(tree.exists(45));
    BOOST_TEST_CHECK(tree.exists(50));
    BOOST_TEST_CHECK(tree.exists(55));

    tree.remove(40);
    tree.remove(50);
    tree.remove(55);
    BOOST_TEST_CHECK(tree.exists(25));
    BOOST_TEST_CHECK(!tree.exists(30));
    BOOST_TEST_CHECK(!tree.exists(35));
    BOOST_TEST_CHECK(!tree.exists(40));
    BOOST_TEST_CHECK(tree.exists(45));
    BOOST_TEST_CHECK(!tree.exists(50));
    BOOST_TEST_CHECK(!tree.exists(55));
}

BOOST_AUTO_TEST_CASE(BigTree)
{
    containers::binary_tree<int, int> tree;
    auto list = { 1, 2, 3, 17, -20, 32, 0, 123, 47, 1000, 43, -11111, -1,
                  10, 12, 14, 15, 13, 11, 54, 98, -100, 100, 999, -99, -14 };

    // Populate tree
    for (auto i : list)
    {
        tree.add(i);
    }

    // Check if all items were added
    for (auto i : list)
    {
        BOOST_TEST_CHECK(tree.exists(i));
    }

    // Remove all items
    for (auto i : list)
    {
        tree.remove(i);
        BOOST_TEST_CHECK(!tree.exists(i));
    }

    // Check if all items were removed
    for (auto i : list)
    {
        BOOST_TEST_CHECK(!tree.exists(i));
    }
}

BOOST_AUTO_TEST_CASE(GiganticTree)
{
    containers::binary_tree<int, int> tree;
    std::vector<int> list;
    for (auto i = -10000; i < 10000; ++i)
    {
        list.emplace_back(i);
    }

    // Populate tree
    for (auto i : list)
    {
        tree.add(i);
    }

    // Check if all items were added
    for (auto i : list)
    {
        BOOST_TEST_CHECK(tree.exists(i));
    }

    // Remove all items
    for (auto i : list)
    {
        tree.remove(i);
        BOOST_TEST_CHECK(!tree.exists(i));
    }

    // Check if all items were removed
    for (auto i : list)
    {
        BOOST_TEST_CHECK(!tree.exists(i));
    }
}

BOOST_AUTO_TEST_SUITE_END()
