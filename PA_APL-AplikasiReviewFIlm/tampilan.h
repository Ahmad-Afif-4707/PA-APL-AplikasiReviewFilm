#ifndef TAMPILAN_H
#define TAMPILAN_H

#include "data.h"
#include <iomanip>

#define LEBAR 52

void cetakGaris(char kar, int panjang) {
    for (int i = 0; i < panjang; i++) cout << kar;
    cout << endl;
}

void cetakTengah(string teks, int lebar) {
    int padding = (lebar - (int)teks.size()) / 2;
    if (padding < 0) padding = 0;
    for (int i = 0; i < padding; i++) cout << " ";
    cout << teks;
}

void cetakJudul(string teks) {
    cout << endl << CYAN;
    cetakGaris('=', LEBAR);
    cout << KUNING << TEBAL;
    cetakTengah(teks, LEBAR);
    cout << RESET << endl << CYAN;
    cetakGaris('=', LEBAR);
    cout << RESET << endl;
}

void cetakGarisTabel() {
    cout << CYAN << " +";
    for (int i = 0; i < LEBAR - 4; i++) cout << "-";
    cout << "+" << RESET << endl;
}

void cetakBarisTabel(string label, string nilai) {
    int lebarLabel = 10;
    cout << CYAN << " | " << RESET;
    cout << KUNING << left << setw(lebarLabel) << label << RESET;
    cout << CYAN << " | " << RESET;
    cout << left << nilai << endl;
}

void tekanEnter() {
    cout << endl;
    system("pause");
}

int pilihMenu(string opsi[], int jumlahOpsi, string judul) {
    int posisi = 0;
    system("cls");

    cout << endl << CYAN;
    cetakGaris('=', LEBAR);
    cout << KUNING << TEBAL;
    cetakTengah(judul, LEBAR);
    cout << RESET << endl << CYAN;
    cetakGaris('=', LEBAR);
    cout << RESET << endl;

    int barisAwal = 6;

    for (int i = 0; i < jumlahOpsi; i++) {
        if (i == posisi) {
            cout << HIJAU << TEBAL << "  >> " << opsi[i];
            int pad = LEBAR - 5 - (int)opsi[i].size();
            for (int j = 0; j < pad && j < 20; j++) cout << " ";
            cout << RESET << endl;
        } else {
            cout << "     " << opsi[i] << endl;
        }
    }

    cout << endl << CYAN;
    cetakGaris('-', LEBAR);
    cout << KUNING;
    cetakTengah("panah atas/bawah + enter", LEBAR);
    cout << RESET << endl << CYAN;
    cetakGaris('-', LEBAR);
    cout << RESET;
    cout.flush();

    while (true) {
        int tombol = getch();
        if (tombol == 224) {
            int arah    = getch();
            int posLama = posisi;

            if (arah == 72 && posisi > 0)                   posisi--;
            else if (arah == 80 && posisi < jumlahOpsi - 1) posisi++;

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