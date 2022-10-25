#include <iostream>
#include <queue>

using namespace std;
//Create Node for lined list data structure
struct Node{
    char data;
    float h,w;
    Node* next;
};
//Create Binary Tree
struct BinTree{
    char data;

    float h,w;

    BinTree *left,*right;
};
//Create node of the binary tree
BinTree* newNodes(char value){
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
        if (parent->data == '-' || parent->data == '|') {
            leftChild = newNodes(head->data);
            q.push(leftChild);
            head = head->next;
            if (head != NULL) {
                rightChild = newNodes(head->data);
                q.push(rightChild);
                head = head->next;
            }
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
int heightOfTree(BinTree* root){
    if(root==NULL)
        return 0;
    return 1+max(heightOfTree(root->left),heightOfTree(root->right));
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
        cout<<root->data<<": height= "<<root->h << " wight= " << root->w << endl;
    else if(level>1){
        printNodes(root->left,level-1);
        printNodes(root->right,level-1);
    }
}
void levelPrint(BinTree* root){
    int h = heightOfTree(root);
    for(int i=1;i<=h;i++){
        printNodes(root,i);
    }
}

//Function that add node to the front of the linked list
void addNodeAtFront(Node** head, char value){
    Node* newNode = new Node;
    newNode->data = value;

    newNode->next = *head;
    *head = newNode;
}


bool isLeaf(BinTree* root) {
    if (root == nullptr)
        return false;
    if (root->left == nullptr && root->right == nullptr)
        return true;
    else
        return false;
    isLeaf(root->left);
    isLeaf(root->right);
}

// print bin tree
void printBT(const std::string& prefix, const BinTree* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        if (node->data != '-' && node->data != '|'){
            std::cout << "(" << node->data << " max-h: " << node->h << " max-w: " << node->w << ")" << std::endl;
        }
        else
            std::cout << "(" << node->data << ")" << std::endl;

        printBT( prefix + (isLeft ? "|   " : "    "), node->left, true);
        printBT( prefix + (isLeft ? "|   " : "    "), node->right, false);
    }
}

void printBT(const BinTree* node)
{
    printBT("", node, false);
}


// denne funker ikke ...
void giveVal(BinTree* root, int height, int width){

    BinTree* root1 = root;

    root->h = height;
    root->w = width;

    if (root->data == '-') {
        root->left->h = height;
        root->left->w = width/2;

        root->right->h = height;
        root->right->w = width/2;

    }
    else if (root->data == '|') {
        root->left->h = height/2;
        root->left->w = width;

        root->right->h = height/2;
        root->right->w = width;
    }

    if (!isLeaf(root->right))
        root = root->right;
    else if (!isLeaf(root->left))
        root = root->left;
    else
        return;

    while (!isLeaf(root)) {
        if (root->data == '-') {
            root->left->h = root->h;
            root->left->w = root->w/2;

            root->right->h = root->h;
            root->right->w = root->w/2;

        }
        else if (root->data == '|') {
            root->left->h = root->h/2;
            root->left->w = root->w;

            root->right->h = root->h/2;
            root->right->w = root->w;

        }

        if (!isLeaf(root->right))
            root = root->right;
        else if (!isLeaf(root->left))
            root = root->left;
        else
            break;
    }

    root = root1->left;

    while (!isLeaf(root)) {
        if (root->data == '-') {
            root->left->h = root->h;
            root->left->w = root->w/2;

            root->right->h = root->h;
            root->right->w = root->w/2;

        }
        else if (root->data == '|') {
            root->left->h = root->h/2;
            root->left->w = root->w;

            root->right->h = root->h/2;
            root->right->w = root->w;

        }


        if (!isLeaf(root->left))
            root = root->left;
        else if (!isLeaf(root->right))
            root = root->right;
        else
            break;
    }
};



int main(){
    Node* head = NULL;
    char polishExpr[12] = "DC|BFE-A||-";

    for (int i = 0; i < 11; ++i) {
        addNodeAtFront(&head, polishExpr[i]);
    }

    BinTree* root;
    convertLLtoBinTree(head,root);
    cout<<"Inorder Traversal:"<<endl;
    inorderTraversal(root);
    cout<<"\nPreorder Traversal:"<<endl;
    preorderTraversal(root);
    cout<<"\nPostorder Traversal:"<<endl;
    postorderTraversal(root);

    cout<<"\nThe height of the tree is: "<<heightOfTree(root)<<endl;
    cout<<"Level Order Traversal:"<<endl;
    //levelPrint(root);

    cout << "\n\n\n";

    // pass the root node of your binary tree
    printBT(root);


    char index = 'y';
    int height = 0;
    int width = 0;

    while (index != 'n'){
        cout << "Enter height" << endl;
        cin >> height;
        cout << "Enter width" << endl;
        cin >> width;

        giveVal(root, height, width);

        levelPrint(root);
        printBT(root);
        //funksjon her

        cout << "continue? y/n" << endl;
        cin >> index;


        while (index != 'y' && index != 'n'){
            cout << "INCORRECT INPUT! Continue? y/n" << endl;
            cin >> index;
        }
    }
}