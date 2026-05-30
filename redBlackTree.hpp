#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP
#include <stdexcept>

enum Color {red, black};

// Use of template to allow multiple data types.
// The goal is to make a general-purpose Red-Black Tree.
template<typename T>
struct TreeNode {
    T data;
    Color color;
    TreeNode<T> *left, *right, *parent;
    TreeNode(T data) : data(data), color(red), left(nullptr), right(nullptr), parent(nullptr) {}
};

template<typename T>
class RedBlackTree {
    private:
        TreeNode<T>* NIL;
        TreeNode<T>* root;
        
        // Auxiliary method for the destructor.
        void destructTree(TreeNode<T>* node) {
            if(node != NIL) {
                destructTree(node->left);
                destructTree(node->right);
                delete node;
            }
        }
        
        // Auxiliary method to reset the pointers and replace one subtree with another.
        void transplant(TreeNode<T>* u, TreeNode<T>* v) {
            if(u->parent == NIL) root = v;
            else if(u == u->parent->left) u->parent->left = v;
            else u->parent->right = v;
            v->parent = u->parent;
        }
        
        // Methods to rebalance the black-height of the tree using rotations.
        void leftRotate(TreeNode<T>* node) {
            TreeNode<T>* children = node->right;
            if(children->left != NIL) children->left->parent = node;
            node->right = children->left;
            children->parent = node->parent;
            if(node->parent != NIL) {
                if(node->parent->left == node) node->parent->left = children;
                else node->parent->right = children;
            }
            else root = children;
            node->parent = children;
            children->left = node;
        }
        
        void rightRotate(TreeNode<T>* node) {
            TreeNode<T>* children = node->left;
            if(children->right != NIL) children->right->parent = node;
            node->left = children->right;
            children->parent = node->parent;
            if(node->parent != NIL) {
                if(node->parent->left == node) node->parent->left = children;
                else node->parent->right = children;
            }
            else root = children;
            node->parent = children;
            children->right = node;
        }
        
        // Method to ensure compliance with the Red-Black Tree rules after inserting a new node.
        void fixInsert(TreeNode<T>* node) {
            while(node->parent && node->parent->color == red) {
                TreeNode<T>* father = node->parent;
                TreeNode<T>* grandfather = father->parent;
                TreeNode<T>* uncle;
                if(father == grandfather->left) {
                    uncle = grandfather->right;
                    // Case 2: uncle is red
                    if(uncle->color == red) {
                        father->color = black;
                        uncle->color = black;
                        grandfather->color = red;
                        node = grandfather;
                    }
                    else {
                        // Case 3: uncle is black (triangle)
                        if(node == father->right) leftRotate(father);
                        // Case 4: uncle is black (line)
                        else {
                            father->color = black;
                            grandfather->color = red;
                            rightRotate(grandfather);
                        }
                    }
                }
                else {
                    uncle = grandfather->left;
                    if(uncle->color == red) {
                        father->color = black;
                        uncle->color = black;
                        grandfather->color = red;
                        node = grandfather;
                    }
                    else {
                        if(node == father->left) rightRotate(father);
                        else {
                            father->color = black;
                            grandfather->color = red;
                            leftRotate(grandfather);
                        }
                    }
                }
            }
        }
        
        // Method to find the minimum value in the right subtree.
        // The goal is to replace the node that will be deleted.
        TreeNode<T>* findMinimum(TreeNode<T>* node) {
            while(node->left != NIL) {
                node = node->left;
            }
            return node;
        }
        
