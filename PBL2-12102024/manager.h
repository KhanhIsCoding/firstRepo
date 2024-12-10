#ifndef manager_h
#define manager_h
#include <iostream>
#include <string>
#include <iomanip>
#include "user.h"
#include "room.h"
#include "receipt.h"
#include "booking.h"
#include "linkedlist.h"
#include "customer.h"
using namespace std; 

class Manager: public User
{
    private:
        LinkList<Customer>* customers;
        LinkList<RoomType>* types;
        LinkList<Room>* rooms;
        LinkList<Booking>* bookings;
        LinkList<Service>* services;
        LinkList<paid_receipt>* receipts;
    public: 
    void Exit(int mode = 0);
    bool Delete() {return 0;};
    int Length(int choice);
    bool TypeIsChangeable(string& ID, bool to_delete);

    void CustomerList();
    void TypeList();
    void RoomList();
    void BookingList();
    void ServiceList();
    void ReceiptList();

    void ShowCustomers(string last = "", bool asc = true, int choice = 0);
    void ShowCustomers(bool have_booking);
    void ShowService(string last = "", bool asc = true, int choice = 0);
    void ShowReceipt(string last = "", bool asc = true, int choice = 0);
    void ShowReceipt(Date d, bool asc, int choice);
    void ShowRoom(string last = "", bool asc = true, int choice = 0);
    void ShowRoom(bool booked);
    void ShowType(string last = "", bool asc = true, int choice = 0);
    void ShowBooking(string last = "", bool asc = true, int choice = 0);
    void ShowBooking(Date d, bool asc, int choice);

    void AddRoom(string& ID, int floor);
    void AddRoomType(string& ID, string& name, string& price, string& multi);
    void AddService(string& name, string& price, string& measure);

    void CustomerStat();
    void RoomStat();
    void ReceiptStat();

    bool DeleteCustomer(string& ID);
    void DeleteRoom(string& ID);
    void DeleteRoomType(string& ID);
    void DeleteService(string& ID);

    void ChangeTypeOfRoom(string& ID, string& new_type);
    void ChangeService(string& ID, string& choice, string& change);
    void ChangeRoomType(string& ID, string& choice, string& change);

    virtual ~Manager() {delete customers, types, rooms, bookings, services, receipts;};
};

void Manager :: Exit(int choice)
{
    if(!choice) 
    delete customers, types, rooms, bookings, services, receipts;
    else if (choice == 1) delete customers;
    else if (choice == 2) delete types;
    else if (choice == 3) delete rooms;
    else if (choice == 4) delete bookings;
    else if (choice == 5) delete services;
    else if (choice == 6) delete receipts;
} 

int Manager :: Length(int choice)
{
    if(!choice) return customers->Length();
    else if (choice == 1)
    return types->Length();
    else if (choice == 2)
    return rooms->Length();
    else if (choice == 3)
    return bookings->Length();
    else if (choice == 4)
    return services->Length();
    else return receipts->Length();
}

void Manager :: RoomList()
{
    rooms = new LinkList<Room>;
    ifstream data_file("DATA/PHONG.txt");
    string line, AllID(""), eachID;
    while (getline(data_file, line)) 
    {
        string Id;
        stringstream ss(line);
        getline(ss, Id, '|');
        AllID += Id + "|";
    }
    stringstream ss(AllID);
    while (getline(ss, eachID, '|'))
    {
        Room *add = new Room;
        add->Load(eachID);
        rooms->AddLast(*add);
        delete add;
    }
}

void Manager :: CustomerList()
{
    customers = new LinkList<Customer>;
    ifstream data_file("DATA/NGUOI DUNG.txt");
    string line, AllID, eachID;
    while (getline(data_file, line)) 
    {
        string Id;
        stringstream ss(line);
        getline(ss, Id, '|');
        if (Id.substr(0,1) != "E")
        AllID += Id + '|';
    }
    stringstream ss(AllID);
    while (getline(ss, eachID, '|'))
    {
        Customer *add = new Customer;
        add->Load(eachID);
        customers->AddLast(*add);
        delete add;
    }
}

