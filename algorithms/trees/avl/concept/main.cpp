#include <iostream>
#include <vector>

using namespace std;

/*
References: 
1. Brevity inspiration: https://github.com/mission-peace/interview/blob/master/src/com/interview/tree/AVLTree.java
2. Confirmation of insertion concept: https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
3. First source of deletion concept reading: https://www.geeksforgeeks.org/avl-tree-set-2-deletion/

Notes:
(1) Juxtapose assignment operator with the corresponding lines in trees/binary_search_tree. 
Why must the result be returned to the root? Because for every operation, AVL guarantees the balance, not the same root. Spent 
most time debugging the tree when this step is missed.
(2) From GeeksForGeeks and mission-peace, the balance operation is repeated in insert and delete operations. They are
the same: check any 4 conditions, then rotate.
(3) Setting the height is a technique, not a necessity. It's just to reduce the time of looking up the height
*/

class Node{
    public:
        Node* left;
        Node* right;
        int item;
        int height;
        Node(int item): left(NULL), right(NULL), item(item), height(0){}
};

class AVLTree{
    private:
        Node* _leftRotate(Node* root){
            Node* newRoot = root->right;
            root->right = newRoot->left;
            newRoot->left = root;
            _setHeight(root);   _setHeight(newRoot);    // (3)
            return newRoot;
        }
        Node* _rightRotate(Node* root){
            Node* newRoot = root->left;
            root->left = newRoot->right;
            newRoot->right = root;
            _setHeight(root);   _setHeight(newRoot);    // (3)
            return newRoot;
        }
        int _balanceFactor(Node* root){
            return _getHeight(root->left) - _getHeight(root->right);
        }
        Node* _balanceAtNode(Node* root){
            int balanceFactor = _balanceFactor(root);
            if(balanceFactor > 1 && _getHeight(root->left->left) > _getHeight(root->left->right)){  // LL rotation
                root = _rightRotate(root);
            }
            else if(balanceFactor > 1 && _getHeight(root->left->right) > _getHeight(root->left->left)){ // LR rotation
                root->left = _leftRotate(root->left);
                root = _rightRotate(root);
            }
            else if(balanceFactor < -1 && _getHeight(root->right->right) > _getHeight(root->right->left)){  // RR rotation
                root = _leftRotate(root);
            }
            else if(balanceFactor < -1 && _getHeight(root->right->left) > _getHeight(root->right->right)){   // RL rotation
                root->right = _rightRotate(root->right);
                root = _leftRotate(root);
            }
            _setHeight(root);
            return root;
        }
        Node* smallestNode(Node* root){
            Node* minNode = root;
            while(minNode->left != NULL) minNode = minNode->left;
            return minNode;
        }
        Node* _insertNode(Node* root, int item){
            // Standard BST insertion logic
            if(root == NULL) return new Node(item);
            if(root->item < item){
                root->right = _insertNode(root->right, item);
            }
            else if(root->item > item){
                root->left = _insertNode(root->left, item);
            }

            // Particular to AVL: Balance check
            root = _balanceAtNode(root);        // (2)
            return root;
        }
        Node* _deleteNode(Node* root, int item){
            // Standard BST deletion logic
            if(root == NULL) return NULL;
            if(root->item < item){
                root->right = _deleteNode(root->right, item);
            }
            else if(root->item > item){
                root->left = _deleteNode(root->left, item);
            }
            else{   // found the node to delete
                if(root->left == NULL && root->right == NULL){  // leaf node
                    delete root;
                    return NULL;
                }
                else if(root->left == NULL){
                    Node* temp = root->right;
                    delete root;
                    return temp;
                }
                else if(root->right == NULL){
                    Node* temp = root->left;
                    delete root;
                    return temp;
                }
                else{   // both children are present
                    Node* successorParent = root;
                    Node* succ = root->right;
                    while(succ->left != NULL){
                        successorParent = succ;
                        succ = succ->left;
                    }
                    if(successorParent != root) successorParent->left = succ->right;
                    else successorParent->right = succ->right;

                    succ->left = root->left;
                    succ->right = root->right;
                    delete root;
                    root = succ;
                }
            }
            if(root == NULL) return NULL;       // special case when there is no more root (but without this is fine)

            // Particular to AVL: Balance check
            _setHeight(root);                   // (3)
            root = _balanceAtNode(root);        // (2)
            return root;
        }
        Node* _findNode(Node* root, int item){
            if(root == NULL) return NULL;
            if(root->item < item) return _findNode(root->right, item);
            if(root->item > item) return _findNode(root->left, item);
            return root;    // this is the node because root->item == item
        }
        void inOrder(Node* root){
            if(root == NULL) return;
            inOrder(root->left);
            cout << root->item << " ";
            inOrder(root->right);
        }
        int _getHeight(Node* root){
            if(root == NULL) return 0;
            return root->height;
        }
        void _setHeight(Node* root){
            if(root == NULL) return;
            root->height = max((root->left? root->left->height: 0), (root->right? root->right->height: 0)) + 1;
        }
    public:
        Node* root;
        AVLTree(){
            root = NULL;
        }
        AVLTree(vector<int> list){
            root = NULL;
            for(int i = 0; i < list.size(); i++){
                insertNode(list[i]);
            }
        }
        void insertNode(int item){
            if(root == NULL) root = _insertNode(root, item);
            else root = _insertNode(root, item);    // (1)
        }
        void deleteNode(int item){
            root = _deleteNode(root, item);     // (1)
        }
        Node* findNode(int item){
            _findNode(root, item);
        }
        void printTree(){
            inOrder(root);
        }
        void updateNode(int oldItem, int newItem){
            deleteNode(oldItem);
            insertNode(newItem);
        }
};

int main(){
    vector<int> list = {90, 80, 70, 60, 50, 40, 30, 20, 10};
    AVLTree avltree(list);
    avltree.printTree();
    avltree.deleteNode(90);
    cout << endl << avltree.findNode(90) << endl;
    avltree.printTree();
    cout << endl << avltree.findNode(80)->item << endl;
    avltree.updateNode(60, 90);
    avltree.printTree();
    return 0;
}