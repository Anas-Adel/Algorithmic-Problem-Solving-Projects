#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

class Heap
{
private:
    vector<int> heap;

    int parent(int index) const { return (index - 1) / 2; }
    int leftChild(int index) const { return 2 * index + 1; }
    int rightChild(int index) const { return 2 * index + 2; }

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    void addElement(int element);
    void removeElement();

    bool isempty() const { return heap.empty(); }
    int size() const { return heap.size(); }
    void displayElements() const;
    void heapSort();
    int getMax() const;
    int getMin() const;
};

void Heap::addElement(int element)
{
    heap.push_back(element); // Add new element at the end
    heapifyUp(size() - 1);   // Restore the heap property
}

void Heap::removeElement()
{
    if (size() == 0)
    {
        cout << "Heap is empty, cannot remove.\n";
        return;
    }
    heap[0] = heap.back(); // Move the last element to the top
    heap.pop_back();       // Remove the last element
    heapifyDown(0);        // Restore the heap property
}

void Heap::heapifyUp(int index)
{
    while (index != 0 && heap[index] > heap[parent(index)])
    {                                           // Max-heap property
        swap(heap[index], heap[parent(index)]); // Swap if the current element violates the heap property
        index = parent(index);                  // Move up the heap
    }
}

void Heap::heapifyDown(int index)
{
    int left = leftChild(index);
    int right = rightChild(index);
    int largest = index;

    if (left < size() && heap[left] > heap[largest])
    {
        largest = left;
    }
    if (right < size() && heap[right] > heap[largest])
    {
        largest = right;
    }

    if (largest != index)
    {
        swap(heap[index], heap[largest]);
        heapifyDown(largest);
    }
}

void Heap::displayElements() const
{
    for (const auto &element : heap)
    {
        cout << element << " ";
    }
    cout << endl;
}

void Heap::heapSort()
{
    vector<int> sortedElements;
    while (!heap.empty())
    {
        sortedElements.push_back(heap[0]); // Get the maximum element
        removeElement();                   // Remove it from the heap
    }

    for (auto it = sortedElements.rbegin(); it != sortedElements.rend(); ++it)
    {
        cout << *it << " "; // Print the sorted elements in ascending order
    }
    cout << endl;
    for (int element : sortedElements)
    {
        addElement(element); // Reinsert elements back into the heap
    }
}

int Heap::getMax() const
{
    return heap.empty() ? -1 : heap[0]; // Return the top element
}

int Heap::getMin() const
{
    int minElement = heap.empty() ? -1 : heap[0];
    for (size_t i = 1; i < heap.size(); ++i)
    {
        if (heap[i] < minElement)
        {
            minElement = heap[i];
        }
    }
    return minElement;
}

void HeapSort(vector<int> &h)
{
    Heap heap;
    for (auto element : h)
        heap.addElement(element); // Add elements to the heap
    for (size_t i = 0; i < h.size(); i++)
    {
        h[h.size() - i - 1] = heap.getMax(); // Get the maximum element
        heap.removeElement();
    }
    return;
}

class PriorityQueue
{
private:
    Heap heap;
    vector<pair<int, int>> elements; // Store pairs of (element, priority)

public:
    void enqueue(int element, int priority)
    {
        elements.push_back({element, priority});
        heap.addElement(priority); // Add priority to the heap
    }

    void dequeue()
    {
        if (heap.isempty())
        {
            cout << "Priority queue is empty.\n";
            return;
        }

        int maxPriority = heap.getMax();
        for (auto it = elements.begin(); it != elements.end(); ++it)
        {
            if (it->second == maxPriority)
            {
                cout << "Dequeued element: " << it->first << " with priority: " << it->second << endl;
                elements.erase(it);   // Remove the element
                heap.removeElement(); // Remove the max priority
                break;
            }
        }
    }

    int peek() const
    {
        return heap.isempty() ? -1 : heap.getMax(); // Returns max priority
    }

    void display() const
    {
        for (const auto &elem : elements)
        {
            cout << "(" << elem.first << ", " << elem.second << ") ";
        }
        cout << endl;
    }

    bool isEmpty() const { return heap.isempty(); }

    int size() const { return heap.size(); }
};

int main()
{
    cout << "Testing Heap:\n";
    Heap heap;
    heap.addElement(3);
    heap.addElement(10);
    heap.addElement(5);
    heap.addElement(8);
    cout << "Heap elements: ";
    heap.displayElements();

    cout << "Max element in heap: " << heap.getMax() << endl;
    cout << "Min element in heap: " << heap.getMin() << endl;

    cout << "Heap after sorting: ";
    heap.heapSort();

    cout << "\nTesting PriorityQueue:\n";
    PriorityQueue pq;
    pq.enqueue(1, 2);
    pq.enqueue(2, 5);
    pq.enqueue(3, 3);
    pq.enqueue(4, 1);
    cout << "Priority Queue elements: ";
    pq.display();

    pq.dequeue();
    pq.dequeue();

    cout << "Priority Queue after two dequeues: ";
    pq.display();

    cout << "\nTesting HeapSort on a vector:\n";
    vector<int> testVector = {15, 3, 7, 10, 1, 4, 8};
    cout << "Original vector: ";
    for (int num : testVector)
    {
        cout << num << " ";
    }
    cout << endl;

    HeapSort(testVector);
    cout << "Sorted vector: ";
    for (int num : testVector)
    {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
