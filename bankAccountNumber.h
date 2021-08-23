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

account user[10];

// creates account for  10 user
void bankInformation() {
    for(int i = 0; i < 10; i++) {
            user[i].name = " ";
    user[i].account = 1000 + i;
    user[i].balance = 1000;
    user[i].securityCode = 1000 + rand()%(9001);
    cout << user[i].securityCode << endl;
    }
}

/* checks whether the customer have enough balance  and provided 
correct security code and account Number to reserve a seat */
bool accountCheck(float payement, int account, int securityCode ) {
     bool isExist = false;
    for(int i = 0; i < 10; i++)
        if((user[i].account==account && user[i].balance > payement) && (user[i].securityCode==securityCode)){
            isExist = true;
            user[i].balance -=payement;
        }

    return isExist;
}