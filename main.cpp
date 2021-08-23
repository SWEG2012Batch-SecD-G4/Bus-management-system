#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <cmath>
#include "bankAccountNumber.h"
#include "bus_city_info.h"

using namespace std;

struct reserve
{
    string fname, lname, fullName;
    string destination, initial_city;
    int payement;
    int accountNumber;
    int securityNumber;
    int resrvd_seat;
    int ticket_size;
    int return_oneWay;
    float travelling_distance;
    string resrvd_bus;
    string leaving_time;
    bool is_reserverd;
};
reserve *resrvd_acc[100];


// list of functions
void list_cities(City *[]);
void showBusInfo(); 
void reserveSeat();
float distance_calculator(int, int);
bool bus_assignment(int, int, reserve *[]);
float payement_calculator(int, reserve *[]);
void confirm_resrv(int);
void receipt(int);

int first_ui();
int cust_first_ui();
void respond_cust_request();
int search_destination();

// global Variables;
int resrv_counter = 0;

int main()
{
    bankInformation(); // a function that calls Bank information of a customer from bankAccountNumber.h library
    destinationCity();  // calling destination city function from bus_city_info.h
    list_cities(Destination);  // showing all cities and bus that travels there
    showBusInfo();  //  showing individual bus information
    starting_city();  // list of cities that customer can travel from
    first_ui();      // first user interface of the program(home page)
}

// Home page of the software
int first_ui()
{
    cout << right << setw(10) << "Welcome to Bus X reservation system\n";
    cout << "[1] Enter as customer \n"
         << "[2] Login as Ticketer \n"
         << "[3] Login as Administrator \n";
    int choice;
    cin >> choice;
    bool do_not_exit = true;

    while (do_not_exit)
    {
        switch (choice)
        {
        case 1:
            respond_cust_request();
            break;
        case 2:
            // ticketer_page();
            break;
        case 3:
            //administrator_page();
            break;

        default:
            do_not_exit = false;
            break;
        }
    }
}

// homepage for customer
int cust_first_ui()
{
    cout << "Welcome to CompanyX Bus Reservation System \n"
         << "[1] Search destination\n"
         << "[2] Make Reservation \n"
         << "[3] See Your Reservation \n"
         << "[4] Home page\n";

    int option;
    cin >> option;
    return option;
}

void respond_cust_request()
{
    bool do_not_exit = true;
    int option;
    while (do_not_exit)
    {
        option = cust_first_ui();

        switch (option)
        {
        case 1:
            search_destination();
            break;
        case 2:
            reserveSeat();
            break;
        case 3:
            //show_reservation();
            break;
        case 4:
            first_ui();
            break;

        default:
            do_not_exit = false;
            break;
        }
    }
}

// searching destination
int search_destination()
{
    cout << "Enter name of the city: ";
    string city_name;
    cin >> city_name;

    for (int i = 0; i < 5; i++)
    {
        // if the city the customer searches are on the destination name
        if (city_name == Destination[i]->dest_name)
        {
            cout << "Name: " << Destination[i]->dest_name << endl
                 << "Distance from AA: " << Destination[i]->km_from_AA << endl
                 << "Direction from AA: " << Destination[i]->direction << endl
                 << "Leaving Time: ";
            for (int j = 0; j < 2; j++)
            {
                cout << Destination[i]->busDestInfo.leaving_time[j] << " ";
            }

            cout << "\nAvailable: ";
            if (Destination[i]->busDestInfo.seatAvailble > 0)
                cout << "Yes\n";
            else
                cout << "No\n";
        } else cout << "No such city recorded on our database\n";
    }
}

