#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <string>
#include <limits>
#include <algorithm>
using namespace std;

// ================= TRANSACTION STRUCT =================
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

// ================= BANK ACCOUNT CLASS =================
class BankAccount {
private:
    int accountNo;
    string name;
    string password;
    string type;         // Savings / Current
    double balance;
    vector<Transaction> transactions;

public:
    BankAccount() : accountNo(0), balance(0) {}

    BankAccount(int no, string n, string pass, string t, double b)
        : accountNo(no), name(n), password(pass), type(t), balance(b) {}

    // Getters
    int getNo() const { return accountNo; }
    string getName() const { return name; }
    string getType() const { return type; }
    double getBalance() const { return balance; }
    bool authenticate(const string& pass) const { return password == pass; }

    // Setters
    void setAccountNo(int no) { accountNo = no; }
    void setName(const string& n) { name = n; }
    void setPassword(const string& p) { password = p; }
    void setType(const string& t) { type = t; }
    void setBalance(double b) { balance = b; }

    // Operations
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
        double interest = balance * (rate / 100.0);
        balance += interest;
        transactions.push_back(Transaction("INTEREST", interest));
    }

    void showDetails() const {
        cout << "\n---------------- ACCOUNT DETAILS ----------------\n";
        cout << "Account No : " << accountNo << "\n";
        cout << "Name       : " << name << "\n";
        cout << "Type       : " << type << "\n";
        cout << "Balance    : Rs. " << fixed << setprecision(2) << balance << "\n";
        cout << "-------------------------------------------------\n";
    }

    void showTransactions(int limit = 10) const {
        if (transactions.empty()) {
            cout << "No transactions yet.\n";
            return;
        }
        cout << "\n----------- LAST " << limit << " TRANSACTIONS -----------\n";
        int count = 0;
        for (auto it = transactions.rbegin(); it != transactions.rend() && count < limit; ++it, ++count) {
            cout << it->date << " | " << setw(10) << left << it->type
                 << " | Rs. " << fixed << setprecision(2) << it->amount << "\n";
        }
        cout << "-------------------------------------------------\n";
    }
};

// =============== PRESENTATION SCREEN ==================
void showPresentation() {
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                                                                      ║\n";
    cout << "║   ██╗██████╗ ███╗   ███╗    ██████╗  █████╗ ███╗   ██╗██╗  ██╗       ║\n";
    cout << "║   ██║██╔══██╗████╗ ████║    ██╔══██╗██╔══██╗████╗  ██║██║ ██╔╝       ║\n";
    cout << "║   ██║██████╔╝██╔████╔██║    ██████╔╝███████║██╔██╗ ██║█████╔╝        ║\n";
    cout << "║   ██║██╔══██╗██║╚██╔╝██║    ██╔══██╗██╔══██║██║╚██╗██║██╔═██╗        ║\n";
    cout << "║   ██║██████╔╝██║ ╚═╝ ██║    ██████╔╝██║  ██║██║ ╚████║██║  ██╗       ║\n";
    cout << "║   ╚═╝╚═════╝ ╚═╝     ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝       ║\n";
    cout << "║                                                                      ║\n";
    cout << "╠══════════════════════════════════════════════════════════════════════╣\n";
    cout << "║  🎓 PRESENTED BY IBM STUDENTS OF ARKA JAIN UNIVERSITY 🎓              ║\n";
    cout << "║                                                                      ║\n";
    cout << "║   👨‍🎓 Mohit Raj        👩‍🎓 Rishika Kumari      👩‍🎓 G. Omkeshwari   ║\n";
    cout << "║      AJU/250609            AJU/250878              AJU/250193         ║\n";
    cout << "║                                                                      ║\n";
    cout << "╠══════════════════════════════════════════════════════════════════════╣\n";
    cout << "║  📚 SEMESTER - 1 | 🏛️ ARKA JAIN UNIVERSITY | 💻 C++ OOP PROJECT        ║\n";
    cout << "║                                                                      ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════════╝\n\n";

    cout << "🎯 Loading IBM Bank System";
    for (int i = 0; i < 3; i++) {
        cout << ".";
        cout.flush();
        for (volatile int j = 0; j < 1000000; j++);
    }
    cout << "\n🚀 IBM BANK MANAGEMENT SYSTEM v2.0 - READY! 🚀\n\n";
}


