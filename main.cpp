#include <iostream>

using namespace std;

class BST {
private:
    struct Node{
        int data;
        Node* left;
        Node* right;
    };
    Node* root = nullptr;

    // addHelper is same function as "add" but it is on Private section to hide hard code, and it should know where to put every node even to right or left form the value of Node

    void addHelper(Node* temp, int value){
        if (value <= temp->data) {
            if(temp->left == nullptr){
                Node* newNode = new Node;
                newNode->data = value;
                newNode->left = nullptr;
                newNode->right = nullptr;

                temp->left = newNode;

            }
            else {
                addHelper(temp->left, value);
            }

        }
        else {
            if(temp->right == nullptr){
                Node* newNode = new Node;
                newNode->data = value;
                newNode->left = nullptr;
                newNode->right = nullptr;

                temp->right = newNode;

            }
            else {
                addHelper(temp->right, value);
            }

        }

    }


public:

    //creat a new Node
    void add(int value){
        if (root == nullptr){
            Node* newNode = new Node;
            newNode->data = value;
            newNode->right = nullptr;
            newNode->left = nullptr;

            root = newNode;
        } else {
            addHelper(root, value);
        }
    }

    //finde Max verdi i tree

    int getMax(){
        Node* temp = root;
        while(temp->right != nullptr){
            temp = temp->right;
        }
        return temp->data;
    }

    //finde Min verdi i tree
    int getMin(){
        Node* temp = root;
        while(temp->left != nullptr){
            temp = temp->left;
        }
        return temp->data;
    }

// Display whole Tree
    void PrinTree (Node* temp) {
        if (root == nullptr) return;
        PrinTree(root->left);
        PrinTree(root->right);
        cout<<root->data <<endl;
    }

};


int main () {

    BST object;
    object.add(13);
    object.add(1);
    object.add(3);
    object.add(5);
    object.add(7);

    cout<<object.getMax()<<endl;
    cout<<object.getMin()<<endl;

    return 0;
}