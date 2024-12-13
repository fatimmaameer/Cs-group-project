#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <cctype>
using namespace std; 

struct schedule {
    string name;
    int minage;
    int price;
    int time;
    int durationinmin;
    string foodnsnacks;
    string drinks;
    int seatinglayout;
};

struct reservation {
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

int main() {
    int choice;
    cout << "enter your designation please !\n";
    cout << "1= manager\n";
    cout << "2= operator\n";
    cout << "3= exit \n" ;
    cin >> choice;
    switch (choice) {
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
        cout << "invalid choice ";
        break;
    }
    return 0;
}

void saveschedule() {
    ofstream outfile;
    outfile.open("file.txt");

    if (!outfile) {
        cout << "Your file does not exist ";
    } else {
        schedule s;  // 
        
        s.name = "Movie Schedule"; 
        s.minage = 18;
        s.price = 20;
        s.time = 120;
        s.durationinmin = 90;
        s.foodnsnacks = "Popcorn";
        s.drinks = "Soda";
        s.seatinglayout = 5;

        // Write the schedule details to the file
        outfile << s.name << " " << s.minage << " " << s.price << " "
                << s.time << " " << s.durationinmin << " "
                << s.foodnsnacks << " " << s.drinks << " "
                << s.seatinglayout << endl;
    }
}
