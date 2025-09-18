#include <iostream>
#include <vector>
#include <math.h>
using namespace std;


class Red_black_node {
    public:
    int value;
    bool is_red;
    bool is_nil;
    Red_black_node* left;
    Red_black_node* right;

    Red_black_node(int valu, bool color=true, bool is_nil=false) {
        value = valu;
        is_red = color;
        this->is_nil = is_nil;
        if (is_nil) {
            left = nullptr;
            right = nullptr;
        }
        else {
            left = new Red_black_node(-1, false, true);
            right = new Red_black_node(-1, false, true);
        }
    }
};

class Red_black_tree {
    Red_black_node* root=nullptr;

    Red_black_node* get_successor(Red_black_node* node) {
        Red_black_node* current = node->left;

        while (!current->right->is_nil)
        current = current->right;

        return current;
    }

    int get_spaces_of_level(int level) {
        if (level==0) 
        return 0;
        
        return (2*get_spaces_of_level(level-1))+1;
        
    }

    int Height(Red_black_node* node){
    if (node == nullptr){
        return 0;
    }
    else{
        return max(Height(node->left),Height(node->right))+1;
    }
    }

    void get_nodes_in_level(Red_black_node*p, int level, vector <int> & elements, vector <bool> & colors) {
        if (p == nullptr) {
            int k = pow(2,level);
            for (int i=0;i<k;i++)
            elements.push_back(-1);
            colors.push_back(-1);
            return;
        }

        if (level == 0) {
        elements.push_back(p->value);
        colors.push_back(p->is_red);
        }
        
        else {
            get_nodes_in_level(p->left, level-1, elements, colors);
            get_nodes_in_level(p->right, level-1, elements, colors);
        }
    }

    void right_rotation(Red_black_node* parent) {
        Red_black_node* child = parent->left;
        Red_black_node* Grand = get_parent(parent);
        
        if (Grand != nullptr)
        Grand->right==parent?Grand->right=child:Grand->left=child;
        else 
        root = child;

        parent->left = child->right;
        child->right = parent;
    }

    void left_rotation(Red_black_node* parent) {
        Red_black_node* child = parent->right;
        Red_black_node* Grand = get_parent(parent);

        if (Grand != nullptr)
        Grand->right==parent?Grand->right=child:Grand->left=child;
        else 
        root = child;

        parent->right = child->left;
        child->left = parent;
    }

    Red_black_node* get_parent(Red_black_node* current, Red_black_node* succecor_swaped=nullptr) {
        if (current == root || current == nullptr)
        return nullptr;

        if (succecor_swaped != nullptr) {
            Red_black_node* parent = succecor_swaped;
            if (parent->left == current)
            return parent;
            else 
            parent = parent->left;

            while (parent->right->is_nil) {
                if (parent->left == current)
                return parent;
                parent = parent->left;   
            }
            

            while (parent != nullptr && parent->right != current)
            parent = parent->right;
            
            if (parent->right == current)
            return parent;
            else
            return nullptr;

        }

        Red_black_node* parent = root;
        while (parent != nullptr && parent->right != current && parent->left != current){
            if (current->value <= parent->value) 
            parent = parent->left;
            else 
            parent = parent->right;
        }
        return parent;
    }

    public:
    void insert(int value) {
        if (root == nullptr) { 
        root = new Red_black_node(value, false);
        return;
        }

        Red_black_node* new_node = new Red_black_node(value);
        Red_black_node* Grand = nullptr;
        Red_black_node* parent = nullptr;
        Red_black_node* current = root;

        // get the parent and Grand parent of the node to be inserted
        while (!current->is_nil) {
            Grand = parent;
            parent = current;
            if (new_node->value <= current->value)
            current = current->left;
            else 
            current = current->right;
        }

        // insert the node
        if (new_node->value <= parent->value) 
            parent->left = new_node;
        else 
            parent->right = new_node;

        // fix violation while it exists
        current = new_node;
        while (Grand!=nullptr && parent->is_red && current->is_red){
            Red_black_node* uncle = Grand->left==parent?Grand->right:Grand->left;
            if (uncle->is_red) {
                parent->is_red = false;
                uncle->is_red = false;

                if (Grand == root)
                return;

                Grand->is_red = true;
                current = Grand;
                parent = get_parent(current);
                Grand = get_parent(parent);
            }
            else {
                if (parent == Grand->left) {
                    if (current == parent->right) {
                        swap(current,parent);
                        left_rotation(current);
                    }
                    right_rotation(Grand);
                }
                else {
                    if (current == parent->left) {
                        swap(current,parent);
                        right_rotation(current);
                    }
                    left_rotation(Grand);
                }
                parent->is_red = false;
                Grand->is_red = true;
            }
        }
        if (root->is_red) 
            root->is_red = false;
        
    }
    
