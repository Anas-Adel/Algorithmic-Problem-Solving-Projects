#include <bits/stdc++.h>
using namespace std;

template <typename T>
vector <T> merge(vector <T> left, vector <T> right) {
    vector <T> merged;
    int i=0,j=0;
    while (i<left.size() and j<right.size()) {
        if (left[i] < right[j]) {
        merged.push_back(left[i]);
        i++;
        }
        else {
        merged.push_back(right[j]);
        j++;
        }
    }
    while (i<left.size()) {
        merged.push_back(left[i]);
        i++;
    }

    while (j<right.size())
    {
        merged.push_back(right[j]);
        j++;
    }
    
    
    return merged;
}

template <typename T>
void merge_sort(vector <T>& list) {
    if (list.size() == 1)
    return;

    vector <T> left, right;
    for (int i=0;i<list.size();i++) {
        if (i<list.size()/2)
        left.push_back(list[i]);
        else
        right.push_back(list[i]);
    }

    merge_sort(left);
    merge_sort(right);

    list = merge(left, right);

}
    
// int main() {
//     clock_t start,end;
//     start = clock();
//     vector <string> Students = {"bibo","anas","zyaed","careem","ahmed"};
//     merge_sort(Students);

//     for (int i=0;i<Students.size();i++) {
//         cout << Students[i] << " ";
//     }
     
//     end = clock();
//     double time_taken = double(end - start) * 1000 / double(CLOCKS_PER_SEC);
//     cout <<"\nthe time taken is " << time_taken << " milliseconds.\n";

//     start = clock();
    
//     vector <int> Students_num = {5,7,1,8,1001, 0,2,4,9,3,6};
//     merge_sort(Students_num);

//     for (int i=0;i<Students_num.size();i++) {
//         cout << Students_num[i] << " ";
//     }
//     end = clock();
//     time_taken = double(end - start) * 1000 / double(CLOCKS_PER_SEC);
//     cout <<"\nthe time taken is " << time_taken << " milliseconds.\n";
// }
