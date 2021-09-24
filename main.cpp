#include <iostream>
#include <string>
#include <string.h>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cctype>
#include "bankAccountNumber.h"
#include "bus_city_info.h"
#include <bits/stdc++.h>

using namespace std;

struct reserve
{
    string fullName;
    unsigned int age;
    string destination, initial_city;
    int payement;
    int accountNumber;
    int securityNumber;
    int resrvd_seat;
    int ticket_size;
    int return_oneWay;
    float travelling_distance;
    bool is_prepaid;
    int dest_no, bus_code;
    int st_cityNO;
    vector<string> resrvd_bus;
    vector<string> leaving_time;
};
reserve *tempReservtn_store;
vector<reserve> reserved_acc;

// functions participating in reserving a seat
void reserveSeat();
float distance_calculator(int, int);
bool bus_assignment(int, int, reserve *, int &);
int change_leaving_time(int);
float payement_calculator(int, reserve *, bool);
void confirm_resrv(int);
void receipt(int);

//global functions
int first_ui();
void date_time();
void write_to_file(vector<reserve>, string);
void read_from_file();
reserve parse_account(ifstream &source);
void sorting_data();

//interface of customer
int cust_first_ui();
void respond_cust_request();
int search_destination();
void modify_reservation(int);
void cancel_reservation(int, int, int);
void see_reservation();

//login page functions
bool login_page(int);
bool login_success(int, int, string, string);

// ticketer interface
int ticketer_interface();
void respond_ticketer_request(int);

// administrator functions
int admnistrator_interface();
void respond_admin_request(int);
void add_city();
void remove_city();
void show_all_reservation();
void massReservation_cancel(int, string);
void cancelAll_reservation();
void generate_report();

// global variable
int resrv_counter = 0;
float total_payement_received = 0;
int total_reservation = 0;

int main()
{
    // random_number generator
    random_generator(random1);
    random_generator(random2);

    // user-defined library functions
    bankInformation();
    destinationCity();

    //login_information container
    login_info();
    first_ui();
}

// Home page
int first_ui()
{
    system("cls");
    bool do_not_exit = true;
    while (do_not_exit)
    {
        cout << right << setw(10) << "Welcome to Bus X reservation system\n";
        cout << "[1] Enter as customer \n"
             << "[2] Login as Ticketer \n"
             << "[3] Login as Administrator \n";

        int choice;
        cin >> choice;
        system("cls");
        switch (choice)
        {
        case 1:
            respond_cust_request();
            break;
        case 2:
            respond_ticketer_request(choice);
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
    system("cls");
    cout << "Welcome to CompanyX Bus Reservation System \n"
         << "[1] Search destination\n"
         << "[2] Make Reservation \n"
         << "[3] See Your Reservation \n"
         << "[4] Create a new prepaid card \n"
         << "[5] Deposit to prepaid card\n"
         << "[Press any number] To Go Home Page\n";

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
            create_prepaidAccount();
            break;
        case 5:
            deposit_prepaid();
            break;
        default:
            system("cls");
            do_not_exit = false;
            break;
        }
    }
}

// searching destination
int search_destination()
{
    system("cls");
    cout << "Enter name of the city: ";
    string city_name;
    cin >> city_name;
    city_name = convert_toupper(city_name);
    cout << "The city name is " << city_name << endl;

    int city_index;
    bool found = false;

    for (int i = 0; i < cityNo_count; i++)
    {
        citiesInfo_database[i].city_name = convert_toupper(citiesInfo_database[i].city_name);
        if (city_name == citiesInfo_database[i].city_name)
        {
            found = true;
            city_index = i;
        }
    }

    if (found)
    {
        cout << "Name: " << citiesInfo_database[city_index].city_name << endl
             << "Distance from AA: " << citiesInfo_database[city_index].km_from_AA << endl
             << "Direction from AA: " << citiesInfo_database[city_index].direction << endl
             << "Leaving Time: ";
        for (int j = 0; j < 2; j++)
            cout << citiesInfo_database[city_index].busDestInfo.leaving_time[j] << " ";

        bool cityExists = false;
        for (int i = 0; i < 2; i++)
            if (citiesInfo_database[city_index].busDestInfo.seatAvailble[i] > 0)
                cityExists = true;

        cout << "\nAvailable: ";
        if (cityExists)
            cout << "Yes\n";
        else
            cout << "No\n";
    }
    else
        cout << "\n No such city found in our database\n";
    system("pause");
}

