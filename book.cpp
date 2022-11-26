/**
 * Title:   Lab 4 - Book class implementation
 *
 * Purpose: Methods for creating, destroying, inputting, and outputting a Book object
 * Class:   CSC 2430 Winter 2022
 * Author:  Karena Qian
 */
#include "book.h"

#include <string>
#include <iostream>
#include <sstream>
#include <cctype>

using std::string;
using std::ostream;
using std::istream;
using std::stringstream;
using std::getline;
using std::isdigit;


/**
 * Constructor
 * Constructs a new Book with given name and year.
 * @param name for new Book
 * @param year for new Book
 */
Book::Book(const string &name, unsigned int year){
    _name = name;
    _year = year;
}
/**
 * Constructor
 * Constructs a new Book with given name, isbn, and year. However, it only sets
 * _isbn if isbn is valid.
 * @param name for new Book
 * @param isbn for new Book
 * @param year for new Book
 */
Book::Book(const string &name, const string &isbn, unsigned int year) {
    _name = name;
    _year = year;
    if(IsValidISBN(isbn)) {
        _isbn = isbn;
    }
}
/**
 * Copy Constructor
 * Constructs a deep copy of given Book.
 * @param rhs Book to copy
 */
Book::Book(const Book &rhs) {
    _name = rhs._name;
    _year = rhs._year;
    _isbn = rhs._isbn;
}
/**
 * ToString
 * Returns the Book as a string with the format "_name._isbn._year".
 * @return Book as a formatted string
 */
string Book::ToString() const{
    stringstream ss;
    ss << _name << "." << _isbn << "." << _year;
    return ss.str();
}
/**
 * ToJSON
 * Returns the Book as a string with the format "{"name":"_name", "isbn":"_isbn", "year":_year}".
 * @return Book as a formatted string
 */
string Book::ToJSON() const{
    stringstream ss;
    ss << "{\"name\":\"" << _name << "\", \"isbn\":\"" << _isbn << "\", \"year\":" << _year << "}";
    return ss.str();
}
/**
 * GetISBN
 * Getter/Accessor for data member _isbn. Returns isbn of Book.
 * @return data member _isbn
 */
string Book::GetISBN() const{
    return _isbn;
}
/**
 * GetName
 * Getter/Accessor for data member _name. Returns name of Book.
 * @return data member _name
 */
string Book::GetName() const{
    return _name;
}
/**
 * GetYear
 * Getter/Accessor for data member _year. Returns year of Book.
 * @return data member _year
 */
unsigned int Book::GetYear() const{
    return _year;
}
/**
 * Read
 * Reads in information about a Book from istream input and sets data members to
 * the respective information (only sets _isbn if inputted information is valid).
 * @param input to read from
 */
void Book::Read(istream &input) {
    string line;
    getline(input, line);
    if(!line.empty()) {
        _name = line.substr(0, line.find('.'));
        string year = line.substr(line.find_last_of('.') + 1, line.length() - line.find_last_of('.'));
        _year = stoi(year);
        string isbn = line.substr(line.find('.') + 1, line.find_last_of('.') - line.find_first_of('.') - 1);
        if (IsValidISBN(isbn)) {
            _isbn = isbn;
        } else {
            _isbn = "";
        }
    }
}
/**
 * Write
 * Writes Book to ostream output as a formatted string, same format as
 * the method ToString. Does not include an end-line.
 * @param output to write to
 */
void Book::Write(ostream &output) const{
    output << ToString();
}

/**
 * This function checks if the string passed as parameter, isbn, represents a valid
 * isbn. To implement this function you will need to do research on how to validate ISBN.
 * Both ISBN10 and ISBN13 are expected to work with this function.
 * @param isbn the isbn that is going to be checked
 * @return true if the isbn given is a valid isbn, false otherwise
 */
bool IsValidISBN(const string& isbn){
    int numValidChar;
    int sumDigits = 0;
    //Assuming valid ISBN13 input should be just a 13-digit string:
    //case ISBN13
    if(isbn.length() == 13){
        numValidChar = 13;
        for(int i = 0; i < isbn.length(); i++){
            if(isdigit(isbn[i])){ //just in case ISBN includes none-numerical chars by mistake
                if(numValidChar % 2 == 0){
                    int n = isbn[i] - '0';
                    sumDigits += (n * 3);
                }
                else{
                    int n = isbn[i] - '0';
                    sumDigits += (n * 1);
                }
                numValidChar--;
            }
        }
        if((sumDigits % 10) == 0){
            return true;
        }
    }
    //Assuming valid ISBN10 input should be just either a 10-digit string
    // or a 9 digit string with an X at the end:
    //case ISBN10
    else if(isbn.length() == 10){
        numValidChar = 10;
        for(int i = 0; i < isbn.length(); i++){
            if(isdigit(isbn[i])){ //in case non-digit chars are mistakenly added
                int n = isbn[i] - '0';
                sumDigits += (n * numValidChar);
                numValidChar--;
            }
            //if ISBN includes the X char
            else if(isbn[i] == 'X'){
                sumDigits += (10 * numValidChar);
                numValidChar--;
            }
        }
        if((sumDigits % 11) == 0){
            return true;
        }
    }
    else{
        return false;
    }
    return false;
}


