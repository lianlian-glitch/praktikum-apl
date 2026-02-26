#include <iostream>
#include <iomanip>
using namespace std;

int main() {

    string nama;
    string password;
    string passwordBenar = "089"; 
    int percobaan = 0;

    cout << "=====================================\n";
    cout << "         PROGRAM KONVERSI PANJANG    \n";
    cout << "=====================================\n\n";

    while (percobaan < 3) {

        cout << "Login Terlebih Dahulu\n";
        cout << "Nama     : ";
        cin >> nama;
        cout << "Password (3 digit terakhir NIM): ";
        cin >> password;

        if (password == passwordBenar) {
            cout << "\nLogin Berhasil! Selamat datang, " << nama << "!\n\n";
            break;
        } else {
            percobaan++;
            cout << "Password salah! Percobaan ke-" << percobaan << endl;
            if (percobaan == 3) {
                cout << "\nAnda salah 3 kali. Program berhenti.\n";
                return 0;
            }
        }
    }

    int pilihan;
    double nilai;

    do {
        cout << "\n=====================================\n";
        cout << "            MENU UTAMA               \n";
        cout << "=====================================\n";
        cout << "1. Meter -> Kilometer & Centimeter\n";
        cout << "2. Kilometer -> Meter & Centimeter\n";
        cout << "3. Centimeter -> Meter & Kilometer\n";
        cout << "4. Keluar\n";
        cout << "=====================================\n";
        cout << "Pilih menu (1-4): ";
        cin >> pilihan;

        switch (pilihan) {

        case 1:
            cout << "\nMasukkan nilai dalam Meter: ";
            cin >> nilai;
            cout << fixed << setprecision(2);
            cout << "Hasil:\n";
            cout << nilai / 1000 << " Kilometer\n";
            cout << nilai * 100 << " Centimeter\n";
            break;

        case 2:
            cout << "\nMasukkan nilai dalam Kilometer: ";
            cin >> nilai;
            cout << fixed << setprecision(2);
            cout << "Hasil:\n";
            cout << nilai * 1000 << " Meter\n";
            cout << nilai * 100000 << " Centimeter\n";
            break;

        case 3:
            cout << "\nMasukkan nilai dalam Centimeter: ";
            cin >> nilai;
            cout << fixed << setprecision(2);
            cout << "Hasil:\n";
            cout << nilai / 100 << " Meter\n";
            cout << nilai / 100000 << " Kilometer\n";
            break;

        case 4:
            cout << "\nTerima kasih telah menggunakan program ini.\n";
            cout << "Program selesai.\n";
            break;

        default:
            cout << "Pilihan tidak valid! Silakan pilih 1-4.\n";
        }

    } while (pilihan != 4);

    return 0;
}