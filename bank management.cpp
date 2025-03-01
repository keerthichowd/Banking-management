#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Account {
public:
    string accNumber;
    string name;
    double balance;

    Account() : balance(0) {}

    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accNumber;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        balance = 0;
        saveToFile();
        cout << "Account created successfully!\n";
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            updateFile();
            cout << "Amount deposited successfully!\n";
        } else {
            cout << "Invalid amount!\n";
        }
    }

    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            updateFile();
            cout << "Withdrawal successful!\n";
            return true;
        } else {
            cout << "Insufficient balance or invalid amount!\n";
            return false;
        }
    }

    void display() const {
        cout << "\nAccount Number: " << accNumber
             << "\nName: " << name
             << "\nBalance: " << balance << "\n";
    }

    void saveToFile() {
        ofstream file("accounts.txt", ios::app);
        file << accNumber << " " << name << " " << balance << endl;
        file.close();
    }

    static vector<Account> loadAccounts() {
        vector<Account> accounts;
        ifstream file("accounts.txt");
        Account acc;
        while (file >> acc.accNumber >> ws && getline(file, acc.name) && file >> acc.balance) {
            accounts.push_back(acc);
        }
        file.close();
        return accounts;
    }

    void updateFile() {
        vector<Account> accounts = loadAccounts();
        ofstream file("accounts.txt");

        for (size_t i = 0; i < accounts.size(); i++) {
            if (accounts[i].accNumber == accNumber) {
                file << accNumber << " " << name << " " << balance << endl;
            } else {
                file << accounts[i].accNumber << " " << accounts[i].name << " " << accounts[i].balance << endl;
            }
        }
        file.close();
    }
};

int main() {
    vector<Account> accounts = Account::loadAccounts();
    int choice;
    do {
        cout << "\nBank Management System";
        cout << "\n1. Create Account";
        cout << "\n2. Deposit Money";
        cout << "\n3. Withdraw Money";
        cout << "\n4. Check Balance";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) {
            Account acc;
            acc.createAccount();
            accounts.push_back(acc);
        } else if (choice == 2 || choice == 3 || choice == 4) {
            string accNumber;
            cout << "Enter Account Number: ";
            cin >> accNumber;
            bool found = false;
            for (size_t i = 0; i < accounts.size(); i++) {
                if (accounts[i].accNumber == accNumber) {
                    found = true;
                    if (choice == 2) {
                        double amount;
                        cout << "Enter amount to deposit: ";
                        cin >> amount;
                        accounts[i].deposit(amount);
                    } else if (choice == 3) {
                        double amount;
                        cout << "Enter amount to withdraw: ";
                        cin >> amount;
                        accounts[i].withdraw(amount);
                    } else if (choice == 4) {
                        accounts[i].display();
                    }
                    break;
                }
            }
            if (!found) cout << "Account not found!\n";
        }
    } while (choice != 5);

    cout << "Exiting... Thank you!\n";
    return 0;
}


