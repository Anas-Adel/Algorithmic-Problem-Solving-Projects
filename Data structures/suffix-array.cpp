#include <iostream>
using namespace std;


template <typename T>
void merge(T arr[], T left[], T right[], int left_size, int right_size) {
    int i=0,j=0, k=0;
    while (i<left_size && j<right_size) {
        if (left[i] < right[j]) {
        arr[k] = left[i];
        i++;
        }
        else {
        arr[k] = right[j];
        j++;
        }
        k++;
    }
    while (i<left_size) {
        arr[k] = left[i];
        i++;
        k++;
    }
    while (j<right_size) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

template <typename T>
void merge_sort(T list[], int size) {
    if (size == 1)
    return;

    int left_size = (size+1)/2;
    int right_size = size/2;
    T left[left_size];
    T right[right_size];

    for (int i=0;i<left_size;i++)
        left[i] = list[i];
    for (int i=0;i<right_size;i++)
        right[i] = list[left_size+i];

    merge_sort(left, left_size);
    merge_sort(right, right_size);

    merge(list, left, right, left_size, right_size);
}


class character {
    public:
    char ch;
    int position;
    int v1;
    int v2;
    character(char c) {
        ch = c;
        v1 = 0;
        v2 = 0;
    }
    character(char c, int pos) {
        ch = c;
        position = pos;
        v1 = 0;
        v2 = 0;
    }
    character() {
        v1 = 0;
        v2 = 0;
    }
    bool operator<(character char2) {
        if (this->ch < char2.ch)
        return true;
        else if (this->ch == char2.ch && this->v1 < char2.v1)
        return true;
        else if (this->ch == char2.ch && this->v1 == char2.v1 && this->v2 < char2.v2)
        return true;
        else
        return false;
    }
    bool operator==(character char2) {
        if (this->ch == char2.ch && this->v1 == char2.v1 && this->v2 == char2.v2)
        return true;

        return false;
    }
    void operator=(character char2) {
        this->ch = char2.ch;
        this->position = char2.position;
        this->v1 = char2.v1;
        this->v2 = char2.v2;
    }
};

class SuffixArray {
    character* Text;
    int size;
    public:
    SuffixArray(string s) {
        Text = new character[s.size()];
        for (int i=0;i<s.size();i++) {
            character c(s[i], i);
            Text[i] = c;
        }

        size = s.size();
    }

    ~SuffixArray() {
        delete[] Text;
    }

    // Total time complexity O(n(logn)^2) and Total space complexity is O(n)
    void ConstructUsingPrefixDoubling() {
        character t[size];

        int k = 1;
        bool repetition_exists = true;
        // time complexity O(logn)
        while (repetition_exists) {
            repetition_exists = false;

            // copy Text to t array
            for (int i=0;i<size;i++) 
            t[i] = Text[i];
            
            // sort t array.time complexity O(nlogn)
            merge_sort(t, size);

            // get v1 for all characters
            for (int i=1;i<size;i++) {
                if (t[i].ch == t[i-1].ch && t[i].v1 == t[i-1].v1 && t[i].v2==t[i-1].v2) {
                    Text[t[i].position].v1 = Text[t[i-1].position].v1;
                    repetition_exists = true;
                }
                else {
                    Text[t[i].position].v1 = Text[t[i-1].position].v1+1;
                }
            }

            // get v2 for all characters
            for (int i=0;i<size;i++) {
                int n = Text[i+k].v1;
                if (i+k >= size) n = 0;
                Text[i].v2 = n;
            }
            
            // cout << "k="<<k/2<<": ";
            // for (int i=0;i<size;i++)
            // cout << Text[i].v1 << " ";
            // cout << "\n";

            k*=2;
        }
        merge_sort(Text, size);
    }

    void Print() {
        cout << "sa : ";
        for (int i=0;i<size;i++)
        cout << Text[i].position << " ";
    }
};


int main()
{
 SuffixArray t("ACGACTACGATAAC$");
 t.ConstructUsingPrefixDoubling();
 t.Print(); // Prints: 14 11 12 0 6 3 9 13 1 7 4 2 8 10 5
 return 0;
}
