//Customers Section
#include <iostream>
#include <string.h>
#include <string>
#include <math.h>
#include "Bus and Cities Data.h"

using namespace std;

void menu();
void customerService(City c[], Person P);
void destinations(City cities[]);
string checkEligibility(Person p);
float calcDistance(Person y, City cities[]);
float calcPayment(float amount, float distance, float discount);
void makePayment(Person x, float payment, float distance);
void ticketAndReciept(Person x, float distance, float total, float rem);
void updateInfo();
void checkTicket();
void information();
void ticketAdministration();
float discount(int numofTickets, Person p);

int ticketCounter = 0, remBal;
Ticket t[500];

int main(){


    criminalsList();
    bankInformation();



    cout << "WELCOME TO OUR BUS AND TICKET RESERVATION SYSTEM\n";
    menu();

    return 0;
}

void menu(){
    Person p;
    int choice;

//    cout << counter << endl << endl;
    do{
        for(int i=0; i<ticketCounter; i++){
        cout << t[i].ticketNum << endl;
        }
        cout << "\nMENU " << endl;
        cout << "[1] Get a ticket " << endl;
        cout << "[2] Update Your Reservation " << endl;
        cout << "[3] Check your Reservation(Ticket)" << endl;
        cout << "[4] Information" << endl;
        cout << "[0] to exit" << endl;
        cout << "Choose: ";
        cin >> choice;
        switch(choice){
        case 0:
            exit(1);
        case 1:
            customerService(cities, p);
            break;
        case 2:
            if(ticketCounter == 0){
                cout << "\nNo Reservations have been made yet!" << endl;
            }
            else
                updateInfo();
            break;
        case 3:
            if(ticketCounter == 0){
                cout << "\nNo Reservations have been made yet!" << endl;
            }
            else
                checkTicket();
            break;
        case 4:
            information();


        default:

            cout << "Invalid Please Try Again!" << endl;
        }

    }while(choice != 0);

}


