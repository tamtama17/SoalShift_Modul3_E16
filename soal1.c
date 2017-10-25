#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

char *weapons[] = {
    "MP4A1",
    "PM2-V1",
    "SPR-3",
    "SS2-V5",
    "SPG1-V3",
    "MINE"
};

void setSHM (key_t key, int value) {
    int shmid = shmget (key, sizeof (int), IPC_CREAT | 0666);
    int *shmvalue = shmat (shmid, NULL, 0);
    *shmvalue = value;
}

int getSHM (key_t key) {
    int shmid = shmget (key, sizeof (int), IPC_CREAT | 0666);
    int *value = shmat (shmid, NULL, 0);
    return *value;
}

void lihatStok (int showEmpty) {
    system ("clear");
    for (int i = 0; i < 6; i++) {
        int count = getSHM (i + 6660);
        if (count > 0 || showEmpty)
            printf ("%s %d\n", weapons[i], count);
    }
    printf ("\n");
}

void tambahStok () {
    printf ("Format: [nama_barang] [jumlah_barang]");
    printf ("> ");

    char weapon[22];
    int count;

    scanf ("%s %d", weapon, &count);
    system ("clear");
    for (int i = 0; i < 6; i++) {
        if (!strcmp (weapon, weapons[i])) {
            setSHM (i + 6660, getSHM (i+6660) + count);
            return;
        }
    }

    printf ("Jangan becanda mas! barang tidak ada di stock!\n\n");
}

void beliSenjata () {
    printf ("Format: [nama_barang] [jumlah_barang]");
    printf ("> ");
    
    char weapon[22];
    int count;

    scanf ("%s %d", weapon, &count);
    system ("clear");

    for (int i = 0; i < 6; i++) {
        if (!strcmp (weapon, weapons[i])) {
            int stock = getSHM (i+6660);
            if (stock - count < 0)
                printf ("barang di stock tidak cukup!\n\n");
            else {
                setSHM (i + 6660, getSHM (i+6660) - count);
                printf ("success!\n\n");
            }
            return;
        }
    }

    printf ("Jangan becanda mas! barang tidak ada di stock!\n\n");
}

void penjual () {
    int choice = 0;
    while (1) {
        printf ("Menu\n");
        printf ("1. Lihat Stok\n");
        printf ("2. Tambah Stok\n");
        printf ("Pilihan: ");
        scanf ("%d", &choice);

        if (choice == 1) lihatStok (0);
        else if (choice == 2) tambahStok ();
    }
}

void pembeli () {
    int choice = 0;
    while (1) {
        printf ("Menu\n");
        printf ("1. Liat liat\n");
        printf ("2. Beli Senjata\n");
        printf ("Pilihan: ");
        scanf ("%d", &choice);

        if (choice == 1) lihatStok (1);
        else if (choice == 2) beliSenjata ();
    }
}

void main (int argc, char **argv) {
    key_t key = 666;
    int *value;

    int mode;
    printf ("Mode\n");
    printf ("1. Penjual\n");
    printf ("2. Pembeli\n");
    printf ("Pilihan: ");
    scanf ("%d", &mode);
    system ("clear");

    if (mode == 1) penjual ();
    else if (choice == 2) pembeli ();
    return 0;
}