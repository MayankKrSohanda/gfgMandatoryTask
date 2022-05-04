//A Code which I wrote for understanding getters and setters

#include <iostream>
#include <map>
using namespace std;

class Book {
public:
    string title;
    int pageCount;
    bool isCheckedOut;
    int dayCheckedOut = -1;

    Book(string bookTitle, int bookPageCount) {
        title = bookTitle;
        pageCount = bookPageCount;
        isCheckedOut = false;
    }

    string getTitle() {
        return title;
    }

    int getPageCount() {
        return pageCount;
    }

    int getdayCheckedOut() {
        return dayCheckedOut;
    }

    bool getIsCheckedOut() {
        return isCheckedOut;
    }

    void setIsCheckedOut(bool newIsCheckedOut, int currentdayCheckedOut) {
        isCheckedOut = newIsCheckedOut;
        setdayCheckedOut(currentdayCheckedOut);
    }

private:
    void setdayCheckedOut(int day) {
        dayCheckedOut = day;
    }
};

class LibraryCatalogue {
public:
    map<string, Book*> bookCollection;
    int currentDay = 0;
    int lengthOfCheckoutPeriod = 7;
    double initialLateFee = 1.0;
    double feePerLateDay = 1.5;


    LibraryCatalogue(map<string, Book*> collection) {
        bookCollection = collection;
    }

    LibraryCatalogue(map<string, Book*> collection, int lengthOfCheckoutPeriod, double initialLateFee, double feePerLateDay) {
        bookCollection = collection;
        lengthOfCheckoutPeriod = lengthOfCheckoutPeriod;
        initialLateFee = initialLateFee;
        feePerLateDay = feePerLateDay;
    }

    int getCurrentDay() {
        return currentDay;
    }

    map<string, Book*> getBookCollection() {
        return bookCollection;
    }

    Book* getBook(string bookTitle) {
        return getBookCollection()[bookTitle];
    }

    int getLengthOfCheckoutPeriod() {
        return lengthOfCheckoutPeriod;
    }
    double getInitialLateFee() {
        return initialLateFee;
    }
    double getFeePerLateDay() {
        return feePerLateDay;
    }

    void nextDay() {
        currentDay++;
    }
    void setDay(int day) {
        currentDay = day;
    }

    void checkoutBook(string title) {
        Book* book = getBook(title);
        if ((*book).getIsCheckedOut()) {
            sorryBookAlreadyCheckedOut(book);
        }
        else {
            book->setIsCheckedOut(true, currentDay);
            cout << "You just checked out " << title << ". It is due on day " << (getCurrentDay() + getLengthOfCheckoutPeriod()) << "." << endl;
        }
    }
    void returnBook(string title) {
        Book* book = getBook(title);
        int daysLate = currentDay - (book->getdayCheckedOut() + getLengthOfCheckoutPeriod());
        if (daysLate > 0) {
            cout << "You owe the library Rs." << (getInitialLateFee() + daysLate * getFeePerLateDay())
                << " because your book is " << daysLate << " days overdue" << endl;
        }
        else {
            cout << "Book returned. Thank you" << endl;
        }
        book->setIsCheckedOut(false, -1);
    }
    void sorryBookAlreadyCheckedOut(Book* book) {
        cout << "Sorry. " << book->getTitle() << " is already checked out. It should be back on day "
            << (book->getdayCheckedOut() + getLengthOfCheckoutPeriod()) << "." << endl;
    }
};

int main() {
    Book harry = Book("Harry Potter", 325);
    map<string, Book*> bookCollection;
    bookCollection.insert(make_pair("Harry Potter", &harry));
    LibraryCatalogue lib = LibraryCatalogue(bookCollection);
    lib.checkoutBook("Harry Potter");
    lib.nextDay();
    lib.nextDay();
    lib.checkoutBook("Harry Potter");
    lib.setDay(17);
    lib.returnBook("Harry Potter");
    lib.checkoutBook("Harry Potter");
    return 0;
}