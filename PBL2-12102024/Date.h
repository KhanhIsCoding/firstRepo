#ifndef Date_h
#define Date_h
#include <iostream>
#include <iomanip>
#include <limits>
#include <stdexcept>
using namespace std;

bool positive_number(string& s, char exc)
{
    int total = 0;
    int e_count = 1;
    for(char c : s)
    {
        if (c == exc && e_count > 0)
        e_count--;
        else if (!isdigit(c))
        return false;
        else total += int(c) - '0';
    }
    return total > 0;
}

void Notification(string s)
{
    system("cls");
    cout << "+-----+---------------------------------------------------+\n";
    cout << "| <+> | " << setw(50) << setfill(' ') << left << s << "|\n";
    cout << "+-----+---------------------------------------------------+\n";
}

bool CinCheck()
{
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        Notification("NHẬP SAI CÚ PHÁP!!!");
        return false;
    }
    else cin.ignore();  
    return true;
}

class Date 
{
    protected:
        int date, month, year;
    public:
        Date(int date = 1, int month = 1, int year = 2000) : date(date), month(month), year(year){};
        friend istream &operator >> (istream &in, Date &d);
        friend ostream &operator << (ostream &out, const Date &d);
        int GetYear() {return year;}
        int GetDay() {return date;}
        bool operator == (const Date& d);
        bool operator > (const Date& d);
        Date operator + (int n);
        int operator - (const Date& d);
 
};

bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int LastDayOfMonth(int month, int year)
{
    int lastDayOfMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool LeapYear = isLeapYear(year);
    if (LeapYear && month == 2)
        lastDayOfMonth[2] = 29;
    return lastDayOfMonth[month];
}

istream &operator >> (istream &in, Date &d)
{
    double in_year = 0.0,in_date, in_month;
    do
    {
        cout << "\nXX/XX/____\n";
        cout << "Nhập năm: ";
        in >> in_year;
        if(!CinCheck()) continue;
        else if (int(in_year) != in_year) Notification("Năm phải là số nguyên!");
        else if (in_year <= 0) Notification("Năm phải lớn hơn 0!");
        else break;
    } while (true);
    d.year = int(in_year);
    system("cls");
    do
    {
        cout << "\nXX/__/" << setw(4) << right
        << setfill('0') << d.year << endl;
        cout << "Nhập tháng: ";
        in >> in_month;
        if(!CinCheck()) continue;
        else if (int(in_month) != in_month) Notification("Tháng phải là số nguyên!");
        else if (in_month <= 0 || in_month > 12) Notification("Tháng phải nằm trong khoảng 1 -> 12!");
        else break;
    } while (true);
    d.month = int(in_month);
    system("cls"); 
    do
    {
        cout << "\n__/" << setw(2) << setfill('0') << right << d.month 
        << "/" << setw(4) << setfill('0') << right << d.year << endl;
        cout << "Nhập ngày: ";
        in >> in_date;
        if(!CinCheck()) continue;
        else if (int(in_date) != in_date) Notification("Ngày phải là số nguyên!");
        else if (in_date <= 0 || in_date > LastDayOfMonth(d.month, d.year)) 
        Notification("Ngày không tồn tại!");
        else break;
    } while (true);   
    d.date = int(in_date);
    system("cls");
    return in;
}

ostream &operator << (ostream &out, Date const &d)
{
    out << setw(2) << setfill('0') << right << d.date << "/";
    out << setw(2) << setfill('0') << right << d.month << "/";
    out << setw(4) << setfill('0') << right << d.year;
    return out;
}

bool Date :: operator==(const Date& d)
{
    return (year == d.year && month == d.month && date == d.date);
}

bool Date::operator > (const Date& d)
{
    if (year != d.year)
    return year > d.year;
    if (month != d.month)
    return month > d.month;
    if (date != d.date)
    return date > d.date;
    else return 0;
}

int Date:: operator - (const Date& d)
{
    int result = date - d.date;
    for (int i = 1; i < month; i++)
    result += LastDayOfMonth(i, year);
    for (int j = 1; j < d.month; j++)
    result -= LastDayOfMonth(j, d.year);
    for (int k = d.year; k < year; k++)
    {
        result += 365;
        if (isLeapYear(k))
        result ++;
    }
    return result;
}

Date Date:: operator + (int n)
{
    Date tmp = *this;
    while (tmp.date + n > LastDayOfMonth(tmp.month, tmp.year))
    {
        n -= LastDayOfMonth(tmp.month, tmp.year) - tmp.date + 1;
        tmp.date = 1;
        if (tmp.month == 12)
        {
            tmp.year ++;
            tmp.month = 1;
        }
        else tmp.month ++;
    }
    tmp.date += n;
    return tmp;
}

#endif
