#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <ctime>
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
bool bus_assignment(int, int, reserve *[], int);
int change_leaving_time(int);
float payement_calculator(int, reserve *[]);
void confirm_resrv(int);
void receipt(int);
void show_all_reservation();

int first_ui();
int cust_first_ui();
void respond_cust_request();
int search_destination();
void cancel_reservation(int);
void modify_reservation(int);
void see_reservation();
// global Variables;
int resrv_counter = 0;

void date_time();
//login page information
bool login_page(int);
bool login_success(int start, int end, string id, string password);
// administrator functions
void respond_admin_request(int);
void add_city();
void remove_city();
int main()
{
    // random_number generator
    random_generator(random1);
    random_generator(random2);

    bankInformation();        // a function that calls Bank information of a customer from bankAccountNumber.h library
    destinationCity();        // calling destination city function from bus_city_info.h
    list_cities(cities_info); // showing all cities and bus that travels there
    showBusInfo();            //  showing individual bus information
    first_ui();               // first user interface of the program(home page)
}

// Home page of the software
int first_ui()
{
    cout << right << setw(10) << "Welcome to Bus X reservation system\n";
    cout << "[1] Enter as customer \n"
         << "[2] Login as Ticketer \n"
         << "[3] Login as Administrator \n";
    bool do_not_exit = true;

    while (do_not_exit)
    {
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            respond_cust_request();
            break;
        case 2:
            add_city();
            break;
        case 3:
            respond_admin_request(choice);
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
            see_reservation();
            break;
        case 4:
            show_all_reservation();
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

    int city_index;
    bool found = false;

    for (int i = 0; i < cityNo_count; i++)
        // if the city the customer searches are on the destination name
        if (city_name == cities_info[i]->city_name)
        {
            city_index = i;
            found = true;
        }

    if (found)
    {
        cout << "Name: " << cities_info[city_index]->city_name << endl
             << "Distance from AA: " << cities_info[city_index]->km_from_AA << endl
             << "Direction from AA: " << cities_info[city_index]->direction << endl
             << "Leaving Time: ";
        for (int j = 0; j < 2; j++)
        {
            cout << cities_info[city_index]->busDestInfo.leaving_time[city_index] << " ";
        }

        cout << "\nAvailable: ";
        if (cities_info[city_index]->busDestInfo.seatAvailble > 0)
            cout << "Yes\n";
        else
            cout << "No\n";
    }
    else
    {
        cout << "\n No such city found in our database\n";
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
        resrvd_acc[resrv_counter]->destination = cities_info[destination]->city_name;
        resrvd_acc[resrv_counter]->initial_city = cities_info[startingPoint]->city_name;

        resrvd_acc[resrv_counter]->travelling_distance = distance_calculator(destination, startingPoint);
    }
    else
        cout << "No inside service \n";

    cout << "Choose Travelling option \n"
         << "[1] One Way \n"
         << "[2] Round Trip: ";
    cin >> resrvd_acc[resrv_counter]->return_oneWay;
    cout << "Number of tickets: ";
    cin >> resrvd_acc[resrv_counter]->ticket_size;

    // asking a customer for time of reservation
    cout << "Leaving Time: \n";
    for (int i = 0; i < 2; i++)
    {
        cout << "[" << i + 1 << "] " << l_time[i] << endl;
    }
    int l_time_choice;
    cin >> l_time_choice;

    // assigning bus to a customer
    // bus_assignment also checks if there's avaible seat
    bool bus_available = bus_assignment(destination, resrv_counter, resrvd_acc, (l_time_choice - 1));
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
                                        resrvd_acc[resrv_counter]->securityNumber, true);
            if (success)
            {
                resrvd_acc[resrv_counter]->resrvd_seat = 1 + resrv_counter;
                receipt(resrv_counter);
                resrvd_acc[resrv_counter]->is_reserverd = true;
                resrv_counter++;
            }
            else
            { /* if customer does provide accountNumber that does not exist, 
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
    if (cities_info[destination]->direction == cities_info[startingPoint]->direction)
    {
        distance_km = cities_info[destination]->km_from_AA -
                      cities_info[startingPoint]->km_from_AA;
        distance_km = (distance_km < 0) ? ((-1) * distance_km) : distance_km;
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
            distance_km = (cities_info[destination]->km_from_AA +
                           cities_info[startingPoint]->km_from_AA);
            break;
        }
        case 2:
        {
            distance_km = sqrt(pow(cities_info[destination]->km_from_AA, 2) +
                               pow(cities_info[startingPoint]->km_from_AA, 2));
            break;
        }
        default:
            break;
        }
    }
    return distance_km;
}

// assignning bus to a customer;
bool bus_assignment(int d_num, int resrv_counter, reserve *resrvd_acc[], int l_choice)
{
    int time_changed;
    bool seat_exist;

    if (bus_rg[d_num]->seatAvailble[l_choice] > 0)
        seat_exist = true;
    // if time customer requests is not available
    else
    {
        time_changed = change_leaving_time(l_choice);
        if (time_changed != l_choice)
        {
            seat_exist = true;
            l_choice = time_changed;
        }
        else
            seat_exist = false;
    }

    if (seat_exist)
    {
        resrvd_acc[resrv_counter]->resrvd_bus = bus_rg[d_num]->bus_cd[l_choice];
        resrvd_acc[resrv_counter]->leaving_time = l_time[l_choice];
        bus_rg[d_num]->seatAvailble[l_choice]--;

        return true;
    }
    else
        return false;
}

// if bus is not available at requested time
int change_leaving_time(int l_choice)
{

    char change;
    int time_index;

    cout << "NO seat available at " << l_time[l_choice] << "\n";
    for (int i = 0; i < 2; i++)
        if ((i != l_choice) && (bus_rg[i]->seatAvailble > 0))
        {
            cout << "Would you like to change time to: " << l_time[i];
            time_index = i;
        }
    cout << (" y/n") << endl;

    cin >> change;
    change = tolower(change);

    // if the customer changes time return the time index;
    if (change == 'y')
    {
        return time_index;
    }
    else
        return l_choice;
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

void date_time()
{
    std::time_t t = std::time(0); // get time now
    std::tm *now = std::localtime(&t);
    std::cout << (now->tm_year + 1900) << '-'
              << (now->tm_mon + 1) << '-'
              << now->tm_mday
              << "\n";
}

// printing receipt after confirming the transaction;
void receipt(int resrv_counter)
{
    //system("cls");
    cout << right << setw(50) << "Bus X Transport Service\n";
    cout << "Receipt Number: " << resrvd_acc[resrv_counter]->resrvd_seat << endl;
    cout << "Prepared for: " << resrvd_acc[resrv_counter]->fname << endl;
    cout << "Travel Info: From " << resrvd_acc[resrv_counter]->initial_city << " TO " << resrvd_acc[resrv_counter]->destination << endl;
    cout << "Leaving Time: " << resrvd_acc[resrv_counter]->leaving_time << endl;
    cout << "Date: ";
    date_time();
    cout << endl;
    cout << endl;
    cout << "Description Quantity price/Quantity Total Price " << endl;
    cout << left << setw(10) << "Transport\t"
         << left << setw(10) << resrvd_acc[resrv_counter]->ticket_size << " "
         << left << setw(10) << resrvd_acc[resrv_counter]->travelling_distance / 10
         << left << setw(10) << resrvd_acc[resrv_counter]->payement << endl;
}

// shows list of  cities
void list_cities(City *cities_info[])
{
    cout << setw(75) << setfill('_') << "_" << endl;
    cout << "|Name of cities   | Distance in KM from AA "
         << "| Direction from AA | Bus Code |\n";
    for (int i = 0; i < 5; i++)
    {
        cout << setw(75) << setfill('_') << "|" << endl;
        cout << left << setw(10) << setfill(' ') << cities_info[i]->city_name << "\t\t"
             << left << setw(5) << cities_info[i]->km_from_AA << "\t\t\t  "
             << left << setw(10) << cities_info[i]->direction << "\t  "
             << cities_info[i]->busDestInfo.bus_dest_cd << "\t  |" << endl;
    }
    cout << setw(75) << setfill('_') << "_" << endl;
}

// show bus information
void showBusInfo()
{
    cout << "AS = Available seat \n";
    cout << "Bus code | Destination | number of buses | "
         << "Bus 1 AS | Leaving Time | Bus2 AS | Leaving Time \n";

    for (int i = 0; i < 5; i++)
    {
        cout << " " << left << setw(10) << setfill(' ')
             << bus_rg[i]->bus_dest_cd << "  "
             << left << setw(10) << cities_info[i]->city_name << "\t\t"
             << left << setw(10) << 2 << "   ";

        for (int j = 0; j < 2; j++)
        {
            cout << left << setw(10) << bus_rg[i]->seatAvailble[j]
                 << left << setw(10) << bus_rg[i]->leaving_time[j] << "\t";
        }
        cout << endl;
    }
}

// void shows all reservation
void show_all_reservation()
{
    cout << "Number of resrvation: " << resrv_counter << endl;
    for (int i = 0; i < resrv_counter; i++)
    {
        cout << "Name " << resrvd_acc[i]->fname << endl;
    }
    show_bank_information();
    cout << endl;
}

void see_reservation()
{
    cout << "Enter name: ";
    string name;
    cin >> name;
    for (int index = 0; index < resrv_counter; index++)
    {
        if (name == resrvd_acc[index]->fname)
        {
            receipt(index); // shows customer his reservation;

            cout << "[1] To cancel reservation \n"
                 << "[2] To change reservation \n";
            int option;
            cin >> option;
            switch (option)
            {
            case 1:
                // put a condition that checks the customer elligibility for cancelling reservation
                cancel_reservation(index);
                cout << "Total Number of people reserved a seat is  " << resrv_counter << endl;
                break;
            case 2:
                modify_reservation(index);
                break;
            default:
                break;
            }
        }
    }
}

// cancel reservation: can be used to make  cancel all the reservation;
void cancel_reservation(int cust_index)
{
    //give the customer is money back;
    bool isMoney_back = accountCheck(resrvd_acc[cust_index]->payement,
                                     resrvd_acc[cust_index]->accountNumber,
                                     resrvd_acc[cust_index]->securityNumber, false);
    // deleting the reservation from system
    for (int i = cust_index; i < resrv_counter; i++)
    {
        resrvd_acc[i] = resrvd_acc[i + 1];
    }
    delete resrvd_acc[resrv_counter];
    resrv_counter--;
}

// modifying reservation
void modify_reservation(int cust_index)
{
    cout << "You can change the following information in your booking \n"
         << "[1] Your name \n"
         << "[2] Leaving Time: \n"
         << "[3] To Finish\n"
         << "[3] To Go back" << endl;

    bool do_not_exit = true;
    while (do_not_exit)
    {
        int option;
        cin >> option;

        switch (option)
        {
        case 1:
        {
            cout << "Enter your new name: ";
            cin >> resrvd_acc[cust_index]->fname;
            break;
        }
        case 2:
        {
            cout << "Leaving Time: \n";
            for (int i = 0; i < 2; i++)
                cout << "[" << i + 1 << "] " << l_time[i] << endl;
            int l_time_choice;
            cin >> l_time_choice;

            // Not the best way to do it, but for now
            resrvd_acc[cust_index]->leaving_time = l_time[l_time_choice - 1];
            break;
        }
        case 3:
            receipt(cust_index);
            break;
        default:
            do_not_exit = false;
            break;
        }
    }
}

// second section of the project
// login page for ticketer and administrator
bool login_page(int i)
{
    // login_information container
    login_info();

    bool status;
    string password, id;
    cout << "ID NO: ";
    cin >> id;
    cout << "password: ";
    cin >> password;

    switch (i)
    {
    case 2:
        status = login_success(0, num_access, id, password);
        break;
    case 3:
         status = login_success(0, 1, id, password);
        break;
    default:
        status  = false;
        break;
    }
    return status;
}

bool login_success(int start, int end, string id, string password)
{
    for (int i = start; i < end; i++)
    {
        if ((id == login_create[i]->id) && (password == login_create[i]->password))
            return true;
        else
            return false;
    }
}

// administrator first user interfaces
int administrator_interface()
{
    cout << "Welcome Mr. Admisnistrator \n"
         << "[1] To add city to lists \n"
         << "[2] To remove city from lists \n"
         << "[3] To Grant a Ticketer priveledges \n";
    int response;
    cin >> response;
    return response;
}

// functional response to administrator requests
void respond_admin_request(int index)
{
    if (login_page(index))
    {
        bool do_not_exit = true;
        while (do_not_exit)
        {
            int response = administrator_interface();
            switch (response)
            {
            case 1:
                add_city();
                break;
            case 2:
                remove_city();
                break;
            default:
                do_not_exit = false;
                break;
            }
        }
    }
}