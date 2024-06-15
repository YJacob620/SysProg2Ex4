// ID: *****1536
// EMAIL: yairjacob620@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "complex.hpp"
#include "doctest.h"
#include "tree_classes.hpp"

TEST_CASE("1") {
  Tree<int> t = Tree<int>();
  vector<Node<int>> v;
  Node<int> n0 = Node<int>(0);
  Node<int> n1 = Node<int>(1);
  Node<int> n2 = Node<int>(2);
  t.add_root(n0);
  n0.addChild(n1);
  t.add_sub_node(n0, n2);

  const auto tn = t.getNodes();
  CHECK(tn[1] == &n2);
  CHECK(n1.children.empty());
  CHECK(n0.children[0] == &n1);
  CHECK(n0.children[1] == &n2);
}

TEST_CASE("2") {
  Tree<int> t = Tree<int>();
  vector<Node<int>> v;

  for (int i = 0; i < 15; ++i) {
    v.push_back(Node<int>(i));
  }
  t.add_root(v[0]);
  for (int i = 1; i < 7; ++i) {
    t.add_sub_node(v[i - 1], v[i]);
  }
  t.add_sub_node(v[0], v[9]);
  t.add_sub_node(v[1], v[8]);
  t.add_sub_node(v[4], v[7]);
  for (int i = 10; i < 13; ++i) {
    t.add_sub_node(v[i - 1], v[i]);
  }
  t.add_sub_node(v[11], v[13]);
  t.add_sub_node(v[10], v[14]);
  v[4].left = false;
  v[6].left = false;
  v[10].left = false;

  string totest = string();
  auto it = t.begin_pre_order();
  auto end = t.end_pre_order();
  for (; it != end; ++it) {
    totest.append(it.to_string() + " ");
  }
  CHECK(totest == "0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 ");
  totest.clear();

  it = t.begin_post_order();
  end = t.end_post_order();
  for (; it != end; ++it) {
    totest.append(it.to_string() + " ");
  }
  CHECK(totest == "6 5 7 4 3 2 8 1 12 13 11 14 10 9 0 ");
  totest.clear();

  it = t.begin_in_order();
  end = t.end_in_order();
  for (; it != end; ++it) {
    totest.append(it.to_string() + " ");
  }
  CHECK(totest == "3 5 6 4 7 2 1 8 0 9 12 11 13 10 14 ");
  totest.clear();

  it = t.begin_bfs_scan();
  end = t.end_bfs_scan();
  for (; it != end; ++it) {
    totest.append(it.to_string() + " ");
  }
  CHECK(totest == "0 1 9 2 8 10 3 11 14 4 12 13 5 7 6 ");
  totest.clear();

  it = t.begin_dfs_scan();
  end = t.end_dfs_scan();
  for (; it != end; ++it) {
    totest.append(it.to_string() + " ");
  }
  CHECK(totest == "0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 ");
}

TEST_CASE("3") {
  Tree<double> t = Tree<double>(3);
  vector<Node<int>> v;
  t.add_root(new Node(23.4));
  t.add_sub_node(t.nodes[0], new Node(123.321));
  t.add_sub_node(t.nodes[0], new Node(-8.331));
  t.add_sub_node(t.nodes[0], new Node(9.51));
  t.add_sub_node(t.nodes[2], new Node(9.51));
  t.add_sub_node(t.nodes[2], new Node(19.51));
  t.add_sub_node(t.nodes[2], new Node(39.51));
  t.add_sub_node(t.nodes[6], new Node(1239.531));
  t.add_sub_node(t.nodes[7], new Node(19.52));

  string totest = string();
  auto it = t.begin_pre_order();
  auto end = t.end_pre_order();
  for (; it != end; ++it) {
    totest.append(it.to_string() + " ");
  }
  CHECK(totest == "23.400000 123.321000 -8.331000 9.510000 19.510000 39.510000 1239.531000 19.520000 9.510000 ");
  totest.clear();

  it = t.begin_post_order();
  end = t.end_post_order();
  for (; it != end; ++it) {
    totest.append(it.to_string() + " ");
  }
  CHECK(totest == "23.400000 123.321000 -8.331000 9.510000 19.510000 39.510000 1239.531000 19.520000 9.510000 ");
  totest.clear();

  it = t.begin_in_order();
  end = t.end_in_order();
  for (; it != end; ++it) {
    totest.append(it.to_string() + " ");
  }
  CHECK(totest == "23.400000 123.321000 -8.331000 9.510000 19.510000 39.510000 1239.531000 19.520000 9.510000 ");
  totest.clear();

  it = t.begin_bfs_scan();
  end = t.end_bfs_scan();
  for (; it != end; ++it) {
    totest.append(it.to_string() + " ");
  }
  CHECK(totest == "23.400000 123.321000 -8.331000 9.510000 9.510000 19.510000 39.510000 1239.531000 19.520000 ");
  totest.clear();

  it = t.begin_dfs_scan();
  end = t.end_dfs_scan();
  for (; it != end; ++it) {
    totest.append(it.to_string() + " ");
  }
  CHECK(totest == "23.400000 123.321000 -8.331000 9.510000 19.510000 39.510000 1239.531000 19.520000 9.510000 ");

  Node<double> *tmp = new Node(double(0));
  CHECK_THROWS(t.add_sub_node(t.nodes[2], tmp));
  CHECK_THROWS(t.add_sub_node(t.nodes[0], tmp));
  delete (tmp);

  for (unsigned i = 0; i < t.nodes.size(); ++i) {
    delete (t.nodes[i]);
  }
}

