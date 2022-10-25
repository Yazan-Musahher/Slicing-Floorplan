#include <iostream>

using namespace std;

enum Type {
    Horizontal,
    Vertical,
    Boundary,
};

class Rectangle {
public:
    int minimum_width;
    int minimum_height;

    Rectangle() {
        this->minimum_width = 0;
        this->minimum_height = 0;
    }

    Rectangle(int minimum_width, int minimum_height) {
        this->minimum_width = minimum_width;
        this->minimum_height = minimum_height;
    }
};

class Node {
public:
    Type type;
    Rectangle boundary;

    int key;
    Node *left;
    Node *right;

    Node(Type type, Rectangle boundary, int key) {
        this->type = type;
        this->boundary = boundary;
        this->key = key;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class BinaryTree {
public:
    Node *root;

    void add(Node *base, Type type, Rectangle boundary, int key) {
        if (root) {
            if (key <= base->key) {
                if (base->left) {
                    add(base->left, type, boundary, key);
                } else {
                    base->left = new Node(type, boundary, key);
                }
            } else {
                if (base->right) {
                    add(base->right, type, boundary, key);
                } else {
                    base->right = new Node(type, boundary, key);
                }
            }
        } else {
            root = new Node(type, boundary, key);
        }
    }

    void addSlice(Type type, int key) {
        add(this->root, type, Rectangle(0, 0), key);
    }

    void addRectangle(Rectangle rectangle, int key) {
        add(this->root, Boundary, rectangle, key);
    }

    void printNode(Node *base, int indent) {
        if (base) {
            // Print indent
            cout << string(indent, ' ') << "|-> ";

            if (base->type == Boundary)
                cout << base->boundary.minimum_width << "x" << base->boundary.minimum_height << endl;

            if (base->type == Horizontal)
                cout << "H" << endl;

            if (base->type == Vertical)
                cout << "V" << endl;

            printNode(base->left, indent + 4);
            printNode(base->right, indent + 4);
        }
    }

    void print() {
        printNode(this->root, 0);
    }
};

int main() {
    BinaryTree binary_tree = BinaryTree();
    binary_tree.addSlice(Vertical, 0);
    binary_tree.addRectangle(Rectangle(1,1), -1);
    binary_tree.addSlice(Horizontal, 2);
    binary_tree.addRectangle(Rectangle(2,2), 1);
    binary_tree.addRectangle(Rectangle(3,3), 3);
    binary_tree.print();
    return 0;
}
