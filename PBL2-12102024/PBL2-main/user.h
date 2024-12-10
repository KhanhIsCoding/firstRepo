#ifndef user_h
#define user_h
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "Date.h"
using namespace std;

class User
{
    protected:
        string account_ID;  
        string password;
        string full_name;
        string ID;
        string phone_number; 
        Date birthday;
        bool gender;

    public:
        User(string name = "", bool gender = true, string ID = "", string number = "", 
        Date birthday = Date(1,1,2000), string password = "");
        bool Load(string account_ID, string acc_password = "");
        friend ostream& operator << (ostream &out, const User &p);
        friend istream& operator >> (istream &in, User &p);
        virtual void ListInfor();
        void ShowInfor();
        void SaveUser();
        virtual bool Delete() = 0;
        virtual ~User() {}
};

User :: User(string name, bool gender, string ID, 
string number, Date birthday, string password)
: full_name(name), gender(gender), ID(ID), phone_number(number), 
birthday(birthday), password(password), account_ID(ID) {}

bool User ::Load(string acc_ID, string acc_password) {
    ifstream data_file("DATA/NGUOI DUNG.txt"); 
    string line,bd;
    bool login_succeeded = false;
    while (getline(data_file, line)) 
    {
        stringstream ss(line);
        string data_acc_ID(""), data_acc_password("");
        getline(ss, data_acc_ID, '|');
        if (data_acc_ID == acc_ID) 
        {
            account_ID = acc_ID;
            getline(ss, data_acc_password, '|');
            if (data_acc_password == acc_password || acc_password == "")
            {
                password = acc_password;
                getline(ss,full_name , '|');
                getline(ss, ID, '|');
                getline(ss, phone_number, '|');
                getline(ss, bd, '|');
                birthday = Date(stoi(bd.substr(0,2)), 
                stoi(bd.substr(3,4)), stoi(bd.substr(6,9)));
                ss >> gender;
                login_succeeded = true;
                break;
            }
        }
    }
    return login_succeeded;
}

void User :: SaveUser()
{ 
    ofstream file("DATA/NGUOI DUNG.txt", ios::app);
    file << account_ID << '|' << password << "|" 
    << full_name << '|' << ID << "|" << phone_number 
    << "|" << birthday << "|" << gender << endl;
}

ostream& operator << (ostream &out, const User &p)
{
    out << "|" << p.account_ID;
    out << "| " << setw(29) << 
    setfill(' ') << left << p.full_name;
    out << "|" << p.ID;
    out << "|" << p.phone_number;
    out << "|" << p.birthday;
    return out;
}

void User :: ListInfor()
{
    cout << *this << "|" << (gender? " nam      |\n" : " nữ       |\n");
}

void User :: ShowInfor()
{
    cout << "Tên tài khoản: " << account_ID << endl;
    cout << "Họ tên: " << full_name << endl;
    cout << "ID: " << ID << endl;
    cout << "Số điện thoại: " << phone_number << endl;
    cout << "Ngày sinh: " << birthday << endl;
    cout << "Giới tinh: " << (gender? "nam\n" : "nu \n");
}

istream& operator >> (istream &in, User &p)
{
    string male("Nam"), input;
    cout << "Nhập họ tên: ";
    getline(in, p.full_name);
    cout << "Nhập số căn cước: ";
    getline(in, p.ID);
    cout << "Nhập giới tính (Nam/Nữ): ";
    in >> input;
    p.gender = (input == male);
    cout << "Nhập số điện thoại: ";
    in >> p.phone_number;
    cout << "Nhập ngày sinh: ";
    in >> p.birthday;
    return in;
}

#endif