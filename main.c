#include "main.h"

int main(void)
{
    int jumlahBuku = hitungBaris("db.txt");
    Buku *daftarBuku = malloc(jumlahBuku * sizeof(Buku));
    Buku *daftarBukuUnsorted = malloc(jumlahBuku * sizeof(Buku));

    if (daftarBuku == NULL)
    {
        fprintf(stderr, "Telah terjadi kesalahan!");
    }

    loadDatabase("db.txt", daftarBuku, jumlahBuku);
    loadDatabase("db.txt", daftarBukuUnsorted, jumlahBuku);
    sort(daftarBuku, jumlahBuku);

    int jumlahRiwayat = hitungBaris("history.txt");
    Riwayat *daftarRiwayat = malloc(jumlahRiwayat * sizeof(Riwayat));

    if (daftarRiwayat == NULL)
    {
        fprintf(stderr, "Telah terjadi kesalahan!");
    }

    loadRiwayat("history.txt", daftarRiwayat, jumlahRiwayat);

    int input;
    do
    {
        system("clear");
        printf("-----------------------------------\n");
        printf("|            BIBAUGUST            |\n");
        printf("|                                 |\n");
        printf("| 1. Cari buku                    |\n");
        printf("| 2. Pinjam buku                  |\n");
        printf("| 3. Kembalikan buku              |\n");
        printf("| 4. Tambah buku                  |\n");
        printf("| 5. Hapus buku                   |\n");
        printf("| 6. Riwayat peminjaman           |\n");
        printf("| 7. Daftar buku                  |\n");
        printf("| 8. Exit                         |\n");
        printf("-----------------------------------\n");
        printf("Masukkan angka dari menu: ");
        scanf("%i", &input);
        getchar();

        switch(input)
        {
            case 1:
                system("clear");
                cariBuku(daftarBuku, jumlahBuku);
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                system("clear");
                tambahBuku(&daftarBuku, &jumlahBuku);
                break;
            case 5:
                system("clear");
                hapusBuku(&daftarBukuUnsorted, &jumlahBuku);
                break;
            case 6:
                system("clear");
                lihatRiwayat(daftarRiwayat, jumlahRiwayat);
                break;
            case 7:
                system("clear");
                lihatDatabase(daftarBuku, jumlahBuku);
                break;
            case 8:
                break;
            default:
                printf("Maaf, angka %i bukan pilihan valid\n", input);
        }
    }
    while (input != 7);

    free(daftarBuku);
    free(daftarRiwayat);
}
