#ifndef USULAN_H
#define USULAN_H

#include "kelolafilm.h"
#include "kelolauser.h"

void menuUsulanFilm() {
    while (true) {
        system("cls");
        cetakJudul("Usulan Film");

        if (totalUsulan == 0) {
            cout << KUNING << " tidak ada usulan" << RESET << endl;
        } else {
            for (int i = 0; i < totalUsulan; i++) {
                string namaUser = "?";
                for (int j = 0; j < totalUser; j++) {
                    if (listUser[j].id == listUsulan[i].idUser) {
                        namaUser = listUser[j].username;
                        break;
                    }
                }
                cout << CYAN << " [" << i+1 << "] " << RESET
                     << "\"" << listUsulan[i].judul << "\""
                     << KUNING << " dari: " << RESET << namaUser << endl;
            }
        }

        cout << endl;
        string opsi[] = {"pilih usulan", "kembali"};
        int pilihan = pilihMenu(opsi, 2, "Usulan Film");

        if (pilihan == 0) {
            if (totalUsulan == 0) {
                cout << MERAH << " tidak ada usulan" << RESET << endl;
                tekanEnter();
                continue;
            }

            system("cls");
            cetakJudul("Pilih Usulan");
            for (int i = 0; i < totalUsulan; i++) {
                string namaUser = "?";
                for (int j = 0; j < totalUser; j++) {
                    if (listUser[j].id == listUsulan[i].idUser) {
                        namaUser = listUser[j].username;
                        break;
                    }
                }
                cout << CYAN << " [" << i+1 << "] " << RESET
                     << "\"" << listUsulan[i].judul << "\""
                     << KUNING << " dari: " << RESET << namaUser << endl;
            }

            cout << endl << KUNING << " nomor (0 batal): " << RESET;

            // pakai bacaInputBaris agar enter kosong tidak lolos
            string inputNomor = bacaInputBaris();
            if (inputNomor.empty() || !hanyaAngka(inputNomor)) {
                cout << MERAH << " input tidak valid" << RESET << endl;
                tekanEnter();
                continue;
            }

            int nomorPilih = stoi(inputNomor);
            if (nomorPilih == 0) continue;
            if (nomorPilih < 1 || nomorPilih > totalUsulan) {
                cout << MERAH << " nomor tidak valid" << RESET << endl;
                tekanEnter();
                continue;
            }

            int indexUsulan = nomorPilih - 1;

            string namaUser = "?";
            for (int j = 0; j < totalUser; j++) {
                if (listUser[j].id == listUsulan[indexUsulan].idUser) {
                    namaUser = listUser[j].username;
                    break;
                }
            }

            system("cls");
            cetakJudul("Detail Usulan");
            cout << KUNING << " judul: " << RESET << listUsulan[indexUsulan].judul << endl;
            cout << KUNING << " dari : " << RESET << namaUser << endl;

            string opsiUsulan[] = {"terima (tambah ke film)", "tolak (hapus usulan)", "kembali"};
            int pilihanUsulan = pilihMenu(opsiUsulan, 3, "Usulan - " + listUsulan[indexUsulan].judul);

            if (pilihanUsulan == 0) {
                system("cls");
                cetakJudul("Terima Usulan");
                cout << KUNING << " judul: " << RESET << listUsulan[indexUsulan].judul << endl << endl;

                int tahunFilm = 0;
                string studioFilm = "";

                cout << KUNING << " tahun : " << RESET;
                string inputTahun = bacaInputBaris();
                if (inputTahun.empty()) {
                    cout << MERAH << " tahun tidak boleh kosong" << RESET << endl;
                    tekanEnter();
                    continue;
                }
                if (!hanyaAngka(inputTahun)) {
                    cout << MERAH << " tahun harus angka" << RESET << endl;
                    tekanEnter();
                    continue;
                }
                tahunFilm = stoi(inputTahun);

                cout << KUNING << " studio: " << RESET;
                studioFilm = bacaInputBaris();
                if (studioFilm.empty()) {
                    cout << MERAH << " studio tidak boleh kosong" << RESET << endl;
                    tekanEnter();
                    continue;
                }

                listFilm[totalFilm].id     = idFilmBaru++;
                listFilm[totalFilm].judul  = listUsulan[indexUsulan].judul;
                listFilm[totalFilm].tahun  = tahunFilm;
                listFilm[totalFilm].studio = studioFilm;
                totalFilm++;

                for (int i = indexUsulan; i < totalUsulan - 1; i++)
                    listUsulan[i] = listUsulan[i + 1];
                totalUsulan--;

                system("cls");
                cout << endl << HIJAU << TEBAL << " diterima dan film ditambahkan!" << RESET << endl;
                tekanEnter();

            } else if (pilihanUsulan == 1) {
                for (int i = indexUsulan; i < totalUsulan - 1; i++)
                    listUsulan[i] = listUsulan[i + 1];
                totalUsulan--;

                system("cls");
                cout << endl << KUNING << " usulan ditolak" << RESET << endl;
                tekanEnter();
            }

        } else {
            break;
        }
    }
}

void menuAdmin() {
    while (true) {
        string opsi[] = {
            "kelola film  (" + to_string(totalFilm)     + " film)",
            "kelola user  (" + to_string(totalUser - 1) + " user)",
            "usulan film  (" + to_string(totalUsulan)   + " usulan)",
            "logout"
        };
        int pilihan = pilihMenu(opsi, 4, "Panel Admin - " + userAktif->username);

        if      (pilihan == 0) menuKelolaFilm();
        else if (pilihan == 1) menuKelolaUser();
        else if (pilihan == 2) menuUsulanFilm();
        else {
            system("cls");
            cout << endl << HIJAU << TEBAL << " sampai jumpa, " << userAktif->username << "!" << RESET << endl;
            userAktif = nullptr;
            tekanEnter();
            break;
        }
    }
}

#endif