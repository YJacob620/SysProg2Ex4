// ID: *****1536
// EMAIL: yairjacob620@gmail.com

#include "complex.hpp"
#include "tree_classes.hpp"
#include "tree_visualizer.hpp"
#include <cstring>
#include <random>

#define TREE_SIZE 30
#define K 30

using std::cout;
using std::endl;

double randomDouble(double min, double max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dist(min, max);
  return dist(gen);
}

int randomInt(int min, int max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(min, max);
  return distr(gen);
}

int main2(int argc, char *argv[]);
int main3(int argc, char *argv[]);

/* Constant/random int Tree */
int main(int argc, char *argv[]) {
  if (argc > 1) {
    if (strcmp(argv[1], "2") == 0) {
      return main2(argc, argv);
    }
    else if (strcmp(argv[1], "3") == 0) {
      return main3(argc, argv);
    }
  }

  QApplication app(argc, argv);

  Tree<int> t;
  vector<Node<int>> v;
  // Tree creation
  {
    for (int i = 0; i < 15; ++i) {
      // v.push_back(Node<int>(i));
      v.push_back(Node<int>(randomInt(-200, 200)));
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
  }

  // Print tree with different Treeterators
  {
    cout << "pre order" << endl;
    auto it = t.begin_pre_order();
    auto end = t.end_pre_order();
    for (; it != end; ++it) {
      cout << it << " ";
    }

    cout << endl
         << "post order" << endl;
    it = t.begin_post_order();
    end = t.end_post_order();
    for (; it != end; ++it) {
      cout << it << " ";
    }

    cout << endl
         << "in order" << endl;
    it = t.begin_in_order();
    end = t.end_in_order();
    for (; it != end; ++it) {
      cout << it << " ";
    }

    cout << endl
         << "bfs" << endl;
    it = t.begin_bfs_scan();
    end = t.end_bfs_scan();
    for (; it != end; ++it) {
      cout << it << " ";
    }

    cout << endl
         << "dfs" << endl;
    it = t.begin_dfs_scan();
    end = t.end_dfs_scan();
    for (; it != end; ++it) {
      cout << it << " ";
    }

    ~t; // Display tree in GUI

    cout << endl
         << "min heap" << endl;
    auto heapterators = t.myHeap();
    it = std::get<0>(heapterators);
    end = std::get<1>(heapterators);
    for (; it != end; ++it) {
      cout << it << " ";
    }
    cout << endl;
  }

  ~t; // Display min-heap in GUI

  return app.exec();
}

/* Random Complex Tree */
int main2(int argc, char *argv[]) {
  QApplication app(argc, argv);

  Tree<Complex> t = Tree<Complex>(K);
  vector<Node<Complex>> v;

  // Tree creation
  {
    for (int i = 0; i < TREE_SIZE; ++i) {
      double re(randomDouble(-100, 100)), im(randomDouble(-100, 100));
      v.push_back(Node<Complex>(Complex(re, im)));
    }
    t.add_root(v[0]);

    for (unsigned i = 0; i < v.size() - 1; ++i) {
      unsigned j = randomInt(0, i);
      t.add_sub_node(v[j], v[i + 1]);
    }
  }

  // Print tree with different Treeterators
  {
    cout << "pre order" << endl;
    auto it = t.begin_pre_order();
    auto end = t.end_pre_order();
    for (; it != end; ++it) {
      cout << it << " ";
    }

    cout << endl
         << "post order" << endl;
    it = t.begin_post_order();
    end = t.end_post_order();
    for (; it != end; ++it) {
      cout << it << " ";
    }

    cout << endl
         << "in order" << endl;
    it = t.begin_in_order();
    end = t.end_in_order();
    for (; it != end; ++it) {
      cout << it << " ";
    }

    cout << endl
         << "bfs" << endl;
    it = t.begin_bfs_scan();
    end = t.end_bfs_scan();
    for (; it != end; ++it) {
      cout << it << " ";
    }

    cout << endl
         << "dfs" << endl;
    it = t.begin_dfs_scan();
    end = t.end_dfs_scan();
    for (; it != end; ++it) {
      cout << it << " ";
    }
  }

  // Display tree in GUI
  ~t;

  return app.exec();
}

/* Random long Tree */
int main3(int argc, char *argv[]) {
  QApplication app(argc, argv);

  Tree<long> t = Tree<long>(K);
  vector<Node<long>> v;

  // Tree creation
  {
    for (int i = 0; i < TREE_SIZE; ++i) {
      v.push_back(Node<long>(randomInt(-100, 100)));
    }
    t.add_root(v[0]);

    for (unsigned i = 0; i < v.size() - 1; ++i) {
      unsigned j = randomInt(0, i);
      t.add_sub_node(v[j], v[i + 1]);
    }
  }

  // Print tree with different Treeterators
  {
    cout << "pre order" << endl;
    auto it = t.begin_pre_order();
    auto end = t.end_pre_order();
    for (; it != end; ++it) {
      cout << it << " ";
    }

    cout << endl
         << "post order" << endl;
    it = t.begin_post_order();
    end = t.end_post_order();
    for (; it != end; ++it) {
      cout << it << " ";
    }

    cout << endl
         << "in order" << endl;
    it = t.begin_in_order();
    end = t.end_in_order();
    for (; it != end; ++it) {
      cout << it << " ";
    }

    cout << endl
         << "bfs" << endl;
    it = t.begin_bfs_scan();
    end = t.end_bfs_scan();
    for (; it != end; ++it) {
      cout << it << " ";
    }

    cout << endl
         << "dfs" << endl;
    it = t.begin_dfs_scan();
    end = t.end_dfs_scan();
    for (; it != end; ++it) {
      cout << it << " ";
    }
  }

  // Display tree in GUI
  ~t;

  return app.exec();
}
