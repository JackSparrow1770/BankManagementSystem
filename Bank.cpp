#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>

using namespace std;

#define MIN_BALANCE 100

class deficient_funds
{
};
class Cl_Accounts
{
private:
    long account_no;
    string client_first_name;
    string client_last_name;
    float client_balance;
    static long next_account_no;

public:
    Cl_Accounts() {} // Default constructor
    Cl_Accounts(string first_name, string last_name, float client_balance);

    long getAccountNo()
    {
        return account_no;
    }

    string get_first_name()
    {
        return client_first_name;
    }
    string get_last_name()
    {
        return client_last_name;
    }

    float getBalance()
    {
        return client_balance;
    }

    void Deposit(float amount);
    void Withdraw(float amount);
    static void setLastAccountNo(long account_no);
    static long getLastAccountNo();

    friend ofstream &operator<<(ofstream &ofs, Cl_Accounts &acc);
    friend ifstream &operator>>(ifstream &ifs, Cl_Accounts &acc);
    friend ostream &operator<<(ostream &os, Cl_Accounts &acc);
};

long Cl_Accounts::next_account_no = 0;

class Bank
{
private:
    map<long, Cl_Accounts> accounts_cl;

public:
    Bank();
    Cl_Accounts Cl_Open_Account(string first_name, string last_name, float balance);
    Cl_Accounts Cl_Balance_Enquiry(long account_no);
    Cl_Accounts Deposit(long account_no, float amt);
    Cl_Accounts Withdraw(long account_no, float amt);

    void CloseAccount(long account_no);
    void ShowAllAccounts();
    ~Bank();
};

int main()
{
    Bank b;
    Cl_Accounts acc;

    int option;
    string first_name, last_name;
    long account_no;
    float balance;
    float amount;

    cout << "***Bank Management System***" << endl;
    do
    {
        cout << "\n\tSelect One Option Below ";
        cout << "\n\t1 Open an Account";
        cout << "\n\t2 Balance Enquiry";
        cout << "\n\t3 Deposit";
        cout << "\n\t4 Withdrawal";
        cout << "\n\t5 Close an Account";
        cout << "\n\t6 Show All Accounts";
        cout << "\n\t7 Quit";
        cout << "\nEnter your choice: ";
        cin >> option;

        switch (option)
        {
        case 1:
            cout << "Enter First name: ";
            cin >> first_name;
            cout << "Enter Last name: ";
            cin >> last_name;
            cout << "Enter Initial balance: ";
            cin >> balance;
            acc = b.Cl_Open_Account(first_name, last_name, balance);
            cout << "Congratulations! Account is Created" << endl;
            cout << acc;
            break;
        case 2:
            cout << "Enter Account Number: ";
            cin >> account_no;
            try
            {
                acc = b.Cl_Balance_Enquiry(account_no);
                cout << "Your Account Details:" << endl;
                cout << acc;
            }
            catch (const char *msg)
            {
                cout << msg << endl;
            }
            break;
        case 3:
            cout << "Enter Account Number: ";
            cin >> account_no;
            cout << "Enter Amount to Deposit: ";
            cin >> amount;
            try
            {
                acc = b.Deposit(account_no, amount);
                cout << "Amount Deposited Successfully!" << endl;
                cout << acc;
            }
            catch (const char *msg)
            {
                cout << msg << endl;
            }
            break;
        case 4:
            cout << "Enter Account Number: ";
            cin >> account_no;
            cout << "Enter Amount to Withdraw: ";
            cin >> amount;
            try
            {
                acc = b.Withdraw(account_no, amount);
                cout << "Amount Withdrawn Successfully!" << endl;
                cout << acc;
            }
            catch (deficient_funds)
            {
                cout << "Insufficient Funds!" << endl;
            }
            catch (const char *msg)
            {
                cout << msg << endl;
            }
            break;
        case 5:
            cout << "Enter Account Number: ";
            cin >> account_no;
            try
            {
                b.CloseAccount(account_no);
                cout << "Account Closed Successfully!" << endl;
            }
            catch (const char *msg)
            {
                cout << msg << endl;
            }
            break;
        case 6:
            b.ShowAllAccounts();
            break;
        case 7:
            cout << "Thank you for using the Bank Management System!" << endl;
            break;
        default:
            cout << "Invalid Option! Please try again." << endl;
        }

    } while (option != 7);

    return 0;
}