// ===================== BANK CLASS =====================
class Bank {
private:
    vector<BankAccount> accounts;
    int nextAccountNo;
    string adminUsername = "admin@ibmbank.in";
    string adminPassword = "ibm@24x7";

public:
    Bank() : nextAccountNo(1001) {
        createDemoAccounts();
        cout << "\n[INFO] Demo accounts loaded.\n";
        cout << "Demo Customer  : 212173314 / 1769\n";
        cout << "Admin Login    : " << adminUsername << " / " << adminPassword << "\n";
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

    BankAccount* findAccount(int no) {
        for (auto& acc : accounts) {
            if (acc.getNo() == no) return &acc;
        }
        return nullptr;
    }

    // ---------- Admin functions ----------
    void createAccount() {
        BankAccount acc;
        string input;
        double initial;

        cout << "\n====== CREATE NEW ACCOUNT ======\n";
        cout << "Enter customer full name : ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, input);
        acc.setName(input);

        cout << "Set login password       : ";
        getline(cin, input);
        acc.setPassword(input);

        cout << "Account type (Savings/Current): ";
        getline(cin, input);
        acc.setType(input);

        cout << "Initial deposit (Rs.)    : ";
        while (!(cin >> initial) || initial < 0) {
            cout << "Enter a valid positive amount: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        acc.setBalance(initial);

        acc.setAccountNo(nextAccountNo++);
        accounts.push_back(acc);

        cout << "\n[ACCOUNT CREATED]\n";
        cout << "Name       : " << acc.getName() << "\n";
        cout << "Account No : " << acc.getNo()   << "\n";
        cout << "Password   : (as entered)\n";
    }

    void deleteAccount() {
        int no;
        cout << "Enter account number to delete: ";
        cin >> no;

        auto it = remove_if(accounts.begin(), accounts.end(),
                            [no](const BankAccount& acc) { return acc.getNo() == no; });
        if (it == accounts.end()) {
            cout << "Account not found.\n";
        } else {
            accounts.erase(it, accounts.end());
            cout << "Account deleted.\n";
        }
    }

    void listAllAccounts() const {
        cout << "\n================ ALL ACCOUNTS ================\n";
        if (accounts.empty()) {
            cout << "No accounts available.\n";
        } else {
            for (const auto& acc : accounts) {
                cout << "No: " << acc.getNo()
                     << " | Name: " << acc.getName()
                     << " | Type: " << acc.getType()
                     << " | Balance: Rs. " << fixed << setprecision(2) << acc.getBalance()
                     << "\n";
            }
        }
        cout << "==============================================\n";
    }

    void applyInterest() {
        double rate;
        cout << "Enter interest rate for Savings accounts (%): ";
        cin >> rate;

        int count = 0;
        for (auto& acc : accounts) {
            if (acc.getType() == "Savings") {
                acc.addInterest(rate);
                count++;
            }
        }
        cout << "Interest applied to " << count << " Savings accounts.\n";
    }

    void adminMenu() {
        int choice;
        do {
            cout << "\n============= ADMIN PANEL (IBM BANKING) =============\n";
            cout << "1. Create Account\n";
            cout << "2. Delete Account\n";
            cout << "3. View All Accounts\n";
            cout << "4. Apply Interest (Savings)\n";
            cout << "0. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1: createAccount();   break;
                case 2: deleteAccount();   break;
                case 3: listAllAccounts(); break;
                case 4: applyInterest();   break;
                case 0: cout << "Admin logged out.\n"; break;
                default: cout << "Invalid choice.\n";
            }
        } while (choice != 0);
    }

    // ---------- Customer functions ----------
    void transfer(BankAccount* from) {
        int toNo;
        double amount;
        cout << "Transfer to account no : ";
        cin >> toNo;
        cout << "Amount (Rs.)           : ";
        cin >> amount;

        BankAccount* to = findAccount(toNo);
        if (!to) {
            cout << "Target account not found.\n";
            return;
        }
        if (!from->withdraw(amount)) {
            cout << "Transfer failed (insufficient balance or invalid amount).\n";
            return;
        }
        to->deposit(amount);
        cout << "Transfer successful.\n";
    }

    void customerMenu() {
        int accNo;
        string pass;

        cout << "\n======= CUSTOMER LOGIN (IBM BANKING) =======\n";
        cout << "Account No : ";
        cin >> accNo;
        cout << "Password   : ";
        cin.ignore();
        getline(cin, pass);

        BankAccount* acc = findAccount(accNo);
        if (!acc || !acc->authenticate(pass)) {
            cout << "Invalid account number or password.\n";
            return;
        }

        int choice;
        do {
            cout << "\n------------ CUSTOMER MENU ------------\n";
            acc->showDetails();
            cout << "1. Deposit\n";
            cout << "2. Withdraw\n";
            cout << "3. Transfer\n";
            cout << "4. View Transactions\n";
            cout << "0. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;

            double amount;
            switch (choice) {
                case 1:
                    cout << "Deposit amount (Rs.): ";
                    cin >> amount;
                    if (acc->deposit(amount)) cout << "Amount deposited.\n";
                    else cout << "Invalid amount.\n";
                    break;

                case 2:
                    cout << "Withdraw amount (Rs.): ";
                    cin >> amount;
                    if (acc->withdraw(amount)) cout << "Amount withdrawn.\n";
                    else cout << "Withdrawal failed.\n";
                    break;

                case 3:
                    transfer(acc);
                    break;

                case 4:
                    acc->showTransactions();
                    break;

                case 0:
                    cout << "Customer logged out.\n";
                    break;

                default:
                    cout << "Invalid choice.\n";
            }
        } while (choice != 0);
    }

    // ---------- Persistence (simple text) ----------
    void saveAccounts() {
        ofstream out("bank_data.txt");
        for (const auto& acc : accounts) {
            out << acc.getNo() << "|"
                << acc.getName() << "|"
                << acc.getType() << "|"
                << fixed << setprecision(2) << acc.getBalance()
                << "\n";
        }
        out.close();
    }
};

// ===================== MAIN ===========================
int main() {
    showPresentation();

    Bank bank;
    int choice;

    do {
        cout << "\n================ IBM BANKING SYSTEM ================\n";
        cout << "1. Admin Login\n";
        cout << "2. Customer Login\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string username, password;
                cout << "\n--- ADMIN LOGIN ---\n";
                cout << "Username : ";
                cin >> username;
                cout << "Password : ";
                cin.ignore();
                getline(cin, password);

                if (bank.adminLogin(username, password)) {
                    bank.adminMenu();
                } else {
                    cout << "Access denied.\n";
                }
                break;
            }
            case 2:
                bank.customerMenu();
                break;

            case 0:
                cout << "\nThank you for using IBM Banking System.\n";
                cout << "Project: Arka Jain University – Semester 1\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
