#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

class Book
{
public:
    int bookID;
    string title;
    string author;
    bool issued;

    Book()
    {
        bookID = 0;
        title = "";
        author = "";
        issued = false;
    }
};

class Member
{
public:
    int memberID;
    string memberName;

    Member()
    {
        memberID = 0;
        memberName = "";
    }
};

class Library
{
private:
    Book books[100];
    Member members[100];

    int bookCount;
    int memberCount;

public:

    Library()
    {
        bookCount = 0;
        memberCount = 0;

        loadBooks();
        loadMembers();
    }

    void loadBooks()
    {
        ifstream file("books.txt");

        if (!file)
            return;

        bookCount = 0;

        while (bookCount < 100 &&
               file >> books[bookCount].bookID)
        {
            file.ignore(numeric_limits<streamsize>::max(), '\n');

            getline(file, books[bookCount].title);
            getline(file, books[bookCount].author);

            file >> books[bookCount].issued;
            file.ignore(numeric_limits<streamsize>::max(), '\n');

            bookCount++;
        }

        file.close();
    }

    void loadMembers()
    {
        ifstream file("members.txt");

        if (!file)
            return;

        memberCount = 0;

        while (memberCount < 100 &&
               file >> members[memberCount].memberID)
        {
            file.ignore(numeric_limits<streamsize>::max(), '\n');

            getline(file, members[memberCount].memberName);

            memberCount++;
        }

        file.close();
    }

    void saveBooks()
    {
        ofstream file("books.txt");

        for (int i = 0; i < bookCount; i++)
        {
            file << books[i].bookID << endl;
            file << books[i].title << endl;
            file << books[i].author << endl;
            file << books[i].issued << endl;
        }

        file.close();
    }

    void saveMembers()
    {
        ofstream file("members.txt");

        for (int i = 0; i < memberCount; i++)
        {
            file << members[i].memberID << endl;
            file << members[i].memberName << endl;
        }

        file.close();
    }

