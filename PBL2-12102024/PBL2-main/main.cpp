#include <windows.h>
#include "manager.h"
using namespace std;

void PressToEscape()
{
    cout << "\n\n\n";
    system("pause");
    system("cls");
}

void Intro()
{
    system("cls");
    cout << "Đề tài: QUẢN LÝ KHÁCH SẠN            " << endl <<
            "Thực hiện bởi nhóm 14                " << endl <<
            "Sinh viên thực hiện:                 " << endl <<
            "Nguyễn Mạnh Kiên         Lớp: 23T_DT2" << endl <<
            "Lương Công Khánh         Lớp: 23T_DT2" << endl;
    PressToEscape();
}

bool Confirm()
{
    string input;
    cout << " \nXÁC NHẬN (Y): ";
    getline(cin, input);
    return (input == "Y" || input == "y");
}
bool SignupConfirm()
{
    string input;
    cout << " XÁC NHẬN ĐĂNG KÝ (Y): ";
    getline(cin, input);
    return (input == "Y" || input == "y");
}

void SignUp()
{
    string ID, name, phone_number, password, input;
    Date* bday = new Date;
    bool gender;
    while(true)
    {
        cout << " #=====================# " << endl << " #       ĐĂNG KÍ       # " << endl << " #=====================# " << endl;
        cout << "ID: ";
        getline(cin, ID);
        if (!positive_number(ID, '\n'))
        Notification("ID KHÔNG HỢP LỆ!!");
        else if(ID.length() != 10)
        Notification("ĐỘ DÀI BẮT BUỘC CỦA ID LÀ 10!!");
        else 
        {
            Customer* tmp = new Customer;
            bool existing = tmp->Load(ID);
            delete tmp;
            if (existing)
            Notification("ĐÃ CÓ TÀI KHOẢN MANG ID NÀY!!");
            else break;
        }
    }
    system("cls");
    while (true)
    {
        cout << " #=====================# " << endl << " #       ĐĂNG KÍ       # " << endl << " #=====================# " << endl;
        cout << "ID: " << ID << endl;
        cout << "Họ tên: ";
        getline(cin, name);
        if (name.length() == 0)
        Notification("KHÔNG THỂ ĐỂ TRỐNG TÊN!!");
        else break;
    }
    system("cls");
    while (true)
    {
        cout << " #=====================# " << endl << " #       ĐĂNG KÍ       # " << endl << " #=====================# " << endl;
        cout << "ID: " << ID << endl;
        cout << "Họ tên: " << name << endl;
        cout << "Ngày sinh: \n";
        cin >> *bday;
        if (bday->GetYear() <= 1900)
        Notification("Năm sinh không hợp lệ!!");
        else break;
    }
    system("cls");
    while (true)
    {
        cout << " #=====================# " << endl << " #       ĐĂNG KÍ       # " << endl << " #=====================# " << endl;
        cout << "ID: " << ID << endl;
        cout << "Họ tên: " << name << endl;
        cout << "Ngày sinh: " << *bday << endl;
        cout << "Giới tính (1: nam| 0: nữ): ";
        getline(cin, input);
        if (input != "1" && input != "0")
        Notification("Chỉ nhập 1 hoặc 0!!");
        else 
        {
            gender = stoi(input);
            break;
        }
    }
    system("cls");
    while (true)
    {
        cout << " #=====================# " << endl << " #       ĐĂNG KÍ       # " << endl << " #=====================# " << endl;
        cout << "ID: " << ID << endl;
        cout << "Họ tên: " << name << endl;
        cout << "Ngày sinh: " << *bday << endl;
        cout << "Giới tính: " << (gender? "nam\n" : "nữ\n");
        cout << "Số điện thoại: ";
        getline(cin, phone_number);
        if (!positive_number(phone_number, '\n'))
        Notification("Số điện thoại không hợp lệ!!");
        else if(phone_number.length() != 10)
        Notification("Số điện thoại phải có 10 chữ số!!");
        else break;
    }
    system("cls");
    while (true)
    {
        cout << " #=====================# " << endl << " #       ĐĂNG KÍ       # " << endl << " #=====================# " << endl;
        cout << "ID: " << ID << endl;
        cout << "Họ tên: " << name << endl;
        cout << "Ngày sinh: " << *bday << endl;
        cout << "Giới tính: " << (gender? "nam\n" : "nữ\n");
        cout << "Số điện thoại: " << phone_number << endl;
        cout << "Tạo mật khẩu cho tài khoản(xxxxxx): ";
        getline(cin, password);
        if (password.length() != 6)
        Notification("Mật khẩu phải có 6 kí tự!!");
        else break;
    }
    system("cls");
    cout << " #=====================# " << endl << " #       ĐĂNG KÍ       # " << endl << " #=====================# " << endl;
    cout << "ID: " << ID << endl;
    cout << "Họ tên: " << name << endl;
    cout << "Ngày sinh: " << *bday << endl;
    cout << "Giới tinh: " << (gender? "nam\n" : "nữ\n");
    cout << "Số điện thoại: " << phone_number << endl;
    cout << "Mật khẩu: " << password << endl;
    if (Confirm())
    {
        Customer* sign_up = new Customer
        (name, gender,ID,phone_number, *bday, password);
        sign_up->SaveUser();
        Notification("TẠO TÀI KHOẢN THÀNH CÔNG!");
        PressToEscape();
        delete sign_up;
    } else {
        Notification("TẠO TÀI KHOẢN KHÔNG THÀNH CÔNG!");
        PressToEscape();
    }
    delete bday;
}

