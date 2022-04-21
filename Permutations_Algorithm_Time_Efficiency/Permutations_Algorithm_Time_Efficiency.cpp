#include <iostream>
#include <string>
#include <chrono>

using namespace std;

void Permutations(string& set, string prefix, int n, int length);
void Combinations(string& set, string prefix, int n, int m);
double Time(string& set, string prefix, int n, int length, void (*pf)(string&, string, int, int));

int main()
{
    cout << "Enter the number of elements in your set: ";
    int n;
    cin >> n;
    cin.get();

    // fill set with natural numbers
    string set = "";
    for (int i = 1; i <= n; i++)
        set += to_string(i);

    cout << "\nAll possible permutations:\n";

    double total = Time(set, "", n, n, Permutations);

    cout << "\nEnter m: ";
    int m;
    cin >> m;

    total += Time(set, "", n, m, Combinations);

    cout << "\n\nTime elapsed: " << RoundTo(total, 2) << " seconds.\n";
}

//
// Generate permutations
//
void Permutations(string& set, string prefix, int n, int length)
{
    if (length == 1)
        for (int j = 0; j < n; j++)
            cout << prefix + set[j] << endl; // print all permutations of an element

    else
        for (int i = 0; i < n; i++)
            Permutations(set, prefix + set[i] + " ", n, length - 1);
}

//
// Count combinations
//
void Combinations(string& set, string prefix, int n, int m)
{
    cout << "\nNumber of combinations:\n";
    cout << (Factorial(n + m - 1)) / (Factorial(m) * Factorial(n - 1));
}

//
// Get time efficiency
//
double Time(string& set, string prefix, int n, int length, void (*pf)(string&, string, int, int))
{
    auto begin = chrono::high_resolution_clock::now();

    pf(set, "", n, length);

    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);

    return elapsed.count() * 1e-9;
}

//
// Round double value to x.xx format
//
double RoundTo(double value, unsigned denom)
{
    return int(value) + round(fmod(value, 1) * pow(10, denom)) / pow(10, denom);
}

//
// Get factorial of a number
//
long double Factorial(int i)
{
    if (i > 1)
        return i * Factorial(i - 1);
    else return i;
}