#ifndef DETAILFILM_H
#define DETAILFILM_H

#include "tampilan.h"

void lihatDetailFilm(int idFilm, bool isAdmin = false) {
    Film* filmDipilih = cariFilm(idFilm);
    if (filmDipilih == nullptr) return;

    while (true) {
        system("cls");
        cetakJudul("Detail Film");

        cout << KUNING << " judul  : " << RESET << filmDipilih->judul  << endl;
        cout << KUNING << " tahun  : " << RESET << filmDipilih->tahun  << endl;
        cout << KUNING << " studio : " << RESET << filmDipilih->studio << endl;
        cout << KUNING << " rating : " << RESET << rataRating(idFilm) << "/10" << endl;

        if (isAdmin == false) {
            if (sudahFavorit(userAktif->id, idFilm)) {
                cout << KUNING << " favorit: " << RESET << HIJAU << "ya" << RESET << endl;
            } else {
                cout << KUNING << " favorit: " << RESET << "belum" << endl;
            }
        }

        cout << endl << CYAN;
        cetakGaris('-', 42);
        cout << KUNING << TEBAL << " semua review" << RESET << endl;
        cetakGaris('-', 42);
        cout << RESET;

        int daftarIndexReview[MAX * 4];
        int jumlahReviewFilm = 0;
        int indexReviewSaya  = -1;
        bool adaReview       = false;

        for (int i = 0; i < totalReview; i++) {
            if (listReview[i].idFilm == idFilm) {
                daftarIndexReview[jumlahReviewFilm] = i;
                jumlahReviewFilm++;

                // cari nama user yang review
                string namaUser = "?";
                for (int j = 0; j < totalUser; j++) {
                    if (listUser[j].id == listReview[i].idUser) {
                        namaUser = listUser[j].username;
                        break;
                    }
                }

                bool milikSaya = false;
                if (isAdmin == false && listReview[i].idUser == userAktif->id) {
                    milikSaya = true;
                    indexReviewSaya = i;
                }

                if (isAdmin == true) {
                    cout << " [" << jumlahReviewFilm << "] ";
                } else {
                    cout << " ";
                }

                cout << "[" << namaUser;
                if (milikSaya) {
                    cout << HIJAU << " (kamu)" << RESET;
                }
                cout << "] " << KUNING << listReview[i].rating << "/10" << RESET << endl;
                cout << "  " << listReview[i].ulasan << endl << endl;
                adaReview = true;
            }
        }

        if (adaReview == false) {
            cout << KUNING << " belum ada review" << RESET << endl;
        }

        // menu untuk user biasa
        if (isAdmin == false) {
            string labelReview = "tulis review";
            if (indexReviewSaya >= 0) {
                labelReview = "edit review";
            }

            string labelHapusReview = "---";
            if (indexReviewSaya >= 0) {
                labelHapusReview = "hapus review";
            }

            string labelFavorit = "tambah favorit";
            if (sudahFavorit(userAktif->id, idFilm)) {
                labelFavorit = "hapus favorit";
            }

            string opsi[4];
            opsi[0] = labelReview;
            opsi[1] = labelHapusReview;
            opsi[2] = labelFavorit;
            opsi[3] = "kembali";

            int pilihan = pilihMenu(opsi, 4, filmDipilih->judul);

            if (pilihan == 0) {
                // tulis atau edit review
                system("cls");
                if (indexReviewSaya >= 0) {
                    cetakJudul("Edit Review");
                } else {
                    cetakJudul("Tulis Review");
                }
                cout << KUNING << " film: " << RESET << filmDipilih->judul << endl << endl;

                if (indexReviewSaya >= 0) {
                    cout << KUNING << " rating lama: " << RESET << listReview[indexReviewSaya].rating << "/10" << endl;
                    cout << KUNING << " ulasan lama: " << RESET << listReview[indexReviewSaya].ulasan << endl << endl;
                }

                int ratingBaru = 0;
                cout << KUNING << " rating (1-10): " << RESET;
                cin >> ratingBaru;

                if (cin.fail() || ratingBaru < 1 || ratingBaru > 10) {
                    cin.clear();
                    cin.ignore(100, '\n');
                    cout << MERAH << " rating tidak valid" << RESET << endl;
                    tekanEnter();
                    continue;
                }

                cin.ignore();
                bersihBuffer();
                cout << KUNING << " ulasan: " << RESET;
                string ulasanBaru = "";
                getline(cin, ulasanBaru);

                if (ulasanBaru.empty()) {
                    cout << MERAH << " ulasan tidak boleh kosong" << RESET << endl;
                    tekanEnter();
                    continue;
                }

                if (indexReviewSaya >= 0) {
                    listReview[indexReviewSaya].rating = ratingBaru;
                    listReview[indexReviewSaya].ulasan = ulasanBaru;
                    cout << endl << HIJAU << TEBAL << " review diupdate!" << RESET << endl;
                } else {
                    listReview[totalReview].idUser = userAktif->id;
                    listReview[totalReview].idFilm = idFilm;
                    listReview[totalReview].rating = ratingBaru;
                    listReview[totalReview].ulasan = ulasanBaru;
                    totalReview++;
                    cout << endl << HIJAU << TEBAL << " review ditambahkan!" << RESET << endl;
                }
                tekanEnter();

            } else if (pilihan == 1) {
                // hapus review milik sendiri
                if (indexReviewSaya < 0) {
                    continue;
                }
                string opsiHapus[] = {"ya hapus", "batal"};
                if (pilihMenu(opsiHapus, 2, "Hapus Review?") == 0) {
                    hapusReviewDi(indexReviewSaya);
                    system("cls");
                    cout << endl << HIJAU << TEBAL << " review dihapus" << RESET << endl;
                    tekanEnter();
                }

            } else if (pilihan == 2) {
                // tambah atau hapus favorit
                system("cls");
                if (sudahFavorit(userAktif->id, idFilm)) {
                    hapusDariFavorit(userAktif->id, idFilm);
                    cout << endl << KUNING << " dihapus dari favorit" << RESET << endl;
                } else {
                    listFavorit[totalFavorit].idUser = userAktif->id;
                    listFavorit[totalFavorit].idFilm = idFilm;
                    totalFavorit++;
                    cout << endl << HIJAU << TEBAL << " ditambahkan ke favorit!" << RESET << endl;
                }
                tekanEnter();

            } else {
                break;
            }

        } else {
            // mode admin: hanya bisa hapus review
            if (adaReview == false) {
                string opsi[] = {"kembali"};
                pilihMenu(opsi, 1, filmDipilih->judul);
                break;
            }

            cout << endl << CYAN;
            cetakGaris('-', 42);
            cout << RESET;
            cout << " 1. hapus review" << endl;
            cout << " 0. kembali" << endl;
            cout << KUNING << " pilihan: " << RESET;

            int pilihan = 0;
            cin >> pilihan;
            bersihBuffer();

            if (pilihan == 1) {
                cout << KUNING << " nomor review yang dihapus: " << RESET;
                int nomorReview = 0;
                cin >> nomorReview;
                bersihBuffer();

                if (nomorReview >= 1 && nomorReview <= jumlahReviewFilm) {
                    hapusReviewDi(daftarIndexReview[nomorReview - 1]);
                    system("cls");
                    cout << endl << HIJAU << TEBAL << " review dihapus" << RESET << endl;
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
}

#endif