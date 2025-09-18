#ifndef BIGDECIMALINT_BIGREAL_H
#define BIGDECIMALINT_BIGREAL_H

#include "bits/stdc++.h"

using namespace std;

class BigReal {
private:
    string number;
    string integer;
    string fraction;
    char sign;

    bool isValidReal(string realnumber);

public:
    BigReal(string realNumber);

    bool operator<(const BigReal &anotherDec);

    bool operator>(const BigReal &anotherDec);

    bool operator==(const BigReal anotherDec);

    BigReal(const BigReal &other);                   // copy constructor

    BigReal &operator=(BigReal const &anotherDec);          //assignment operator

    BigReal operator+(BigReal &other);
    
    BigReal operator-(BigReal &other);

    friend ostream &operator<<(ostream &out, BigReal &num);

    void print();

    int size();                  //returns size of the number

    char Sign();                 //returns sign of the number

};


#endif //BIGDECIMALINT_BIGREAL_H