void ManageCustomer(Manager *mana)
{
    string input;
    int choice;
    int s_choice = 0;
    bool asc = true;
    mana->CustomerList();
    do
    {
        if (mana->Length(0) == 0) 
        {
            Notification("CHƯA CÓ KHÁCH HÀNG NÀO!!!");
            break;
        }
        cout << "\n       QUẢN LÝ KHÁCH HÀNG\n\n";
        cout << "1.Danh sách khách hàng\n"; // sap xep theo ten, tuoi (tang, giam)
        cout << "2.Tìm kiếm khách hàng\n"; // theo ten (them theo trang thai [dat phong/ko dat phong])
        cout << "3.Xóa tài khoản khách hàng\n"; // chi xoa khi khong co don va chi xoa khoi file nguoi dung
        cout << "4.Thống kê khách hàng\n";
        cout << "0.Thoát\n\n";
        cout << "Chức năng: ";
        cin >> choice; 
        if(!CinCheck())
        {choice = -1;}
        else system("cls");
        switch (choice)
        {
        case 1:
        while (true)
        {
            string sort_on = "Sắp xếp theo ";
            while (true)
            {
                cout << "\n                           #========================#\n";
                cout << "                           #  DANH SÁCH KHÁCH HÀNG  #\n";
                cout << "                           #========================#\n\n";
                mana->ShowCustomers("",asc, s_choice);
                string sort_choice;
                cout << "\n[Nhập q để thoát]\n";
                cout << "Sắp xếp danh sách theo(0: tên| 1: ngày sinh): ";
                getline(cin, sort_choice);
                if (sort_choice == "Q" || sort_choice == "q")
                {
                    s_choice = -1;
                    break;
                }
                if (sort_choice != "0" && sort_choice != "1")
                Notification("Không có lựa chọn trên!!");
                else 
                {
                    s_choice = stoi(sort_choice);
                    break;
                }
            } 
            system("cls");
            if (s_choice < 0) break;             
            while (true)
            {
                cout << "\n                           #========================#\n";
                cout << "                           #  DANH SÁCH KHÁCH HÀNG  #\n";
                cout << "                           #========================#\n\n";
                mana->ShowCustomers("",asc, s_choice);
                cout << "\nSắp xếp theo: " << (s_choice? "ngày sinh\n" : "tên\n");
                string ascending;
                cout << "Sắp xếp danh sách (0: tăng| 1: giảm): ";
                getline(cin, ascending);
                if (ascending != "" && ascending != "0" && ascending != "1")
                Notification("Không có lựa chọn trên!!");
                else
                {
                    asc = !stoi(ascending);
                    break;
                }
            }
            sort_on += (s_choice? "ngày sinh " : "tên ");
            sort_on += (asc? "tăng dần;." : "giảm dần.");
            Notification(sort_on);
        }
        system("cls");
        break;
        case 2:
            while (true)
            {
                cout << "[Nhập q để thoát]\n";
                cout << "Tìm kiếm khách hàng theo(0: họ tên| 1: trạng thái): ";
                getline(cin, input);
                if (input == "Q" || input == "q")
                {
                    s_choice = -1;
                    break;
                }
                if (input != "0" && input != "1")
                Notification("Không có lựa chọn trên!!");
                else
                {
                    s_choice = stoi(input);
                    break;
                }
            }
            system("cls");
            if (s_choice < 0) break;
            else if (s_choice == 0)
            {
                cout << "Họ tên khách hàng: ";
                getline(cin, input);
                system("cls");
                cout << "\n                           #========================#\n";
                cout << "                           #    KẾT QUẢ TÌM KIẾM    #\n";
                cout << "                           #========================#\n\n";
                mana->ShowCustomers(input);
            }
            else
            {
                cout << "Trạng thái(0: không có đơn đặt phòng| 0: có đơn đặt phòng): ";
                getline(cin, input);
                if (input != "0" && input != "1")
                Notification("Không có lựa chọn trên!!");
                else break; 
                system("cls");
                cout << "\n                           #========================#\n";
                cout << "                           #    KẾT QUẢ TÌM KIẾM    #\n";
                cout << "                           #========================#\n\n";     
                mana->ShowCustomers(input == "1");          
            }
            PressToEscape();
            break;
        case 3:
            cout << "\nXÓA TÀI KHOẢN KHÁCH HÀNG\n\n";
            cout << "Nhập tên tài khoản cần xóa: ";
            getline(cin, input);
            try
            {
                if (mana->DeleteCustomer(input)) 
                Notification("XÓA TÀI KHOẢN THÀNH CÔNG!!");
            }
            catch(const invalid_argument& e)
            {
                Notification(e.what());
            }
            break;
        case 4:
            mana->CustomerStat();
            PressToEscape();
            break;
        case 0:
            system("cls");
            break;
        default:
            break;
        }     
    } while (choice != 0);
    mana->Exit(1);
}

