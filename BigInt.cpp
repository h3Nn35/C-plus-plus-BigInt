#include "BigInt.h"
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;


// Konstruktoren
BigInt::BigInt(int n) {
    digits = to_string(n);
}

BigInt::BigInt(unsigned long long int n) {
    digits = to_string(n);
}

BigInt::BigInt(string &text){
    digits = "";
    for (int i = text.size() - 1; i >= 0; i--)
        if (!isdigit(text[i]))
            throw("ERROR! String enthält nicht nur Zahlen");

    digits = text;    
}

BigInt::BigInt(char * text) {
    digits = "";
    for (int i = strlen(text) - 1; i >= 0; i--)
        if (!isdigit(text[i]))
            throw ("ERROR! String enthält nicht nur Zahlen");
        else
            digits.push_back(text[i]);
}

BigInt::BigInt(BigInt & other) : digits(other.digits) {}


// Hilfsfunktionen
bool Null(const BigInt &other) {
    if (other.digits.size() == 1 && other.digits[0] == '0') {
        return true;
    }
    return false;
}

int Length(const BigInt &other) {
    return other.digits.size();
}

int BigInt::operator[](const int index) const {
    if(digits.size() <= index || index < 0) {
        throw ("ERROR! Index ausserhalb des gueltigen Bereichs!");
    }
    return digits[index] - '0';
}

void cleanup(BigInt &a) {
    while (a.digits.substr(0, 1) == "0") {
        a.digits = a.digits.substr(1, a.digits.size() - 1);
    }
}


/***********************    OPERATOREN    ***********************/

// Lesen und schreiben
ostream &operator<<(ostream & out, const BigInt & other) {
    for (int i = 0; i < other.digits.size(); i++){
        out << other.digits[i];
    }
    return out;
}

istream &operator>>(istream & in, BigInt & other){
    string input;
    in >> input;
    other.digits = "";
    for (int i = 0; i < input.size(); i++)
        if (isdigit(input[i]))
            other.digits.append(input.substr(i, 1));
        else
            throw("ERROR! Eingabe enthält nicht nur Zahlen");
    return in;
}


// Direktzuweisungen
BigInt &BigInt::operator=(const BigInt & other) {
    digits = other.digits;
    return *this;
}

BigInt &BigInt::operator=(const string & text) {
    digits = "";
    for (int i = text.size() - 1; i >= 0; i--){
        if (!isdigit(text[i]))
            throw("ERROR! String enthält nicht nur Zahlen");
        digits.push_back(text[i] -'0');
    }
    return *this;
}

BigInt &BigInt::operator=(const unsigned long long & zahl) {
    digits = to_string(zahl);
    return *this;
}

BigInt &BigInt::operator=(const int & zahl) {
    digits = to_string(zahl);
    return *this;
}


// Inkrementieren / Decrementieren
BigInt &BigInt::operator++(){
    int ueber = 1, i = digits.size(), zahl;
    while (ueber > 0){
        i--;
        if (i < 0){
            digits = to_string(ueber) + digits;
            break;
        }
        zahl = digits[i] - '0';
        if (zahl == 9)
            digits[i] = 0 + '0';
        else{
            digits[i] = (zahl + 1) + '0';
            ueber--;
        }
    }
    return *this;
}

BigInt BigInt::operator++(int temp){
    ++(*this);
    return *this;
}

BigInt BigInt::operator--(int temp) {
    --(*this);
    return *this;
}

BigInt &BigInt::operator--() {
    int ueber = 1, i = digits.size(), zahl;
    while (ueber > 0){
        i--;
        if (i < 0){
            digits = to_string(ueber) + digits;
            break;
        }
        zahl = digits[i] - '0';
        if (zahl == 0)
            digits[i] = 9 + '0';
        else{
            digits[i] = (zahl - 1) + '0';
            ueber--;
        }
    }
    return *this;
}


