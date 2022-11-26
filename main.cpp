/**
 * Title:   Lab 4 - Test Script
 *
 * Purpose: This file contains the main function, it includes 70 tests on your code.
 *          DO NOT MODIFY THIS FILE!
 * Class:   CSC 2430 Winter 2022
 * Author:  Carlos R. Arias
 */

#include "book_list.h"
#include "book.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::stringstream;
using std::string;
using std::left;
using std::setw;
/*
    __   ___
   / /  / _ \
  / /_ | (_) |
 | '_ \ > _ <
 | (_) | (_) |
 \___/ \___/
 Total Tests. . . . . . . . . . . .
*/

void Test(bool condition, const char* message, unsigned int& passedTests);



int main() {
    unsigned int tests = 0;
    stringstream inputStream, outputStream;

    // Valid ISBN Tests
    cout << "- * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * " << endl;
    cout << "- * - * - *     ISBN TESTS      - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * " << endl;
    cout << endl;
    Test(IsValidISBN("9780306406157") == true, "Test Valid ISBN = 9780306406157", tests);
    Test(IsValidISBN("007462542X") == true, "Test Valid ISBN = 007462542X", tests);
    Test(IsValidISBN("0112112425")  == false, "Test Not-Valid ISBN = 0112112425", tests);
    Test(IsValidISBN("9386954214") == true, "Test Valid ISBN = 9386954214", tests);
    Test(IsValidISBN("9971502100") == true,  "Test Valid ISBN = 9971502100", tests);
    Test(IsValidISBN("9780131103627") == true,  "Test Valid ISBN = 9780131103627", tests);
    Test(IsValidISBN("0131103628") == true,  "Test Valid ISBN = 0131103628", tests);
    Test(IsValidISBN("9780131103621") == false, "Test Not-Valid ISBN = 9780131103621", tests);
    Test(IsValidISBN("0131103608") == false,  "Test Not-Valid ISBN = 0131103608", tests);
    Test(IsValidISBN("0857861018") == true,  "Test Valid ISBN = 0857861018", tests);
    Test(IsValidISBN("9780382007354") == true,  "Test Valid ISBN = 9780382007354", tests);
    Test(IsValidISBN("0382007352") == true,  "Test Valid ISBN = 0382007352", tests);
    Test(IsValidISBN("9780825432286") == true,  "Test Valid ISBN = 9780825432286", tests);
    Test(IsValidISBN("0825432286") == true,  "Test Valid ISBN = 0825432286", tests);
    Test(IsValidISBN("080442957X") == true,  "Test Valid ISBN = 080442957X", tests);
    Test(IsValidISBN("080442157X") == false,  "Test Not-Valid ISBN = 080442157X", tests);
    Test(IsValidISBN("") == false,  "Test Not-Valid ISBN = \"\"", tests);


    // Book Tests
    Book* book = nullptr;
    book = new Book("My Book", 1970);
    cout << endl;
    cout << "- * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * " << endl;
    cout << "- * - * - *     Book TESTS      - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * " << endl;
    cout << endl;
    Test(book->ToString() == "My Book..1970", "Book::ToString()", tests);
    Test(book->ToJSON() == "{\"name\":\"My Book\", \"isbn\":\"\", \"year\":1970}", "Book::ToJSON", tests);
    Test(book->GetISBN() == "", "Book::GetISBN()", tests);
    Test(book->GetName() == "My Book", "Book::GetName()", tests);
    Test(book->GetYear() == 1970, "Book::GetYear()", tests);
    book->Write(outputStream);
    Test(outputStream.str() == "My Book..1970", "Book::Write()", tests);
    inputStream.str("Your Book..2000");
    book->Read(inputStream);
    Test(book->ToString() == "Your Book..2000", "Book::Read()", tests);
    delete book;
    outputStream.str("");
    inputStream.str("");

    book = new Book("Moby Dick", "9781987478105", 2018);
    Test(book->ToString() == "Moby Dick.9781987478105.2018", "Book::ToString()", tests);
    Test(book->ToJSON() == "{\"name\":\"Moby Dick\", \"isbn\":\"9781987478105\", \"year\":2018}", "Book::ToJSON", tests);
    Test(book->GetISBN() == "9781987478105", "Book::GetISBN()", tests);
    Test(book->GetName() == "Moby Dick", "Book::GetName()", tests);
    Test(book->GetYear() == 2018, "Book::GetYear()", tests);
    book->Write(outputStream);
    Test(outputStream.str() == "Moby Dick.9781987478105.2018", "Book::Write()", tests);
    delete book;
    outputStream.str("");
    inputStream.str("");

    // Finished Book tests . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .



    // BookList tests

    BookList list;
    cout << endl;
    cout << "- * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * " << endl;
    cout << "- * - * - *     BookList TESTS      - * - * - * - * - * - * - * - * - * - * - * - * - * - * " << endl;
    cout << endl;
    Test(list.ToJSON() == "[]", "BookList::ToJSON()", tests);
    Test(list.ToString()== "[]", "BookList::ToString()", tests);
    Test(list.Size() == 0, "BookList::Size()", tests);
    Test(list.AddBook("Algorithms and more", 2015), "BookList::Add(...) returned true", tests);
    Test(list.Size() == 1, "Size increment to 1", tests);
    Test(list.AddBook("A Random Book", "007462542X", 1980), "BookList::Add(...) returned true", tests);
    Test(list.Size() == 2, "Size increment to 2", tests);

    list.Write(outputStream);
    Test(outputStream.str() == "A Random Book.007462542X.1980\nAlgorithms and more..2015\n", "BookList::Write()", tests);
    outputStream.str("");

    Test(list.AddBook(Book("Moby Dick", "9781494890261", 2015)), "BookList::Add(...) returned true", tests);
    Test(list.Size() == 3, "Size increment to 3", tests);

    Test(list.IndexOf("9781494890261") == 0, "BookList::IndexOf() test 1", tests);
    Test(list.IndexOf("007462542X") == 1, "BookList::IndexOf() test 2", tests);
    Test(list.IndexOf("") == 2, "BookList::IndexOf() test 3", tests);
    Test(list.IndexOf("9780306406157") == -1, "BookList::IndexOf() test 4", tests);

    Test(list.Get(0)->ToString() == "Moby Dick.9781494890261.2015", "BookList::Get() test 1", tests);
    Test(list.Get(1)->ToString() == "A Random Book.007462542X.1980", "BookList::Get() test 2", tests);
    Test(list.Get(2)->ToString() == "Algorithms and more..2015", "BookList::Get() test 3", tests);
    Test(list.Get(3) == nullptr, "BookList::Get() test 4", tests);

    Test(list.Remove(3) == false, "BookList::Remove() Invalid Position", tests);
    Test(list.Size() == 3, "BookList::Size() = 3, did not remove", tests);
    Test(list.Remove(1) == true, "BookList::Remove() Middle", tests);
    Test(list.Size() == 2, "BookList::Size() = 2, did remove", tests);
    Test(list.Remove(0) == true, "BookList::Remove() First", tests);
    Test(list.Size() == 1, "BookList::Size() = 1, did remove", tests);
    Test(list.Remove(0) == true, "BookList::Remove() Last and Only", tests);
    Test(list.Size() == 0, "BookList::Size() = 0, did remove", tests);

    list.AddBook("Book #1", 1990);
    list.AddBook("Book #2", 1993);
    list.AddBook("Book #4", 1994);
    Test(list.ToString() == "[Book #4..1994, Book #2..1993, Book #1..1990]", "BookList::ToString()", tests);
    Test(list.ToJSON() == "[{\"name\":\"Book #4\", \"isbn\":\"\", \"year\":1994}, {\"name\":\"Book #2\", \"isbn\":\"\", \"year\":1993}, {\"name\":\"Book #1\", \"isbn\":\"\", \"year\":1990}]", "BookList::ToJSON()", tests);
    list.Write(outputStream);
    Test(outputStream.str() ==  "Book #4..1994\n"
                                "Book #2..1993\n"
                                "Book #1..1990\n", "BookList::Write()", tests);

    outputStream.str("");
    list.Clear();
    Test(list.Size() == 0, "Empty list (size == 0) after BookList::Clear()", tests);
    Test(list.ToString() == "[]", "Empty list (ToString() == []) after BookList::Clear()", tests);
    Test(list.Get(0) == nullptr, "Empty list (Get(0) == nullptr) after BookList::Clear()", tests);

    // Need to check list.Read(inputStream)
    inputStream.clear();
    inputStream.str(
            "Holy Bible.9780340979655.2010\n"
            "Revelation.9780857861016.2010\n"
            "The New American Bible.9780382007354.1970\n"
            "How to Read the Bible Book by Book.9780310211181.2002\n"
            "The Bible.9780825432286.2004\n"
    );
    list.Read(inputStream);
    Test(list.Size() == 5, "After reading from istream BookList::Read()", tests);
    Test(list.ToString() == "[The Bible.9780825432286.2004, How to Read the Bible Book by Book.9780310211181.2002, The New American Bible.9780382007354.1970, Revelation.9780857861016.2010, Holy Bible.9780340979655.2010]", "ToString after reading from stream BookList::Read()", tests);
    Test(list.Get(0)->GetISBN() == "9780825432286", "Check after reading from istream, element 0", tests);
    Test(list.Get(1)->GetISBN() == "9780310211181", "Check after reading from istream, element 1", tests);
    Test(list.Get(2)->GetISBN() == "9780382007354", "Check after reading from istream, element 2", tests);
    Test(list.Get(3)->GetISBN() == "9780857861016", "Check after reading from istream, element 3", tests);
    Test(list.Get(4)->GetISBN() == "9780340979655", "Check after reading from istream, element 4", tests);
    Test(list.Get(5) == nullptr, "No sixth element on list of 5 elements", tests);



    return 0;

}

void Test(bool condition, const char* message, unsigned int& passedTests){
    if (condition){
        cout << "+\tTEST PASSED (" << left << setw(55) << message << ") Total Passed: " << ++passedTests << endl;
    }else{
        cout << "-\tTEST FAILED (" << left << setw(55) << message << ") " << string(25, '*') << "   <----- Failed" << endl;
    }
}