void ManageRoom(Manager *mana)
{
    string input, chosen_ID, name, price, multi, c_choice;
    int choice;
    int s_choice = 0;
    Room *rtmp;
    RoomType* ttmp;
    bool asc = true;
    mana->RoomList();
    mana->TypeList();
    do
    {
        cout << "\n           QUẢN LÝ PHÒNG\n\n";
        cout << "1.Danh sách phòng\n"; // sap xep theo loai, trang thai, gia, thu tu
        cout << "2.Tìm phòng\n";
        cout << "3.Thêm phòng\n";
        cout << "4.Xóa phòng\n"; // chi khi con trong
        cout << "5.Thay đổi thông tin phòng\n"; // chi co the khi ko duoc su dung
        cout << "6.Danh sách loại phòng\n";
        cout << "7.Thêm loại phòng\n";
        cout << "8.Xóa loại phòng\n"; // chi khi khong co phong nao trong loai nay
        cout << "9.Thay đổi thông tin loại phòng\n"; //chi khi tat ca phong loai nay con trong
        cout << "10.Thống kê\n";
        cout << "0.Thoát\n";
        cout << "Chức năng: ";
        cin >> choice;
        if(!CinCheck())
        {choice = -1;}
        else system("cls");

        switch (choice)
        {
        case 1:
        case 6:
        while (true)
        {
            if (mana->Length(2) == 0 && choice == 1)
            {
                Notification("KHÔNG CÓ PHÒNG NÀO!!!!");
                break;
            }
            else if (mana->Length(1) == 0 && choice == 6)
            {
                Notification("KHÔNG CÓ LOẠI PHÒNG NÀO!!!");
                break;
            }
            string sort_by("sắp xếp theo ");
            while (true)
            {
                cout << "\n\n                  DANH SÁCH " 
                << ((choice == 1)? "" : "LOẠI ") << "PHÒNG\n\n";
                (choice == 1)? mana->ShowRoom("",asc, s_choice) 
                : mana->ShowType("",asc, s_choice);
                cout << "[Nhập q để thoát]\n";
                cout << "Sắp xếp danh sách theo (0: thứ tự| 1: giá): ";
                getline(cin, input);
                if (input == "Q" || input == "q")
                {
                    system("cls");
                    s_choice = -1;
                    break;
                }
                if (input != "0" && input != "1")
                Notification("không có lựa chọn trên!!");
                else
                {
                    s_choice = stoi(input);
                    break;
                }

            }
            if (s_choice < 0) break;             
            while (true)
            {
                cout << "\n\n                  DANH SÁCH " 
                << ((choice == 1)? "" : "LOẠI") << "PHÒNG\n\n";
                (choice == 1)? mana->ShowRoom("",asc, s_choice) 
                : mana->ShowType("",asc, s_choice);
                cout << "Sắp xếp theo: " << (s_choice ? "giá" : "thứ tự") << endl;
                cout << "Sắp xếp danh sách (0: tăng| 1: giảm): ";
                getline(cin, input);
                if (input != "" && input != "0" && input != "1")
                Notification("Không có lựa chọn trên!!");
                else
                {
                    asc = !stoi(input);
                    break;
                }
            }
            sort_by += (s_choice? "giá " : "thứ tự ");
            sort_by += (asc? "tăng dần." : "giảm dần.");
            Notification(sort_by);
        }
        break;
        case 2:
            if (mana->Length(2) == 0)
            {
                Notification("KHÔNG CÓ PHÒNG NÀO!!!!");
                break;
            }
            while (true)
            {
                cout << "\n    TÌM PHÒNG\n\n";
                cout << "[Nhập q để thoát]\n";
                cout << "Tìm phòng theo(0: loại| 1: trạng thái): ";
                getline(cin, input);
                if (input == "Q" || input == "q")
                {
                    s_choice = -1;
                    break;
                }
                if (input != "0" && input != "1")
                Notification("Không có lựa chọn trên!!");
                else
                {
                    s_choice = stoi(input);
                    break;
                }
            }   
            system("cls"); 
            if (s_choice < 0) break;
            else if (s_choice == 0)
            {
                cout << "\n    TÌM PHÒNG\n\n";
                cout << "Nhập mã loại phòng: ";
                getline(cin, input);
                ttmp = new RoomType;
                system("cls");
                cout << "\n            #========================#\n";
                cout << "            #    KẾT QUẢ TÌM KIẾM    #\n";
                cout << "            #========================#\n\n";
                if(ttmp->Load(input)) mana->ShowRoom(input);
                else cout << "Không có khách hàng nào có ID trên!!\n\n";
                delete ttmp;
                PressToEscape();
            }
            else
            {
                while (true)
                {
                    cout << "\n    TÌM PHÒNG\n\n";
                    cout << "Nhập trạng thái(1: còn trống|0: được đặt): ";
                    getline(cin, input);
                    if (input != "0" && input != "1")
                    Notification("Không có lựa chọn trên!!");
                    else break;
                }
                system("cls");
                cout << "\n            #========================#\n";
                cout << "            #    KẾT QUẢ TÌM KIẾM    #\n";
                cout << "            #========================#\n\n";
                mana->ShowRoom(stoi(input));
                PressToEscape();
            } 
            system("cls");
            break;
        case 3:
            if (mana->Length(1) == 0)
            {
                Notification("CHƯA CÓ LOẠI PHÒNG NÀO!!!");
                break;
            }
            while (true)
            {
                cout << "\n   THÊM PHÒNG\n\n";
                ttmp = new RoomType;
                ttmp->ShowAllType();
                cout << "MÃ LOẠI PHÒNG: ";
                getline(cin, chosen_ID);
                if (ttmp->Load(chosen_ID)) break;
                else
                Notification("KHÔNG CÓ LOẠI PHÒNG TRÊN!!!");
                delete ttmp;
            }
            system("cls");
            while (true)
            {
                cout << "\n   THÊM PHÒNG\n\n";
                cout << "Mã loại phòng: " << chosen_ID << endl;
                cout << "Số tầng (1->9): ";
                getline(cin,input);
                if (!positive_number(input, '\n'))
                Notification("Chỉ nhập số tầng hợp lệ!!");
                else if (stoi(input) > 9 || stoi(input) < 1)
                Notification("Số tầng phải từ 1 đến 9!!!");
                else break;
            }
            system("cls");
            mana->AddRoom(chosen_ID, stoi(input));
            cout << "\n   THÊM PHÒNG\n\n";
            cout << "Mã loại phòng: " << chosen_ID << endl;
            cout << "Tầng: " << stoi(input) << endl;
            cout << "\nThêm phòng thành công!!!\n\n";
            PressToEscape();
            break;
        case 4:
        case 5:
            if (mana->Length(2) == 0)
            {
                Notification("KHÔNG CÓ PHÒNG NÀO!!!");
                break;
            }
            cout << "\n    " << (choice == 4 ? "XÓA " : "ĐỔI LOẠI ") << "PHÒNG\n\n";
            cout << "Mã phòng cần " << (choice == 4 ? "xóa: " : "đổi loại: ");
            getline(cin, chosen_ID);
            try
            {
                rtmp = new Room;
                rtmp->Load(chosen_ID);
                if (!rtmp->Check_state())
                {
                    input = "KHÔNG THỂ ";
                    input += (choice == 4 ? "XÓA" : "ĐỔI LOẠI");
                    input += " PHÒNG ĐANG ĐƯỢC ĐẶT!!!!";
                    Notification(input);
                }
                else
                {
                    system("cls");
                    if (choice == 4)
                    {
                        cout << "\n   XÓA PHÒNG\n\n";
                        cout << "+----------+---------------------+---------+------------+\n";
                        cout << *rtmp << endl;
                        cout << "+----------+---------------------+---------+------------+\n";
                        if (Confirm())
                        {
                            mana->DeleteRoom(chosen_ID);
                            Notification("XÓA PHÒNG THÀNH CÔNG!!");
                        }
                        else system("cls");
                    }
                    else 
                    {
                        ttmp = new RoomType;
                        while (true)
                        {
                            cout << "  \nĐỔI LOẠI PHÒNG\n\n";
                            cout << "+----------+---------------------+---------+------------+\n";
                            cout << *rtmp << endl;
                            cout << "+----------+---------------------+---------+------------+\n";
                            rtmp->ShowAllType();
                            cout << "Chọn loại phòng: ";
                            getline(cin, input);
                            if (ttmp->Load(input)) break;
                            else
                            Notification("KHÔNG CÓ LOẠI PHÒNG TRÊN!!!");
                        } 
                        delete ttmp;  
                        mana->ChangeTypeOfRoom(chosen_ID, input);
                        Notification("ĐÃ ĐỔI LOẠI PHÒNG THÀNH CÔNG!!");
                    }
                } 
            }
            catch(const invalid_argument& e)
            {
                Notification(e.what());
                cout << "Mã phòng: " << chosen_ID;
                PressToEscape();
            }
            delete rtmp;
            break;
        case 7:
            while (true)
            {
                cout << "\n    THÊM LOẠI PHÒNG\n\n";
                cout << "Mã loại phòng (A->Z): ";
                getline(cin, chosen_ID);
                if (chosen_ID.length() == 1)
                {
                    if (chosen_ID > "Z" || chosen_ID < "A")
                    {
                        Notification("MÃ PHẢI LÀ MỘT CHỮ CÁI VIẾT HOA!!");
                        continue;
                    }
                    ttmp = new RoomType;
                    if(!ttmp->Load(chosen_ID))
                    break;
                    delete ttmp;
                    Notification("Mã đã được sử dụng!!!");
                }
                else if (chosen_ID.length() > 1)
                Notification("Mã loại phòng chỉ là một kí tự duy nhất!!");
                else Notification("Không được bỏ trống mã loại phòng!!!");
            }
            system("cls");
            while(true)
            {
                cout << "\n    THÊM LOẠI PHÒNG\n\n";
                cout << "Mã loại phòng: " << chosen_ID << endl;
                cout << "Tên loại phòng: ";
                getline(cin,name);
                if (name == "") 
                Notification("Không thể bỏ trống tên loại phòng!");
                else break;
            } 
            system("cls");
            while(true)
            {
                cout << "\n    THÊM LOẠI PHÒNG\n\n";
                cout << "Mã loại phòng: " << chosen_ID << endl;
                cout << "Tên loại phòng: " << name << endl;
                cout << "Đơn giá loại phòng: ";
                getline(cin, price);
                if (!positive_number(price, '\n'))
                Notification("Đơn giá loại phòng phải là số nguyên dương!!!");
                else break;
            }
            system("cls");
            while (true)
            {
                cout << "\n    THÊM LOẠI PHÒNG\n\n";
                cout << "Mã loại phòng: " << chosen_ID << endl;
                cout << "Tên loại phòng: " << name << endl;
                cout << "Đơn giá loại phòng: " << price << "k\n";
                cout << "Hệ số dịch vụ(>= 1.0): ";
                getline(cin, multi);
                if (!positive_number(multi, '.')) 
                Notification("Hệ số dịch vụ phải là một số!!!");
                else if (stod(multi) < 1)
                Notification("Hệ số dịch vụ thấp nhất là 1!!!");
                else break; 
            } 
            mana->AddRoomType(chosen_ID, name, price, multi);
            Notification("Thêm loại phòng thành công!!!");
            cout << "\n    THÊM LOẠI PHÒNG\n\n";
            cout << "Mã loại phòng: " << chosen_ID << endl;
            cout << "Tên loại phòng: " << name << endl;
            cout << "Đơn giá loại phòng: " << price << "k\n";
            cout << "Hệ số dịch vụ: " << setprecision(1) << stod(multi) << endl;
            cout << "\nTHÊM LOẠI PHÒNG THÀNH CÔNG!!!\n\n";
            PressToEscape();
            break;
        case 8:
        case 9:
            if (mana->Length(1) == 0)
            {
                Notification("KHÔNG CÓ LOẠI PHÒNG NÀO!!!");
                break;
            }
            cout << "\n   " << (choice == 8 ? "XÓA " : "THAY ĐỔI ") << "LOẠI PHÒNG\n\n";
            cout << "Nhập mã của loại phòng cần " << (choice == 8 ? "xóa: " : "thay đổi: ");
            getline(cin, chosen_ID);
            if (!mana->TypeIsChangeable(chosen_ID, choice == 8))
            {
                Notification("MÃ KHÔNG TỒN TẠI HOẶC PHÒNG MANG MÃ ĐÃ ĐƯỢC ĐẶT!");
                cout << "Mã loại đã chọn: " << chosen_ID << endl;
                PressToEscape();
                break;
            }
            system("cls");
            if (choice == 8)
            {
                mana->ShowType(chosen_ID);
                if(Confirm)
                {
                mana->DeleteRoomType(chosen_ID);
                cout << "Đã xóa loại phòng thành công!!\n\n";
                }
                else system("cls");
            }
            else
            {
                while (true)
                {
                    cout << "\n[0: hệ số dịch vụ| 1: đơn giá]\n";
                    cout << "Chọn thông tin cần thay đổi: ";
                    getline(cin, c_choice);
                    if (c_choice != "0" && c_choice != "1")
                    Notification("Không có lựa chọn trên!!");
                    else break;
                } 
                switch (stoi(c_choice))
                {
                case 1:
                    while (true)
                    { 
                        cout << "Nhập đơn giá mới: ";
                        getline(cin, input);
                        if (!positive_number(input, '\n'))
                        Notification("Giá loại phải là số nguyên dương!!!");
                        else break;
                    } 
                    system("cls");
                    break;
                case 0:
                    while (true)
                    {
                        cout << "Nhập hệ số dịch vụ(>= 1.0): ";
                        getline(cin, input);
                        if (!positive_number(input, '.')) 
                        Notification("Hệ số dịch vụ phải là 1 số dương!!!");
                        else if (stod(input) < 1)
                        Notification("Hệ số dịch vụ thấp nhất là 1!!!");
                        else break; 
                    } 
                    system("cls");
                    break;
                }
                mana->ChangeRoomType(chosen_ID, c_choice, input);
                Notification("Thay đổi thông tin thành công!!");
            }
            break;
        case 10:
            mana->RoomStat();
            PressToEscape();
            break;
        case 0:
            system("cls");
            break;
        default:
            break;
        }

    } while (choice != 0);
    mana->Exit(2);
    mana->Exit(3);
}

