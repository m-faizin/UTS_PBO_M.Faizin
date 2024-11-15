#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Kelas Buku
class Buku{
protected:          // Atribut dari kelas Buku menggunakan access protected
    string judul;
    string pengarang;
    int tahunTerbit;
    string ISBN;
    bool status;    // true jika buku tersedia, false jika buku dipinjam
// Constructor dari kelas Buku
public:
    Buku(string judul, string pengarang, int tahunTerbit, string ISBN)
        : judul(judul), pengarang(pengarang), tahunTerbit(tahunTerbit), ISBN(ISBN), status(true){} // Initializer list
    // Method untuk menampilkan informasi buku
    void tampilkanInfoBuku(){
        cout << "Judul: " << judul << endl;
        cout << "Pengarang: " << pengarang << endl;
        cout << "Tahun Terbit: " << tahunTerbit << endl;
        cout << "ISBN: " << ISBN << endl;
        cout << "Status: " << (status ? "Tersedia" : "Dipinjam") << endl;   // Operator ternary
        cout << "------------------------------------------------------" << endl;
    }
    // Method untuk mendapatkan nilai atribut status
    bool statusTersedia(){
        return status;
    }
    // Method untuk menetapkan nilai atribut status
    void setStatus(bool s){
        status = s;
    }
    // Method untuk mendapatkan data judul buku
    string getJudul(){
        return judul;
    }
};

// Kelas Buku Digital, kelas turunan dari kelas Buku
class BukuDigital : public Buku{
private:        // Atribut dari kelas Buku Digital menggunakan access private
    string kategori;
// Constructor dari kelas Buku Digital
public:
    BukuDigital(string judul, string pengarang, int tahunTerbit, string ISBN, string kategori)
        : Buku(judul, pengarang, tahunTerbit, ISBN), kategori(kategori){}    // Initializer list
    // Method untuk menampilkan informasi buku
    void tampilkanInfoBuku(){
        Buku::tampilkanInfoBuku();    // Memanggil method dari kelas Buku/super class
        cout << "Kategori: " << kategori << endl;
    }
};
// Kelas Anggota
class Anggota{
private:        // Atribut dari kelas Anggota menggunakan access private
    string nama;
    int nomorAnggota;
    string alamat;
    vector<Buku*> daftarPinjaman;   // Vector untuk menyimpan objek daftar pinjaman
// Constructor dari kelas Anggota
public:
    Anggota(string nama, int nomorAnggota, string alamat)
        : nama(nama), nomorAnggota(nomorAnggota), alamat(alamat){}  // Initializer list
    // Method untuk menampilkan informasi Anggota
    void tampilkanInfoAnggota(){
        cout << "\n    Informasi Anggota Perpustakaan" << endl;
        cout << "======================================" << endl;
        cout << endl;
        cout << "Nama: " << nama << endl;
        cout << "Nomor Anggota: " << nomorAnggota << endl;
        cout << "Alamat: " << alamat << endl;
        cout << "Buku yang dipinjam:" << endl;
        for (Buku* buku : daftarPinjaman){              // Melakukan looping untuk menampilkan daftar pinjaman
            cout << "- " << buku->getJudul() << endl;   // Mengakses method menggunakan -> karena menggunakan pointer
        }
        cout << "\n" << endl;
    }
    // Method untuk mendapatkan nilai atribut nomor anggota
    int getNomorAnggota(){
        return nomorAnggota;
    }
    // Method untuk menentukan buku yang ingin dipinjam dan menyimpan alamat dari buku yang dipinjam oleh anggota
    void pinjamBuku(Buku* buku){
        daftarPinjaman.push_back(buku);     // Menyimpan alamat dari buku yang dipinjam ke dalam objek daftar pinjaman
    }
    // Method untuk menghapus buku yang dipinjam oleh anggota dari daftar pinjaman anggota
    void kembalikanBuku(Buku* buku){
        for (auto it = daftarPinjaman.begin(); it != daftarPinjaman.end(); ++it){   // it = iterator, begin() mengembalikan iterator ke
            if (*it == buku){               // elemen pertama dalam daftarPinjaman, end() menunjukkan satu posisi setelah elemen terakhir
                daftarPinjaman.erase(it);   // Menghapus elemen di posisi (it) dari objek daftar pinjaman
                break;
            }
        }
    }
    // Method untuk memeriksa apakah anggota memiliki buku tertentu di dalam daftar pinjaman anggota tersebut
    bool memilikiBuku(Buku* buku){
        for (Buku* b : daftarPinjaman){     // Menelusuri alamat buku di dalam daftar pinjaman
            if (b == buku) return true;     // Jika buku ditemukan, maka akan mengembalikan nilai true,
        }                                   // jika tidak, maka akan mengembalikan nilai false
        return false;
    }
};

