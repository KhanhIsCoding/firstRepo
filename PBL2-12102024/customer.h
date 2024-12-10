#ifndef customer_h
#define customer_h
#include "user.h"
#include "receipt.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;
 
class Customer : public User
{
    private:
    bool have_booking;
    public:
        receipt* cus_receipt;
        Customer(Customer &o);
        Customer(string name = "", bool gender = true, string ID = "", string number = "", 
        Date birthday = Date(1,1,2000), string password = "") : have_booking(false),
        User(name, gender, ID,number, birthday, password){cus_receipt = new receipt;}
        bool Load(string account_ID, string acc_password = "");
        bool HaveBooking() const {return have_booking;}
        string& Name() {return full_name;}
        bool CustomerGender() {return gender;};
        int LastName() const;
        void ChangeBookingState();
        void Loadreceipt();
        bool Delete();
        string Customer_ID();
        friend bool Compare(const Customer& c1, const Customer& c2,bool asc, int choice);
        friend bool operator == (Customer &c1, Customer &c2);
        friend ostream &operator << (ostream &out, const Customer &c);
        friend istream &operator >> (istream &in, Customer &c);
        virtual ~Customer() {delete cus_receipt;}
};
 
Customer :: Customer(Customer& o)
{
    account_ID = o.account_ID;
    password = o.password;
    full_name = o.full_name;
    ID = o.ID;
    phone_number = o.phone_number;
    birthday = o.birthday;
    gender = o.gender;
    cus_receipt = new receipt;
    have_booking = cus_receipt->Load(account_ID);
}

bool Customer :: Load(string account_ID, string acc_password)
{
    bool loaded =  User :: Load (account_ID, acc_password); 
    have_booking = cus_receipt->Load(account_ID);
    return loaded;
}

int Customer :: LastName() const
{
    string last;
    stringstream ns(full_name);
    while (getline(ns, last, ' ')){}
    return int(last[0]);
}

bool Customer :: Delete()
{
    string file_data("");
    ifstream file("DATA/NGUOI DUNG.txt");
    string line;
    bool found = false;
    while (getline(file, line))
    {
        string d_ID;
        stringstream ss(line); 
        getline(ss, d_ID, '|');
        if (d_ID != ID)
        file_data += line + '\n';
        else found = true;
    }
    ofstream rewrite("DATA/NGUOI DUNG.txt", ios :: out);
    rewrite << file_data;
    rewrite.close();
    return found;
}

bool Compare(const Customer& l, const Customer& r,bool asc, int choice) // 0 ten, !0 tuoi
{
    if(asc)
    {
        if (!choice) return l.LastName() > r.LastName();
        else return const_cast<Date&>(l.birthday) > const_cast<Date&>(r.birthday);
    }
    else
    {
        if (!choice) return l.LastName() < r.LastName();
        else return const_cast<Date&>(r.birthday) > const_cast<Date&>(l.birthday);
    }
}

void Customer :: ChangeBookingState()
{
    have_booking = !have_booking;
}

bool operator == (Customer &c1, Customer &c2)
{
    return c1.account_ID == c2.account_ID;
}

ostream &operator << (ostream &out, const Customer &c)
{
    out << (User&)c;
    out << "||" << c.HaveBooking() << endl;
    return out;
}

string Customer :: Customer_ID()
{
    return account_ID;
}

#endif