void Manager :: TypeList()
{
    types = new LinkList<RoomType>;
    ifstream data_file("DATA/LOAI PHONG.txt");
    string line,AllID(""), eachID;
    while (getline(data_file, line)) 
    {
        string Id;
        stringstream ss(line);
        getline(ss, Id, '|');
        AllID += Id + "|";
    }
    stringstream ss(AllID);
    while (getline(ss, eachID, '|'))
    {
        RoomType *add = new RoomType;
        add->Load(eachID);
        types->AddLast(*add);
        delete add;
    }
}

void Manager :: BookingList()
{
    bookings = new LinkList<Booking>;
    ifstream data_file("DATA/DAT PHONG.txt");
    string line, AllID(""), eachID;
    while (getline(data_file, line)) 
    {
        string Id;
        stringstream ss(line);
        getline(ss, Id, '|');
        getline(ss, Id, '|');
        AllID += Id + "|";
    }
    stringstream ss(AllID);
    while (getline(ss, eachID, '|'))
    {
        Booking *add = new Booking;
        if (add->Load(eachID))
        bookings->AddLast(*add);
        delete add;
    }
}

void Manager :: ServiceList()
{
    services = new LinkList<Service>;
    ifstream data_file("DATA/DICH VU.txt");
    string line, AllID(""), eachID;
    while (getline(data_file, line)) 
    {
        string Id;
        stringstream ss(line);
        getline(ss, Id, '|');
        AllID += Id + "|";
    }
    stringstream ss(AllID);
    while (getline(ss, eachID, '|'))
    {
        Service *add = new Service;
        add->Load(eachID);
        services->AddLast(*add);
        delete add;
    }
}

void Manager :: ReceiptList()
{
    receipts = new LinkList<paid_receipt>;
    ifstream data_file("DATA/HOA DON.txt");
    string d_line, serv;
    string data_ID, r_ID, book_ID,
    arrive, leave, payday, total, method;
    while (getline(data_file, d_line)) 
    {
        stringstream ss(d_line);
        getline(ss, data_ID, '|');
        getline(ss, book_ID, '|');
        getline(ss, arrive, '|');
        getline(ss, leave, '|');
        getline(ss, r_ID, '|');
        getline(ss, payday, '|');
        getline(ss, total, '|');
        getline(ss, method, '|');
        getline(ss, serv, '|');
        paid_receipt* tmp = new paid_receipt(data_ID, book_ID, r_ID,arrive,
        total, leave, Date(stoi(payday.substr(0,2)), 
        stoi(payday.substr(3,4)), stoi(payday.substr(6,9))), method, serv);
        receipts->AddLast(*tmp);
        delete tmp;     
    }
}

void Manager :: ShowRoom(string last, bool asc, int choice)
{
    bool found = false;
    rooms->Sort(asc, choice);
    cout << "+----------+---------------------+---------+------------+\n";
    cout << "| MÃ PHÒNG | LOẠI PHÒNG          | SỐ TẦNG | TRẠNG THÁI |\n";
    cout << "+----------+---------------------+---------+------------+\n";
    for (int i = 0; i < rooms->Length(); i++)
    if ((*rooms)[i]->data.TypeID() == last || last == "")
    {
        found = true;
        cout << (*rooms)[i]->data << endl;
        cout << "+----------+---------------------+---------+------------+\n";
    }
    if(!found) cout << "Không có phòng mang mã trên!!\n";
}

void Manager :: ShowRoom(bool booked)
{
    rooms->Sort();
    cout << "+----------+---------------------+---------+------------+\n";
    cout << "| MÃ PHÒNG | LOẠI PHÒNG          | SỐ TẦNG | TRẠNG THÁI |\n";
    cout << "+----------+---------------------+---------+------------+\n";
    for (int i = 0; i < rooms->Length(); i++)
    if ((*rooms)[i]->data.Check_state() == booked)
    {
        cout << (*rooms)[i]->data << endl;
        cout << "+----------+---------------------+---------+------------+\n";
    }
}

