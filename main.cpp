#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

enum Data {
    Horizontal,
    Vertical,
    border,
};

class Rectangle {
public:
    int minimum_w;
    int minimum_h;

    Rectangle() {
        this->minimum_w = 0;
        this->minimum_h = 0;
    }

    Rectangle(int minimum_width, int minimum_height) {
        this->minimum_w = minimum_width;
        this->minimum_h = minimum_height;
    }

    void Print() {
        cout << this->minimum_w << "x" << this->minimum_h;
    }
};

class Node {
public:
    Data type;
    Rectangle border;

    int data;
    Node *left;
    Node *right;

    Node(Data type, Rectangle border, int data) {
        this->type = type;
        this->border = border;
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class BinTree {
public:
    Node *root;
    unordered_map<int, Rectangle> rectangles;

    BinTree(int width, int height) {
//        this->width = width;e
//        this->height = height;
        this->root = nullptr;
    }

    void add(Node *base, Data type, Rectangle boundary, int key) {
        if (root) {
            if (key <= base->data) {
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

    void addSlice(Data type, int key) {
        add(this->root, type, Rectangle(0, 0), key);
    }

    void addRectangle(Rectangle rectangle, int key) {
        add(this->root, border, rectangle, key);
    }

    void printDisplay(Node *base, int indent) {
        if (base) {
            // Print indent
            cout << string(indent, ' ') << "|-> ";

            if (base->type == border)
                cout << base->border.minimum_w << "x" << base->border.minimum_h << endl;
            if (base->type == Horizontal) {
                Rectangle rectangle = this->rectangles[base->data];
                cout << "H: [" << rectangle.minimum_w << "x" << rectangle.minimum_h << "]" << endl;
            }
            if (base->type == Vertical) {
                Rectangle rectangle = this->rectangles[base->data];
                cout << "V: [" << rectangle.minimum_w << "x" << rectangle.minimum_h << "]" << endl;
            }

            printDisplay(base->left, indent + 4);
            printDisplay(base->right, indent + 4);
        }
    }

    void print() {
        printDisplay(this->root, 0);
    }

    Rectangle* calculate(Node* current) {
        // Check if exists
        if (current == nullptr)
            return nullptr;

        // Calculate
        Rectangle* left = calculate(current->left);
        Rectangle* right = calculate(current->right);

        if (current->type == border) {
            return &current->border;
        } else if (current->type == Horizontal) {
            int width = max(left->minimum_w , right->minimum_w);
            int height = left->minimum_h + right->minimum_h;
            left->minimum_w = width;
            right->minimum_w = width;
            Rectangle* rectangle = new Rectangle(width, height);
            this->rectangles[current->data] = *rectangle;
            return rectangle;
        } else if (current->type == Vertical) {
            int width = left->minimum_w + right->minimum_w;
            int height = max(left->minimum_h, right->minimum_h);
            left->minimum_h = height;
            right->minimum_h = height;
            Rectangle* rectangle = new Rectangle(width, height);
            this->rectangles[current->data] = *rectangle;
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


        BinTree binary_tree = BinTree(width, height);

        // Root
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

        // Print section
        binary_tree.calculate(binary_tree.root);
        binary_tree.print();
        hardPrint();

        // Ask user if he want to continue
        cout << "continue? y/n" << endl;
        cin >> index;


        while (index != 'y' && index != 'n'){
            cout << "INCORRECT INPUT! Continue? y/n" << endl;
            cin >> index;
        }
    }



    return 0;
}