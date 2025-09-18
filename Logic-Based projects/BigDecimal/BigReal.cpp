#include "BigReal.h"


bool BigReal::isValidReal(string realNumber) {
    // You can use regular expressions to validate the input
    regex r("^[-+]?[0-9]*\\.?[0-9]+$");
    return regex_match(realNumber, r);
}

BigReal::BigReal(string realNumber) {
    if (isValidReal(realNumber)) {
        if (realNumber[0] == '-') {
            sign = '-';
            realNumber.erase(0,1);
        } else if (realNumber[0] == '+') {
            sign = '+';
            realNumber.erase(0,1);;
        }
        else {
            sign = '+';
        }
        number = realNumber;
        if (realNumber.find('.') != string::npos) {
            integer = realNumber.substr(0, realNumber.find('.'));
            fraction = realNumber.substr(integer.size() + 1, realNumber.size() - 1);
        }
        else {
            fraction = "0";
            integer = realNumber;
        }

    }
    else {
        number = "0";
        cout<<"Invalid real number";
        return;
    }
}

bool BigReal::operator<(const BigReal &anotherDec)
{
    if (sign == '-' and anotherDec.sign == '+')
        return true;
    if (sign == '+' and anotherDec.sign == '-')
        return false;


    string int_1, int_2 , frac_1, frac_2;


//  make the two integer strings with the same size to compare them
    for (int i=0;i < integer.size()-anotherDec.integer.size(); i++)
        int_2 += '0';
    for (int i=0;i < anotherDec.integer.size()-integer.size(); i++)
        int_1 += '0';
    int_1 += integer;
    int_2 += anotherDec.integer;


//  compare every digit in the two integer strings
    for (int i=0; i<int_1.size(); i++) {
        if (int_1[i] < int_2[i] && sign == '+')
            return true;
        else if (int_1[i] > int_2[i] && sign == '+')
            return false;
        else if (int_1[i] < int_2[i] && sign == '-')
            return false;
        else if (int_1[i] > int_2[i] && sign == '-')
            return true;
    }


//  make the two fraction strings with the same size to compare them
    frac_1 += fraction;
    frac_2 += anotherDec.fraction;
    for (int i=0;i < fraction.size()-anotherDec.fraction.size(); i++)
        frac_2 += '0';
    for (int i=0;i < anotherDec.fraction.size()-fraction.size(); i++)
        frac_1 += '0';


//  compare every digit in the fraction strings
    for (int i=0; i< frac_1.size(); i++) {
        if (frac_1[i] < frac_2[i] && sign == '+')
            return true;
        else if (frac_1[i] > frac_2[i] && sign == '+')
            return false;
        else if (frac_1[i] < frac_2[i] && sign == '-')
             return false;
        else if (frac_1[i] > frac_2[i] && sign == '-')
            return true;
    }

// if there is no number that is bigger than the other then they are equal and return false
    return false;
}

bool BigReal::operator>(const BigReal &anotherDec)
{
    if (sign == '-' and anotherDec.sign == '+')
        return false;
    if (sign == '+' and anotherDec.sign == '-')
        return true;

    string int_1, int_2 , frac_1, frac_2;


//  make the two integer strings with the same size to compare them
    for (int i=0;i < integer.size()-anotherDec.integer.size(); i++)
        int_2 += '0';
    for (int i=0;i < anotherDec.integer.size()-integer.size(); i++)
        int_1 += '0';
    int_1 += integer;
    int_2 += anotherDec.integer;

//  compare every digit in the two integer strings
    for (int i=0; i<int_1.size(); i++) {
        if (int_1[i] > int_2[i] && sign == '+')
            return true;
        else if (int_1[i] < int_2[i] && sign == '+')
            return false;
        else if (int_1[i] > int_2[i] && sign == '-')
            return false;
        else if (int_1[i] < int_2[i] && sign == '-')
            return true;
    }


//  make the two fraction strings with the same size to compare them
    frac_1 += fraction;
    frac_2 += anotherDec.fraction;
    for (int i=0;i < fraction.size()-anotherDec.fraction.size(); i++)
        frac_2 += '0';
    for (int i=0;i < anotherDec.fraction.size()-fraction.size(); i++)
        frac_1 += '0';


//  compare every digit in the two fraction strings
    for (int i=0; i< frac_1.size(); i++) {
        if (frac_1[i] > frac_2[i] && sign == '+')
            return true;
        else if (frac_1[i] < frac_2[i] && sign == '+')
            return false;
        else if (frac_1[i] > frac_2[i] && sign == '-')
             return false;
        else if (frac_1[i] < frac_2[i] && sign == '-')
            return true;
    }

//  if there is no number that is bigger than the other then they are equal and return false
    return false;
}

