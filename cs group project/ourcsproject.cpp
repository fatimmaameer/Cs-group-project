#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <cctype>
using namespace std;






// Structure for a schedule, which stores movie or event details
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
    int time; // Time when you reserve the seat
};

// Constants for max values in seating, schedule, and reservation
const int MAX_SCHEDULE = 100;
const int MAX_RESERVATION = 100;
const int MAX_ROWS = 100;
const int MAX_COLUMN = 100;

// Global variables
char seating[MAX_SCHEDULE][MAX_ROWS][MAX_COLUMN];
schedule schedules[MAX_SCHEDULE];
int scheduleCount = 0;

// Function prototypes
void displaymenu();
void managerpassword();
void loadSchedules();
void loadSeating(int scheduleIndex);
void reserveschedule();
void operatorpassword();
void initializeSeating(int scheduleIndex, int rows, int columns);
void saveschedule();
void displaySeating(int scheduleIndex);
void reserveSeat(int scheduleIndex);
void saveSeating(int scheduleIndex);
void cancelReservation(int scheduleIndex);
bool checkGenderAdjacency(int scheduleIndex, int row, int col, char gender, int userid);
void cancelSeat(int scheduleIndex, int userid);
void showHeader();

int main()
{
    loadSchedules();

    while (true)
    {
        displaymenu();
        char continueChoice;
        cout << "Do you want to continue with more operations? (Y/N): ";
        cin >> continueChoice;
        if (continueChoice == 'N' || continueChoice == 'n')
            break;
    }
    return 0;
}
void showHeader()
{
    system ("cls");
    cout << "\033[1;1H"; // Move the cursor to the top-left corner.
    cout << R"(
  _____  ______  _____ ______ _______      __  _______ _____ ____  _   _    _______     _______ _______ ______ __  __ 
 |  __ \|  ____|/ ____|  ____|  __ \ \    / /\|__   __|_   _/ __ \| \ | |  / ____\ \   / / ____|__   __|  ____|  \/  |
 | |__) | |__  | (___ | |__  | |__) \ \  / /  \  | |    | || |  | |  \| | | (___  \ \_/ / (___    | |  | |__  | \  / |
 |  _  /|  __|  \___ \|  __| |  _  / \ \/ / /\ \ | |    | || |  | | . ` |  \___ \  \   / \___ \   | |  |  __| | |\/| |
 | | \ \| |____ ____) | |____| | \ \  \  / ____ \| |   _| || |__| | |\  |  ____) |  | |  ____) |  | |  | |____| |  | |
 |_|  \_\______|_____/|______|_|  \_\  \/_/    \_\_|  |_____\____/|_| \_| |_____/   |_| |_____/   |_|  |______|_|  |_|
                                                                                                                      
                                                                                                                     
)";
  
     cout << "\033[8;1H\033[J"; // Clear content below the header only.// Set cursor position to row 4, column 1, below the header.
}

void loadSchedules()
{
    ifstream inFile("schedules.txt");
    if (!inFile)
        return;

    while (scheduleCount < MAX_SCHEDULE && inFile >> ws, getline(inFile, schedules[scheduleCount].name))
    {
        schedule &currentSchedule = schedules[scheduleCount];
        inFile >> currentSchedule.minage >> currentSchedule.price >> currentSchedule.time >> currentSchedule.durationinmin;
        inFile >> currentSchedule.foodnsnacks >> currentSchedule.drinks >> currentSchedule.rows >> currentSchedule.column >> currentSchedule.isMovie;
        inFile.ignore();
        
        loadSeating(scheduleCount);
        scheduleCount++;
    }
    inFile.close();
}

void loadSeating(int scheduleIndex)
{
    const schedule &schedule = schedules[scheduleIndex];
    ifstream inFile(schedule.name + "_seating.txt");
    if (!inFile)
    {
        initializeSeating(scheduleIndex, schedule.rows, schedule.column);
        return;
    }

    for (int i = 0; i < schedule.rows; ++i)
    {
        for (int j = 0; j < schedule.column; ++j)
        {
            inFile >> seating[scheduleIndex][i][j];
        }
    }
    inFile.close();
}

void displaymenu()
{
   while (true)
    {
        
        showHeader();
        cout << "\nPlease select your designation:\n";
        cout << "-----------------------------------------\n";
        cout << "1) Manager\n";
        cout << "2) Operator\n";
        cout << "3) Exit\n";
        cout << "-----------------------------------------\n";
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            managerpassword();
            break;
        case 2:
            showHeader();
            cout << "\n=========================================\n";
            cout << "           OPERATOR MENU                 \n";
            cout << "=========================================\n";
            operatorpassword();
            break;
        case 3:
            showHeader();
            cout << "\nThank you for using the Reservation System. Goodbye!\n";
            return;
        default:
            cout << "\nInvalid choice. Please try again.\n";
        }
    }

}

void managerpassword()
{
    
    showHeader();
    cout << "\n=========================================\n";
    cout << "           MANAGER MENU                  \n";
    cout << "=========================================\n";
    
    cout << "-----------------------------------------\n";
    cout << "          MANAGER PASSWORD LOGIN         \n";
    cout << "-----------------------------------------\n";
    int password, actualpassword = 12345;
    string actdogname = "bubble", actfavclr = "blue";
    string dogname, favclr;

    cout << "Enter your password: ";
    cin >> password;

    if (password == actualpassword)
    {
        cout << "\nPassword correct. Access granted.\n";
        saveschedule();
    }
    else
    {
        cout << "\nForgot password? Let's verify your identity.\n";
        cout << "-----------------------------------------\n";
        cout << "Security Questions:\n";
        cout << "1) What is your dog's name? ";
        cin >> dogname;
        cout << "2) What is your favorite color? ";
        cin >> favclr;

        if (dogname == actdogname && favclr == actfavclr)
        {
            cout << "\nIdentity verified. Access granted.\n";
            saveschedule();
        }
        else
        {
            cout << "\nSorry, couldn't verify identity\n";
        }
    }
}

void saveschedule()
{
    ofstream outfile("schedules.txt", ios::app);

    if (!outfile)
    {
        cout << "Your file does not exist.\n";
        return;
    }

    schedule s;
    char choice;
    showHeader();
    
    cout << "\n=====================================================\n";
    cout << "\n         Welcome to the schedule creator!\n";
    cout << "\n=====================================================\n";
    cout << "\nWhat service do you operate? cinema or Bus?  (C/B) \n";
    cin >> choice;
    cin.ignore();
    choice = toupper(choice);
    s.isMovie = (choice == 'C');

    cout << "Enter name of the movie/bus you want to create\n: ";
    getline(cin, s.name);
    cout << "\nEnter minimum age: ";
    cin >> s.minage;
    cout << "\nEnter price: ";
    cin >> s.price;
    cout << "\nEnter time (in '1200' format): ";
    cin >> s.time;
    cout << "\nEnter duration in minutes: ";
    cin >> s.durationinmin;
    cout << "\nEnter food and snacks: ";
    cin.ignore();
    getline(cin, s.foodnsnacks);
    cout << "\nEnter drinks: ";
    getline(cin, s.drinks);
    cout << "\nEnter rows: ";
    cin >> s.rows;
    cout << "\nEnter columns: ";
    cin >> s.column;

    outfile << s.name << "\n" << s.minage << " " << s.price
            << " " << s.time << " " << s.durationinmin
            << " " << s.foodnsnacks << " " << s.drinks
            << " " << s.rows << " " << s.column << " " << s.isMovie << endl;

    outfile.close();
    schedules[scheduleCount] = s;
    initializeSeating(scheduleCount, s.rows, s.column);
    scheduleCount++;
}

void initializeSeating(int scheduleIndex, int rows, int columns)
{
    if (rows < 0 || rows > MAX_ROWS || columns < 0 || columns > MAX_COLUMN)
    {
        cout << "\n         error           \n";
        cout << "\nInvalid input for rows or columns.\n";
        return;
    }

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            seating[scheduleIndex][i][j] = '*';
        }
    }

    saveSeating(scheduleIndex);
}

void operatorpassword()
{
    showHeader();
    int password, actualpassword = 2468;
    string actfvrtfood = "biryani", actfvrtcar = "bentley";
    string fvrtfood, fvrtcar;

    cout << "\n Enter your password: ";
    cin >> password;

    if (password == actualpassword)
    {
        cout << "\nPassword correct.\n";
        reserveschedule();
    }
    else
    {
        cout << "\nForgot password? Try answering these questions.\n";
        cout << "\nYour favorite food: ";
        cin >> fvrtfood;
        cout << "\nYour favorite car: ";
        cin >> fvrtcar;

        if (fvrtfood == actfvrtfood && fvrtcar == actfvrtcar)
        {
            reserveschedule();
        }
        else
        {
            cout << "\nIncorrect information.\n";
        }
    }
}

void reserveschedule()
{
    if (scheduleCount == 0)
    {
        cout << "\nNo schedules available. Ask the manager to set up a schedule.\n";
        return;
    }

    while (true)
    {
        showHeader();
        
        cout << "\n=========================================\n";
        cout << "         AVAILABLE SCHEDULES             \n";
        cout << "=========================================\n";

        for (int i = 0; i < scheduleCount; ++i)
        {
            cout << i + 1 << ". " << schedules[i].name << "\n";
        }

        cout << scheduleCount + 1 << ". Return to Main Menu\n";
        cout <<  "--------------------------------------------------------------------\n";     cout << "Enter your choice: ";
        cout <<  "\n";  
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == scheduleCount + 1)
            break;

        if (choice < 1 || choice > scheduleCount)
        {
            cout << "\nInvalid choice. Try again.\n";
            continue;
        }

        int scheduleIndex = choice - 1;

        while (true)
        {
            showHeader();
            
            cout << "\n-----------------------------------------\n";
            cout << "  Options for Schedule: " << schedules[scheduleIndex].name << "\n";
            cout << "-----------------------------------------\n";
            cout << "1. View Seating Layout\n";
            cout << "2. Reserve a Seat\n";
            cout << "3. Cancel a Reservation\n";
            cout << "4. Return to Schedule Selection\n";
            cout << "-------------------------------------------\n";
            cout << "Enter your choice: ";
            int opChoice;
            cin >> opChoice;

            switch (opChoice)
            {
            case 1:
               
                showHeader();
                displaySeating(scheduleIndex);
                system("pause");
                break;
            case 2:
                
                showHeader();
                reserveSeat(scheduleIndex);
                system("pause");
                break;
            case 3:
                
                showHeader();
                cancelSeat(scheduleIndex, -1);
                system("pause");
                break;
            case 4:
                return;
            default:
                cout << "Invalid choice. Try again.\n";
            }
        }
    }
}

bool checkGenderAdjacency(int scheduleIndex, int row, int col, char gender, int userid)
{
    const int rowOffset[] = {-1, 1, 0, 0};
    const int colOffset[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; ++i)
    {
        int newRow = row + rowOffset[i];
        int newCol = col + colOffset[i];

        if (newRow >= 0 && newRow < schedules[scheduleIndex].rows && newCol >= 0 && newCol < schedules[scheduleIndex].column)
        {
            char adjacent = seating[scheduleIndex][newRow][newCol];
            if ((gender == 'M' && adjacent == 'F') || (gender == 'F' && adjacent == 'M'))
            {
                cout << "\nCannot reserve adjacent to opposite gender seat.\n\n\n";
                return false;
            }
        }
    }

    return true;
}

void reserveSeat(int scheduleIndex)
{
    
    showHeader();
    cout << "\n==================================================\n";
    cout << " \n             Reservation tab\n";
     cout <<"\n==================================================\n";
    int row, col, userid;
    char gender;
    cout << "\nEnter User ID: ";
    cin >> userid;
    cout << "\nEnter your gender (M/F): ";
    cin >> gender;
    gender = toupper(gender);
    cout << "\nEnter the row and column to reserve (1-" << schedules[scheduleIndex].rows << " for rows and 1-" << schedules[scheduleIndex].column << " for columns): ";
    cin >> row >> col;

    if (row < 1 || row > schedules[scheduleIndex].rows || col < 1 || col > schedules[scheduleIndex].column)
    {
        cout << "\nInvalid seat number.\n";
        return;
    }

    if (seating[scheduleIndex][row - 1][col - 1] != '*')
    {
        cout << "\nSeat already reserved. Try again.\n\n";
        return;
    }

    if (!checkGenderAdjacency(scheduleIndex, row - 1, col - 1, gender, userid))
    {
        return;
    }

    seating[scheduleIndex][row - 1][col - 1] = (gender == 'M') ? 'M' : 'F';
    cout << "\nSeat reserved successfully!\n\n\n";
    saveSeating(scheduleIndex);
}

void cancelSeat(int scheduleIndex, int userid)
{
    int row, col;
    cout << "\nEnter row and column of the seat to cancel (1-" << schedules[scheduleIndex].rows << " for rows and 1-" << schedules[scheduleIndex].column << " for columns): ";
    cin >> row >> col;

    if (row < 1 || row > schedules[scheduleIndex].rows || col < 1 || col > schedules[scheduleIndex].column || seating[scheduleIndex][row - 1][col - 1] == '*')
    {
        cout << "\nNo reservation found at this seat.\n";
        return;
    }

    seating[scheduleIndex][row - 1][col - 1] = '*';
    cout << "Reservation canceled successfully!\n";
    saveSeating(scheduleIndex);
}

void displaySeating(int scheduleIndex)
{
    cout << "\nSeating Layout for " << schedules[scheduleIndex].name << ":\n";
    for (int i = 0; i < schedules[scheduleIndex].rows; ++i)
    {
        for (int j = 0; j < schedules[scheduleIndex].column; ++j)
        {
            cout << seating[scheduleIndex][i][j] << ' ';
        }
        cout << endl;
    }
}

void saveSeating(int scheduleIndex)
{
    ofstream ffile;
    string filename = schedules[scheduleIndex].name + "_seating.txt";
    ffile.open(filename);

    if (!ffile)
    {
        cout << "\nError opening seating layout file.\n";
        return;
    }

    for (int i = 0; i < schedules[scheduleIndex].rows; i++)
    {
        for (int j = 0; j < schedules[scheduleIndex].column; j++)
        {
            ffile << seating[scheduleIndex][i][j] << ' ';
        }
        ffile << endl;
    }

    ffile.close();
}
