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

// =========================================================================
// DEKLARASI PROSEDUR DAN FUNGSI
// =========================================================================

// 1. PROSEDUR DENGAN PARAMETER (Pass by Reference untuk userCount)
void registerUser(User users[], int &userCount) {
    if (userCount < MAX_USERS) {
        cout << "\n--- REGISTER PENGGUNA BARU ---\n";
        
        string inputNama;
        bool namaSudahAda;

        // Validasi agar tidak ada nama akun yang sama
        do {
            namaSudahAda = false; // Reset status menjadi false setiap kali mencoba input
            cout << "Masukkan Nama : "; 
            getline(cin, inputNama);

            // Mengecek apakah nama sudah ada di database (array users)
            for (int i = 0; i < userCount; i++) {
                if (users[i].username == inputNama) {
                    namaSudahAda = true; // Tandai bahwa nama ketemu (duplikat)
                    cout << "[!] Pendaftaran Gagal: Nama '" << inputNama << "' sudah digunakan!\n";
                    cout << "    Silakan masukkan nama akun yang berbeda.\n\n";
                    break; // Hentikan pencarian (for), langsung kembali ke atas (do)
                }
            }
        } while (namaSudahAda == true); // Terus mengulang jika namaSudahAda bernilai true

        // Simpan nama yang sudah tervalidasi ke dalam array
        users[userCount].username = inputNama;
        
        // ---> PERUBAHAN TEKS: "NIM" menjadi "Password" <---
        cout << "Masukkan Password : "; 
        getline(cin, users[userCount].password);
        
        users[userCount].role = "user"; 
        userCount++;
        cout << "Registrasi sukses! Silakan login.\n";
    } else {
        cout << "Kapasitas pengguna penuh!\n";
    }
}

// 2. FUNGSI MENGEMBALIKAN NILAI (Pass by Reference untuk currentUser)
bool loginUser(User users[], int userCount, User &currentUser) {
    string inNama, inNIM;
    int kesempatan = 3;

    while (kesempatan > 0) {
        cout << "\n--- LOGIN ---\n";
        cout << "Nama (Username) : "; 
        getline(cin, inNama);
        // ---> PERUBAHAN TEKS: "NIM" menjadi "Password" <---
        cout << "Password        : "; 
        getline(cin, inNIM);

        for (int i = 0; i < userCount; i++) {
            if (users[i].username == inNama && users[i].password == inNIM) {
                currentUser = users[i];
                cout << "\n[!] Login Berhasil! Selamat datang, " << currentUser.username << ".\n";
                return true; // Berhenti dan kembalikan true
            }
        }
        kesempatan--;
        cout << "[!] Login Gagal! Kesempatan tersisa: " << kesempatan << "\n";
    }
    return false; // Gagal 3 kali
}

// 3. FUNGSI OVERLOADING - VERSI 1 (Hanya butuh 2 parameter, untuk ADMIN)
void tampilkanPesanan(Pesanan pesanan[], int panjangPesanan) {
    if (panjangPesanan == 0) {
        cout << "Belum ada pesanan masuk.\n";
        return;
    }
    cout << "\n=== SEMUA DATA PESANAN (ADMIN) ===\n";
    cout << "=======================================================================================\n";
    cout << left << setw(5) << "No" << setw(20) << "Pemesan" << setw(15) << "Gaya" << setw(15) << "Ukuran" << setw(20) << "Status" << "Harga (Rp)" << endl;
    cout << "=======================================================================================\n";
    for (int i = 0; i < panjangPesanan; i++) {
        cout << left << setw(5) << i + 1 << setw(20) << pesanan[i].pemesan << setw(15) << pesanan[i].detail.gaya << setw(15) << pesanan[i].detail.ukuran << setw(20) << pesanan[i].status << pesanan[i].harga << endl;
    }
    cout << "---------------------------------------------------------------------------------------\n";
}

