#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct SinhVien {
    string maSV;
    string hoTen;
    SinhVien* next;
};

struct MonHoc {
    string maMH;
    string tenMH;
    MonHoc* next;
};

struct Diem {
    string maSV;
    string maMH;
    float diem;
    Diem* next;
};

SinhVien* dsSV = nullptr;
MonHoc* dsMH = nullptr;
Diem* dsDiem = nullptr;

SinhVien* timSV(string ma) {
    SinhVien* p = dsSV;
    while (p) {
        if (p->maSV == ma) return p;
        p = p->next;
    }
    return nullptr;
}

MonHoc* timMH(string ma) {
    MonHoc* p = dsMH;
    while (p) {
        if (p->maMH == ma) return p;
        p = p->next;
    }
    return nullptr;
}

//void themSinhVien(string ma, string ten) {
//    if (timSV(ma)) {
//        cout << "Sinh vien da ton tai.\n";
//        return;
//    }
//    SinhVien* p = new SinhVien{ma, ten, nullptr};
//    if (!dsSV) dsSV = p;
//    else {
//        SinhVien* temp = dsSV;
//        while (temp->next) temp = temp->next;
//        temp->next = p;
//    }
//    cout << "Da them sinh vien thanh cong! \n";
//}
//
//void themMonHoc(string ma, string ten) {
//    if (timMH(ma)) {
//        cout << "Mon hoc da ton tai.\n";
//        return;
//    }
//    MonHoc* p = new MonHoc{ma, ten, nullptr};
//    if (!dsMH) dsMH = p;
//    else {
//        MonHoc* temp = dsMH;
//        while (temp->next) temp = temp->next;
//        temp->next = p;
//    }
//    cout << "Da them mon hoc thanh cong! \n";
//}
//
//void themDiem(string maSV, string maMH, float diem) {
//    if (!timSV(maSV) || !timMH(maMH)) {
//        cout << "Ma sinh vien hoac ma mon hoc khong hop le.\n";
//        return;
//    }
//    Diem* p = new Diem{maSV, maMH, diem, nullptr};
//    if (!dsDiem) dsDiem = p;
//    else {
//        Diem* temp = dsDiem;
//        while (temp->next) temp = temp->next;
//        temp->next = p;
//    }
//}
//Tien Thanh update add sinh vien, mon, diem
void themSinhVien(string ma, string ten, bool inThongBao = true) {
    if (timSV(ma)) {
        if (inThongBao) cout << "Sinh vien da ton tai.\n";
        return;
    }
    SinhVien* p = new SinhVien{ma, ten, nullptr};
    if (!dsSV) dsSV = p;
    else {
        SinhVien* temp = dsSV;
        while (temp->next) temp = temp->next;
        temp->next = p;
    }
    if (inThongBao) cout << "Da them sinh vien thanh cong! \n";
}

void themMonHoc(string ma, string ten, bool inThongBao = true) {
    if (timMH(ma)) {
        if (inThongBao) cout << "Mon hoc da ton tai.\n";
        return;
    }
    MonHoc* p = new MonHoc{ma, ten, nullptr};
    if (!dsMH) dsMH = p;
    else {
        MonHoc* temp = dsMH;
        while (temp->next) temp = temp->next;
        temp->next = p;
    }
    if (inThongBao) cout << "Da them mon hoc thanh cong! \n";
}

void themDiem(string maSV, string maMH, float diem, bool inThongBao = true) {
    if (!timSV(maSV) || !timMH(maMH)) {
        if (inThongBao) cout << "Ma sinh vien hoac ma mon hoc khong hop le.\n";
        return;
    }

    Diem* p = dsDiem;
    while (p) {
        if (p->maSV == maSV && p->maMH == maMH) {
            p->diem = diem;
            if (inThongBao) {
                SinhVien* sv = timSV(maSV);
                MonHoc* mh = timMH(maMH);
                if (sv && mh)
                    cout << "Da cap nhat diem mon " << mh->tenMH
                         << " cho sinh vien " << sv->hoTen << "!\n";
            }
            return;
        }
        p = p->next;
    }

    Diem* newDiem = new Diem{maSV, maMH, diem, nullptr};
    if (!dsDiem) dsDiem = newDiem;
    else {
        Diem* temp = dsDiem;
        while (temp->next) temp = temp->next;
        temp->next = newDiem;
    }

    if (inThongBao) {
        SinhVien* sv = timSV(maSV);
        MonHoc* mh = timMH(maMH);
        if (sv && mh)
            cout << "Da them diem mon " << mh->tenMH
                 << " cho sinh vien " << sv->hoTen << " thanh cong!\n";
    }
}



