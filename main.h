#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Buku
{
    char judul[128];
    int tahunTerbit;
    char penulis[64];
    int halaman;
    double berat;
    long long int isbn;
    float rating;
    bool dipinjam;
}
Buku;

typedef struct Riwayat
{
    char tanggal[32];
    char judul[128];
    char peminjam[64];
}
Riwayat;

// tools.c
void hapusBuku(Buku **daftarBuku, int *jumlahBuku);
void tambahBuku(Buku **daftarBuku, int *jumlahBuku);
void lihatRiwayat(Riwayat *daftarRiwayat, int jumlahRiwayat);
void cariBuku(Buku *daftarBuku, int jumlahBuku);
void lihatDatabase(Buku *daftarBuku, int jumlahBuku);

// load.c
int hitungBaris(char *filename);
int binarySearch(Buku *daftarBuku, char *keyword, int min, int max);
void loadDatabase(char *filename, Buku daftarBuku[], int n);
void loadRiwayat(char *filename, Riwayat daftarRiwayat[], int n);
void updateDatabase(char *filename, Buku **daftarBuku, int *jumlahBuku);
void updateRiwayat(char *filename, Riwayat **daftarRiwayat, int *jumlahRiwayat);

// sort.c
void merge(Buku daftarBuku[], int left, int mid, int right);
void split(Buku daftarBuku[], int left, int right);
void sort(Buku daftarBuku[], int n);