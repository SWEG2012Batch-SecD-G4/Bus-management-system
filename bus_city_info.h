#include <string>
#include <iostream>

using namespace std;

struct Bus
{
    int bus_dest_cd;
    string bus_cd[2];
    int seatAvailble[2];
    string leaving_time[4];
};
Bus *bus_rg[100];

struct City
{
    string dest_name;
    float km_from_AA;
    string direction;
    Bus busDestInfo;
};
City *Destination[100], *startingCity[100];

// variables
int counter = 0;
    int number_buses = 10;
    int number_dest = 5;

// initial_destination city and km
string city[5] = {"Jimma", "Nakemte", "Bahirdar", "Gambela", "Makelle"};
float distance_AA[5] = {25, 50, 100, 30, 10};
string direction_AA[5] = {"North", "South", "West", "East", "North"};
string l_time[4] = {"12:00 AM", "6:00 AM", "12:00 PM", "6:00 PM"};

// list of destination city
int travelling_city()
{
    int city_choice;
    for (int i = 0; i < 5; i++)
    {
        cout << "[" << i + 1 << "] " << city[i] << endl;
    }
    cin >> city_choice;
    return city_choice;
}

// returns structure
Bus bus_info()
{
    // bus_rg[counter] = new Bus;
    int value = 0;
    bus_rg[counter] = new Bus;
    bus_rg[counter]->bus_dest_cd = 100 + counter;
    int dest_per_bus = number_buses / number_dest;

    for (int i = 0; i < dest_per_bus; i++)
    {
        char code = 65;
        code += i;
        bus_rg[counter]->bus_cd[i] = to_string(bus_rg[counter]->bus_dest_cd) + code;
        bus_rg[counter]->leaving_time[i] = l_time[i];
        bus_rg[counter]->seatAvailble[i] = 100;
    }

    return *bus_rg[counter];
}

// create  destination city;
void destinationCity()
{

    for (int i = 0; i < 5; i++)
    {
        Destination[counter] = new City;
        Destination[counter]->dest_name = city[i];
        Destination[counter]->km_from_AA = distance_AA[i];
        Destination[counter]->direction = direction_AA[i];
        Destination[counter]->busDestInfo = bus_info();
        counter++;
    }
}

// create initial starting city
void starting_city()
{
    for (int i = 0; i < 5; i++)
    {
        startingCity[i] = new City;
        startingCity[i]->dest_name = city[i];
        startingCity[i]->km_from_AA = distance_AA[i];
        startingCity[i]->direction = direction_AA[i];
    }
}
