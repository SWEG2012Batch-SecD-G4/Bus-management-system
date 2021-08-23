# Bus-Ticketing and reservation management
# The program has three main sections
    # 1. The customer sections
The functionality of the customer pages are
1. searching for destination city
2. reserving seat 
3. making changes to reservation and canceling reservation

    # 2. Ticketer section
The functionality of the ticketer secions includes
Note: Ticketer must login to the page by providing correct password and ID number;
1. searching for destination city
2. making reservation and changes to reservation
3. searching bus information

The only difference between these two section is that customer cannot search for bus information
Why Ticketer section?
    This section for someone who maynot know how to reserve a seat, and needs help from the company. Most online registration system provides this type of services for their customre

    # 3. Administrator section
The admisnistrator section includes the following functionality
1. Adding/removing destination city, initial city and buses to the system
2. Generating reports
3. Overal administrator of the system

Note: Creating default destination city is useful.
default destination city and bus prevents the admnistrator providing destination city and buses before the customer starts to reserve a seat.

# How to create a defualt destination city and buses?
bus_city_info.h library is built for this purposes.
it enables the user to reserve a seat and search for destination city before the administrator section of the program adding city and buses to the program

###### to be continued
