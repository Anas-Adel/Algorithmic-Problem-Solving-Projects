#include "merge_sort.cpp"
#include "quick_sort.cpp"
#include "insertionSort.cpp"
#include "selectionSort.cpp"
#include "bubbleSort.cpp"
#include "shellSort.cpp"
#include <bits/stdc++.h>
using namespace std::chrono;
using namespace std;

class Student {
    string id;
    string name;
    double gpa;
    
    public:
    Student() {}
    Student(string id, string name, double gpa) {
        this->id = id; 
        this->name = name;
        this->gpa = gpa;
    }
    void set_name(string name) {
        this->name = name;
    }
    void set_id(string id) {
        this->id = id;
    }
    void set_gpa(double gpa) {
        this->gpa = gpa;
    }
    string get_name() {
        return name;
    }
    string get_id() {
        return id;
    }
    double get_gpa() {
        return gpa;
    }
    bool operator < (const Student& stud) {
        if (this->name < stud.name)
        return true;
        return false;
    }
    bool operator ==( const Student& stud) {
        if (this->name == stud.name)
        return true;
        return false;
    }
};

vector<Student> read_file(string fileName) {
    ifstream inputFile(fileName); 
    vector <Student> students;
    string line;

    getline(inputFile, line);
    int students_num = stoi(line);

    for (int i=0;i<students_num;i++) {
        Student stud;
        getline(inputFile, line);
        stud.set_name(line);
        getline(inputFile, line);
        stud.set_id(line);
        getline(inputFile, line);
        stud.set_gpa(stod(line));
        students.push_back(stud);
    }
    inputFile.close();
    return students;
}

void write_in_file(vector<Student> &Students, ofstream &outputFile) {
        for (int i = 0; i < Students.size(); i++) {
            outputFile << Students[i].get_name() << '\n';
            outputFile << Students[i].get_id() << '\n';
            outputFile << Students[i].get_gpa() << '\n';
        }
    }

string algos[6] = {"Merge sort", "Quick sort" , "Insertion sort", "Selection sort", "Shell sort", "Bubble sort"};

void sort_by_name(vector<Student>& Students) {
    ofstream outputFile("SortedByName.txt");

    auto start = high_resolution_clock::now();
    merge_sort(Students);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    outputFile << "Algorithm: " << "merge sort" << '\n';
    outputFile << "Running Time: " << duration.count() << " nanoseconds" <<'\n';
    write_in_file(Students, outputFile);


    for (int i=1;i<6;i++) {
        start = high_resolution_clock::now();

        switch (i) {
        case 1:
            quick_sort(Students, 0, Students.size()-1);
            break;
        case 2:
            InsertionSort(Students, Students.size());
            break;
        case 3:
            SelectionSort(Students, Students.size());
            break;
        case 4:
            shellSort(Students, Students.size());
            break;
        case 5:
            bubbleSort(Students, Students.size());
            break;
        }

        stop = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(stop - start);
        outputFile << "Algorithm: " << algos[i] << '\n';
        outputFile << "Running Time: " << double(duration.count()) << " nanoseconds" << '\n';
        write_in_file(Students, outputFile);
    }


    outputFile.close();
}


void sort_by_gpa(vector<Student> Students) {
    ofstream outputFile("SortedByGPA.txt");
    vector <double> stds_gpa(Students.size(), 0);

    auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);


    for (int z=0;z<6;z++) {
        for (int i =0; i < Students.size(); i++)
            stds_gpa[i] = Students[i].get_gpa();

        start = high_resolution_clock::now();
        switch (z) {
        case 0:
            merge_sort(stds_gpa);
            break;
        case 1:
            quick_sort(stds_gpa, 0, stds_gpa.size() - 1);
            break;
        case 2:
            InsertionSort(stds_gpa, stds_gpa.size());
            break;
        case 3:
            SelectionSort(stds_gpa, stds_gpa.size());
            break;
        case 4:
            shellSort(stds_gpa, stds_gpa.size());
            break;
        case 5:
            bubbleSort(stds_gpa, stds_gpa.size());
            break;
        }

        stop = high_resolution_clock::now();

        for (int i = 0; i < stds_gpa.size(); i++)
            for (int j = 0; j < Students.size(); j++)
                if (Students[j].get_gpa() == stds_gpa[i]) {
                    swap(Students[i], Students[j]);
                    break;
                }
        for (int i = 0; i < Students.size() / 2; i++)
            swap(Students[i], Students[Students.size() - i - 1]);

        
        duration = duration_cast<nanoseconds>(stop - start);
        outputFile << "Algorithm: " << algos[z] << '\n';
        outputFile << "Running Time: " << duration.count() << " nanoseconds" << '\n';
        write_in_file(Students, outputFile);
    }


    outputFile.close();
}

int main() {
    vector Students = read_file("students.txt");

    sort_by_name(Students);

    sort_by_gpa(Students);
}
