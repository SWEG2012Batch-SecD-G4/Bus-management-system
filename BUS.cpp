#include<iostream>

using namespace std;

struct bus_info{
    int bus_code;
    int bus_des_code;
};
struct destination{
   string des_name[5];
   float des_kM[5];


}*des1;

void destination(destination arry)
{
    int n;
     cout<<"Enter the value of the user"<<endl;
    cin>>n;
    destination arry[n]={{"Adama","Jima","Harrar","makele","dire"},{100,230,140,430,210}};

    for(int i=0;i<n;i++)
    {
        cout<<"Des "<<i+1<<" "<<arry[i].des_name[i]<<endl;
    }
}
int main()
{
   destination arry[];
    destination(arry);
}
