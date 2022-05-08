#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<map>

using namespace std;

#define MIN_BALANCE 100  

class deficient_funds{};
class Cl_Accounts{
    private: 
        long account_no;
        string client_first_name;
        string client_last_name;
        float client_balance;
        static long next_account_no; 

    public: 
        Cl_Accounts(){}  //constructor
        Cl_Accounts(string first_name,string last_name,float client_balance);
        
        long getAccountNo(){
            return account_no;
        }

        string get_first_name(){
            return client_first_name;
        }
        string get_last_name(){
            return client_last_name;
        }

        float getBalance(){
            return client_balance;
        }
        
        //flag : operation on the indivial account
        void Deposit(float amount);
        void Withdraw(float amount);
        static void setLastAccountNo(long account_no);
        static long getLastAccountNo(); 

        //flag : understand the frind function 
        friend ofstream & operator<<(ofstream &ofs,Cl_Accounts &acc);
        friend ifstream & operator>>(ifstream &ifs,Cl_Accounts &acc);
        friend ostream & operator <<(ostream &os,Cl_Accounts &acc); 

};

long Cl_Accounts:: next_account_no = 0; 

class Bank{
    private:
        //flag : what is map , and how this is working
        map<long,Cl_Accounts> accounts_cl;
    public: 
        Bank();
        Cl_Accounts Cl_Open_Account(string first_name, string last_name, float balance);
        Cl_Accounts Cl_Balance_Enquiry(long account_no);
        Cl_Accounts Deposit(long account_no, float amt);
        Cl_Accounts Withdraw(long account_no,float amt);

        void CloseAccount(long account_no);
        void ShowAllAccounts(); 
        ~Bank();
};


int main(){
    Bank b;
    Cl_Accounts acc;
    
    int option;
    string first_name,last_name;
    long account_no;
    float balance;
    float amount;

    cout << "***Bank Management System***" << endl;
    do{
        cout<<"\n\tSelect One Option Below ";
        cout<<"\n\t1 Open an Account";
        cout<<"\n\t2 Balance Enquiry";
        cout<<"\n\t3 Deposit";
        cout<<"\n\t4 Withdrawal";
        cout<<"\n\t5 Close an Account";
        cout<<"\n\t6 Show All Accounts";
        cout<<"\n\t7 Quit";
        cout<<"\nEnter your choice: ";
        cin >> option;

        switch(option){
            case 1:
                cout << "Enter First name: "; cin >> first_name;
                cout << "Enter last name: " ; cin >> last_name;
                cout << "Enter Initial balance: "; cin >> balance;
                acc = b.Cl_Open_Account(first_name,last_name,balance);
                cout << "Congratulations Account is Created" << endl;
                cout << acc;
                break;
            case 2: 
                cout << "Enter Account Number: ";
                cin >> account_no;
                acc = b.Cl_Balance_Enquiry(account_no);
                cout << "Yours account Details" << endl;
                cout << acc ;
                break;
            case 3: 
                cout << "Enter Account Number: ";
                cin >> account_no;
                cout << "Enter amount you want to deposit: ";
                cin >> amount;
                acc = b.Deposit(account_no,amount);
                cout << "Your Amount is Deposited" << endl;
                cout << acc;
                break;
            case 4:
                cout<< "Enter Account no : "; cin >> account_no;
                cout << "Enter Amount you want to withdraw : "; cin >> amount;
                acc = b.Withdraw(account_no,amount);
                cout << "Amount withdrawn " << endl;
                cout << acc;
                break;
            case 5: 
                cout << "Enter Account Number: "; cin >> account_no;
                b.CloseAccount(account_no);
                cout << "Account is closed" << endl;
                cout << acc;
                //flag : will there be the break here?
                break;  
            case 6: 
                b.ShowAllAccounts();
                break;
            case 7: 
                break;
            default: 
                cout << "Enter correct choice";
            exit(0);  
        }

    }while(option !=7);

    return 0;
}

