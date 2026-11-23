
#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

// Bobot penilaian
const double W_HADIR = 0.10;
const double W_TUGAS = 0.45;
const double W_UTS = 0.25;
const double W_UAS = 0.20;

// Deklarasi fungsi
int inputJumlah();
string inputNama();
double inputNilai(const string& keterangan);
void inputMahasiswa(string& nama, string& npm,
                    double& hadir, double& tugas,
                    double& uts, double& uas);

double kalkulasiNilai(double hadir, double tugas,
                      double uts, double uas);

string tentukanGrade(double nilai);
void tampilkanHasil(string nama, double nilai,
                    string grade, bool status);

void hitungGrade(char grade, int& a, int& b,
                 int& c, int& d, int& e);

void tampilkanStatistik(int a, int b, int c,
                        int d, int e);

int main() {
    cout << "=== SiNilai v0.7 ===\n";

    int totalMahasiswa = inputJumlah();

    cout << fixed << setprecision(2);

    double akumulasiNilai = 0;
    double nilaiMaksimum = -1;
    string mahasiswaTerbaik;

    int totalLulus = 0;

    int gradeA = 0;
    int gradeB = 0;
    int gradeC = 0;
    int gradeD = 0;
    int gradeE = 0;

    for (int urutan = 0; urutan < totalMahasiswa; urutan++) {
        string nama, npm;
        double hadir, tugas, uts, uas;

        cout << "\n--- Mahasiswa ke-" << urutan + 1
             << " dari " << totalMahasiswa << " ---\n";

        inputMahasiswa(nama, npm, hadir, tugas, uts, uas);

        double hasil = kalkulasiNilai(hadir, tugas, uts, uas);
        string grade = tentukanGrade(hasil);

        bool status = (hasil >= 60);

        tampilkanHasil(nama, hasil, grade, status);

        akumulasiNilai += hasil;

        if (status == true) {
            totalLulus++;
        }

        hitungGrade(grade[0], gradeA, gradeB,
                    gradeC, gradeD, gradeE);

        if (hasil > nilaiMaksimum) {
            nilaiMaksimum = hasil;
            mahasiswaTerbaik = nama;
        }
    }

    cout << "\n=== Laporan Kelas ===\n";
    cout << "Jumlah mahasiswa : " << totalMahasiswa << "\n";
    cout << "Lulus            : " << totalLulus << "\n";
    cout << "Belum lulus      : "
         << totalMahasiswa - totalLulus << "\n";

    cout << "Rata-rata kelas  : "
         << akumulasiNilai / totalMahasiswa << "\n";

    cout << "Tertinggi        : "
         << mahasiswaTerbaik << " (" << nilaiMaksimum << ")\n";

    tampilkanStatistik(gradeA, gradeB, gradeC, gradeD, gradeE);

    return 0;
}

// Input jumlah mahasiswa
int inputJumlah() {
    int banyak;

    cout << "Jumlah mahasiswa (paling sedikit 1): ";
    cin >> banyak;

    while (cin.fail() || banyak < 1) {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Harus bilangan bulat paling sedikit 1. Coba lagi: ";
        cin >> banyak;
    }

    cin.ignore(1000, '\n');

    return banyak;
}

// Input dan pengolahan nama
string inputNama() {
    string nama;

    do {
        cout << "Nama mahasiswa: ";
        getline(cin, nama);

        if (nama.empty()) {
            cout << "Nama tidak boleh kosong.\n";
        }
    } while (nama.empty());

    bool kapital = true;

    for (int i = 0; i < (int)nama.size(); i++) {
        unsigned char karakter = static_cast<unsigned char>(nama[i]);

        if (isspace(karakter)) {
            kapital = true;
        } else {
            if (kapital) {
                nama[i] = toupper(karakter);
                kapital = false;
            } else {
                nama[i] = tolower(karakter);
            }
        }
    }

    return nama;
}

// Input nilai komponen
double inputNilai(const string& keterangan) {
    double nilai;

    cout << keterangan << ": ";
    cin >> nilai;

    while (cin.fail() || nilai < 0 || nilai > 100) {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Harus angka 0 sampai 100. "
             << keterangan << ": ";

        cin >> nilai;
    }

    return nilai;
}

// Mengambil seluruh data mahasiswa
void inputMahasiswa(string& nama, string& npm,
                    double& hadir, double& tugas,
                    double& uts, double& uas) {

    nama = inputNama();

    cout << "NPM: ";
    getline(cin, npm);

    hadir = inputNilai("Kehadiran ");
    tugas = inputNilai("Mingguan  ");
    uts = inputNilai("UTS       ");
    uas = inputNilai("UAS       ");

    cin.ignore(1000, '\n');
}

// Menghitung nilai akhir
double kalkulasiNilai(double hadir, double tugas,
                      double uts, double uas) {

    double hasil = 0;

    hasil += hadir * W_HADIR;
    hasil += tugas * W_TUGAS;
    hasil += uts * W_UTS;
    hasil += uas * W_UAS;

    return hasil;
}

// Menentukan huruf mutu
string tentukanGrade(double nilai) {
    if (nilai < 60) return "E";
    if (nilai < 65) return "D";
    if (nilai < 70) return "C";
    if (nilai < 75) return "C+";
    if (nilai < 80) return "B";
    if (nilai < 85) return "B+";

    return "A";
}

// Menampilkan nilai mahasiswa
void tampilkanHasil(string nama, double nilai,
                    string grade, bool status) {

    cout << "  " << left << setw(20) << nama
         << right << setw(7) << nilai
         << "  " << left << setw(3) << grade;

    cout << (status ? "Lulus\n" : "Belum lulus\n");
}

// Menghitung jumlah setiap huruf mutu
void hitungGrade(char grade, int& a, int& b,
                 int& c, int& d, int& e) {

    if (grade == 'A') {
        ++a;
    } else if (grade == 'B') {
        ++b;
    } else if (grade == 'C') {
        ++c;
    } else if (grade == 'D') {
        ++d;
    } else {
        ++e;
    }
}

// Menampilkan grafik sebaran nilai
void tampilkanStatistik(int a, int b, int c,
                        int d, int e) {

    int dataGrade[5] = {a, b, c, d, e};
    char labelGrade[5] = {'A', 'B', 'C', 'D', 'E'};

    cout << "\nSebaran huruf mutu:\n";

    for (int i = 0; i < 5; i++) {
        cout << labelGrade[i] << " : ";

        int jumlahBintang = dataGrade[i];

        while (jumlahBintang > 0) {
            cout << "*";
            jumlahBintang--;
        }

        cout << " (" << dataGrade[i] << ")\n";
    }
}
