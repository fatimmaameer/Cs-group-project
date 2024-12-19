#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <cctype>
using namespace std;
// structure for a schedule, which stores movie or event details
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
void displaymenu(); // Display the main menu to the user
void managerpassword();
void reserveschedule();
void operatorpassword();
void seatinglayout(int sccheduleindex, int rows, int column);
void enhancedVisualization(const string &text, char borderChar); // Function to enhance visualization with borders
void saveschedule();
void displaySeating(int scheduleIndex);
void reserveSeat(int scheduleIndex);
void saveSeating(int scheduleIndex); // Save the seating arrangement after reservation
void cancelReservation(int scheduleIndex);
// global variables
char seating[MAX_SCHEDULE][MAX_ROWS][MAX_COLUMN];
schedule schedules[MAX_SCHEDULE];
int schedulecount = 0;

reservation reservations[MAX_RESERVATION];
int reservationCount = 0;

int main()
{
    displaymenu(); // Call the main menu function to begin the user interaction
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
    cout << "enter you password ";
    cin >> password;
    if (password == actualpassword)
    {
        cout << "wow your password is correct.\n";
        cout << "carry on.\n ";
        saveschedule(); // If password is correct, allow the manager to save a schedule
    }
    else if (password != actualpassword)
    {
        // If password is incorrect, ask for security questions
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
    outfile.open("filee.txt", ios::app); // Open the file in append mode to save schedule details

    if (!outfile)
    {
        cout << "Your file does not exist.\n";
        return; // Exit function if file could not be opened
    }

    schedule s; // Prompt user for schedule details
    cout << "Enter name: ";

    getline(cin, s.name);
    cin.ignore();
    cout << "Enter minimum age required: ";
    cin >> s.minage;
    cin.ignore();
    cout << "Enter price: ";
    cin >> s.price;
    cin.ignore();
    cout << "Enter time: ";
    cin >> s.time;
    cin.ignore();
    cout << "Enter duration in minutes: ";
    cin >> s.durationinmin;
    cin.ignore();
    cout << "Enter food or snack you want in the menu: ";
    getline(cin, s.foodnsnacks);
    cin.ignore();
    cout << "Enter drinks you want in the menu: ";
    getline(cin, s.drinks);
    cin.ignore();
    cout << "Enter rows: ";
    cin >> s.rows;
    cin.ignore();
    cout << "Enter columns: ";
    cin >> s.column;
    cin.ignore();
    // Initialize the seating layout before saving schedule details
    seatinglayout(scheduleCount, s.rows, s.column);

    // Save schedule details to file
    outfile << s.name << " " << s.minage << " " << s.price
            << " " << s.time << " " << s.durationinmin
            << " " << s.foodnsnacks << " " << s.drinks
            << " " << s.rows << " " << s.column << endl;

    outfile.close(); // Close schedule file

    // Write the seating layout to the 'seatinglayout.txt' file
    ofstream ffile;
    ffile.open("seatinglayout.txt", ios::app); // Open in append mode

    if (!ffile)
    {
        cout << "Error opening seating layout file.\n";
        return;
    }

    // Write seating layout (initialize all seats as available with '*')
    for (int i = 0; i < s.rows; i++)
    {
        for (int j = 0; j < s.column; j++)
        {
            seating[scheduleCount][i][j] = '*'; // Set all seats as available ('*')
            ffile << seating[scheduleCount][i][j] << ' ';
        }
        ffile << endl;
    }

    ffile.close();   // Close the seating layout file
    scheduleCount++; // Increment the schedule count after saving
}

void seatinglayout(int scheduleIndex, int rows, int column)
{
    // Check if the rows and columns are within valid limits
    if (rows < MIN_ROW || rows > MAX_ROWS || column < MIN_COLUMN || column > MAX_COLUMN)
    {
        cout << "Invalid input for rows or columns.\n";
        return; // Exit function if the input is invalid
    }

    // Set all seats as available ('*')
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < column; ++j)
        {
            seating[scheduleIndex][i][j] = '*'; // Set all seats as available ('*')
        }
    }

    // Display seating arrangement for the operator
    cout << "Seating layout for schedule: " << schedules[scheduleIndex].name << endl;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < column; ++j)
        {
            cout << seating[scheduleIndex][i][j] << ' ';
        }
        cout << endl;
    }
}
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
    // check if any scheudles are available
    if (scheduleCount == 0)
    {
        cout << "No schedules available. Please ask the manager to set up a schedule first.\n";
        return;
    }
    while (true)
    {
        // display a title for operator menu
        enhancedVisualization("Operator Menu", '=');
        // Display the list of available schedules
        cout << "Available Schedules:\n";
        for (int i = 0; i < scheduleCount; ++i)
        {
            cout << i + 1 << ". " << schedules[i].name << " ("
                 << (schedules[i].isMovie ? "Cinema" : "Bus Service") << ")\n";
        }
        // if operator choose to exit menu
        cout << scheduleCount + 1 << ". Return to Main Menu\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == scheduleCount + 1)
            return;

        if (choice < 1 || choice > scheduleCount)
        {
            cout << "Invalid choice. Please try again.\n";
            continue;
        }

        int scheduleIndex = choice - 1;
        seatinglayout(schedulecount);

        while (true)
        {
            cout << "1. View Seating Layout\n"
                 << "2. Reserve a Seat\n"
                 << "3. Cancel a Reservation\n"
                 << "4. Return to Schedule Selection\n";
            cout << "Enter your choice: ";
            int opChoice;
            cin >> opChoice;

            switch (opChoice)
            {
            case 1:
                displaySeating(schedulecount);
                break;
            case 2:
                reserveSeat(schedulecount);
                saveSeating(schedulecount);
                break;
            case 3:
                cancelReservation(scheduleIndex);
                saveSeating(schedulecount);
                break;
            case 4:
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        }
    }
}