// reserve seat
void reserveSeat()
{
    // create a new reserve everytime this function is called
    resrvd_acc[resrv_counter] = new reserve;

    cout << "Enter Name: ";
    cin >> resrvd_acc[resrv_counter]->fname;

    // travelling city information;
    cout << "Choose starting Point: ";
    int startingPoint = travelling_city() - 1;
    cout << "Choose Destination City: ";
    int destination = travelling_city() - 1;

    // calculating distance between starting city and destination city;
    // checks whether customer enters the same name at both destination and starting city
    if (startingPoint != destination)
    {
        // assign a city to customer information
        resrvd_acc[resrv_counter]->destination = city[destination];
        resrvd_acc[resrv_counter]->initial_city = city[startingPoint];

        resrvd_acc[resrv_counter]->travelling_distance = distance_calculator(destination, startingPoint);
    }
    else
        cout << "No inside service \n";

    cout << "Choose Travelling option \n"
         << "[1] One Way \n"
         << "[2] Return: ";
    cin >> resrvd_acc[resrv_counter]->return_oneWay;
    cout << "Number of tickets: ";
    cin >> resrvd_acc[resrv_counter]->ticket_size;

    // assigning bus to a customer 
    // bus_assignment also checks if there's avaible seat 
    bool bus_available = bus_assignment(destination, resrv_counter, resrvd_acc);
    if (bus_available)
    {
        // Bank Account Information;
        cout << "Enter account: ";
        cin >> resrvd_acc[resrv_counter]->accountNumber;
        cout << "Enter security Code: ";
        cin >> resrvd_acc[resrv_counter]->securityNumber;

        // calculates total payement;
        float payement = payement_calculator(resrv_counter, resrvd_acc);
        resrvd_acc[resrv_counter]->payement = payement;

        // confirm payement and reservation;
        confirm_resrv(resrv_counter);
        cout << "Do you want to continue \n (Y\\N)";
        char confirm;
        cin >> confirm;
        confirm = tolower(confirm);

        if (confirm == 'y')
        {
            // check your payement information from banks
            // if the customer have balance that allows him to reserve a seat success will be true.
            bool success = accountCheck(resrvd_acc[resrv_counter]->payement,
                                        resrvd_acc[resrv_counter]->accountNumber,
                                        resrvd_acc[resrv_counter]->securityNumber);
            if (success)
            {
                resrvd_acc[resrv_counter]->resrvd_seat = 1 + resrv_counter;
                receipt(resrv_counter);
                resrv_counter++;
            }
            else
            {   /* if customer does provide accountNumber that does not exist, 
                    does not have enough balance in the account, and 
                    haven't not provided correct security code, cancel the reservation
                 */
                
                delete resrvd_acc[resrv_counter];
                cout << "Transaction was not successful \n"
                     << "Please check your bank information \n";
            }
        }
        else
        {
            // if the customer do not want to continue cancle reservation
            delete resrvd_acc[resrv_counter];
            cout << "Request canceled \n";
        }
    }
}

// distance calculator
float distance_calculator(int destination, int startingPoint)
{
    float distance_km;
    // if the two cities are on the same direction
    if (Destination[destination]->direction == startingCity[startingPoint]->direction)
    {
        bool dist_check = Destination[destination]->km_from_AA >
                          startingCity[startingPoint]->km_from_AA;
        if (dist_check)
        {
            distance_km = (Destination[destination]->km_from_AA -
                           startingCity[startingPoint]->km_from_AA);
        }
        else
        {
            distance_km = (startingCity[startingPoint]->km_from_AA -
                           Destination[destination]->km_from_AA);
        }
    }
    else // if the two cities are on different direction;
    {
        cout << "Choose path: "
             << "[1] Through Addis Ababa \n"
             << "[2] Direct way \n";
        int option;
        cin >> option;
        switch (option)
        {
        case 1:
        {
            distance_km = (Destination[destination]->km_from_AA +
                           startingCity[startingPoint]->km_from_AA);
            break;
        }
        case 2:
        {
            distance_km = sqrt(pow(Destination[destination]->km_from_AA, 2) +
                               pow(startingCity[startingPoint]->km_from_AA, 2));
            break;
        }
        default:
            break;
        }
    }
    return distance_km;
}

