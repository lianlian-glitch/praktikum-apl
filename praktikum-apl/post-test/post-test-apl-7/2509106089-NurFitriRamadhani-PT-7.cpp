#include <iostream>
#include <string>
#include <iomanip>
#include <stdexcept> 
#include <limits>    
#include <thread>    
#include <chrono>    
#include "komisi.h"  

using namespace std;

void animasiLoading(string pesan) {
    cout << pesan;
    for (int i = 0; i < 3; i++) {
        this_thread::sleep_for(chrono::milliseconds(400));
        cout << ".";
    }
    cout << endl;
    this_thread::sleep_for(chrono::milliseconds(300));
}

void linearSearchHarga(Pesanan *pesanan, int n, long targetHarga) {
    bool found = false;
    cout << "\n=== HASIL PENCARIAN HARGA Rp " << targetHarga << " ===\n";
    cout << "=======================================================================================\n";
    cout << left << setw(5) << "No" << setw(20) << "Pemesan" << setw(15) << "Gaya" << setw(15) << "Ukuran" << setw(20) << "Status" << "Harga (Rp)" << endl;
    cout << "=======================================================================================\n";
    for (int i = 0; i < n; i++) {
        if (pesanan[i].harga == targetHarga) {
            cout << left << setw(5) << i + 1 << setw(20) << pesanan[i].pemesan << setw(15) << pesanan[i].detail.gaya << setw(15) << pesanan[i].detail.ukuran << setw(20) << pesanan[i].status << pesanan[i].harga << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Pesanan dengan harga tersebut tidak ditemukan.\n";
    }
    cout << "---------------------------------------------------------------------------------------\n";
}

void binarySearchPemesan(Pesanan *pesanan, int n, string targetNama) {
    insertionSortNamaAsc(pesanan, n); 
    
    int low = 0;
    int high = n - 1;
    int hasil = -1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (pesanan[mid].pemesan == targetNama) {
            hasil = mid;
            break;
        } else if (pesanan[mid].pemesan < targetNama) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    cout << "\n=== HASIL PENCARIAN NAMA '" << targetNama << "' ===\n";
    cout << "=======================================================================================\n";
    if (hasil != -1) {
        cout << left << setw(5) << "No" << setw(20) << "Pemesan" << setw(15) << "Gaya" << setw(15) << "Ukuran" << setw(20) << "Status" << "Harga (Rp)" << endl;
        cout << left << setw(5) << hasil + 1 << setw(20) << pesanan[hasil].pemesan << setw(15) << pesanan[hasil].detail.gaya << setw(15) << pesanan[hasil].detail.ukuran << setw(20) << pesanan[hasil].status << pesanan[hasil].harga << endl;
    } else {
        cout << "Pesanan atas nama tersebut tidak ditemukan.\n";
    }
    cout << "---------------------------------------------------------------------------------------\n";
}

void registerUser(User users[], int &userCount) {
    if (userCount < MAX_USERS) {
        cout << "\n--- REGISTER PENGGUNA BARU ---\n";
        
        string inputNama;
        bool namaSudahAda;

        do {
            namaSudahAda = false;
            cout << "Masukkan Nama : "; 
            getline(cin, inputNama);

            for (int i = 0; i < userCount; i++) {
                if (users[i].username == inputNama) {
                    namaSudahAda = true;
                    cout << "[!] Pendaftaran Gagal: Nama '" << inputNama << "' sudah digunakan!\n";
                    cout << "    Silakan masukkan nama akun yang berbeda.\n\n";
                    break;
                }
            }
        } while (namaSudahAda == true);

        users[userCount].username = inputNama;
        
        cout << "Masukkan Password : "; 
        getline(cin, users[userCount].password);
        
        users[userCount].role = "user"; 
        userCount++;
        
        animasiLoading("Memproses registrasi");
        cout << "Registrasi sukses! Silakan login.\n";
    } else {
        cout << "Kapasitas pengguna penuh!\n";
    }
}

bool loginUser(User users[], int userCount, User &currentUser) {
    string inNama, inNIM;
    int kesempatan = 3;

    while (kesempatan > 0) {
        cout << "\n--- LOGIN ---\n";
        cout << "Nama (Username) : "; 
        getline(cin, inNama);
        cout << "Password        : "; 
        getline(cin, inNIM);

        animasiLoading("Mencocokkan data");

        for (int i = 0; i < userCount; i++) {
            if (users[i].username == inNama && users[i].password == inNIM) {
                currentUser = users[i];
                cout << "\n[!] Login Berhasil! Selamat datang, " << currentUser.username << ".\n";
                return true;
            }
        }
        kesempatan--;
        if (kesempatan > 0) {
            cout << "[!] Login Gagal! Kesempatan tersisa: " << kesempatan << "\n";
        }
    }
    throw runtime_error("Gagal login terlalu banyak. Program dihentikan demi keamanan.");
    return false;
}

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

long hitungTotalBelanjaRekursif(Pesanan pesanan[], int index, string username) {
    if (index < 0) {
        return 0; 
    }
    
    long totalSebelah = hitungTotalBelanjaRekursif(pesanan, index - 1, username);
    
    if (pesanan[index].pemesan == username) {
        return pesanan[index].harga + totalSebelah;
    }
    
    return totalSebelah;
}

void tambahInfoAdmin(string papanInfo[], int *infoCount) {
    if(*infoCount < MAX_INFO) {
        cout << "\n--- TAMBAH INFORMASI ---\n";
        cout << "Masukkan teks informasi: ";
        string teks;
        getline(cin, teks);
        papanInfo[*infoCount] = "[INFO ADMIN] " + teks;
        (*infoCount)++;
        cout << "Informasi berhasil ditambahkan!\n";
    } else {
        cout << "Papan informasi penuh!\n";
    }
}

void kelolaStatusPesanan(Pesanan pesanan[], int panjangPesanan, string statusBaru) {
    tampilkanPesanan(pesanan, panjangPesanan);
    if (panjangPesanan == 0) return;

    int index;
    try {
        cout << "Masukkan Nomor Pesanan yang akan diproses: ";
        if (!(cin >> index)) {
            throw invalid_argument("Input harus berupa angka!");
        }
        cin.ignore(256, '\n');

        if (index <= 0 || index > panjangPesanan) {
            throw out_of_range("Nomor pesanan tidak valid!");
        }

        Pesanan *ptrPesanan = &pesanan[index - 1];
        ptrPesanan->status = statusBaru;
        cout << "Status pesanan berhasil diubah menjadi: " << statusBaru << "!\n";

    } catch (const exception& e) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "[ERROR] " << e.what() << "\n";
    }
}

