#include <bits/stdc++.h>

using namespace std;

struct node {
    Item data;
    node *left;
    node *right;

    node() : left(nullptr), right(nullptr) {}

    node(Item item) : data(item), left(nullptr), right(nullptr) {}
};

class BST : public Tree{
    node *root;

    void inorder(node *p) const {
        if (p != nullptr) {
            p->data.print();
            inorder(p->left);
            inorder(p->right);
        }
    }

    void inorderNames( node *p) const {
        if (p != nullptr) {
            inorderNames(p->left);
            p->data.print();
            inorderNames(p->right);
        }
    }
    
    void inorderNamesdes(node *p) const {
        if (p != nullptr) {
            inorderNamesdes(p->right);
            p->data.print();
            inorderNamesdes(p->left);
        }
    }

    node* getSuccessor(node* nod){
    node* succsesor = nod->right;
    if(succsesor->left !=  nullptr){
        succsesor= getSuccessor(succsesor->left);
        }
    return succsesor;
    }

    node* removeNode(node* root,node* nodeToRemove) {
    if (root == nullptr) {
        return root;
    }
    if (root->data < nodeToRemove->data) {
        root->right = removeNode(root->right,nodeToRemove);

    } else if (nodeToRemove->data < root->data) {
        root->left = removeNode(root->left, nodeToRemove);

        // When we found the place of the node in the tree
    }else {
        //First case where the node is a leafe (with zero children)
        if(root->left == nullptr || root->right == nullptr ) {
            //Store the non-NULL child into temp
            node* temp= root->left ? root->left : root->right;
            //Both left and right children are null -> First case [Leaf Deletion]
            if (temp == nullptr) {
                root = nullptr;
            }
            //Only one of the children is null -> Second Case [Node with one child]
            else{
                root = temp;
            }
        // Both left and right children aren't null -> Third case [node has two children]
        }else{
           node* temp = getSuccessor(root);
           root->data = temp->data;
           root->right = removeNode(root->right,temp);
         }
        }


    return root;
    }


public:
    
    BST() {
        root = nullptr;
    }

    void add(Item x) {
        if (x.get_name() == "")
        {
            string n, c;
            int p;
            cout << "Enter item name: ";
            cin >> n;
            cout << "Enter item category: ";
            cin >> c;
            cout << "Enter item price: ";
            cin >> p;
            x = Item(n, c, p);
        }

        node *p = root;
        node *prev = nullptr;
        while (p != nullptr) {
            prev = p;
            if (p->data < x)
                p = p->right;
            else
                p = p->left;
        }
        if (root == nullptr) {
            root = new node(x);
        } else if (prev->data < x) {
            prev->right = new node(x);
        } else {
            prev->left = new node(x);
        }
    }

    void remove() {
        string n;
        cout << "Enter the name of the item to remove: ";
        cin >> n;
        Item it;
        it.set_name(n);
        node *nod = new node(it);
        root =  removeNode(root, nod);
    }
    
    void display(){
        inorder(root);
    }
    
    void diplayOrderdByNameAsc(){
        inorderNames(root);
    }
    
    void diplayOrderdByNameDesc(){
        inorderNamesdes(root);
    }
    vector<Item>  inorderTraversPrice(node* nod){
    vector <Item> items;
    if(nod != nullptr){
        // Traverse left subtree first
        vector<Item> leftItems = inorderTraversPrice(nod->left);
        items.insert(items.end(), leftItems.begin(), leftItems.end());

        // Append current nod's data
        items.push_back(nod->data);

        // Traverse right subtree
        vector<Item> rightItems = inorderTraversPrice(nod->right);
        items.insert(items.end(), rightItems.begin(), rightItems.end());
    }

    return items;
}
    void diplayOrderdByPricAsc() {
        vector<Item> items = inorderTraversPrice(root);

        int n = items.size();
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (items[j].getPrice() > items[i].getPrice())
                {
                    swap(items[i], items[j]);
                }
            }
        }

        for (Item i : items)
        {
            i.print();
        }
    }
    void diplayOrderdByPricDesc() {
        vector<Item> items = inorderTraversPrice(root);
        int n = items.size();
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (items[j].getPrice() < items[i].getPrice())
                {
                    swap(items[i], items[j]);
                }
            }
        }

        for (Item i : items)
        {
            i.print();
        }
    }
};
