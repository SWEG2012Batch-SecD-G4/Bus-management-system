#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>

using namespace std;

// bus information container
struct Bus
{
    int bus_dest_cd;
    vector<string>bus_cd;
    vector<int>seatAvailble;
    vector<int>payement;
    vector<string>leaving_time;
};
Bus *bus_rg;
vector <Bus>busInfo_database;

// contains information about city
struct City
{
    string city_name;
    float km_from_AA;
    string direction;
    Bus busDestInfo;
};
City *cities_info;
vector<City> citiesInfo_database;

// login informatino container
struct login
{
    string id, password;
};
login *login_create;
vector <login> loginInfo_database;

// variables
int cityNo_count = 0;

// list of initial cities city and km
vector<string> city ( {"Jimma", "Nakemte", "Bahirdar", "Gambela", "Makelle" });
vector<float> distance_AA ( {25, 50, 100, 30, 10 });
vector <string> direction_AA ( {"north", "south", "west", "east", "north" });
vector <string> l_time ( {"12:00 AM", "6:00 AM", "12:00 PM", "6:00 PM" });

// initial login information for ticketer and administrator
vector<vector<string> > initial_login{{"admin", "password"}, {"ticketer", "password"}};

// ammending bus information
int number_buses = 10;
int number_dest = 5;
int bus_dest_count = 0;

Bus bus_info()
{
    bus_rg = new Bus;
    bus_rg->bus_dest_cd = 100 + bus_dest_count;
    int dest_per_bus = number_buses / number_dest;

    for (int i = 0; i < dest_per_bus; i++)
    {
        char code = 65;
        code += i;
        bus_rg->bus_cd.push_back(to_string(bus_rg->bus_dest_cd) + code);
        bus_rg->leaving_time.push_back(l_time[i]);
        bus_rg->seatAvailble.push_back(100);
        bus_rg->payement.push_back(0);
    }
        bus_dest_count++;
    busInfo_database.push_back(*bus_rg);
    return *bus_rg;
}

// create  destination city;
void destinationCity()
{

    for (int i = 0; i < 5; i++)
    {
        cities_info = new City;
        cities_info->city_name = city[i];
        cities_info->km_from_AA = distance_AA[i];
        cities_info->direction = direction_AA[i];
        cities_info->busDestInfo = bus_info();
        citiesInfo_database.push_back(*cities_info);
        cityNo_count++;

        //release a memory
        delete bus_rg;
        delete cities_info;
    }

    for(int i = 0; i < busInfo_database.size(); i++)
    {
        cout << busInfo_database[i].bus_dest_cd << " ";
        for(int j = 0;  j < 2; j++)
         cout << busInfo_database[i].bus_cd[j] << " " << busInfo_database[i].leaving_time[j] << " " ;
        
        cout << endl;
    }
    system("pause");
}

// shows customer list of cities giving service
int travelling_city()
{
    int city_choice;
    for (int i = 0; i < cityNo_count; i++)
    {
        cout << "[" << i + 1 << "] " << citiesInfo_database[i].city_name << endl;
    }
    cin >> city_choice;
    return city_choice;
}

// INITIAL ACCESS GRANTING
int num_access = 0;
void login_info()
{
    for (int i = 0; i < 2; i++)
    {
        login_create = new login;
        login_create->id = initial_login[i][0];
        login_create->password = initial_login[i][1];
        loginInfo_database.push_back(*login_create);
        num_access++;

        delete login_create; // release a memory
    }
}

// TICKETER PAGE FUNCTIONALITIES
// show lists of all cities and correspoing bus information
void list_cities()
{
    system("cls");
    cout << setw(75) << setfill('_') << "_" << endl;
    cout << "|Name of cities   | Distance in KM from AA "
         << "| Direction from AA | Bus Code |\n";
    for (int i = 0; i < citiesInfo_database.size(); i++)
    {
            cout << setw(75) << setfill('_') << "|" << endl;
            cout << left << setw(10) << setfill(' ') << citiesInfo_database[i].city_name << "\t\t"
                 << left << setw(5) << citiesInfo_database[i].km_from_AA << "\t\t\t  "
                 << left << setw(10) << citiesInfo_database[i].direction << "\t  "
                 << citiesInfo_database[i].busDestInfo.bus_dest_cd << "\t  |" << endl;
    }
    cout << setw(75) << setfill('_') << "_" << endl;
        system("pause");
}

// show buscode, leaving time, and available seat
void showBusInfo()
{
    system("cls");
    cout << "AS = Available seat \n";
    cout << "Bus code | Destination | number of buses | "
         << "Bus 1 AS | Leaving Time | Bus2 AS | Leaving Time \n";

    for (int i = 0; i < busInfo_database.size(); i++)
    {
        cout << " " << left << setw(10) << setfill(' ')
             << busInfo_database[i].bus_dest_cd << "  "
             << left << setw(10) << citiesInfo_database[i].city_name << "\t\t"
             << left << setw(10) << 2 << "   ";

        for (int j = 0; j < 2; j++)
        {
            cout << left << setw(10) << busInfo_database[i].seatAvailble[j]
                 << left << setw(10) << busInfo_database[i].leaving_time[j] << "\t";
        }
        cout << endl;
    }
        system("pause");
}

// ## administrator functionalites
void add_city()
{
    system("cls");
    cities_info = new City;
    cout << "Enter name of new city: ";
    cin >> cities_info->city_name;
    cout << "Enter city distance in km from AA: ";
    cin >> cities_info->km_from_AA;
    cout << "Enter city direction from AA: ";
    cin >> cities_info->direction;

    // appending bus information
    cities_info->busDestInfo = bus_info();
    citiesInfo_database.push_back(*cities_info);
        cityNo_count++;
    cout << "Operation ended successfuly\n";

    delete cities_info; // release a memory;
        system("pause");
}

void remove_city()
{
        system("cls");
    string city_rmv;
    int city_rmv_index;
    bool found_city = false;

    cout << "Enter a city Name to be removed: ";
    cin >> city_rmv;

    for (int i = 0; i < cityNo_count; i++)
    {
        if (city_rmv == citiesInfo_database[i].city_name)
        {
            city_rmv_index = i;
            found_city = true;
        }
    }

    if (found_city)
    {
        // remove city and buses that travels there from the list
        citiesInfo_database.erase(citiesInfo_database.begin()+city_rmv_index);
        busInfo_database.erase(busInfo_database.begin()+city_rmv_index);
        cityNo_count--;
    }
    else 
        cout << "The city you have entered does not exist \n";
            system("pause");
}

//access granting to ticketer by administrator
void create_ticketer_login()
{
        system("cls");
    login_create = new login;
    cout << "Enter ticketer ID: ";
    cin >> login_create->id;
    cout << "Enter ticketer password: ";
    cin >> login_create->password;
    
    loginInfo_database.push_back(*login_create);
    num_access++;
    cout << "Operation ended successfuly \n";\
    delete login_create; // release a memory;
        system("pause");
}