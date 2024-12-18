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
    bool isMovie;
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
int scheduleCount = 0;
// void loadschedule(); // to be defined with paramreters (), will load the struct of the movie from the schedules filevoid saveschedule();
// functions
void displaymenu();
void managerpassword();
void reserveschedule();
void operatorpassword();
void seatinglayout(int sccheduleindex, int row, int column);
void enhancedVisualization(const string &text, char borderChar);
void saveschedule();
void displaySeating(int scheduleIndex);
  
void reserveSeat(int scheduleIndex);
     
void saveSeating(int scheduleIndex);
     
void cancelReservation (int scheduleIndex);



// global variables
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
        operatorpassword();
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
    cout <<"enter you password ";
    cin >> password;
    if (password == actualpassword)
    {    
        cout<<"wow your password is correct.\n";
        cout<<"carry on.\n ";
        saveschedule();
    }
    else if (password != actualpassword)
    {
        cout<<"forget password!!!!! \n ";
        cout<<"try answering these question so that we can make sure you are manager \n ";
        cout<<"your dog name\n";
        cin >> dogname;
        cout<<"your fav clr\n";
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
        cout<<"sorry you are not manager dont waste time go and do your work";
    }
}
void saveschedule()
{
    ofstream outfile;
    outfile.open("filee.txt");
    char choice;

    if (!outfile)
    {
        cout << "Your file does not exist ";
    }
    else
    {

        schedule s;
        cout<<"Enter name: ";
        cin.ignore();
        getline(cin, s.name);
        cout << " Is it a movie?";
        cin >> choice;
        s.isMovie = (choice == 'C' || choice == 'c');
        cout<<"Enter minimum age required: ";
        cin >> s.minage;
        cout<<"Enter price: ";
        cin >> s.price;
        cout<<"Enter time: ";
        cin >> s.time;
        cout<<"Enter duration in minutes: ";
        cin >> s.durationinmin;
        cout<<"Enter food or snack you want in the menu: ";
        cin.ignore();
        getline(cin, s.foodnsnacks);
        cout<<"Enter drinks you want in the menu: ";
        getline(cin, s.drinks);
        cout<<"Enter rows: ";
        cin >> s.rows;
        cout<<"Enter column: ";
        cin >> s.column;
        seatinglayout(schedulecount, s.rows, s.column);
        outfile << s.name << " " << s.minage << " " << s.isMovie << " "<< s.price
                << " " << s.time << " " << s.durationinmin
                << " " << s.foodnsnacks << " " << s.drinks
                << " " << s.rows << " " << s.column << endl;
        
        
         // Write the seating layout to the file 
         for (int i = 0; i < s.rows; i++) 
         {
             for (int j = 0; j < s.column; j++) 
         { 
            outfile << seating[schedulecount][i][j] << " "; 
         } outfile << endl;
    } schedulecount++;
    outfile.close();
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
    for (int i = 0; i < rows; ++i){
        {
            for (int j = 0; j < column; ++j)
            {
                cout<<seating[scheduleindex][i][j] << ' ';
            }
            cout<<endl;
        }

}scheduleindex++;

}
void operatorpassword()
{
    int password, actualpassword;
    actualpassword = 2468;
    string actfvrtfood = "biryani";
    string actfvrtcar = "bentley";
    string fvrtfood, fvrtcar;

    cout << "Enter your password: ";
    cin >> password;

    if (password == actualpassword)
    {
        cout << "Wow, your password is correct.\n";
        cout << "Carry on.\n";
        reserveschedule();
    }
    else
    {
        cout << "Forgot password? \n";
        cout << "Try answering these questions to verify your identity: \n";
        cout << "Your favourite food: ";
        cin >> fvrtfood;
        cout << "Your favourite car: ";
        cin >> fvrtcar;

        if (fvrtfood == actfvrtfood && fvrtcar == actfvrtcar)
        {
            reserveschedule();
        }
        else
        {
            cout << "Sorry, verification failed. You are not authorized.\n";
        }
    }
}
void reserveschedule()
{   
    //check if any scheudles are available
    if (scheduleCount == 0) {
        cout << "No schedules available. Please ask the manager to set up a schedule first.\n";
        return;
    }
    while (true) {
        //display a title for operator menu
        enhancedVisualization("Operator Menu", '=');
        //Display the list of available schedules
        cout << "Available Schedules:\n";
        for (int i = 0; i < scheduleCount; ++i) {
            cout << i + 1 << ". " << schedules[i].name << " (" 
                 << (schedules[i].isMovie ? "Cinema" : "Bus Service") << ")\n";
        }
        cout << scheduleCount + 1 << ". Return to Main Menu\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == scheduleCount + 1) return;
        //validate the selected schedule
        if (choice < 1 || choice > scheduleCount) {
            cout << "Invalid choice. Please try again.\n";
            continue;
        }

        int scheduleIndex = choice - 1;
        

        while (true) {
            cout << "1. View Seating Layout\n" //display the current sitting layout
                 << "2. Reserve a Seat\n"  //allowing reserving in specific seat
                 << "3. Cancel a Reservation\n" //allow canceling an existing reservation
                 << "4. Return to Schedule Selection\n"; //go back to the schedule list
            cout << "Enter your choice: ";
            int opChoice;
            cin >> opChoice;
            //  user choices
            switch (opChoice) {
            case 1:
                displaySeating(scheduleIndex); //will displaySeating by using schedulecount intitalixzed at line xyz adn will
                // use xyz logic to perform
                break;
            case 2:
                reserveSeat(scheduleIndex); //reserve seat
                saveSeating(scheduleIndex); // saving a updated seat information
                break;
            case 3:
                cancelReservation(scheduleIndex); //Cancel reservation
                saveSeating(scheduleIndex); //save updating seat info
                break;
            case 4:
                return; //exit to schedule selection menu
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        }
    }




}
void enhancedVisualization(const string &text, char borderChar) {
    string border(text.length(), borderChar);
    cout << border << endl
         << text << endl
         << border << endl;
}



