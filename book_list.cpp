/**
 * Title:   Lab 4 - BookList class implementation.
 *
 * Purpose: Methods for creating, destroying, and modifying BookList objects
 * Class:   CSC 2430 Winter 2022
 * Author:  Karena Qian
 */
#include "book_list.h"

#include <sstream>
#include <string>
#include <iostream>
using std::string;
using std::stringstream;
using std::ostream;
using std::istream;
using std::endl;
using std::getline;

/**
 * Copy Constructor of the Book List
 * You don't need to implement this method.
 * @param other the original BookList that is going to be copied.
 */
BookList::BookList(const BookList &other) {
}
/**
 * Copy Assignment operator of the Book List
 * You don't need to implement this method.
 * @param rhs The right hand side operand of the assignment.
 * @return a reference to the caller object
 */
BookList &BookList::operator=(const BookList &rhs) {
    return *this;
}
/**
 * Default constructor
 * Constructs an empty BookList
 */
BookList::BookList(): _head(nullptr){
    _size = 0;
}
/**
 * Destructor
 * Deletes the whole list and frees all dynamically allocated memory
 */
BookList::~BookList() {
    if(_head != nullptr) {
        Node *temp = _head;
        for(int i = 0; i < _size; i++) {
            _head = temp->next;
            temp->next = nullptr;
            delete temp->book;
            delete temp;
            temp = _head;
        }
    }
    _size = 0;
}
/**
 * AddBook
 * Adds a new Node containing the given Book object to the front of the BookList.
 * @param book to be added
 * @return always returns true
 */
bool BookList::AddBook(const Book &book) {
    if(_head == nullptr){
        _head = new Node(book);
    }
    else{
        Node* neo = new Node(book);
        neo->next = _head;
        _head = neo;
    }
    _size++;
    return true;
}
/**
 * AddBook
 * Constructs and adds a new Node containing a new Book object to the front of the BookList using given information.
 * @param name for new Book
 * @param isbn for new Book
 * @param year for new Book
 * @return always returns true
 */
bool BookList::AddBook(const string &name, const string &isbn, unsigned int year) {
    Book neoBook(name, isbn, year);
    AddBook(neoBook);
    return true;
}
/**
 * AddBook
 * Constructs and adds a new Node containing a new Book object to the front of the BookList using given information.
 * @param name for new Book
 * @param year for new Book
 * @return always returns true
 */
bool BookList::AddBook(const string &name, unsigned int year) {
    Book neoBook(name, year);
    AddBook(neoBook);
    return true;
}
/**
 * IndexOf
 * Iterates through the BookList and returns the position of the Node containing the Book object
 * containing the given isbn if found.
 * If not found, returns -1.
 * @param isbn the isbn of the book the user is searching for
 * @return position of the book in the list if found, -1 otherwise
 */
int BookList::IndexOf(const string &isbn) const {
    Node* temp = _head;
    for(int i = 0; i < _size; i++){
        if(temp->book->GetISBN() == isbn){
            return i;
        }
        temp = temp->next;
    }
    return -1;
}
/**
 * Get
 * Iterates and returns the Book object in the Node at given position in the BookList.
 * If position is invalid or the BookList is empty, returns nullptr.
 * @param position of Book in BookList
 * @return the Book object at given position, or nullptr if position is invalid or the BookList is empty
 */
const Book *BookList::Get(unsigned int position) const {
    if(_head == nullptr){
        return nullptr;
    }
    Node* temp = _head;
    if(position >= _size || position < 0){
        return nullptr;
    }
    for(int i = 0; i < position; i++){
        temp = temp->next;
    }
    return temp->book;
}
/**
 * Remove
 * Gets and deletes the Node at given position. Returns true if desired Node is successfully removed from the list,
 * but returns false if position is invalid or the BookList is empty.
 * @param position of Book to be removed
 * @return true if Book at given position is successfully removed, false otherwise
 */
bool BookList::Remove(unsigned int position) {
    if(_head == nullptr){
        return false;
    }
    if(position >= _size || position < 0){
        return false;
    }
    Node* temp = _head;
    if(position == 0){
        _head = temp->next;
        temp->next = nullptr;
        delete temp->book;
        delete temp;
        _size--;
        return true;
    }
    for(int i = 0; i < position - 1; i++){
        temp = temp->next;
    }
    Node* toDelete = temp->next;
    temp->next = temp->next->next;
    toDelete->next = nullptr;
    delete toDelete->book;
    delete toDelete;
    _size--;
    return true;
}
/**
 * ToString
 * Returns the whole BookList as a string with the below format:
 * Format for string to be returned:
 * [Book1Name.Book1ISBN.Book1Year, Book2Name.Book2ISBN, Book2Year, ...]
 * @return BookList as a formatted string
 */
string BookList::ToString() const {
    stringstream ss;
    ss << "[";
    if(_head != nullptr) {
        Node *temp = _head;
        for (int i = 0; i < _size - 1; i++) {
            ss << temp->book->ToString() << ", ";
            temp = temp->next;
        }
        ss << temp->book->ToString();
    }
    ss << "]";
    string result = ss.str();
    return ss.str();
}
/**
 * Read
 * Reads from an input stream, each book will be stored in the stream in a single line.
 * @param input stream to read from
 * @return input to allow stream chaining
 */
istream &BookList::Read(istream &input) {
    Clear();
    string line;
    while(!input.eof()){
        Book neoBook("", 0);
        neoBook.Read(input);
        if(!neoBook.GetName().empty()){
            AddBook(neoBook);
        }
    }
    return input;
}
/**
 * Write
 * Writes to the output stream, each book should be stored in a single line.
 * @param output
 * @return output to allow stream chaining
 */
ostream &BookList::Write(ostream &output) const {
    if(_head != nullptr) {
        Node *temp = _head;
        for (int i = 0; i < _size; i++) {
            temp->book->Write(output);
            output << endl;
            temp = temp->next;
        }
    }
    else{
        output << endl;
    }
    return output;
}
/**
 * Clear
 * Deletes the whole BookList and resets it to an empty list
 */
void BookList::Clear() {
    BookList::~BookList();
    BookList();
}
/**
 * ToJSON
 * Returns the whole BookList as a string with the below format:
 * Example:
 * [{"name":"book one", "isbn":"1234567890", "year":1900}, {"name":"book two", "isbn":"0987654321", "year":1901}]
 * @return the BookList as a formatted string
 */
string BookList::ToJSON() const {
    stringstream ss;
    ss << "[";
    if(_head != nullptr) {
        Node *temp = _head;
        for (int i = 0; i < _size - 1; i++) {
            ss << temp->book->ToJSON() << ", ";
            temp = temp->next;
        }
        ss << temp->book->ToJSON();
    }
    ss << "]";
    return ss.str();
}
/**
 * Size
 * Getter/Accessor for data member _size. Returns the size of the BookList.
 * @return data member _size
 */
unsigned int BookList::Size() const {
    return _size;
}
/**
 * Node constructor
 * Constructs a new Node object with the given Book object
 * @param book to insert into new Node
 */
BookList::Node::Node(const Book &book) {
    this->book = new Book(book);
    next = nullptr;
}

/**
 * Node default constructor
 * Constructs an empty Node object
 */
BookList::Node::Node() {
    book = nullptr;
    next = nullptr;
}