void inDSSV() {
    cout << "\nDanh sach sinh vien:\n";
    SinhVien* p = dsSV;
    while (p) {
        cout << p->maSV << " - " << p->hoTen << endl;
        p = p->next;
    }
}

void inDSMH() {
    cout << "\nDanh sach mon hoc:\n";
    MonHoc* p = dsMH;
    while (p) {
        cout << p->maMH << " - " << p->tenMH << endl;
        p = p->next;
    }
}

void inDSDiem() {
    cout << "\nBang diem:\n";
    Diem* p = dsDiem;
    while (p) {
        cout << p->maSV << " - " << p->maMH << " - " << fixed << setprecision(2) << p->diem << endl;
        p = p->next;
    }
}

void timKiemSVTheoTen(string keyword) {
    SinhVien* p = dsSV;
    cout << "\nKet qua tim theo ten:\n";
    while (p) {
        if (p->hoTen.find(keyword) != string::npos)
            cout << p->maSV << " - " << p->hoTen << endl;
        p = p->next;
    }
}

float tinhDiemTB(string maSV) {
    Diem* p = dsDiem;
    float tong = 0;
    int dem = 0;
    while (p) {
        if (p->maSV == maSV) {
            tong += p->diem;
            dem++;
        }
        p = p->next;
    }
    return dem == 0 ? 0 : tong / dem;
}

void thongKeHocLuc() {
    SinhVien* p = dsSV;
    cout << "\nThong ke hoc luc:\n";
    while (p) {
        float dtb = tinhDiemTB(p->maSV);
        string hl;
        if (dtb >= 8.0) hl = "Gioi";
        else if (dtb >= 6.5) hl = "Kha";
        else if (dtb >= 5.0) hl = "Trung binh";
        else hl = "Yeu";
        cout << p->maSV << " - " << p->hoTen << " - " << fixed << setprecision(2) << dtb << " - " << hl << endl;
        p = p->next;
    }
}

void suaSinhVien(string ma) {
    SinhVien* p = timSV(ma);
    if (!p) {
        cout << "Khong tim thay sinh vien.\n";
        return;
    }
    cout << "Nhap ten moi: ";
    getline(cin, p->hoTen);
    cout << "Da cap nhat ten sinh vien.\n";
}

void suaMonHoc(string ma) {
    MonHoc* p = timMH(ma);
    if (!p) {
        cout << "Khong tim thay mon hoc.\n";
        return;
    }
    cout << "Nhap ten moi: ";
    getline(cin, p->tenMH);
    cout << "Da cap nhat ten mon hoc.\n";
}

void suaDiem(string maSV, string maMH) {
    Diem* p = dsDiem;
    while (p) {
        if (p->maSV == maSV && p->maMH == maMH) {
            cout << "Nhap diem moi: ";
            cin >> p->diem;
            cin.ignore();
            cout << "Da cap nhat diem.\n";
            return;
        }
        p = p->next;
    }
    cout << "Khong tim thay diem.\n";
}

void xoaSinhVien(string ma) {
    SinhVien *p = dsSV, *prev = nullptr;
    while (p) {
        if (p->maSV == ma) {
            if (!prev) dsSV = p->next;
            else prev->next = p->next;
            delete p;
            cout << "Da xoa sinh vien.\n";

            Diem *d = dsDiem, *dprev = nullptr;
            while (d) {
                if (d->maSV == ma) {
                    if (!dprev) dsDiem = d->next;
                    else dprev->next = d->next;
                    delete d;
                    d = (dprev) ? dprev->next : dsDiem;
                    continue;
                }
                dprev = d;
                d = d->next;
            }
            return;
        }
        prev = p;
        p = p->next;
    }
    cout << "Khong tim thay sinh vien.\n";
}

