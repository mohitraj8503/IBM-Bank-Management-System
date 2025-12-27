#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <string>
#include <limits>
#include <algorithm>
using namespace std;

// Transaction structure
struct Transaction {
    string type;
    double amount;
    string date;
    Transaction(string t, double a) : type(t), amount(a) {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        char buf[20];
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", ltm);
        date = buf;
    }
};

// Account class with PROPER getters/setters
class BankAccount {
private:
    int accountNo;
    string name;
    string password;
    string type;
    double balance;
    vector<Transaction> transactions;

public:
    BankAccount() : accountNo(0), balance(0) {}
    
    BankAccount(int no, string n, string pass, string t, double b) 
        : accountNo(no), name(n), password(pass), type(t), balance(b) {}

    // GETTERS
    int getNo() const { return accountNo; }
    string getName() const { return name; }
    string getType() const { return type; }
    double getBalance() const { return balance; }
    const vector<Transaction>& getTransactions() const { return transactions; }
    bool authenticate(const string& pass) const { return password == pass; }

    // SETTERS
    void setAccountNo(int no) { accountNo = no; }
    void setName(const string& n) { name = n; }
    void setPassword(const string& pass) { password = pass; }
    void setType(const string& t) { type = t; }
    void setBalance(double b) { balance = b; }

    // Core banking operations
    bool deposit(double amount) {
        if (amount <= 0) return false;
        balance += amount;
        transactions.push_back(Transaction("DEPOSIT", amount));
        return true;
    }

    bool withdraw(double amount) {
        if (amount <= 0 || amount > balance) return false;
        balance -= amount;
        transactions.push_back(Transaction("WITHDRAWAL", -amount));
        return true;
    }

    void addInterest(double rate) {
        double interest = balance * (rate / 100);
        balance += interest;
        transactions.push_back(Transaction("INTEREST", interest));
    }

    // Display functions
    void showDetails() const {
        cout << "\n=== ACCOUNT DETAILS ===" << endl;
        cout << "Account No: " << accountNo << endl;
        cout << "Name: " << name << endl;
        cout << "Type: " << type << endl;
        cout << "Balance: Rs. " << fixed << setprecision(2) << balance << endl;
    }

    void showTransactions(int limit = 10) const {
        if (transactions.empty()) {
            cout << "No transactions yet." << endl;
            return;
        }
        cout << "\n=== LAST " << limit << " TRANSACTIONS ===" << endl;
        int count = 0;
        for (auto it = transactions.rbegin(); it != transactions.rend() && count < limit; ++it, ++count) {
            cout << it->date << " | " << it->type << " | Rs. " 
                 << fixed << setprecision(2) << it->amount << endl;
        }
    }
};

// ✅ FIXED PRESENTATION SCREEN - NO THREADING!
void showPresentation() {
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                                                                      ║" << endl;
    cout << "║    ██████╗ ██████╗██╗  ██╗██████╗  █████╗ ███╗   ██╗███████╗         ║" << endl;
    cout << "║    ██╔══██╗██╔══██╗██║ ██╔╝██╔══██╗██╔══██╗████╗  ██║██╔════╝         ║" << endl;
    cout << "║    ██████╔╝██████╔╝█████╔╝ ██████╔╝███████║██╔██╗ ██║█████╗           ║" << endl;
    cout << "║    ██╔══██╗██╔══██╗██╔═██╗ ██╔══██╗██╔══██║██║╚██╗██║██╔══╝           ║" << endl;
    cout << "║    ██████╔╝██║  ██║██║  ██╗██║  ██║██║  ██║██║ ╚████║███████╗         ║" << endl;
    cout << "║    ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚══════╝         ║" << endl;
    cout << "║                                                                      ║" << endl;
    cout << "╠══════════════════════════════════════════════════════════════════════╣" << endl;
    cout << "║  🎓 PRESENTED BY IBM STUDENTS OF ARKA JAIN UNIVERSITY 🎓              ║" << endl;
    cout << "║                                                                      ║" << endl;
    cout << "║  👨‍🎓 Mohit Raj              👩‍🎓 Rishika Kumari          👩‍🎓 G. Omkeshwari ║" << endl;
    cout << "║     AJU/250609                    AJU/250878                    AJU/250193 ║" << endl;
    cout << "║                                                                      ║" << endl;
    cout << "╠══════════════════════════════════════════════════════════════════════╣" << endl;
    cout << "║  📚 SEMESTER - 1  |  🏛️ ARKA JAIN UNIVERSITY  |  💻 C++ OOP PROJECT     ║" << endl;
    cout << "║                                                                      ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════════════╝" << endl;
    cout << "\n";

    // ✨ Simple loading animation without threading
    cout << "🎯 Loading IBM Bank System";
    for (int i = 0; i < 3; i++) {
        cout << ".";
        cout.flush();
        for (volatile int j = 0; j < 1000000; j++); // Simple delay
    }
    cout << "\n🚀 IBM BANK MANAGEMENT SYSTEM v2.0 - READY! 🚀\n" << endl;
}

