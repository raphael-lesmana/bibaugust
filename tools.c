#include "main.h"

void hapusBuku(Buku **daftarBuku, int *jumlahBuku)
{
    int indexHapus = 0;
    char judul[128];
    printf("Masukkan nama buku yang ingin dihapus: ");
    scanf("%[^\n]", judul);
    getchar();

    if ((indexHapus = binarySearch(*daftarBuku, judul, 0, *jumlahBuku - 1)) == -1)
    {
        printf("Buku tidak ditemukan!\n");
        printf("Tekan tombol apa saja untuk kembali ke menu\n");
        getchar();
    }
    FILE *dbFile = fopen("db.txt", "r");
    FILE *tmpFile = fopen("tmp", "w");
    int i = 0;
    char buffer[512];

    while (fscanf(dbFile, "%[^\n]\n", buffer) != EOF)
    {
        if (i == indexHapus)
        {
            i++;
            continue;
        }
        fprintf(tmpFile, "%s\n", buffer);
        i++;
    }

    fclose(dbFile);
    fclose(tmpFile);

    dbFile = fopen("db.txt", "w");
    tmpFile = fopen("tmp", "r");

    while (fscanf(tmpFile, "%[^\n]\n", buffer) != EOF)
    {
        fprintf(dbFile, "%s\n", buffer);
    }

    fclose(dbFile);
    fclose(tmpFile);
    remove("tmp");

    updateDatabase("db.txt", daftarBuku, jumlahBuku);
    printf("Buku berhasil dihapus\n");
    printf("Tekan tombol apa saja untuk kembali ke menu\n");
    getchar();
}

void tambahBuku(Buku **daftarBuku, int *jumlahBuku)
{
    Buku bukuTambahan;

    printf("Masukkan data buku yang ingin Anda tambahkan ke dalam database!\n");
    printf("Judul Buku: ");
    scanf("%[^\n]", bukuTambahan.judul);
    getchar();
    printf("Tahun Terbit: ");
    scanf("%d", &bukuTambahan.tahunTerbit);
    getchar();
    printf("Nama Penulis: ");
    scanf("%[^\n]", bukuTambahan.penulis);
    getchar();
    printf("Jumlah Halaman: ");
    scanf("%d", &bukuTambahan.halaman);
    getchar();
    printf("Berat Buku: ");
    scanf("%lf", &bukuTambahan.berat);
    getchar();
    printf("ISBN: ");
    scanf("%lld", &bukuTambahan.isbn);
    getchar();
    printf("Rating Buku: ");
    scanf("%f", &bukuTambahan.rating);
    getchar();
    printf("Dipinjam (Masukkan 1 = True, 0 = False): ");
    scanf("%i", &bukuTambahan.dipinjam);
    getchar();

    // menambahkan input user ke dalam db.txt
    FILE *dbFile = fopen("db.txt", "a+");
    fprintf(dbFile, "%s#%d#%s#%d#%lf#%lld#%f#%i\n", bukuTambahan.judul,
            bukuTambahan.tahunTerbit, bukuTambahan.penulis,
            bukuTambahan.halaman, bukuTambahan.berat, bukuTambahan.isbn,
            bukuTambahan.rating, bukuTambahan.dipinjam);

    fclose(dbFile);
    // update array
    updateDatabase("db.txt", daftarBuku, jumlahBuku);

    printf("Buku Anda telah ditambahkan ke database kami!\n");
    printf("Tekan tombol apa saja untuk kembali ke menu\n");
    getchar();
}

void lihatRiwayat(Riwayat *daftarRiwayat, int jumlahRiwayat)
{
    for (int i = 0; i < jumlahRiwayat; i++)
    {

        printf("Tanggal: %s\n", daftarRiwayat[i].tanggal);
        printf("Judul: %s\n", daftarRiwayat[i].judul);
        printf("Peminjam: %s\n", daftarRiwayat[i].peminjam);
        printf("Keterangan: %s\n\n", (daftarRiwayat[i].keterangan == 'P') ? "Meminjam" : "Mengembalikan" );
    }
    printf("\nTekan tombol apa saja untuk kembali ke menu\n");
    getchar();
}