void xoaMonHoc(string ma) {
    MonHoc *p = dsMH, *prev = nullptr;
    while (p) {
        if (p->maMH == ma) {
            if (!prev) dsMH = p->next;
            else prev->next = p->next;
            delete p;
            cout << "Da xoa mon hoc.\n";

            Diem *d = dsDiem, *dprev = nullptr;
            while (d) {
                if (d->maMH == ma) {
                    if (!dprev) dsDiem = d->next;
                    else dprev->next = d->next;
                    delete d;
                    d = (dprev) ? dprev->next : dsDiem;
                    continue;
                }
                dprev = d;
                d = d->next;
            }
            return;
        }
        prev = p;
        p = p->next;
    }
    cout << "Khong tim thay mon hoc.\n";
}

void xoaDiem(string maSV, string maMH) {
    Diem *p = dsDiem, *prev = nullptr;
    while (p) {
        if (p->maSV == maSV && p->maMH == maMH) {
            if (!prev) dsDiem = p->next;
            else prev->next = p->next;
            delete p;
            cout << "Da xoa diem.\n";
            return;
        }
        prev = p;
        p = p->next;
    }
    cout << "Khong tim thay diem.\n";
}

void ghiFile() {
    ofstream fsv("students.txt");
    for (SinhVien* p = dsSV; p; p = p->next)
        fsv << p->maSV << "," << p->hoTen << endl;
    fsv.close();

    ofstream fmh("courses.txt");
    for (MonHoc* p = dsMH; p; p = p->next)
        fmh << p->maMH << "," << p->tenMH << endl;
    fmh.close();

    ofstream fdiem("scores.txt");
    for (Diem* p = dsDiem; p; p = p->next)
        fdiem << p->maSV << "," << p->maMH << "," << p->diem << endl;
    fdiem.close();

    cout << "Da ghi du lieu ra file.\n";
}

void docFile() {
    ifstream fsv("students.txt");
    string line;
    while (getline(fsv, line)) {
        size_t pos = line.find(",");
        string ma = line.substr(0, pos);
        string ten = line.substr(pos + 1);
        themSinhVien(ma, ten, false);
    }
    fsv.close();

    ifstream fmh("courses.txt");
    while (getline(fmh, line)) {
        size_t pos = line.find(",");
        string ma = line.substr(0, pos);
        string ten = line.substr(pos + 1);
        themMonHoc(ma, ten, false);
    }
    fmh.close();

    ifstream fdiem("scores.txt");
    while (getline(fdiem, line)) {
        size_t p1 = line.find(",");
        size_t p2 = line.rfind(",");
        string maSV = line.substr(0, p1);
        string maMH = line.substr(p1 + 1, p2 - p1 - 1);
        float diem = stof(line.substr(p2 + 1));
        themDiem(maSV, maMH, diem, false);
    }
    fdiem.close();

    cout << "Da doc du lieu tu file.\n";
}

void sapXepSVTheoTen() {
    vector<SinhVien*> svList;
    for (SinhVien* p = dsSV; p; p = p->next) svList.push_back(p);
    sort(svList.begin(), svList.end(), [](SinhVien* a, SinhVien* b) {
        return a->hoTen < b->hoTen;
    });
    cout << "\nSV theo ten:\n";
    for (SinhVien* sv : svList)
        cout << sv->maSV << " - " << sv->hoTen << endl;
}

void sapXepSVTheoMa() {
    vector<SinhVien*> svList;
    for (SinhVien* p = dsSV; p; p = p->next) svList.push_back(p);
    sort(svList.begin(), svList.end(), [](SinhVien* a, SinhVien* b) {
        return a->maSV < b->maSV;
    });
    cout << "\nSV theo ma SV:\n";
    for (SinhVien* sv : svList)
        cout << sv->maSV << " - " << sv->hoTen << endl;
}