// assignning bus to a customer;
bool bus_assignment(int destination, int resrv_counter, reserve *resrvd_acc[])
{
    if (bus_rg[destination]->seatAvailble[0] > 0)
    {
        resrvd_acc[resrv_counter]->resrvd_bus = bus_rg[destination]->bus_cd[0];
        resrvd_acc[resrv_counter]->leaving_time = l_time[0];
        bus_rg[destination]->seatAvailble[0]--;
        return true;
    }
    else if ((bus_rg[destination]->seatAvailble[0] == 0) &&
             bus_rg[destination]->seatAvailble[1] > 0)
    {
        resrvd_acc[resrv_counter]->resrvd_bus = bus_rg[destination]->bus_cd[1];
        resrvd_acc[resrv_counter]->leaving_time = l_time[1];
        bus_rg[destination]->seatAvailble[1]--;
        return true;
    }
    else
    {
        cout << "NO available seat \n";
        return false;
    }
}

// calculating payement;
float payement_calculator(int resrv_counter, reserve *resrvd_acc[])
{

    float payement = resrvd_acc[resrv_counter]->return_oneWay *
                     resrvd_acc[resrv_counter]->ticket_size *
                     resrvd_acc[resrv_counter]->travelling_distance * 10;
    return payement;
}

// confirm reservation
void confirm_resrv(int i)
{
    cout << "Name: " << resrvd_acc[i]->fname << endl;
    cout << "Destination: " << resrvd_acc[i]->destination << endl;
    cout << "Bus code : " << resrvd_acc[i]->resrvd_bus << endl;
    cout << "Leaving time: " << resrvd_acc[i]->leaving_time << endl;
    cout << "Distance in km: " << resrvd_acc[i]->travelling_distance << endl;
    cout << "Total payment : " << resrvd_acc[i]->payement << endl;
}

// printing receipt after confirming the transaction;
void receipt(int resrv_counter)
{
    system("cls");
    cout << right << setw(50) << "Bus X Transport Service\n";
    cout << "Receipt Number: " << resrvd_acc[resrv_counter]->resrvd_seat << endl;
    cout << "Prepared for: " << resrvd_acc[resrv_counter]->fname << endl;
    cout << "Travel Info: From " << resrvd_acc[resrv_counter]->initial_city << " TO " << resrvd_acc[resrv_counter]->destination << endl;
    cout << "Date: "
         << "01-01-2021" << endl;
    cout << endl;
    cout << "Description Quantity price/Quantity Total Price " << endl;
    cout << left << setw(10) << "Transport\t"
         << left << setw(10) << resrvd_acc[resrv_counter]->ticket_size << " "
         << left << setw(10) << resrvd_acc[resrv_counter]->travelling_distance / 10
         << left << setw(10) << resrvd_acc[resrv_counter]->payement << endl;
}

// show customer his/her reservation
void show_cust_reservation() {

}
// shows list of  cities
void list_cities(City *Destination[])
{
    cout << setw(75) << setfill('_') << "_" << endl;
    cout << "|Name of cities   | Distance in KM from AA "
         << "| Direction from AA | Bus Code |\n";
    for (int i = 0; i < 5; i++)
    {
        cout << setw(75) << setfill('_') << "|" << endl;
        cout << left << setw(10) << setfill(' ') << Destination[i]->dest_name << "\t\t"
             << left << setw(5) << Destination[i]->km_from_AA << "\t\t\t  "
             << left << setw(10) << Destination[i]->direction << "\t  "
             << Destination[i]->busDestInfo.bus_dest_cd << "\t  |" << endl;
    }
    cout << setw(75) << setfill('_') << "_" << endl;
}

// show bus information
void showBusInfo()
{
    cout << "AS = Available seat \n";
    cout << "Bus code | Destination | number of buses | Bus 1 AS | Leaving Time | Bus2 AS | Leaving Time \n";

    for (int i = 0; i < 5; i++)
    {
        cout << " " << left << setw(10) << setfill(' ') 
             << bus_rg[i]->bus_dest_cd << "  "
             << left << setw(10) << Destination[i]->dest_name << "\t\t"
             << left << setw(10) << 2 << "   ";

        for (int j = 0; j < 2; j++)
        {
            cout << left << setw(10) << bus_rg[i]->seatAvailble[j]
                 << left << setw(10) << bus_rg[i]->leaving_time[j] << "\t";
        }
        cout << endl;
    }
}
