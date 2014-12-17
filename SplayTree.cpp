// ============================================================================
// SplayTree.cpp
// ~~~~~~~~~~~~~~
// Saurav Mohapatra
// - Implementation of a Very Basic Splay Tree Class
// ============================================================================

#include <stdexcept>
#include <vector>
#include <deque>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "SplayTree.h"
#include "term_control.h"

using namespace std; // BAD PRACTICE

void SplayTree::splay(Node* node)
{
    if (node == NULL)
        return;

	//Node* root = root_;
//	int splrot_cnt = 0;
    // TODO: TBD, splay node pointed to by node
   // Base cases: root is NULL or key is present at root

	Node *p;
        Node *g;
        Node* root =root_;
        if(node==root)
            return;
        else if(node->parent==root)
        {
            if(node==(node->parent)->left){
                rightRotate(root);}
            else{
                leftRotate(root);}
        }
        else
                {
            p=node->parent;
            g=p->parent;
            if(node==p->left&&p==g->left)
            {
                rightRotate(g);
                rightRotate(p);
            }
            else if(node==p->right&&p==g->right)
            {
                leftRotate(g);
                leftRotate(p);
            }
            else if(node==p->right&&p==g->left)
            {
                leftRotate(p);
                rightRotate(g);
            }
            else if(node==p->left&&p==g->right)
            {
                rightRotate(p);
                leftRotate(g);
            }
            splay(node);
        }
} 

bool SplayTree::remove(int key)
{

    // TODO: TBD
    // find node with key given by key and remove it
    // if the key is not found, splay the node just before hitting NULL
    // - return false
    // if the key is found at node,
    // - if node has <= child, splice it out, delete it, splay parent
    // - if node has 2 children, copy successor's key here
    //    splice out successor, delete it, and splay successor's parent
    // - return true
    //
	
	Node* root = root_;
	Node* node;



	if (!findNode(key))
	//	cout << "FALSE" << endl;
		return false;
	
	//root = splay(root);
	splay (root);
	if (key== root->key ) {

		if (root->left ==NULL)
		node=root->right;
		
		else {
		node = root->left;
		splay(node);
		node->right = root->right;

           } 	
	cout << "TRUE1" << endl;
	delete root;
	root = node;
//	splay(root);
	return true;

     }
	splay(root);
	toString();
	cout << "TRUE2" << endl;
	return true;	
}

/*
		splay(root);
		return false; }
	else
            {
		if (!root->left) {
			node = root;
			root = root->right;
		} else {
			node = root;
			//root = splay(root->left);
			splay(root->left);
			root->right = node->right;
			}

	delete node;
	splay(root);
	return true;

	}	
	return false;
}



            splay(root);

            if( root->key != key )
                return false;   // Item not found; do nothing

            if( root->left == NULL ) {
                node = root->right;
		//return true; 
            } else
            {
                // Find the maximum in the left subtree
                // Splay it to the root; and then attach right child
                node = root->left;
                splay(node);
                node->right = root->right;
		//return true;
            }
            delete root;
            root = node;
	return true;	
        }
//return true;
//}

*/

bool SplayTree::findKey(int key)
{
    Node* tmp = findNode(key);
    if (tmp != NULL)
        splay(tmp);
    return tmp != NULL;
}

SplayTree::Node* SplayTree::findNode(int key)
{
    Node* p = NULL;
    Node* cur = root_;
    while (cur != NULL) {
        if (cur->key == key)
            break;
        p = cur;
        cur = (key < cur->key? cur->left : cur->right);
    }
    if (cur == NULL)
        splay(p);
    return cur;
}

void SplayTree::leftRotate(Node*& node) 
{
    if (node == NULL || node->right == NULL) 
        return;

    Node* c = node;
    Node* b = c->right;
    Node* p = c->parent;

    // first, adjust all 3 parent pointers of b, c, and the left child's of b
    b->parent = p;
    c->parent = b;
    if (b->left != NULL) 
        b->left->parent = c;

    // second, adjust other downward pointers
    if (p != NULL) {    
        if (p->right == c) p->right = b;
        else p->left = b;
    }
    c->right = b->left;
    b->left  = c;

    node = b;         // new local root
    if (root_ == c) 
        root_ = b;    // new root if necessary
}

void SplayTree::rightRotate(Node*& node) 
{
    if (node == NULL || node->left == NULL) 
        return;

    Node* c = node;
    Node* b = c->left;
    Node* p = c->parent;

    // first, adjust all 3 parent pointers of b, c, and the right child's of b
    b->parent = p;
    c->parent = b;
    if (b->right != NULL) 
        b->right->parent = c;

    // second, adjust other downward pointers
    if (p != NULL) {
        if (p->right == c) p->right = b;
        else p->left = b;
    }
    c->left  = b->right;
    b->right = c;

    node = b;       // new local root
    if (root_ == c) 
        root_ = b;  // new root if necessary
}

std::string SplayTree::Node::toString()
{
    ostringstream oss;
    oss << "[" << key << "]";
    return oss.str();
}

