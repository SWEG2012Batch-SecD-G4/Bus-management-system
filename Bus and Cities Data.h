#include <iostream>
using namespace std;

struct City{
    string name;
    float distFromAa;
    string direction;
};

struct Person{
    string name;
    int id;
    int age;
    string initialCity;
    string destinationCity;
    string update;

};

struct Bus{
    string busDestination;
    int seatAvailable;
};

struct Bank{
    int account;
    float balance;
    int securityCode;

};

struct Ticket{
    int ticketNum;
    string name;
    int id,age, bankAccount;
    string initialCity, destinationCity, eligibility;
    float dist, cost, remBalance;
};


City cities[7] = { {"Jimma", 150, "North"}, {"Mekele", 200, "East"}, {"Gondar", 75, "West"}, {"Harrari", 256, "South"},
                    {"Gambella", 326, "West"}, {"Adigrat", 206, "North"} , {"Sidama", 175, "East"}};
Bus Buses[7] = {{"Jimma", 75}, {"Mekele", 100}, {"Gondar", 100}, {"Harrari", 150},
                {"Gambella", 75}, {"Adigrat", 200} , {"Sidama", 150} };

Person criminals[12];
Bank acc[10];

void criminalsList(){
    for(int i=0; i<12; i++){
    criminals[i].id = 1000 + rand()%(9001);
}
}



void bankInformation() {
    for(int i = 0; i < 10; i++) {
        acc[i].account = 1000 + i;
        acc[i].balance = 1000 + rand()%(9001);
        acc[i].securityCode = 1000 + rand()%(9001);
    }
}



