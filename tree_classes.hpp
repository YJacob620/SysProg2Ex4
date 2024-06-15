#ifndef TREE_CLASSES_HPP
#define TREE_CLASSES_HPP

#endif // TREE_CLASSES_HPP

#pragma once
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <type_traits>

#define PRE 0
#define POST 1
#define INORDER 2
#define BFS 3
#define DFS 4
#define HEAP 5
#define B_MAX_CHILDREN 2

using std::runtime_error;
using std::string;
using std::vector;

template <typename T>
class Tree;

template <typename T>
class TreeVisualizer;

template <typename T>
class Node {
    friend class Tree<T>::Treeterator; // Let Treeterator have access to private members.

private:
    T value;

public:
    bool left;
    Node<T> *parent;
    vector<Node<T> *> children;

    Node() = delete; // Delete default constructor.

    /// @brief Regular constructor of Node.
    /// @param _value Value the Node stores.
    Node(T _value) : value(_value), left(true), parent(nullptr), children() {}

    inline const T getValue() const { return value; }

    /// @brief Adds a child to this node.
    /// @param child Node to add as a child.
    inline void addChild(Node<T> &child) { addChild(&child); }

    inline void addChild(Node<T> *child) {
        if (child == nullptr) {
            return;
        }
        if (!children.empty()) {
            child->left = false;
        }
        children.push_back(child);
        child->parent = this;
    }

    inline void swap(Node<T> &other) {
        T tmp = value;
        this->value = other.value;
        other.value = tmp;
    }
};

template <typename T>
bool customComparator(const Node<T> *lhs, const Node<T> *rhs) {
    return lhs->getValue() < rhs->getValue();
}

template <typename T>
class Tree {
public:
    /// @brief Iterator for tree types.
    class Treeterator {
        friend class Tree; // Let tree have access to private members.

    private:
        Node<T> *curr;
        Node<T> *prev;
        vector<Node<T> *> queue;
        unsigned type : 3; // Type of the iterator, can be: PRE/POST/IN/BFS/DFS/HEAP.

    public:
        Treeterator() = delete; // Delete default constructor.
        Treeterator(const unsigned &_type, Node<T> *_ptr) : curr(_ptr), prev(nullptr), queue(), type(_type) {}

        inline Node<T> *operator*() const { return curr; }
        inline bool operator==(const Treeterator &other) const { return curr == other.curr; }
        inline bool operator!=(const Treeterator &other) const { return curr != other.curr; }

        friend std::ostream &operator<<(std::ostream &os, const Treeterator &it) {
            if (it.curr == nullptr) {
                os << nullptr;
            }
            else {
                os << it.curr->getValue();
            }
            return os;
        }

    private:
        inline void queueBFS() {
            this->queue.clear();
            Node<T> *tmp = curr;
            unsigned t = 0;
            while (true) {
                // while (t != this->queue.size()) {
                for (unsigned i = 0; i < tmp->children.size(); ++i) {
                    this->queue.push_back(tmp->children[i]);
                }
                if (t == this->queue.size()) {
                    break;
                }
                tmp = this->queue[t++];
            }
        }

        inline void queueDFS() {
            this->queue.clear();
            enqueueDFS(this->queue, this->curr);
            this->queue.erase(this->queue.begin());
        }

        inline void enqueueDFS(vector<Node<T> *> &queue, Node<T> *tmp) {
            queue.push_back(tmp);
            for (Node<T> *child : tmp->children) {
                enqueueDFS(queue, child);
            }
        }

    public:
        string to_string() { return std::to_string(curr->value); }