// Kelas Perpustakaan
class Perpustakaan{
private:        // Atribut dari kelas Perpustakaan menggunakan access private
    vector<Buku*> daftarBuku;       // Vector untuk menyimpan objek buku
    vector<Anggota> daftarAnggota;  // Vector untuk menyimpan objek anggota
public:
    // Method untuk menambahkan alamat objek buku ke dalam daftar buku di perpustakaan
    void tambahBuku(Buku* buku){
        daftarBuku.push_back(buku);
    }
    // Method untuk menambahkan alamat objek anggota ke dalam daftar anggota di perpustakaan
    void tambahAnggota(const Anggota& anggota){
        daftarAnggota.push_back(anggota);
    }
    // Method untuk menampilkan daftar buku di perpustakaan yang tersedia/tidak sedang dipinjam
    void daftarBukuTersedia(){
        cout << endl;
        for (Buku* buku : daftarBuku){      // Menelusuri alamat buku di dalam daftar buku
            if (buku->statusTersedia()){    // Jika buku yang sedang ditelusuri statusnya tersedia maka
                buku->tampilkanInfoBuku();  // Memanggil method untuk menampilkan info buku
                cout << endl;
            }
        }
    }
    // Method untuk meminjamkan buku kepada anggota perpustakaan tertentu
    void pinjamBuku(int nomorAnggota, string judulBuku){
        Anggota* anggota = nullptr;  // Mendaklarasikan pointer dan diset nullptr (kosong)
        Buku* buku = nullptr;

        for (auto& a : daftarAnggota){      // Menelusuri setiap anggota di daftar anggota
            if (a.getNomorAnggota() == nomorAnggota){   // Jika ditemukan anggota dengan nomor anggota yang cocok, maka
                anggota = &a;                           // pointer anggota akan diisi dengan alamat anggota tersebut
                break;
            }
        }

        for (Buku* b : daftarBuku){         // Menelusuri setiap buku di daftar buku
            if (b->getJudul() == judulBuku && b->statusTersedia()){  // Memeriksa apakah buku cocok dengan judul buku dan
                buku = b;                                            // memeriksa apakah buku tersedia, jika kedua kondisi
                break;                                               // terpenuhi, buku diisi dengan pointer ke buku yang cocok
            }
        }

        if (anggota && buku){               // Jika anggota dan buku ditemukan/cocok, status buku diubah menjadi "dipinjam"
            buku->setStatus(false);
            anggota->pinjamBuku(buku);      // Menambahkan buku ke daftar pinjaman anggota tersebut
            cout << "Buku \"" << judulBuku << "\" berhasil dipinjam oleh anggota " << nomorAnggota << "." << endl;
        } else {
            cout << "Buku atau anggota tidak ditemukan atau buku sudah dipinjam." << endl;
        }
    }
    // Method untuk mengembalikan buku dari anggota ke perpustakaan
    void kembalikanBuku(int nomorAnggota, string judulBuku){
        Anggota* anggota = nullptr;        // Mendaklarasikan pointer dan diset nullptr (kosong)
        Buku* buku = nullptr;

        for (auto& a : daftarAnggota){
            if (a.getNomorAnggota() == nomorAnggota){
                anggota = &a;
                break;
            }
        }

        for (Buku* b : daftarBuku){
            if (b->getJudul() == judulBuku && !b->statusTersedia()){  // Memeriksa apakah buku cocok dengan judul buku dan
                buku = b;                                             // memeriksa apakah buku tidak tersedia, jika kedua kondisi
                break;                                                // terpenuhi, buku diisi dengan pointer ke buku yang cocok
            }
        }

        if (anggota && buku && anggota->memilikiBuku(buku)){  // Jika anggota dan buku ditemukan/cocok dan buku terdapat pada daftar
            buku->setStatus(true);                            // pinjaman anggota, maka status buku diubah menjadi "tersedia"
            anggota->kembalikanBuku(buku);                    // Menghapus buku dari daftar pinjaman anggota tersebut
            cout << "Buku \"" << judulBuku << "\" berhasil dikembalikan oleh anggota " << nomorAnggota << "." << endl;
        } else {
            cout << "Buku atau anggota tidak ditemukan atau buku tidak dipinjam." << endl;
        }
    }
    // Method untuk menampilkan informasi anggota
    void tampilkanInfoAnggota(int nomorAnggota){
        for (Anggota& a : daftarAnggota) {
            if (a.getNomorAnggota() == nomorAnggota){
                a.tampilkanInfoAnggota();
                return;
            }
        }
        cout << "Anggota dengan nomor " << nomorAnggota << " tidak ditemukan." << endl;
    }
    // Method untuk menampilkan main menu
    void tampilkanMenu(){
    cout << "\n    Menu Perpustakaan" << endl;
    cout << "=========================" << endl;
    cout << "1. Daftar Buku Tersedia" << endl;
    cout << "2. Tampilkan Info Anggota" << endl;
    cout << "3. Pinjam Buku" << endl;
    cout << "4. Kembalikan Buku" << endl;
    cout << "5. Tambah Buku Baru" << endl;
    cout << "6. Tambah Anggota Baru" << endl;
    cout << "0. Keluar" << endl;
    cout << "=========================" << endl;
    cout << "Pilih opsi: ";
    }
};