Cl_Accounts::Cl_Accounts(string first_name,string last_name,float client_balance){
    next_account_no++;
    account_no = next_account_no;
    client_first_name = first_name;
    client_last_name = last_name;
    this->client_balance = client_balance;
}

void Cl_Accounts::Deposit(float amount){
    client_balance += amount;
}

void Cl_Accounts::Withdraw(float amount){
    if(client_balance - amount < MIN_BALANCE)
        throw deficient_funds();
    client_balance -=amount;
    //flag : understand the throw statement here
}

void Cl_Accounts::setLastAccountNo(long account_no){
    next_account_no = account_no;
}

long Cl_Accounts::getLastAccountNo(){
    return next_account_no;
}

//flag : this is a friend function, how this is working?
ofstream & operator<<(ofstream &ofs,Cl_Accounts &acc){
    ofs << acc.account_no << endl;
    ofs << acc.client_first_name<<endl;
    ofs << acc.client_last_name << endl;
    ofs << acc.client_balance << endl;
    return ofs;
}

ifstream & operator >> (ifstream &ifs, Cl_Accounts &acc){
    ifs >> acc.account_no;
    ifs >> acc.client_first_name;
    ifs >> acc.client_last_name;
    ifs >> acc.client_balance;
    return ifs;
}

ostream & operator<<(ostream &os,Cl_Accounts &acc){
    os << "First Name: " << acc.get_first_name() << endl;
    os << "Last Name: " << acc.get_last_name() << endl;
    os << "Account Number: " << acc.getAccountNo() << endl;
    os << "Balance: " << acc.getBalance() << endl;
    return os;
}


//coding The Bank constructor
Bank::Bank(){
    Cl_Accounts acnt;
    ifstream infile;
    infile.open("Bank.data");
    if(!infile){
        cout << "Error in Opening! File Not Found!!" << endl;
        return;
        //flag : GET IT. checking if the file exists or not.
    }
    while(!infile.eof()){
        infile >>acnt;
        accounts_cl.insert(pair<long,Cl_Accounts>(acnt.getAccountNo(),acnt));
    }

    Cl_Accounts::setLastAccountNo(acnt.getAccountNo());
    infile.close();
}

Cl_Accounts Bank::Cl_Open_Account(string first_name,string last_name,float balance){
    ofstream outfile;
    Cl_Accounts acnt(first_name,last_name,balance);
    accounts_cl.insert(pair<long,Cl_Accounts>(acnt.getAccountNo(),acnt));
    outfile.open("Bank.data",ios::trunc);
    map<long,Cl_Accounts>::iterator itr;
    for(itr=accounts_cl.begin(); itr!=accounts_cl.end();itr++){
        outfile<<itr->second;
    }
    outfile.close();
    return acnt;
}


Cl_Accounts Bank::Cl_Balance_Enquiry(long account_no){
    map<long,Cl_Accounts>::iterator itr=accounts_cl.find(account_no);
    return itr->second;
}

Cl_Accounts Bank::Deposit(long account_no, float amt){
    map<long,Cl_Accounts>::iterator itr=accounts_cl.find(account_no);
    itr->second.Deposit(amt);
    return itr->second;
}

Cl_Accounts Bank::Withdraw(long account_no,float amt){
    map<long,Cl_Accounts>::iterator itr=accounts_cl.find(account_no);
    itr->second;
}

void Bank::CloseAccount(long account_no){
    map<long,Cl_Accounts>::iterator itr = accounts_cl.find(account_no);
    cout << "Account Deleted" << itr->second;
    accounts_cl.erase(account_no);
}

void Bank::ShowAllAccounts(){
    map<long,Cl_Accounts>::iterator itr;
    for(itr=accounts_cl.begin(); itr!=accounts_cl.end();itr++){
        cout << "Account " << itr->first<<endl<<itr->second<<endl;
    }
}

Bank::~Bank(){
    ofstream outfile;
    outfile.open("Bank.data",ios::trunc);
    map<long,Cl_Accounts>::iterator itr;
    for(itr=accounts_cl.begin(); itr!=accounts_cl.end();itr++){
        outfile<<itr->second;
    }
    outfile.close();
}

