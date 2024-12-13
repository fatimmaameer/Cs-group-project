#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<ctime>
#include<cctype>
struct schedule{
    string name;
    string foodnsnacks;
    string drinks;
    int minage;
    int price;
    int time;
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
    int time;//time when you reserve seat;
    
};

    
