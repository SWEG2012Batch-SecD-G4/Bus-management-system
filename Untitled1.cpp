#include<iostream>
using namespace std;
struct Bus{
  int destinationcode;
  int buscode;
};
struct city
{
    char cityname[100];
    float distance;
    char directionFrom;
    Bus busInfo;
    }destination;
int main(){
 int n;
 for(int i = 0; i<n; i++)
          {
    cout<< "Please Enter your destination city: ";
   cin.get (destination.cityname,100);
   cout<< "Please enter the distance from your start point to destination: ";
   cin>>destination.distance;
   cout<< "Please enter the direction of the city: ";
   cin.get(destination.directionFrom);
   cout<<"please enter the bus destination code : ";
   cin>>destination.busInfo.destinationcode;
   cout<< "Please enter the bus code : ";
   cin>>destination.busInfo.buscode;
    }
   cout<<endl<<endl;


for(int i = 0; i<n; i++)
{
   cout<< "The information of your bus :\n ";
   cout<< "Your destination city: "<< destination.cityname<<endl;
   cout<< "The distance of your destination from start point: "<<destination.distance<<endl;
   cout<< "The direction of city from the start point: "<<destination.directionFrom<<endl;
   cout<< "The bus destination code is: "<<destination.busInfo.destinationcode<<endl;
   cout<< "The bus code is : "<<destination.busInfo.buscode<<endl;
}
   return 0;

 }