void Manager :: ShowType(string last, bool asc, int choice)
{
    bool found = false;
    types->Sort(asc, choice);
    cout << "+----+---------------------+---------------+---------------+\n";
    cout << "| MÃ | LOẠI PHÒNG          | ĐƠN GIÁ/ ngày | HỆ SỐ DỊCH VỤ |\n";
    cout << "+----+---------------------+---------------+---------------+\n";
    for (int i = 0; i < types->Length(); i++)
    if ((*types)[i]->data.TypeID() == last || last == "")
    {
        found = true;
        cout << (*types)[i]->data << endl;
        cout << "+----+---------------------+---------------+---------------+\n";
    }
    if(!found) cout << "Không có loại phòng có mã trên!!\n";
}

void Manager :: ShowCustomers(bool havebooking)
{
    bool found = false;
    customers->Sort();
    cout << "+----------+------------------------------+----------+----------+----------+----------+\n";                                                   
    cout << "|TÀI KHOẢN | HỌ TÊN KHÁCH HÀNG            | ID       | SDT      |NGÀY SINH |GIỚI TÍNH |\n";
    cout << "+----------+------------------------------+----------+----------+----------+----------+\n"; 
    for (int i = 0; i < customers->Length(); i++)
    if ((*customers)[i]->data.HaveBooking() == havebooking)
    {
        found = true;
        (*customers)[i]->data.ListInfor();
        cout << "+----------+------------------------------+----------+----------+----------+----------+\n"; 
    }
    if(!found) cout << "Không có khách hàng có tên trên!!\n";
}

void Manager :: ShowCustomers(string last, bool asc, int choice)
{
    bool found = false;
    customers->Sort(asc, choice);
    cout << "+----------+------------------------------+----------+----------+----------+----------+\n";                                                   
    cout << "|TÀI KHOẢN | HỌ TÊN KHÁCH HÀNG            | ID       | SDT      |NGÀY SINH |GIỚI TÍNH |\n";
    cout << "+----------+------------------------------+----------+----------+----------+----------+\n"; 
    for (int i = 0; i < customers->Length(); i++)
    if ((*customers)[i]->data.Name() == last || last == "")
    {
        found = true;
        (*customers)[i]->data.ListInfor();
        cout << "+----------+------------------------------+----------+----------+----------+----------+\n"; 
    }
    if(!found) cout << "Không có khách hàng có tên trên!!\n";
}

void Manager :: ShowService(string last, bool asc, int choice)
{
    bool found = false;
    cout << "+----+--------------------+---------------------+\n";
    cout << "| MÃ | DỊCH VỤ            | ĐƠN GIÁ             |\n";
    cout << "+----+--------------------+---------------------+\n";
    for (int i = 0; i < services->Length(); i++)
    if ((*services)[i]->data.ID() == last || last == "")
    {
        found = true;
        cout << (*services)[i]->data << endl;
        cout << "+----+--------------------+---------------------+\n";
    }
    if(!found) cout << "Không có dịch vụ nào có mã trên!!\n";
}

void Manager :: ShowReceipt(string last, bool asc, int choice)
{
    bool found = false;
    receipts->Sort(asc, choice);
    cout << "+-----------+----------------+-------------+-------------+----------+" <<
        "----------+----------+----------+------+----------------------------------------+\n";
    cout << "|MÃ HÓA ĐƠN |NGÀY THANH TOÁN |TỔNG HÓA ĐƠN |PHƯƠNG THỨC  |TÀI KHOẢN |ĐƠN ĐẶT   |"
    << "NGÀY ĐẾN  |NGÀY ĐI   |PHÒNG |CHI TIẾT DỊCH VỤ (DỊCH VỤ: SỐ LƯỢNG)    |\n";
    cout << "+-----------+----------------+-------------+-------------+----------+" <<
        "----------+----------+----------+------+----------------------------------------+\n";
    for (int i = 0; i < receipts->Length(); i++)
    if ((*receipts)[i]->data.Cus_ID() == last || last == "")
    {
        found = true;
        cout << (*receipts)[i]->data << endl;
        cout << "+-----------+----------------+-------------+-------------+----------+" <<
        "----------+----------+----------+------+----------------------------------------+\n";
    }
    if(!found) cout << "Không có hóa đơn nào!!\n";
}

