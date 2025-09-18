#include <bits/stdc++.h>
using namespace std;
template< class T>
struct node{
    T info;
    node *next = nullptr;
    node *prev = nullptr;
};
template <class T>
class Double_linked_list{
private:
    int size = 0;
    node <T> *head = nullptr;
    node <T> *tail = nullptr;
public:
    Double_linked_list(T value){
        insertAtTail(value);

    }

    template <class...Ts>
    Double_linked_list(T value , Ts... values)
    {
        insertAtTail(value, values...);
    }


    void insertAtHead(T value) {
        node<T> *newNode = new node<T>;
        newNode->info = value;
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        if(tail== nullptr){
            tail = newNode;
        }
        size++;

    }

    template<class...Ts>
        void insertAthead(T value,Ts...values) {

        node<T> *newNode = new node<T>;
        newNode->info = value;
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        if(tail== nullptr){
            tail = newNode;
        }
        size++;
        insertAtHead(values...);

    }
    void insertAtTail(T value) {
        node<T>* newNode = new node<T>;
        newNode->info = value;
        if (tail!= nullptr) {
            tail->next= newNode;
            newNode->prev = tail;
            tail = newNode;
        } else {
            head = newNode;
            tail = newNode;

        }
        size++;

    }

    template<class...Ts>
        void insertAtTail(T value , Ts...values ) {
        node<T> *newNode = new node<T>;
        newNode->info = value;
        if (tail != nullptr) {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        } else {
            head = newNode;
            tail = newNode;
        }
        size++;
        insertAtTail(values...);

    }

    void insertAt(T value,int pos) {
        node<T> *current = head;
        node<T> *newnode = new node<T>;
        newnode->info = value;
        newnode->prev = nullptr;
        newnode->next = nullptr;

        if(head == nullptr){
            head = newnode;
            return;
        }

        if (pos > size) {
            insertAtTail(value);
            return;
        }
        for (int i = 0; i < pos - 1; i++)
            current = current->next;

        newnode->next = current->next;
        newnode->prev = current;
        if (current->next != nullptr) {
            current->next->prev = newnode;
        }
        current->next = newnode;

        size++;
    }

    void removeAtHead(){
        node<T> *s = head;
        head = head->next;
        head->next->prev = nullptr;
        delete s;
        size--;

    }
    void removeAtTail(){
        node<T> *current = head;
        for (int i = 0; i < size - 2; i++)
            current = current->next;
        tail->prev = current->prev;
        tail->prev->next= nullptr;
        delete current;
        size--;


    }
    void removeAt(int pos) {
        node<T> *current = head;
        if (pos > size) {
            cout << "index out of list" << endl;
            return;
        }
        if (!head) return; // Empty list


        for (int i = 1; current != NULL && i < pos; i++) {
            current = current->next;
        }

        if (pos == 1) {
            removeAtHead();
        }
        else if (current == tail) {
            removeAtTail();
        }
        else if (current != NULL) {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            size--;
        }

    }
    T retrieveAt(int i)
    {
        node<T> *current = head;
        for (int j = 0; j < i; j++)
            current = current->next;

        return current->info;
    }

    void replaceAt(T value, int i)
    {
        node<T> *current = head;
        for (int j = 0; j < i; j++)
            current = current->next;

        current->info = value;
    }

    bool isExist(T value)
    {
        node<T> *current = head;
        for (int j = 0; j < size; j++)
        {
            if (current->info == value)
                return true;
            current = current->next;
        }
        return false;
    }
    bool isItemAtEqual(T value, int i)
    {
        node<T> *current = head;
        for (int j = 0; j < i - 1; j++)
            current = current->next;

        if (current->info == value)
            return true;
        else
            return false;
    }
    bool isEmpty()
    {
        if (size == 0)
            return true;
        else
            return false;
    }
    int ListSize()
    {
        return size;
    }
    void clear()
    {
        node<T> *current = head;
        for (int i = 0; i < size - 2; i++)
        {
            node<T> *n = current;
            current = current->next;
            delete n;
        }
        head = nullptr;
        size = 0;
    }
    void print()
    {
        node<T> *current = head;
        if (head == nullptr) {
            cout << "list is empty!" << '\n';
            return;
        }
                while (current != nullptr) {
                    cout << current->info << " ";
                    current = current->next;
                }
                cout << endl;

    }
    void swap(int first, int second) {
        if (first > size - 1 or second > size - 1)
        {
            cout << "index out of range";
            return;
        }
        if (first == second)
            return;
        if (first > second) {
            swap(second, first);
            return;
        }

    if (first > size - 1 or second > size - 1)
    {
        cout << "index out of range";
        return;
    }
    if (first == second)
        return;

    node<T> *current = head;
    node<T> *f, *s;
    for (int i = 0; i < size - 1; i++)
    {
        if (i == first - 1)
            f = current;
        if (i == second - 1)
            s = current;
        current = current->next;
    }

    if (first == 0)
    {
        if (second - first > 1)
        {
            head->next->prev = s->next;
            s->next = head;
            if (head->next->prev->next != nullptr)
                head->next->prev->next->prev = head;
            node<T> *temp = head->next;    
            head->next = head->next->prev->next;
            temp->prev->next = temp;
            head->prev = temp->prev->prev;
            head = temp->prev;
            temp->prev->prev = nullptr;
        }
        else
        {

            s = s->next;
            if (s->next != nullptr)
            s->next->prev = s->prev;
            head->next = head->next->next;
            s->next = s->prev;
            s->prev = nullptr;
            head = s;

        }
    }
    else
    {

        if (second - first > 1)
        {
            f->next->prev = s->next->prev;
            s->next->prev = f;
            if (s->next->next != nullptr)
                s->next->next->prev = f->next->next->prev;
                f->next->next->prev = s->next;

                node<T> *temp = s->next->next;
                s->next->next = f->next->next;
                f->next->next = temp;
                temp = f->next;
                f->next = s->next;
                s->next = temp;
        }
        else
        {
            s = s->next;
            if (s->next!=nullptr)
            s->next->prev = f->next;
            f->next->next->prev = f;
            f->next->prev = s;

            node<T> *temp = s->next;
            s->next = f->next;
            f->next->next = temp;
            f->next = s;
        }
    }
    }
};


int main() {
    Double_linked_list<int> list(1, 2, 3, 4, 5);
    cout << "The list values : ";
    list.print();
    cout<<"The size of the list: "<<list.ListSize()<<endl;
    list.insertAt(8,2);
    list.print();
    list.removeAt(3);
    list.print();
    list.swap(1,2);
    list.print();
    cout<<list.isEmpty()<<endl;
    return 0;
}