void sapXepSVTheoDTBTang() {
    vector<SinhVien*> svList;
    for (SinhVien* p = dsSV; p; p = p->next) svList.push_back(p);
    sort(svList.begin(), svList.end(), [](SinhVien* a, SinhVien* b) {
        return tinhDiemTB(a->maSV) < tinhDiemTB(b->maSV);
    });
    cout << "\nSV theo diem TB tang:\n";
    for (SinhVien* sv : svList)
        cout << sv->maSV << " - " << sv->hoTen << " - " << tinhDiemTB(sv->maSV) << endl;
}

void sapXepSVTheoDTBGiam() {
    vector<SinhVien*> svList;
    for (SinhVien* p = dsSV; p; p = p->next) svList.push_back(p);
    sort(svList.begin(), svList.end(), [](SinhVien* a, SinhVien* b) {
        return tinhDiemTB(a->maSV) > tinhDiemTB(b->maSV);
    });
    cout << "\nSV theo diem TB giam:\n";
    for (SinhVien* sv : svList)
        cout << sv->maSV << " - " << sv->hoTen << " - " << tinhDiemTB(sv->maSV) << endl;
}

void diemCaoNhat() {
    float maxDiem = -1;
    Diem* p = dsDiem;
    while (p) {
        if (p->diem > maxDiem) maxDiem = p->diem;
        p = p->next;
    }
    cout << "\nDiem cao nhat: " << maxDiem << endl;
}

void diemThapNhat() {
    float minDiem = 11;
    Diem* p = dsDiem;
    while (p) {
        if (p->diem < minDiem) minDiem = p->diem;
        p = p->next;
    }
    cout << "\nDiem thap nhat: " << minDiem << endl;
}

void svDiemTBCaoNhat() {
    SinhVien* best = nullptr;
    float maxDTB = -1;
    for (SinhVien* p = dsSV; p; p = p->next) {
        float dtb = tinhDiemTB(p->maSV);
        if (dtb > maxDTB) {
            maxDTB = dtb;
            best = p;
        }
    }
    if (best)
        cout << "\nSV co DTB cao nhat: " << best->maSV << " - " << best->hoTen << " - " << maxDTB << endl;
}

void svDiemTBThapNhat() {
    SinhVien* worst = nullptr;
    float minDTB = 11;
    for (SinhVien* p = dsSV; p; p = p->next) {
        float dtb = tinhDiemTB(p->maSV);
        if (dtb < minDTB) {
            minDTB = dtb;
            worst = p;
        }
    }
    if (worst)
        cout << "\nSV co DTB thap nhat: " << worst->maSV << " - " << worst->hoTen << " - " << minDTB << endl;
}

void thongKeDauRotTheoMon() {
    map<string, pair<int, int>> kq; // maMH -> (dau, rot)
    Diem* p = dsDiem;
    while (p) {
        if (p->diem >= 5)
            kq[p->maMH].first++;
        else
            kq[p->maMH].second++;
        p = p->next;
    }
    cout << "\nThong ke dau/rot (theo mon):\n";
    for (auto& kv : kq) {
        MonHoc* mh = timMH(kv.first);
        cout << kv.first << " - " << (mh ? mh->tenMH : "") << " => Dau: " << kv.second.first << ", Rot: " << kv.second.second << endl;
    }
}

void demSoLuongThongKe() {
    int sv = 0, mh = 0, diem = 0;
    for (SinhVien* p = dsSV; p; p = p->next) sv++;
    for (MonHoc* p = dsMH; p; p = p->next) mh++;
    for (Diem* p = dsDiem; p; p = p->next) diem++;
    cout << "\nSo luong: " << sv << " SV, " << mh << " mon, " << diem << " diem.\n";
}

