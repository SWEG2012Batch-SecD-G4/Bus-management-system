#include<iostream>
#include<cmath>

using namespace std;
void dest();
int cal_distance(int ,int);//calculate the distance from starting point to destination
void dest_code(int m);
void Report();
void create();//registor the user and give the prepaid
int check(int n,int t,int);///check the seat size number
void paid(int price,int key);//payment transaction takes place
void receipt(int n,int m,int t,float tax,float price);//Give receipt for the user
void last_point();//It display the lasting  point
void prepaid();//Give  the perpaid Card to the user
void station();//It display the starting point
int check(int n,int t);//It check the seat for one bus is avalable;
int counter=0;//It count the customer that have been registor
string direction[20]={"N","NE","NW","E","S","SE","SW","W"};//It is the direction of the location of starting to destioation
int degree[5][5]={{25,45,65,75,90},{110,125,145,165,180},{134,65,120,34,50},{32,12,34,54,565},{32,34,54,56,123}};//The degree that each starting point to each destination
char code_bus[2]={'A','B'};//To defferinciate the Bud code
   string crime[20]={"abebe kebede","abel kebed","jafar husen","lawrence jhon ","ismael abera","birhanu alemu","kebede chukala","hawe dawit","dory gana","chris mack","charles evans","israel tewdro","Kirubel seifu","esubalew abebe","Asabu mogese","dagim moges","boru biratu","jerard  jigsaw","keti wondewson","biscute dagim"};
    int age_crime[20]={32,34,45,21,65,36,37,24,26,75,57,63,24,28,32,67,87,89,78,32};

int des_code=1000;//The destination code for each bus


int seat=100;
 struct acount
  {
 int acount_num;
  float balance;
 }acount_user[100];
//This structure store the destination name, Km from addis,the destination bus code,bus id
  struct destination{
    string name[5];
    float KM[5];
    int bus_des_code[5];
    string bus_code[2];
};
//This structure store the customer name, age,balance
struct customer{
  string name;
  int age;
  int acount_num;
  int balance;
  float tax_payment;//The tax payment for the service
  float price;
  int seat_place[5][2];
//This structure store thd starting place, Km from addis,seat number, time of bus leaving,reservation
struct ticket{
string start[5];
float Km_addis[5];

string time[2];
string reservation[3];
}start_bus={{"Bahirdar","Somlia","Afar","Sidama","Guji"},{150,320,300,210,200},{"12:00am","6:00pm"},{"seat reserved","No seat avalability","No ticket for underage 15,have a nice day"}};
destination des={{"Jimma","Adama","Mekele","Gonder","Hawassa"},{430,100,540,350,250}};
};

