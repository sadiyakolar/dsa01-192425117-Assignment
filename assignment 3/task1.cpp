#include <iostream>
#include <stdexcept>
#include <string>

class Book {
    std::string title;
    std::string author;
    int copies;
public:
    Book() : Book("Untitled", "Unknown", 0) {}
    explicit Book(const std::string& t) : Book(t, "Unknown", 1) {}
    Book(const std::string& t, const std::string& a, int c)
        : title(t), author(a), copies(c) {
        if (c < 0) throw std::invalid_argument("copies cannot be negative");
    }
    void print() const {
        std::cout << "Title: " << title << ", Author: " << author
                  << ", Copies: " << copies << '\n';
    }
};
int main() {
    Book empty;
    Book donated("C++ Basics");
    Book full("Data Structures", "Mark Allen", 5);
    empty.print(); donated.print(); full.print();
    try { Book invalid("Invalid", "Test", -2); }
    catch (const std::invalid_argument& e) { std::cout << "Rejected: " << e.what() << '\n'; }
}
