#ifndef service_h
#define service_h
#include <iostream>
#include <string>
using namespace std;

class Service
{
    protected:
        string serv_ID;
        string serv_name; 
        string serv_measure; 
        int serv_price;
        int serv_count = 0;
    public:
        Service(string serv_ID = "", string serv_name = "", int serv_price = 0.0,
        string serv_measure = "", int serv_count = 0);
        void Use(int count) {serv_count += count;}
        int Total() {return serv_price * serv_count;}
        int UseTime() {return serv_count;}
        bool RoomDepend() const 
        {return serv_name.back() == '*';}
        string& ID() {return serv_ID;}
        string& Measure() {return serv_measure;}
        string& name() {return serv_name;}
        void Load(string ID);
        void Save();
        void Delete();
        void ChangeInfo(int choice, string& change);
        void AllServiceExcept(string &used_service);
        bool operator > (const Service& o) {return serv_ID > o.serv_ID;}
        bool operator == (const Service& s) {return s.serv_ID == serv_ID;}
        friend bool Compare(Service& s1, Service& s2, bool asc, int choice);
        friend ostream& operator << (ostream &out, const Service &s);
};

Service:: Service(string ID, string name, int price, string measure, int use)
: serv_ID(ID), serv_name(name), serv_price(price), serv_measure(measure), serv_count(use){}

void Service:: AllServiceExcept(string &used_service)
{
    ifstream data_file("DATA/DICH VU.txt");
    string line, used, ID, name, price, measure;
    while (getline(data_file, line)) 
    {
        bool same = false;
        stringstream tmp_used(used_service);
        stringstream ss(line);
        getline(ss, ID, '|');
        while (getline(tmp_used, used, '|'))
        {
            if (ID == used)
            {
                same = true;
                break;
            }
        }
        if (!same)
        {
            getline(ss, name, '|');
            getline(ss, measure, '|');
            ss >> price;
            cout << '|' << setw(4) << setfill(' ') << left  << ID;
            cout << '|' << setw(20) << setfill(' ') << left  << name;
            cout << '|' << (name.back() == '*' ? "hs*" : "   ") 
            << setw(5) << setfill(' ') << right << price 
            << "k/ " << setw(10) << setfill(' ') << left << measure;
            cout << "|0   " << setw(6) << left << measure << "|xxxx       |\n";
            cout << "+----+--------------------+---------------------+----------+-----------+\n";
        }
    }
}

void Service:: Load(string ID)
{
    ifstream data_file("DATA/DICH VU.txt");
    string line;
    while (getline(data_file, line)) 
    {
        string data_ID;
        stringstream ss(line);
        getline(ss, data_ID, '|');
        if (data_ID == ID)
        {
            serv_ID = ID;
            getline(ss, serv_name, '|');
            getline(ss, serv_measure, '|');
            ss >> serv_price;
            serv_count = 0;
            return;
        }     
    }
    throw invalid_argument("SAI MÃ DỊCH VỤ!");
}

void Service :: ChangeInfo(int choice, string& s)
{
    this->Delete();
    if (choice == 0)
    {
        if (this->RoomDepend())
        s += '*';
        serv_name = s;
    } 
    else if (choice == 1)
    {
        if (this->RoomDepend())
        serv_name.pop_back();
        else serv_name += '*';
    } 
    else if (choice == 2) serv_price = stoi(s);
    else serv_measure = s;
    this->Save();
}

void Service :: Delete()
{
    ifstream data_file("DATA/DICH VU.txt");
    string line, data("");
    while (getline(data_file, line))
    {
        string in_ID;
        stringstream ss(line);
        getline(ss, in_ID, '|');
        if (in_ID != serv_ID)
        data += line + '\n';
    }
    fstream file("DATA/DICH VU.txt", ios::out);
    file << data;
    file.close();
}

void Service :: Save()
{
    ofstream file("DATA/DICH VU.txt", ios :: app);
    file << serv_ID << '|' << serv_name << '|' 
    << serv_measure << '|' << serv_price << endl;
}

bool Compare(Service& s1, Service& s2, bool asc, int choice) // 0 theo ma, !0 theo gia
{
    if(asc)
    {
        if(!choice) 
        return s1.ID() > s2.ID();
        else return s1.serv_price > s2.serv_price;
    }
    else
    {
        if(!choice) 
        return s1.ID() < s2.ID();
        else return s1.serv_price < s2.serv_price;
    }
}

ostream& operator << (ostream &out, const Service &s)
{
    out << '|' << setw(4) << setfill(' ') << left << s.serv_ID;
    out << '|' << setw(20) << setfill(' ') << left << s.serv_name;
    out << '|' << (s.RoomDepend()? "hs*" : "   ") 
    << setw(5) << setfill(' ') << right << s.serv_price 
    << "k/ " << setw(10) << setfill(' ') << left << s.serv_measure << "|";
    return out;
}

#endif