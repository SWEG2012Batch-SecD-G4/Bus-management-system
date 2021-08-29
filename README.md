# Bus-Ticketing and reservation management
## Sections of the program
The program has three main sections
##    1. The customer sections
The functionality of the customer pages are
1. searching for destination city
2. reserving seat 
3. making changes to reservation and canceling reservation

##    2. Ticketer section
The functionality of the ticketer secions includes
Note: Ticketer must login to the page by providing correct password and ID number;
1. searching for destination city
2. making reservation and changes to reservation
3. searching bus information

The only difference between these two section is that customer cannot search for bus information
Why Ticketer section?
    This section for someone who maynot know how to reserve a seat, and needs help from the company. Most online registration system provides this type of services for their customre

## 3. Administrator section
The admisnistrator section includes the following functionality
1. Adding/removing destination city, initial city and buses to the system
2. Generating reports
3. Overal administrator of the system

# Functional requirements of the program
## 1. Library that manages the customer bank account, security code and balance;
  
Description: 
When customer makes reservation  the program, asks the customer for his/her bank account number and security code. 
Based on the account number  and security code provided the transaction takes place. If customer provides a correct information, the program reduces the payement calculated for the reservation from his/her bank account. 
In case customer #cancels reseravation after (money reduced from his bank account), this library returns money back into a customer's bank account.

### Functionalities of this library
##### 1.1 Creating bank Account for N number of customer(in our case 10)
            Each customer have account number starting from 1000 + their position, and randomly generated balance and security code between 1000 and 10000
##### 1.2 Creating a function that makes transaction happen
            This function takes 4 parameters, these parameters are how much money to be paid, account number, security code of the accountnumber and boolean information that  tells whether the customer is reserving a seat or cancelling a reservation. 
            After taking parameters from the main program when customer makes reservation or cancels this function first checks if the account number and security code provided are correct and found in database. 
            After that it makes transaction provided during the paramtere passing(canceling or reserving seat). 
            In case of reserving a seat, this funcions reduces payement from customer bank account. 
            If customer wants to cancel his reservation, the money should be give back.

## 2. library that manages the cities and buses 
Description:
The program ammends buses to cities. Example, if we have 4 buses and 2 cities A and B, the first two buses will be given to the city A,  and the last two will be given to the other city B. These  2 buses that will travel to A, will have a bus destination code 100 as collective, and 100A and 100B individually. The individual buses under the same destination city is identified by bus code + letter. Each buses may have their own seats and leaving time. 

### Functionalities of this library
#### 2.1 Adding  initial city and buses information(default city and buses)
        create struct named Bus hat hold bus information such as bus destination code, number of buses, leaving time and number of seat available for each buses.
        create struct named City that holds information about city like, city_name, distance from AA, direction from AA, and finally add a  nested structure that appends bus information to each city.

Note: Creating default city and buses is useful.
Default city and bus prevents the admnistrator providing  city and buses information every time the program execution starts.

##### How to create a defualt destination city and buses?
bus_city_info.h library is built for this purposes.
it enables the user to reserve a seat and search for destination city before the administrator section of the program adding city and buses to the program

#### 2.2 Adding/removing cities from travelling cities list
    A new city is added to the lists of cities by creating a function that adds new city to structure dynamically using pointer new operator. Administrator should provide name of the city, distance of the city from AA, and direction of the city from AA.
    Bus will be ammended to the city at the instance new city is added by the administrator.

    Another function removes cities from the list.
    Only administrator have priveledge to remove cities from list of travelling.

#### 2.3 Creating login information for ticketer and administrator
    create a default administrator  and  ticketer login information. 
    Administrator can add/remove ticketer from the organization, the same goes for ticketer login information.

## 3. Main program(main.cpp)
Description:
The main functionalities of this program includes
1. providing interface for the customer, ticketer and admnistrator.
2. responding to customer, ticketer and administrator requests.
The main function of the program should be included here and all other functions from both libraries should be called in this program's main function. 

### functional requirements of this program
#### 3.1 including all necessary libraries
    Important libraries that should be included in this program are iostream, string, iomanip, cstdlib, cmath, ctime,and both user defined libraries bus_city_info.h and bankAccountNumber.h.

#### 3.2 Creating a structure that holds reservation information
###### create struct named reserve that holds the customer's name, destination city, initial_city, payement, accountNumber, securityNumber, reserved seat, ticket size, return type, travelling distance, reserved bus leaving time, and age.

#### 3.3 call the neccessary functions from both libraries that we have included

###### to be continued
