#ifndef TAMPILAN_H
#define TAMPILAN_H

#include "data.h"

void cetakGaris(char kar, int panjang) {
    for (int i = 0; i < panjang; i++) {
        cout << kar;
    }
    cout << endl;
}

void cetakJudul(string teks) {
    cout << endl << CYAN;
    cetakGaris('=', 42);
    cout << " " << KUNING << TEBAL << teks << RESET << endl;
    cout << CYAN;
    cetakGaris('=', 42);
    cout << RESET << endl;
}

void tekanEnter() {
    cout << endl;
    system("pause");
}

int pilihMenu(string opsi[], int jumlahOpsi, string judul) {
    int posisi = 0;
    system("cls");

    cout << endl << CYAN;
    cetakGaris('=', 42);
    cout << " " << KUNING << TEBAL << judul << RESET << endl;
    cout << CYAN;
    cetakGaris('=', 42);
    cout << RESET << endl;

    int barisAwal = 6;

    for (int i = 0; i < jumlahOpsi; i++) {
        if (i == posisi) {
            cout << HIJAU << TEBAL << "  >> " << opsi[i] << "                   " << RESET << endl;
        } else {
            cout << "     " << opsi[i] << endl;
        }
    }

    cout << endl << CYAN;
    cetakGaris('-', 42);
    cout << KUNING << " panah atas/bawah + enter" << RESET << endl;
    cout << CYAN;
    cetakGaris('-', 42);
    cout << RESET;
    cout.flush();

    while (true) {
        int tombol = getch();
        if (tombol == 224) {
            int arah    = getch();
            int posLama = posisi;

            if (arah == 72 && posisi > 0) {
                posisi--;
            } else if (arah == 80 && posisi < jumlahOpsi - 1) {
                posisi++;
            }

            if (posLama != posisi) {
                cout << "\033[" << (barisAwal + posLama) << ";1H\033[2K";
                cout << "     " << opsi[posLama];

                cout << "\033[" << (barisAwal + posisi) << ";1H\033[2K";
                cout << HIJAU << TEBAL << "  >> " << opsi[posisi] << RESET;
                cout.flush();
            }
        } else if (tombol == 13) {
            cin.clear();
            cin.sync();
            return posisi;
        }
    }
}
#endif