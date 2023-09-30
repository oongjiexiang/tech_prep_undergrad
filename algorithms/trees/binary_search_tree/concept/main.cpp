#include <iostream>
#include <vector>

using namespace std;


/*
(1) delete BST Node: when a successor is found, ideally the original root should be deleted whereas the successor 
establishes connections with the root's original connections. While GeeksForGeeks code *copies* the root's content 
to the successor before deleting the root, such case is not ideal when the node is large, eg a User comprising of all
of his past information     -- Oong
*/

class Node{
    public:
        Node* left;
        Node* right;
        int item;
        Node(int item): left(NULL), right(NULL), item(item){}
};

class BinarySearchTree{
    private:
        Node* _insert_node(Node* cur, int item){
            if(cur == NULL) return new Node(item);
            if(cur->item >= item) cur->left = _insert_node(cur->left, item);
            else cur->right = _insert_node(cur->right, item);
            return cur;
        }
        Node* _find_node(Node* cur, int item){
            if(cur == NULL) return NULL;
            if(cur->item == item) return cur;
            _find_node(cur->left, item);
            _find_node(cur->right, item);
        }
        void _print_bst_inorder(Node* cur){
            if(cur == NULL) return;
            _print_bst_inorder(cur->left);
            cout << cur->item << "  ";
            _print_bst_inorder(cur->right);
        }
        void _print_bst_preorder(Node* cur){
            if(cur == NULL) return;
            cout << cur->item << "  ";
            _print_bst_preorder(cur->left);
            _print_bst_preorder(cur->right);
        }
        void _print_bst_postorder(Node* cur){
            if(cur == NULL) return;
            _print_bst_postorder(cur->left);
            _print_bst_postorder(cur->right);
            cout << cur->item << "  ";
        }
        Node* _delete_node(Node* cur, int item){
            if(cur == NULL) return cur;

            if(cur->item > item) cur->left = _delete_node(cur->left, item);
            else if(cur->item < item) cur->right = _delete_node(cur->right, item);
            else{
                if(cur->left == NULL && cur->right == NULL){
                    delete cur;
                    return NULL;
                }
                else if(cur->left == NULL){
                    Node* temp = cur->right;
                    delete cur;
                    return temp;
                }
                else if(cur->right == NULL){
                    Node* temp = cur->left;
                    delete cur;
                    return temp;
                }

                // This node has both children, so need to first identify the successor for its current position
                Node* successorParent = cur;
                Node* succ = cur->right;  // the successor is the smallest node in the right subtree (ie slightly larger than cur->item)
                while(succ->left != NULL){
                    successorParent = succ;
                    succ = succ->left;      // keep traversing left node of this right subtree
                }

                if(cur != successorParent) successorParent->left = succ->right;
                else successorParent->right = succ->right;

                // successor accedes the root position (1)
                succ->left = cur->left;
                succ->right = cur->right;
                delete cur;
                cur = succ;
            }
            return cur;
        }
        int _height_tree(Node* cur, int h){
            if(cur == NULL) return 0;
            return max(_height_tree(cur->left, h+1), _height_tree(cur->right, h+1)) + 1;
        }
        int countNode(Node* cur){
            if(cur == NULL) return 0;
            return countNode(cur->left) + countNode(cur->right) + 1;
        }

    public:
        Node* root = NULL;
        void create_bst(vector<int> list){
            for(int i = 0; i < list.size(); i++){
                if(root == NULL) root = _insert_node(root, list[i]);
                else _insert_node(root, list[i]);
            }
        }
        bool find_node(int item){
            return _find_node(root, item);
        }
        void print_bst(){
            cout << "------BST Printing------\n";
            _print_bst_inorder(root);
            cout << "\n------BST Printing End------\n\n";
        }
        void delete_node(int item){
            _delete_node(root, item);
        }
        void update_node(int old_item, int new_item){
            _delete_node(root, old_item);
            _insert_node(root, new_item);
        }
        int countNode(){
            return countNode(root);
        }
        int heightTree(){
            return _height_tree(root, -1);
        }
};

int main(){
    BinarySearchTree bst;
    vector<int> a = {6, 1, 4, 3, 8, 5, 10, 11, 2};
    bst.create_bst(a);
    bst.print_bst();
    bst.update_node(10, 100);
    bst.print_bst();
    bst.delete_node(8);
    bst.print_bst();
    return 0;
}