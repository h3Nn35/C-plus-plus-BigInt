#ifndef BIGINT_BIGINT_H
#define BIGINT_BIGINT_H

#include <iostream>

using namespace std;

class BigInt{
    private:
        string digits;

    public:

        // Konstruktoren
        BigInt(int n = 0);
        BigInt(unsigned long long);
        BigInt(string &);
        BigInt(char *);
        BigInt(BigInt &);

        // Hilfsfunktionen
        friend bool Null(const BigInt &other);
        friend int Length(const BigInt &);
        int operator[](const int)const;
        friend void cleanup(BigInt &);


        /***********************    OPERATOREN    ***********************/

        // Lesen und Schreiben
        friend ostream &operator<<(ostream &,const BigInt &);
        friend istream &operator>>(istream &, BigInt &);

        // Direktzuweisungen
        BigInt &operator=(const BigInt &);
        BigInt &operator=(const string &);
        BigInt &operator=(const unsigned long long&);
        BigInt &operator=(const int &);

        // Inkrementieren / Decrementieren
        BigInt operator++(int);
        BigInt &operator++();
        BigInt operator--(int temp);
        BigInt &operator--();

        // Addition und Subtraktion
        friend BigInt &operator+=(BigInt &, const BigInt &);
        friend BigInt operator+(const BigInt &, const BigInt &);
        friend BigInt &operator-=(BigInt &, const BigInt &);
        friend BigInt operator-(const BigInt &, const BigInt &);

        // Vergleiche
        friend bool operator<(const BigInt &, const BigInt &);
        friend bool operator<=(const BigInt &, const BigInt &);
        friend bool operator>(const BigInt &, const BigInt &);
        friend bool operator>=(const BigInt &, const BigInt &);
        friend bool operator==(const BigInt &, const BigInt &);
        friend bool operator!=(const BigInt &, const BigInt &);

        // Multiplikation und Division
        friend BigInt &operator*=(BigInt &, const BigInt &);
        friend BigInt operator*(const BigInt &, const BigInt &);
};

#endif //BIGINT_BIGINT_H
