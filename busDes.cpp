#include<iostream>

using namespace std;
int counter=0;
char code_bus[2]={'A','B'};
string time[2]={"12:00am","6:00pm"};
int des_code=1000;

struct bus_code{
  int bus_des_code[5];
  string bus_code[2];



}code;
struct destination{
  string name[5];
  float KM[5];
}des={{"Jimma","Adama","Mekele","Gonder","Hawassa"},{430,100,540,350,250}};
void dest()
{
        des.name[counter];
        code.bus_des_code[counter]=des_code+counter;
        for(int i=0;i<2;i++){
        code.bus_code[i]=des_code+counter;
        }


}
int main()
{
    //code.starting_time[={12,6}
    cout<<"The destination information: "<<endl;
   char exit;
    do
    {
        dest();
        cout<<"Name\tdes_code\t\tbus_Targa/Time"<<endl;

        cout<<des.name[counter]<<"\t"<<code.bus_des_code[counter];
        for(int i=0;i<2;i++)
        {
            cout<<"\t\t"<<code.bus_des_code[counter]<<code_bus[i]<<"/";
            cout<<time[i];
        }
        cout<<endl;

        counter++;
        cout<<"Do you want to continue Y/N "<<endl;
        cin>>exit;
        if(exit=='N')
        {
            return 0;
        }


    }while(exit!='Y');
}

