#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <ctype.h>
using namespace std;

void gotoxy(int x, int y){
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void login(string flag){
    cout << "                                                                        O========================================================O" << endl << 
            "                                                                        |                       DANG NHAP                        |" << endl <<
            "                                                                        O========================================================O" << endl <<
            "                                                                        |                                                        |" << endl <<
            "                                                                        |                      O--------------------O            |" << endl <<
            "                                                                        |            YOUR ID:  |                    |            |" << endl <<
            "                                                                        |                      O--------------------O            |" << endl <<  
            "                                                                        |                                                        |" << endl <<
            "                                                                        |                      O--------------------O            |" << endl <<
            "                                                                        |            PASSWORD: |                    |            |" << endl <<
            "                                                                        |                      O--------------------O            |" << endl <<
            "                                                                        |                                                        |" << endl;
    if(flag == "normal")
    cout << "                                                                        |                                                        |" << endl <<
            "                                                                        |    ID va PASSWORD phai co IT NHAT 8 ki tu              |" << endl << 
            "                                                                        |    va khong duoc chua ki tu dac biet!                  |" << endl <<
            "                                                                        |    Nhan ENTER de xac nhan                              |" << endl <<
            "                                                                        |                                                        |" << endl <<
            "                                                                        O========================================================O" << endl;
    else if (flag == "none")
    cout << "                                                                        |                                                        |" << endl <<
            "                                                                        |    Khong ton tai nguoi dung.                           |" << endl <<
            "                                                                        |    Vui long nhap lai.                                  |" << endl <<
            "                                                                        |    Nhan ENTER de xac nhan                              |" << endl <<
            "                                                                        |                                                        |" << endl <<
            "                                                                        O========================================================O" << endl;
    else if (flag == "error")
    cout << "                                                                        |                                                        |" << endl <<
            "                                                                        |    Loi ki tu.                                          |" << endl <<
            "                                                                        |    Vui long nhap lại thong tin chinh xac.              |" << endl <<
            "                                                                        |    Nhan ENTER de xac nhan                              |" << endl <<
            "                                                                        |                                                        |" << endl <<
            "                                                                        O========================================================O" << endl;
    }
void menu(int role){
    if(role = 1){
        cout << "O=====================================================O" << endl <<
                "|      Welcome, [INSERT KHACH HANG NAME]              |" << endl <<
                "O=====================================================O" << endl <<
                "|      BAN MUON LAM GI?                               |" << endl <<
                "|      [INSERT KHACH HANG MENU]                       |" << endl <<
                "O=====================================================O" << endl;
    } else if (role = 2){
        cout << "O=====================================================O" << endl <<
                "|      Welcome, [INSERT NHAN VIEN NAME]               |" << endl <<
                "O=====================================================O" << endl <<
                "|      BAN MUON LAM GI?                               |" << endl <<
                "|      [INSERT NHAN VIEN MENU]                        |" << endl <<
                "O=====================================================O" << endl;
    } else if (role = 3){
        cout << "O=====================================================O" << endl <<
                "|      Welcome, [INSERT BOSS NAME]                    |" << endl <<
                "O=====================================================O" << endl <<
                "|      BAN MUON LAM GI?                               |" << endl <<
                "|      [INSERT BOSS MENU]                             |" << endl <<
                "O=====================================================O" << endl;
    }
}
bool checker(string a, string b){
    if(a.length() < 8 or b.length() < 8) return false;
    for(int i=0; i<a.length();i++){
        if(!isalnum(a[i])) return false;
    }
    for(int i=0; i<b.length();i++){
        if(!isalnum(b[i])) return false;
    }
    return true;
}

int main(){
    system("cls");
    string user, pass;
    
    login("normal");
    gotoxy(52,5);
    cin >> user;
    gotoxy(52,11);
    cin >> pass;
    gotoxy(0,17);

    while(true) { //ID, pass, ROLE (để show login tương ứng)
        if(!checker(user, pass)) { //Kiểm tra syntax error
            system("cls");
            login("error");
            gotoxy(52,7);
            cin >> user;
            gotoxy(52,13);
            cin >> pass;
            gotoxy(0,19);
        }
        else if(user != "admindeptrai" || pass != "12345678") { //Kiểm tra xác thực
            system("cls");
            login("none");
            gotoxy(52,7);
            cin >> user;
            gotoxy(52,13);
            cin >> pass;
            gotoxy(0,19);
        }
        else{
            system("cls");
            cout << "ACCESS GRANTED!" << endl; //GRANT ACCESS
            break;
        }
    }

    int roleKH = 1, roleNV = 2, roleBOSS = 3;
    menu(roleKH); cout << endl;
    menu(roleNV); cout << endl;
    menu(roleBOSS); cout << endl;

    return 0;
}
