#ifndef LOGINREGIS_H
#define LOGINREGIS_H

#include "tampilan.h"
void menuAdmin();
void menuUser();

bool usernameSudahAda(const string &usernameBaru)
{
    for (int i = 0; i < totalUser; i++)
    {
        if (listUser[i].username == usernameBaru)
        {
            return true;
        }
    }
    return false;
}

void prosesRegistrasi()
{
    while (true)
    {
        system("cls");

        cout << endl << CYAN;
        cetakGaris('=', 42);
        cout << " " << KUNING << TEBAL << "Review Film & Serial" << RESET << endl;
        cout << CYAN;
        cetakGaris('-', 42);
        cout << " Registrasi" << endl;
        cetakGaris('=', 42);
        cout << RESET << endl;

        if (totalUser >= MAX)
        {
            cout << MERAH << " data user sudah penuh" << RESET << endl;
            tekanEnter();
            return;
        }

        string usernameBaru;
        string passwordBaru;
        string konfirmasiPassword;

        cout << KUNING << " username baru: " << RESET;
        usernameBaru = bacaInputBaris();

        if (usernameBaru.empty())
        {
            cout << MERAH << " username tidak boleh kosong" << RESET << endl;
            tekanEnter();
            continue;
        }

        if (usernameSudahAda(usernameBaru))
        {
            cout << MERAH << " username sudah dipakai" << RESET << endl;
            tekanEnter();
            continue;
        }

        cout << KUNING << " password: " << RESET;
        passwordBaru = bacaInputBaris();

        if (passwordBaru.empty())
        {
            cout << MERAH << " password tidak boleh kosong" << RESET << endl;
            tekanEnter();
            continue;
        }

        cout << KUNING << " konfirmasi password: " << RESET;
        konfirmasiPassword = bacaInputBaris();

        if (konfirmasiPassword.empty())
        {
            cout << MERAH << " konfirmasi password tidak boleh kosong" << RESET << endl;
            tekanEnter();
            continue;
        }

        if (passwordBaru != konfirmasiPassword)
        {
            cout << MERAH << " password dan konfirmasi password tidak sama" << RESET << endl;
            tekanEnter();
            continue;
        }

        listUser[totalUser].id = idUserBaru++;
        listUser[totalUser].username = usernameBaru;
        listUser[totalUser].password = passwordBaru;
        listUser[totalUser].role = "user";
        totalUser++;

        cout << endl << HIJAU << TEBAL << " registrasi berhasil!." << RESET << endl;
        tekanEnter();
        return;
    }
}

User *prosesLogin()
{
    int jumlahPercobaan = 0;

    while (jumlahPercobaan < 3)
    {
        system("cls");

        cout << endl << CYAN;
        cetakGaris('=', 42);
        cout << " " << KUNING << TEBAL << "Review Film & Serial" << RESET << endl;
        cout << CYAN;
        cetakGaris('-', 42);
        cout << " Login" << endl;
        cetakGaris('=', 42);
        cout << RESET << endl;

        if (jumlahPercobaan > 0)
        {
            cout << MERAH << " login gagal! sisa percobaan: " << 3 - jumlahPercobaan << RESET << endl << endl;
        }

        string inputNama;
        string inputPassword;

        cout << KUNING << " username: " << RESET;
        inputNama = bacaInputBaris();

        if (inputNama.empty())
        {
            cout << MERAH << " username tidak boleh kosong" << RESET << endl;
            tekanEnter();
            jumlahPercobaan++;
            continue;
        }

        cout << KUNING << " password: " << RESET;
        inputPassword = bacaInputBaris();

        if (inputPassword.empty())
        {
            cout << MERAH << " password tidak boleh kosong" << RESET << endl;
            tekanEnter();
            jumlahPercobaan++;
            continue;
        }

        for (int i = 0; i < totalUser; i++)
        {
            if (listUser[i].username == inputNama && listUser[i].password == inputPassword)
            {
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

void menuAwal()
{
    while (true)
    {
        string opsi[] = {"login", "registrasi", "keluar"};
        int pil = pilihMenu(opsi, 3, "Review Film & Serial");

        if (pil == 0)
        {
            userAktif = prosesLogin();

            if (userAktif != nullptr)
            {
                if (userAktif->role == "admin")
                {
                    menuAdmin();
                }
                else
                {
                    menuUser();
                }
            }
        }
        else if (pil == 1)
        {
            prosesRegistrasi();
        }
        else
        {
            system("cls");
            cout << endl << CYAN;
            cetakGaris('=', 42);
            cout << " " << KUNING << "makasih sudah pake aplikasinya!" << RESET << endl;
            cout << CYAN;
            cetakGaris('=', 42);
            cout << RESET << endl << endl;
            break;
        }
    }
}

#endif