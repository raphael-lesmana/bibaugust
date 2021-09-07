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
        return;
    }
    FILE *dbFile = fopen("db.txt", "r");
    FILE *tmpFile = fopen("tmp", "w");
    int i = 0;
    char buffer[256];

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

    updateDatabase("db.txt", daftarBuku, jumlahBuku);
    printf("Buku berhasil dihapus\n");
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
}

void lihatRiwayat(Riwayat *daftarRiwayat, int jumlahRiwayat)
{
    for (int i = 0; i < jumlahRiwayat; i++)
    {
        printf("Tanggal: %s\n", daftarRiwayat[i].tanggal);
        printf("Judul: %s\n", daftarRiwayat[i].judul);
        printf("Peminjam: %s\n\n", daftarRiwayat[i].peminjam);
    }
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
    	printf("Jumlah Halaman%d\n", daftarBuku[n].halaman);
    	printf("Berat Buku: %lf\n", daftarBuku[n].berat);
    	printf("ISBN: %lld\n", daftarBuku[n].isbn);
    	printf("Rating: %f\n", daftarBuku[n].rating);
    	printf("Dipinjam? %s\n", (daftarBuku[n].dipinjam) ? "Iya" : "Tidak");
    }
    else
    {
        printf("Buku tidak ditemukan!\n");
    }
}

void lihatDatabase(Buku *daftarBuku, int jumlahBuku)
{
    for(int i=0; i<jumlahBuku; i++)
    {
    	printf("%s\n", daftarBuku[i].judul);
    	printf("%d\n", daftarBuku[i].tahunTerbit);
    	printf("%s\n", daftarBuku[i].penulis);
    	printf("%d\n", daftarBuku[i].halaman);
    	printf("%lf\n", daftarBuku[i].berat);
    	printf("%lld\n", daftarBuku[i].isbn);
    	printf("%f\n", daftarBuku[i].rating);
    	printf("%d\n", daftarBuku[i].dipinjam);
    }
}

