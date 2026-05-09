#ifndef LOGINREGIS_H
#define LOGINREGIS_H

#include "tampilan.h"

inline bool usernameSudahAda(const string& username) {
    for (int i = 0; i < totalUser; i++) {
        if (listUser[i].username == username) {
            return true;
        }
    }
    return false;
}

inline void prosesRegistrasi() {
    system("cls");

    cout << endl << CYAN;
    cetakGaris('=', 42);
    cout << " " << KUNING << TEBAL << "Review Film & Serial" << RESET << endl;
    cout << CYAN;
    cetakGaris('-', 42);
    cout << " Registrasi" << endl;
    cetakGaris('=', 42);
    cout << RESET << endl;

    if (totalUser <= 0) {
    }

    int kapasitasUser = sizeof(listUser) / sizeof(listUser[0]);
    if (totalUser >= kapasitasUser) {
        cout << MERAH << " kapasitas user penuh, registrasi gagal" << RESET << endl;
        tekanEnter();
        return;
    }

    string inputNama     = "";
    string inputPassword = "";

    bersihBuffer();
    cout << KUNING << " username baru: " << RESET;
    cin >> inputNama;

    if (inputNama.empty()) {
        cout << endl << MERAH << " username tidak boleh kosong" << RESET << endl;
        tekanEnter();
        return;
    }

    if (usernameSudahAda(inputNama)) {
        cout << endl << MERAH << " username sudah dipakai, silakan pilih yang lain" << RESET << endl;
        tekanEnter();
        return;
    }

    bersihBuffer();
    cout << KUNING << " password baru: " << RESET;
    cin >> inputPassword;

    if (inputPassword.empty()) {
        cout << endl << MERAH << " password tidak boleh kosong" << RESET << endl;
        tekanEnter();
        return;
    }

    listUser[totalUser].username = inputNama;
    listUser[totalUser].password = inputPassword;
    totalUser++;

    cout << endl << HIJAU << TEBAL << " registrasi berhasil, silakan login" << RESET << endl;
    tekanEnter();
}

inline User* prosesLogin() {
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
            cout << MERAH << " login gagal, sisa percobaan: " << 3 - jumlahPercobaan << RESET << endl << endl;
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

inline User* menuLoginRegis() {
    while (true) {
        system("cls");

        cout << endl << CYAN;
        cetakGaris('=', 42);
        cout << " " << KUNING << TEBAL << "Review Film & Serial" << RESET << endl;
        cout << CYAN;
        cetakGaris('-', 42);
        cout << " Menu Login" << endl;
        cetakGaris('=', 42);
        cout << RESET << endl;

        cout << KUNING << "1. Login" << endl;
        cout << "2. Registrasi" << endl;
        cout << "3. Keluar" << RESET << endl;
        cout << endl << KUNING << "pilih menu: " << RESET;

        int pilihan;
        cin >> pilihan;

        if (pilihan == 1) {
            User* userAktif = prosesLogin();
            if (userAktif != nullptr) {
                return userAktif;
            }
        } 
        else if (pilihan == 2) {
            prosesRegistrasi();
        } 
        else if (pilihan == 3) {
            return nullptr;
        } 
        else {
            cout << endl << MERAH << " pilihan tidak valid" << RESET << endl;
            tekanEnter();
        }
    }
}

#endif