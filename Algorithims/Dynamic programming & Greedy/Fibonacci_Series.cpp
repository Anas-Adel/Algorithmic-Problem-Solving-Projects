#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long

// Fibonacci Series Using Recursion.
int recursiveFibonacci(int n) // Time Complexity = O(2^n)
{
    if (n <= 1)
        return n;

    return recursiveFibonacci(n - 1) + recursiveFibonacci(n - 2);
}

// 2x2 Matrix Multiplication Function
void multiply(ull F[2][2], ull M[2][2]) // Time Complexity = O(1)
{
    ull x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
    ull y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
    ull z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
    ull w = F[1][0] * M[0][1] + F[1][1] * M[1][1];

    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}

// Matrix Power Function using Divide and Conquer
void power(ull F[2][2], ull n) // Time Complexity = O(logn)
{
    if (n == 0 || n == 1)
        return;

    ull M[2][2] = {{1, 1}, {1, 0}};

    power(F, n / 2);
    multiply(F, F);

    if (n % 2 != 0)
        multiply(F, M);
}

// Fibonacci Series using Matrix Multiplication
ull matrixFibonacci(ull n) // Time Complexity = O(logn)
{
    if (n == 0)
        return 0;

    ull F[2][2] = {{1, 1}, {1, 0}};
    power(F, n - 1);

    return F[0][0];
}

// Fibonacci Series using Dynamic Programming
ull dpFibonacci(ull n) // Time Complexity = O(n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    ull fibArr[n + 1];
    fibArr[0] = 0;
    fibArr[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        fibArr[i] = fibArr[i - 1] + fibArr[i - 2];
    }
    return fibArr[n];
}

int main()
{
    int n;
    cout << "Enter a number: ";
    cin >> n;

    // Recursive approach (Not Recommended for large Numbers)
    cout << "Recursive Fibonacci of " << n << " is " << recursiveFibonacci(n) << endl;

    // Matrix Multiplication approach
    cout << "Matrix Fibonacci of " << n << " is " << matrixFibonacci(n) << endl;

    // Dynamic Programming approach
    cout << "DP Fibonacci of " << n << " is " << dpFibonacci(n) << endl;

    return 0;
}
