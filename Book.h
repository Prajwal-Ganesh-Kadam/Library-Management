#pragma once

#include <iostream>
#include <string>
#include<iomanip>
using namespace std;

class Book
{
private:
    string Title;
    string Author;
    bool CheckedOut;

public:
    int Id;
    Book();
    Book(string title, string author);

    void SetBookId(int id);
    void CheckInOrOut(bool checkOut);
    void DisplayBook();
    bool IscheckedOut();
    string GetBookFileData();

    bool operator==(const Book &book) const
    {
        if (Title.compare(book.Title) == 0)
            return true;
        else
            return false;
    }
};

Book ::Book() {}

Book ::Book(string title, string author)
{
    Book ::Title = title;
    Book ::Author = author;
    Book ::CheckedOut = false;
}

void Book ::CheckInOrOut(bool checkOut)
{
    CheckedOut = checkOut;
}

void Book ::DisplayBook()
{
    int col_width = 20;
    cout<<left;
    cout<< setw(col_width) << Id << setw(col_width)<<Title <<setw(col_width) << Author;
}

bool Book :: IscheckedOut()
{
    return CheckedOut;
}

string Book ::GetBookFileData()
{
    return to_string(Id) + "|" + Title + "|" + Author + "|" + (CheckedOut ? "1" : "0");
}