TEST_CASE("4") {
  Tree<Complex> t = Tree<Complex>(2);
  Node<Complex> n0 = Node<Complex>(Complex(100, 100));
  Node<Complex> n1 = Node<Complex>(Complex(10, -5));
  Node<Complex> n2 = Node<Complex>(Complex(5, 0));
  Node<Complex> n3 = Node<Complex>(Complex(0.5, 0.1));
  Node<Complex> n4 = Node<Complex>(Complex(0.5, 0.2));
  Node<Complex> n5 = Node<Complex>(Complex(0.3, 15));

  t.add_root(n0);
  t.add_sub_node(n0, n1);
  t.add_sub_node(n0, n2);
  t.add_sub_node(n1, n3);
  t.add_sub_node(n2, n4);
  t.add_sub_node(n2, n5);

  CHECK_THROWS(t.add_sub_node(n2, n5));

  string totest = string();
  auto it = t.begin_pre_order();
  auto end = t.end_pre_order();
  for (; it != end; ++it) {
    totest.append((*it)->getValue().to_string() + " ");
  }
  CHECK(totest == "(100.00, 100.00) (10.00, -5.00) (0.50, 0.10) (5.00, 0.00) (0.50, 0.20) (0.30, 15.00) ");
  totest.clear();

  it = t.begin_post_order();
  end = t.end_post_order();
  for (; it != end; ++it) {
    totest.append((*it)->getValue().to_string() + " ");
  }
  CHECK(totest == "(0.50, 0.10) (10.00, -5.00) (0.50, 0.20) (0.30, 15.00) (5.00, 0.00) (100.00, 100.00) ");
  totest.clear();

  it = t.begin_in_order();
  end = t.end_in_order();
  for (; it != end; ++it) {
    totest.append((*it)->getValue().to_string() + " ");
  }
  CHECK(totest == "(0.50, 0.10) (10.00, -5.00) (100.00, 100.00) (0.50, 0.20) (5.00, 0.00) (0.30, 15.00) ");
  totest.clear();

  it = t.begin_bfs_scan();
  end = t.end_bfs_scan();
  for (; it != end; ++it) {
    totest.append((*it)->getValue().to_string() + " ");
  }
  CHECK(totest == "(100.00, 100.00) (10.00, -5.00) (5.00, 0.00) (0.50, 0.10) (0.50, 0.20) (0.30, 15.00) ");
  totest.clear();

  it = t.begin_dfs_scan();
  end = t.end_dfs_scan();
  for (; it != end; ++it) {
    totest.append((*it)->getValue().to_string() + " ");
  }
  CHECK(totest == "(100.00, 100.00) (10.00, -5.00) (0.50, 0.10) (5.00, 0.00) (0.50, 0.20) (0.30, 15.00) ");
  totest.clear();

  it = t.myHeap();
  for (; *it != nullptr; ++it) {
    totest.append((*it)->getValue().to_string() + " ");
  }
  CHECK(totest == "(0.30, 15.00) (0.50, 0.10) (0.50, 0.20) (5.00, 0.00) (10.00, -5.00) (100.00, 100.00) ");
}