bool BigReal::operator==(const BigReal anotherDec)
{
    if (*this > anotherDec || *this < anotherDec)
        return false;
    else
    return true;
}

BigReal::BigReal(const BigReal &other) {
     this -> number = other.number;
     this -> sign = other.sign;
     this -> integer = other.integer;
     this -> fraction = other.fraction;
}

BigReal &BigReal::operator=(const BigReal &anotherDec) {
    sign = anotherDec.sign;
    number = anotherDec.number;
    integer = anotherDec.integer;
    fraction = anotherDec.fraction;
    return *this;
}

BigReal BigReal::operator+(BigReal &other) {
    string result, result_integer, result_fraction;

    // Make the fraction parts the same length
    while (fraction.size() < other.fraction.size()) fraction += '0';
    while (other.fraction.size() < fraction.size()) other.fraction += '0';

    // Make the integer parts the same length
    while (integer.size() < other.integer.size()) integer = '0' + integer;
    while (other.integer.size() < integer.size()) other.integer = '0' + other.integer;

    if (sign == other.sign) {
        // Add the fraction parts
        int carry = 0;
        for (int i = fraction.size() - 1; i >= 0; --i) {
            int temp = carry + (fraction[i] - '0') + (other.fraction[i] - '0');
            if (temp > 9) {
                carry = 1;
                temp -= 10;
            } else {
                carry = 0;
            }
            result_fraction = static_cast<char>(temp + '0') + result_fraction;
        }
        // Add the integer parts
        for (int i = integer.size() - 1; i >= 0; --i) {
            int temp = carry + (integer[i] - '0') + (other.integer[i] - '0');
            if (temp > 9) {
                carry = 1;
                temp -= 10;
            }
            else
                carry = 0;
            result_integer = static_cast<char>(temp + '0') + result_integer;
        }

        // If there's still a carry, add it to the result
        if (carry > 0) result_integer = static_cast<char>(carry + '0') + result_integer;
        for(int i = 0; result_integer[i] == '0'; ++i)
            result_integer.erase(i,1);
        result_integer = sign + result_integer;

    }
    else {
        bool are_switched = false;
        char result_sign = sign;
        char other_sign = other.sign;
        char this_sign = sign;
        sign = '+';
        other.sign = '+';
        if(other > *this) {
            string temp_number = number;
            number = other.number;
            other.number = temp_number;

            string temp = integer;
            integer = other.integer;
            other.integer = temp;

            string temp_fraction = fraction;
            fraction = other.fraction;
            other.fraction = temp_fraction;

            result_sign = other_sign;
            are_switched = true;
        }
        sign = this_sign;
        other.sign = other_sign;
        // Subtract the fraction parts
        int borrow = 0;
        for (int i = fraction.size() - 1; i >= 0; --i) {
            int temp = (fraction[i] - '0') - (other.fraction[i] - '0') - borrow;
            if (temp < 0) {
                borrow = 1;
                temp += 10;
            }
            else
                borrow = 0;

            result_fraction = static_cast<char>(temp + '0') + result_fraction;
        }

        // Subtract the integer parts
        for (int i = integer.size() - 1; i >= 0; --i) {
            int temp = (integer[i] - '0') - (other.integer[i] - '0') - borrow;
            // if (i == 0 && temp < 0) {
            //     temp *= -1;
            //     result_integer = static_cast<char>(temp + '0') + result_integer;
            //     result_integer = "-" + result_integer;
            //     break;
            // }
            if (temp < 0) {
                borrow = 1;
                temp += 10;
            }
            else
                borrow = 0;
            result_integer = static_cast<char>(temp + '0') + result_integer;
        }
        result_integer = result_sign + result_integer;

        if (are_switched) {
        string temp_number = number;
        number = other.number;
        other.number = temp_number;

        string temp = integer;
        integer = other.integer;
        other.integer = temp;

        string temp_fraction = fraction;
        fraction = other.fraction;
        other.fraction = temp_fraction; 
        }       
    }

    for(int i = 0; i < result_integer.size(); ++i){
        if(result_integer[i] != '+' and result_integer[i] != '-' and result_integer[i] != '0')
            break;
        if(result_integer[i] == '0')
            result_integer.erase(i,1);
    }

    result = result_integer + "." + result_fraction;
    return BigReal(result);
}