        Treeterator &operator++() {
            if (curr == nullptr) {
                throw runtime_error("Null iterator.");
            }
            switch (type) {
            case PRE: {
                if (curr->children.empty()) {
                loop_pre:
                    while (curr->children.size() < 2) {
                        prev = curr;
                        curr = curr->parent;
                    }
                    if (prev == curr->children[1]) {
                        prev = curr;
                        curr = curr->parent;
                        if (curr != nullptr) {
                            goto loop_pre;
                        }
                    }
                    if (curr != nullptr) {
                        curr = curr->children[1];
                    }
                }
                else {
                    curr = curr->children[0];
                }
                break;
            }
            case POST: {
                prev = curr;
                curr = curr->parent;
                if (curr != nullptr && curr->children.size() > 1) {
                    if (curr->children[1] != prev) {
                        curr = curr->children[1];
                        while (!curr->children.empty()) {
                            curr = curr->children[0];
                        }
                    }
                }
                break;
            }
            case INORDER: {
                if (curr->children.empty()) {
                    if (curr->left) {
                        prev = curr;
                        curr = curr->parent;
                    }
                    else {
                        // find end of left sub tree of ancestor
                        prev = curr;
                        curr = curr->parent;
                        while (!prev->left) {
                            prev = curr;
                            curr = curr->parent;
                        }
                    }
                }
                else {
                    if (curr->children.size() == 1) {
                        if (curr->children[0] == prev) {
                            // find end of left sub tree of ancestor
                            prev = curr;
                            curr = curr->parent;
                            while (!prev->left) {
                                prev = curr;
                                curr = curr->parent;
                            }
                        }
                        else {
                            prev = curr;
                            curr = curr->children[0];
                            while (!curr->children.empty() && curr->children[0]->left) {
                                prev = curr;
                                curr = curr->children[0];
                            }
                        }
                    }
                    else {
                        if (curr->children[0] == prev) {
                            prev = curr;
                            curr = curr->children[1];
                            while (!curr->children.empty() && curr->children[0]->left) {
                                prev = curr;
                                curr = curr->children[0];
                            }
                        }
                        else {
                            // find end of left sub tree of ancestor
                            prev = curr;
                            curr = curr->parent;
                            while (!prev->left) {
                                prev = curr;
                                curr = curr->parent;
                            }
                        }
                    }
                }
                break;
            }
            case BFS: {
                if (queue.empty()) {
                    curr = nullptr;
                }
                else {
                    curr = queue.front();
                    queue.erase(queue.begin());
                }
                break;
            }
            case DFS: {
                if (curr->parent == nullptr) {
                    this->queueDFS();
                }
                if (queue.empty()) {
                    curr = nullptr;
                }
                else {
                    curr = queue.front();
                    queue.erase(queue.begin());
                }
                break;
            }
            case HEAP:
                if (queue.empty()) {
                    curr = nullptr;
                }
                else {
                    curr = queue.front();
                    queue.erase(queue.begin());
                }
                break;
            }
            return *this;
        }
    };

private:
    unsigned k;
    Node<T> *root;
    TreeVisualizer<T>* window = nullptr;

public:
    vector<Node<T> *> nodes;

    Tree() : k(B_MAX_CHILDREN), nodes() {}
    Tree(unsigned max_children_pre_node) : k(max_children_pre_node), nodes() {}
    ~Tree() { delete(window); }

    inline const vector<Node<T> *> &getNodes() const { return nodes; }
    inline const Node<T> * getRoot() const { return root; }

    inline bool add_root(Node<T> &new_root) {
        return add_root(&new_root);
    }

    inline bool add_root(Node<T> *new_root) {
        if (nodes.empty()) {
            root = new_root;
            nodes.push_back(root);
            return true;
        }
        return false;
    }

    inline bool add_sub_node(Node<T> &node, Node<T> &new_child) {
        for (Node<T> *n : nodes) {
            if (n == &node) {
                if (node.children.size() == this->k) {
                    throw runtime_error("Node exceeds maximum children possible");
                }
                node.addChild(new_child);
                nodes.push_back(&new_child);
                return true;
            }
        }
        return false;
    }

    inline bool add_sub_node(Node<T> *node, Node<T> *new_child) {
        return add_sub_node(*node, *new_child);
    }

    inline Treeterator begin_pre_order() {
        if (k > B_MAX_CHILDREN) {
            return begin_dfs_scan();
        }
        return Treeterator(PRE, root);
    }

    inline Treeterator end_pre_order() {
        // Treeterator ans = Treeterator(PRE, root);
        // while (!ans.curr->children.empty()) {
        //   auto s = ans.curr->children.size();
        //   if (s > 1) {
        //     ans.curr = ans.curr->children[s - 1];
        //   }
        //   else if (!ans.curr->children[0]->left) {
        //     ans.curr = ans.curr->children[0];
        //   }
        //   else {
        //     break;
        //   }
        // }
        // return ans;
        return Treeterator(PRE, nullptr);
    }

