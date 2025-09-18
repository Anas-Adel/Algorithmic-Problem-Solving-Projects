#include <iostream>
using namespace std;

int sequential_search(int List[], int size, int target)
{
    for (int i = 0; i < size; i++)
    {
        if (target == List[i])
            return i;
    }
    return -1;
}

int recursive_sequential_search(int List[], int size, int target, int i = 0)
{
    if (i == size)
        return -1;
    if (target == List[i])
        return i;
    else
        return recursive_sequential_search(List, size, target, i + 1);
}

int binary_search(int List[], int size, int target)
{
    int begin = 0;
    int end = size;
    int i;
    while (begin < end)
    {
        i = (begin + end) / 2;
        if (target == List[i])
            return i;
        else if (target > List[i])
            begin = i + 1;
        else
            end = i;
    }
    return -1;
}

int recursive_binary_search(int List[], int size, int target, int begin = 0, int end = -1)
{
    if (end == -1)
        end = size;

    int i = (begin + end) / 2;

    if (begin >= end)
        return -1;

    if (target == List[i])
        return i;
    else if (target > List[i])
        return recursive_binary_search(List, size, target, i + 1, end);
    else
        return recursive_binary_search(List, size, target, begin, i);
}

int main()
{
    int List[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int size = sizeof(List) / sizeof(List[0]);
    int target = 6;

    int index = sequential_search(List, size, target);
    if (index == -1)
        cout << "Sequential Search: not found";
    else
        cout << "Sequential Search: found at index " << index;

    index = recursive_sequential_search(List, size, target);
    if (index == -1)
        cout << "\nRecursive Sequential Search: not found";
    else
        cout << "\nRecursive Sequential Search: found at index " << index;

    index = binary_search(List, size, target);
    if (index == -1)
        cout << "\nBinary Search: not found";
    else
        cout << "\nBinary Search: found at index " << index;

    index = recursive_binary_search(List, size, target);
    if (index == -1)
        cout << "\nRecursive Binary Search: not found";
    else
        cout << "\nRecursive Binary Search: found at index " << index;
}