// reserve seat
void reserveSeat()
{
    system("cls");
    // create a new reserve everytime this function is called

    tempReservtn_store = new reserve;
    cout << "Enter FullName: ";
    string fname, lname;
    cin >> fname >> lname;
    tempReservtn_store->fullName = fname + " " + lname;
    tempReservtn_store->fullName = convert_toupper(tempReservtn_store->fullName);

    cout << "Enter your age: ";
    cin >> tempReservtn_store->age;
    while (tempReservtn_store->age < 18)
    {
        cout << "You are under Age: ";
        cin >> tempReservtn_store->age;
    }
// travelling city information;
label:
    cout << "Choose starting Point: \n";
    int startingPt = travelling_city() - 1;
    cout << "Choose Destination City: \n";
    int destination = travelling_city() - 1;
    tempReservtn_store->dest_no = destination;
    tempReservtn_store->st_cityNO = startingPt;

    // calculating distance between starting city and destination city;
    // checks whether customer enters the same name at both destination and starting city
    if (startingPt != destination)
    {
        // assign a city to customer information
        tempReservtn_store->destination = citiesInfo_database[destination].city_name;
        tempReservtn_store->initial_city = citiesInfo_database[startingPt].city_name;

        tempReservtn_store->travelling_distance = distance_calculator(destination, startingPt);
    }
    else
    {
        cout << "No inside service:Please enter again! \n";
        goto label;
    }

    cout << "Choose Travelling option \n"
         << "[1] One Way \n"
         << "[2] Round Trip: ";
    cin >> tempReservtn_store->return_oneWay;
    cout << "Number of tickets: ";
    cin >> tempReservtn_store->ticket_size;

    // asking a customer for time of reservation
    cout << "Leaving Time: \n";
    for (int i = 0; i < 2; i++)
    {
        cout << "[" << i + 1 << "] " << l_time[i] << endl;
    }
    int l_time_choice;
    cin >> l_time_choice;
    l_time_choice -= 1;

    // assigning bus to a customer
    // bus_assignment also checks if there's avaible seat
    bool bus_available = bus_assignment(destination, resrv_counter, tempReservtn_store, (l_time_choice));
    if (bus_available)
    {
        // payement
        cout << "Choose payement method\n"
             << "[1] Prepaid\n"
             << "[2] Bank \n";
        int payement_method;
        cin >> payement_method;
        if (payement_method == 1)
            tempReservtn_store->is_prepaid = true;
        else
            tempReservtn_store->is_prepaid = false;

        // Bank Account Information;
        cout << "Enter account: ";
        cin >> tempReservtn_store->accountNumber;
        cout << "Enter security Code: ";
        cin >> tempReservtn_store->securityNumber;

        // calculates total payement;
        float payement = payement_calculator(resrv_counter, tempReservtn_store,
                                             tempReservtn_store->is_prepaid);
        tempReservtn_store->payement = payement;

        //assign buses to the customer
        tempReservtn_store->resrvd_bus.push_back(busInfo_database[destination].bus_cd[l_time_choice]);
        tempReservtn_store->leaving_time.push_back(l_time[l_time_choice]);

        if (tempReservtn_store->return_oneWay == 2)
        {
            bool return_bus_avbl = bus_assignment(startingPt, resrv_counter, tempReservtn_store, (l_time_choice));
            tempReservtn_store->resrvd_bus.push_back(busInfo_database[startingPt].bus_cd[l_time_choice]);
            tempReservtn_store->leaving_time.push_back(l_time[l_time_choice]);
        }

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
            bool success = accountCheck(tempReservtn_store->payement,
                                        tempReservtn_store->accountNumber,
                                        tempReservtn_store->securityNumber,
                                        tempReservtn_store->is_prepaid, true);

            if (success)
            {
                // recording payement information
                // if trip is round trip divide payment between buses
                if (tempReservtn_store->return_oneWay == 2)
                {
                    busInfo_database[startingPt].seatAvailble[l_time_choice] -= (tempReservtn_store->ticket_size);
                    busInfo_database[destination].seatAvailble[l_time_choice] -= (tempReservtn_store->ticket_size);
                    busInfo_database[startingPt].payement[l_time_choice] += payement / (2.0);
                    busInfo_database[destination].payement[l_time_choice] += payement / (2.0);
                }
                else
                {
                    busInfo_database[destination].seatAvailble[l_time_choice] -= (tempReservtn_store->ticket_size);
                    busInfo_database[destination].payement[l_time_choice] += payement;
                }

                tempReservtn_store->resrvd_seat = (100 - busInfo_database[destination].seatAvailble[l_time_choice]);
                tempReservtn_store->bus_code = l_time_choice;
                total_payement_received += payement;
                total_reservation += (tempReservtn_store->ticket_size * tempReservtn_store->return_oneWay);

                reserved_acc.push_back(*tempReservtn_store);
                receipt(resrv_counter);

                // write a reservation data to a file
                write_to_file(reserved_acc, "reservationfile.txt");
                resrv_counter++;
                delete tempReservtn_store; // release a memory;
            }
            else
            { /* if customer does provide accountNumber that does not exist,
                    does not have enough balance in the account, and
                    haven't not provided correct security code, cancel the reservation
                 */

                cout << "Transaction was not successful \n"
                     << "Please check your bank information \n";
                delete tempReservtn_store; // release a memory;
                system("pause");
            }
        }
        else
        {
            cout << "Request canceled \n";
            delete tempReservtn_store; // release a memory;
        }
    }
}

