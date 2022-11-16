#include <iostream>

int getMonthNum(const std::string& month) {
    if (month == "January") { return 1; }
    if (month == "February") { return 2; }
    if (month == "March") { return 3; }
    if (month == "April") { return 4; }
    if (month == "May") { return 5; }
    if (month == "June") { return 6; }
    if (month == "July") { return 7; }
    if (month == "August") { return 8; }
    if (month == "September") { return 9; }
    if (month == "October") { return 10; }
    if (month == "November") { return 11; }
    if (month == "December") { return 12; }
    std::cout << "something went wrong" << std::endl;
    return 1;
}

std::string getDayStr(int weekday) {
    switch (weekday) {
        case 0:
            return "Sunday";
        case 1:
            return "Monday";
        case 2:
            return "Tuesday";
        case 3:
            return "Wednesday";
        case 4:
            return "Thursday";
        case 5:
            return "Friday";
        case 6:
            return "Saturday";
        default:
            return "something went wrong";
    }
}

int getCenturyCode(int century) {
    switch (century) {
        case 17:
            return 0;
        case 18:
            return 5;
        case 19:
            return 3;
        case 20:
            return 2;
        default:
            if (century > 20) return getCenturyCode(century - 4);
            return getCenturyCode(century + 4);
    }
}

int getDoomsday(int century, int year) {
    return (getCenturyCode(century) + year/12 + year%12 + ((year % 12) / 4)) % 7;
}

int getRefDay(int month, int year) {
    bool leapYear = year % 4 == 0;
    switch (month) {
        case 1:
            if (leapYear) return 4;
            return 3;
        case 2:
            if (leapYear) return 29;
            return 28;
        case 3:
            return 14;
        case 4:
            return 4;
        case 5:
            return 9;
        case 6:
            return 6;
        case 7:
            return 11;
        case 8:
            return 8;
        case 9:
            return 5;
        case 10:
            return 10;
        case 11:
            return 7;
        case 12:
            return 12;
        default:
            std::cout << "something went wrong" << std::endl;
            if (leapYear) return 4;
            return 3;
    }
}

using namespace std;
string getWeekday(const string& date) {
    int month, day, century, year;
    int slashIndex = date.find('/');

    if (slashIndex == string::npos) {
        int spaceIndex = date.find(' ');
        month = getMonthNum(date.substr(0,spaceIndex));

        int commaIndex = date.find(',');
        day = stoi(date.substr(spaceIndex + 1, commaIndex - spaceIndex - 1));

        century = stoi(date.substr(commaIndex + 2, 2));
        year = stoi(date.substr(commaIndex + 4, 2));
    } else {
        month = stoi(date.substr(0,slashIndex));

        int slashIndex2 = date.find('/', slashIndex + 1);
        day = stoi(date.substr(slashIndex+1, slashIndex2 - slashIndex - 1));

        century = stoi(date.substr(slashIndex2 + 1, 2));
        year = stoi(date.substr(slashIndex2 + 3, 2));
    }
    int doomsday = getDoomsday(century, year);
    int refDay = getRefDay(month, year);
    int weekday;

    if (day > refDay) {
        weekday = (((day - refDay) % 7) + doomsday) % 7;
    } else {
        weekday = doomsday - ((refDay - day) % 7);
        if (weekday < 0) weekday += 7;
    }
    return getDayStr(weekday);
}

using namespace std;
int main() {
    string date;
    cout << "Enter date: ";
    getline(cin, date);
    cout << getWeekday(date) << endl;

    return 0;
}