void customerService(City c[], Person p){

    float dist, numOfTickets, totalPayment, disc;
    int choice;
    string eligibility;



    system("cls");
    cout << "PLEASE FILL THE REQUIRED INFORMATIONS " << endl << endl;
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

    disc = discount(numOfTickets, p);
    totalPayment = calcPayment(numOfTickets, dist, disc);

    system("cls");

    cout << "The distance from you starting point to you destination is " << dist << " kms."<< endl;
    cout << "The discount for " << numOfTickets << " tickets is " << disc << endl;
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

float calcPayment(float amount, float distance, float discount){
    float payPerKm = 10, totalpayment;
    totalpayment = payPerKm * distance * amount * discount;

    return totalpayment;

}

void makePayment(Person x, float payment, float distance){
    int choice, i=0;
    int tries = 0;
    Bank user;
    bool checkAccID = false, checkAccPass;

    system("cls");
    cout << "PAYMENT MENU " << endl;
    cout << "[1] CBE Account" << endl;
    cout << "Choose your preferable payment method: ";
    cin >> choice;

    if(choice == 1){
        system("cls");
        loop:
        cout << "Account Number: ";
        cin >> user.account;

        for(i=0; i<10; i++){
            if(user.account == acc[i].account){
                checkAccID = true;
                break;
            }
        }

        if(checkAccID){
                loop2:
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
            goto loop;

        }


        if(checkAccPass){
                cout << "Login Successful!" << endl;
                if(payment == acc[i].balance || payment < acc[i].balance){
                    system("cls");
                    cout << "Payment Successful!";
                    acc[i].balance -= payment;
                    cout << "You current balance is now " << acc[i].balance << endl;
                    if(x.update == "yes"){
                        remBal = acc[i].balance;
                    }
                    else{
                        ticketAndReciept(x, distance, payment, acc[i].balance);
                    }
                }
                else{
                    system("cls");
                    cout << "Sorry but your balance is insufficient right now. Try again later.\n";
                    menu();
                }
        }

        else{
                cout << "Wrong Password!" << endl;
                tries++;
                if(tries <= 3){
                    goto loop2;
                }
                else{
                    cout << "Too many attempts!" << endl;
                    exit(1);
                }
            }
    }
    else{
        cout << "Invalid! Please Try Again" << endl;
        goto loop;
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
    cout << "your ticket number is tck-" << ticketCounter << endl;
    cout << "***************************" << endl << endl;

    t[ticketCounter].ticketNum = ticketCounter;
    t[ticketCounter].name = x.name;
    t[ticketCounter].id = x.id;
    t[ticketCounter].initialCity = x.initialCity;
    t[ticketCounter].destinationCity = x.destinationCity;
    t[ticketCounter].eligibility = checkEligibility(x);
    t[ticketCounter].dist = distance;
    t[ticketCounter].cost = total;
    t[ticketCounter].remBalance = rem;

    ticketCounter++;
    menu();

};

void updateInfo(){
    int ticketNum, choice, id, numOfTickets, choice2;
    Person x;
    float dist, totalPayment, disc;
    loop:
    cout << "Enter your ticket number tck-";
    cin >> ticketNum;
    cout << "Enter the id you registered with: ";
    cin >> id;


    if(t[ticketNum].id == id){
        system("cls");
        cout << "Your ticket is found!" << endl;
        cout << "\nWhat do you want to change: " << endl;
        cout << "[1] Personal Information" << endl;
        cout << "[2] Travel Information" << endl;
        cout << "[3] Full Information (Personal and Travel)" << endl;
        cout << "[4] Cancel Reservation" << endl;
        cout << "Choice: ";
        cin >> choice;
        switch(choice){
        case 1:
            system("cls");
            cout << "Enter your name: ";
            cin >> t[ticketNum].name;
            cout << "Enter your Kebelle ID: ";
            cin >> t[ticketNum].id;
            cout << "Enter your age: ";
            cin >> t[ticketNum].age;
            cout << "Your information has been updated successfully!" << endl;
            menu();

        case 2:
            system("cls");
            cout << "Select Your starting point: ";
            cin >> x.initialCity;
            cout << "Select your Destination point: ";
            cin >> x.destinationCity;

            dist = calcDistance(x, cities);
            cout << "How many tickets do you want: ";
            cin >> numOfTickets;
            disc = discount(numOfTickets, x);
            totalPayment = calcPayment(numOfTickets, dist, disc);
            system("cls");

            cout << "\nThe distance from you starting point to you destination is " << dist << " kms."<< endl;
            cout << "The discount for " << numOfTickets << " tickets is " << disc << endl;
            cout << "Your payment would be " << totalPayment << " birr do you want to continue: ";
            cout << "\n[1]Yes \n[2]No \n";
            cin >> choice2;
            switch(choice2){
            case 1:
                x.update = "yes";
                makePayment(x,totalPayment, dist);
                break;
            case 2:
                cout << "Reservation Canceled!\n" << endl;
                break;
            default:
                cout << "Invalid! Please Try Again" << endl;
            }

            t[ticketNum].initialCity = x.initialCity;
            t[ticketNum].destinationCity = x.destinationCity;
            t[ticketNum].dist = dist;
            t[ticketNum].cost = totalPayment;
            t[ticketNum].remBalance = remBal;

            cout << "Your information has been updated successfully!" << endl;
            menu();

            break;

        case 3:

            system("cls");
            cout << "Enter your name: ";
            cin >> t[ticketNum].name;
            cout << "Enter your Kebelle ID: ";
            cin >> t[ticketNum].id;
            cout << "Enter your age: ";
            cin >> t[ticketNum].age;
            cout << "Select Your starting point: ";
            cin >> x.initialCity;
            cout << "Select your Destination point: ";
            cin >> x.destinationCity;

            dist = calcDistance(x, cities);
            cout << "How many tickets do you want: ";
            cin >> numOfTickets;
            disc = discount(numOfTickets, x);
            totalPayment = calcPayment(numOfTickets, dist, disc);
            system("cls");

            cout << "\nThe distance from you starting point to you destination is " << dist << " kms."<< endl;
            cout << "The discount for " << numOfTickets << " tickets is " << disc << endl;
            cout << "Your payment would be " << totalPayment << " birr do you want to continue: ";
            cout << "\n[1]Yes \n[2]No \n";
            cin >> choice2;
            switch(choice2){
            case 1:
                x.update = "yes";
                makePayment(x,totalPayment, dist);
                break;
            case 2:
                cout << "Reservation Canceled!\n" << endl;
                break;
            default:
                cout << "Invalid! Please Try Again" << endl;
            }

            t[ticketNum].initialCity = x.initialCity;
            t[ticketNum].destinationCity = x.destinationCity;
            t[ticketNum].dist = dist;
            t[ticketNum].cost = totalPayment;
            t[ticketNum].remBalance = remBal;

            cout << "Your information has been updated successfully!" << endl;
            menu();

            break;
        case 4:

            t[ticketNum].ticketNum = 0;
            t[ticketNum].name = "NULL";
            t[ticketNum].id = 0;
            t[ticketNum].initialCity = "NULL";
            t[ticketNum].destinationCity = "NULL";
            t[ticketNum].eligibility = "NULL";
            t[ticketNum].dist = 0;
            t[ticketNum].cost = 0;
            t[ticketNum].remBalance = 0;
            cout << "Your Reservation has been canceled successfully!" << endl;
            menu();

        default:
            cout << "Invalid! Please Try Again" << endl;
        }
    }
    else{
        cout << "You have entered a wrong ticket number or id. Try Again!" << endl;
        goto loop;
    }

}

void checkTicket(){
    int ticketNum, id;
    system("cls");

    cout << "Enter your ticket number tck-";
    cin >> ticketNum;
    cout << "Enter the id you registered with: ";
    cin >> id;

    if(t[ticketNum].id == id){
        cout << "\n\nYour Ticket Information" << endl << endl;
        cout << "***************************" << endl;
        cout << "Name: " << t[ticketNum].name << endl;
        cout << "ID: " << t[ticketNum].id << endl;
        cout << "Initial City: " << t[ticketNum].initialCity << endl;
        cout << "Destination City: " << t[ticketNum].destinationCity << endl;
        cout << "Eligibility: " << t[ticketNum].eligibility << endl;
        cout << "Distance you will travel: " << t[ticketNum].dist << "Kms" << endl;
        cout << "Total Payment: " << t[ticketNum].cost << " Birr" << endl;
        cout << "your remaining balance in your account: " << t[ticketNum].remBalance << " Birr" << endl;
        cout << "your ticket number is tck-" << t[ticketNum].ticketNum << endl;
        cout << "***************************" << endl << endl;

        menu();
    }
    else{
        cout << "Incorrect Ticket Number or Registration ID." << endl;
        menu();
    }


}

void information(){
    system("cls");
    cout << "CUSTOMER INFORMATION\n";
    cout << "- You can reserve a seat for your travel by choosing get a ticket option from the menu" << endl;
    cout << "- You will need to be of legal age in order to get a ticket for travel" << endl;
    cout << "- You can change any information you want after reserving a seat using your ticket number (tck-'x') to login" << endl;
    cout << "- Payment for a ticket can be done with a CBE Bank account" << endl;

}

void administration(){
    int choice, busCounter = 0;
    Bus newBuses[100];

    cout << "\nMENU " << endl;
    cout << "[1] Add a new bus to a destination " << endl;
    cout << "[2] The number of seats left for a destination " << endl;
    cout << "[3] Get all the ticket information so far " << endl;
    cout << "[4] How much money is gained so far" << endl;
    cout << "Choose: ";
    cin >> choice;

    switch(choice){
    case 1:
        cout << "Enter the destination of bus: ";
        cin >> newBuses[busCounter].busDestination;
        cout << "Enter the number of seats for the bus: ";
        cin >> newBuses[busCounter].seatAvailable;
        busCounter++;
        break;
    case 2:


            updateInfo();
        break;
    case 3:


            checkTicket();
        break;
    case 4:
        information();


    default:

        cout << "Invalid Please Try Again!" << endl;
    }



}

float discount(int numofTickets, Person p){
    int numOfTravel = 0;
    float discount;
    for(int i=0; i<ticketCounter; i++){
        if(p.id == t[i].id){
            numOfTravel++;
        }
    }

    if(numOfTravel = 0){
        if(numofTickets > 2){
            discount = 0.8;
            cout << "found 0" << endl;
        }
        else
            discount = 1;
    }
    else if(numOfTravel = 1){
        if(numofTickets > 2){
            cout << "found 1" << endl;
            discount = (0.8 * 0.9);
        }
        else
            discount = 0.9;
    }

    else if(numOfTravel > 1){
        if(numofTickets > 2){
            discount = 0.8 * 1.25 * sqrt((1/numOfTravel));
            cout << "found > 1 and 2" << endl;
        }
        else
            discount = 1.25 * sqrt((1/numOfTravel));
            cout << "found > 1 and 2" << endl;
    }

    return discount;

}