void cariBuku(Buku *daftarBuku, int jumlahBuku)
{
    char input[128];
    printf("Masukkan judul buku yang ingin dicari: ");
    scanf("%[^\n]", input );
    getchar();
    int n;
    n = binarySearch(daftarBuku, input, 0, jumlahBuku - 1);
    if (n != -1)
    {
        printf("Judul: %s\n", daftarBuku[n].judul);
    	printf("Tahun Terbit: %d\n", daftarBuku[n].tahunTerbit);
    	printf("Penulis: %s\n", daftarBuku[n].penulis);
    	printf("Jumlah Halaman: %d\n", daftarBuku[n].halaman);
    	printf("Berat Buku: %lf\n", daftarBuku[n].berat);
    	printf("ISBN: %lld\n", daftarBuku[n].isbn);
    	printf("Rating: %f\n", daftarBuku[n].rating);
    	printf("Dipinjam? %s\n\n", (daftarBuku[n].dipinjam) ? "Iya" : "Tidak");
        printf("Tekan tombol apa saja untuk kembali ke menu\n");
        getchar();
    }
    else
    {
        printf("Buku tidak ditemukan!\n");
        printf("Tekan tombol apa saja untuk kembali ke menu\n");
        getchar();
    }
}

void lihatDatabase(Buku *daftarBuku, int jumlahBuku)
{
    for(int i=0; i<jumlahBuku; i++)
    {
    	printf("Judul: %s\n", daftarBuku[i].judul);
    	printf("Tahun Terbit: %d\n", daftarBuku[i].tahunTerbit);
    	printf("Penulis: %s\n", daftarBuku[i].penulis);
    	printf("Jumlah Halaman: %d\n", daftarBuku[i].halaman);
    	printf("Berat Buku: %lf\n", daftarBuku[i].berat);
    	printf("ISBN: %lld\n", daftarBuku[i].isbn);
    	printf("Rating: %f\n", daftarBuku[i].rating);
    	printf("Dipinjam? %s\n", (daftarBuku[i].dipinjam) ? "Iya" : "Tidak");
    	printf("-----------------------------\n");
    }
    printf("\nTekan tombol apa saja untuk kembali ke menu\n");
    getchar();
}

void kembalikanBuku(Buku **daftarBuku, int *jumlahBuku, Riwayat **daftarRiwayat, int *jumlahRiwayat)
{
    int indexBuku = 0;
    char judul[128];

    printf("Masukkan nama buku yang ingin dikembalikan: ");
    scanf("%[^\n]", judul);
    getchar();

    if ((indexBuku = binarySearch(*daftarBuku, judul, 0, *jumlahBuku - 1)) == -1)
    {
        printf("Buku tidak ditemukan!\n");
        return;
    }


    if ((*daftarBuku)[indexBuku].dipinjam != 1)
    {
        printf("Buku tidak sedang dipinjam!\n");
        printf("Tekan tombol apa saja untuk kembali ke menu\n");
        getchar();
    }

    FILE *tmpFile = fopen("tmp", "w");

    for (int i = 0; i < *jumlahBuku; i++)
    {
        if (*jumlahBuku == indexBuku)
        {
            fprintf(tmpFile, "%s#%d#%s#%d#%lf#%lld#%f#0\n", (*daftarBuku)[i].judul,
                    (*daftarBuku)[i].tahunTerbit, (*daftarBuku)[i].penulis,
                    (*daftarBuku)[i].halaman, (*daftarBuku)[i].berat, (*daftarBuku)[i].isbn,
                    (*daftarBuku)[i].rating);
            continue;
        }
        fprintf(tmpFile, "%s#%d#%s#%d#%lf#%lld#%f#%i\n", (*daftarBuku)[i].judul,
                (*daftarBuku)[i].tahunTerbit, (*daftarBuku)[i].penulis,
                (*daftarBuku)[i].halaman, (*daftarBuku)[i].berat, (*daftarBuku)[i].isbn,
                (*daftarBuku)[i].rating, (*daftarBuku)[i].dipinjam);
    }

    fclose(tmpFile);
    tmpFile = fopen("tmp", "r");

    FILE *dbFile = fopen("db.txt", "w");
    char buffer[512];
    while (fscanf(tmpFile, "%[^\n]\n", buffer) != EOF)
    {
        fprintf(dbFile, "%s\n", buffer);
    }

    fclose(tmpFile);
    fclose(dbFile);
    remove("tmp");

    char peminjam[64];
    printf("Nama peminjam: ");
    scanf("%s", peminjam);
    getchar();

    time_t rawtime;
    struct tm *info;
    char date[80];

    time(&rawtime);

    info = localtime(&rawtime);

    strftime(date, 80, "%Y-%m-%d", info);

    FILE *histFile = fopen("history.txt", "a");
    fprintf(histFile, "%s#%s#%s#K\n", date, judul, peminjam);
    fclose(histFile);

    updateDatabase("db.txt", daftarBuku, jumlahBuku);
    updateRiwayat("history.txt", daftarRiwayat, jumlahRiwayat);

    printf("Buku telah dikembalikan!\n");
    printf("Tekan tombol apa saja untuk kembali ke menu\n");
    getchar();
}

