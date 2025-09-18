#include <bits/stdc++.h>
using namespace std;


class Item {
    string name;
    string category;
    int price;
    public:
    Item(){
    name = "";
    category = "";
    price = 0;
    }
    Item(string n, string c, int p) {
        name = n;
        category = c; 
        price = p;
    }
    void print() {
        cout << "********************\n* Name: " << name << "\n* Category: " << category << "\n* Price: " << price << "\n\n";
    }
    void set_name(string n) {
        name = n;
    }
    string get_name() {
        return name;
    }
    int getPrice() {
        return price;
    }
    bool operator <(const Item& it) {
        return name < it.name;
    }
    bool operator>(const Item item) {
    return name > item.name;
    }
};


class Tree {
public:
    virtual void add(Item it) {}
    virtual void remove() {}
    virtual void display() {}
    virtual void diplayOrderdByNameAsc() {}
    virtual void diplayOrderdByNameDesc() {}
    virtual void diplayOrderdByPricAsc() {}
    virtual void diplayOrderdByPricDesc() {}
};
