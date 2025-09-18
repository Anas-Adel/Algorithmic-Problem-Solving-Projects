#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct node
{
    T value;
    node *next = nullptr;
};

template <typename T>
class CircularLinked
{
    int size = 0;
    node<T> *head = nullptr;
    node<T> *last = nullptr;

public:
    CircularLinked(T val)
    {
        insertAtTail(val);
    }
    template <typename... Ts>
    CircularLinked(T val, Ts... vals)
    {
        insertAtTail(val, vals...);
    }

    void insertAtHead(T val)
    {
        node<T> *n = new node<T>;
        n->value = val;
        n->next = head;
        head = n;
        if (last == nullptr)
            last = n;
        last->next = head;
        size++;
    }
    template <typename... Ts>
    void insertAtHead(T val, Ts... vals)
    {
        node<T> *n = new node<T>;
        n->value = val;
        n->next = head;
        head = n;
        if (last == nullptr)
            last = n;
        last->next = head;
        size++;
        insertAtHead(vals...);
    }

    void insertAtTail(T val)
    {
        node<T> *n = new node<T>;
        n->value = val;
        if (last != nullptr)
        {
            last->next = n;
            last = n;
        }
        else
        {
            head = n;
            last = n;
        }
        last->next = head;
        size++;
    }
    template <typename... Ts>
    void insertAtTail(T val, Ts... vals)
    {
        node<T> *n = new node<T>;
        n->value = val;
        if (last != nullptr)
        {
            last->next = n;
            last = n;
        }
        else
        {
            head = n;
            last = n;
        }
        last->next = head;
        size++;
        insertAtTail(vals...);
    }

    void insertAt(T val, int i)
    {
        node<T> *current = head;
        if (i > size) {
            insertAtTail(val);
            return;
        }
        for (int j = 0; j < i - 1; j++)
            current = current->next;

        node<T> *n = new node<T>;
        n->value = val;
        n->next = current->next;
        current->next = n;
        last->next = head;
        size++;
    }

    void removeAtHead()
    {
        node<T> *p = head;
        head = head->next;
        last->next = head;
        delete p;
        size--;
    }

    void removeAtTail()
    {
        node<T> *current = head;
        for (int i = 0; i < size - 2; i++)
            current = current->next;
        last = current;
        current = current->next;
        delete current;
        last->next = head;
        size--;
    }

    void removeAt(int i)
    {
        node<T> *current = head;
        if (i > size)
        {
            cout << "index out of the list";
            return;
        }
        for (int j = 0; j < i - 2; j++)
            current = current->next;

        node<T> *n = current->next;
        current->next = current->next->next;
        delete n;
        last->next = head;
        size--;
    }

    T retrieveAt(int i)
    {
        node<T> *current = head;
        for (int j = 0; j < i; j++)
            current = current->next;

        return current->value;
    }

    void replaceAt(T val, int i)
    {
        node<T> *current = head;
        for (int j = 0; j < i; j++)
            current = current->next;

        current->value = val;
    }

    bool isExist(T val)
    {
        node<T> *current = head;
        for (int j = 0; j < size; j++)
        {
            if (current->value == val)
                return true;
            current = current->next;
        }
        return false;
    }

    bool isItemAtEqual(T val, int i)
    {
        node<T> *current = head;
        for (int j = 0; j < i - 1; j++)
            current = current->next;

        if (current->value == val)
            return true;
        else
            return false;
    }

    void swap(int first, int second) {
        if (first > size-1 or second >size-1) {
            cout << "index out of range";
            return;
        }
        if (first > second) {
            swap(second, first);
            return;
        }
        if (first == second)
        return;
        node<T> *current = head;
        node<T> *f, *s;
        for (int i = 0; i < size - 1; i++) {
            if (i == first - 1)
                f = current;
            if (i == second - 1)
                s = current;
            current = current->next;
        }


        if (first == 0) {
            if (second == size - 1)
                last = head;
            if (second - first > 1) {
                node<T> *temp = s->next->next;
                s->next->next = head->next;
                head->next = temp;
                temp = head;
                head = s->next;
                s->next = temp;
            }
            else {
                s = s->next;
                node<T> *temp = s->next;
                s->next = head;
                head->next = temp;
                head = s;
            }
        }
        else {
            if (second == size - 1)
                last = f;
            if (second - first > 1) {
                node<T> *temp = s->next->next;
                s->next->next = f->next->next;
                f->next->next = temp;
                temp = f->next;
                f->next = s->next;
                s->next = temp;
            }
            else {
                s = s->next;
                node<T> *temp = s->next;
                s->next = f->next;
                f->next->next = temp;
                f->next = s;
            }
        }
        last->next = head;
    }

    bool isEmpty()
    {
        if (size == 0)
            return true;
        else
            return false;
    }

    int linkedListSize()
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
        if (head == nullptr)
        {
            cout << "list is empty!" << '\n';
            return;
        }
        cout << current->value;
        current = current->next;
        for (int i = 0; i < size -1; i++)
        {
            cout << " , " << current->value;
            current = current->next;
        }
        cout << '\n';
    }
};

int main()
{
    CircularLinked<int> list(1, 2, 3, 4, 5);

    cout << "This is the initial linked list values: ";
    list.print();

    cout << "insert at head 0 : ";
    list.insertAtHead(0);
    list.print();

    cout << "insert at tail 6 : ";
    list.insertAtTail(6);
    list.print();

    cout << "insert at index 3 value 0 : ";
    list.insertAt(3, 3);
    list.print();

    cout << "remove at head (0) : ";
    list.removeAtHead();
    list.print();

    cout << "remove at tail (6) : ";
    list.removeAtTail();
    list.print();

    cout << "remove at index 3 (3) : ";
    list.removeAt(3);
    list.print();

    cout << "retrive at index 4 : ";
    cout << list.retrieveAt(4) << '\n';

    cout << "replace at index 4 with the value 6 : ";
    list.replaceAt(6, 4);
    list.print();

    cout << "is 6 Exist: ";
    cout << list.isExist(6) << '\n';
    cout << "is Item at index 4 equal 5 : ";
    cout << list.isItemAtEqual(5, 4) << '\n';

    cout << "swap index 1 with 3 : ";
    list.swap(3, 1);
    list.print();

    cout << "linked List Size : ";
    cout << list.linkedListSize() << '\n';

    cout << "Clear list then print : ";
    list.clear();
    list.print();
    cout << "is list empty: ";
    cout << list.isEmpty() << '\n';
}