// 4. FUNGSI OVERLOADING - VERSI 2 (Butuh 3 parameter, ada filter username, untuk USER)
void tampilkanPesanan(Pesanan pesanan[], int panjangPesanan, string username) {
    cout << "\n=== DAFTAR PESANANKU ===\n";
    cout << "=======================================================================================\n";
    cout << left << setw(5) << "No" << setw(20) << "Pemesan" << setw(15) << "Gaya" << setw(15) << "Ukuran" << setw(20) << "Status" << "Harga (Rp)" << endl;
    cout << "=======================================================================================\n";
    bool adaData = false;
    for (int i = 0; i < panjangPesanan; i++) {
        if (pesanan[i].pemesan == username) {
            cout << left << setw(5) << i + 1 << setw(20) << pesanan[i].pemesan << setw(15) << pesanan[i].detail.gaya << setw(15) << pesanan[i].detail.ukuran << setw(20) << pesanan[i].status << pesanan[i].harga << endl;
            adaData = true;
        }
    }
    if (!adaData) {
        cout << "Anda belum memiliki pesanan aktif.\n";
    }
    cout << "---------------------------------------------------------------------------------------\n";
}

// 5. FUNGSI REKURSIF (Memanggil dirinya sendiri untuk menghitung total belanja)
long hitungTotalBelanjaRekursif(Pesanan pesanan[], int index, string username) {
    // Base case: jika index kurang dari 0, hentikan rekursi
    if (index < 0) {
        return 0; 
    }
    
    // Panggil fungsi untuk index sebelumnya
    long totalSebelah = hitungTotalBelanjaRekursif(pesanan, index - 1, username);
    
    // Tambahkan harga jika pesanan milik user tersebut
    if (pesanan[index].pemesan == username) {
        return pesanan[index].harga + totalSebelah;
    }
    
    return totalSebelah;
}

// --- FUNGSI & PROSEDUR TAMBAHAN UNTUK MEMECAH KODE ---

void tambahInfoAdmin(string papanInfo[], int &infoCount) {
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
}

void kelolaStatusPesanan(Pesanan pesanan[], int panjangPesanan, string statusBaru) {
    tampilkanPesanan(pesanan, panjangPesanan); // Memanggil Overloading 1
    if (panjangPesanan == 0) return;

    int index;
    cout << "Masukkan Nomor Pesanan yang akan diproses: ";
    cin >> index;
    cin.ignore(256, '\n');

    if (index > 0 && index <= panjangPesanan) {
        pesanan[index - 1].status = statusBaru;
        cout << "Status pesanan berhasil diubah menjadi: " << statusBaru << "!\n";
    } else {
        cout << "Nomor pesanan tidak valid.\n";
    }
}

void hapusPesanan(Pesanan pesanan[], int &panjangPesanan, string usernameAdminAtauUser, bool isAdmin) {
    if (isAdmin) {
        tampilkanPesanan(pesanan, panjangPesanan); // Overloading 1
    } else {
        tampilkanPesanan(pesanan, panjangPesanan, usernameAdminAtauUser); // Overloading 2
    }
    
    if (panjangPesanan == 0) return;

    int index;
    cout << "Masukkan Nomor Pesanan yang akan dibatalkan/dihapus: ";
    cin >> index;
    cin.ignore(256, '\n');

    if (index > 0 && index <= panjangPesanan) {
        // Jika bukan admin, pastikan pesanan miliknya
        if (!isAdmin && pesanan[index - 1].pemesan != usernameAdminAtauUser) {
            cout << "Itu bukan pesanan Anda!\n";
            return;
        }

        // Geser array untuk menghapus
        for (int i = index - 1; i < panjangPesanan - 1; i++) {
            pesanan[i] = pesanan[i + 1];
        }
        panjangPesanan--;
        cout << "Pesanan berhasil dibatalkan (dihapus)!\n";
    } else {
        cout << "Nomor pesanan tidak valid.\n";
    }
}

