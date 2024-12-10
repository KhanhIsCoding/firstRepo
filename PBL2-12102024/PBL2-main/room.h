#ifndef room_h
#define room_h
#include "RoomType.h"
#include <fstream>
#include <sstream>
#include <iostream> 
#include <string>
using namespace std;


class Room : public RoomType 
{
    protected:
        string Room_ID;
        bool Room_state;
    public:
        Room(string ID = "");
        double Total(int staying) {return staying * T_price;};
        bool Check_state() {return Room_state;}
        void Update_state();
        void ChangeType(string& type);
        void SaveRoom();
        void DeleteRoom();
        string& ID() {return Room_ID;}
        void Show_available();
        void Load(string& ID);
        friend bool operator == (const Room &r1, const Room& r2) {return r1.Room_ID == r2.Room_ID;}
        friend bool Compare(const Room& r1, const Room& r2, bool asc, int choice);
        friend ostream& operator << (ostream &out, const Room &r);
        virtual ~Room() {}
};

Room :: Room(string ID): Room_ID(ID)
{
    RoomType :: Load(Room_ID.substr(0,1));
    Room_state = 1;
}

void Room :: ChangeType(string& type)
{
    this->DeleteRoom();
    Room_ID = type + Room_ID.substr(1);
    RoomType :: Load(Room_ID.substr(0,1));
    this->SaveRoom();
}

void Room :: SaveRoom()
{
    ofstream file("DATA/PHONG.txt", ios :: app);
    file << Room_ID << '|' << Room_state << endl;
}

void Room :: DeleteRoom()
{
    ifstream data_file("DATA/PHONG.txt");
    string line, data("");
    while (getline(data_file, line))
    {
        string in_ID;
        stringstream ss(line);
        getline(ss, in_ID, '|');
        if (in_ID != Room_ID)
        data += line + '\n';
    }
    fstream file("DATA/PHONG.txt", ios::out);
    file << data;
    file.close();  
}

void Room :: Update_state()
{ 
    Room_state = !Room_state;
    ifstream data_file("DATA/PHONG.txt");
    string line, data("");
    while (getline(data_file, line))
    {
        string in_ID;
        stringstream ss(line);
        getline(ss, in_ID, '|');
        if (in_ID != Room_ID)
        data += line + '\n';
        else data += Room_ID + '|' + (Room_state? '1':'0') + '\n';
    }
    fstream file("DATA/PHONG.txt", ios::out);
    file << data;
    file.close();
}

void Room :: Show_available()
{
    string each, All_ID(""), T_line;

    ifstream data_file("DATA/LOAI PHONG.txt");
    while (getline(data_file, T_line)) 
    {
        stringstream ss(T_line);
        getline(ss, each, '|'); 
        All_ID += each + " ";
    }
    stringstream dss(All_ID);
    cout << "                                  #=================#\n";
    cout << "                                  # DANH SÁCH PHÒNG #\n";
    cout << "                                  #=================#\n\n";
    cout << "+----+---------------------+---------------+---------------+----------------------------------------+\n";
    cout << "| MÃ | LOẠI PHÒNG          | ĐƠN GIÁ/ ngày | HỆ SỐ DỊCH VỤ |          CÁC PHÒNG CÒN TRỐNG           |\n";
    cout << "+----+---------------------+---------------+---------------+----------------------------------------+\n";
    while (getline(dss, each, ' '))
    {
        RoomType :: Load(each);
        cout << (RoomType&)*this;
        ifstream data_file("DATA/PHONG.txt");
        string line, avail("");
        while (getline(data_file, line)) 
        {
            string ID;
            bool state;
            stringstream ss(line);
            getline(ss, ID, '|');
            ss >> state;
            if (ID.substr(0,1) == T_ID)
            {
                if (state) avail.append(ID + " ");
            }
        }
        if (avail.length() > 0)
        {
            if (avail.length() > 40)
            cout << setw(40) << setfill(' ') << left << avail.substr(0, 40) << "|\n";
            else 
            cout << setw(40) << setfill(' ') << left << avail << "|\n";

            while (avail.length() > 40)
            {
                avail = avail.substr(40);
                cout << "|    |                     |               |               |" << setw(40) 
                << setfill(' ') << left << avail.substr(0, 40) << "|\n";
            }
        }
        else cout << setw(40) << setfill(' ') << left << "Không còn phòng trống" << "|\n";
        cout << "+----+---------------------+---------------+---------------+----------------------------------------+\n";
    }
    RoomType :: Load(Room_ID.substr(0,1));
}

void Room :: Load(string& ID)
{
    ifstream data_file("DATA/PHONG.txt");
    string line;
    while (getline(data_file, line)) 
    {
        string data_ID;
        stringstream ss(line);
        getline(ss, data_ID, '|');
        if (data_ID == ID)
        {
            Room_ID = ID;
            ss >> Room_state;
            RoomType :: Load(Room_ID.substr(0,1));
            return;
        }
    }
    throw invalid_argument("Phòng không tồn tại");
}

bool Compare(const Room& r1, const Room& r2, bool asc, int choice) // 0 theo thu tu, !0 theo gia
{
    if(asc)
    {
        if(!choice) 
        return r1.Room_ID.substr(1, r1.Room_ID.length()) > r2.Room_ID.substr(1, r2.Room_ID.length());
        else return r1.T_price > r2.T_price;
    }
    else
    {
        if(!choice) 
        return r1.Room_ID.substr(1, r1.Room_ID.length()) < r2.Room_ID.substr(1, r2.Room_ID.length());
        else return r1.T_price < r2.T_price;
    }
}

ostream& operator << (ostream &out, const Room &r)
{
    out << "| " << setw(9) << setfill(' ') << left << r.Room_ID;
    out << "| " << setw(20) << setfill(' ') << left << r.T_name;
    out << "| " << setw(8) << setfill(' ') << left << r.Room_ID.substr(1,1);
    out << "| " << (r.Room_state ? "CÒN TRỐNG  |" : "ĐƯỢC ĐẶT   |");
    return out;
}

#endif