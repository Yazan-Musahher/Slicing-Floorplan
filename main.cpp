#include <iostream>
#include <queue>
using namespace std;
//Create Node for lined list data structure
struct Node{
    int data;
    Node* next;
};
//Create Binary Tree
struct BinTree{
    int data;
    BinTree *left,*right;
};
//Create node of the binary tree
BinTree* newNodes(int value){
    BinTree* newNode = new BinTree();
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
//convert Linked list to binary tree
void convertLLtoBinTree(Node* head,BinTree* &root){
    if(head == NULL){
        root = NULL;
        return;
    }
    queue<BinTree* > q;
    root = newNodes(head->data);
    q.push(root);
    head = head->next;
    while(head!=NULL){
        BinTree* parent = q.front();
        q.pop();
        BinTree *leftChild=NULL,*rightChild=NULL;
        leftChild = newNodes(head->data);
        q.push(leftChild);
        head = head->next;
        if(head!=NULL){
            rightChild = newNodes(head->data);
            q.push(rightChild);
            head = head->next;
        }
        parent->left = leftChild;
        parent->right = rightChild;
    }
}
//Function for inorder Traversal
void inorderTraversal(BinTree* root){
    if(root!=NULL){
        inorderTraversal(root->left);
        cout<<root->data<<" ";
        inorderTraversal(root->right);
    }
}
//Function for height of the tree
int height(BinTree* root){
    if(root==NULL)
        return 0;
    return 1+max(height(root->left),height(root->right));
}
//Function for preorder Traversal
void preorderTraversal(BinTree* root){
    if(root!=NULL){
        cout<<root->data<<" ";
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}
//Function for postorder Traversal
void postorderTraversal(BinTree* root){
    if(root!=NULL){
        preorderTraversal(root->left);
        preorderTraversal(root->right);
        cout<<root->data<<" ";
    }
}
//Function for level order traversal
void printNodes(BinTree* root,int level){
    if(root == NULL)
        return;
    if(level == 1)
        cout<<root->data<<" ";
    else if(level>1){
        printNodes(root->left,level-1);
        printNodes(root->right,level-1);
    }
}
void levelPrint(BinTree* root){
    int h = height(root);
    for(int i=1;i<=h;i++){
        printNodes(root,i);
    }
}
//Function that add node to the front of the linked list
void addNodeAtFront(Node** head,int value){
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = *head;
    *head = newNode;
}
int main(){
    Node* head = NULL;
    addNodeAtFront(&head,10);
    addNodeAtFront(&head,12);
    addNodeAtFront(&head,8);
    addNodeAtFront(&head,7);
    addNodeAtFront(&head,6);
    addNodeAtFront(&head,13);
    addNodeAtFront(&head,14);
    addNodeAtFront(&head,20);
    BinTree* root;
    convertLLtoBinTree(head,root);
    cout<<"Inorder Traversal:"<<endl;
    inorderTraversal(root);
    cout<<"\nPreorder Traversal:"<<endl;
    preorderTraversal(root);
    cout<<"\nPostorder Traversal:"<<endl;
    postorderTraversal(root);
    int h = height(root);
    cout<<"\nThe height of the tree is: "<<h<<endl;
    cout<<"Level Order Traversal:"<<endl;
    levelPrint(root);


    int index = 0;
    int height = 0;
    int width = 0;

    while (1){
        cout << "choose" << endl;
        cin >> index;
        if (index == 1){
            cout << "Enter height" << endl;
            cin >> height;
            cout << "Enter width" << endl;
            cin >> width;
        }
        else if (index == 2){

        }
        else if (index == 3){
            break;
        }
    }

}
