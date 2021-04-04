#pragma once

#include "Book.h"
#include "CheckInOrOutResult.h"
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

class Inventory
{
private:
    vector<Book> Books;

public:
    void DisplayAllBooks();
    void DisplayCheckedOutBooks();
    int NumberOfBooks();
    Book GetBookByIndex(int index);
    void AddBook(Book book);
    void LoadBooks();
    void RemoveBook(string title);
    int FindBookByTitle(string title);
    CheckInOrOutResult CheckInOrOutBook(string title, bool checkOut);
};

void Inventory ::DisplayAllBooks()
{

    // cout << "\nID\tTitle\tAuthor\tStatus" << endl;
    int col_width = 20;
    cout << left;
    cout << setw(col_width) << "ID" << setw(col_width) << "Title" << setw(col_width) << "Author" << setw(col_width) << "Status" << endl;
    cout << "----------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < NumberOfBooks(); i++)
    {
        string available = "";
        if (GetBookByIndex(i).IscheckedOut())
            available = "Checked Out";
        else
            available = "Available";
        Books[i].DisplayBook();
        cout << setw(col_width) << available << endl;
    }
    cout << endl;
}

void Inventory ::DisplayCheckedOutBooks()
{
    int col_width = 20;
    cout << left;
    cout << setw(col_width) << "ID" << setw(col_width) << "Title" << setw(col_width) << "Author" << endl;

    cout << "----------------------------------------------------------------------------" << endl;
    for (int i = 0; i < NumberOfBooks(); i++)
    {
        if (GetBookByIndex(i).IscheckedOut())
        {
            Books[i].DisplayBook();
            cout << endl;
        }
    }
    cout << endl;
}

int Inventory ::NumberOfBooks()
{
    return Inventory ::Books.size();
}

Book Inventory ::GetBookByIndex(int index)
{
    return Inventory ::Books[index];
}

void Inventory ::AddBook(Book book)
{
    int nextBookId = 0;
    if (Books.size() > 0)
        nextBookId = Books.back().Id + 1;

    book.Id = nextBookId;

    Inventory ::Books.push_back(book);
    ofstream oFile("books.txt", ios_base ::app);
    oFile << book.GetBookFileData() << endl;
    oFile.close();
}

void Inventory ::LoadBooks()
{
    Books.clear();
    ifstream inFile("books.txt");

    string bookData[4];
    //bookData[0] = Id
    //bookData[1] = Title
    //bookData[2] = Author
    //bookData[3] = Checked Out

    string bookLine;
    while (getline(inFile, bookLine))
    {

        size_t nextIndex = bookLine.find('|');
        bookData[0] = bookLine.substr(0, nextIndex);

        size_t prevIndex = nextIndex;
        nextIndex = bookLine.find('|', prevIndex + 1);
        bookData[1] = bookLine.substr(prevIndex + 1, nextIndex - (prevIndex + 1));

        prevIndex = nextIndex;
        nextIndex = bookLine.find('|', prevIndex + 1);
        bookData[2] = bookLine.substr(prevIndex + 1, nextIndex - (prevIndex + 1));

        prevIndex = nextIndex;
        nextIndex = bookLine.find('|', prevIndex + 1);
        bookData[3] = bookLine.substr(prevIndex + 1, nextIndex - (prevIndex + 1));

        Book loadedBook(bookData[1], bookData[2]);
        loadedBook.Id = stoi(bookData[0]);
        loadedBook.CheckInOrOut(stoi(bookData[3]));

        Books.push_back(loadedBook);
    }
}

void Inventory ::RemoveBook(string title)
{
    vector<Book>::iterator it = find(Inventory::Books.begin(), Inventory::Books.end(), Book(title, ""));
    if (it != Inventory::Books.end())
    {
        Inventory ::Books.erase(it);
    }
    ofstream oFile("books.txt");
    for (int i = 0; i < Books.size(); i++)
    {
        oFile << Books[i].GetBookFileData() << endl;
    }
}

int Inventory ::FindBookByTitle(string title)
{
    vector<Book>::iterator it = find(Inventory::Books.begin(), Inventory::Books.end(), Book(title, ""));
    if (it == Inventory::Books.end())
    {
        return -1;
    }
    int index = it - Inventory ::Books.begin();
    return index;
}

CheckInOrOutResult Inventory ::CheckInOrOutBook(string title, bool checkOut)
{
    int foundBookIndex = Inventory::FindBookByTitle(title);
    if (foundBookIndex < 0)
    {
        return CheckInOrOutResult ::BookNotFound;
    }
    else if (checkOut == Books[foundBookIndex].IscheckedOut())
    {
        if (checkOut)
        {
            return CheckInOrOutResult ::AlreadyCheckedOut;
        }
        else
        {
            return CheckInOrOutResult ::AlreadyCheckedIn;
        }
    }

    Books[foundBookIndex].CheckInOrOut(checkOut);

    ofstream oFile("books.txt");
    for (int i = 0; i < Books.size(); i++)
    {
        oFile << Books[i].GetBookFileData() << endl;
    }

    return CheckInOrOutResult ::Success;
}
