#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;
struct account
{
    string name;
    int account;
    float balance;
    int securityCode;
};

account *user[10];
void balance_manage(int i, float payement, bool reserve_or_cancel = true);

// random number generator;
int random_balance[10] = {1041, 1465, 7334, 9498, 2167, 7723, 3477, 3355, 9960, 7462};
int random2[10] = {};
int random1[10] = {};

void random_generator(int random_assign[10])
{
    for (int i = 0; i < 10; i++)
    {
        int random_number = 1000 + rand() % (9001);
        random_assign[i] = random_number;
    }
};
// creates account for  10 user
void bankInformation()
{
    for (int i = 0; i < 10; i++)
    {
        user[i] = new account;
        user[i]->name = " ";
        user[i]->account = 1000 + i;
        cout << user[i]->account << " ";
        user[i]->balance = random1[i];
        cout << user[i]->balance << " ";
        user[i]->securityCode = random2[i];
        cout << "Code " << user[i]->securityCode << endl;
    }
}

// to see changes to customer bank account;
void show_bank_information() {
    for(int i = 0; i < 10; i++) {
        cout << user[i]->balance << endl;
    }
}


/* checks whether the customer have enough balance  and provided 
correct security code and account Number to reserve a seat */
bool accountCheck(float payement, int account, int securityCode, bool txn_status)
{
    bool success_txn = false;
    bool is_found;
    int acc_index;

    // checks wether the account number and password exists;
    for (int i = 0; i < 10; i++)
    {
        if ((user[i]->account == account) && (user[i]->securityCode == securityCode))
        {
            acc_index = i;
            is_found = true;
        }
    }

    // if the account is found
    if (is_found)
    {
        if (txn_status) // if the status is reservation
        {
            if (user[acc_index]->balance > payement)
            {
                user[acc_index]->balance -= payement;
                success_txn = true;
            }
            else
            {
                cout << "No Sufficient balance \n";
                success_txn = false;
            }
        }
        else // if the status is cancelling reservation
        {
            user[acc_index]->balance += payement;
            success_txn = true;
        }
    }
    else
    {
        cout << "The Account Number or password is not correct \n";
        success_txn = false;
    }
    return success_txn;
}