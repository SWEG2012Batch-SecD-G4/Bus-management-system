#include<iostream>

using namespace std;

struct bus_info{
    int bus_destn_code;
    int bus_code[5];
};
struct location{

    float dist_from_AA;
    float direc_from_AA;
    bus_info bus_dest_num[5];
};
struct dest_init{
   string destination[5];
   string initial_city[5];
    location loc_info;
};

int fee(int );

int main()
{
    int age,finalfee,a;

    dest_init dest_info;
    cout << "Enter your age" << endl;
     cin >> age ;

    a= fee(int age);
    cout << "Your fee is: " << a<<" Birr";
    return 0;
}
int fee(int age){
    int finalfee;
    if (age <11)
      {
          finalfee = dest_info.dist_from_AA * 4;
      }
    else if (age >60)
     {
         finalfee = dest_info.dist_from_AA * 2;
     }
     else if (17 < age <  65)
     {
         finalfee = dest_info.dist_from_AA * 6;
     }
    return(finalfee);
}












