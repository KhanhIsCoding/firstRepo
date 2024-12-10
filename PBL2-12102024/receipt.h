#ifndef receipt_h
#define receipt_h
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include "linkedlist.h"
#include "service.h"
#include "booking.h"
using namespace std; 

class paid_receipt
{
    private:
        string cus_ID;
        string book_ID;
        string rec_ID;
        string arrive;
        string leave;
        Date payday;
        string total;
        string method;
        string serv_detail;
    public:
        paid_receipt(string cus_ID = "", string book_ID = "", string rec_ID = "", string arrive = "", string total = "",
        string leave = "", Date payday = Date(1,1,2024), string method = "", string serv_detail = "")
        :cus_ID(cus_ID), book_ID(book_ID), rec_ID(rec_ID), arrive(arrive), leave(leave), 
        payday(payday), method(method), serv_detail(serv_detail), total(total) {}
        string& Cus_ID() {return cus_ID;}
        string& Rec_ID() {return rec_ID;}
        int Total() {return stoi(total);}
        Date& PayDate() {return payday;}
        friend ostream& operator << (ostream& out, const paid_receipt& p);
        friend bool Compare(const paid_receipt& r1, const paid_receipt& r2, bool asc, int choice);
        void DetailView();
};

ostream& operator << (ostream& out, const paid_receipt& p)
{
    cout << '|' << setw(11) << setfill(' ') << left << 
    p.rec_ID << "| " << p.payday 
    << "     | " << setw(12) << setfill(' ') << left << p.total << "|" 
    << (p.method == "0" ? "CHUYỂN KHOẢN " 
    : (p.method == "1"? "TIỀN MẶT     " : "QUẸT THẺ     "))
    << "|" << p.cus_ID << "| " << p.book_ID << " |" << p.arrive
    << "|" << p.leave << "| " << p.book_ID.substr(0,4) << " |";
    stringstream ss(p.serv_detail);
    string detail(""), sd;
    while (getline(ss,sd,'_'))
    {
        if (detail.length() >= 38)
        {
            cout << setw(40) << setfill(' ') << left << detail << "|\n"; 
            detail.clear();
            cout << "|           |                |             |             |"
            << "          |          |          |          |      |";
        }
        else if (detail.length() > 0) detail += "  ";
        if (detail.length() + sd.length() < 40)
        detail += sd;
    }
    cout << setw(40) << setfill(' ') << left << detail << "|"; 
    return out;
}

bool Compare(const paid_receipt& r1, const paid_receipt& r2, bool asc, int choice)
{
    if(asc)
    {
        if (!choice) return const_cast<Date&>(r1.payday) > const_cast<Date&>(r2.payday);
        else return stoi(r1.total) > stoi(r2.total);
    }
    else
    {
        if (!choice) return const_cast<Date&>(r2.payday) > const_cast<Date&>(r1.payday);
        return stoi(r1.total) < stoi(r2.total);
    }
}

