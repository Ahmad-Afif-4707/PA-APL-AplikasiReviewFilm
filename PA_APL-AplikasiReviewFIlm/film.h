#ifndef FILM_H
#define FILM_H

#include "detailfilm.h"

inline string keHurufKecil(string teks) {
    for (int i = 0; i < teks.size(); i++) {
        teks[i] = tolower((unsigned char)teks[i]);
    }
    return teks;
}

inline bool usulanSudahAda(const string& judulUsulan, int idUser) {
    string judulKecilBaru = keHurufKecil(judulUsulan);

    for (int i = 0; i < totalUsulan; i++) {
        if (listUsulan[i].idUser == idUser &&
            keHurufKecil(listUsulan[i].judul) == judulKecilBaru) {
            return true;
        }
    }
    return false;
}

inline void tambahUsulanFilm(const string& judulUsulan) {
    if (totalUsulan >= MAX) {
        cout << MERAH << " kapasitas usulan penuh" << RESET << endl;
        tekanEnter();
        return;
    }

    if (usulanSudahAda(judulUsulan, userAktif->id)) {
        cout << KUNING << " film ini sudah pernah kamu usulkan" << RESET << endl;
        tekanEnter();
        return;
    }

    listUsulan[totalUsulan].id = idUsulanBaru++;
    listUsulan[totalUsulan].judul = judulUsulan;
    listUsulan[totalUsulan].idUser = userAktif->id;
    totalUsulan++;

    cout << HIJAU << TEBAL << " usulan film berhasil dikirim ke admin" << RESET << endl;
    tekanEnter();
}

void menuDaftarFilm() {
    while (true) {
        system("cls");
        cetakJudul("Daftar Film");

        if (totalFilm == 0) {
            cout << KUNING << " belum ada film" << RESET << endl;
        } else {
            for (int i = 0; i < totalFilm; i++) {
                cout << CYAN << " [" << i + 1 << "] " << RESET
                    << listFilm[i].judul << " (" << listFilm[i].tahun << ")"
                    << KUNING << " - " << rataRating(listFilm[i].id) << "/10" << RESET << endl;
            }
        }

        string opsi[] = {"cari film", "pilih dari list", "kembali"};
        int pil = pilihMenu(opsi, 3, "Daftar Film");

        if (pil == 0) {
            system("cls");
            cetakJudul("Cari Film");

            cin.ignore();
            bersihBuffer();
            cout << KUNING << " ketik judul: " << RESET;
            string kataCari;
            getline(cin, kataCari);

            if (kataCari.empty()) {
                cout << MERAH << " pencarian tidak boleh kosong" << RESET << endl;
                tekanEnter();
                continue;
            }

            int indexHasil[MAX];
            int totalHasil = 0;

            string cariKecil = keHurufKecil(kataCari);

            for (int i = 0; i < totalFilm; i++) {
                string judulKecil = keHurufKecil(listFilm[i].judul);

                if (judulKecil.find(cariKecil) != string::npos) {
                    indexHasil[totalHasil++] = i;
                }
            }

            if (totalHasil == 0) {
                cout << endl << KUNING << " film tidak ditemukan" << RESET << endl;

                string opsiUsulan[] = {"ya, usulkan film ini", "tidak"};
                int pilUsulan = pilihMenu(opsiUsulan, 2, "Usulkan Film");

                if (pilUsulan == 0) {
                    tambahUsulanFilm(kataCari);
                }
            } else {
                system("cls");
                cetakJudul("Hasil Cari");

                for (int i = 0; i < totalHasil; i++) {
                    cout << CYAN << " [" << i + 1 << "] " << RESET
                        << listFilm[indexHasil[i]].judul
                        << " (" << listFilm[indexHasil[i]].tahun << ")"
                        << KUNING << " - " << rataRating(listFilm[indexHasil[i]].id) << "/10" << RESET
                        << endl;
                }

                cout << endl << KUNING << " pilih nomor (0 batal): " << RESET;
                int pilihanNomor;
                cin >> pilihanNomor;
                bersihBuffer();

                if (pilihanNomor >= 1 && pilihanNomor <= totalHasil) {
                    lihatDetailFilm(listFilm[indexHasil[pilihanNomor - 1]].id);
                }
            }

        } else if (pil == 1) {
            if (totalFilm == 0) {
                cout << MERAH << " belum ada film" << RESET << endl;
                tekanEnter();
                continue;
            }

            cout << KUNING << " pilih nomor (0 batal): " << RESET;
            int pilihanNomor;
            cin >> pilihanNomor;
            bersihBuffer();

            if (pilihanNomor >= 1 && pilihanNomor <= totalFilm) {
                lihatDetailFilm(listFilm[pilihanNomor - 1].id);
            }

        } else {
            break;
        }
    }
}

#endif