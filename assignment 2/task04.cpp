#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class SavingsAccount {
private:
    string accountNumber;
    double balance;
    double transactions[10];
    int count;

    void addTransaction(double amount) { // defined inside the class
        if (count < 10) transactions[count++] = amount;
        else {
            for (int i = 1; i < 10; ++i) transactions[i - 1] = transactions[i];
            transactions[9] = amount;
        }
    }

public:
    SavingsAccount(const string& number, double openingBalance)
        : accountNumber(number), balance(openingBalance), count(0) {}

    void deposit(double amount);
    bool withdraw(double amount);
    void miniStatement() const;
};

void SavingsAccount::deposit(double amount) {
    if (amount <= 0) return;
    balance += amount;
    addTransaction(amount);
}

bool SavingsAccount::withdraw(double amount) {
    if (amount <= 0 || amount > balance) return false;
    balance -= amount;
    addTransaction(-amount);
    return true;
}

void SavingsAccount::miniStatement() const {
    cout << "Account: " << accountNumber << "\nBalance: Rs " << fixed << setprecision(2) << balance
         << "\nLast " << count << " transactions (positive=deposit, negative=withdrawal):\n";
    for (int i = 0; i < count; ++i) cout << transactions[i] << '\n';
}

int main() {
    SavingsAccount account("SB1001", 5000.0);
    account.deposit(1000);
    account.withdraw(500);
    account.deposit(250);
    for (int i = 1; i <= 9; ++i) account.deposit(i * 100);
    account.miniStatement();
}