void ManageService(Manager *mana)
{
    int choice;
    int s_choice = 0;
    bool asc = true;
    bool cancel = false; string inp;
    string ID(""), name(""), c_choice,
    measure(""), price, change;
    Service *tmp;
    mana->ServiceList();
    do
    {
        if (mana->Length(4) == 0) 
        {
            cout << "KHÁCH SẠN HIỆN KHÔNG CÓ DỊCH VỤ NÀO!!!\n";
            break;
        }
        cout << "\n----------------QUẢN LÝ DỊCH VỤ--------------------\n";
        cout << "1.Danh sách dịch vụ\n"; // sap xep theo don gia, ma
        cout << "2.Thêm dịch vụ\n";
        cout << "3.Xóa dịch vụ\n"; // chi khi ko duoc su dung ??
        cout << "4.Thay đổi thông tin dịch vụ\n"; 
        cout << "0.Thoát\n";
        cout << "Chức năng: ";
        cin >> choice;
        if(!CinCheck())
        {choice = -1;}
        else system("cls");
        switch (choice)
        { 
        case 1:
        while (true)
        {
            string sort_on = "Sắp xếp theo ";
            while (true)
            {
                cout << "\n              #=======================#\n";
                cout << "              #   DANH SACH DICH VU   #\n";
                cout << "              #=======================#\n\n";
                mana->ShowService("",asc, s_choice);
                string sort_choice;
                cout << "\n[Nhập q để thoát]\n";
                cout << "Sắp xếp danh sách theo(0: mã| 1: đơn giá): ";
                getline(cin, sort_choice);
                if (sort_choice == "Q" || sort_choice == "q")
                {
                    s_choice = -1;
                    break;
                }
                if (sort_choice != "0" && sort_choice != "1")
                Notification("Không có lựa chọn trên!!");
                else 
                {
                    s_choice = stoi(sort_choice);
                    break;
                }
            } 
            system("cls");
            if (s_choice < 0) break;             
            while (true)
            {
                cout << "\n              #=======================#\n";
                cout << "              #   DANH SÁCH DỊCH VỤ   #\n";
                cout << "              #=======================#\n\n";
                mana->ShowService("",asc, s_choice);
                cout << "\nSắp xếp theo: " << (s_choice? "đơn giá\n" : "mã\n");
                string ascending;
                cout << "Sắp xếp danh sách (0: tăng| 1: giảm): ";
                getline(cin, ascending);
                if (ascending != "" && ascending != "0" && ascending != "1")
                Notification("Không có lựa chọn trên!!");
                else
                {
                    asc = !stoi(ascending);
                    break;
                } 
            }
            sort_on += (s_choice? "đơn giá " : "mã ");
            sort_on += (asc? "tăng dần." : "giảm dần.");
            Notification(sort_on);
        }
        system("cls");
        break;
        case 2:
            do
            {
                cout << "\nTHÔNG TIN DỊCH VỤ\n\n";
                cout << "Dịch vụ: ";
                getline(cin,name);
                if (name == "") Notification("Không thể bỏ trống tên dịch vụ!");
                else break;
            } while (true);
            system("cls");
            cout << "\nTHÔNG TIN DỊCH VỤ\n\n";
            cout << "Dịch vụ: " << name << endl;
            cout << "ĐƠN GIÁ PHỤ THUỘC LOẠI PHÒNG\n";
            if(Confirm()) name += '*';
            system("cls");
            do
            {
                cout << "\nTHÔNG TIN DỊCH VỤ\n\n";
                cout << "Dịch vụ: " << name << endl;
                cout << "Nhập đơn giá dịch vụ: ";
                getline(cin, price);
                if (!positive_number(price, '\n'))
                Notification("Giá dịch vụ phải là số nguyên dương!!!");
                else break;
            } while (true);
            system("cls");
            do
            {
                cout << "\nTHÔNG TIN DỊCH VỤ\n\n";
                cout << "Dịch vụ: " << name << endl;
                cout << "Đơn giá: " << price << "k\n";
                cout << "Đơn vị sử dụng dịch vụ: ";
                getline(cin,measure);
                if (measure == "") Notification("Không thể bỏ trống đơn vị dịch vụ!");
                else break;
            } while (true);
            system("cls");
            cout << "\nTHÔNG TIN DỊCH VỤ\n\n";
            cout << "Dịch vụ: " << name << endl;
            cout << "Đơn giá: " << price << "k/" << measure << endl;
            mana->AddService(name,price,measure);
            cout << "\n#====================================#\n";
            cout << "X      THÊM DỊCH VỤ THÀNH CÔNG!!     X\n";
            cout << "#====================================#\n";
            PressToEscape();
            break;
        case 3:
            cout << "\n  XÓA DỊCH VỤ\n\n";
            cout << "Mã dịch vụ muốn xóa: ";
            getline(cin,ID);
            try
            {
                tmp = new Service;
                tmp->Load(ID);
                ifstream data_file("DATA/CHI TIET DICH VU.txt");
                string line;    
                while (getline(data_file, line))
                {
                    string detail;
                    stringstream ss(line);
                    getline(ss, detail, '|');
                    getline(ss, detail);
                    stringstream des(detail);
                    string each_service;
                    while(getline(des, each_service, ' ')) 
                    {
                        stringstream sers(each_service);
                        string ser_ID;
                        getline(sers,ser_ID,':');
                        if (ser_ID == ID) 
                        throw out_of_range("KHÔNG THỂ XÓA DỊCH VỤ ĐANG ĐƯỢC SỬ DỤNG!!");
                    }  
                }
                system("cls");
                delete tmp;
            }
            catch (exception& e)
            {
                Notification(e.what());
                cout << "Mã dịch vụ đã chọn: " << ID << endl;
                PressToEscape();
                delete tmp;
                break;
            }
            mana->ShowService(ID);
            if (Confirm())
            {
                mana->DeleteService(ID);
                Notification("XÓA THÀNH CÔNG!!!");
            } 
            else system("cls");
            break;
        case 4: 
            try
            {
                cout << "\nTHAY ĐỔI THÔNG TIN DỊCH VỤ\n\n";
                cout << "Nhập mã của dịch vụ cần thay đổi thông tin: ";
                getline(cin,ID);
                tmp = new Service;
                tmp->Load(ID);
                system("cls");
                string change;
                do
                {
                    cout << "\nTHAY ĐỔI THÔNG TIN DỊCH VỤ\n\n";
                    mana->ShowService(ID);
                    cout << "\n(0: tên dịch vụ| 1: đơn giá theo phòng| 2:đơn giá| 3: đơn vị)\n";
                    cout << "Chọn thông tin cần thay đổi: ";
                    getline(cin,c_choice);
                    if (c_choice != "0" && c_choice != "1" && c_choice != "2" && c_choice != "3")
                    Notification("Không có lựa chọn trên!!");
                    else break;
                } while (true);
                system("cls");
                switch (stoi(c_choice))
                {
                case 1:
                    Notification("ĐÃ THAY ĐỔI TÍNH PHỤ THUỘC PHÒNG CỦA ĐƠN GIÁ!");
                    break;
                case 0:
                    while (true)
                    {
                        cout << "\nTHAY ĐỔI THÔNG TIN DỊCH VỤ\n\n";
                        mana->ShowService(ID);
                        cout << "Nhập tên dịch vụ: ";
                        getline(cin, change);
                        if (change == "") 
                        Notification("Không thể bỏ trống tên dịch vụ!");
                        else break;
                    } 
                    Notification("ĐÃ ĐỔI TÊN DỊCH VỤ!!!");
                    break;
                case 2:
                    while (true)
                    {
                        cout << "\nTHAY ĐỔI THÔNG TIN DỊCH VỤ\n\n";
                        mana->ShowService(ID);
                        cout << "Nhập đơn giá dịch vụ: ";
                        getline(cin, change);
                        if (!positive_number(change, '\n'))
                        Notification("Giá dịch vụ phải là số nguyên dương!!!");
                        else break;
                    } 
                    Notification("ĐÃ THAY ĐỔI ĐƠN GIÁ DỊCH VỤ!!");
                    break;
                case 3:
                    while (true)
                    {
                        cout << "\nTHAY ĐỔI THÔNG TIN DỊCH VỤ\n\n";
                        mana->ShowService(ID);
                        cout << "Nhập đơn vị: ";
                        getline(cin,change);
                        if (change == "")
                        Notification("Không thể bỏ trống đơn vị dịch vụ!");
                        else break;
                    } 
                    Notification("ĐÃ THAY ĐỔI ĐƠN VỊ SỬ DỤNG DỊCH VỤ");
                    break;
                }
                mana->ChangeService(ID, c_choice, change);
                cout << endl;
                mana->ShowService(ID);
                PressToEscape();
                delete tmp, change;
            }
            catch(const invalid_argument& e) 
            {
                Notification(e.what());
                delete tmp;
            };
            break;
        case 0:
            system("cls"); 
            break;
        default:
            break;
        }     
    } while (choice != 0);
    mana->Exit(5);
}