void hapusPesanan(Pesanan pesanan[], int &panjangPesanan, string usernameAdminAtauUser, bool isAdmin) {
    if (isAdmin) {
        tampilkanPesanan(pesanan, panjangPesanan);
    } else {
        tampilkanPesanan(pesanan, panjangPesanan, usernameAdminAtauUser); 
    }
    
    if (panjangPesanan == 0) return;

    int index;
    try {
        cout << "Masukkan Nomor Pesanan yang akan dibatalkan/dihapus: ";
        if (!(cin >> index)) {
            throw invalid_argument("Input harus berupa angka!");
        }
        cin.ignore(256, '\n');

        if (index <= 0 || index > panjangPesanan) {
            throw out_of_range("Nomor pesanan tidak ditemukan!");
        }

        if (!isAdmin && pesanan[index - 1].pemesan != usernameAdminAtauUser) {
            throw runtime_error("Itu bukan pesanan Anda! Hak akses ditolak.");
        }

        for (int i = index - 1; i < panjangPesanan - 1; i++) {
            pesanan[i] = pesanan[i + 1];
        }
        panjangPesanan--;
        cout << "Pesanan berhasil dibatalkan (dihapus)!\n";

    } catch (const exception& e) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "[ERROR] " << e.what() << "\n";
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

        try {
            cout << "Masukkan Harga (Rp)                       : ";
            if (!(cin >> pesanan[panjangPesanan].harga)) {
                throw invalid_argument("Harga harus dimasukkan dalam bentuk angka murni!");
            }
            cin.ignore(256, '\n');

            if (pesanan[panjangPesanan].harga < 0) {
                throw logic_error("Harga tidak mungkin bernilai negatif (minus)!");
            }

            panjangPesanan++;
            animasiLoading("Menyimpan pesanan");
            cout << "Pesanan berhasil dibuat!\n";

        } catch (const exception& e) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n[GAGAL] " << e.what() << "\n";
            cout << "Pembuatan pesanan dibatalkan.\n";
        }
    } else {
        cout << "Kapasitas pesanan penuh!\n";
    }
}