void buatPesananUser(Pesanan pesanan[], int &panjangPesanan, string username) {
    if (panjangPesanan < MAX_PESANAN) {
        cout << "\n--- TAMBAH PESANAN BARU ---\n";
        pesanan[panjangPesanan].pemesan = username; 
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
}

void ubahPesananUser(Pesanan pesanan[], int panjangPesanan, string username) {
    tampilkanPesanan(pesanan, panjangPesanan, username); // Overloading 2
    if (panjangPesanan == 0) return;

    int index;
    cout << "Masukkan Nomor Pesanan yang akan diubah: ";
    cin >> index;
    cin.ignore(256, '\n');

    if (index > 0 && index <= panjangPesanan) {
        if (pesanan[index - 1].pemesan == username) {
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

void bacaPapanInfo(string papanInfo[], int infoCount) {
    cout << "\n============= PAPAN INFORMASI =============\n";
    if (infoCount == 0) {
        cout << "Belum ada informasi terbaru dari Admin.\n";
    } else {
        for(int i = 0; i < infoCount; i++) {
            cout << "- " << papanInfo[i] << endl;
        }
    }
    cout << "===========================================\n";
}

// =========================================================================
// PROGRAM UTAMA (MAIN)
// =========================================================================

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
    users[0].password = "2509106089"; // Ini adalah password default admin
    users[0].role = "admin";
    userCount++;
    // ---------------------------

    int menuAwal;
    
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
            case 1: 
                registerUser(users, userCount); // Panggilan Prosedur
                cout << "\nTekan Enter untuk kembali...";
                cin.get();
                break;
            
            case 2: 
                if (userCount == 0) {
                    cout << "Belum ada akun yang terdaftar.\n";
                    cout << "\nTekan Enter untuk kembali...";
                    cin.get();
                } else {
                    bool suksesLogin = loginUser(users, userCount, currentUser); // Panggilan Fungsi dgn Return
                    
                    if (!suksesLogin) {
                        cout << "\n[!] Program otomatis berhenti karena gagal login.\n";
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
                                case 1: tambahInfoAdmin(papanInfo, infoCount); break;
                                case 2: tampilkanPesanan(pesanan, panjangPesanan); break; // Overload 1
                                case 3: kelolaStatusPesanan(pesanan, panjangPesanan, "Disetujui Admin"); break;
                                case 4: hapusPesanan(pesanan, panjangPesanan, currentUser.username, true); break;
                                case 5: cout << "Logout berhasil.\n"; break;
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
                                case 1: buatPesananUser(pesanan, panjangPesanan, currentUser.username); break;
                                case 2: {
                                    int subMenu;
                                    cout << "\n1. Liat papan info\n";
                                    cout << "2. Lihat status pesananku\n";
                                    cout << "Pilih: ";
                                    cin >> subMenu;
                                    cin.ignore(256, '\n');

                                    if (subMenu == 1) {
                                        bacaPapanInfo(papanInfo, infoCount);
                                    } else if (subMenu == 2) {
                                        tampilkanPesanan(pesanan, panjangPesanan, currentUser.username); // Overload 2
                                        
                                        // Menerapkan Hasil Fungsi Rekursif (Bonus Point)
                                        long total = hitungTotalBelanjaRekursif(pesanan, panjangPesanan - 1, currentUser.username);
                                        cout << ">> Estimasi Total Belanja Anda: Rp " << total << endl;
                                    } else {
                                        cout << "Pilihan tidak valid.\n";
                                    }
                                    break;
                                }
                                case 3: ubahPesananUser(pesanan, panjangPesanan, currentUser.username); break;
                                case 4: hapusPesanan(pesanan, panjangPesanan, currentUser.username, false); break;
                                case 5: cout << "Logout berhasil.\n"; break;
                                default: cout << "Pilihan tidak valid.\n"; break;
                            }
                        } while (pilihanUser != 5);
                    }
                }
                break;
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