void ManageReceipt(Manager *mana)
{
    string input;
    string element[5] = {"phòng", "ngày check-in", 
    "ngày check-out", "thời gian thuê", "giá"};
    int choice;
    int s_choice = 0;
    bool asc = true;
    mana->ReceiptList();
    mana->BookingList();
    do
    {
        cout << "\n     QUẢN LÝ GIAO DỊCH\n\n";
        cout << "1.Danh sách hóa đơn\n"; 
        cout << "2.Tra cứu lịch sử giao dịch\n";
        cout << "3.Danh sách đơn đặt phòng\n"; 
        cout << "4.Tra cứu đơn đặt phòng\n";
        cout << "5.Thống kê\n";
        cout << "0.Thoát\n\n";
        cout << "Chức năng: ";
        cin >> choice;
        if(!CinCheck())
        {choice = -1;}
        else system("cls");
        switch (choice)
        {
        case 1:
        case 3:
        while (true)
        {
            string sort_by("sắp xếp theo ");
            if (mana->Length(5) == 0 && choice == 1)
            {
                Notification("CHƯA CÓ HÓA ĐƠN NÀO!");
                break;
            }
            else if (mana->Length(3) == 0 && choice == 3)
            {
                Notification("CHƯA CÓ ĐƠN ĐẶT PHÒNG NÀO!!");
                break;
            }
            while (true)
            {
                cout << "\n\n                   DANH SÁCH " 
                << ((choice == 1)? "HÓA ĐƠN" : "ĐƠN ĐẶT PHÒNG") << "\n\n";
                (choice == 1)? mana->ShowReceipt("",asc, s_choice) : mana->ShowBooking("",asc, s_choice);
                string sort_choice;
                cout << "\n[Nhập q để thoát]\n";
                if (choice == 1) cout << "Sắp xếp danh sách theo(0: ngày thanh toán| 1: tổng thanh toán): ";
                else
                {
                    cout << "(0: " << element[0] << "|1: " << element[1] << "|2: " 
                    << element[2] << "|3: " << element[3] << "|4: " << element[4] << ")\n";
                    cout << "Sắp xếp danh sách theo: "; 
                }
                getline(cin, sort_choice);
                if (sort_choice == "Q" || sort_choice == "q")
                {
                    system("cls");
                    s_choice = -1;
                    break;
                }
                if ((sort_choice != "0" && sort_choice != "1" && choice == 1) ||
                    (sort_choice != "0" && sort_choice != "1" && sort_choice != "2" 
                    && choice == 3 && sort_choice != "3" && sort_choice != "4"))
                Notification("Không có lựa chọn trên!!");
                else
                {
                    s_choice = stoi(sort_choice);
                    break;
                }
            } 
            system("cls");
            if (s_choice < 0) break;             
            while (true)
            {
                cout << "\n\n                   DANH SÁCH " 
                << ((choice == 1)? "HÓA ĐƠN" : "ĐƠN ĐẶT PHÒNG") << "\n\n";
                string ascending;
                (choice == 1)? mana->ShowReceipt("",asc, s_choice) 
                : mana->ShowBooking("",asc, s_choice);
                cout << "\nSắp xếp theo " << ((choice == 1) ? 
                (s_choice ? "tổng thanh toán" : "ngày thanh toán") : element[s_choice]) << endl;
                cout << "Sắp xếp danh sách (0: tăng| 1: giảm): ";
                getline(cin, ascending);
                if (ascending != "" && ascending != "0" && ascending != "1")
                Notification("Không có lựa chọn trên!!");
                else
                {
                    asc = !stoi(ascending);
                    break;
                }
            }
            sort_by += (choice == 1) ? (s_choice ? "tổng thanh toán" : "ngày thanh toán") : element[s_choice];
            sort_by += asc ? " tăng dần" : " giảm dần";
            Notification(sort_by);
        }
        system("cls");
        break;
        case 2:
        case 4:
            while (true)
            {
                cout << "Tra cứu " << ((choice == 2)? "hóa đơn" : "đơn đặt phòng") << "\n\n";
                string sort_choice;
                cout << "[Nhập q để thoát]\n";
                cout << "Tra cứu " << ((choice == 2)? "hóa đơn" : "đơn đặt phòng")
                << " theo(0: ID khách hàng| 1: ngày " << ((choice == 2)? "thanh toán" : "đến") << "): ";
                getline(cin, sort_choice);
                if (sort_choice == "Q" || sort_choice == "q")
                {
                    s_choice = -1;
                    break;
                }
                if (sort_choice != "0" && sort_choice != "1")
                Notification("Không có lựa chọn trên!!");
                else
                {
                    s_choice = stoi(sort_choice);
                    break;
                }
            } 
            system("cls");
            if (s_choice < 0) break;
            else if (s_choice == 0)
            {
                string *cusID = new string;
                cout << "Nhập ID khách hàng cần tra cứu: ";
                getline(cin, *cusID);
                Customer* tmp = new Customer;
                if(tmp->Load(*cusID))
                {
                    cout << "----Danh sách " << ((choice == 2)? "hóa đơn" : "đơn đặt phòng") << "----\n";
                    (choice == 2)? mana->ShowReceipt(*cusID,true,0) : mana->ShowBooking(*cusID,true,0);
                }
                else cout << "Không có khách hàng nào có ID trên!!\n\n";
                delete tmp, cusID;
            }
            else
            {
                cout << "Nhập ngày cần tra cứu:\n";
                Date* d = new Date;
                cin >> *d;
                cout << "----Lịch sử " << ((choice == 2)? "hóa đơn" : "đơn đặt phòng") << "----\n";
                (choice == 2)? mana->ShowReceipt(*d,true,0) :  mana->ShowBooking(*d,true,0);
                delete d;
            }
            PressToEscape();
            break;
        case 5:
            mana->ReceiptStat();
            PressToEscape();
            break;
        case 0:
            system("cls");
            break;
        default:
            break;
        }        
    } while (choice != 0);
    mana->Exit(6);
    mana->Exit(4);
}

