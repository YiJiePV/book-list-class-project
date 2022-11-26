/**
 * Title:   Lab 4 - Menu class and BookList class Implementation: extracredit.cpp
 *
 * Purpose: Extracredit.cpp implements the classes Book, BookList, Menu and Menu_Element to construct a menu program
 * for creating, manipulating, and analyzing a BookList.
 * Class:   CSC 2430 Winter 2022
 * Author:  Karena Qian
 */
#include <iostream>
#include <iomanip>
#include "menu.h"
#include "book_list.h"

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::fixed;
using std::setprecision;
using std::getline;

int main(){
    int userInput; //for menu choice user input
    BookList list; //the BookList
    string isbn, line; //for ISBN user input and book info input respectively
    int index; //for book index user input
    Book neo("", 0); //for adding a Book

    //create the BookList menu
    Menu bookMenu(6);
    bookMenu.SetTitle("Book Store Menu");
    bookMenu.SetInputType(INT);
    bookMenu.SetErrorMessage("- - > Unrecognized Input < - -");
    bookMenu.SetInvalidOption("- - > Please Input One of the Given Choices < - -");
    bookMenu.AddMenuOption(0, "1", "Add a Book");
    bookMenu.AddMenuOption(1, "2", "Find a Book");
    bookMenu.AddMenuOption(2, "3", "Get a Book");
    bookMenu.AddMenuOption(3, "4", "List all Books");
    bookMenu.AddMenuOption(4, "5", "Remove one Book");
    bookMenu.AddMenuOption(5, "6", "Remove all Books");


    //The Main Program
    while ((userInput = bookMenu.Run()) != EXIT){
        switch (userInput) {
            //Error for incorrect integer from user input
            case INVALID_INPUT:
                break;
                //Error for incorrect type of input from user
            case INPUT_ERROR:
                break;
            //Option 1: Add a Book
            case 0:
                //Assuming the user will always input the book as name.ISBN.year .......
                cout << "\nPlease enter the book name, ISBN, and publishing year in the following format: name.ISBN.year\n";
                getline(cin, line);
                neo.Read(cin);
                list.AddBook(neo);
                if(!IsValidISBN(neo.GetISBN())){
                    cout << "\nALERT: ISBN is found unavailable/invalid." << endl;
                }
                cout << "\nBook \"" << neo.GetName() << "\" successfully added." << endl << endl;
                break;
            //Option 2: Find a Book
            case 1:
                cout << "\nPlease input the isbn of desired book (n/a if ISBN is not available/invalid): ";
                cin >> isbn;
                if(isbn == "n/a"){
                    index = list.IndexOf("");
                }
                else{
                    index = list.IndexOf(isbn);
                }
                if(index != -1){
                    cout << "\nIn regular format: ";
                    list.Get(index)->Write(cout);
                    cout << "\nIn JSON: " << list.Get(index)->ToJSON() << endl << endl;
                }
                else{
                    cout << "\nBook with ISBN \"" << isbn << "\" is not found" << endl << endl;
                }
                break;
            //Option 3: Get a Book
            case 2:
                cout << "\nPlease enter the index of desired book: ";
                cin >> index;
                if(list.Get(index) != nullptr){
                    cout << "\nIn regular format: ";
                    list.Get(index)->Write(cout);
                    cout << "\nIn JSON: " << list.Get(index)->ToJSON() << endl << endl;
                }
                else{
                    cout << "\nInvalid position" << endl << endl;
                }
                break;
            //Option 4: List all Books
            case 3:
                cout << "\nYour Current Book List:" << endl;
                list.Write(cout);
                cout << endl;
                break;
            //Option 5: Remove one Book
            case 4:
                cout << "\nPlease input the isbn of desired book to remove (n/a if ISBN is not available/invalid): ";
                cin >> isbn;
                if(isbn == "n/a"){
                    index = list.IndexOf("");
                }
                else{
                    index = list.IndexOf(isbn);
                }
                if(index != -1){
                    cout << "Removing book \"" << list.Get(index)->GetName() << "\" from the list...." << endl << endl;
                    list.Remove(index);
                }
                else{
                    cout << "Book is not found. Unable to remove." << endl << endl;
                }
                break;
            //Option 6: Remove all Books
            case 5:
                cout << "\nEmptying the list...." << endl << endl;
                list.Clear();
                break;
        }
    }
    cout << "Thank you for visiting!" << endl << endl;
    return 0;
}