void Manager :: ShowBooking(string last, bool asc, int choice)
{
    bool found = false;
    bookings->Sort(asc, choice);
    cout << "+----------+----------+----------+----------+------+-----------+\n";
    cout << "|TÀI KHOẢN | ĐƠN ĐẶT  | NGÀY ĐẾN | NGÀY ĐI  |PHÒNG |THANH TOÁN |\n";
    cout << "+----------+----------+----------+----------+------+-----------+\n";
    for (int i = 0; i < bookings->Length(); i++)
    if ((*bookings)[i]->data.Cus_ID() == last || last == "")
    {
        found = true;
        cout << (*bookings)[i]->data << "| " <<
        (*bookings)[i]->data.booked->ID() << " | "
        << setw(8) << setfill(' ') << left <<
        (*bookings)[i]->data.RoomTotal() << "k |\n";
        cout << "+----------+----------+----------+----------+------+-----------+\n";
    }
    if(!found) cout << "Không có đơn đặt phòng nào!!\n";
}

void Manager :: ShowReceipt(Date d, bool asc, int choice)
{
    bool found;
    cout << "+-----------+----------------+-------------+-------------+----------+" <<
        "----------+----------+----------+------+----------------------------------------+\n";
    cout << "|MÃ HÓA ĐƠN |NGÀY THANH TOÁN |TỔNG HÓA ĐƠN |PHƯƠNG THỨC  |TÀI KHOẢN |ĐƠN ĐẶT   |"
    << "NGÀY ĐẾN  |NGÀY ĐI   |PHÒNG |CHI TIẾT DỊCH VỤ (DỊCH VỤ: SỐ LƯỢNG)    |\n";
    cout << "+-----------+----------------+-------------+-------------+----------+" <<
        "----------+----------+----------+------+----------------------------------------+\n";
    for (int i = 0; i < receipts->Length(); i++)
    if ((*receipts)[i]->data.PayDate()== d)
    {
        found = true;
        cout << (*receipts)[i]->data << endl;
        cout << "+-----------+----------------+-------------+-------------+----------+" <<
        "----------+----------+----------+------+----------------------------------------+\n";
    }
    if(!found) cout << "Không có hóa đơn nào!!\n"; 
}

void Manager :: ShowBooking(Date d, bool asc, int choice)
{
    bool found;
    cout << "+----------+----------+----------+----------+------+-----------+\n";
    cout << "|TÀI KHOẢN | ĐƠN ĐẶT  | NGÀY ĐẾN | NGÀY ĐI  |PHÒNG |THANH TOÁN |\n";
    cout << "+----------+----------+----------+----------+------+-----------+\n";
    for (int i = 0; i < bookings->Length(); i++)
    if ((*bookings)[i]->data.ArriveLeave()== d)
    {
        found = true;
        cout << (*bookings)[i]->data << "| " <<
        (*bookings)[i]->data.booked->ID() << " | "
        << setw(8) << setfill(' ') << left <<
        (*bookings)[i]->data.RoomTotal() << "k |\n";
        cout << "+----------+----------+----------+----------+------+-----------+\n";
    }
    if(!found) cout << "Không có đơn đặt phòng nào!!\n"; 
}