void ManagerMenu(Manager *mana)
{
    int choice;
    do 
    {
        cout << "\n       MENU QUẢN LÝ\n\n";
        cout << "1.Xem thông tin cá nhân\n";
        cout << "2.Quản lý người dùng \n";
        cout << "3.Quản lý phòng\n";
        cout << "4.Quản lý dịch vụ\n";
        cout << "5.Quản lý giao dịch\n";
        cout << "0.Đăng xuất\n\n";
        cout << "Chức năng: ";
        cin >> choice;
        if(!CinCheck())
        {choice = -1;}
        else system("cls");
        switch (choice)
        {
        case 1:
            cout << "THÔNG TIN CÁ NHÂN\n\n";
            mana->ShowInfor();
            PressToEscape();
            break;
        case 2:
            ManageCustomer(mana);
            break;
        case 3:
            ManageRoom(mana);
            break;
        case 4:
            ManageService(mana);
            break;
        case 5:
            ManageReceipt(mana);
            break;
        case 0:
            system("cls");
            break;
        default:
            break;
        }
    }while(choice != 0);
}

void ReceiptMenu(Customer *cus)
{
    int choice;
    string confirm, method;
    bool conf;
    Date &date = cus->cus_receipt->book->ArriveLeave(false);
    do
    {
        cout << "\n------------------THANH TOÁN------------------\n";
        cout << "1.Thanh toán\n";
        cout << "2.Lịch sử giao dịch\n";
        cout << "0.Thoát\n";
        cout << "Chức năng: ";
        cin >> choice;
        if(!CinCheck())
        {choice = -1;}
        else system("cls");
        switch (choice)
        {
        case 1:
        if (cus->HaveBooking())
        {
            while (true)
            {
                cus->cus_receipt->Show();
                cout << "XÁC NHẬN THANH TOÁN(Y/N): ";
                getline(cin, confirm);
                if (confirm != "Y" && confirm != "y" && confirm != "N" && confirm != "n")
                Notification("KHÔNG CÓ LỰA CHỌN NÀY!!");
                else
                {
                    conf = confirm == "Y" || confirm == "y";
                    system("cls");
                    break;
                }
            }
            if (!conf) break;
            do
            {
                cus->cus_receipt->Show();
                cout << "Ngày thanh toán: " << date << endl;
                cout << "(0:chuyển khoản, 1:tiền mặt, 2:quẹt thẻ)\n";
                cout << "Phương thức thanh toán: ";
                getline(cin, method);
                if (method != "0" && method != "1" && method != "2")
                {
                    Notification("KHÔNG CÓ PHƯƠNG THỨC TRÊN!!");
                    continue;
                }
                else break;
            } while (true);
            system("cls");
            cus->cus_receipt->Show();
            cout << "Ngày thanh toán: " << date << endl;
            cout << "Phương thức thanh toán: " << method << endl;
            cus->cus_receipt->MakeReceipt(date, stoi(method));
            cus->cus_receipt->SaveReceipt();
            cus->ChangeBookingState();
            cout << "\n\n#=================================#\n";
            cout << "X     THANH TOÁN THÀNH CÔNG!!     X\n";
            cout << "#=================================#\n";
            PressToEscape();
        }
        else Notification("KHÔNG CÓ HÓA ĐƠN NÀO CẦN THANH TOÁN!!");  
        break;
        case 2:
            cus->cus_receipt->History(cus->Customer_ID());
            PressToEscape();
            break;
        case 0:
            system("cls");
            break;
        default: 
            break;
        }
    } while (choice != 0);
}

