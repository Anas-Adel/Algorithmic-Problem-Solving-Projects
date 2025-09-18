// File: A2_Task2_S1_S2_20220381_20220399_20220070
// Purpose: Developing a new C++ type (class)
// that can hold unlimited decimal values and performs arithmetic operations on them like: +, -, <, and >.
// Author: Youssef Abdulmoneim, Anas Adel, Yassin Ali
// Section: S1,S2
// ID: 20220399, 20220070, 20220381
// TA: Khaled Ebrahim
// Date: 5 Nov 2023

#include "BigReal.cpp"

using namespace std;

int main() {
    cout << "---------------TEST_ONE--------------------\n";
    BigReal n1("5.15"), n2("9.87");
    BigReal n3 = n1 + n2;
    BigReal n4 = n1 - n2;
    cout << n3 << n4;
    cout << n3.Sign() << "\n";
    cout << n4.size() << "\n";
    cout << (n3 > n4) << "\n";
    cout << "---------------TEST_TWO--------------------\n";
    BigReal n5("-5.15"), n6("-9.87");
    BigReal n7 = n5 + n6;
    BigReal n8 = n5 - n6;
    cout << n7 << n8;
    cout << (n7 < n8) << "\n";
    cout << n7.Sign() << "\n";
    cout << "---------------TEST_THREE--------------------\n";
    BigReal n9("-5.15"), n10("9.87");
    BigReal n11 = n9 + n10;
    BigReal n12 = n9 - n10;
    cout << n11 << n12;
    cout << (n11 == n12) << "\n";
    cout << n11.Sign() << "\n";
    cout << "---------------TEST_FOUR--------------------\n";
    BigReal r1("11.90000000000000000000000000001");
    BigReal r2("233333333333333339.1134322222222222222292");
    BigReal r3 = r1 + r2;
    cout << r3 << r3.Sign() << "\n";
    cout << "---------------TEST_FIVE--------------------\n";
    BigReal r4("5.15"), r5("-9.80");
    BigReal r6 = r4 + r5;
    BigReal r7 = r4 - r5;
    cout << r6 << r7;
    cout << (r6 < r7) << "\n";
    cout << r7.Sign() << "\n";
    cout << r7.size() << "\n";
    cout << "---------------TEST_SIX--------------------\n";
    BigReal r8("900.90"), r9("-100.50");
    BigReal r10 = r8 + r9;
    BigReal r11 = r8 - r9;
    cout << r10 << r11;
    cout << r10.Sign() << "\n";
    cout << "---------------TEST_SEVEN--------------------\n";
    BigReal c1("-5000.123456"), c2("1000.123456");
    BigReal c3 = c1 + c2;
    cout << c3;
    cout << c3.Sign() << "\n";
    cout << "---------------TEST_EIGHT--------------------\n";
    BigReal x1("0.0"), x2("0.0");
    BigReal x3 = x1 + x2;
    BigReal x4 = x1 - x2;
    cout << x3 << x4;
    cout << x3.Sign() << "\n";
    cout << x4.size() << "\n";
    cout << (x3 == x4) << "\n";
    cout << "---------------TEST_NINE--------------------\n";
    BigReal y1("10.0");
    BigReal y2("4.0");
    BigReal y3 = y1 + y2;
    BigReal y4 = y1 - y2;
    cout << y3 << '\n' << y4;
    cout << y3.Sign() << "\n";
    cout << y4.size() << "\n";
    cout << (y3 == BigReal("0.0")) << "\n";
}