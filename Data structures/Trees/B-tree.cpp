#include <iostream>
using namespace std;

template <typename t, int m>
class BNode {
    public:
    t values[m];
    BNode* childern[m+1];
    int no_values = 0;

    BNode() {
        for (int i = 0; i < m+1; i++)
            childern[i] = nullptr;
    }

    bool is_leaf() {
        bool leaf = true;
        for (int i=0;i<m;i++) {
            if (childern[i] != nullptr)
                leaf = false;
        }
        return leaf;
    }

    void insert_value(t value, BNode* new_child=nullptr) {
        if (no_values == m) 
        return;

        if (no_values == 0) {
            values[0] = value;
            childern[1] = new_child;
            no_values++;
            return;
        }

        for (int i=no_values;i>=0;i--) {
            if (i==0 || value >= values[i-1]) {
                values[i] = value;
                childern[i+1] = new_child;
                break;
            }
            else {
                values[i] = values[i-1];
                childern[i+1] = childern[i];
            }
        }
        no_values++;
    }
};

template <typename t, int m>
class BTree {
    BNode<t,m>* root=nullptr;

    void print(BNode<t,m>* node ,string spaces="") {
        if (node == nullptr)
        return;
        cout << spaces << node->values[0];
        for (int i=1;i<node->no_values;i++) {
            cout << "," << node->values[i];
        }
        cout << "\n";
        spaces += "  ";
        for (int i=0;i<node->no_values+1;i++) 
            print(node->childern[i], spaces);
        
    }

    BNode<t,m>* get_parent(BNode<t,m>* node) {
        if (node == root) 
        return nullptr;

        BNode<t,m>* parent=root;
        bool is_parent = false;

        while (!is_parent && !parent->is_leaf()) {
            for (int i=0;i<parent->no_values+1;i++) {
                if (parent->childern[i] == node) 
                    is_parent = true;
                else if (i==parent->no_values)
                break;
                else if (node->values[0] <= parent->values[i])
                    parent = parent->childern[i];
            }    
        }
        return parent;
    }

    public:
    void Insert(t value) {
        BNode<t,m>* current = root;

        if (root == nullptr) {
            root = new BNode<t,m>;
            root->insert_value(value);
            return;
        }

        // go to the leaf node to insert the value
        while (!current->is_leaf()) {
            for (int i=0;i<m;i++) {
                if (value <= current->values[i] || i == current->no_values) {
                    current = current->childern[i];
                    break;
                }
            }
        }
        
        // insert the value
        current->insert_value(value);

        // if values are more than the limit split and pass the mid to the parent and repeat
        while (current->no_values == m) {
            // if there is no parent for the node create a parent for it
            if (current == root) {
                root = new BNode<t,m>;
                root->childern[0] = current;
            }

            // split the node
            BNode<t,m>* parent = get_parent(current);
            BNode<t,m>* new_node = new BNode<t,m>;
            int mid = ((current->no_values+1)/2)-1;
            for (int i=mid+1;i<m;i++) {
                new_node->values[i-mid-1] = current->values[i];
                new_node->childern[i-mid-1] = current->childern[i];
                current->childern[i]=nullptr;
                new_node->no_values++;
            }
            new_node->childern[m-mid-1] = current->childern[m];
            current->childern[m]=nullptr;

            // pass the mid to the parent
            parent->insert_value(current->values[mid], new_node);
            current->no_values = mid;

            current = parent;
        }
    }

    void Print() {
        print(root);
    }
};


int main()
{
 // Construct a BTree of order 3, which stores int data
 BTree<int,3> t1;
 t1.Insert(1);
 t1.Insert(5);
 t1.Insert(0);
 t1.Insert(4);
 t1.Insert(3);
 t1.Insert(2);
 t1.Print(); // Should output the following on the screen:
 /*
 1,4
 0
 2,3
 5
 */
 BTree <char,5> t; // Construct a BTree of order 5, which stores char data, Look at the example in our lecture:
 t.Insert('G');
 t.Insert('I');
 t.Insert('B');
 t.Insert('J');
 t.Insert('C');
 t.Insert('A');
 t.Insert('K');
 t.Insert('E');
 t.Insert('D');
 t.Insert('S');
 t.Insert('T');
 t.Insert('R');
 t.Insert('L');
 t.Insert('F');
 t.Insert('H');
 t.Insert('M');
 t.Insert('N');
 t.Insert('P');
 t.Insert('Q');
 t.Print(); // Should output the following on the screen:
 /*
 K
 C,G
 A,B
 D,E,F
 H,I,J
 N,R
 L,M
 P,Q
 S,T
 */
}
