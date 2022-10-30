#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

enum Type {
    Horizontal,
    Vertical,
    Boundary,
};

class Rectangle {
public:
    float minimum_width;
    float minimum_height;

    Rectangle() {
        this->minimum_width = 0;
        this->minimum_height = 0;
    }

    Rectangle(float minimum_width, float minimum_height) {
        this->minimum_width = minimum_width;
        this->minimum_height = minimum_height;
    }

    void print() {
        cout << this->minimum_width << "x" << this->minimum_height;
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
    unordered_map<float, Rectangle> rectangles;

    BinaryTree(int width, int height) {
//        this->width = width;e
//        this->height = height;
        this->root = nullptr;
    }

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
            if (base->type == Horizontal) {
                Rectangle rectangle = this->rectangles[base->key];
                cout << "H: [" << rectangle.minimum_width << "x" << rectangle.minimum_height << "]" << endl;
            }
            if (base->type == Vertical) {
                Rectangle rectangle = this->rectangles[base->key];
                cout << "V: [" << rectangle.minimum_width << "x" << rectangle.minimum_height << "]" << endl;
            }

            printNode(base->left, indent + 4);
            printNode(base->right, indent + 4);
        }
    }

    void print() {
        printNode(this->root, 0);
    }

    Rectangle* calculate(Node* current) {
        // Check if exists
        if (current == nullptr)
            return nullptr;

        // Calculate
        Rectangle* left = calculate(current->left);
        Rectangle* right = calculate(current->right);

        if (current->type == Boundary) {
            return &current->boundary;
        } else if (current->type == Horizontal) {
            float width = max(left->minimum_width , right->minimum_width);
            float height = left->minimum_height + right->minimum_height;
            left->minimum_width = width;
            right->minimum_width = width;
            Rectangle* rectangle = new Rectangle(width, height);
            this->rectangles[current->key] = *rectangle;
            return rectangle;
        } else if (current->type == Vertical) {
            float width = left->minimum_width + right->minimum_width;
            float height = max(left->minimum_height, right->minimum_height);
            left->minimum_height = height;
            right->minimum_height = height;
            Rectangle* rectangle = new Rectangle(width, height);
            this->rectangles[current->key] = *rectangle;
            return rectangle;
        } else {
            return nullptr;
        }
    }
};

void hardPrint(){
    cout << "_________________________\n"
            "|        |              |\n"
            "|   E    |       F      |\n"
            "|________|______________|\n"
            "|     |            |    |\n"
            "|     |            |    |\n"
            "|     |      C     | D  |\n"
            "|  A  |            |    |\n"
            "|     |____________|____|\n"
            "|     |       B         |\n"
            "|_____|_________________|"<<endl;
}

int main() {
    int width, height;
    char index = 'y';

    while (index != 'n'){
        cout << "Enter width" << endl;
        cin >> width;
        cout << "Enter height" << endl;
        cin >> height;


        BinaryTree binary_tree = BinaryTree(width, height);

        // Start
        binary_tree.addSlice(Horizontal, 50);

        // Left
        binary_tree.addSlice(Vertical, 25);
        binary_tree.addRectangle(Rectangle(width*0.2,height*0.7), 15);
        binary_tree.addSlice(Horizontal, 37);
        binary_tree.addRectangle(Rectangle(width*0.7,height*0.2), 30);
        binary_tree.addSlice(Vertical, 42);
        binary_tree.addRectangle(Rectangle(width*0.5,height*0.5), 40);
        binary_tree.addRectangle(Rectangle(width*0.3,height*0.5), 43);

        // Right
        binary_tree.addSlice(Vertical, 75);
        binary_tree.addRectangle(Rectangle(width*0.4,height*0.3), 70);
        binary_tree.addRectangle(Rectangle(width*0.6,height*0.3), 80);

        // Show
        binary_tree.calculate(binary_tree.root);
        binary_tree.print();
        hardPrint();

        cout << "continue? y/n" << endl;
        cin >> index;


        while (index != 'y' && index != 'n'){
            cout << "INCORRECT INPUT! Continue? y/n" << endl;
            cin >> index;
        }
    }



    return 0;
}
