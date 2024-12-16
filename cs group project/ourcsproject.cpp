#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <cctype>
using namespace std;
//structure for a schedule, which stores movie or event details
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
// Constants for max values in seating, schedule, and reservation
const int MAX_SCHEDULE = 100;
const int MAX_RESERVATION = 100;
const int MAX_ROWS = 100;
const int MAX_COLUMN = 100;
const int MIN_ROW = 0;
const int MIN_COLUMN = 0;
int scheduleCount = 0;
// void loadschedule(); // to be defined with paramreters (), will load the struct of the movie from the schedules filevoid saveschedule();
// functions
void displaymenu();// Display the main menu to the user
void managerpassword();
void reserveschedule();
void operatorpassword();
void seatinglayout(int sccheduleindex, int row, int column);// Create seating layout for the schedule
void enhancedVisualization(const string &text, char borderChar);// Function to enhance visualization with borders
void saveschedule();
void displaySeating(int scheduleIndex);
void reserveSeat(int scheduleIndex);  
void saveSeating(int scheduleIndex);// Save the seating arrangement after reservation   
void cancelReservation (int scheduleIndex);



// global Variables
char seating[MAX_SCHEDULE][MAX_ROWS][MAX_COLUMN];
schedule schedules[MAX_SCHEDULE];
int schedulecount = 0;

reservation reservations[MAX_RESERVATION];
int reservationCount = 0;

int main()
{
    displaymenu();  // Call the main menu function to begin the user interaction
    return 0;
}
// Displays the main menu for the user to select their role
void displaymenu()
{
    
    int choice;

    cout << "enter your designation please !\n";
    cout << "1= manager\n";
    cout << "2= operator\n";
    cout << "3= exit \n";
    cin >> choice;
     // Based on user choice, call the respective login function or exit
    switch (choice)
    {
    case 1:
        cout << "1= I'm a manager\n";
        managerpassword(); // Call manager login and password verification
        break;
    case 2:
        cout << "2= I'm an operator\n";
        operatorpassword(); // Call operator login and password verification
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
    // Manages manager login and verifies their identity
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
        saveschedule();  // If password is correct, allow the manager to save a schedule
    }
    else if (password != actualpassword)
    {
        // If password is incorrect, ask for security questions
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
    outfile.open("filee.txt"); // Open the file to save schedule details

    if (!outfile)
    {
        cout << "Your file does not exist ";
    }
    else
    {

        schedule s;
         // Prompt user for schedule details
        cout<<"Enter name: ";
        cin.ignore();
        getline(cin, s.name);
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
        // Save schedule details to file
        outfile << s.name << " " << s.minage << " " << s.price
                << " " << s.time << " " << s.durationinmin
                << " " << s.foodnsnacks << " " << s.drinks
                << " " << s.rows << " " << s.column << endl;
        
        
          // Write seating layout to file
         for (int i = 0; i < s.rows; i++) 
         { for (int j = 0; j < s.column; j++) 
         { 
            outfile << seating[schedulecount][i][j] << " "; // Write seat status to file
         } outfile << endl;
    } schedulecount++;
    outfile.close();
}
}

void seatinglayout(int scheduleindex, int rows, int column)
{
    
  // Initialize seating arrangement for the schedule
    if (rows < MIN_ROW || rows > MAX_ROWS || column < MIN_COLUMN || column > MAX_COLUMN)
    {
        cout << "invalid input ";
    }
    else
    {
         // Set all seats as available ('*')
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
            // Display seating arrangement for the operator
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
        //if operator choose to exit menu
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
                displaySeating(scheduleIndex); //show the seating layout for schedule
                break;
            case 2:
                reserveSeat(scheduleIndex); // Call to reserve a seat
                saveSeating(scheduleIndex); // Save the seating after reservation
                break;
            case 3:
                cancelReservation(scheduleIndex); //Cancel reservation
                saveSeating(scheduleIndex); // Save after cancellation
                break;
            case 4:
                return; //exit to schedule selection menu
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        }
    }




}
//function is used to add borders around text to improve the user experience
void enhancedVisualization(const string &text, char borderChar) {
    string border(text.length(), borderChar);
    cout << border << endl
         << text << endl
         << border << endl;
}