void BookingMenu(Customer *cus)
{
    int choice;
    Date arrive, leave;
    string Room_ID, staying;
    do
    {
        cout << "\n           ĐẶT PHÒNG\n\n";
        cout << "1.Đặt phòng\n";
        cout << "2.Hủy đơn đặt phòng\n";
        cout << "3.Xem thông tin đơn đặt phòng\n";
        cout << "4.Danh sách phòng chi tiết\n";
        cout << "0.Thoát\n";
        cout << "\nChức năng: ";
        cin >> choice;
        if(!CinCheck())
        {choice = -1;}
        else system("cls");
        switch (choice)
        {
        case 1:
            if (cus->HaveBooking())
            {
                Notification("BẠN ĐANG CÓ ĐƠN ĐẶT PHÒNG!!!");
                cus->cus_receipt->book->ShowInfor();
                PressToEscape();
                break;
            }
            else
            {
                while (true)
                {
                    cus->cus_receipt->book->booked->Show_available();
                    cout << "CHỌN PHÒNG MUỐN ĐẶT: ";
                    getline(cin,Room_ID);
                    try
                    {
                        cus->cus_receipt->book->booked->Load(Room_ID);
                    }
                    catch(const invalid_argument& e)
                    {
                        Notification(e.what());
                        continue;
                    }
                    if (!cus->cus_receipt->book->booked->Check_state())
                    Notification("PHÒNG ĐÃ ĐƯỢC ĐẶT!!");
                    else break;
                } 
                system("cls");
                do
                {
                    cout << "\n     ĐƠN ĐẶT PHÒNG\n\n";
                    cout << "Phòng: " << Room_ID << endl;
                    cout << "NGÀY ĐẾN (từ năm 2024):\n";
                    cin >> arrive;
                    if (arrive.GetYear() < 2024)
                    Notification("CHỈ CÓ THỂ ĐẶT PHÒNG TỪ NĂM 2024!!");
                    else break;
                } while (true); 
                system("cls");
                do
                {
                    cout << "\n     ĐƠN ĐẶT PHÒNG\n\n";
                    cout << "Phòng: " << Room_ID << endl;
                    cout << "NGÀY ĐẾN: " << arrive << endl;
                    cout << "Thời gian lưu trữ (Nhiều nhất là 365 ngày!): ";
                    getline(cin, staying);
                    if (!positive_number(staying, '\n'))
                    Notification("SỐ NGÀY KHÔNG HỢP LỆ!!");
                    else if (stoi(staying) <= 0)
                    Notification("PHẢI THUÊ ÍT NHẤT 1 NGÀY ĐỂ ĐẶT PHÒNG!!");
                    else break;
                } while (true);
                system("cls");
                leave = arrive + stoi(staying);
                cout << "\n     ĐƠN ĐẶT PHÒNG\n\n";
                cout << "Phòng: " << Room_ID << endl;
                cout << "NGÀY ĐẾN: " << arrive << endl;
                cout << "NGÀY ĐI: " << leave << endl;
                cout << "\n\n#=================================#\n";
                cout << "X      ĐẶT PHÒNG THÀNH CÔNG!!     X\n";
                cout << "#=================================#\n";
                PressToEscape();
                cus->cus_receipt->book->
                MakeBooking(arrive, leave, cus->Customer_ID(), Room_ID);
                cus->ChangeBookingState();
                break;
            }

        case 2:
            if (cus->HaveBooking())
            {
                if (cus->cus_receipt->used->Length() != 0)
                Notification("KHÔNG THỂ HỦY ĐƠN SAU KHI CHECK-IN!");
                else
                {
                    if (Confirm())
                    {
                        cus->cus_receipt->book->DeleteBooking();
                        cus->ChangeBookingState();
                        Notification("HỦY ĐƠN THÀNH CÔNG!!!");
                    } 
                    else system("cls");
                }
            }
            else Notification("CHƯA CÓ ĐƠN ĐẶT PHÒNG!!!");
            break;
        case 3:
            if (cus->HaveBooking())
            {
                cout << "\n\n";
                cus->cus_receipt->book->ShowInfor();
                PressToEscape();
            }
            else Notification("CHƯA CÓ ĐƠN ĐẶT PH!!!");
            break;
        case 4:
            cus->cus_receipt->book->booked->Show_available();
            PressToEscape();
            break;
        case 0:
            system("cls");
            break;
        default: 
            break;
        }
    } while (choice != 0);
}