// Fungsi utama
int main(){
    // Instansiasi kelas Perpustakaan
    Perpustakaan perpustakaan;
    int pilihan;              // Membuat variabel pilihan untuk menyimpan input pilihan dari user di main menu
    // Instansiasi kelas Buku
    perpustakaan.tambahBuku(new Buku("Filosofi Teras", "Henry Manampiring", 2018, "978-6-02412-518-9"));
    perpustakaan.tambahBuku(new Buku("History of Western Philosophy", "Bertrand Russell", 1946, "0-415-32505-6"));
    perpustakaan.tambahBuku(new Buku("The 48 Laws of Power", "Robert Greene", 1998, "0670881465"));
    perpustakaan.tambahBuku(new BukuDigital("Atomic Habits: Tiny Changes, Remarkable Result", "James Clear", 2018,
                                             "9780735211292", "Pengembangan diri"));
    // Instansiasi kelas Anggota
    perpustakaan.tambahAnggota(Anggota("Faizin", 1, "Jl. Ciujung"));
    perpustakaan.tambahAnggota(Anggota("Kodir", 2, "Jl. Bundaran"));
    perpustakaan.tambahAnggota(Anggota("Riki", 3, "Jl. Industri"));
    perpustakaan.tambahAnggota(Anggota("Deri", 4, "Jl. Merpati"));
    do{     // Melakukan looping untuk menampilkan main menu
        perpustakaan.tampilkanMenu();   // Memanggil method untuk menampilkan main menu
        cin >> pilihan;                 // Mengambil input pilihan user
        cin.ignore();                   // Mengabaikan newline setelah input angka
        // Menggunakan switch case untuk menyeleksi pilihan user mengakses fungsi-fungsi aplikasi
        switch (pilihan){
            case 1:{
                // Daftar Buku Tersedia
                system("cls");      // Membersihkan console
                cout << "\n    Daftar Buku Tersedia" << endl;
                cout << "============================" << endl;
                perpustakaan.daftarBukuTersedia();
                break;
            }
            case 2:{
                // Tampilkan Info Anggota
                system("cls");
                int nomorAnggota;
                cout << "\n    Informasi Anggota" << endl;
                cout << "=========================" << endl;
                cout << "\nNomor Anggota: ";
                cin >> nomorAnggota;
                cin.ignore();
                system("cls");
                perpustakaan.tampilkanInfoAnggota(nomorAnggota);
                break;
            }
            case 3:{
                // Pinjam Buku
                system("cls");
                int nomorAnggota;
                string judulBuku;
                cout << "\n    Pinjam Buku" << endl;
                cout << "===================" << endl;
                cout << "\nNomor Anggota: ";
                cin >> nomorAnggota;
                cin.ignore();
                cout << "Judul Buku: ";
                getline(cin, judulBuku);
                cout << endl;

                perpustakaan.pinjamBuku(nomorAnggota, judulBuku);
                cout << "\n" << endl;
                break;
            }
            case 4:{
                // Kembalikan Buku
                system("cls");
                int nomorAnggota;
                string judulBuku;
                cout << "\n    Kembalikan Buku" << endl;
                cout << "=======================" << endl;
                cout << "\nNomor Anggota: ";
                cin >> nomorAnggota;
                cin.ignore();
                cout << "Judul Buku: ";
                getline(cin, judulBuku);
                cout << endl;

                perpustakaan.kembalikanBuku(nomorAnggota, judulBuku);
                cout << "\n" << endl;
                break;
            }
            case 5:{
                // Tambah Buku Baru
                system("cls");
                string judul, pengarang, ISBN;
                int tahunTerbit;
                cout << "\n    Tambah Buku Baru" << endl;
                cout << "========================" << endl;
                cout << "\nJudul: ";
                getline(cin, judul);
                cout << "Pengarang: ";
                getline(cin, pengarang);
                cout << "Tahun Terbit: ";
                cin >> tahunTerbit;
                cin.ignore();
                cout << "ISBN: ";
                getline(cin, ISBN);
                perpustakaan.tambahBuku(new Buku(judul, pengarang, tahunTerbit, ISBN));
                cout << "\nBuku berhasil ditambahkan!" << endl;
                cout << "\n" << endl;
                break;
            }
            case 6:{
                // Tambah Anggota Baru
                system("cls");
                string nama, alamat;
                int nomorAnggota;
                cout << "\n    Tambah Anggota Baru" << endl;
                cout << "===========================" << endl;
                cout << "\nNama: ";
                getline(cin, nama);
                cout << "Nomor Anggota: ";
                cin >> nomorAnggota;
                cin.ignore();
                cout << "Alamat: ";
                getline(cin, alamat);
                perpustakaan.tambahAnggota(Anggota(nama, nomorAnggota, alamat));
                cout << "\nAnggota berhasil ditambahkan!" << endl;
                cout << "\n" << endl;
                break;
            }
            case 0:{    // Program berhenti ketika memilih opsi 0 pada main menu
                system("cls");
                cout << "Terima kasih telah menggunakan aplikasi perpustakaan!" << endl;
                break;
            }
            default:
                system("cls");
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilihan != 0);    // Looping dilakukan selama pilihan user tidak sama dengan 0
    return 0;
}
