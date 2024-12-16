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
    int rows, column;
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
const int MAX_COLUMN = 100;
const int MIN_ROW = 0;
const int MIN_COLUMN = 0;
// void loadschedule(); // to be defined with paramreters (), will load the struct of the movie from the schedules filevoid saveschedule();
// functions
void displaymenu();
void managerpassword();
void seatinglayout(int sccheduleindex, int row, int column);
void saveschedule();
// void ranumwhenseatreserved();
//  global variables
char seating[MAX_SCHEDULE][MAX_ROWS][MAX_COLUMN];
schedule schedules[MAX_SCHEDULE];
int schedulecount = 0;

reservation reservations[MAX_RESERVATION];
int reservationCount = 0;
int main()
{
    displaymenu();
    return 0;
}

void displaymenu()
{
    int choice;

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
void managerpassword()
{
    int password, actualpassword;
    actualpassword = 12345;
    string actdogname, bubble, blue, actfavclr, dogname, favclr;
    actdogname = "bubble";
    actfavclr = "blue";
    cout << "enter you password ";
    cin >> password;
    if (password == actualpassword)
    {
        cout << "wow your password is correct.\n";
        cout << "carry on.\n ";
        saveschedule();
    }
    else if (password != actualpassword)
    {
        cout << "forget password!!!!! \n ";
        cout << "try answering these question so that we can make sure you are manager \n ";
        cout << "your dog name\n";
        cin >> dogname;
        cout << "your fav clr\n";
        cin >> favclr;
        {
            if (dogname == actdogname && favclr == actfavclr)
            {
                saveschedule();
            }
        }
    }
    else
    {
        cout << "sorry you are not manager dont waste time go and do your work";
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
        cout << "Enter rows: ";
        cin >> s.rows;
        cout << "Enter column: ";
        cin >> s.column;
        seatinglayout(schedulecount, s.rows, s.column);
        outfile << s.name << " " << s.minage << " " << s.price
                << " " << s.time << " " << s.durationinmin  //in this file just wrote name age time rows number and column number etc
                << " " << s.foodnsnacks << " " << s.drinks
                << " " << s.rows << " " << s.column << endl;

        outfile.close();
        // Write the seating layout to the file named seating layout this is the separate file
        ofstream ffile;
        ffile.open("seatinglayout.txt");
        for (int i = 0; i < s.rows; i++)
        {
            for (int j = 0; j < s.column; j++)
            {
                seating[schedulecount][i][j] ='*';
           ffile<<seating[schedulecount][i][j]<<' ';

            }
             ffile << endl;
        }
        
            
                
        ffile.close();
    }
}

void seatinglayout(int scheduleindex, int rows, int column)
{

    if (rows < MIN_ROW || rows > MAX_ROWS || column < MIN_COLUMN || column > MAX_COLUMN)
    {
        cout << "invalid input ";
    }
    else
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < column; ++j)
            {
                seating[scheduleindex][i][j] = '*';
            }
        }
    }
    for (int i = 0; i < rows; ++i)
    {
        {
            for (int j = 0; j < column; ++j)
            {
                cout << seating[scheduleindex][i][j] << ' ';
            }
            cout << endl;
        }
    }
    scheduleindex++;
}
// void ranumwhenseatreserved(){

//}