    inline Treeterator begin_post_order() {
        if (k > B_MAX_CHILDREN) {
            return begin_dfs_scan();
        }
        Treeterator ans = Treeterator(POST, root);
        while (!ans.curr->children.empty()) {
            ans.curr = ans.curr->children[0];
        }
        return ans;
    }

    inline Treeterator end_post_order() {
        if (k > B_MAX_CHILDREN) {
            return end_dfs_scan();
        }
        // return Treeterator(POST, root);
        return Treeterator(PRE, nullptr);
    }

    inline Treeterator begin_in_order() {
        if (k > B_MAX_CHILDREN) {
            return begin_dfs_scan();
        }
        Treeterator ans = Treeterator(INORDER, root);
        while (!ans.curr->children.empty()) {
            if (!ans.curr->children[0]->left) {
                break;
            }
            ans.curr = ans.curr->children[0];
        }
        return ans;
    }

    inline Treeterator end_in_order() {
        return end_pre_order();
    }

    inline Treeterator begin_bfs_scan() {
        Treeterator ans = Treeterator(BFS, root);
        ans.queueBFS();
        return ans;
    }

    inline Treeterator end_bfs_scan() {
        return Treeterator(BFS, nullptr);
    }

    inline Treeterator begin_dfs_scan() {
        Treeterator ans = Treeterator(DFS, root);
        ans.queueDFS();
        return ans;
    }

    inline Treeterator end_dfs_scan() {
        // return end_pre_order();
        return Treeterator(PRE, nullptr);
    }

    Treeterator myHeap(Treeterator pre_order_it, /*Treeterator post_order, */ Treeterator in_order_it) {
        if (pre_order_it.type != PRE || /*post_order.type != POST ||*/ in_order_it.type != INORDER) {
            throw runtime_error("Mismatched Treeterators types");
        }
        return myHeap();
    }

    Treeterator myHeap() {
        // if (k > B_MAX_CHILDREN) {
        //     throw runtime_error("Tree is not binary");
        // }

        std::sort(nodes.begin(), nodes.end(), customComparator<T>);
        Treeterator ans = Treeterator(HEAP, nodes[0]);
        ans.queue = nodes;
        ans.queue.erase(ans.queue.begin());

        // vector<Node<T> *> preorder, inorder;
        // while (pre_order_it.curr != nullptr) {
        //   preorder.push_back(pre_order_it.curr);
        //   ++pre_order_it;
        // }
        // while (in_order_it.curr != nullptr) {
        //   inorder.push_back(in_order_it.curr);
        //   ++in_order_it;
        // }

        // Node<T> *reco = reconstructTree(preorder, inorder);

        return ans;
    }

    inline Node<T> *reconstructTree(vector<Node<T> *> /*&*/ preorder, vector<Node<T> *> /*&*/ inorder) {
        if (preorder.empty() || inorder.empty()) {
            return nullptr;
        }
        Node<T> *root = new Node<T>(preorder[0]->getValue());
        unsigned root_index_in_inorder = 0;
        while (inorder[root_index_in_inorder] != preorder[0]) {
            ++root_index_in_inorder;
        }

        vector<Node<T> *> left_inorder, right_inorder, left_preorder, right_preorder;
        for (unsigned i = 0; i < root_index_in_inorder; ++i) {
            left_inorder.push_back(inorder[i]);
        }
        for (unsigned i = root_index_in_inorder + 1; i < inorder.size(); ++i) {
            right_inorder.push_back(inorder[i]);
        }
        for (unsigned i = 1; i < 1 + left_inorder.size(); ++i) {
            left_preorder.push_back(preorder[i]);
        }
        for (unsigned i = 1 + left_inorder.size(); i < preorder.size(); ++i) {
            right_preorder.push_back(preorder[i]);
        }

        root->addChild(reconstructTree(left_preorder, left_inorder));
        root->addChild(reconstructTree(right_preorder, right_inorder));

        return root;
    }

    void operator~() {
        window = new TreeVisualizer(nullptr, this);
        window->show();
    }
};