bool Manager :: DeleteCustomer(string& ID)
{
    bool succ = false;
    Customer* tmp = new Customer;
    if(tmp->Load(ID))
    {
        if (tmp->HaveBooking())
            throw invalid_argument("Khách hàng đang có đơn đặt phòng!");
        else
        {
            succ = tmp->Delete();
            if (succ) customers->Delete(*tmp);
        }
    }
    else throw invalid_argument("Tài khoản không tồn tại!");
    delete tmp;
    return succ;
}

void Manager :: DeleteService(string& ID)
{
    Service *tmp = new Service;
    tmp->Load(ID);
    services->Sort();
    services->Delete(*tmp);
    tmp->Delete();
    delete tmp;
}

void Manager :: DeleteRoom(string& ID)
{
    Room *tmp = new Room;
    tmp->Load(ID);
    rooms->Delete(*tmp);
    tmp->DeleteRoom();
    delete tmp;
}

void Manager :: DeleteRoomType(string& ID)
{
    RoomType* tmp = new RoomType;
    tmp->Load(ID);
    types->Delete(*tmp);
    tmp->Delete();
    delete tmp;
}

void Manager :: CustomerStat()
{
    int male = 0, booked = 0;
    customers->Sort();
    for (int i = 0; i < customers->Length(); i++)
    {
        if ((*customers)[i]->data.HaveBooking()) booked++;
        if ((*customers)[i]->data.CustomerGender()) male++;
    }
    cout << "\n                                        THỐNG KÊ KHÁCH HÀNG\n\n";
    cout << "+-----------+-----------+---------------+--------------+-----------------------+----------------------------+\n";
    cout << "|Trạng thái |Khách hàng |Khách hàng nam |Khách hàng nữ |Khách có đơn đặt phòng |Khách không có đơn đặt phòng|\n";
    cout << "+-----------+-----------+---------------+--------------+-----------------------+----------------------------+\n";
    cout << "|Số lượng   | " << setw(10) << setfill(' ') << left << customers->Length() << "| "
         << setw(14) << setfill(' ') << left << male << "| " << setw(13) << setfill(' ') << left 
         << customers->Length() - male << "| " << setw(22) << setfill(' ') << left << booked << "| "
         << setw(27) << setfill(' ') << left << customers->Length() - booked << "| \n"; 
    cout << "+-----------+-----------+---------------+--------------+-----------------------+----------------------------+\n";
}

void Manager :: RoomStat()
{
    int state = 0, type_count = types->Length(), room_count = rooms->Length();
    int name_length[type_count];
    for (int i = 0; i < room_count; i++)
    if (!(*rooms)[i]->data.Check_state()) state++;

    cout << "\n------------------THỐNG KÊ PHÒNG----------------------------\n";
    cout << "\n+-----------+--------+---------+----------+";
    for (int i = 0; i < type_count; i++)
    name_length[i] = (*types)[i]->data.Type().length() + 2;
    for (int i = 0; i < type_count; i++)
    cout << setw(name_length[i]) << setfill('-') << right << '+';

    cout << "\n|Trạng thái |Tổng số |Được đặt |Còn trống |";
    for (int i = 0; i < type_count; i++)
    cout << (*types)[i]->data.Type() << " |";

    cout << "\n+-----------+--------+---------+----------+";
    for (int i = 0; i < type_count; i++)
    cout << setw(name_length[i]) << setfill('-') << '+';
    cout << endl;

    cout << "|Số lượng   | " << setw(7) << setfill(' ') << left << room_count << "| "
         << setw(8) << setfill(' ') << left << state << "| "
         << setw(9) << setfill(' ') << left << room_count - state << "| ";
    for (int i = 0; i < type_count; i++)
    {
        int count = 0;
        for (int j = 0; j < room_count; j++)
        if ((*types)[i]->data.TypeID() == (*rooms)[j]->data.TypeID())
        count++;
        cout << setw(name_length[i]-2) << setfill(' ') << left << count << "| ";
    }

    cout << "\n+-----------+--------+---------+----------+";
    for (int i = 0; i < type_count; i++)
    cout << setw(name_length[i]) << setfill('-') << right << '+';
}