// Addition und Subtraktion
BigInt &operator+=(BigInt &a, const BigInt &b) {
    int i, x, ueber = 0, zahl1, zahl2, zwischenerg, lang = a.digits.size();
    if (a.digits.size() < b.digits.size())
        lang = b.digits.size();
    x = 0;
    while (x < lang || ueber != 0) {
        if (x < a.digits.size())
            zahl1 = stoi(a.digits.substr(a.digits.size() - 1 - x, 1));
        else{
            zahl1 = 0;
        }

        if (x < b.digits.size())
            zahl2 = stoi(b.digits.substr(b.digits.size() - 1 - x, 1));
        else
            zahl2 = 0;

        zwischenerg = zahl1 + zahl2 + ueber;
        if (zwischenerg >= 10)
            ueber = 1;
        else
            ueber = 0;

        if (x < a.digits.size())
            a.digits[a.digits.size() - 1 - x] = (zwischenerg % 10) + '0';
        else{
            a.digits = to_string(zwischenerg % 10) + a.digits;
        }
        x++;
    }
    return a;
}

BigInt operator+(const BigInt &a, const BigInt &b) {
    BigInt temp;
    temp = a;
    temp += b;
    return temp;
}

BigInt &operator-=(BigInt &a, const BigInt &b) {
    if(a < b)
        throw("UNDERFLOW");
    int i, x, ueber = 0, zahl1, zahl2, zwischenerg, lang = a.digits.size();
    if (a.digits.size() < b.digits.size())
        lang = b.digits.size();
    x = 0;
    while (x < lang || ueber != 0) {
        if (x < a.digits.size())
            zahl1 = stoi(a.digits.substr(a.digits.size() - 1 - x, 1));
        else{
            zahl1 = 0;
        }

        if (x < b.digits.size())
            zahl2 = stoi(b.digits.substr(b.digits.size() - 1 - x, 1));
        else
            zahl2 = 0;

        zwischenerg = zahl1 - (zahl2 + ueber);
        if (zwischenerg < 0){
            zwischenerg = 10 + zwischenerg;
            ueber = 1;
        }
        else
            ueber = 0;

        if (x < a.digits.size())
            a.digits[a.digits.size() - 1 - x] = (zwischenerg % 10) + '0';
        else{
            a.digits = to_string(zwischenerg % 10) + a.digits;
        }
        x++;
    }
    cleanup(a);
    return a;
}

BigInt operator-(const BigInt &a, const BigInt &b) {
    BigInt temp;
    temp = a;
    temp -= b;
    return temp;
}


// Vergleiche
bool operator<(const BigInt &a, const BigInt &b) {
    return (a.digits < b.digits);
}

bool operator<=(const BigInt &a, const BigInt &b) {
    return (a.digits <= b.digits);
}

bool operator>(const BigInt &a, const BigInt &b) {
    return (a.digits > b.digits);
}

bool operator>=(const BigInt &a, const BigInt &b) {
    return (a.digits >= b.digits);
}

bool operator==(const BigInt &a, const BigInt &b) {
    return (a.digits == b.digits);
}

bool operator!=(const BigInt &a, const BigInt &b) {
    return (a.digits != b.digits);
}


// Multiplikation und Division
BigInt &operator*=(BigInt &a, const BigInt &b) {
    int n, m, p;
    n = a.digits.size();
    m = b.digits.size();
    string ans(n + m, '0');
    for(int i = n - 1; i>=0; i--)
        for(int j = m - 1; j >= 0; j--){
            p = (a.digits[i] - '0') * (b.digits[j] - '0') + (ans[i + j + 1] - '0');
            ans[i+j+1] = p % 10 + '0';
            ans[i+j] += p / 10 ;
        }

    for(int i = 0; i < m + n; i++)
        if(ans[i] !='0'){
            a.digits = ans.substr(i);
            return a;
        }
    a.digits = "0";
    return a;
}

BigInt operator*(const BigInt &a, const BigInt &b) {
    BigInt temp;
    temp = a;
    temp*=b;
    return temp;
}
