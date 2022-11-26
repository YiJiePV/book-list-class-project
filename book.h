/**
 * Title:   Lab 4 - Book Class Declaration
 *
 * Purpose: Declares the class Book
 *          You may add methods additional methods
 *          You must declare and define the methods listed/described below
 * Class:   CSC 2430 Winter 2022
 * Author:  Carlos R. Arias
 * Author:  Karena Qian
 */
#ifndef LINKED_LIST_A_BOOK_H
#define LINKED_LIST_A_BOOK_H

#include <string>
#include <iostream>
using std::string;
using std::istream;
using std::ostream;

class Book {
private:
    string _name;
    string _isbn;
    unsigned int _year;
public:
    // Constructor that takes in name and year
    Book(const string &name, unsigned int year);
    // Constructor that takes in name, isbn and year
    Book(const string &name, const string &isbn, unsigned int year);
    // Copy constructor
    Book(const Book &rhs);
    // ToString method
    string ToString() const;
    // ToJSON method
    string ToJSON() const;
    // ISBN getter/accessor method
    string GetISBN() const;
    // Name getter/accessor method
    string GetName() const;
    // Year getter/accessor method
    unsigned int GetYear() const;
    // Read from istream method
    void Read(istream &input);
    // Write to ostream method
    void Write(ostream &output) const;
};

 bool IsValidISBN(const string& isbn);

#endif //LINKED_LIST_A_BOOK_H