bool SplayTree::insert(int key)
{
    bool found = false;
    Node* parent = NULL;
    Node* cur = root_;
    while (cur != NULL) {
        if (cur->key == key) {
            found = true;
            break;
        }
        parent = cur;
        cur = (key < cur->key? cur->left : cur->right);
    }
    if (!found) {
        cur = new Node(key, NULL, NULL, parent);
        if (parent != NULL) {
            if (cur->key < parent->key)
                parent->left = cur;
            else
                parent->right = cur;
        } else {
            root_ = cur; // tree empty before this insert
        }
    }
    splay(cur);
    return !found;
}

SplayTree::Node* SplayTree::minimum(Node* node)
{
    if (node == NULL)
        return NULL;
    while (node->left != NULL)
        node = node->left;
    return node;
}

SplayTree::Node* SplayTree::maximum(Node* node)
{
    if (node == NULL)
        return NULL;
    while (node->right != NULL)
        node = node->right;
    return node;
}

SplayTree::Node* SplayTree::predecessor(Node* node)
{
    if (node == NULL)
        return NULL;
    if (node->left != NULL)
        return maximum(node->left);
    while (node->parent != NULL && node->parent->left == node)
        node = node->parent;
    return node->parent;
}

SplayTree::Node* SplayTree::successor(Node* node)
{
    if (node == NULL)
        return NULL;
    if (node->right != NULL)
        return minimum(node->right);
    while (node->parent != NULL && node->parent->right == node)
        node = node->parent;
    return node->parent;
}

SplayTree::~SplayTree()
{
    clearTree(root_);
    root_ = NULL;
}

void SplayTree::clear()
{
    clearTree(root_);
    root_ = NULL;
}

void SplayTree::clearTree(Node* node) 
{
    if (node != NULL) {
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
}

bool SplayTree::isEmpty() const
{
    return root_ == NULL;
}

string SplayTree::printLevel(const vector<Text>& vec) 
{
    ostringstream oss;
    size_t cur_pos = 0; // where we are on the line
    size_t new_pos;
    for (size_t i=0; i<vec.size(); i++) {
        new_pos = vec[i].pos + vec[i].text.length();
        oss << setfill(' ') << right << setw(new_pos - cur_pos) << vec[i].text;
        cur_pos = new_pos;
    }
    if (!vec.empty()) oss << endl;
    return oss.str();
}

string SplayTree::toString() 
{
    if (root_ == NULL) 
        return "";

    ostringstream oss;
    coordinate_.clear();
    computeCoordinates(root_);

    deque<Node*> nodeQ; nodeQ.push_front(root_);
    deque<size_t> indentationQ;        indentationQ.push_front(0);
    size_t c = 1;  // # of nodes on the current level in queue
    size_t n = 0;  // # of nodes on the next level in queue
    string horiLine; // the _____ part
    Coordinate lc, rc;
    size_t horiLineLen, x;
    vector<Text> node_vec;
    vector<Text> conn_vec;
    while (!nodeQ.empty()) 
    {
        Node* cur = nodeQ.back(); // head of Q
        size_t indent = indentationQ.back();     // head of indent Q
        nodeQ.pop_back();
        indentationQ.pop_back();
        --c;

        if (cur == NULL) {
            node_vec.push_back(Text("x", indent));
        } else if (cur->left == NULL && cur->right == NULL) {
            node_vec.push_back(Text(cur->toString(), indent));
        } else {
            lc = coordinate_[cur->left];
            rc = coordinate_[cur->right];
            x = max(cur->toString().length()+lc.offset+rc.width-
                    rc.offset+2,lc.width+rc.width) - lc.width-rc.width+1;

            nodeQ.push_front(cur->left); 
            indentationQ.push_front(indent);
            nodeQ.push_front(cur->right);
            indentationQ.push_front(indent + lc.width + x);

            n += 2;
            horiLineLen = x+lc.width+rc.width-2-lc.offset-(rc.width-rc.offset+1)
                          -cur->toString().length();
            horiLine = string(horiLineLen/2, '_') + cur->toString()+ 
                       string(horiLineLen - horiLineLen/2, '_');

            node_vec.push_back(Text(horiLine, indent+lc.offset+1));
            conn_vec.push_back(Text("/", indent+lc.offset));
            conn_vec.push_back(Text("\\", indent+lc.width+x+rc.offset-2));
        }

        if (c == 0) { // reached the end of a level
            oss << printLevel(node_vec); 
            node_vec.clear();
            oss << printLevel(conn_vec); 
            conn_vec.clear();
            c = n;
            n = 0;
        }
    } // end while (!nodeQ.empty()))
    return oss.str();
}

void SplayTree::computeCoordinates(Node* node)
{
    Coordinate ret, lc, rc;
    size_t x;
    if (node == NULL) { 
        ret.width  = 1;
        ret.offset = 1;
    } else if (node->left == NULL && node->right == NULL) {
        ret.width = node->toString().length();
        ret.offset = 1 + ret.width/2;
    } else {
        computeCoordinates(node->left);
        computeCoordinates(node->right);
        lc = coordinate_[node->left];
        rc = coordinate_[node->right];
        x = max(node->toString().length()+lc.offset+rc.width-
                rc.offset+2,lc.width+rc.width) - lc.width-rc.width+1;
        ret.width = lc.width+rc.width+x;
        ret.offset = lc.offset + 1 + (lc.width+rc.offset+x-1-lc.offset)/2;
    }
    coordinate_[node] = ret;
}
