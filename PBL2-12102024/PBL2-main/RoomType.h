#ifndef RoomType_h
#define RoomType_h
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

class RoomType
{
    protected:
        string T_ID;
        string T_name; 
        int T_price;
        double T_multi;
    public:
        RoomType(string ID = "", string name = "", int price = 0.0, double multi = 0.0);
        bool Load(string ID);
        friend ostream& operator << (ostream &out, const RoomType &t);
        string& TypeID() {return T_ID;}
        int Price() {return T_price;}
        string Type() {return T_name;}
        double Multi() {return T_multi;}
        void Change(int choice, string& change);
        void ShowAllType();
        void Save();
        void Delete();
        friend bool operator == (const RoomType &t1, const RoomType &t2) {return t1.T_ID == t2.T_ID;}
        friend bool Compare(RoomType& t1, RoomType& t2, bool asc, int choice);
        virtual ~RoomType() {}
};


RoomType :: RoomType(string ID, string name, int price, double multi)
: T_ID(ID), T_name(name), T_price(price), T_multi(multi){}

bool RoomType :: Load(string ID)
{
    ifstream data_file("DATA/LOAI PHONG.txt");
    string line;
    while (getline(data_file, line)) 
    {
        string data_ID, price;
        stringstream ss(line);
        getline(ss, data_ID, '|'); 
        if (data_ID == ID)
        {
            T_ID = ID;
            getline(ss, T_name, '|');
            getline(ss, price, '|');
            T_price = stod(price);
            ss >> T_multi;
            return true;
        }     
    }
    return false;
}

void RoomType :: ShowAllType()
{
    ifstream data_file("DATA/LOAI PHONG.txt");
    string line, ID, name;
    cout << "|";
    while (getline(data_file, line)) 
    {
        stringstream ss(line);
        getline(ss, ID, '|'); 
        getline(ss, name, '|');
        cout << ID << ": " << name << "|";
    }
    cout << endl;
}

void RoomType :: Delete()
{
    ifstream data_file("DATA/LOAI PHONG.txt");
    string line, data("");
    while (getline(data_file, line))
    {
        string in_ID;
        stringstream ss(line);
        getline(ss, in_ID, '|');
        if (in_ID != T_ID)
        data += line + '\n';
    }
    fstream file("DATA/LOAI PHONG.txt", ios::out);
    file << data;
    file.close();
}

void RoomType :: Save()
{
    ofstream file("DATA/LOAI PHONG.txt", ios :: app);
    file << T_ID << '|' << T_name << '|' 
    << T_price << '|' << T_multi << endl;
}

void RoomType :: Change(int choice, string& change)
{
    this->Delete();
    if (choice) T_price = stoi(change);
    else T_multi = stoi(change) + int((stod(change) - stoi(change))*10)/10.0 +   
    ((stod(change)-stoi(change)-int((stod(change)-stoi(change))*10)/10.0) > 0.05 ? 0.1 : 0);
    this->Save();
}

bool Compare(RoomType& t1, RoomType& t2, bool asc, int choice)
{
    if(asc)
    {
        if(!choice) 
        return t1.T_ID > t2.T_ID;
        else return t1.T_price > t2.T_price;
    }
    else
    {
        if(!choice) 
        return t1.T_ID < t2.T_ID;
        else return t1.T_price < t2.T_price;
    }
}

ostream& operator << (ostream &out, const RoomType &t)
{
    out << "| " << setw(3) << setfill(' ') << left << t.T_ID;
    out << "| " << setw(20) << setfill(' ') << left << t.T_name;
    out << "| " << setw(12) << setfill(' ') << left << t.T_price << "k ";
    out << "|  " << setw(13)<< setfill(' ') << left << t.T_multi << '|';
    return out;
}

#endif