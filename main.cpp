//Customers Section
#include <iostream>
#include <math.h>
#include "Bus and Cities Data.h"

using namespace std;

void customerService(City c[], Person P);
void destinations(City cities[]);
string checkEligibility(Person p);
float calcDistance(Person y, City cities[]);
float calcPayment(float amount, float distance);
void makePayment(Person x, float payment, float distance);
void ticketAndReciept(Person x, float distance, float total, float rem);


int main(){
    Person p;
    int choice;

    criminalsList();
    bankInformation();

    cout << "WELCOME TO OUR BUS AND TICKET RESERVATION SYSTEM\n\n";

    do{
        cout << "MENU " << endl;
        cout << "[1] Get a ticket " << endl;
        cout << "[0] to exit" << endl;
        cin >> choice;
        switch(choice){
        case 1:
            customerService(cities, p);
            break;
        default:
            if(choice!=0)
            cout << "Invalid Please Try Again!" << endl;
        }

    }while(choice != 0);

    return 0;
}

void customerService(City c[], Person p){

    float dist;
    float numOfTickets, totalPayment;
    int choice;
    string eligibility;



    system("cls");
    cout << "PLEASE FILL YOUR INFORMATIONS REUIRED" << endl << endl;
    cout << "Enter your name: ";
    cin >> p.name;
    cout << "Enter your Kebelle ID: ";
    cin >> p.id;
    cout << "Enter your age: ";
    cin >> p.age;

    eligibility = checkEligibility(p);
    if(eligibility == "Ineligible"){
        cout << "Sorry but you are not eligible to travel!" << endl;
        exit(1);
    }

    destinations(c);

    cout << "\nSelect Your starting point: ";
    cin >> p.initialCity;
    cout << "Select your Destination point: ";
    cin >> p.destinationCity;

    dist = calcDistance(p, c);

    cout << "How many tickets do you want: ";
    cin >> numOfTickets;
    totalPayment = calcPayment(numOfTickets, dist);
    system("cls");


    cout << "\nThe distance from you starting point to you destination is " << dist << " kms."<< endl;
    cout << "Your payment would be " << totalPayment << " birr do you want to continue: ";
    cout << "\n[1]Yes \n[2]No \n";
    cin >> choice;
    switch(choice){
    case 1:
        makePayment(p,totalPayment, dist);
        break;
    case 2:
        cout << "Reservation Canceled!\n" << endl;
        break;
    default:
        cout << "Invalid! Please Try Again" << endl;
    }

}

void destinations(City city[]){
    cout << "\nLIST OF OUR CURRENT DESTINATIONS: \n";
    for(int i=0; i<7; i++){
        cout << "Destinations " << i+1 << " : " << city[i].name << endl;
    }

}

string checkEligibility(Person p){

    for(int i=0; i<12; i++){
        if(p.id == criminals[i].id || p.age <= 18){
            return "Ineligible";
            break;
        }
    }

    return "Eligible";
}

float calcDistance(Person y, City cities[]){
    float distance;
    float x1, x2, sum;
    string initial, destination;

    //Calculating the distance for different cases
    for(int i=0; i<7; i++){
        if(y.initialCity == cities[i].name){
            x1 = cities[i].distFromAa;
            initial = cities[i].direction;
        }
        if(y.destinationCity == cities[i].name){
            x2 = cities[i].distFromAa;
            destination = cities[i].direction;
        }
    }

    if(y.initialCity == y.destinationCity){
        distance = (x2 - x1);
        if(distance < 0){
            distance = (-1)*(distance);
        }
    }

    if(y.initialCity != y.destinationCity){
        if((initial == "North" && destination == "South") || (initial == "South" && destination == "North") ||
           (initial == "East" && destination == "West") || (initial == "West" && destination == "East") ) {

            distance = (x2 + x1);
        }
        else{
            sum = pow(x1, 2) + pow(x2, 2);
            distance = sqrt(sum);
        }


    }



    return distance;

}

float calcPayment(float amount, float distance){
    float payPerKm = 10, totalpayment;
    totalpayment = payPerKm * distance * amount;

    return totalpayment;

}

void makePayment(Person x, float payment, float distance){
    int choice, i=0;
    Bank user;
    bool checkAccID = false, checkAccPass;

    system("cls");
    cout << "PAYMENT MENU " << endl;
    cout << "[1] CBE Account" << endl;
    cout << "Choose your preferable payment method: ";
    cin >> choice;

    if(choice == 1){
        system("cls");

        cout << "Account Number: ";
        cin >> user.account;

        for(i=0; i<10; i++){
            if(user.account == acc[i].account){
                checkAccID = true;
                break;
            }
        }

        if(checkAccID){
                cout << "Password: ";
                cin >> user.securityCode;

                if(user.securityCode == acc[i].securityCode){
                    checkAccPass = true;
                }
                else{
                    checkAccPass = false;
                }
        }
        if(!checkAccID){
            cout << "The account you entered was not found." << endl;
            exit(1);

        }


        if(checkAccPass){
                cout << "Login Successful!" << endl;
                if(payment == acc[i].balance || payment < acc[i].balance){
                    system("cls");
                    cout << "Payment Successful!";
                    acc[i].balance -= payment;
                    cout << "You current balance is now " << acc[i].balance << endl;

                    ticketAndReciept(x, distance, payment, acc[i].balance);
                }
                else{
                    system("cls");
                    cout << "Sorry but your balance is insufficient right now. Try again later.\n";
                    exit(1);
                }
        }

        else{
                cout << "Wrong Password!" << endl;
                exit(1);
            }

    }
    else{
        cout << "Invalid! Please Try Again" << endl;
        exit(1);
    }

}

void ticketAndReciept(Person x, float distance, float total, float rem){

    cout << "\nCongratulations! You have successfully made a reservation. Have a nice Trip! " << endl << endl;
    cout << "Your Reciept\n";
    cout << "***************************" << endl;
    cout << "Name: " << x.name << endl;
    cout << "ID: " << x.id << endl;
    cout << "Initial City: " << x.initialCity << endl;
    cout << "Destination City: " << x.destinationCity << endl;
    cout << "Eligibility: " << checkEligibility(x) << endl;
    cout << "Distance you will travel: " << distance << "Kms" << endl;
    cout << "Total Payment: " << total << " Birr" << endl;
    cout << "your remaining balance in your account: " << rem << " Birr" << endl;
    cout << "***************************" << endl << endl;

}





