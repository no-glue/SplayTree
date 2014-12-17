// ============================================================================
// SplayTree.h
// ~~~~~~~~~~~~

#ifndef SPLAY_TREE_H_
#define SPLAY_TREE_H_

#include <vector>
#include <string>
#include <map>

class SplayTree
{
private:
    struct Node 
    {
        int key;
        Node* left;
        Node* right;
        Node* parent;
        Node(int k = 0, Node* l = NULL, Node* r = NULL, Node* p = NULL) 
            : key(k), left(l), right(r), parent(p)
        {}
        std::string toString();
    };

public:
    // default constructor
    SplayTree() : root_(NULL) 
    { }

    // destructor
    ~SplayTree();

    // clear the tree, deallocate space
    void clear();

    // simple size check
    bool isEmpty() const;

    // print the tree symmetrically
    std::string toString();

    // insert a new key in the tree, return 
    //  - true if a new node was created (and inserted)
    //  - false if the key already exists
    bool insert(int key);

    // remove a key from the tree, return 
    //  - true if a node was removed
    //  - false if the key is not found
    bool remove(int key);

    // returns whether a key is in the tree
    bool findKey(int key);

private:
    // root of the tree
    Node* root_;

    // helper function for destructor and clear()
    void clearTree(Node*);

    // the following four are often necessary in BST operations
    Node* minimum(Node* node); // minimum under node's subtree
    Node* maximum(Node*);      // maximum under node's subtree
    Node* successor(Node*);
    Node* predecessor(Node*);

    // look for a node with a given key, return NULL if not found
    // if not found, splay the node just before hitting NULL
    // if found, DON'T splay, let the caller do it
    Node* findNode(int key); 

    // helper functions for SplayTree operations
    void splay(Node*);
    void leftRotate(Node*&);  // note that the pointer is passed by reference
    void rightRotate(Node*&); // note that the pointer is passed by reference


    struct Text 
    {
        std::string text; // the text to be printed, e. "abc__"
        size_t pos;       // its position on the line
        Text(std::string t="", size_t p=0) : text(t), pos(p) {}
    };

    struct Coordinate 
    {
        size_t width;  // width of a subtree box
        size_t offset; // offset to where the parent points
    };

    std::string printLevel(const std::vector<Text>&);
    void computeCoordinates(Node*);
    std::map<Node*, Coordinate> coordinate_;
};

#endif
