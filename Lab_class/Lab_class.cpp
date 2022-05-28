// Lab_class.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
using namespace std;

class Date {
public:
    int year;
    int month;
    int day;
    int day_in_month[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    bool format;
    string M;
    Date() {
        year = 0;
        month = 0;
        day = 0;
        format = 0;
        M = "None";
    }

    Date(int y, int m, int d) {
        year = y;
        month = m;
        day = d;
        format = 0;
        M = getMonth(m);
    }
    Date(int y, string m, int d) {
        year = y;
        month = getDigitOfMonth(m);
        day = d;
        format = 1;
        M = m;
    }
    Date(const Date& d) {
        year = d.year;
        month = d.month;
        day = d.day;
        M = getMonth(d.month);
        format = d.format;
    }
    ~Date() {
        
    }

 int getDay() {
     int a = (14 - month) / 12;
     int y = year + 4800 - a;
     int m = month + 12 * a - 3;
     return (day + (153 * m + 2) / 5) + 365 * y + (y / 4) -(y/100)+(y/400) - 32045;
    }

 string getMonth(int i) {
     switch (i) {
     case 1: return "January";
     case 2: return "February";
     case 3: return "March";
     case 4: return "April";
     case 5: return "May";
     case 6: return "June";
     case 7: return "July";
     case 8: return "August";
     case 9: return "September";
     case 10: return "October";
     case 11: return "November";
     case 12: return "December";
     default: return "None";
     }
 }
 int getDigitOfMonth(string s) {
     if (!s.compare("January")) return 1;
     if (!s.compare("February")) return 2;
     if (!s.compare("March")) return 3;
     if (!s.compare("April")) return 4;
     if (!s.compare("May")) return 5;
     if (!s.compare("June")) return 6;
     if (!s.compare("July")) return 7;
     if (!s.compare("August")) return 8;
     if (!s.compare("September")) return 9;
     if (!s.compare("October")) return 10;
     if (!s.compare("November")) return 11;
     if (!s.compare("December")) return 12;
         return 0;
 }
 Date operator+(Date& other);
 Date operator-(Date& other);
 Date operator=(Date& other);
 bool operator>(Date& other);
 bool operator>=(Date& other);
 bool operator<(Date& other);
 bool operator<=(Date& other);
 bool operator==(Date& other);




 


 Date& another() {
     if (format == false) {
         format = true;
     }
     else {
         format = false;
     }
     return *this;
 }
 int NumberOfDay() {

     int res = day;
     if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) day_in_month[1] = 29;
     for (int i = 0; i <month-1; i++) {
         res += day_in_month[i];
     }
     day_in_month[1] = 28;
     return res;
 }

};
Date getDate(int i) {
    int a = i + 32044;
    int b = (4 * a + 3) / 146097;
    int c = a - (146097 * b / 4);
    int d = (4 * c + 3) / 1461;
    int e = c - ((1461 * d) / 4);
    int m = (5 * e + 2) / 153;

    Date date;
    date.day = e - ((153 * m + 2) / 5) + 1;
    date.month = m + 3 - 12 * (m / 10);
    date.year = 100 * b + d - 4800 + (m / 10);
    return date;

}
ostream& operator<<(ostream& os, const Date& d) {
    if(d.format) return os<<d.year <<" "<<d.M<<" "<<d.day;
    return os << d.year << "." << d.month << "." << d.day;

}
istream& operator>>(istream& is, Date& d) {

    is >> d.year;
    
    
    
    if (is>>d.month) {
        
        d.M = d.getMonth(d.month);
        d.format = false;
    }
    else {
        is.clear();

        is >> d.M;
        d.month = d.getDigitOfMonth(d.M);
        d.format = true;
    }
    is >> d.day;
    return is;

     
}

Date Date::operator+(Date& other) {
    Date date3;
    date3.day = 0;
    date3.month = 0;
    date3.year = 0;
    int days1 = this->getDay();
    int days2 = other.getDay();
    int days3 = date3.getDay();
    return getDate(days1+days2-days3+1);

}
Date Date::operator-(Date& other) {
    Date date3;
    date3.day = 0;
    date3.month = 0;
    date3.year = 0;
    int days1 = this->getDay();
    int days2 = other.getDay();
    int days3 = date3.getDay();
   
    if (days1 == days2) {
        return date3;
    }
    if (days1>days2) {
        return getDate(days1 - days2 + days3);
    }
    if (days1 < days2) {
        Date d = getDate(days2 - days1 + days3);
        d.year = -d.year;
        return d;
    }

}
Date Date::operator=(Date& other) {

    Date* a = new Date(other);
    return *a;
}

bool Date::operator>(Date& other) {
    return this->getDay() > other.getDay();
}

bool Date::operator<(Date& other) {
    return this->getDay() < other.getDay();
}

bool Date::operator>=(Date& other) {
    return this->getDay() >= other.getDay();
}
bool Date::operator<=(Date& other) {
    return this->getDay() <= other.getDay();
}

bool Date::operator==(Date& other) {
    return this->getDay() == other.getDay();
}


int main()
{
    ifstream in("input.txt");
    int key;
    in >> key;
    Date date1, date2;
    in >> date1>> date2;
    
    in.close();
    ofstream out("output.txt");
  
    if (key == 1)
    {
        Date date3 = date1 + date2;
        out << date3;
    }
    else if (key == 2)
    {
        Date date4 = date1 - date2;
        out << date4;
    }
    else if (key == 3)
    {
        out << date1.another() << "\n" << date2;
    }
    else if (key == 4)
    {
        out << date1.NumberOfDay() << "\n" << date2.NumberOfDay();
    }
    else if (key == 5)
    {
        out << (date1 < date2) << "\n" << (date1 > date2) << "\n" << (date1 >= date2) << "\n" << (date1 <= date2) << "\n" << (date1 == date2);
    }
 
    out.close();
    
}