// distance calculator
float distance_calculator(int destination, int startingPt)
{
    float distance_km;
    // if the two cities are on the same direction
    if (citiesInfo_database[destination].direction == citiesInfo_database[startingPt].direction)
    {
        distance_km = citiesInfo_database[destination].km_from_AA -
                      citiesInfo_database[startingPt].km_from_AA;
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
            distance_km = (citiesInfo_database[destination].km_from_AA +
                           citiesInfo_database[startingPt].km_from_AA);
            break;
        }
        case 2:
        {
            distance_km = sqrt(pow(citiesInfo_database[destination].km_from_AA, 2) +
                               pow(citiesInfo_database[startingPt].km_from_AA, 2));
            break;
        }
        default:
            break;
        }
    }
    return distance_km;
}

// assignning bus to a customer;
bool bus_assignment(int d_num, int resrv_counter, reserve *tempReservtn_store, int &l_choice)
{
    int time_changed;
    bool seat_exist;

    if (busInfo_database[d_num].seatAvailble[l_choice] > 0)
        seat_exist = true;
    // if time customer request is not available
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

    return seat_exist;
}

// if bus is not available at requested time
int change_leaving_time(int l_choice)
{

    char change;
    int time_index;

    cout << "NO seat available at " << l_time[l_choice] << "\n";
    for (int i = 0; i < 2; i++)
        if ((i != l_choice) && (busInfo_database[i].seatAvailble[i] > 0))
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
float payement_calculator(int resrv_counter, reserve *tempReservtn_store, bool isPrepaid)
{
    float birr_per_km = 10;
    float discount_rate = 20 / 100.0;

    // prepaid card have discount
    if (isPrepaid)
        birr_per_km = birr_per_km - (birr_per_km * discount_rate);

    float payement = tempReservtn_store->return_oneWay *
                     tempReservtn_store->ticket_size *
                     tempReservtn_store->travelling_distance * birr_per_km;
    return payement;
}

// confirm reservation
void confirm_resrv(int i)
{
    system("cls");
    cout << "Confirm Your Reservation\n\n";
    cout << "Name: " << tempReservtn_store->fullName << endl;
    cout << tempReservtn_store->initial_city << " --->" << tempReservtn_store->destination << endl;
    cout << "Bus code : " << tempReservtn_store->resrvd_bus[0]
         << " ---- Leaving Time : " << tempReservtn_store->leaving_time[0] << endl;

    if (tempReservtn_store->return_oneWay == 2)
    {
        cout << "\n"
             << tempReservtn_store->destination << " ---> " << tempReservtn_store->initial_city;
        cout << "\nBus code : " << tempReservtn_store->resrvd_bus[1]
             << "----- Leaving Time : " << tempReservtn_store->leaving_time[1] << endl;
    }
    cout << "Distance in km: " << tempReservtn_store->travelling_distance << "Km" << endl;
    cout << "Total payment : " << tempReservtn_store->payement << " Birr" << endl;
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
void receipt(int pos)
{
    system("cls");
    cout << right << setw(50) << "Bus X Transport Service\n";
    cout << "Reciept \n";

    cout << "Seat Number: ";
    for (int i = reserved_acc[pos].resrvd_seat;
         i > (reserved_acc[pos].resrvd_seat - reserved_acc[pos].ticket_size); i--)
        cout << i << ", ";

    cout << "\nPrepared for: " << reserved_acc[pos].fullName << endl;
    cout << "Travel Info: From " << reserved_acc[pos].initial_city
         << " TO " << reserved_acc[pos].destination << endl;
    cout << "Trip type: ";
    if (reserved_acc[pos].return_oneWay == 2)
        cout << "round trip" << endl;
    else
        cout << "One way trip " << endl;
    cout << "Leaving Time: " << reserved_acc[pos].leaving_time[0] << endl;
    cout << "Date: ";
    date_time();

    cout << endl
         << endl;
    cout << "Description Quantity price/Quantity Total Price " << endl;
    cout << left << setw(10) << "Transport\t"
         << left << setw(10) << reserved_acc[pos].ticket_size << " "
         << left << setw(10) << reserved_acc[pos].travelling_distance / 10
         << left << setw(10) << reserved_acc[pos].payement << endl;
    system("pause");
}

void see_reservation()
{
    system("cls");
    cout << "Enter FullName: ";
    string fname, lname, name;
    cin >> fname >> lname;
    name = fname + " " + lname;
    transform(name.begin(), name.end(), name.begin(), ::toupper);

    bool isFound = false;
    int index;
    for (int i = 0; i < reserved_acc.size(); i++)
        if (name == reserved_acc[i].fullName)
        {
            isFound = true;
            index = i;
        }

    if (isFound)
    {
        receipt(index); // shows customer his reservation;

        cout << "[1] To cancel reservation \n"
             << "[2] To change reservation \n";
        int option;
        cin >> option;
        switch (option)
        {
        case 1:
            cancel_reservation(index, reserved_acc[index].dest_no, reserved_acc[index].bus_code);
            cout << "Reservation canceled \n";
            break;
        case 2:
            modify_reservation(index);
            break;
        default:
            break;
        }
    }
    else
        cout << "No reservation under the name " << name << endl;
    system("pause");
}

// cancel reservation: can be used to make  cancel all the reservation;
void cancel_reservation(int cust_index, int i, int j)
{
    //payback the money
    float payement = reserved_acc[cust_index].payement;
    int number_seats = reserved_acc[cust_index].ticket_size;
    int k = reserved_acc[cust_index].st_cityNO;
    bool isMoney_back = accountCheck(payement,
                                     reserved_acc[cust_index].accountNumber,
                                     reserved_acc[cust_index].securityNumber,
                                     reserved_acc[cust_index].is_prepaid, false);

    //  rearranging bus seat number and payement;
    total_payement_received -= payement;
    if (reserved_acc[cust_index].return_oneWay == 2)
    {
        busInfo_database[k].payement[j] -= payement / (2.0);
        busInfo_database[k].seatAvailble[j] += number_seats;
        busInfo_database[i].payement[j] -= payement / (2.0);
        busInfo_database[i].seatAvailble[i] += number_seats;
    }
    else
    {
        busInfo_database[i].payement[j] -= payement;
        busInfo_database[i].seatAvailble[j] += number_seats;
    }

    //delete tempReservtn_store[resrv_counter];
    reserved_acc.erase(reserved_acc.begin() + cust_index);

    // write changes to a file
                write_to_file(reserved_acc, "reservationfile.txt");
    resrv_counter -= number_seats;
    total_reservation -= number_seats;
}

// modifying reservation
void modify_reservation(int cust_index)
{
    bool do_not_exit = true;
    while (do_not_exit)
    {
        cout << "You can change the following information in your booking \n"
             << "[1] Your name \n"
             << "[2] Leaving Time: \n"
             << "[3] To Finish\n";
        int option;
        cin >> option;

        switch (option)
        {
        case 1:
        {
            cout << "Enter your new name: ";
            string fname, lname, fullname;
            cin >> fname >> lname;
            reserved_acc[cust_index].fullName = fname + " " + lname;
            reserved_acc[cust_index].fullName = convert_toupper(reserved_acc[cust_index].fullName);
            cout << "Name changed successfuly \n";
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
            reserved_acc[cust_index].leaving_time[0] = l_time[l_time_choice - 1];
            cout << "Leaving time is changed successfuly \n";
            break;
        }
        case 3:
            receipt(cust_index);
            break;
        default:
            system("cls");
            do_not_exit = false;
            break;
        }
    }

    // write a modified account to a file
        write_to_file(reserved_acc, "reservationfile.txt");
}

// login page for ticketer and administrator
bool login_page(int i)
{
    system("cls");
    bool status;
    string password, id;
    cout << setw(10) << "Enter your Login information below\n";
    cout << "Both ID and password are case sensitive \n";
    cout << "ID NO: ";
    cin >> id;
    cout << "password: ";
    cin >> password;

    switch (i)
    {
    case 2:
        status = login_success(1, num_access, id, password);
        break;
    case 3:
        status = login_success(0, 1, id, password);
        break;
    default:
        status = false;
        break;
    }
    return status;
}

// confirms login credentials
bool login_success(int start, int end, string id, string password)
{
    bool login_success = false;
    for (int i = start; i < end; i++)
        if ((id == loginInfo_database[i].id) && (password == loginInfo_database[i].password))
            login_success = true;

    return login_success;
}

// ticketer page
int ticketer_interface()
{
    system("cls");
    cout << "Welcome to CompanyX Bus Reservation System \n"
         << "[1] Reserve for customer\n"
         << "[2] Show All cities and Buses Assigned \n"
         << "[3] Show All Major Buses Information \n"
         << "[Press any number] To Go Home Page\n";

    int option;
    cin >> option;
    return option;
}

void respond_ticketer_request(int index)
{
    if (login_page(index))
    {
        bool do_not_exit = true;
        int option;
        while (do_not_exit)
        {
            option = ticketer_interface();

            switch (option)
            {
            case 1:
                respond_cust_request();
                break;
            case 2:
                list_cities();
                break;
            case 3:
                showBusInfo();
                break;
            case 4:
                first_ui();
                break;
            default:
                system("cls");
                do_not_exit = false;
                break;
            }
        }
    }
    else
        cout << "Incorrect login information \n";
}

// administrator first user interfaces
int administrator_interface()
{
    system("cls");
    cout << "Welcome Mr. Admisnistrator \n"
         << "[1] To add city to lists \n"
         << "[2] To remove city from lists \n"
         << "[3] show all reservations \n"
         << "[4] To Grant a Ticketer priveledges \n"
         << "[5] Mass reservation cancelling \n"
         << "[6] Generate Report \n"
         << "[7] Write data to a file \n"
         << "[6] Generate Report \n"
         << "[Press any number] To Go Home Page\n";

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
            case 3:
                show_all_reservation();
                break;
            case 4:
                create_ticketer_login();
                break;
            case 5:
                cancelAll_reservation();
                break;
            case 6:
                generate_report();
                break;
            case 7:
                write_to_file(reserved_acc, "reservationfile.txt");
                break;
                        case 8:
                sorting_data();
                break;
            default:
                system("cls");
                do_not_exit = false;
                break;
            }
        }
    }
    else
        cout << "Incorrect Login information \n";
}