    void remove(int value) {
        Red_black_node* node = search(value);

        if (node == nullptr || node->is_nil) {
            cout << "The number "<< value <<" doesn't exist in the rb tree";
            return;
        }

        Red_black_node* successor=nullptr;
        while (!node->left->is_nil || !node->right->is_nil) {
            successor = get_successor(node);
            swap(node->value, successor->value);
            swap(node, successor);
        }

        if (node == root) {
            root = nullptr;
            return;
        }

        Red_black_node* parent = get_parent(node, successor);

        Red_black_node* DB=nullptr;
        // remove the node and put a nill node
        if (parent != nullptr) {
            if (node == parent->right) {
                if (!node->is_red) {
                    DB = new Red_black_node(-1,false,true);
                    parent->right=DB;
                }
                else
                parent->right=new Red_black_node(-1,false,true);
                
            }
            else {
                if (!node->is_red) {
                    DB = new Red_black_node(-1,false,true);
                    parent->left=DB;
                }
                else
                parent->left=new Red_black_node(-1,false,true);
                
            }
        }
        


        while(DB !=root && DB != nullptr) {
            Red_black_node* brother = DB==parent->right? brother = parent->left : brother = parent->right;

            if (brother->is_red) {
                swap(brother->is_red, parent->is_red);

                if (brother = parent->right)
                left_rotation(parent);
                else
                right_rotation(parent);
            }
            else {
                Red_black_node* near, *far;
                // get near and far children
                if (brother == parent->right) {
                    near = brother->left;
                    far = brother->right;
                }
                else {
                    near = brother->right;
                    far = brother->left;
                }

                if (near != nullptr && far != nullptr && !near->is_red && !far->is_red) {
                    brother->is_red = true;

                    DB = nullptr;

                    if (!parent->is_red)
                    DB = parent;
                    else 
                    parent->is_red = false;
                }
                else if (far != nullptr && far->is_red) {
                    brother->is_red = parent->is_red;
                    parent->is_red = false;
                    far->is_red = false;
                    DB = nullptr;
                    if (brother == parent->right)
                    left_rotation(parent);
                    else
                    right_rotation(parent);
                }
                else {
                    swap(near->is_red, brother->is_red);
                    if (near == brother->right) 
                    left_rotation(brother);
                    else
                    right_rotation(brother);
                }
            }
        }
    }
    
    Red_black_node* search(int value) {
        Red_black_node* current = root;
        while (current != nullptr) {
            if (value == current->value)
            return current;
            else if (value <= current->value) 
            current = current->left;
            else 
            current = current->right;
        }
        return current;
    }

    void display() {
        int no_levels = Height(root);
        for (int i=0;i<no_levels;i++) {
            vector <int> e_in_level;
            vector <bool> color_in_level;
            get_nodes_in_level(root,i,e_in_level, color_in_level);

            int no_spaces = get_spaces_of_level(no_levels - i - 1);
            string spaces(no_spaces, ' ');

            if (i != 0) {
            cout << '\n';

            for (int j=0; j<e_in_level.size(); j++) {
                
                
                if (j%2==0 and i!=no_levels-1) {
                    cout << spaces << string((no_spaces+1)/2, ' ');
                    if (e_in_level[j] != -1)
                    cout << "/" << spaces;
                    else
                    cout << " " << spaces;
                }
                else if (j%2==0 and i==no_levels-1) {
                    if (e_in_level[j] != -1)
                    cout << "/" << " " ;
                    else
                    cout << "  ";
                    j++;
                    if (e_in_level[j] != -1)
                    cout << "\\" << " ";
                    else
                    cout << "  ";
                }
                else if (i==no_levels-1)
                    if (e_in_level[j] != -1)
                    cout << "\\" << string(2*no_spaces+1, ' ');
                    else
                    cout << " " << string(2*no_spaces+1, ' ');
                else
                    if (e_in_level[j] != -1)
                    cout << "\\" << string(2*no_spaces+2-pow(2,(no_levels-i-2)), ' ');
                    else
                    cout << " " << string(2*no_spaces+2-pow(2,(no_levels-i-2)), ' ');
            }

            cout << '\n';
            }

            for (int j=0; j<e_in_level.size(); j++) {
                string color =color_in_level[j]?"r":"b";
                if (e_in_level[j] != -1)
                cout << spaces << e_in_level[j] << color << spaces;
                else
                cout << spaces << " " << spaces << " ";

            }
        }
    }
};


int main() {
    Red_black_tree tree;

    int func_choice = 1;
    while (func_choice) {
            cout << "0. Exit\n"
                 << "1. Add number data\n"
                 << "2. Remove number data\n"
                 << "3. Display\n";
            cin >> func_choice;
            int n; 
            switch (func_choice) {
            case 0:
                break;
            case 1:
                cout << "Enter the number to insert: ";
                cin >> n;
                tree.insert(n);
                cout << '\n';
                break;
            case 2:
                cout << "Enter the number to remove: ";
                cin >> n;
                tree.remove(n);
                cout << '\n';
                break;
            case 3:
                tree.display();
                cout << '\n';
                break;
            default:
                cout << "choose one of the listed numbers\n";
                break;
            }
    }
}