void Manager :: ReceiptStat()
{
    long int income = 0;
    for (int i = 0; i < receipts->Length(); i++)
    income += (*receipts)[i]->data.Total();

    cout << "\n                             THỐNG KÊ GIAO DỊCH\n\n";
    cout << "+--------------------------+-------------------------+----------------------+\n";
    cout << "|SỐ ĐƠN ĐẶT PHÒNG HIỆN TẠI |SỐ HÓA ĐƠN ĐÃ THANH TOÁN |TỔNG DOANH THU (k vnd)|\n";
    cout << "+--------------------------+-------------------------+----------------------+\n";
    cout << "| " << setw(25) << setfill(' ') << left << bookings->Length()
         << "| " << setw(24) << setfill(' ') << left << receipts->Length()
         << "| " << setw(21) << setfill(' ') << left << income << "|\n";
    cout << "+--------------------------+-------------------------+----------------------+\n";
}

void Manager :: AddService(string& name, string& price, string& measure)
{
    int new_ID = 1;
    services->Sort();
    for (int i = 0; i < services->Length(); i++)
    {
        if ((*services)[i]->data.ID() == to_string(new_ID))
        new_ID++;
        else break;
    }
    Service *tmp = new Service(to_string(new_ID), name, stoi(price), measure);
    tmp->Save();
    services->AddLast(*tmp);
    delete tmp;
}

void Manager :: AddRoom(string& ID, int floor)
{
    string new_ID = ID + to_string(floor);
    int room_num = 1;
    rooms->Sort();
    for (int i = 0; i < rooms->Length(); i++)
    {
        string name = (*rooms)[i]->data.ID();
        if (stoi(name.substr(1,1)) == floor)
        {
            if (stoi(name.substr(2,4)) == room_num)
            room_num++;
            else break;
        }
    }
    new_ID += (room_num > 10 ? "" : "0") + to_string(room_num);
    Room* new_room = new Room(new_ID);
    new_room->SaveRoom();
    rooms->AddFirst(*new_room);
    delete new_room;
}

void Manager :: AddRoomType(string& ID, string& name, string& price, string& multi)
{
    double precise_multi = stoi(multi) + int((stod(multi) - stoi(multi))*10)/10.0 +   
    ((stod(multi)-stoi(multi)-int((stod(multi)-stoi(multi))*10)/10.0) > 0.05 ? 0.1 : 0);
    RoomType *tmp = new RoomType(ID, name, stoi(price), precise_multi);
    tmp->Save();
    types->AddLast(*tmp);
    delete tmp;
}

bool Manager :: TypeIsChangeable(string& ID, bool to_delete)
{
    RoomType* tmp = new RoomType;
    if (!tmp->Load(ID))
    {
        delete tmp;
        return false;
    }
    delete tmp;
    for (int i = 0; i < rooms->Length(); i++)
    if ((*rooms)[i]->data.TypeID() == ID)
    {
        if (to_delete) return false;
        if ((*rooms)[i]->data.Check_state() == false)
        return false;
    }
    return true;
}

void Manager :: ChangeService(string& ID, string& choice, string& change)
{
    Service *tmp = new Service;
    tmp->Load(ID);
    services->Find(*tmp)->data.ChangeInfo(stoi(choice), change);
    delete tmp;
}

void Manager :: ChangeTypeOfRoom(string& ID, string& new_type)
{
    Room* tmp = new Room;
    tmp->Load(ID);
    rooms->Find(*tmp)->data.ChangeType(new_type);
    delete tmp;
}

void Manager :: ChangeRoomType(string& ID, string& choice, string& change)
{
    RoomType* tmp = new RoomType;
    tmp->Load(ID);
    types->Find(*tmp)->data.Change(stoi(choice), change);
    delete tmp;
}

#endif