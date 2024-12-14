#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <cctype>
using namespace std;

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
const int MAX_SCHEDULE = 100;
const int MAX_RESERVATION = 100;
const int MAX_ROWS = 100;
const int MAX_COLUMN=100;

//void loadschedule(); // to be defined with paramreters (), will load the struct of the movie from the schedules file
void saveschedule();
void displaymenu();
void managerpassword();


int main()
{
    displaymenu();
    return 0;
}


void displaymenu(){
    int  choice;
    
    cout << "enter your designation please !\n";
    cout << "1= manager\n";
    cout << "2= operator\n";
    cout << "3= exit \n";
    cin >> choice;
    switch (choice)
    {
    case 1:
        cout << "1= I'm a manager\n";
        managerpassword();
        break;
    case 2:
        cout << "2= I'm an operator\n";
        break;
    case 3:
        cout << "3= I want to exit \n";
        break;
    default:
        cout << "invalid choice ";
        break;
    }
}

void saveschedule()
{
    ofstream outfile;
    outfile.open("filee.txt");

    if (!outfile)
    {
        cout << "Your file does not exist ";
    }
    else
    {

        schedule s;
        cout << "Enter name: ";
        cin.ignore(); 
        getline(cin, s.name);
        cout << "Enter minimum age required: ";
        cin >> s.minage;
        cout << "Enter price: ";
        cin >> s.price;
        cout << "Enter time: ";
        cin >> s.time;
        cout << "Enter duration in minutes: ";
        cin >> s.durationinmin;
        cout << "Enter food or snack you want in the menu: ";
        cin.ignore(); 
        getline(cin, s.foodnsnacks);
        cout << "Enter drinks you want in the menu: "; 
        getline(cin, s.drinks);
        cout << "Enter seating layout: "; 
        cin >> s.seatinglayout; 
        outfile << s.name << " " << s.minage << " " << s.price 
                << " " << s.time << " " << s.durationinmin 
                << " " << s.foodnsnacks << " " << s.drinks 
                << " " << s.seatinglayout << endl;
                 } outfile.close();
    }
void managerpassword()
    {
        int password, actualpassword;
        actualpassword = 12345;
        string actdogname, bubble,blue,actfavclr, dogname, favclr;
        actdogname = bubble;
        actfavclr = blue;
        cout << "enter you password ";
        cin >> password;
        if (password == actualpassword)
        {
            cout << "carry on.\n ";
             saveschedule();
        }
        else
        {
            cout << "forget password!!!!! \n ";
            cout << "try answering these question so that we can make sure you are manager \n ";
            cout<<"your dog name\n";
            cin>>dogname;
            cout<<" your fav clr\n";
            cin>>favclr;
            if (dogname == actdogname && favclr == actfavclr)
            {
                saveschedule();
            }
            else
            {
                cout << "sorry you are not manager dont waste time go and do your work";
            }
        }
    }