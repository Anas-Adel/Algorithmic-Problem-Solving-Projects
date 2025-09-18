#include <bits/stdc++.h>
using namespace std;


template <typename T>
bool is_sorted(vector <T>& list,int start, int end) {
    bool sorted = true;
    while (start < end) {
        if (list[start+1] < list[start] ) {
            sorted = false;
            break;
        }
        start++;
    }
    return sorted;
}

template <typename T>
void quick_sort(vector <T>& list,int start, int end) {
    if (start >= end)
        return;

    if (is_sorted(list, start, end)) // to prevent the complexity from being O(n^2)
        return;                      // because if the list is sorted quick_sort will have complexity of O(n^2)

    T pivot = list[start];
    int i=start,j=start;

    while(j<end) {
        j++;
        if (list[j] < pivot) {
            i++;
            T temp = list[i];
            list[i] = list[j];
            list[j] = temp;
        }
    }
    T temp = list[i];
    list[i] = list[start];
    list[start] = temp;

    quick_sort(list, 0,i-1);
    quick_sort(list, i+1, end);
}

    
// int main() {
//     vector <int> list = {10,4,8,6,100,3,9,5,1,0,7,2};
//     clock_t start,end;
//     start = clock();
//     quick_sort(list, 0, list.size()-1);
//         for (int i=0;i<list.size();i++) {
//         cout << list[i] << " ";
//     }
//     end = clock();
//     double time_taken = double(end - start) * 1000 / double(CLOCKS_PER_SEC);
//     cout <<"Running time: " << time_taken << " milliseconds.\n";
// }