// Bank class (unchanged)
class Bank {
private:
    vector<BankAccount> accounts;
    int nextAccountNo;
    string adminUsername = "admin@ibmbank.in";
    string adminPassword = "ibm@24x7";

public:
    Bank() : nextAccountNo(1001) {
        createDemoAccounts();
        cout << "\n✅ DEMO ACCOUNTS LOADED!" << endl;
        cout << "👤 Customer: 212173314 / 1769" << endl;
        cout << "👨‍💼 Admin: " << adminUsername << " / " << adminPassword << endl;
    }

    ~Bank() {
        saveAccounts();
    }

    void createDemoAccounts() {
        BankAccount demoCust(212173314, "Demo Customer", "1769", "Savings", 50000.00);
        accounts.push_back(demoCust);
        nextAccountNo = 212173315;

        BankAccount* demo = findAccount(212173314);
        if (demo) {
            demo->deposit(25000);
            demo->withdraw(5000);
        }
    }

    bool adminLogin(const string& username, const string& password) {
        return (username == adminUsername && password == adminPassword);
    }

    void createAccount() {
        BankAccount acc;
        string pass;
        
        cout << "\n👤 === NEW ACCOUNT CREATION ===" << endl;
        cout << "Enter customer FULL NAME: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, pass);
        acc.setName(pass);
        
        cout << "🔐 Enter LOGIN PASSWORD for this customer: ";
        getline(cin, pass);
        acc.setPassword(pass);
        
        cout << "🏦 Account type (Savings/Current): ";
        getline(cin, pass);
        acc.setType(pass);
        
        double initial;
        cout << "💰 Initial deposit amount: Rs. ";
        while (!(cin >> initial) || initial < 0) {
            cout << "❌ Invalid amount! Enter positive number: Rs. ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        acc.setBalance(initial);

        acc.setAccountNo(nextAccountNo++);
        accounts.push_back(acc);
        
        cout << "\n✅ ACCOUNT CREATED SUCCESSFULLY!" << endl;
        cout << "👤 Name     : " << acc.getName() << endl;
        cout << "📱 Account No: " << acc.getNo() << endl;
        cout << "🔐 Login Password: " << pass << " (save this!)" << endl;
        cout << "💰 Balance  : Rs. " << fixed << setprecision(2) << acc.getBalance() << endl;
    }

    BankAccount* findAccount(int no) {
        for (auto& acc : accounts) {
            if (acc.getNo() == no) return &acc;
        }
        return nullptr;
    }

    void adminMenu() {
        int choice;
        do {
            cout << "\n=== 👨‍💼 ADMIN PANEL ===" << endl;
            cout << "1. Create Account" << endl;
            cout << "2. Delete Account" << endl;
            cout << "3. View All Accounts" << endl;
            cout << "4. Apply Interest (Savings)" << endl;
            cout << "0. Logout" << endl;
            cout << "Choice: ";
            cin >> choice;

            switch (choice) {
                case 1: createAccount(); break;
                case 2: deleteAccount(); break;
                case 3: listAllAccounts(); break;
                case 4: applyInterest(); break;
                case 0: cout << "👋 Admin logged out!" << endl; break;
                default: cout << "❌ Invalid choice!" << endl;
            }
        } while (choice != 0);
    }

    void customerMenu() {
        int accNo;
        string pass;
        
        cout << "\n🔐 Enter Account No: ";
        cin >> accNo;
        cout << "🔐 Enter Password: ";
        cin.ignore();
        getline(cin, pass);

        BankAccount* acc = findAccount(accNo);
        if (!acc || !acc->authenticate(pass)) {
            cout << "❌ Invalid credentials!" << endl;
            return;
        }

        int choice;
        do {
            cout << "\n=== 👤 CUSTOMER MENU (" << acc->getName() << ") ===" << endl;
            acc->showDetails();
            cout << "1. 💰 Deposit" << endl;
            cout << "2. 💸 Withdraw" << endl;
            cout << "3. 🔄 Transfer" << endl;
            cout << "4. 📋 Transaction History" << endl;
            cout << "0. 🚪 Logout" << endl;
            cout << "Choice: ";
            cin >> choice;

            double amount;
            switch (choice) {
                case 1:
                    cout << "💰 Deposit amount: Rs. ";
                    cin >> amount;
                    if (acc->deposit(amount)) 
                        cout << "✅ Deposited successfully!" << endl;
                    else 
                        cout << "❌ Deposit failed!" << endl;
                    break;
                    
                case 2:
                    cout << "💸 Withdraw amount: Rs. ";
                    cin >> amount;
                    if (acc->withdraw(amount)) 
                        cout << "✅ Withdrawn successfully!" << endl;
                    else 
                        cout << "❌ Withdrawal failed!" << endl;
                    break;
                    
                case 3: transfer(acc); break;
                case 4: acc->showTransactions(); break;
                case 0: cout << "👋 Logged out!" << endl; break;
                default: cout << "❌ Invalid choice!" << endl;
            }
        } while (choice != 0);
    }

private:
    void deleteAccount() {
        int no;
        cout << "🗑️ Account No to delete: ";
        cin >> no;
        
        auto it = remove_if(accounts.begin(), accounts.end(),
            [no](const BankAccount& acc) { return acc.getNo() == no; });
        accounts.erase(it, accounts.end());
        
        cout << "✅ Account deleted!" << endl;
    }

    void listAllAccounts() const {
        cout << "\n=== 📊 ALL ACCOUNTS (" << accounts.size() << ") ===" << endl;
        for (const auto& acc : accounts) {
            cout << "No: " << acc.getNo() << " | " << acc.getName() 
                 << " | " << acc.getType() 
                 << " | Rs. " << fixed << setprecision(2) << acc.getBalance() << endl;
        }
    }

    void applyInterest() {
        double rate;
        cout << "📈 Interest rate (%): ";
        cin >> rate;
        int count = 0;
        for (auto& acc : accounts) {
            if (acc.getType() == "Savings") {
                acc.addInterest(rate);
                count++;
            }
        }
        cout << "✅ Interest applied to " << count << " Savings accounts!" << endl;
    }

    void transfer(BankAccount* from) {
        int toNo;
        double amount;
        cout << "➡️ To Account No: ";
        cin >> toNo;
        cout << "💰 Amount: Rs. ";
        cin >> amount;

        BankAccount* to = findAccount(toNo);
        if (to && from->withdraw(amount)) {
            to->deposit(amount);
            cout << "✅ Transfer successful!" << endl;
        } else {
            cout << "❌ Transfer failed!" << endl;
        }
    }

    void saveAccounts() {
        ofstream out("bank_data.txt");
        for (const auto& acc : accounts) {
            out << acc.getNo() << "|" << acc.getName() << "|" 
                << "*****|" << acc.getType() << "|" 
                << fixed << setprecision(2) << acc.getBalance() << endl;
        }
        out.close();
    }
};

int main() {
    // 🔥 STUNNING PRESENTATION SCREEN - FIXED!
    showPresentation();
    
    Bank bank;
    int choice;

    do {
        cout << "\n🎯 MAIN MENU" << endl;
        cout << "1. 👨‍💼 Admin Login" << endl;
        cout << "2. 👤 Customer Login" << endl;
        cout << "0. ❌ Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string username, password;
                cout << "\n🔐 Username: ";
                cin >> username;
                cout << "🔐 Password: ";
                cin.ignore();
                getline(cin, password);
                
                if (bank.adminLogin(username, password)) {
                    bank.adminMenu();
                } else {
                    cout << "❌ Access Denied!" << endl;
                }
                break;
            }
            case 2:
                bank.customerMenu();
                break;
            case 0:
                cout << "\n👋 Thank you for using IBM Bank!" << endl;
                cout << "🎓 Project by Arka Jain University Students" << endl;
                break;
            default:
                cout << "❌ Invalid choice!" << endl;
        }
    } while (choice != 0);

    return 0;
}
