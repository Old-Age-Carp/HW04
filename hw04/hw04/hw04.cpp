#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

class Book {
public:
    string title;
    string author;
    int stock;
    int borrowedCount;

    Book(const string& title, const string& author)
        : title(title), author(author), stock(3), borrowedCount(0) {
    }

    bool isAvailableForLending() const {
        return borrowedCount < stock;
    }

    bool lend() {
        if (isAvailableForLending()) {
            borrowedCount++;
            return true;
        }
        return false;
    }

    bool returnBook() {
        if (borrowedCount > 0) {
            borrowedCount--;
            return true;
        }
        return false;
    }

    void displayBookInfo() const {
        cout << "- 제목: " << title
            << ", 저자: " << author
            << ", 재고: " << stock - borrowedCount
            << "권 (총 " << stock << "권, 대여 중: " << borrowedCount << "권)";
        if (isAvailableForLending()) {
            cout << " [대여 가능]";
        }
        else {
            cout << " [모두 대여 중]";
        }
        cout << endl;
    }
};

class BookManager {
private:
    vector<Book> books;

public:
    void addBook(const string& title, const string& author) {
        books.push_back(Book(title, author));
        cout << "책이 추가되었습니다: " << title << " by " << author << endl;
    }

    void displayAllBooks() const {
        if (books.empty()) {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        cout << "--- 현재 도서 목록: (" << books.size() << "권) ---" << endl;
        for (size_t i = 0; i < books.size(); i++) {
            books[i].displayBookInfo();
        }
        cout << "-----------------------------------" << endl;
    }

    void searchByTitle(const string& title) const {
        cout << "\n--- 제목으로 책 검색: '" << title << "' ---" << endl;
        bool found = false;
        for (const auto& book : books) {
            if (book.title == title) {
                book.displayBookInfo();
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "책을 찾을 수 없습니다: '" << title << "'" << endl;
        }
        cout << "---------------------------------------" << endl;
    }

    void searchByAuthor(const string& author) const {
        cout << "\n--- 작가로 책 검색: '" << author << "' ---" << endl;
        bool found = false;
        for (const auto& book : books) {
            if (book.author == author) {
                book.displayBookInfo();
                found = true;
            }
        }
        if (!found) {
            cout << "해당 작가의 책을 찾을 수 없습니다: '" << author << "'" << endl;
        }
        cout << "---------------------------------------" << endl;
    }

    void lendBook(const string& identifier, bool isTitleSearch) {
        cout << "\n--- 책 대여 시도: '" << identifier << "' ---" << endl;
        bool actionTaken = false;
        for (auto& book : books) {
            bool match = false;
            if (isTitleSearch && book.title == identifier) {
                match = true;
            }
            else if (!isTitleSearch && book.author == identifier) {
                match = true;
            }

            if (match) {
                if (book.lend()) {
                    cout << "'" << book.title << "'(저자: " << book.author << ") 책을 대여했습니다." << endl;
                    cout << "남은 재고: " << book.stock - book.borrowedCount << "권" << endl;
                    actionTaken = true;
                    if (isTitleSearch) break;
                }
                else {
                    cout << "'" << book.title << "'(저자: " << book.author << ") 책은 현재 대여 불가합니다 (모두 대여 중)." << endl;
                    actionTaken = true;
                    if (isTitleSearch) break;
                }
            }
        }
        if (!actionTaken) {
            if (isTitleSearch) cout << "해당 제목의 책을 찾을 수 없습니다: '" << identifier << "'" << endl;
            else cout << "해당 작가의 책을 찾을 수 없습니다: '" << identifier << "'" << endl;
        }
        cout << "---------------------------------------" << endl;
    }

    void returnBook(const string& identifier, bool isTitleSearch) {
        cout << "\n--- 책 반납 시도: '" << identifier << "' ---" << endl;
        bool actionTaken = false;
        for (auto& book : books) {
            bool match = false;
            if (isTitleSearch && book.title == identifier) {
                match = true;
            }
            else if (!isTitleSearch && book.author == identifier) {
                match = true;
            }

            if (match) {
                if (book.returnBook()) {
                    cout << "'" << book.title << "'(저자: " << book.author << ") 책을 반납했습니다." << endl;
                    cout << "남은 재고: " << book.stock - book.borrowedCount << "권" << endl;
                    actionTaken = true;
                    if (isTitleSearch) break;
                }
                else {
                    cout << "'" << book.title << "'(저자: " << book.author << ") 책은 현재 대여 중이지 않습니다." << endl;
                    actionTaken = true;
                    if (isTitleSearch) break;
                }
            }
        }
        if (!actionTaken) {
            if (isTitleSearch) cout << "해당 제목의 책을 찾을 수 없습니다: '" << identifier << "'" << endl;
            else cout << "해당 작가의 책을 찾을 수 없습니다: '" << identifier << "'" << endl;
        }
        cout << "---------------------------------------" << endl;
    }
};

int main() {
    BookManager manager;

    while (true) {
        cout << "\n========== 도서관 관리 프로그램 ==========" << endl;
        cout << "1. 책 추가" << endl;
        cout << "2. 모든 책 출력" << endl;
        cout << "3. 종료" << endl;
        cout << "--------------------------------------" << endl;
        cout << "4. 제목으로 책 검색" << endl;
        cout << "5. 작가로 책 검색" << endl;
        cout << "6. 제목으로 책 대여" << endl;
        cout << "7. 작가로 책 대여" << endl;
        cout << "8. 제목으로 책 반납" << endl;
        cout << "9. 작가로 책 반납" << endl;
        cout << "==========================================" << endl;
        cout << "선택: ";

        int choice;
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string inputIdentifier;

        if (choice == 1) {
            string title, author;
            cout << "책 제목: ";
            getline(cin, title);
            cout << "책 저자: ";
            getline(cin, author);
            manager.addBook(title, author);
        }
        else if (choice == 2) {
            manager.displayAllBooks();
        }
        else if (choice == 3) {
            cout << "프로그램을 종료합니다." << endl;
            break;
        }
        else if (choice == 4) {
            cout << "검색할 책 제목: ";
            getline(cin, inputIdentifier);
            manager.searchByTitle(inputIdentifier);
        }
        else if (choice == 5) {
            cout << "검색할 작가 이름: ";
            getline(cin, inputIdentifier);
            manager.searchByAuthor(inputIdentifier);
        }
        else if (choice == 6) {
            cout << "대여할 책 제목: ";
            getline(cin, inputIdentifier);
            manager.lendBook(inputIdentifier, true);
        }
        else if (choice == 7) {
            cout << "대여할 책 작가 이름: ";
            getline(cin, inputIdentifier);
            manager.lendBook(inputIdentifier, false);
        }
        else if (choice == 8) {
            cout << "반납할 책 제목: ";
            getline(cin, inputIdentifier);
            manager.returnBook(inputIdentifier, true);
        }
        else if (choice == 9) {
            cout << "반납할 책 작가 이름: ";
            getline(cin, inputIdentifier);
            manager.returnBook(inputIdentifier, false);
        }
        else {
            cout << "잘못된 입력입니다. 메뉴를 다시 확인하고 시도하세요." << endl;
        }
    }

    return 0;
}