void show_all_reservation()
{
    system("cls");
    cout << "Total Number of resrvation: " << total_reservation << endl;
    cout << " Full Name   \t| Initial | Destination | "
         << "Bus Assigned | seatNumber | Leaving Time | Distance | payement\n";
    cout << setprecision(1) << fixed;
    for (int i = 0; i < resrv_counter; i++)
    {
        cout << " " << left << setw(5) << reserved_acc[i].fullName << right << setw(10)
             << reserved_acc[i].initial_city << right << setw(15)
             << reserved_acc[i].destination << right << setw(12)
             << reserved_acc[i].resrvd_bus[0] << right << setw(10);

        if (reserved_acc[i].ticket_size > 1)
            cout << reserved_acc[i].resrvd_seat - reserved_acc[i].ticket_size + 1
                 << " - " << reserved_acc[i].resrvd_seat << right << setw(17);
        else
            cout << reserved_acc[i].resrvd_seat << right << setw(20);

        cout << reserved_acc[i].leaving_time[0] << right << setw(10)
             << reserved_acc[i].travelling_distance << right << setw(10)
             << reserved_acc[i].payement << endl;
    }
    system("pause");
}

void cancelAll_reservation()
{
    system("cls");
    bool do_not_exit = true;
    string cancelType[2] = {" Destination name: ", " Bus code: "};

    cout << "[1] To all reservation to destination\n"
         << "[2] To cancel specific buses reservation to destination\n";

    int option;
    cin >> option;

    switch (option)
    {
    case 1:
        massReservation_cancel(option, cancelType[option - 1]);
        break;
    case 2:
        massReservation_cancel(option, cancelType[option - 1]);
        break;
    default:
        do_not_exit = false;
        break;
    }
}