        // Ensures that all paths to the NIL node have the same number of black nodes.
        // This is important to keep the tree balanced after node deletions.
        void deleteFixup(TreeNode<T>* node) {
            TreeNode<T>* brother;
            while(node != root && node->color == black) {
                if(node == node->parent->left) {
                    brother = node->parent->right;
                    // Case 1: red brother
                    if(brother->color == red) {
                        brother->color = black;
                        node->parent->color = red;
                        leftRotate(node->parent);
                        brother = node->parent->right;
                    }
                    else {
                        // Case 2: black brother, both of the brother's children are black
                        if(brother->left->color == black && brother->right->color == black) {
                            brother->color = red;
                            node = node->parent;
                        }
                        // Case 3: black brother, brother's left child is red, right child is black
                        else if(brother->left->color == red && brother->right->color == black) {
                            brother->color = red;
                            brother->left->color = black;
                            rightRotate(brother);
                        }
                        // Case 4: black brother, brother's right child is red 
                        else {
                            brother->color = node->parent->color;
                            node->parent->color = black;
                            brother->right->color = black;
                            leftRotate(node->parent);
                            node = root;
                        }
                    }
                }
                else {
                    brother = node->parent->left;
                    if(brother->color == red) {
                        brother->color = black;
                        node->parent->color = red;
                        rightRotate(node->parent);
                        brother = node->parent->left;
                    }
                    else {
                        if(brother->left->color == black && brother->right->color == black) {
                            brother->color = red;
                            node = node->parent;
                        }
                        else if(brother->right->color == red && brother->left->color == black) {
                            brother->color = red;
                            brother->right->color = black;
                            leftRotate(brother);
                        }
                        else {
                            brother->color = node->parent->color;
                            node->parent->color = black;
                            brother->left->color = black;
                            rightRotate(node->parent);
                            node = root;
                        }
                    }
                }
            }
            node->color = black; 
        }
    public:

        // Prohibits copying the class to prevent double-free errors.
        RedBlackTree(const RedBlackTree&) = delete;
        RedBlackTree& operator=(const RedBlackTree&) = delete;
        
        // Constructor of the Red-Black Tree class.
        // Initializes the NIL node that will replace the nullptr in this type of tree.
        RedBlackTree() {
            NIL = new TreeNode<T>(T());
            NIL->color = black;
            NIL->left = NIL;
            NIL->right = NIL;
            NIL->parent = NIL;
            root = NIL;
        }
        
        // Destructor of the Red-Black Tree class.
        // Calls the auxiliary method to clear the entire tree and deletes the NIL node.
        // This is necessary to prevent memory leaks.
        ~RedBlackTree() {
            destructTree(root);
            delete NIL;
        }
        
        // Time complexity: O(log n)
        // Deletes a node from the tree and rebalances it.
        void deleteNode(TreeNode<T>* node) {
            if(!node || node == NIL) {
                throw std::invalid_argument("RedBlackTree::deleteNode failed: argument is null or sentinel (NIL).");
            }
            TreeNode<T>* substitute;
            Color originalColor = node->color;
            // Case 1: left child is NIL
            if(node->left == NIL) {
                substitute = node->right;
                transplant(node, substitute);
            }
            // Case 2: right child is NIL
            else if(node->right == NIL) {
                substitute = node->left;
                transplant(node, substitute);
            }
            // Case 3: neither child is NIL
            else {
                TreeNode<T>* nodeSubstitute = findMinimum(node->right);
                substitute = nodeSubstitute->right;
                originalColor = nodeSubstitute->color;
                if(nodeSubstitute != node->right) {
                    transplant(nodeSubstitute, substitute);
                    nodeSubstitute->right = node->right;
                    nodeSubstitute->right->parent = nodeSubstitute;
                }
                else substitute->parent = nodeSubstitute;
                transplant(node, nodeSubstitute);
                nodeSubstitute->left = node->left;
                nodeSubstitute->left->parent = nodeSubstitute;
                nodeSubstitute->color = node->color;
            }
            if(originalColor == black) deleteFixup(substitute);
            delete node;
        }

        // Time complexity: O(log n)
        // Inserts a node into the tree and rebalances it.
        void insert(T value) {
            if(search(value)) {
                throw std::logic_error("RedBlackTree::insert failed: key already exists.");
            }
            TreeNode<T>* node = new TreeNode<T>(value);
            node->left = NIL;
            node->right = NIL;
            node->parent = NIL;
            TreeNode<T>* x = root;
            TreeNode<T>* y = NIL;
            while(x != NIL) {
                y = x;
                if(node->data < x->data) x = x->left;
                else x = x->right;
            }
            // Case 1: root
            if(y == NIL) {
                root = node;
                root->color = black;
            }
            // Cases 2, 3, 4
            else {
                node->parent = y;
                if(node->data < y->data) y->left = node;
                else y->right = node;
                fixInsert(node);
            }
            root->color = black;
        }
        
        // Time complexity: O(log n)
        // Searches for a value in the tree and returns a pointer to its node.
        TreeNode<T>* search(T value) const {
            TreeNode<T>* node = root;
            while(node != NIL) {
                if(value == node->data) {
                    return node;
                }
                else if(value < node->data) {
                    node = node->left;
                }
                else {
                    node = node->right;
                }
            }
            return nullptr;
        }
};

#endif