void pinjamBuku(Buku **daftarBuku, int *jumlahBuku, Riwayat **daftarRiwayat, int *jumlahRiwayat)
{
    int indexBuku = 0;
    char judul[128];

    printf("Masukkan nama buku yang ingin dipinjam: ");
    scanf("%[^\n]", judul);
    getchar();

    if ((indexBuku = binarySearch(*daftarBuku, judul, 0, *jumlahBuku - 1)) == -1)
    {
        printf("Buku tidak ditemukan!\n");
        return;
    }


    if ((*daftarBuku)[indexBuku].dipinjam != 0)
    {
        printf("Buku sedang dipinjam!\n");
        printf("Tekan tombol apa saja untuk kembali ke menu\n");
        getchar();
    }

    FILE *tmpFile = fopen("tmp", "w");

    for (int i = 0; i < *jumlahBuku; i++)
    {
        if (*jumlahBuku == indexBuku)
        {
            fprintf(tmpFile, "%s#%d#%s#%d#%lf#%lld#%f#1\n", (*daftarBuku)[i].judul,
                    (*daftarBuku)[i].tahunTerbit, (*daftarBuku)[i].penulis,
                    (*daftarBuku)[i].halaman, (*daftarBuku)[i].berat, (*daftarBuku)[i].isbn,
                    (*daftarBuku)[i].rating);
            continue;
        }
        fprintf(tmpFile, "%s#%d#%s#%d#%lf#%lld#%f#%i\n", (*daftarBuku)[i].judul,
                (*daftarBuku)[i].tahunTerbit, (*daftarBuku)[i].penulis,
                (*daftarBuku)[i].halaman, (*daftarBuku)[i].berat, (*daftarBuku)[i].isbn,
                (*daftarBuku)[i].rating, (*daftarBuku)[i].dipinjam);
    }

    fclose(tmpFile);
    tmpFile = fopen("tmp", "r");

    FILE *dbFile = fopen("db.txt", "w");
    char buffer[512];
    while (fscanf(tmpFile, "%[^\n]\n", buffer) != EOF)
    {
        fprintf(dbFile, "%s\n", buffer);
    }

    fclose(tmpFile);
    fclose(dbFile);
    remove("tmp");

    char peminjam[64];
    printf("Nama peminjam: ");
    scanf("%s", peminjam);
    getchar();

    time_t rawtime;
    struct tm *info;
    char date[80];

    time(&rawtime);

    info = localtime(&rawtime);

    strftime(date, 80, "%Y-%m-%d", info);

    FILE *histFile = fopen("history.txt", "a");
    fprintf(histFile, "%s#%s#%s#P\n", date, judul, peminjam);
    fclose(histFile);

    updateDatabase("db.txt", daftarBuku, jumlahBuku);
    updateRiwayat("history.txt", daftarRiwayat, jumlahRiwayat);

    printf("Buku telah dipinjam!\n");
    printf("Tekan tombol apa saja untuk kembali ke menu\n");
    getchar();
}