void menu() {
    int chon;
    do {
        cout << "\n======= MENU =======\n";
        cout << "1. Them sinh vien\n";
        cout << "2. Them mon hoc\n";
        cout << "3. Them diem\n";
        cout << "4. In danh sach sinh vien\n";
        cout << "5. In danh sach mon hoc\n";
        cout << "6. In bang diem\n";
        cout << "7. Tim sinh vien theo ten\n";
        cout << "8. Sap xep sinh vien\n";
		cout << "9. Thong ke so luong va hoc luc\n";
        cout << "10. Thong ke diem cao nhat/ thap nhat\n";
        cout << "11. Sua sinh vien/ mon hoc/ diem\n";
        cout << "12. Xoa sinh vien/ mon hoc/ diem\n";

        cout << "0. Thoat\n";
        cout << "Chon: ";
        cin >> chon;
        cin.ignore();

        if (chon == 1) {
            string ma, ten;
            cout << "Nhap ma SV: "; getline(cin, ma);
            cout << "Nhap ten: "; getline(cin, ten);
            themSinhVien(ma, ten);
        } else if (chon == 2) {
            string ma, ten;
            cout << "Nhap ma MH: "; getline(cin, ma);
            cout << "Nhap ten MH: "; getline(cin, ten);
            themMonHoc(ma, ten);
        } else if (chon == 3) {
            string maSV, maMH;
            float diem;
            cout << "Nhap ma SV: "; getline(cin, maSV);
            cout << "Nhap ma MH: "; getline(cin, maMH);
            cout << "Nhap diem: "; cin >> diem; cin.ignore();
            themDiem(maSV, maMH, diem);
        } else if (chon == 4) inDSSV();
        else if (chon == 5) inDSMH();
        else if (chon == 6) inDSDiem();
        else if (chon == 7) {
            string ten;
            cout << "Nhap tu khoa ten: "; getline(cin, ten);
            timKiemSVTheoTen(ten);
        }
        else if (chon == 8) {
		    int loai;
		    cout << "1. Theo ma SV | 2. Theo ten | 3. DTB tang | 4. DTB giam: ";
		    cin >> loai; cin.ignore();
		    if (loai == 1) sapXepSVTheoMa();
		    else if (loai == 2) sapXepSVTheoTen();
		    else if (loai == 3) sapXepSVTheoDTBTang();
		    else if (loai == 4) sapXepSVTheoDTBGiam();
		}
        else if (chon == 9) {
		    demSoLuongThongKe();
		    thongKeHocLuc();
		    thongKeDauRotTheoMon();
		}
		else if (chon == 10) {
		    diemCaoNhat();
		    diemThapNhat();
		    svDiemTBCaoNhat();
		    svDiemTBThapNhat();
		}
        else if (chon == 11) {
            int loai;
            cout << "1. Sua SV | 2. Sua MH | 3. Sua diem: ";
            cin >> loai; cin.ignore();
            if (loai == 1) {
                string ma; cout << "Nhap ma SV: "; getline(cin, ma);
                suaSinhVien(ma);
            } else if (loai == 2) {
                string ma; cout << "Nhap ma MH: "; getline(cin, ma);
                suaMonHoc(ma);
            } else if (loai == 3) {
                string maSV, maMH;
                cout << "Nhap ma SV: "; getline(cin, maSV);
                cout << "Nhap ma MH: "; getline(cin, maMH);
                suaDiem(maSV, maMH);
            }
        }
        else if (chon == 12) {
            int loai;
            cout << "1. Xoa SV | 2. Xoa MH | 3. Xoa diem: ";
            cin >> loai; cin.ignore();
            if (loai == 1) {
                string ma; cout << "Nhap ma SV: "; getline(cin, ma);
                xoaSinhVien(ma);
            } else if (loai == 2) {
                string ma; cout << "Nhap ma MH: "; getline(cin, ma);
                xoaMonHoc(ma);
            } else if (loai == 3) {
                string maSV, maMH;
                cout << "Nhap ma SV: "; getline(cin, maSV);
                cout << "Nhap ma MH: "; getline(cin, maMH);
                xoaDiem(maSV, maMH);
            }
        }
        
    } while (chon != 0);
}

int main() {
	docFile(); 
    menu();
    ghiFile(); 
    return 0;
}
