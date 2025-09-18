#include <iostream>
#include <bits/stdc++.h>
using namespace std;
template  <class T>
    void bubbleSort(vector <T> &arr,int size){
    bool swapped;
    for (int i = 0; i < size - 1 ; ++i) {
        swapped = false;
        for (int j = size -1 ; j > i ; --j) {
            if(arr[j] < arr[j-1]) {
                T temp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = temp;
                swapped = true;
            }
        }

   if(!swapped)//if array is sorted
       break;
    }

    }

// int main() {
//     // clock_t start,end;
//     // string names[4] = {"sara ahmed","ali kamal","mohamed osama","mariam mostafa"};
//     // start = clock();
//     // bubbleSort(names,4);
//     // for (int i = 0; i <4 ; ++i) {
//     //     cout<<names[i]<<endl;
//     // }
//     // end = clock();
//     // double time_taken = double(end - start) * 1000 / double(CLOCKS_PER_SEC);
//     // cout <<"Running time: " << time_taken << " milliseconds.\n";
//     // float GPA[4] = {3.5,2.4,4,3.2};
//     // start = clock();
//     // bubbleSort(GPA,4);
//     // for (int i = 0; i <4 ; ++i) {
//     //     cout<<GPA[i]<<endl;
//     // }
//     // end = clock();
//     // cout <<"Running time: " << time_taken << " milliseconds.\n";
//     // return 0;
// }
