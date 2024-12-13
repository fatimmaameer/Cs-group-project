#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <cctype>
struct schedule
{
    string name;
    int minage;
    int price;
    int time;
    int durationinmin;
    string foodnsnacks;
    string drinks;
    int seatinglayout;
};
struct reservation
{
    int chooseschadule;
    int userid;
    int age;
    string gender;
    int row;
    int column;
    int time; // time when you reserve seat;
};
void loadschedule();
void saveschedule();
int main()
{
    int choice;
    cout << "enter your designation please !\n";
    cout << "1= manager\n";
    cout << "2=  operator\n";
    cout << "3=  exit \n" ;
    cin >> choice;
    switch (choice)
    {
    case 1:
        cout << "1= I'm a manager\n";
        saveschedule();
        break;
    case 2:
        cout << "2= I'm an operator\n";
        break;
    case 3:
        cout << "3= I want to exit \n";
        break;
    default:
       cout<<"invalid choice ";
       break;
    }
    return 0;
}
void saveschedule(){
ofstream outfile;
outfile.open("file.txt");
if(!outfile){
    cout<<"your file doesnot exists ";
}
else {
    outfile<<schedule.name<<schedule.minage<<schedule.price;
    outfile<<schedule.time<<schedule.durationinmin<<schedule.foodnsnacks<<schedule.drinks<<schedule.seatinglayout;

}
}