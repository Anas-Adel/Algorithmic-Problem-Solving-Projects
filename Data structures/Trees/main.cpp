#include "Tree.h"
#include "heap.h"
#include "AVL.h"
#include "BST.h"

using namespace std; 

void readItems(ifstream& input,Tree* tree) {
    string name, category, str;
    getline(input, str);
    int price,n;
    n = stoi(str);
    for (int i=0;i<n;i++) {
        getline(input,name);
        getline(input,category);
        getline(input,str);
        price = stoi(str);

        Item it(name, category, price);
        tree->add(it);
    }
    }

int main () {
    Tree *tree;
    int tree_choice, func_choice=1;
    cout << "choose which non linear structure:\n"
         << "0. Exit\n"
         << "1. Binary Search Trees (BST)\n"
         << "2. Heaps\n"
         << "3. AVL Trees\n";

    
    bool done = false;
    while (!done) {
        cin >> tree_choice;
        switch (tree_choice) {
        case 0:
            done = true;
            break;
        case 1:
            done = true;
            tree = new BST;
            break;
        case 2:
            done = true;
            tree = new Heap;
            break;
        case 3:
            tree = new AVLTree;
            done = true;
            break;
        default:
            cout << "choose one of the listed numbers\n";
            break;
        }
    }

    if (tree_choice) {
        ifstream input;
        input.open("items.txt");
        readItems(input, tree);
        input.close();

        while (func_choice) {
            cout << "0. Exit\n"
                 << "1. Add item data\n"
                 << "2. Remove item data\n"
                 << "3. Display the item data normally\n"
                 << "4. Display all the items sorted by their name ascending\n"
                 << "5. Display all the items sorted by their name descending\n"
                 << "6. Display all the items sorted by their prices ascending\n"
                 << "7. Display all the items sorted by their prices descending\n";
            cin >> func_choice;
            Item it;
            switch (func_choice) {
            case 0:
                break;
            case 1:
                tree->add(it);
                break;
            case 2:
                if (tree_choice == 2)
                    cout << "Heap removes from the root automatically\n";
                tree->remove();
                break;
            case 3:
                tree->display();
                break;
            case 4:
                tree->diplayOrderdByNameAsc();
                break;
            case 5:
                tree->diplayOrderdByNameDesc();
                break;
            case 6:
                tree->diplayOrderdByPricAsc();
                break;
            case 7:
                tree->diplayOrderdByPricDesc();
            default:
                cout << "choose one of the listed numbers\n";
                break;
            }
        }
        delete tree;
    }
}