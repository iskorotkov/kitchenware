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

BOOST_AUTO_TEST_SUITE_END()
