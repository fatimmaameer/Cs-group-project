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
    cout << "Enter your designation please!\n";
    cout << "1 = Manager\n";
    cout << "2 = Operator\n";
    cout << "3 = Exit\n";
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "1) I'm a manager\n";
        managerpassword(); // Call manager login and password verification
        break;
    case 2:
        cout << "2) I'm an operator\n";
        operatorpassword(); // Call operator login and password verification
        break;
    case 3:
        cout << "3) Exit\n";
        break;
    default:
        cout << "Invalid choice.\n";
        break;
    }
}

void managerpassword()
{
    int password, actualpassword = 12345;
    string actdogname = "bubble", actfavclr = "blue";
    string dogname, favclr;

    cout << "Enter your password: ";
    cin >> password;

    if (password == actualpassword)
    {
        cout << "Password correct.\n";
        saveschedule(); // If correct, proceed to save schedule
    }
    else
    {
        cout << "Forgot password? Try answering these questions.\n";
        cout << "Your dog's name: ";
        cin >> dogname;
        cout << "Your favorite color: ";
        cin >> favclr;

        if (dogname == actdogname && favclr == actfavclr)
        {
            saveschedule(); // If security answers are correct, proceed
        }
        else
        {
            cout << "Sorry, incorrect information.\n";
        }
    }
}

void saveschedule()
{
    ofstream outfile;
    outfile.open("filee.txt");
    char choice;

    if (!outfile)
    {
        cout << "Your file does not exist.\n";
        return; // Exit function if file could not be opened
    }

    schedule s; // Prompt user for schedule details
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, s.name);
    cout << "Enter minimum age: ";
    cin >> s.minage;
    cout << "Enter price: ";
    cin >> s.price;
    cout << "Enter time: ";
    cin >> s.time;
    cout << "Enter duration in minutes: ";
    cin >> s.durationinmin;
    cout << "Enter food and snacks: ";
    cin.ignore();
    getline(cin, s.foodnsnacks);
    cout << "Enter drinks: ";
    getline(cin, s.drinks);
    cout << "Enter rows: ";
    cin >> s.rows;
    cout << "Enter columns: ";
    cin >> s.column;

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

void operatorpassword()
{
    int password, actualpassword = 2468;
    string actfvrtfood = "biryani", actfvrtcar = "bentley";
    string fvrtfood, fvrtcar;

    cout << "Enter your password: ";
    cin >> password;

    if (password == actualpassword)
    {
        cout << "Password correct.\n";
        reserveschedule(); // Proceed to reserve schedule
    }
    else
    {
        cout << "Forgot password? Try answering these questions.\n";
        cout << "Your favorite food: ";
        cin >> fvrtfood;
        cout << "Your favorite car: ";
        cin >> fvrtcar;

        if (fvrtfood == actfvrtfood && fvrtcar == actfvrtcar)
        {
            reserveschedule(); // If answers are correct, proceed
        }
        else
        {
            cout << "Incorrect information.\n";
        }
    }
}


void reserveschedule()
{
    if (scheduleCount == 0)
    {
        cout << "No schedules available. Ask the manager to set up a schedule.\n";
        return;
    }

    while (true)
    {
        cout << "Available Schedules:\n";
        for (int i = 0; i < scheduleCount; ++i)
        {
            cout << i + 1 << ". " << schedules[i].name << " (" << (schedules[i].isMovie ? "Movie" : "Bus Service") << ")\n";
        }

        cout << scheduleCount + 1 << ". Return to Main Menu\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == scheduleCount + 1)
            return;

        if (choice < 1 || choice > scheduleCount)
        {
            cout << "Invalid choice. Try again.\n";
            continue;
        }

        int scheduleIndex = choice - 1;
        seatinglayout(scheduleIndex, schedules[scheduleIndex].rows, schedules[scheduleIndex].column);

        while (true)
        {
            cout << "1. View Seating Layout\n";
            cout << "2. Reserve a Seat\n";
            cout << "3. Cancel a Reservation\n";
            cout << "4. Return to Schedule Selection\n";
            cout << "Enter your choice: ";
            int opChoice;
            cin >> opChoice;

            switch (opChoice)
            {
            case 1:
                displaySeating(scheduleIndex);
                break;
            case 2:
                reserveSeat(scheduleIndex);
                break;
            case 3:
                cancelReservation(scheduleIndex);
                break;
            case 4:
                return;
            default:
                cout << "Invalid choice. Try again.\n";
            }
        }
    }
}

void reserveSeat(int scheduleIndex)
{
    int row, col;
    char gender;
    cout << "Enter your gender (M/F): ";
    cin >> gender;
    cout << "Enter the row and column to reserve (0-" << schedules[scheduleIndex].rows - 1 << " for rows and columns): ";
    cin >> row >> col;

    if (row >= schedules[scheduleIndex].rows || col >= schedules[scheduleIndex].column || seating[scheduleIndex][row][col] != '*')
    {
        cout << "Invalid seat or already reserved. Try again.\n";
        return;
    }

    seating[scheduleIndex][row][col] = (gender == 'M' || gender == 'm') ? '/' : '*';
    cout << "Seat reserved successfully!\n";
}


// Displays the seating layout of a schedule
void displaySeating(int scheduleIndex)
{
    for (int i = 0; i < schedules[scheduleIndex].rows; ++i)
    {
        for (int j = 0; j < schedules[scheduleIndex].column; ++j)
        {
            cout << seating[scheduleIndex][i][j] << ' ';
        }
        cout << endl;
    }
}
void cancelReservation(int scheduleIndex)
{
    int row, col;
    cout << "Enter row and column of the seat to cancel (0-" << schedules[scheduleIndex].rows - 1 << "): ";
    cin >> row >> col;

    if (row >= schedules[scheduleIndex].rows || col >= schedules[scheduleIndex].column || seating[scheduleIndex][row][col] == '*')
    {
        cout << "No reservation found at this seat.\n";
        return;
    }

    seating[scheduleIndex][row][col] = '*';
    cout << "Reservation canceled successfully!\n";
}
