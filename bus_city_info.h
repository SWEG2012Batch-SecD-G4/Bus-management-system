#include <string>
#include <iostream>

using namespace std;

// bus iformation container
struct Bus
{
    int bus_dest_cd;
    string bus_cd[2];
    int seatAvailble[2];
    string leaving_time[4];
};
Bus *bus_rg[100];

// city information container
struct City
{
    string city_name;
    float km_from_AA;
    string direction;
    Bus busDestInfo;
};
City *cities_info[100];

// login informatino container
struct login
{
    string id, password;
};
login *login_create[5];

// variables
int cityNo_count = 0;
int number_buses = 10;
int number_dest = 5;

// list of initial cities city and km
string city[5] = {"Jimma", "Nakemte", "Bahirdar", "Gambela", "Makelle"};
float distance_AA[5] = {25, 50, 100, 30, 10};
string direction_AA[5] = {"North", "South", "West", "East", "North"};
string l_time[4] = {"12:00 AM", "6:00 AM", "12:00 PM", "6:00 PM"};

// initial login information for ticketer and administrator
string initial_login[][2] = {{"admin", "password"}, {"ticketer", "password"}};


// ammending bus information
int bus_dest_count;
Bus bus_info()
{
    bus_rg[bus_dest_count] = new Bus;
    bus_rg[bus_dest_count]->bus_dest_cd = 100 + bus_dest_count;
    int dest_per_bus = number_buses / number_dest;

    for (int i = 0; i < dest_per_bus; i++)
    {
        char code = 65;
        code += i;
        bus_rg[bus_dest_count]->bus_cd[i] = to_string(bus_rg[bus_dest_count]->bus_dest_cd) + code;
        bus_rg[bus_dest_count]->leaving_time[i] = l_time[i];
        bus_rg[bus_dest_count]->seatAvailble[i] = 100;
    }

    return *bus_rg[bus_dest_count];
}

// create initial destination city;
void destinationCity()
{

    for (int i = 0; i < 5; i++)
    {
        cities_info[cityNo_count] = new City;
        cities_info[cityNo_count]->city_name = city[i];
        cities_info[cityNo_count]->km_from_AA = distance_AA[i];
        cities_info[cityNo_count]->direction = direction_AA[i];
        cities_info[cityNo_count]->busDestInfo = bus_info();
        cityNo_count++;
        bus_dest_count++;
    }
}

// list of  cities
int travelling_city()
{
    int city_choice;
    for (int i = 0; i < cityNo_count; i++)
    {
        cout << "[" << i + 1 << "] " << cities_info[i]->city_name << endl;
    }
    cin >> city_choice;
    return city_choice;
}

// Access granting
int num_access;

void login_info()
{
    for (int i = 0; i < 2; i++)
    {
        login_create[num_access] = new login;
        login_create[num_access]->id = initial_login[i][0];
        login_create[num_access]->password = initial_login[i][1];
        num_access++;
    }
}

// add/remove destination city
void add_city()
{
    cities_info[cityNo_count] = new City;
    cout << "Enter name of new city: ";
    cin >> cities_info[cityNo_count]->city_name;
    cout << "Enter city distance in km from AA: ";
    cin >> cities_info[cityNo_count]->km_from_AA;
    cout << "Enter city direction from AA: ";
    cin >> cities_info[cityNo_count]->direction;

    // appending bus information
    cities_info[cityNo_count]->busDestInfo = bus_info();
    cityNo_count++;
}

// removing city from lists
void remove_city()
{

    string city_rmv;
    int city_rmv_index;
    bool found_city = false;

    cout << "Enter a city Name to be removed: ";
    cin >> city_rmv;

    for (int i = 0; i < cityNo_count; i++)
    {
        if (city_rmv == cities_info[i]->city_name)
        {
            city_rmv_index = i;
            found_city = true;
        }
    }

    if (found_city)
    {
        for (int i = city_rmv_index; i < cityNo_count; i++)
            cities_info[i] = cities_info[i + 1];

        delete cities_info[cityNo_count];
        cityNo_count--;
    }
}