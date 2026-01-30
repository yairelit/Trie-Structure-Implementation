// Submitter name: Yair Elitzur
// Submitter ID: 314699778

#include <iostream>
#include <string>
#include <limits>
#include "Book.h"

using namespace std;

int main() {
    string path;
    cout << "Enter the book's path: ";
    // הנחה: שם הקובץ מוזן ללא רווחים או שמטפלים בזה. בדוגמה שלך: hamlet.txt
    cin >> path;

    try {
        Book book(path);

        char action;
        while (true) {
            cout << "Enter 's' to search, 'c' to censor or 'e' to quit: ";
            cin >> action;

            if (action == 'e') {
                break;
            }

            // ניקוי חוצץ הקלט (Buffer) כדי ש-getline יעבוד תקין
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (action == 's') {
                cout << "Enter prefix: " << endl; // שים לב ל-endl שמוסיף ירידת שורה כמו בפלט
                string query;
                getline(cin, query);
                book.searchAndPrint(query);
            }
            else if (action == 'c') {
                cout << "Enter search term to censor: " << endl;
                string query;
                getline(cin, query);
                book.censorQuery(query);
            }
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}