void reserveSeat(schedulecount)
{
    ofstream file;
    file.open("reserveseat.txt", ios::app); // Open the reservation file in append mode
    if (!file)
    {
        cout << "Error opening the file to save seat reservation.\n";
        return;
    }
    int row, col;
    char gender;
    int randomNumbers[scheduleIndex][row][col];
    cout << "Enter your gender (M/F): ";
    cin >> gender;
    cout << "Enter the row and column to reserve (0-" << schedules[scheduleIndex].rows - 1
         << " for rows and columns): ";
    cin >> row >> col;

    // Check if the seat selection is valid
    if (row < 0 || row >= schedules[scheduleIndex].rows || col < 0 || col >= schedules[scheduleIndex].columns)
    {
        cout << "Invalid seat selection.\n";
        return;
    }

    // Check if the seat is already reserved
    if (seating[scheduleIndex][row][col] != '.')
    {
        cout << "Seat already reserved.\n";
        return;
    }

    // Check gender compatibility with adjacent seats
    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            int adjRow = row + i;
            int adjCol = col + j;

            // Skip out-of-bounds or the seat itself
            if ((i == 0 && j == 0) || adjRow < 0 || adjRow >= schedules[scheduleIndex].rows ||
                adjCol < 0 || adjCol >= schedules[scheduleIndex].columns)
            {
                continue;
            }

            // Check if the adjacent seat has an incompatible gender
            if ((gender == 'M' || gender == 'm') && seating[scheduleIndex][adjRow][adjCol] == '*')
            {
                cout << "Cannot reserve. A male and a female cannot sit next to each other.\n";
                return;
            }

            if ((gender == 'F' || gender == 'f') && seating[scheduleIndex][adjRow][adjCol] == '\\')
            {
                cout << "Cannot reserve. A male and a female cannot sit next to each other.\n";
                return;
            }
        }
    }

    // Reserve the seat
    randomNumbers[scheduleIndex][row][col] = rand() % 10 + 1;                         // Generate random number
    seating[scheduleIndex][row][col] = (gender == 'M' || gender == 'm') ? '\\' : '*'; // Gender-based symbol

    // Save reservation details to the file
    file << "Schedule: " << schedules[scheduleIndex].name << "\n";
    file << "Reserved Seat at Row " << row << ", Column " << col
         << " for Gender: " << gender
         << " with Random Number: " << randomNumber << "\n";

    cout << "Seat reserved successfully! Random number for this seat: " << randomNumber << "\n";

    // Close the file after saving the reservation
    file.close();
    displaySeating(scheduleIndex); // Show updated seating and reservation details
}
// Displays the seating layout of a schedule
void displaySeating(int scheduleIndex)
{
    ifstream file("reserveseat.txt"); // Open the reservation file for reading

    if (!file)
    {
        cout << "Error opening the file to display seat reservations.\n";
        return;
    }

    cout << "Seating Layout for Schedule: " << schedules[scheduleIndex].name << endl;

    // Display the seating layout from the 'seating' array

    for (int i = 0; i < schedules[scheduleIndex].rows; ++i)
    {
        for (int j = 0; j < schedules[scheduleIndex].column; ++j)
        {
            cout << seating[scheduleIndex][i][j] << ' ';
        }
        cout << endl;
    }
    // Now, read and display the reservation details from the file
    string line;
    cout << "\nReservation Details:\n";
    while (getline(file, line))
    {
        // Display only the reservations for the current schedule
        if (line.find(schedules[scheduleIndex].name) != string::npos)
        {
            cout << line << endl; // Print reservation details for this schedule
        }
    }

    file.close(); // Close the file after reading
}
void cancelReservation(int scheduleIndex)
{
    int row, col;

    cout << "Enter the row and column of the seat to cancel (0-"
         << schedules[scheduleIndex].rows - 1
         << " for rows and columns): ";
    cin >> row >> col;

    if (row < 0 || row >= schedules[scheduleIndex].rows || col < 0 || col >= schedules[scheduleIndex].column)
    {
        cout << "Invalid seat selection. Please try again.\n";
        return;
    }

    if (seating[scheduleIndex][row][col] == '*')
    {
        cout << "This seat is already available.\n";
        return;
    }
}
