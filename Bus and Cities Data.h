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
    int busCode;
    int busnumber;
    int seatAvailble;
};

struct Bank{
    int account;
    float balance;
    int securityCode;

};

struct Ticket{
    int ticketNum;
    string name;
    int id,age;
    string initialCity, destinationCity, eligibility;
    float dist, cost, remBalance;
};


City cities[7] = { {"Jimma", 150, "North"}, {"Mekele", 200, "East"}, {"Gondar", 75, "West"}, {"Harrari", 256, "South"},
                    {"Gambella", 326, "West"}, {"Adigrat", 206, "North"} , {"Sidama", 175, "East"}};
Bus Buses[5] = { {10, 0001 ,75}, {11, 0002, 100}, {12, 0003, 100}, {13, 0004, 150}, {10, 0005, 75} };

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