void paid_receipt :: DetailView()
{
    string each_service;
    stringstream serv_s(serv_detail);
    cout << "Mã hóa đơn: " << rec_ID << endl;
    cout << "Ngày thanh toán: " << payday << endl;
    cout << "Phương thức thanh toán: " << 
    (method == "0" ? "chuyển khoản\n" : 
    (method == "1"? "tiền mặt\n" : "quẹt thẻ\n"));
    cout << "TỔNG THANH TOÁN: " << total << "k" << endl; 
    cout << "\n---CHI TIẾT ĐƠN ĐẶT PHÒNG---\n\n";
    cout << "Mã đặt phòng: " << book_ID << endl;
    cout << "Ngày check-in: " << arrive << endl;
    cout << "Ngày check-out: " << leave << endl;
    cout << "Phòng đã đặt: " << book_ID.substr(0,4) << endl;
    cout << "\n-------CHI TIẾT DỊCH VỤ---------\n";
    cout << "+--------------------+---------+\n";
    cout << "|DỊCH VỤ             |SỐ LƯỢNG |\n";
    cout << "+--------------------+---------+\n";
    while(getline(serv_s, each_service, '_'))
    {
        string name;
        int count;
        stringstream es(each_service);
        getline(es,name, ':');
        es >> count;
        cout << '|' << setw(20) << setfill(' ') << left << name;
        cout << '|' << setw(9) << setfill(' ') << left <<  count << "|\n";
    }
    cout << "+--------------------+---------+\n";
    cout << "___________________________________________________\n\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////

class receipt
{
    private:
        string re_ID;  
        Date pay_date;
        int method; //0 ck, 1 cash, 2 card 
    public:
        Booking *book;
        LinkList<Service> *used;
        receipt(string ID = "", Date pay_date = Date(1,1,2000),int method = -1);
        virtual ~receipt() {delete book, used;};
        void MakeReceipt(Date& pay_date,int method);
        bool Load(string& ID);
        int Total();
        void SaveReceipt();
        void UnpaidReceipt();
        void UseService(string ID, int count = INT_MAX);
        int ServiceTotal();
        void ShowService();
        void Show();
        void PaidLoad(string ID);
        friend bool Compare(receipt& r1, receipt& r2, bool asc, int choice);
        friend ostream& operator << (ostream &out, const receipt &r);
        void History(string ID); 
};

receipt :: receipt(string ID,Date pay_date,int method)
        :re_ID(ID), pay_date(pay_date), method(method) 
        {
            book = new Booking;
            used = new LinkList<Service>;
        }

void receipt :: MakeReceipt(Date& pay_date,int method)
{
    this->pay_date = pay_date;
    this->method = method;
    re_ID = to_string(pay_date.GetDay()) + book->ID().substr(0,6);
}

bool receipt :: Load(string& ID)
{
    bool loaded = book->Load(ID);
    ifstream data_file("DATA/CHI TIET DICH VU.txt");
    string line;    
    while (getline(data_file, line))
    {
        string detail, d_ID;
        stringstream ss(line);
        getline(ss, d_ID, '|');
        if (d_ID == ID)
        {
            getline(ss, detail);
            stringstream des(detail);
            string each_service;
            while(getline(des, each_service, ' '))
            {
                stringstream sers(each_service);
                string ser_ID;
                int count;
                getline(sers,ser_ID,':');
                sers >> count;
                this->UseService(ser_ID, count);
            }
        }
        else continue;
    }
    return loaded;
}

int receipt :: ServiceTotal()
{
    int total = 0;
    for (int s = 0; s < used->Length(); s++)
    if ((*used)[s]->data.RoomDepend())
    total += (*used)[s]->data.Total()*book->booked->Multi();
    else total += (*used)[s]->data.Total();
    return total;
}

int receipt :: Total()
{
    return book->RoomTotal() + this->ServiceTotal();
}

void receipt :: SaveReceipt() 
{
    ofstream file("DATA/HOA DON.txt", ios::app);
    file << *book << "|" << re_ID << "|" << pay_date 
    << "|" << this->Total() << "|" << method << "|";
    for (int s = 0; s < used->Length(); s++)
    file << (*used)[s]->data.name() << ":" 
    << (*used)[s]->data.UseTime() << "_";
    file << endl;
    string file_data("");
    ifstream service_data("DATA/CHI TIET DICH VU.txt");
    string line;
    while(getline(service_data, line))
    {
        string d_ID;
        stringstream ss(line); 
        getline(ss, d_ID, '|');
        if (d_ID != book->Cus_ID())
        file_data += line + '\n'; 
    }
    ofstream rewrite("DATA/CHI TIET DICH VU.txt", ios :: out);
    rewrite << file_data;
    rewrite.close();
    delete used;
    used = new LinkList<Service>;
    book->DeleteBooking();
}

void receipt :: UnpaidReceipt()
{
    if (used->Length() == 0) return;
    string file_data("");
    ifstream service_data("DATA/CHI TIET DICH VU.txt");
    string line;
    while(getline(service_data, line))
    {
        string d_ID;
        stringstream ss(line); 
        getline(ss, d_ID, '|');
        if (d_ID != book->Cus_ID())
        file_data += line + '\n'; 
    }
    file_data += book->Cus_ID() + '|';
    for (int s = 0; s < used->Length(); s++)
    {
        file_data += (*used)[s]->data.ID() + ':' 
        + to_string((*used)[s]->data.UseTime()) + ' ';
    }
    file_data += '\n';
    ofstream rewrite("DATA/CHI TIET DICH VU.txt", ios :: out);
    rewrite << file_data;
    rewrite.close();
}

void receipt :: UseService(string ID, int count)
{
    Service add;
    add.Load(ID);
    if (count == INT_MAX) return;
    else if (count <= 0) 
    throw invalid_argument("SỐ LẦN SỬ DỤNG PHẢI LÀ SỐ NGUYÊN DƯƠNG!!");
    Node<Service> *s = nullptr;
    s = used->Find(add);
    if (s != nullptr)
    s->data.Use(count);
    else
    {
        add.Use(count);
        used->AddFirst(add);
    }
}

void receipt :: ShowService()
{
    string used_service("");
    Service* tmp;
    cout << "\n                          #=====================#\n";
    cout << "                          #  DANH SÁCH DỊCH VỤ  #\n";
    cout << "                          #=====================#\n\n";
    cout << "+----+--------------------+---------------------+----------+-----------+\n";
    cout << "| MÃ |      DỊCH VỤ       |       ĐƠN GIÁ       | ĐÃ DÙNG  |THANH TOÁN |\n";
    cout << "+----+--------------------+---------------------+----------+-----------+\n";
    used->Sort();
    for (int i = 0; i < used->Length(); i++)
    {
        cout << (*used)[i]->data << setw(3) << setfill(' ') 
        << left << (*used)[i]->data.UseTime() << ' ' << setw(6) 
        << setfill(' ') << left << (*used)[i]->data.Measure() << "| ";
        if ((*used)[i]->data.RoomDepend())
        cout << setw(8) << setfill(' ') << left <<
        (*used)[i]->data.Total()*book->booked->Multi() << "k |\n";
        else cout << setw(8) << setfill(' ') << left << (*used)[i]->data.Total() << "k |\n";
        cout << "+----+--------------------+---------------------+----------+-----------+\n";
    }
    for (int i = 0; i < used->Length(); i++)
    used_service += (*used)[i]->data.ID() + '|';
    tmp->AllServiceExcept(used_service);
    cout << "[Dịch vụ kết thức với '*' có giá phụ thuộc vào hệ số phòng]\n";
}

void receipt :: Show()
{
    cout << "\n----------------HÓA ĐƠN-----------------\n\n";
    book->ShowInfor();
    cout << "Đơn giá: " << book->booked->Price() << "k/ngày\n";
    cout << "Tổng tiền phòng = " << book->staying()
    << " x " << book->booked->Price() 
    << " = " << book->RoomTotal() << "k\n";
    cout << "\n             -------------DANH SÁCH DỊCH VỤ------------\n\n";
    cout << "+----+--------------------+---------------------+----------+------------+\n";
    cout << "| MÃ | DỊCH VỤ            | ĐƠN GIÁ             | ĐÃ DÙNG  | THANH TOÁN |\n";
    cout << "+----+--------------------+---------------------+----------+------------+\n";
    for (int i = 0; i < used->Length(); i++)
    {
        cout << (*used)[i]->data << '|' << setw(3) << setfill(' ') 
        << left << (*used)[i]->data.UseTime() << ' ' << setw(6) 
        << setfill(' ') << left << (*used)[i]->data.Measure() << "| ";
        if ((*used)[i]->data.RoomDepend())
        cout << setw(9) << setfill(' ') << left << 
        (*used)[i]->data.Total()*book->booked->Multi() << "k |\n";
        else cout << setw(9) << setfill(' ') << left << (*used)[i]->data.Total() << "k |\n";
        cout << "+----+--------------------+---------------------+----------+------------+\n";
    }
    cout << "|                 TỔNG THANH TOÁN DỊCH VỤ                 | " 
    << setw(9) << setfill(' ') << left << this->ServiceTotal() << "k |\n";
    cout << "+----------------------------------------------------------+------------+\n";
    cout << "(phòng hạng " << this->book->booked->TypeID()
    << " có hệ số dịch vụ là: " << this->book->booked->Multi() << ")\n";
    cout << "\nTỔNG THANH TOÁN: " << this->Total() << "k\n\n";
}

void receipt :: History(string ID)
{
    cout << "\n------------------LỊCH SỬ GIAO DỊCH----------------\n\n";
    ifstream data_file("DATA/HOA DON.txt");
    string d_line, serv;
    string each_service;
    Service *tmp;
    string data_ID, r_ID, book_ID, pay,
    arrive, leave, payday, total, method;
    while (getline(data_file, d_line)) 
    {
        stringstream ss(d_line);
        getline(ss, data_ID, '|');
        if (data_ID == ID)
        {
            getline(ss, book_ID, '|');
            getline(ss, arrive, '|');
            getline(ss, leave, '|');
            getline(ss, r_ID, '|');
            getline(ss, payday, '|');
            getline(ss, total, '|');
            getline(ss, method, '|');
            getline(ss, serv, '|');
            paid_receipt* tmp = new paid_receipt(ID, book_ID, r_ID,arrive,
            total, leave, Date(stoi(payday.substr(0,2)), 
            stoi(payday.substr(3,4)), stoi(payday.substr(6,9))), method, serv);
            tmp->DetailView();
            delete tmp;
        }     
    }
}

bool Compare(receipt& r1, receipt& r2, bool asc, int choice) // 0 theo gia, !0 theo ngay thanh toan
{
    if(asc)
    {
        if(!choice) 
        return r1.Total() > r2.Total();
        else return r1.pay_date > r2.pay_date;
    }
    else
    {
        if(!choice) 
        return r1.Total() < r2.Total();
        else return r2.pay_date > r1.pay_date;
    }
}

ostream& operator << (ostream &out, const receipt &r)
{
    out << r.used;
    out << *r.book;
    return out;
}

#endif