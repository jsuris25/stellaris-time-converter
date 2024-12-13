#include <iostream>
#include <cmath>
#include <vector>
//For sleep functionality
#include <unistd.h> // sleep()
#include <chrono> //time, units

// Returns true if detects non-digit to trigger throw
bool digitChecker(const std::string &num){
    for (int i=0; i < num.size(); i++){
        char dig = num[i];
        if (!std::isdigit(dig)){
            return true;
        }
    }
    return false;
}

//Checks if inputed unit is valid, else return false
bool validTemporalUnit(const char &t_input){
    char val_units[] = {'r', 'm', 'd'};
    for(int i = 0; i < 3; i++){
        if (t_input == val_units[i]){
            return true;
        }
    }
    return false;
}

//Loops until valid confirmed unit is chosen
char ChooseUnit(){
    bool confirm = false;
    char unit;
    while (!confirm){
        std::cout << "What temporal units do you wish to convert to?\n"
            << "Years[r]\nMonths[m]\nDays[d]\n";
        std::cin >> unit;
        //Confirm vaild t_unit
        if (!validTemporalUnit(unit)){
            std::cerr << "Invalid input received. Please input a "
                << "matching corresponding characters.\n";    
            continue;
        }

        std::cout << "Do you wish to confirm? [y/n] ";
        char cfrm;
        std::cin >> cfrm;
        if(cfrm == 'y')
            confirm = true;
    }
    return unit;
}


void TimeConversion(const char &t_unit, std::vector<int> &time){
    int f_years = 0;
    int f_months = 0;
    int f_days = 0;
    switch (t_unit){
    //Convert to Days
    case 'd':
        std::cout << "\nCONVERTING TO DAYS\n";
        //Year -> Days + Months -> Days + Days
        f_days = time[0]*360 + time[1]*30 + time[2];

        break;

    //Convert to Months
    case 'm':
        std::cout << "\nCONVERTING TO MONTHS\n";
        //Year -> Month + Days -> Months + R Days
        f_months = time[0]*12 + time[1] + time[2]/30;
        f_days = time[2]%30;
        break;
    
    //Convert to Years
    case 'r':
        std::cout << "\nCONVERTING TO YEARS\n";
        //Months -> Years + Days -> Years + R Months + R Days
        f_years = time[0] + (time[1] + (time[2]/30)) /12;
        f_months = (time[1]+(time[2]/30))%12;
        f_days = time[2]%30;
        break;
    }
    //All for show loading time
    int buffer_time = 1000000; // microsecpnds 10^6
    for (int i = 0; i < 10; i++){
        if (!(i < 3) && (i < 6)){buffer_time = 500000;}
        else {buffer_time = 250000;}
        
        usleep(buffer_time);
        std::cout << "." << std::flush;
    
    }
    std::cout << std::endl;

    std::cout << "\nTime has been found!\n";
    time = {f_years, f_months, f_days};

    return;
}


// Recives [Years, Months, Days]
int main(int argc, char* argv[]){
    if(argc != 4){
        std::cerr << "Missing Arguments Detected!\n";
        std::cerr << "Please input the desired wait time in:\nYears Months Days\t(Input 0 if none)"
            << std::endl;
        exit(1);
    }
    for (int i=1; i < 4; i++){
        try{
            std::string x = std::to_string(*argv[i]);
            if (digitChecker(x)){
                throw x;
            }
        }
        catch (std::string &non_num) {
            std::cerr << non_num << " is not recognized as a number.\n";
            std::cerr << "Please ensure that only digits are inserted into the time slots.\n"
                << "Please input the desired wait time in:\nYears Months Days\t(Input 0 if none)"
                << std::endl;
                exit(2);
        }
    }
    
    //Read the desired action
    char t_unit = ChooseUnit();

    std::vector<int> time = {std::stoi(argv[1]),
        std::stoi(argv[2]), std::stoi(argv[3])};
    TimeConversion(t_unit, time);
    //
    std::cout << "The time of " << argv[1] << " YEARS " << argv[2]
        << " MONTHS " << argv[3] << " DAYS" << " has been converted to "
        << time[0] << " YEARS " << time[1] << " MONTHS " << time[2]
        << " DAYS." << std::endl;
    
    return 0;
}