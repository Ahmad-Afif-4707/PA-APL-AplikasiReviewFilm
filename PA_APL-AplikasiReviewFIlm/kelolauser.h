#ifndef KELOLAUSER_H
#define KELOLAUSER_H

#include "tampilan.h"

void menuKelolaUser() {
    while (true) {
        int daftarUserBiasa[MAX];
        int totalUserBiasa = 0;

        for (int i = 0; i < totalUser; i++) {
            if (listUser[i].role != "admin") {
                daftarUserBiasa[totalUserBiasa] = i;
                totalUserBiasa++;
            }
        }

        string opsiUtama[] = {"pilih user", "kembali"};
        int pil = pilihMenu(opsiUtama, 2, "Kelola User");

        if (pil == 0) {
            if (totalUserBiasa == 0) {
                system("cls");
                cetakJudul("Kelola User");
                cout << MERAH << " belum ada user yang bisa dipilih" << RESET << endl;
                tekanEnter();
                continue;
            }

            string daftarUser[MAX + 1];
            for (int i = 0; i < totalUserBiasa; i++) {
                daftarUser[i] = listUser[daftarUserBiasa[i]].username;
            }
            daftarUser[totalUserBiasa] = "kembali";

            int pilihanDaftar = pilihMenu(daftarUser, totalUserBiasa + 1, "Pilih User");
            if (pilihanDaftar == totalUserBiasa) {
                continue;
            }

            int indexUser   = daftarUserBiasa[pilihanDaftar];
            int idUserPilih = listUser[indexUser].id;

            while (true) {
                system("cls");
                cetakJudul("Detail User");

                cout << KUNING << " username     : " << RESET << listUser[indexUser].username << endl;

                int daftarReviewUser[MAX * 4];
                int jumlahReviewUser = 0;

                for (int i = 0; i < totalReview; i++) {
                    if (listReview[i].idUser == idUserPilih) {
                        daftarReviewUser[jumlahReviewUser] = i;
                        jumlahReviewUser++;
                    }
                }

                cout << KUNING << " total review : " << RESET << jumlahReviewUser << endl;

                cout << endl << CYAN;
                cetakGaris('-', 42);
                cout << KUNING << TEBAL << " daftar review" << RESET << endl;
                cetakGaris('-', 42);
                cout << RESET;

                if (jumlahReviewUser == 0) {
                    cout << KUNING << " user ini belum punya review" << RESET << endl;
                } else {
                    for (int i = 0; i < jumlahReviewUser; i++) {
                        Film* filmReview = cariFilm(listReview[daftarReviewUser[i]].idFilm);
                        string judulFilm = "(film tidak ditemukan)";
                        if (filmReview != nullptr) {
                            judulFilm = filmReview->judul;
                        }
                        cout << CYAN << " [" << i + 1 << "] " << RESET
                             << judulFilm
                             << KUNING << " - " << listReview[daftarReviewUser[i]].rating << "/10" << RESET << endl;
                        cout << "     " << listReview[daftarReviewUser[i]].ulasan << endl;
                    }
                }

                string opsiUser[] = {"hapus user", "hapus review", "kembali"};
                int pilihanUser = pilihMenu(opsiUser, 3, listUser[indexUser].username);

                if (pilihanUser == 0) {
                    string opsiHapus[] = {"ya hapus", "batal"};
                    if (pilihMenu(opsiHapus, 2, "Hapus User?") == 0) {
                        hapusUser(idUserPilih);
                        system("cls");
                        cout << endl << HIJAU << TEBAL << " user berhasil dihapus" << RESET << endl;
                        tekanEnter();
                        break;
                    }

                } else if (pilihanUser == 1) {
                    if (jumlahReviewUser == 0) {
                        cout << MERAH << " user ini belum punya review" << RESET << endl;
                        tekanEnter();
                        continue;
                    }

                    string daftarReview[MAX * 4 + 1];
                    for (int i = 0; i < jumlahReviewUser; i++) {
                        Film* filmReview = cariFilm(listReview[daftarReviewUser[i]].idFilm);
                        string judulFilm = "(film tidak ditemukan)";
                        if (filmReview != nullptr) judulFilm = filmReview->judul;
                        daftarReview[i] = judulFilm + " - " + to_string(listReview[daftarReviewUser[i]].rating) + "/10";
                    }
                    daftarReview[jumlahReviewUser] = "kembali";

                    int pilihanReview = pilihMenu(daftarReview, jumlahReviewUser + 1, "Hapus Review");
                    if (pilihanReview == jumlahReviewUser) {
                        continue;
                    }

                    hapusReviewDi(daftarReviewUser[pilihanReview]);
                    system("cls");
                    cout << endl << HIJAU << TEBAL << " review berhasil dihapus" << RESET << endl;
                    tekanEnter();

                } else {
                    break;
                }

                for (int i = 0; i < totalUser; i++) {
                    if (listUser[i].id == idUserPilih) {
                        indexUser = i;
                        break;
                    }
                }
            }

        } else {
            break;
        }
    }
}

#endif