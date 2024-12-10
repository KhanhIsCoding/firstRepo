#ifndef booking_h
#define booking_h
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>
#include "room.h"
#include "Date.h"
using namespace std; 

class Booking
{ 
    protected:
        string booking_ID;
        Date arrive;
        Date leave;
        string Room_ID;
        string customer_ID;
    public:
        Room *booked;
        Booking(const Booking& b);
        Booking(string booking_ID = "", Date arrive = Date(1,1,2000), Date leave = Date(1,1,2000), 
        string customer_ID = "", string Room_ID = "",  int state = -1);
        virtual ~Booking() {delete booked;};
        void MakeBooking(Date& arrive, Date& leave, string customer_ID, string& Room_ID);
        Date& ArriveLeave(bool arr = true) {return arr ? arrive : leave;}
        int RoomTotal() 
        {return booked->Total(this->staying());}
        bool checkBookingState();
        string& ID() {return booking_ID;}
        string& Cus_ID() {return customer_ID;}
        void DeleteBooking();
        int staying() {return leave - arrive;}
        void ShowInfor();
        void WriteToFile();
        bool Load(string &ID);
        friend bool Compare(const Booking& b1, const Booking& b2, bool asc, int choice);
        friend ostream& operator << (ostream &out, const Booking &b);
        friend istream& operator >> (istream &in, Booking &b);
};

Booking :: Booking(string booking_ID, Date arrive, Date leave, string customer_ID, string Room_ID,  int state)
: booking_ID(booking_ID), arrive(arrive), leave(leave), customer_ID(customer_ID), Room_ID(Room_ID) {booked = new Room;}

Booking :: Booking(const Booking& b)
{
    booked = new Room;
    booking_ID = b.booking_ID;
    arrive = b.arrive;
    leave = b.leave;
    Room_ID = b.Room_ID;
    customer_ID = b.customer_ID;
    booked->Load(Room_ID);

}

void Booking :: MakeBooking (Date& arrive, Date& leave, string customer_ID, string& Room_ID)
{
    this->arrive = arrive;
    this->leave = leave;
    this->customer_ID= customer_ID;
    this->Room_ID = Room_ID;
    booked->Update_state();
    booking_ID = Room_ID + customer_ID.substr(0,4);
    this->WriteToFile();
}


void Booking :: DeleteBooking()
{
    booked->Update_state();
    ifstream data_file("DATA/DAT PHONG.txt");
    string line, data("");
    while (getline(data_file, line))
    {
        string in_ID;
        stringstream ss(line);
        getline(ss, in_ID, '|');
        if (in_ID != booking_ID)
        data += line + '\n';
    }
    fstream file("DATA/DAT PHONG.txt", ios::out);
    file << data;
    file.close();
}

void Booking :: ShowInfor()
{
    cout << "\n---CHI TIET DON DAT PHONG---\n\n";
    cout << "Mã đơn: " << booking_ID << endl;
    cout << "Ngày check-in: " << arrive << endl;
    cout << "Ngày check-out: " << leave << endl;
    cout << "Phòng đã đặt: " << Room_ID << endl;
} 

void Booking :: WriteToFile()
{
    ofstream file("DATA/DAT PHONG.txt", ios::app);
    file << booking_ID << "|" << customer_ID << "|" 
    << arrive << "|" << leave << "|"
    << Room_ID << "\n";
}

bool Booking :: Load(string &ID)
{
    ifstream data_file("DATA/DAT PHONG.txt");
    string line;
    while (getline(data_file, line)) 
    {
        string data_ID, data_cus_ID;
        stringstream ss(line);
        getline(ss, data_ID, '|');
        getline(ss, data_cus_ID, '|');
        if (data_cus_ID == ID) 
        {
            string da,dl;
            booking_ID = data_ID;
            customer_ID = ID;
            getline(ss, da, '|');
            arrive = Date(stoi(da.substr(0,2)), 
            stoi(da.substr(3,4)), stoi(da.substr(6,9)));
            getline(ss, dl, '|');
            leave = Date(stoi(dl.substr(0,2)), 
            stoi(dl.substr(3,4)), stoi(dl.substr(6,9)));
            getline(ss, Room_ID, '|');             
            booked->Load(Room_ID);
            return true;
        }   
        else continue;
    }
    return false;
}

bool Compare(const Booking& b1, const Booking& b2, bool asc, int choice) // 0 phong, 1 den, 2 di, thoi gian luu tru, tong
{
    if (choice == 0) return Compare(*b1.booked, *b2.booked, asc, choice);
    if (asc)
    {
        if (choice == 1) return const_cast<Date&>(b1.arrive) > const_cast<Date&>(b2.arrive);
        else if (choice == 2) return const_cast<Date&>(b1.leave) > const_cast<Date&>(b2.leave);
        else if (choice == 3) return const_cast<Booking&>(b1).staying() > const_cast<Booking&>(b2).staying();
        else return const_cast<Booking&>(b1).RoomTotal() > const_cast<Booking&>(b2).RoomTotal();
    }
    else
    {
        if (choice == 1) return const_cast<Date&>(b2.arrive) > const_cast<Date&>(b1.arrive);
        else if (choice == 2) return const_cast<Date&>(b2.leave) > const_cast<Date&>(b1.leave);
        else if (choice == 3) return const_cast<Booking&>(b1).staying() < const_cast<Booking&>(b2).staying();
        else return const_cast<Booking&>(b1).RoomTotal() < const_cast<Booking&>(b2).RoomTotal();
    }
}

ostream& operator << (ostream &out, const Booking &b)
{
    out << "|" << b.customer_ID;
    out << "| " << b.booking_ID;
    out << " |" << b.arrive;
    out << "|" << b.leave;
    return out;
}

#endif

