#include <iostream>

using namespace std;

int r=0,p=0,k=20;
float allsell=0;

struct bus{

char arriva[9],deprt[9],from[9],to[9],pname[99];
int busn,dtym,tseat,fair,s;
	void install();
	void show();
	void book();
	void exit();


}b[8];

void bus::install(void)
{
	cout.setf(ios::right,ios::adjustfield);
	cout.width(15);
cout<<"Enter Bus No:";
cin>>busn;
	cout.setf(ios::right,ios::adjustfield);
	cout.width(15);
cout<<"\nFrom: ";
cin>>from;
cout<<"\nTo: ";
cin>>to;
cout<<"\nDeparture: ";
cin>>dtym;
cout<<"\nTotal seats: ";
cin>>tseat;

p++;
cout<<"\n";
cout<<"Bus Information Added!!\n";
system("PAUSE");
system("CLS");

}

void bus::show(void)
{
	cout<<"total bus available:"<<endl;
	for(int i=0;i<p;i++)
		{
			cout<<"Bus No: ";
			cout<<b[i].busn<<endl;
			cout<<"From: ";
			cout<<b[i].from<<endl;
			cout<<"To: ";
			cout<<b[i].to<<endl;
			cout<<"Departure: ";
			cout<<"Seats: ";
			cout<<b[i].tseat<<endl<<endl<<endl;

		}
		system("PAUSE");
		system("CLS");
}


void bus::book(void)
{
int number;
float fair;
	cout<<"Enter Bus No: ";
	cin>>number;
	int n;
 for(n=0;n<p;n++)
 {
	 if(b[n].busn==number)
	 {
		if(b[n].tseat<=0)
		{
		cout<<"\tSORRY!"<<endl<<"\tNo  Seat Available\t";
		}
		else
		{
		 cout<<endl<<"Total seat available: "<<b[n].tseat;
		 cout<<endl<<"Enter Passenger's Name: ";
		 cin>>pname;
		 cout<<endl<<"Number of seats: ";
		 cin>>s;
		 while((b[n].tseat=b[n].tseat-s)<0)
			 {cout<<endl<<"Limit Exceed...Please re-enter ";
			 b[n].tseat=b[n].tseat+s;
				cin>>s;


		 }


cout<<endl<<"Your purchase is completed"<<endl;
cout<<"Bus No: ";
cout<<b[n].busn<<endl;
cout<<"From: ";
cout<<b[n].from<<" to "<<b[n].to<<endl;
cout<<"Departure: ";
cout<<b[n].dtym<<" O'clock"<<endl;
cout<<"Total seat: ";
cout<<s<<endl;
fair=300*s;
fair=fair+(fair*.7);
allsell=allsell+fair;
cout<<"Total Fair(with 7%vat): ";

cout.setf(ios::showpoint);
cout.precision(3);
cout.setf(ios::fixed,ios::floatfield);
cout.width(8);
cout<<fair<<endl;

cout.setf(ios::right,ios::adjustfield);
	cout.width(30);
cout<<"Thank You"<<endl<<endl;

			}
	 }
 }
system("PAUSE");
system("CLS");

}

int main()
 {
	int w,g=1;
 while(g){
 cout<<"\n\n\t\t\t\t==================================================="<<endl;
 cout<<"\t\t\t\t\t\tBus Ticketing System\n";
 cout<<"\t\t\t\t==================================================="<<endl;

 cout<<"\t\t\t\t\t 1 => Install\n\t\t\t\t\t 2 => List Available Bus\n\t\t\t\t\t 3 => Book Tickets\n\t\t\t\t\t 4 => Exit";
 cout<<"\n\n\t\t\t\t\t Enter your choice: ";
 cin>>w;
 switch(w){
 case 1:
	b[p].install();//fn1353p

 break;
 case 2:
	 b[0].show();
 break;
 case 3:
	b[p].book();

 break;
 case 4:
	 {
g=0;

cout<<endl<<"Total Sales:"<<allsell<<endl<<"******Thank You******"<<endl;
cout<<"Brought To You By code-projects.org";
break;
	 }
 }
}
return 0;
}
