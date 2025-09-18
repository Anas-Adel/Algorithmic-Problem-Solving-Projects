#include <bits/stdc++.h>
using namespace std;

class Issue
{
protected:
    int ID, priority;
    string description;
    static int no_issues;
public:
    Issue()
    {
        cout << "default";
    }
    Issue(int id, int pri, string describe = "")
    {
        ID = id;
        priority = pri;
        description = describe;
        no_issues++;
    }

    int NUMBER()
    {
        return no_issues;
    }

    virtual void print()
    {
        cout << "issue id " << ID << " of the priority " << priority;
        if (description.size() != 0)
            cout << " is described \"" << description << "\" \n";
        else
            cout << "\n";
    }

    // friend bool operator<(const Issue &issue1,const Issue &issue2);
    bool operator<(const Issue &issue2)
    {
        if (priority < issue2.priority)
            return true;
        else
            return false;
    }
};

// bool operator<(const Issue &issue1,const Issue &issue2)
//     {
//         if (issue1.priority < issue2.priority)
//             return true;
//         else
//             return false;
//     }
int Issue ::no_issues = 0;

template <class T>
class Bug : public Issue
{
protected:
    T severity;
    int location;
public:
    Bug(int id, int pri, string describe = "", T sev = 'A', int loc = 0) : Issue(id, pri, describe), severity(sev), location(loc) {}

    void print()
    {
        cout << "Bug id " << ID << " of the priority " << priority;
        if (description.size() != 0)
            cout << " is described \"" << description << "\" \n";

        cout << "severity of the bug is " << severity << '\n';
    }
};

int main()
{
    multiset<Issue> Issues;
    Issues.insert(Issue(1, 2, "low priority"));
    Issues.insert(Issue(1, 1, "high priority"));

    // auto it = Issues.begin();
    // for (; it != Issues.end(); it++) {
    // (*it)->print();  
    // cout << '\n';
    // }

    // Issue *ptr = new Bug(1, 1, "no Bug", "a");
    // cout << "number of issues is "<<issue.NUMBER() << '\n';
}