customer user[500];
int acount()
{

   for(int i=0;i<100;i++)
   {
       acount_user[i].acount_num=1000+ rand()%999;
   }
  return acount_user[counter].acount_num;
}
void criminality(string name,int age)
{


    for(int i=0;i<20;i++)
    {
        if(name==crime[i]&&(age==age_crime[i]))
        {
            cout<<"Sorry we are not give a service Today,good day"<<endl;
            exit('a');
        }
    }
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
             int total_price=acount_user[counter].balance-price;
             cout<<"Than for your using us: "<<endl;


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
    criminality( user[counter].name, user[counter].age);
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
    user[counter].tax_payment=dis*(15)/100;
    user[counter].price=price+user[counter].tax_payment;
    dest_code(ends);
    cout<<"The distance from "<<user[counter].start_bus.start[start-1]<<" to "<<user[counter].des.name[ends-1]<<" is "<<dis<<endl;
    cout<<"\nChoose time to leave\n1,12:00am:\n2,6:00pm ";cin>>time;
    dest_code(ends);
    seat=check(ends,time);
    system("cls");
    cout<<"Your unique key "<<unique_key<<endl;
    cout<<"\nThe price for the travel is: "<<user[counter].price<<endl;
    paid(user[counter].price,unique_key);
    user[counter].seat_place[ends][time]=100;
     cout<<"your bus code is: "<<user[counter].des.bus_des_code[ends-1]<<code_bus[time-1]<<"\nStarting your time "<<user[counter].start_bus.time[time-1]<<endl;
    cout<<"\nYour seat place is "<<seat<<endl;
     system("cls");
    receipt(start,ends,time,user[counter].tax_payment,price);
    counter++;



}
void receipt(int n,int m,int t ,float tax,float price)
{
    float dis=cal_distance(n,m);

    cout<<"-------------------receipt----------------"<<endl;
    cout<<"Name: "<<user[counter].name<<"|"<<endl;
    cout<<"start point "<<user[counter].start_bus.start[n-1]<<"->destination point "<<user[counter].des.name[m-1]<<endl;
    cout<<"Seat: "<<user[counter].seat_place[m-1][t-1]<<""<<endl;
    cout<<"Price: "<<user[counter].price<<""<<endl;
    cout<<"Bus Destination Code: "<<user[counter].des.bus_des_code[m-1]<<"   Bus_ID: "<<user[counter].des.bus_des_code[m-1]<<code_bus[t-1]<<"   Leaaving time: "<<user[counter].start_bus.time[t-1]<<endl;
    cout<<"Distance: "<<dis<<endl;
    cout<<"Tax payment: "<<tax<<endl;
    cout<<"The price is :"<<price<<endl;
    cout<<"Total price is: "<<tax+price<<endl;
    cout<<"--------------THANKS FOR COMING-----------"<<endl;

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
     cout<<"Destination\tBus code\t Bus_Id(Time of leaving)"<<endl;
     for(int i=0;i<5;i++)
     {
    cout<<user[counter].des.name[i]<<"\t       "<<des_code+i<<"\t"<<des_code+i<<code_bus[0]<<"("<<user[counter].start_bus.time[0]<<")"<<"   and     "<<des_code<<code_bus[1]<<"("<<user[counter].start_bus.time[1]<<")"<<endl;
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

    dest_code(n);
   user[counter].seat_place[n][t]=user[counter].seat_place[n][t]--;
  if(user[counter].seat_place[n][t]>counter)
    cout<<"congrat"<<endl;

else
    cout<<user[counter].start_bus.reservation[2];


    return user[counter].seat_place[n][t];

}
void report()
{
    cout<<"Starting_point\t    Destination\t    Bus code\t Bus_Id(Time of leaving)"<<endl;
     for(int i=0;i<5;i++)
     {
    cout<<user[counter].start_bus.start[i]<<"\t    "<<user[counter].des.name[i]<<"\t       "<<des_code+i<<"\t"<<des_code+i<<code_bus[0]<<"("<<user[counter].start_bus.time[0]<<")"<<"   and     "<<des_code<<code_bus[1]<<"("<<user[counter].start_bus.time[1]<<")"<<endl;
     }
}
void display_Crimal()
{
    cout<<"-------------------------------------------"<<endl;
    cout<<"----------MOST WANTED FUGITIVRES-----------"<<endl;
    cout<<"_______________________"<<endl;
    cout<<"|NAME\t\t   AGE"<<"|"<<endl;
    for(int i=0;i<20;i++)
    {
      cout<<"|"<<crime[i]<<"\t    "<<age_crime[i]<<"|"<<endl;
    }
    cout<<"_______________________"<<endl;

}

void customers()
{
       int choice,exit;

    do
    {
         cout<<"__________________________"<<endl;
    cout<<"|Choose the bellow option:| "<<endl;
    cout<<"|1.Register               |\n|2.Information            |\n|4.To exit                |"<<endl;
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
void admin()
{
    string pass,user;
    string username="jima";
    string password="0000";
     cout<<"Enter the username: ";cin>>user;
     cout<<"Enter passcode: ";cin>>pass;
     if((user==username)&&(password==pass))
        {
            cout<<"Welcome to bus manegment system "<<endl;
            cout<<"Choose the bellow option "<<endl;
            cout<<"[1].Full Report on the bus system\n[2].Fugitives(Most Wanted people's name)"<<endl;
            int choice;
            cin>>choice;
            system("cls");
            switch(choice)
            {
            case 1:
                report();
                break;
            case 2:
                display_Crimal();
            }
        }
}

int main()
{
    int choose;
    cout<<"Choose the bellow option"<<endl;
    cout<<"1.Customer\n2.Adimn"<<endl;
    cin>>choose;
    switch(choose)
    {
    case 1:
        customers();
        break;
    case 2:
       admin();


}
}
