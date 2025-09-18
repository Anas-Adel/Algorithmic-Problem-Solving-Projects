#include <iostream>
#include <bits/stdc++.h>
using namespace std;
template<class T>
void shellSort(vector <T> &arr,int size) {
    // Start with a big gap, then reduce the gap
    for (int gap = size / 2; gap > 0; gap /= 2) {

        for (int i = gap; i < size; ++i) {

            T temp = arr[i];

            int j;
            for (j = i; j >= gap && temp < arr[j - gap]; j -= gap)
                arr[j] = arr[j - gap];


            arr[j] = temp;
        }
    }
}


// int main() {
//     string names[4] = {"sara ahmed","ali kamal","mohamed osama","mariam mostafa"};
//     shellSort(names,4);
//     for (int i = 0; i <4 ; ++i) {
//         cout<<names[i]<<endl;
//     }
//     float GPA[4] = {3.5,2.4,4,3.2};
//     shellSort(GPA,4);
//     for (int i = 0; i <4 ; ++i) {
//         cout<<GPA[i]<<endl;
//     }



//     return 0;
// }
