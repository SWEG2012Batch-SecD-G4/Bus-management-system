#include<iostream>
#include<cmath>

using namespace std;
void dest();
int cal_distance(int ,int);
void dest_code(int m);
int check(int n,int t);
void paid(int price,int key);
void reciet(int n,int m,int t);
void last_point();
void station();
int counter=0;
char direction[20]={'N','K','L','E','S','M','P','W'};
int degree[5][5]={{25,45,65,75,90},{110,125,145,165,180},{134,65,120,34,50},{32,12,34,54,565},{32,34,54,56,123}};
char code_bus[2]={'A','B'};

int des_code=1000;


 struct acount
  {
 int acount_num;
  float balance;
 }acount_user[100];

  struct destination{
    string name[5];
    float KM[5];
    int bus_des_code[5];
    string bus_code[2];
};//Killo meter from addis
struct customer{
  string name;
  int age;
  int acount_num;
  int balance;
  int account(float);

struct ticket{
string start[5];
float Km_addis[5];
int seat;
string time[2];
string reservation[3];
}start_bus={{"Bahirdar","Somlia","Afar","Sidama","Guji"},{150,320,300,210,200},100,{"12:00am","6:00pm"},{"seat reserved","No seat avalability","No ticket for underage 15,have a nice day"}};
destination des={{"Jimma","Adama","Mekele","Gonder","Hawassa"},{430,100,540,350,250}};
};
customer user[500];
int acount()
{

   for(int i=0;i<100;i++)
   {
       acount_user[i].acount_num=1000+ rand()%999;
       acount_user[i].balance=10000+rand()&100;
   }
  return acount_user[counter].acount_num;
}
void paid(int price,int key)
{
    label:
    int pass,account;
    cout<<"Enter your unique key :"<<endl;
    cin>>pass;
    if(pass==key)
    {
    cout<<"Welcome to  the transportation service "<<endl;
    cout<<"Do you like to continue y/n "<<endl;
             int total_price=acount_user[i].balance-price;
             cout<<"Than for your using us: "<<endl;


    }
    }
    else{

        cout<<"\nTry again"<<endl;
        goto label;
    }
}
void station()
{
    string*starting_point=user[counter].start_bus.start;

    cout<<"Starting points: "<<endl;
    for(int i=0;i<5;i++)
    {
        cout<<i+1<<"."<<*(starting_point+i)<<endl;

    }
}
void last_point()
{
    string*last=user[counter].des.name;

    cout<<"destination points: "<<endl;
    for(int i=0;i<5;i++)
    {
        cout<<i+1<<"."<<*(last+i)<<endl;

    }
}
void perpaid(int n,int pass_code)
{
    cout<<"-----------------------------------------------------------------"<<endl;
    cout<<"      Perpaid Card    "<<endl;
    cout<<"Name\tAge\tBalance\tYour pass code"<<endl;
    cout<<user[n].name<<"  "<<user[n].age<<"\t"<<user[n].balance<<"\t   "<<pass_code<<endl<<endl;
    cout<<"  Thanks for using this company  "<<endl;
    cout<<"-----------------------------------------------------------------"<<endl;
}

void create()
{
    int start,ends,price,time,unique_key,seat;
    unique_key=100+rand()%2000;
    cout<<"Name: ";getline(cin,user[counter].name);
    cout<<"Age: ";cin>>user[counter].age;
    cout<<"Enter Balance: ";cin>>user[counter].balance;
     if(user[counter].age<15)
        {cout<<user[counter].start_bus.reservation[2];
        exit('0');
        }
     char choice;
     cout<<"Would You like to continue: Y/N"<<endl;
     cin>>choice;
     if(choice=='Y'|| choice=='y')
        perpaid(counter,unique_key);
     else if(choice=='N'||choice=='n')
             cout<<"Thanks for using; good day "<<endl;
     else
     {
        cout<<"Wrong input "<<endl;
     }
     cout<<"choose the starting point bellow "<<endl;
    cout<<"1.Bahirdar\n2.Somalia\n3.Afar\n4.Sidama\n5.Guji"<<endl;
    cin>>start;
    cout<<"Choose the destination bellow"<<endl;
    cout<<"1.Jimma\n2.Adamma\n3.Mekele\n4.Gonder\n5.hawassa"<<endl;
    cin>>ends;
    dest_code(ends);
    int dis=cal_distance(start,ends);
    price=dis*10;
    dest_code(ends);
    cout<<"The distance from "<<user[counter].start_bus.start[start-1]<<" to "<<user[counter].des.name[ends-1]<<" is "<<dis<<endl;

     if(user[counter].start_bus.seat>counter)
        seat=check(ends,time);



    else
    cout<<user[counter].start_bus.reservation[2];
    cout<<"\nChoose time to leave\n1,12:00am:\n2,6:00pm ";cin>>time;
    dest_code(ends);
    system("cls");
    cout<<"\nThe price for the travel is: "<<price;
    paid(price,unique_key);
    cout<<"your bus code is: "<<user[counter].des.bus_des_code[ends-1]<<code_bus[time-1]<<"\nStarting your time "<<user[counter].start_bus.time[time-1]<<endl;
    cout<<"\nYour seat place is "<<seat<<endl;
    counter++;



}
void reciet(int n,int m,int t)
{
    cout<<"Name\tDestination\tSeat\tPrice\tBus_Code\tDistance "<<endl;
   // cout<<user[counter].name<<"\t"<<
}
 int cal_distance(int n,int m)
 {
     int i=n-1;
     int j=m-1;
     float R=sqrt(pow(user[counter].des.KM[i],2)-(2*(user[counter].des.KM[i]*user[counter].start_bus.Km_addis[j])*int(cos(degree[i][j])))+pow(user[counter].start_bus.Km_addis[j],2));
     return R;
 }
 void bus_info()
 {
     int bus;
     cout<<"Choose the bellow option to know more about the bus info "<<endl;
     cout<<"1.Bus code for each destinaiton\n2.bus code with their initial time :"<<endl;
     cin>>bus;
     for(int i=0;i<5;i++)
     {

     }
 }
 void info()
 {
     int choose;
     cout<<"Choose the bellow information to know"<<endl;
     cout<<"1.Station point\n2.Destination place\n3.Bus info"<<endl;
     cin>>choose;
     switch(choose)
     {
     case 1:
         station();
         break;
     case 2:
        last_point();
         break;
     case 3:
        bus_info();


     }
 }
void dest_code(int m)
{

        user[counter].des.name[m-1];
        user[counter].des.bus_des_code[m-1]=des_code+(m-1);

}
int check(int n,int t)
{
    int seat=100,place;
    dest_code(n);
    for(int i=0;i<5;i++)
    {
        if((user[counter].des.bus_des_code[i]==user[counter].des.bus_des_code[n-1])&&(user[counter].start_bus.time[i]==user[counter].start_bus.time[i]))
           {
               place=seat--;
           }
    }
    return place;

}

int main()
{

    int choice,exit;

    do
    {
         cout<<"__________________________"<<endl;
    cout<<"|Choose the bellow option:| "<<endl;
    cout<<"|1.Register               |\n|2.Information             |\n|4.To exit                |"<<endl;
    cout<<"---------------------------"<<endl;
    cin>>choice;
    cin.ignore();
    exit=choice;
    switch(choice)
    {
case 1:
    create();
    break;
case 2:
    info();


    }


    }while(exit!=0);


}

