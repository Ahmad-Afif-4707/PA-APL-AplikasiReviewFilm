#ifndef KOLEKSI_H
#define KOLEKSI_H

#include "film.h"
#include "loginregis.h"

inline Film* cariFilmById(int idFilm) {
    for (int i = 0; i < totalFilm; i++) {
        if (listFilm[i].id == idFilm) {
            return &listFilm[i];
        }
    }
    return nullptr;
}

inline int cariIndexUserByUsername(const string& username) {
    for (int i = 0; i < totalUser; i++) {
        if (listUser[i].username == username) {
            return i;
        }
    }
    return -1;
}

inline int cariIndexReviewUserFilm(int idUser, int idFilm) {
    for (int i = 0; i < totalReview; i++) {
        if (listReview[i].idUser == idUser && listReview[i].idFilm == idFilm) {
            return i;
        }
    }
    return -1;
}

inline bool usernameSudahDipakai(const string& usernameBaru) {
    for (int i = 0; i < totalUser; i++) {
        if (listUser[i].username == usernameBaru) {
            return true;
        }
    }
    return false;
}

inline void menuFavorit() {
    while (true) {
        system("cls");
        cetakJudul("Film Favorit");

        int indexFavorit[MAX];
        int totalFav = 0;

        for (int i = 0; i < totalReview; i++) {
            if (listReview[i].idUser == userAktif->id && listReview[i].rating >= 8) {
                int idFilm = listReview[i].idFilm;
                bool sudahAda = false;

                for (int j = 0; j < totalFav; j++) {
                    if (listFilm[indexFavorit[j]].id == idFilm) {
                        sudahAda = true;
                        break;
                    }
                }

                if (!sudahAda) {
                    for (int k = 0; k < totalFilm; k++) {
                        if (listFilm[k].id == idFilm) {
                            indexFavorit[totalFav++] = k;
                            break;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < totalFav - 1; i++) {
            for (int j = i + 1; j < totalFav; j++) {
                if (listFilm[indexFavorit[i]].judul > listFilm[indexFavorit[j]].judul) {
                    int temp = indexFavorit[i];
                    indexFavorit[i] = indexFavorit[j];
                    indexFavorit[j] = temp;
                }
            }
        }

        if (totalFav == 0) {
            cout << KUNING << " belum ada favorit" << RESET << endl;
        } else {
            for (int i = 0; i < totalFav; i++) {
                cout << CYAN << " [" << i + 1 << "] " << RESET
                     << listFilm[indexFavorit[i]].judul << " (" << listFilm[indexFavorit[i]].tahun << ")"
                     << KUNING << " - " << rataRating(listFilm[indexFavorit[i]].id) << "/10" << RESET << endl;
            }
        }

        string opsi[] = {"buka detail film", "kembali"};
        int pil = pilihMenu(opsi, 2, "Film Favorit");

        if (pil == 0) {
            if (totalFav == 0) {
                cout << MERAH << " belum ada favorit" << RESET << endl;
                tekanEnter();
                continue;
            }

            cout << KUNING << " nomor film: " << RESET;
            int nomorPilih;
            cin >> nomorPilih;
            bersihBuffer();

            if (nomorPilih >= 1 && nomorPilih <= totalFav) {
                lihatDetailFilm(listFilm[indexFavorit[nomorPilih - 1]].id);
            } else {
                cout << MERAH << " nomor tidak valid" << RESET << endl;
                tekanEnter();
            }
        } else {
            break;
        }
    }
}

inline void menuHistory() {
    while (true) {
        system("cls");
        cetakJudul("History Review");

        int indexReviewUser[MAX];
        int totalHistory = 0;

        for (int i = 0; i < totalReview; i++) {
            if (listReview[i].idUser == userAktif->id) {
                indexReviewUser[totalHistory++] = i;
            }
        }

        if (totalHistory == 0) {
            cout << KUNING << " belum ada history review" << RESET << endl;
        } else {
            for (int i = 0; i < totalHistory; i++) {
                int idxReview = indexReviewUser[i];
                Film* film = cariFilmById(listReview[idxReview].idFilm);

                cout << CYAN << " [" << i + 1 << "] " << RESET;
                if (film != nullptr) {
                    cout << film->judul << " (" << film->tahun << ")";
                } else {
                    cout << "film tidak ditemukan";
                }
                cout << KUNING << " - rating: " << listReview[idxReview].rating << "/10" << RESET << endl;
            }
        }

        string opsi[] = {"lihat detail review", "kembali"};
        int pil = pilihMenu(opsi, 2, "History Review");

        if (pil == 0) {
            if (totalHistory == 0) {
                cout << MERAH << " belum ada history review" << RESET << endl;
                tekanEnter();
                continue;
            }

            cout << KUNING << " pilih nomor review: " << RESET;
            int nomorPilih;
            cin >> nomorPilih;
            bersihBuffer();

            if (nomorPilih >= 1 && nomorPilih <= totalHistory) {
                int idxReview = indexReviewUser[nomorPilih - 1];
                Film* film = cariFilmById(listReview[idxReview].idFilm);

                system("cls");
                cetakJudul("Detail Review");

                if (film != nullptr) {
                    cout << KUNING << " judul  : " << RESET << film->judul << endl;
                    cout << KUNING << " tahun  : " << RESET << film->tahun << endl;
                } else {
                    cout << KUNING << " judul  : " << RESET << "film tidak ditemukan" << endl;
                }

                cout << KUNING << " rating : " << RESET << listReview[idxReview].rating << "/10" << endl;
                cout << KUNING << " ulasan : " << RESET << listReview[idxReview].ulasan << endl;

                tekanEnter();
            } else {
                cout << MERAH << " nomor tidak valid" << RESET << endl;
                tekanEnter();
            }
        } else {
            break;
        }
    }
}

inline void menuAkun() {
    while (true) {
        system("cls");
        cetakJudul("Akun Saya");

        cout << KUNING << " username : " << RESET << userAktif->username << endl;
        cout << KUNING << " role     : " << RESET << userAktif->role << endl << endl;

        string opsi[] = {"ganti username", "ganti password", "kembali"};
        int pil = pilihMenu(opsi, 3, "Akun Saya");

        if (pil == 0) {
            system("cls");
            cetakJudul("Ganti Username");

            cin.ignore();
            bersihBuffer();

            string usernameBaru;
            cout << KUNING << " username baru: " << RESET;
            getline(cin, usernameBaru);

            if (usernameBaru.empty()) {
                cout << MERAH << " username tidak boleh kosong" << RESET << endl;
                tekanEnter();
                continue;
            }

            bool duplikat = false;
            for (int i = 0; i < totalUser; i++) {
                if (i != cariIndexUserByUsername(userAktif->username) && listUser[i].username == usernameBaru) {
                    duplikat = true;
                    break;
                }
            }

            if (duplikat) {
                cout << MERAH << " username sudah dipakai user lain" << RESET << endl;
                tekanEnter();
                continue;
            }

            userAktif->username = usernameBaru;
            cout << HIJAU << TEBAL << " username berhasil diubah" << RESET << endl;
            tekanEnter();

        } else if (pil == 1) {
            system("cls");
            cetakJudul("Ganti Password");

            cin.ignore();
            bersihBuffer();

            string passwordLama, passwordBaru, konfirmasi;
            cout << KUNING << " password lama   : " << RESET;
            getline(cin, passwordLama);

            if (passwordLama != userAktif->password) {
                cout << MERAH << " password lama salah" << RESET << endl;
                tekanEnter();
                continue;
            }

            cout << KUNING << " password baru   : " << RESET;
            getline(cin, passwordBaru);

            if (passwordBaru.empty()) {
                cout << MERAH << " password baru tidak boleh kosong" << RESET << endl;
                tekanEnter();
                continue;
            }

            cout << KUNING << " konfirmasi ulang: " << RESET;
            getline(cin, konfirmasi);

            if (passwordBaru != konfirmasi) {
                cout << MERAH << " konfirmasi password tidak cocok" << RESET << endl;
                tekanEnter();
                continue;
            }

            userAktif->password = passwordBaru;
            cout << HIJAU << TEBAL << " password berhasil diubah" << RESET << endl;
            tekanEnter();

        } else {
            break;
        }
    }
}

inline void menuKoleksi() {
    while (true) {
        string opsi[] = {"favorit", "history review", "kembali"};
        int pil = pilihMenu(opsi, 3, "Koleksi Saya");

        if (pil == 0) {
            menuFavorit();
        } else if (pil == 1) {
            menuHistory();
        } else {
            break;
        }
    }
}

inline void menuUser() {
    string opsi[] = {"daftar film", "koleksi saya", "akun saya", "logout"};

    while (true) {
        int pil = pilihMenu(opsi, 4, "Halo, " + userAktif->username + "!");

        if (pil == 0) {
            menuDaftarFilm();
        } else if (pil == 1) {
            menuKoleksi();
        } else if (pil == 2) {
            menuAkun();
        } else {
            system("cls");
            cout << endl << HIJAU << TEBAL << " sampai jumpa, " << userAktif->username << "!" << RESET << endl;
            userAktif = nullptr;
            tekanEnter();
            break;
        }
    }
}

#endif