BigReal BigReal::operator-(BigReal &other) {
    string result, result_integer, result_fraction;

    // Make the fraction parts the same length
    while (fraction.size() < other.fraction.size()) fraction += '0';
    while (other.fraction.size() < fraction.size()) other.fraction += '0';

    // Make the integer parts the same length
    while (integer.size() < other.integer.size()) integer = '0' + integer;
    while (other.integer.size() < integer.size()) other.integer = '0' + other.integer;

    if (sign == other.sign) {
        bool are_switched;
        char result_sign = sign;
        char other_sign = other.sign;
        char this_sign = sign;
        sign = '+';
        other.sign = '+';
        if(other > *this) {
            string temp_number = number;
            number = other.number;
            other.number = temp_number;

            string temp = integer;
            integer = other.integer;
            other.integer = temp;

            string temp_fraction = fraction;
            fraction = other.fraction;
            other.fraction = temp_fraction;

            if (this_sign == '+') result_sign = '-';
            else if (this_sign == '-') result_sign = '+';
        }

        sign = this_sign;
        other.sign = other_sign;
        // Subtract the fraction parts
        int borrow = 0;
        for (int i = fraction.size() - 1; i >= 0; --i) {
            int temp = (fraction[i] - '0') - (other.fraction[i] - '0') - borrow;
            if (temp < 0) {
                borrow = 1;
                temp += 10;
            }
            else
                borrow = 0;
            result_fraction = static_cast<char>(temp + '0') + result_fraction;
        }

        // Subtract the integer parts
        for (int i = integer.size() - 1; i >= 0; --i) {
            int temp = (integer[i] - '0') - (other.integer[i] - '0') - borrow;
            // if (i == 0 && temp < 0) {
            //     temp *= -1;
            //     result_integer = static_cast<char>(temp + '0') + result_integer;
            //     result_integer = "-" + result_integer;
            //     break;
            // }
            if (temp < 0) {
                borrow = 1;
                temp += 10;
            }
            else
                borrow = 0;
            result_integer = static_cast<char>(temp + '0') + result_integer;
        }
        result_integer = result_sign + result_integer;

        if (are_switched) {
        string temp_number = number;
        number = other.number;
        other.number = temp_number;

        string temp = integer;
        integer = other.integer;
        other.integer = temp;

        string temp_fraction = fraction;
        fraction = other.fraction;
        other.fraction = temp_fraction; 
        }
    }
    else {
        // Add the fraction parts
        int carry = 0;
        for (int i = fraction.size() - 1; i >= 0; --i) {
            int temp = carry + (fraction[i] - '0') + (other.fraction[i] - '0');
            if (temp > 9) {
                carry = 1;
                temp -= 10;
            } else {
                carry = 0;
            }
            result_fraction = static_cast<char>(temp + '0') + result_fraction;
        }


        // Add the integer parts
        for (int i = integer.size() - 1; i >= 0; --i) {
            int temp = carry + (integer[i] - '0') + (other.integer[i] - '0');
            if (temp > 9) {
                carry = 1;
                temp -= 10;
            }
            else
                carry = 0;
            result_integer = static_cast<char>(temp + '0') + result_integer;
        }

        // If there's still a carry, add it to the result
        if (carry > 0) result_integer = static_cast<char>(carry + '0') + result_integer;

        result_integer = sign + result_integer;
    }
    
    for(int i = 0; i < result_integer.size(); ++i){
        if(result_integer[i] != '+' and result_integer[i] != '-' and result_integer[i] != '0')
            break;
        if(result_integer[i] == '0')
            result_integer.erase(i,1);
    }
    result = result_integer + "." + result_fraction;

    return BigReal(result);
}

ostream &operator<<(ostream &out, BigReal &num)
{
    for(int i = 0; num.integer[i] == '0'; ++i)
        num.integer.erase(i,1);

    if (num.sign == '-')
    out << num.sign;
    
    out << num.integer << '.' << num.fraction << '\n';
    return out;
}

void BigReal::print() {
    cout << sign << integer << '.' << fraction << '\n';
}

// function to return size of number (including decimal point)
int BigReal::size() {
    return number.size();
}

// function to return sign of number
char BigReal::Sign() {
    if (sign == '+')
        return '+';
    else
        return '-';
}