    void addBook()
    {
        if (bookCount >= 100)
        {
            cout << "Library is full!\n";
            return;
        }

        Book b;

        cout << "\nEnter Book ID: ";
        cin >> b.bookID;

        for (int i = 0; i < bookCount; i++)
        {
            if (books[i].bookID == b.bookID)
            {
                cout << "Book ID already exists!\n";
                return;
            }
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Book Title: ";
        getline(cin, b.title);

        cout << "Enter Author Name: ";
        getline(cin, b.author);

        b.issued = false;

        books[bookCount] = b;
        bookCount++;

        saveBooks();

        cout << "\nBook Added Successfully!\n";
    }

    void displayBooks()
    {
        if (bookCount == 0)
        {
            cout << "\nNo Books Available!\n";
            return;
        }

        cout << "\n========== BOOK DETAILS ==========\n";

        for (int i = 0; i < bookCount; i++)
        {
            cout << "\nBook ID: " << books[i].bookID;
            cout << "\nTitle: " << books[i].title;
            cout << "\nAuthor: " << books[i].author;
            cout << "\nStatus: "
                 << (books[i].issued ? "Issued" : "Available");
            cout << "\n----------------------------------\n";
        }
    }

    void searchByTitle()
    {
        string searchTitle;
        bool found = false;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nEnter Book Title: ";
        getline(cin, searchTitle);

        for (int i = 0; i < bookCount; i++)
        {
            if (books[i].title == searchTitle)
            {
                cout << "\nBook Found!\n";
                cout << "Book ID: " << books[i].bookID << endl;
                cout << "Title: " << books[i].title << endl;
                cout << "Author: " << books[i].author << endl;

                found = true;
            }
        }

        if (!found)
            cout << "\nBook Not Found!\n";
    }

    void searchByAuthor()
    {
        string searchAuthor;
        bool found = false;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nEnter Author Name: ";
        getline(cin, searchAuthor);

        for (int i = 0; i < bookCount; i++)
        {
            if (books[i].author == searchAuthor)
            {
                cout << "\nBook Found!\n";
                cout << "Book ID: " << books[i].bookID << endl;
                cout << "Title: " << books[i].title << endl;
                cout << "Author: " << books[i].author << endl;

                found = true;
            }
        }

        if (!found)
            cout << "\nNo Books Found for This Author!\n";
    }

    void registerMember()
    {
        if (memberCount >= 100)
        {
            cout << "Member limit reached!\n";
            return;
        }

        Member m;

        cout << "\nEnter Member ID: ";
        cin >> m.memberID;

        for (int i = 0; i < memberCount; i++)
        {
            if (members[i].memberID == m.memberID)
            {
                cout << "Member ID already exists!\n";
                return;
            }
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Member Name: ";
        getline(cin, m.memberName);

        members[memberCount] = m;
        memberCount++;

        saveMembers();

        cout << "\nMember Registered Successfully!\n";
    }

    void displayMembers()
    {
        if (memberCount == 0)
        {
            cout << "\nNo Members Registered!\n";
            return;
        }

        cout << "\n========== MEMBER DETAILS ==========\n";

        for (int i = 0; i < memberCount; i++)
        {
            cout << "\nMember ID: " << members[i].memberID;
            cout << "\nMember Name: " << members[i].memberName;
            cout << "\n------------------------------------\n";
        }
    }

    void issueBook()
    {
        int id;

        cout << "\nEnter Book ID: ";
        cin >> id;

        bool memberFound = false;

        for (int i = 0; i < memberCount; i++)
        {
            if (members[i].memberID == id)
            {
                memberFound = true;
                break;
            }
        }

        if (!memberFound)
        {
            cout << "Register the member first!\n";
            return;
        }

        int bookID;

        cout << "Enter Book ID to Issue: ";
        cin >> bookID;

        for (int i = 0; i < bookCount; i++)
        {
            if (books[i].bookID == bookID)
            {
                if (books[i].issued)
                {
                    cout << "Book Already Issued!\n";
                }
                else
                {
                    books[i].issued = true;
                    saveBooks();

                    cout << "\nBook Issued Successfully!\n";
                }

                return;
            }
        }

        cout << "Book Not Found!\n";
    }

    void returnBook()
    {
        int id;

        cout << "\nEnter Book ID to Return: ";
        cin >> id;

        for (int i = 0; i < bookCount; i++)
        {
            if (books[i].bookID == id)
            {
                if (books[i].issued)
                {
                    books[i].issued = false;
                    saveBooks();

                    cout << "\nBook Returned Successfully!\n";
                }
                else
                {
                    cout << "This Book Was Not Issued!\n";
                }

                return;
            }
        }

        cout << "Book Not Found!\n";
    }
};

int main()
{
    Library library;
    int choice;

    do
    {
        cout << "\n====================================\n";
        cout << "       LIBRARY MANAGEMENT SYSTEM    \n";
        cout << "====================================\n";

        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book by Title\n";
        cout << "4. Search Book by Author\n";
        cout << "5. Register Member\n";
        cout << "6. Display Members\n";
        cout << "7. Issue Book\n";
        cout << "8. Return Book\n";
        cout << "9. Exit\n";

        cout << "\nEnter Your Choice: ";

        if (!(cin >> choice))
        {
            cout << "Invalid Input!\n";
            break;
        }

        switch (choice)
        {
            case 1:
                library.addBook();
                break;

            case 2:
                library.displayBooks();
                break;

            case 3:
                library.searchByTitle();
                break;

            case 4:
                library.searchByAuthor();
                break;

            case 5:
                library.registerMember();
                break;

            case 6:
                library.displayMembers();
                break;

            case 7:
                library.issueBook();
                break;

            case 8:
                library.returnBook();
                break;

            case 9:
                cout << "\nThank You for Using Library Management System!\n";
                break;

            default:
                cout << "\nInvalid Choice! Try Again.\n";
        }

    } while (choice != 9);

    return 0;
}