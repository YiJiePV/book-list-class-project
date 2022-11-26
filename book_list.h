/**
 * Title:   Lab 4 - BookList Class Declaration
 *
 * Purpose: Declares the BookList class
 *          You may add methods, but you cannot change (or remove) any of the methods that are
 *          declared below.
 * Class:   CSC 2430 Winter 2022
 * Author:  Carlos R. Arias
 * Author:  Karena Qian
 */

#ifndef LINKED_LIST_A_BOOK_LIST_H
#define LINKED_LIST_A_BOOK_LIST_H

#include "book.h"



class BookList {
private:
    class Node{
    public:
        Node(const Book& book);
        Node();
        Book* book;
        Node* next;
    };
    Node* _head;
    size_t _size;
    BookList(const BookList& other);
    BookList& operator=(const BookList& rhs);
public:
    BookList();
    ~BookList();
    bool AddBook(const Book& book);
    bool AddBook(const string& name, const string& isbn, unsigned int year);
    bool AddBook(const string& name, unsigned int year);
    int IndexOf(const string& isbn)const;
    const Book* Get(unsigned int position)const;
    bool Remove(unsigned int position);
    string ToString()const;
    string ToJSON()const;
    istream& Read(istream& input);
    ostream& Write(ostream& output)const;
    void Clear();
    unsigned int Size()const;
};


#endif //LINKED_LIST_A_BOOK_LIST_H
