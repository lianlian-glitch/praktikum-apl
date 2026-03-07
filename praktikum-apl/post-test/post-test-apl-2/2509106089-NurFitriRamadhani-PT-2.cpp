#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct DetailLukisan {
    string gaya;   
    string ukuran; 
};

struct Pesanan {
    string pemesan;
    DetailLukisan detail; 
    string status;
    long harga;
};

struct User {
    string username; 
    string password; 
    string role; 
};

#define MAX_USERS 50
#define MAX_PESANAN 100
#define MAX_INFO 100 

int main() {
    User users[MAX_USERS];
    int userCount = 0;

    Pesanan pesanan[MAX_PESANAN];
    int panjangPesanan = 0; 
    
    string papanInfo[MAX_INFO];
    int infoCount = 0;

    User currentUser; 

    // --- SUNTIKAN DATA ADMIN ---
    users[0].username = "NurFitriRamadhani"; 
    users[0].password = "2509106089"; 
    users[0].role = "admin";
    userCount++;
    // ---------------------------

    int menuAwal;
    
    // ================= LOOPING MENU AWAL =================
    do {
        system("cls"); // Membersihkan layar khusus untuk menu awal
        cout << "\n==============================\n";
        cout << " SISTEM KOMISI LUKISAN\n";
        cout << "==============================\n";
        cout << "1. Register (Pengguna Baru)\n";
        cout << "2. Login\n";
        cout << "3. Keluar\n";
        cout << "Pilihan: ";
        cin >> menuAwal;
        cin.ignore(256, '\n');

        switch (menuAwal) {
            
            // ------------------ REGISTER ------------------
            case 1: {
                if (userCount < MAX_USERS) {
                    cout << "\n--- REGISTER PENGGUNA BARU ---\n";
                    cout << "Masukkan Nama : "; 
                    getline(cin, users[userCount].username);
                    
                    cout << "Masukkan NIM  : "; 
                    getline(cin, users[userCount].password);
                    
                    users[userCount].role = "user"; 
                    userCount++;
                    cout << "Registrasi sukses! Silakan login.\n";
                } else {
                    cout << "Kapasitas pengguna penuh!\n";
                }
                
                cout << "\nTekan Enter untuk kembali...";
                cin.get();
                break;
            }
            
            // ------------------ LOGIN ------------------
            case 2: {
                if (userCount == 0) {
                    cout << "Belum ada akun yang terdaftar.\n";
                    cout << "\nTekan Enter untuk kembali...";
                    cin.get();
                } else {
                    string inNama, inNIM;
                    int kesempatan = 3;
                    bool isLogin = false; 

                    while (kesempatan > 0) {
                        cout << "\n--- LOGIN ---\n";
                        cout << "Nama (Username) : "; 
                        getline(cin, inNama);
                        cout << "NIM (Password)  : "; 
                        getline(cin, inNIM);

                        for (int i = 0; i < userCount; i++) {
                            if (users[i].username == inNama && users[i].password == inNIM) {
                                currentUser = users[i];
                                isLogin = true;
                                break;
                            }
                        }

                        if (isLogin) {
                            cout << "\n[!] Login Berhasil! Selamat datang, " << currentUser.username << ".\n";
                            break; 
                        } else {
                            kesempatan--;
                            cout << "[!] Login Gagal! Kesempatan tersisa: " << kesempatan << "\n";
                        }
                    }

                    if (!isLogin) {
                        cout << "\n[!] Anda gagal login 3 kali. Program otomatis berhenti.\n";
                        return 0; 
                    } 
                    
                    // ================= MENU ADMIN =================
                    if (currentUser.role == "admin") {
                        int pilihanAdmin;
                        do {
                            cout << "\n=== MENU ADMIN (" << currentUser.username << ") ===\n";
                            cout << "1. Tambah Informasi/Pengumuman (Create)\n";
                            cout << "2. Lihat Semua Pesanan Masuk (Read)\n";
                            cout << "3. Setujui Pesanan (Update)\n";
                            cout << "4. Batalkan Pesanan (Delete)\n";
                            cout << "5. Logout\n";
                            cout << "Pilihan: ";
                            cin >> pilihanAdmin;
                            cin.ignore(256, '\n');

                            switch(pilihanAdmin) {
                                case 1: { 
                                    if(infoCount < MAX_INFO) {
                                        cout << "\n--- TAMBAH INFORMASI ---\n";
                                        cout << "Masukkan teks informasi: ";
                                        string teks;
                                        getline(cin, teks);
                                        papanInfo[infoCount] = "[INFO ADMIN] " + teks;
                                        infoCount++;
                                        cout << "Informasi berhasil ditambahkan!\n";
                                    } else {
                                        cout << "Papan informasi penuh!\n";
                                    }
                                    break;
                                }
                                case 2: { 
                                    if (panjangPesanan == 0) {
                                        cout << "Belum ada pesanan masuk.\n";
                                    } else {
                                        cout << "\n=== SEMUA DATA PESANAN ===\n";
                                        cout << "=======================================================================================\n";
                                        cout << left << setw(5) << "No" << setw(20) << "Pemesan" << setw(15) << "Gaya" << setw(15) << "Ukuran" << setw(20) << "Status" << "Harga (Rp)" << endl;
                                        cout << "=======================================================================================\n";
                                        for (int i = 0; i < panjangPesanan; i++) {
                                            cout << left << setw(5) << i + 1 << setw(20) << pesanan[i].pemesan << setw(15) << pesanan[i].detail.gaya << setw(15) << pesanan[i].detail.ukuran << setw(20) << pesanan[i].status << pesanan[i].harga << endl;
                                        }
                                        cout << "---------------------------------------------------------------------------------------\n";
                                    }
                                    break;
                                }
                                case 3: { 
                                    if (panjangPesanan == 0) {
                                        cout << "Belum ada pesanan masuk.\n";
                                    } else {
                                        cout << "\n=== SEMUA DATA PESANAN ===\n";
                                        cout << "=======================================================================================\n";
                                        cout << left << setw(5) << "No" << setw(20) << "Pemesan" << setw(15) << "Gaya" << setw(15) << "Ukuran" << setw(20) << "Status" << "Harga (Rp)" << endl;
                                        cout << "=======================================================================================\n";
                                        for (int i = 0; i < panjangPesanan; i++) {
                                            cout << left << setw(5) << i + 1 << setw(20) << pesanan[i].pemesan << setw(15) << pesanan[i].detail.gaya << setw(15) << pesanan[i].detail.ukuran << setw(20) << pesanan[i].status << pesanan[i].harga << endl;
                                        }
                                        cout << "---------------------------------------------------------------------------------------\n";

                                        int index;
                                        cout << "Masukkan Nomor Pesanan yang ingin Disetujui: ";
                                        cin >> index;
                                        cin.ignore(256, '\n');

                                        if (index > 0 && index <= panjangPesanan) {
                                            pesanan[index - 1].status = "Disetujui Admin";
                                            cout << "Pesanan berhasil disetujui!\n";
                                        } else {
                                            cout << "Nomor pesanan tidak valid.\n";
                                        }
                                    }
                                    break;
                                }
                                case 4: { 
                                    if (panjangPesanan == 0) {
                                        cout << "Belum ada pesanan masuk.\n";
                                    } else {
                                        cout << "\n=== SEMUA DATA PESANAN ===\n";
                                        cout << "=======================================================================================\n";
                                        cout << left << setw(5) << "No" << setw(20) << "Pemesan" << setw(15) << "Gaya" << setw(15) << "Ukuran" << setw(20) << "Status" << "Harga (Rp)" << endl;
                                        cout << "=======================================================================================\n";
                                        for (int i = 0; i < panjangPesanan; i++) {
                                            cout << left << setw(5) << i + 1 << setw(20) << pesanan[i].pemesan << setw(15) << pesanan[i].detail.gaya << setw(15) << pesanan[i].detail.ukuran << setw(20) << pesanan[i].status << pesanan[i].harga << endl;
                                        }
                                        cout << "---------------------------------------------------------------------------------------\n";

                                        int index;
                                        cout << "Masukkan Nomor Pesanan yang akan dibatalkan: ";
                                        cin >> index;
                                        cin.ignore(256, '\n');

                                        if (index > 0 && index <= panjangPesanan) {
                                            for (int i = index - 1; i < panjangPesanan - 1; i++) {
                                                pesanan[i] = pesanan[i + 1];
                                            }
                                            panjangPesanan--;
                                            cout << "Pesanan berhasil dibatalkan (dihapus)!\n";
                                        } else {
                                            cout << "Nomor pesanan tidak valid.\n";
                                        }
                                    }
                                    break;
                                }
                                case 5: cout << "Logout berhasil. Kembali ke Menu Awal...\n"; break;
                                default: cout << "Pilihan tidak valid.\n"; break;
                            }
                        } while (pilihanAdmin != 5);
                    } 
                    
                    // ================= MENU PENGGUNA =================
                    else {
                        int pilihanUser;
                        do {
                            cout << "\n=== MENU PENGGUNA (" << currentUser.username << ") ===\n";
                            cout << "1. Buat Pesanan Lukisan (Create)\n";
                            cout << "2. Lihat Info & Pesanan (Read)\n";
                            cout << "3. Ubah Pesanan (Update)\n";
                            cout << "4. Batalkan Pesanan Sendiri (Delete)\n";
                            cout << "5. Logout\n";
                            cout << "Pilihan: ";
                            cin >> pilihanUser;
                            cin.ignore(256, '\n');

                            switch(pilihanUser) {
                                case 1: { 
                                    if (panjangPesanan < MAX_PESANAN) {
                                        cout << "\n--- TAMBAH PESANAN BARU ---\n";
                                        pesanan[panjangPesanan].pemesan = currentUser.username; 
                                        pesanan[panjangPesanan].status = "Menunggu Konfirmasi"; 

                                        cout << "Masukkan Gaya Lukisan (Cth: Anime/Realis) : ";
                                        getline(cin, pesanan[panjangPesanan].detail.gaya);
                                        
                                        cout << "Masukkan Ukuran (Cth: A4/1080p)           : ";
                                        getline(cin, pesanan[panjangPesanan].detail.ukuran);

                                        cout << "Masukkan Harga (Rp)                       : ";
                                        cin >> pesanan[panjangPesanan].harga;
                                        cin.ignore(256, '\n');

                                        panjangPesanan++;
                                        cout << "Pesanan berhasil dibuat!\n";
                                    } else {
                                        cout << "Kapasitas pesanan penuh!\n";
                                    }
                                    break;
                                }
                                case 2: { 
                                    int subMenu;
                                    cout << "\n1. liat papan info\n";
                                    cout << "2. lihat status pesananku\n";
                                    cout << "Pilih: ";
                                    cin >> subMenu;
                                    cin.ignore(256, '\n');

                                    if (subMenu == 1) {
                                        cout << "\n============= PAPAN INFORMASI =============\n";
                                        if (infoCount == 0) {
                                            cout << "Belum ada informasi terbaru dari Admin.\n";
                                        } else {
                                            for(int i = 0; i < infoCount; i++) {
                                                cout << "- " << papanInfo[i] << endl;
                                            }
                                        }
                                        cout << "===========================================\n";
                                    } else if (subMenu == 2) {
                                        cout << "\n=== DAFTAR PESANANKU ===\n";
                                        cout << "=======================================================================================\n";
                                        cout << left << setw(5) << "No" << setw(20) << "Pemesan" << setw(15) << "Gaya" << setw(15) << "Ukuran" << setw(20) << "Status" << "Harga (Rp)" << endl;
                                        cout << "=======================================================================================\n";
                                        for (int i = 0; i < panjangPesanan; i++) {
                                            if (pesanan[i].pemesan == currentUser.username) {
                                                cout << left << setw(5) << i + 1 << setw(20) << pesanan[i].pemesan << setw(15) << pesanan[i].detail.gaya << setw(15) << pesanan[i].detail.ukuran << setw(20) << pesanan[i].status << pesanan[i].harga << endl;
                                            }
                                        }
                                        cout << "---------------------------------------------------------------------------------------\n";
                                    } else {
                                        cout << "Pilihan tidak valid.\n";
                                    }
                                    break;
                                }
                                case 3: { 
                                    if (panjangPesanan == 0) {
                                        cout << "Anda belum memiliki pesanan.\n";
                                    } else {
                                        cout << "\n=== DAFTAR PESANANKU ===\n";
                                        cout << "=======================================================================================\n";
                                        cout << left << setw(5) << "No" << setw(20) << "Pemesan" << setw(15) << "Gaya" << setw(15) << "Ukuran" << setw(20) << "Status" << "Harga (Rp)" << endl;
                                        cout << "=======================================================================================\n";
                                        for (int i = 0; i < panjangPesanan; i++) {
                                            if (pesanan[i].pemesan == currentUser.username) {
                                                cout << left << setw(5) << i + 1 << setw(20) << pesanan[i].pemesan << setw(15) << pesanan[i].detail.gaya << setw(15) << pesanan[i].detail.ukuran << setw(20) << pesanan[i].status << pesanan[i].harga << endl;
                                            }
                                        }
                                        cout << "---------------------------------------------------------------------------------------\n";

                                        int index;
                                        cout << "Masukkan Nomor Pesanan yang akan diubah: ";
                                        cin >> index;
                                        cin.ignore(256, '\n');

                                        if (index > 0 && index <= panjangPesanan) {
                                            if (pesanan[index - 1].pemesan == currentUser.username) {
                                                cout << "Masukkan Gaya Lukisan baru : ";
                                                getline(cin, pesanan[index - 1].detail.gaya);
                                                
                                                cout << "Masukkan Ukuran baru       : ";
                                                getline(cin, pesanan[index - 1].detail.ukuran);

                                                cout << "Masukkan Harga baru (Rp)   : ";
                                                cin >> pesanan[index - 1].harga;
                                                cin.ignore(256, '\n');
                                                
                                                cout << "Pesanan berhasil diubah.\n";
                                            } else {
                                                cout << "Itu bukan pesanan Anda!\n";
                                            }
                                        } else {
                                            cout << "Nomor pesanan tidak valid.\n";
                                        }
                                    }
                                    break;
                                }
                                case 4: { 
                                    if (panjangPesanan == 0) {
                                        cout << "Anda belum memiliki pesanan.\n";
                                    } else {
                                        cout << "\n=== DAFTAR PESANANKU ===\n";
                                        cout << "=======================================================================================\n";
                                        cout << left << setw(5) << "No" << setw(20) << "Pemesan" << setw(15) << "Gaya" << setw(15) << "Ukuran" << setw(20) << "Status" << "Harga (Rp)" << endl;
                                        cout << "=======================================================================================\n";
                                        for (int i = 0; i < panjangPesanan; i++) {
                                            if (pesanan[i].pemesan == currentUser.username) {
                                                cout << left << setw(5) << i + 1 << setw(20) << pesanan[i].pemesan << setw(15) << pesanan[i].detail.gaya << setw(15) << pesanan[i].detail.ukuran << setw(20) << pesanan[i].status << pesanan[i].harga << endl;
                                            }
                                        }
                                        cout << "---------------------------------------------------------------------------------------\n";

                                        int index;
                                        cout << "Masukkan Nomor Pesanan yang akan dibatalkan: ";
                                        cin >> index;
                                        cin.ignore(256, '\n'); 

                                        if (index > 0 && index <= panjangPesanan) {
                                            if (pesanan[index - 1].pemesan == currentUser.username) {
                                                string komenUser;
                                                cout << "Masukkan alasan batal (Wajib diisi): ";
                                                getline(cin, komenUser);

                                                if (komenUser == "") {
                                                    cout << "[!] Pembatalan gagal! Alasan pembatalan wajib diisi.\n";
                                                } else {
                                                    // Data langsung dihapus TANPA dimasukkan ke papanInfo
                                                    for (int i = index - 1; i < panjangPesanan - 1; i++) {
                                                        pesanan[i] = pesanan[i + 1];
                                                    }
                                                    panjangPesanan--;
                                                    cout << "Pesanan Anda berhasil dibatalkan!\n";
                                                }
                                            } else {
                                                cout << "Itu bukan pesanan Anda!\n";
                                            }
                                        } else {
                                            cout << "Nomor pesanan tidak valid.\n";
                                        }
                                    }
                                    break;
                                }
                                case 5: cout << "Logout berhasil. Kembali ke Menu Awal...\n"; break;
                                default: cout << "Pilihan tidak valid.\n"; break;
                            }
                        } while (pilihanUser != 5);
                    }
                }
                break;
            }
            case 3:
                cout << "Program selesai.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
    } while (menuAwal != 3);

    return 0;
}