Cl_Accounts::Cl_Accounts(string first_name, string last_name, float client_balance)
{
    next_account_no++;
    account_no = next_account_no;
    client_first_name = first_name;
    client_last_name = last_name;
    this->client_balance = client_balance;
}

void Cl_Accounts::Deposit(float amount)
{
    client_balance += amount;
}

void Cl_Accounts::Withdraw(float amount)
{
    if (client_balance - amount < MIN_BALANCE)
        throw deficient_funds();
    client_balance -= amount;
}

void Cl_Accounts::setLastAccountNo(long account_no)
{
    next_account_no = account_no;
}

long Cl_Accounts::getLastAccountNo()
{
    return next_account_no;
}

ofstream &operator<<(ofstream &ofs, Cl_Accounts &acc)
{
    ofs << acc.account_no << endl;
    ofs << acc.client_first_name << endl;
    ofs << acc.client_last_name << endl;
    ofs << acc.client_balance << endl;
    return ofs;
}

ifstream &operator>>(ifstream &ifs, Cl_Accounts &acc)
{
    ifs >> acc.account_no;
    ifs >> acc.client_first_name;
    ifs >> acc.client_last_name;
    ifs >> acc.client_balance;
    return ifs;
}

ostream &operator<<(ostream &os, Cl_Accounts &acc)
{
    os << "First Name: " << acc.get_first_name() << endl;
    os << "Last Name: " << acc.get_last_name() << endl;
    os << "Account Number: " << acc.getAccountNo() << endl;
    os << "Balance: " << acc.getBalance() << endl;
    return os;
}

Bank::Bank()
{
    Cl_Accounts acnt;
    ifstream infile("Bank.data");
    if (!infile)
    {
        cout << "Error in Opening! File Not Found!!" << endl;
        return;
    }
    while (infile >> acnt)
    {
        accounts_cl.insert(pair<long, Cl_Accounts>(acnt.getAccountNo(), acnt));
    }
    Cl_Accounts::setLastAccountNo(acnt.getAccountNo());
    infile.close();
}

Cl_Accounts Bank::Cl_Open_Account(string first_name, string last_name, float balance)
{
    if (balance < MIN_BALANCE)
    {
        throw "Initial balance must be at least 100!";
    }
    Cl_Accounts acnt(first_name, last_name, balance);
    accounts_cl.insert(pair<long, Cl_Accounts>(acnt.getAccountNo(), acnt));
    ofstream outfile("Bank.data", ios::trunc);
    for (auto &entry : accounts_cl)
    {
        outfile << entry.second;
    }
    outfile.close();
    return acnt;
}

Cl_Accounts Bank::Cl_Balance_Enquiry(long account_no)
{
    auto itr = accounts_cl.find(account_no);
    if (itr == accounts_cl.end())
    {
        throw "Account not found!";
    }
    return itr->second;
}

Cl_Accounts Bank::Deposit(long account_no, float amt)
{
    auto itr = accounts_cl.find(account_no);
    if (itr == accounts_cl.end())
    {
        throw "Account not found!";
    }
    itr->second.Deposit(amt);
    return itr->second;
}

Cl_Accounts Bank::Withdraw(long account_no, float amt)
{
    auto itr = accounts_cl.find(account_no);
    if (itr == accounts_cl.end())
    {
        throw "Account not found!";
    }
    itr->second.Withdraw(amt);
    return itr->second;
}

void Bank::CloseAccount(long account_no)
{
    auto itr = accounts_cl.find(account_no);
    if (itr == accounts_cl.end())
    {
        throw "Account not found!";
    }
    cout << "Account Deleted: " << itr->second << endl;
    accounts_cl.erase(account_no);
}

void Bank::ShowAllAccounts()
{
    for (auto &entry : accounts_cl)
    {
        cout << "Account " << entry.first << endl
             << entry.second << endl;
    }
}

Bank::~Bank()
{
    ofstream outfile("Bank.data", ios::trunc);
    for (auto &entry : accounts_cl)
    {
        outfile << entry.second;
    }
    outfile.close();
}
