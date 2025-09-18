#include <bits/stdc++.h>
using namespace std;


class Heap : public Tree{
private:
    vector<Item> heap;
public:
    Heap() {}
    void add(Item it) {
        if (it.get_name() == "") {
            string n, c;
            int p;
            cout << "Enter item name: ";
            cin >> n;
            cout << "Enter item category: ";
            cin >> c;
            cout << "Enter item price: ";
            cin >> p;
            it = Item(n, c, p);
        }
        heap.push_back(it);
        int i = heap.size() - 1;
        int parent = (i - 1) / 2;
        while (i != 0 && heap[i] < heap[parent]) {
            swap(heap[parent], heap[i]);
            i = parent;
            parent = (i - 1) / 2;
        }
    }

    void remove() {
        if (heap.size() == 0)
            cout << "Heap is empty\n";

        heap[0] = heap.back();
        heap.pop_back();

        int i = 0;

        while (true) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left >= heap.size())
                break;

            int smallest = left;

            if (right < heap.size() and heap[right] < heap[left])
                smallest = right;

            if (heap[smallest] < heap[i]) {
                swap(heap[i], heap[smallest]);
                i = smallest;
            }
            else
                break;
        }
    }

    void display() {
        for (int i=0;i<heap.size();i++)
            heap[i].print();
    }

    void diplayOrderdByNameAsc() {
        vector <Item> name = heap;
        vector <Item> result;

        for (int j=0;j<name.size();j++) {
            result.push_back(heap[0]);
            remove();
        }

        heap = name;

        for (int i=0;i<result.size();i++)
            result[i].print();
    }

    void diplayOrderdByNameDesc() {
        vector <Item> name = heap;
        deque <Item> result;

        for (int j=0;j<name.size();j++) {
            result.push_front(heap[0]);
            remove();
        }

        heap = name;

        for (int i=0;i<result.size();i++)
            result[i].print();
    }

    void diplayOrderdByPricAsc() {
        vector <Item> result = heap;

        for (int i=0;i<result.size();i++) {
            int min = i;
            for (int j=i+1;j<result.size();j++) {
                if (result[j].getPrice() < result[min].getPrice())
                min = j;
            }
            swap(result[i], result[min]);
        }


        for (int i=0;i<result.size();i++)
            result[i].print();
    }

    void diplayOrderdByPricDesc() {
        vector <Item> result = heap;

        for (int i=0;i<heap.size();i++) {
            int max = i;
            for (int j=i+1;j<heap.size();j++) {
                if (heap[j].getPrice() > heap[max].getPrice())
                max = j;
            }
            swap(result[i], result[max]);
        }
        
        for (int i=0;i<result.size();i++)
            result[i].print();
    }

};