void ServiceMenu(Customer *cus)
{
    int count = 0;
    string used,choice;
    if (cus->HaveBooking() == false)
    {
        Notification("ĐẶT PHÒNG TRƯỚC KHI SỬ DỤNG DỊCH VỤ!");
        return;
    }
    while (true)
    {
        try
        {
            cus->cus_receipt->ShowService();
            cout << "\n(nhập 0 để thoát)\n";
            cout << "Nhập mã dịch vụ bạn muốn sử dụng: ";
            getline(cin,choice);
            if (choice == "0")
            {
                system("cls");
                break;
            } 
            cus->cus_receipt->UseService(choice);
            cout << "Nhập số lượng bạn muốn sử dụng: ";
            cin >> count;
            CinCheck();
            cus->cus_receipt->UseService(choice, count);
            cus->cus_receipt->UnpaidReceipt();
            system("cls");
        }
        catch(invalid_argument &e)
        {
            Notification(e.what());
        }
    }
}

void CustomerMenu(Customer *cus)
{
    int choice;
    do
    {
        cout << "\n     MENU \n\n";
        cout << "1. Xem thông tin cá nhân\n";
        cout << "2. Đặt phòng\n";
        cout << "3. Sử dụng dịch vụ\n";
        cout << "4. Thanh toán\n";
        cout << "0. Đăng xuất\n\n";
        cout << "Chức năng: ";
        cin >> choice;
        if(!CinCheck())
        {choice = -1;}
        else system("cls");
        switch (choice)
        {
        case 1:
            cout << "THÔNG TIN CÁ NHÂN\n\n";
            cus->ShowInfor();
            PressToEscape();
            break;
        case 2:
            BookingMenu(cus);
            break;
        case 3:
            ServiceMenu(cus); 
            break;
        case 4:
            ReceiptMenu(cus);
            break;
        case 0:
            system("cls");
            break;
        default:
            break;
        }
    } while (choice != 0);
}

User* login(string ID, string pass)
{
    ifstream data_file("DATA/NGUOI DUNG.txt"); 
    string line;
    while (getline(data_file, line)) 
    {
        stringstream ss(line);
        string data_acc_ID(""), data_acc_password("");
        getline(ss, data_acc_ID, '|');
        if (data_acc_ID == ID) 
        {
            getline(ss, data_acc_password, '|');
            if (data_acc_password == pass)
            {
                if (ID.substr(0,1) == "E")
                {
                    Manager *mn = new Manager;
                    mn->Load(ID,pass);
                    return mn;
                }
                else
                {
                    Customer *cus = new Customer;
                    cus->Load(ID,pass);
                    return cus;
                }
            }
        }
    }
    return nullptr;
}

void gotoxy(int x, int y){
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void LoginPanel()
{
    cout << "                                                                        #========================================================#" << endl << 
            "                                                                        #                        ĐĂNG NHẬP                       #" << endl <<
            "                                                                        #========================================================#" << endl <<
            "                                                                        #                                                        #" << endl <<
            "                                                                        #                      #====================#            #" << endl <<
            "                                                                        #       MÃ TÀI KHOẢN:  #                    #            #" << endl <<
            "                                                                        #                      #====================#            #" << endl <<  
            "                                                                        #                                                        #" << endl <<
            "                                                                        #                      #====================#            #" << endl <<
            "                                                                        #       MẬT KHẨU:      #                    #            #" << endl <<
            "                                                                        #                      #====================#            #" << endl <<
            "                                                                        #                                                        #" << endl <<
            "                                                                        #                                                        #" << endl <<
            "                                                                        #                                                        #" << endl <<
            "                                                                        #========================================================#" << endl;
}

int main()
{
    Intro();
    int quit = 1;
    string account_ID, password;
    while (quit) 
    {
        LoginPanel();
        gotoxy(98,5);
        getline(cin,account_ID);

        if (account_ID == "Q" || account_ID == "q")
        {
            Notification("Đã thoát ứng dụng!");
            break;
        }
        gotoxy(98,9);
        getline(cin, password);
        gotoxy(0,13);
        if (account_ID == "" && password == "")
        {
            system("cls");
            LoginPanel();
            gotoxy(79,12);
            if(SignupConfirm())
            {
                system("cls");
                SignUp();
                continue;
            } else {
                Notification("Đã hủy đăng kí");
                // PressToEscape();
                continue;
            }
        }
        User *s = login(account_ID, password);
        if (s)
        {
            system("cls");
            if (Manager * mn = dynamic_cast<Manager*>(s))
                ManagerMenu(mn);
            else if (Customer *cus = dynamic_cast<Customer*>(s))
                CustomerMenu(cus);
        }
        else 
        {
            Notification("Mật khẩu hoặc tài khoản không tồn tại.");
            // PressToEscape();
            continue;
        }
    }

    // Notification("Hello World");

    return 0;
}