// mass bus reservation cancelling
void massReservation_cancel(int option, string cancelType)
{
    cout << "Enter a" << cancelType;
    string cancel_type;
    cin >> cancel_type;

    bool is_canceled = false;
    for (int i = 0; i < resrv_counter; i++)
    {
        switch (option)
        {
        case 1:
        {
            cancel_type = convert_toupper(cancel_type);
            if (reserved_acc[i].destination == cancel_type)
            {
                cancel_reservation(i, reserved_acc[i].dest_no, reserved_acc[i].bus_code);
                is_canceled = true;
            }
        }
        break;
        case 2:
            if (reserved_acc[i].resrvd_bus[0] == cancel_type)
            {
                cancel_reservation(i, reserved_acc[i].dest_no, reserved_acc[i].bus_code);
                is_canceled = true;
            }
            break;
        default:
            cout << "Incorrect option/ please try again!. \n";
            break;
        }
    }

    if (is_canceled)
        cout << "All reservation have been canceled succesfully!\n";
    else
        cout << "Operation was not successful, check " << cancelType << "again!\n";
    system("pause");
}

// a function that generates report
void generate_report()
{
    system("cls");
    cout << "Date: ";
    date_time();
    cout << "Bus Code | payement Received | Seat Reserved" << endl;
    for (int i = 0; i < busInfo_database.size(); i++)
        for (int j = 0; j < 2; j++)
        {
            cout << " " << busInfo_database[i].bus_cd[j] << right << setw(15);
            if (busInfo_database[i].seatAvailble[j] < 100)
            {
                cout << busInfo_database[i].payement[j] << right << setw(15)
                     << (100 - busInfo_database[i].seatAvailble[j]) << endl;
            }
            else
                cout << "None" << right << setw(15)
                     << "0" << endl;
        }

    cout << "Total reservation made: " << total_reservation << endl;
    cout << "Total Payement Received: " << total_payement_received << endl;
    system("pause");
}

