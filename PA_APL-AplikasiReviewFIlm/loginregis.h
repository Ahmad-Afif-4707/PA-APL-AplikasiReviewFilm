#ifndef LOGIN_H
#define LOGIN_H

#include "tampilan.h"

User* prosesLogin() {
    int jumlahPercobaan = 0;

    while (jumlahPercobaan < 3) {
        system("cls");

        cout << endl << CYAN;
        cetakGaris('=', 42);
        cout << " " << KUNING << TEBAL << "Review Film & Serial" << RESET << endl;
        cout << CYAN;
        cetakGaris('-', 42);
        cout << " Login" << endl;
        cetakGaris('=', 42);
        cout << RESET << endl;

        if (jumlahPercobaan > 0) {
            cout << MERAH << " login gagal! sisa percobaan: " << 3 - jumlahPercobaan << RESET << endl << endl;
        }

        string inputNama     = "";
        string inputPassword = "";

        bersihBuffer();
        cout << KUNING << " username: " << RESET;
        cin >> inputNama;

        bersihBuffer();
        cout << KUNING << " password: " << RESET;
        cin >> inputPassword;

        for (int i = 0; i < totalUser; i++) {
            if (listUser[i].username == inputNama && listUser[i].password == inputPassword) {
                cout << endl << HIJAU << TEBAL << " halo, " << inputNama << "!" << RESET << endl;
                tekanEnter();
                return &listUser[i];
            }
        }

        jumlahPercobaan++;
        cout << endl << MERAH << " username atau password salah" << RESET << endl;
        tekanEnter();
    }

    cout << MERAH << " terlalu banyak percobaan" << RESET << endl;
    tekanEnter();
    return nullptr;
}

#endif