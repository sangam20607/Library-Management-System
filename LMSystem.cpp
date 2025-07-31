#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Book {
    int id;
    string title;
    string author;
};

void addBook() {
    ofstream file("library.txt", ios::app);
    Book book;
    cout << "\nEnter Book ID: ";
    cin >> book.id;
    cin.ignore();
    cout << "Enter Book Title: ";
    getline(cin, book.title);
    cout << "Enter Author Name: ";
    getline(cin, book.author);

    file << book.id << "," << book.title << "," << book.author << endl;
    file.close();
    cout << "✅ Book added successfully!\n";
}

void displayBooks() {
    ifstream file("library.txt");
    Book book;
    string line;

    cout << "\n📚 All Books:\n";
    while (getline(file, line)) {
        size_t pos1 = line.find(",");
        size_t pos2 = line.rfind(",");

        book.id = stoi(line.substr(0, pos1));
        book.title = line.substr(pos1 + 1, pos2 - pos1 - 1);
        book.author = line.substr(pos2 + 1);

        cout << "ID: " << book.id << " | Title: " << book.title << " | Author: " << book.author << endl;
    }
    file.close();
}

void searchBook() {
    ifstream file("library.txt");
    Book book;
    string line;
    int searchId, found = 0;

    cout << "\nEnter Book ID to search: ";
    cin >> searchId;

    while (getline(file, line)) {
        size_t pos1 = line.find(",");
        size_t pos2 = line.rfind(",");

        book.id = stoi(line.substr(0, pos1));
        book.title = line.substr(pos1 + 1, pos2 - pos1 - 1);
        book.author = line.substr(pos2 + 1);

        if (book.id == searchId) {
            cout << "✅ Book Found: " << book.title << " by " << book.author << endl;
            found = 1;
            break;
        }
    }

    if (!found) {
        cout << "❌ Book not found!\n";
    }
    file.close();
}

void deleteBook() {
    ifstream file("library.txt");
    ofstream temp("temp.txt");
    Book book;
    string line;
    int deleteId;
    bool found = false;

    cout << "\nEnter Book ID to delete: ";
    cin >> deleteId;

    while (getline(file, line)) {
        size_t pos1 = line.find(",");
        size_t pos2 = line.rfind(",");

        book.id = stoi(line.substr(0, pos1));
        if (book.id != deleteId) {
            temp << line << endl;
        } else {
            found = true;
        }
    }

    file.close();
    temp.close();
    remove("library.txt");
    rename("temp.txt", "library.txt");

    if (found) {
        cout << "✅ Book deleted successfully!\n";
    } else {
        cout << "❌ Book ID not found!\n";
    }
}

int main() {
    int choice;

    do {
        cout << "\n=== 📚 Library Management System ===\n";
        cout << "1. Add Book\n2. Display All Books\n3. Search Book\n4. Delete Book\n5. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: deleteBook(); break;
            case 5: cout << "👋 Exiting..."; break;
            default: cout << "⚠️ Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}