// file handling functions
void write_to_file(vector<reserve> reserv_file, string file_name)
{
    ofstream fout;
    fout.open(file_name.c_str(), ios::out);

    // checks wether the file is opened correctly or not.
    if (!fout)
    {
        cout << "File did not opened.\n";
        exit(0);
    }

    // write a file to
    for(int i = 0; i < reserv_file.size(); i++)
    {
            fout << left << setw(20) << reserv_file[i].fullName << left << setw(5)
         << reserv_file[i].accountNumber << "\t\t" << reserv_file[i].initial_city << left << setw(5)
         << reserv_file[i].destination << "\t\t" << reserv_file[i].travelling_distance << "\t "
         << reserv_file[i].resrvd_bus[0] << " \t\t" << reserv_file[i].payement << "\t" << reserv_file.size() << endl;
    }
    fout.close();
}

void sorting_data()
{
    vector <reserve> sorted_storage;
    for (int i = 0; i < reserved_acc.size(); i++)
     for(int j = i+1; j < reserved_acc.size(); j++)
    {
        if (reserved_acc[i].payement < reserved_acc[j].payement)
        {
            sorted_storage[i] = reserved_acc[i];
            reserved_acc[i] = reserved_acc[j];
            reserved_acc[j] = sorted_storage[i];
        }
    
    }
    
}