void ubahPesananUser(Pesanan pesanan[], int panjangPesanan, string username) {
    tampilkanPesanan(pesanan, panjangPesanan, username);
    if (panjangPesanan == 0) return;

    int index;
    try {
        cout << "Masukkan Nomor Pesanan yang akan diubah: ";
        if (!(cin >> index)) {
            throw invalid_argument("Input nomor harus berupa angka!");
        }
        cin.ignore(256, '\n');

        if (index <= 0 || index > panjangPesanan) {
            throw out_of_range("Nomor pesanan tidak valid.");
        }

        if (pesanan[index - 1].pemesan != username) {
            throw runtime_error("Itu bukan pesanan Anda!");
        }

        Pesanan *ptrPesanan = &pesanan[index - 1];
        
        cout << "Masukkan Gaya Lukisan baru : ";
        getline(cin, ptrPesanan->detail.gaya);
        
        cout << "Masukkan Ukuran baru       : ";
        getline(cin, ptrPesanan->detail.ukuran);

        cout << "Masukkan Harga baru (Rp)   : ";
        if (!(cin >> ptrPesanan->harga)) {
            throw invalid_argument("Harga harus berupa angka murni!");
        }
        cin.ignore(256, '\n');

        if (ptrPesanan->harga < 0) {
            throw logic_error("Harga tidak mungkin negatif!");
        }
        
        cout << "Pesanan berhasil diubah.\n";

    } catch (const exception& e) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n[ERROR] " << e.what() << " Perubahan dibatalkan.\n";
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

int main() {
    User users[MAX_USERS];
    int userCount = 0;
    Pesanan pesanan[MAX_PESANAN];
    int panjangPesanan = 0; 
    string papanInfo[MAX_INFO];
    int infoCount = 0;
    User currentUser; 

    users[0].username = "NurFitriRamadhani"; 
    users[0].password = "2509106089";
    users[0].role = "admin";
    userCount++;

    int menuAwal;
    bool isProgramRunning = true;
    
    while (isProgramRunning) {
        try {
            system("cls");
            cout << "\n==============================\n";
            cout << " SISTEM KOMISI LUKISAN\n";
            cout << "==============================\n";
            cout << "1. Register (Pengguna Baru)\n";
            cout << "2. Login\n";
            cout << "3. Keluar\n";
            cout << "Pilihan: ";

            if (!(cin >> menuAwal)) {
                throw invalid_argument("Masukkan angka 1, 2, atau 3 saja!");
            }
            cin.ignore(256, '\n');

            switch (menuAwal) {
                case 1: 
                    registerUser(users, userCount);
                    cout << "\nTekan Enter untuk kembali...";
                    cin.get();
                    break;
                
                case 2: 
                    if (userCount == 0) {
                        cout << "Belum ada akun yang terdaftar.\n";
                        cout << "\nTekan Enter untuk kembali...";
                        cin.get();
                    } else {
                        loginUser(users, userCount, currentUser); 
                        
                        if (currentUser.role == "admin") {
                            int pilihanAdmin;
                            do {
                                cout << "\n=== MENU ADMIN (" << currentUser.username << ") ===\n";
                                cout << "1. Tambah Informasi/Pengumuman\n";
                                cout << "2. Lihat Semua Pesanan Masuk\n";
                                cout << "3. Cari Pesanan Masuk\n";
                                cout << "4. Setujui Pesanan\n";
                                cout << "5. Batalkan Pesanan\n";
                                cout << "6. Logout\n";
                                cout << "Pilihan: ";
                                
                                try {
                                    if (!(cin >> pilihanAdmin)) {
                                        throw invalid_argument("Masukkan angka 1-6!");
                                    }
                                    cin.ignore(256, '\n');

                                    if(pilihanAdmin < 1 || pilihanAdmin > 6) {
                                        throw out_of_range("Pilihan tidak valid!");
                                    }

                                    switch(pilihanAdmin) {
                                        case 1: tambahInfoAdmin(papanInfo, &infoCount); break;
                                        case 2: {
                                            if (panjangPesanan == 0) {
                                                cout << "Belum ada pesanan masuk.\n";
                                            } else {
                                                int opsiSort = 0;
                                                do {
                                                    try {
                                                        cout << "\n--- OPSI TAMPILAN PESANAN ---\n";
                                                        cout << "1. Data Pesanan\n";
                                                        cout << "2. Urutkan berdasar Nama Pemesan (A-Z)\n";
                                                        cout << "3. Urutkan berdasar Harga Tertinggi (9-0)\n";
                                                        cout << "4. Urutkan berdasar Gaya Lukisan (A-Z)\n";
                                                        cout << "Pilih: ";
                                                        
                                                        if (!(cin >> opsiSort)) {
                                                            throw invalid_argument("Masukkan angka 1-4!");
                                                        }
                                                        cin.ignore(256, '\n');

                                                        if (opsiSort >= 1 && opsiSort <= 4) {
                                                            animasiLoading("Mengurutkan data");
                                                            if (opsiSort == 2) insertionSortNamaAsc(pesanan, panjangPesanan);
                                                            else if (opsiSort == 3) bubbleSortHargaDesc(pesanan, panjangPesanan);
                                                            else if (opsiSort == 4) selectionSortGayaAsc(pesanan, panjangPesanan);
                                                            
                                                            tampilkanPesanan(pesanan, panjangPesanan);
                                                            break;
                                                        } else {
                                                            throw out_of_range("Pilihan tidak valid!");
                                                        }
                                                    } catch(const exception& e) {
                                                        cin.clear();
                                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                                        cout << "\n[ERROR] " << e.what() << endl;
                                                        opsiSort = 0;
                                                    }
                                                } while (true);
                                            }
                                            break; 
                                        }
                                        case 3: {
                                            if (panjangPesanan == 0) {
                                                cout << "Belum ada pesanan masuk untuk dicari.\n";
                                            } else {
                                                int opsiCari = 0;
                                                do {
                                                    try {
                                                        cout << "\n--- CARI PESANAN ---\n";
                                                        cout << "1. Cari berdasarkan Nama Pemesan (Kata/Huruf)\n";
                                                        cout << "2. Cari berdasarkan Harga (Angka)\n";
                                                        cout << "Pilih: ";
                                                        
                                                        if (!(cin >> opsiCari)) {
                                                            throw invalid_argument("Masukkan angka 1 atau 2!");
                                                        }
                                                        cin.ignore(256, '\n');

                                                        if (opsiCari == 1) {
                                                            string targetNama;
                                                            cout << "Masukkan Nama Pemesan yang dicari: ";
                                                            getline(cin, targetNama);
                                                            animasiLoading("Mencari data");
                                                            binarySearchPemesan(pesanan, panjangPesanan, targetNama);
                                                            break;
                                                        } else if (opsiCari == 2) {
                                                            long targetHarga;
                                                            cout << "Masukkan nominal Harga yang dicari (Rp): ";
                                                            if (!(cin >> targetHarga)) {
                                                                throw invalid_argument("Input Harga harus berupa angka!");
                                                            }
                                                            cin.ignore(256, '\n');
                                                            animasiLoading("Mencari data");
                                                            linearSearchHarga(pesanan, panjangPesanan, targetHarga);
                                                            break;
                                                        } else {
                                                            throw out_of_range("Pilihan tidak valid!");
                                                        }
                                                    } catch(const exception& e) {
                                                        cin.clear();
                                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                                        cout << "\n[ERROR] " << e.what() << endl;
                                                        opsiCari = 0;
                                                    }
                                                } while (true);
                                            }
                                            break;
                                        }
                                        case 4: kelolaStatusPesanan(pesanan, panjangPesanan, "Disetujui Admin"); break;
                                        case 5: hapusPesanan(pesanan, panjangPesanan, currentUser.username, true); break;
                                        case 6: cout << "Logout berhasil.\n"; break;
                                    }
                                } catch(const exception& e) {
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    cout << "\n[ERROR ADMIN] " << e.what() << endl;
                                    pilihanAdmin = 0;
                                }
                            } while (pilihanAdmin != 6);
                        } 

                        else {
                            int pilihanUser;
                            do {
                                cout << "\n=== MENU PENGGUNA (" << currentUser.username << ") ===\n";
                                cout << "1. Buat Pesanan Lukisan\n";
                                cout << "2. Lihat Info & Pesanan\n";
                                cout << "3. Ubah Pesanan\n";
                                cout << "4. Batalkan Pesanan Sendiri\n";
                                cout << "5. Logout\n";
                                cout << "Pilihan: ";
                                
                                try {
                                    if (!(cin >> pilihanUser)) {
                                        throw invalid_argument("Masukkan angka 1-5!");
                                    }
                                    cin.ignore(256, '\n');

                                    if(pilihanUser < 1 || pilihanUser > 5) {
                                        throw out_of_range("Pilihan tidak valid!");
                                    }

                                    switch(pilihanUser) {
                                        case 1: buatPesananUser(pesanan, panjangPesanan, currentUser.username); break;
                                        case 2: {
                                            int subMenu = 0;
                                            do {
                                                try {
                                                    cout << "\n1. Liat papan info\n";
                                                    cout << "2. Lihat status pesananku\n";
                                                    cout << "Pilih: ";
                                                    
                                                    if (!(cin >> subMenu)) {
                                                        throw invalid_argument("Masukkan angka 1 atau 2!");
                                                    }
                                                    cin.ignore(256, '\n');

                                                    if (subMenu == 1) {
                                                        bacaPapanInfo(papanInfo, infoCount);
                                                        break;
                                                    } else if (subMenu == 2) {
                                                        tampilkanPesanan(pesanan, panjangPesanan, currentUser.username); 
                                                        long total = hitungTotalBelanjaRekursif(pesanan, panjangPesanan - 1, currentUser.username);
                                                        cout << ">> Estimasi Total Belanja Anda: Rp " << total << endl;
                                                        break;
                                                    } else {
                                                        throw out_of_range("Pilihan tidak valid!");
                                                    }
                                                } catch(const exception& e) {
                                                    cin.clear();
                                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                                    cout << "\n[ERROR] " << e.what() << endl;
                                                    subMenu = 0;
                                                }
                                            } while (true);
                                            break;
                                        }
                                        case 3: ubahPesananUser(pesanan, panjangPesanan, currentUser.username); break;
                                        case 4: hapusPesanan(pesanan, panjangPesanan, currentUser.username, false); break;
                                        case 5: cout << "Logout berhasil.\n"; break;
                                    }
                                } catch(const exception& e) {
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    cout << "\n[ERROR USER] " << e.what() << endl;
                                    pilihanUser = 0;
                                }
                            } while (pilihanUser != 5);
                        }
                    }
                    break;
                case 3:
                    cout << "Program selesai. Sampai jumpa!\n";
                    isProgramRunning = false;
                    break;
            }
        } 
        catch (const exception& e) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            
            if(string(e.what()) == "Gagal login terlalu banyak. Program dihentikan demi keamanan.") {
                cout << "\n[CRITICAL ERROR] " << e.what() << "\n";
                isProgramRunning = false;
            } else {
                cout << "\n[ERROR] " << e.what() << "\n";
                cout << "Silakan tekan Enter untuk mengulang...";
                cin.get();
            }
        }

    } 

    return 0;
}