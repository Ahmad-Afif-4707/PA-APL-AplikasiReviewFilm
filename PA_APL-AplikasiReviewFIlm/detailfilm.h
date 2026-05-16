#ifndef DETAILFILM_H
#define DETAILFILM_H

#include "tampilan.h"

void lihatDetailFilm(int idFilm, bool isAdmin = false) {
    Film* filmDipilih = cariFilm(idFilm);
    if (filmDipilih == nullptr) return;

    while (true) {
        system("cls");
        cetakJudul("Detail Film");

        cetakGarisTabel();
        cetakBarisTabel("Judul",  filmDipilih->judul);
        cetakBarisTabel("Tahun",  to_string(filmDipilih->tahun));
        cetakBarisTabel("Studio", filmDipilih->studio);
        cetakBarisTabel("Rating", to_string(rataRating(idFilm)) + "/10");

        if (isAdmin == false) {
            string statusFav = sudahFavorit(userAktif->id, idFilm) ? "Ya" : "Belum";
            cetakBarisTabel("Favorit", statusFav);
        }
        cetakGarisTabel();

        cout << endl << CYAN;
        cetakTengah("~ Semua Review ~", LEBAR);
        cout << RESET << endl;
        cetakGaris('-', LEBAR);

        int daftarIndexReview[MAX * 4];
        int jumlahReviewFilm = 0;
        int indexReviewSaya  = -1;
        bool adaReview       = false;

        for (int i = 0; i < totalReview; i++) {
            if (listReview[i].idFilm == idFilm) {
                daftarIndexReview[jumlahReviewFilm] = i;
                jumlahReviewFilm++;

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
                    cout << CYAN << " [" << jumlahReviewFilm << "] " << RESET;
                } else {
                    cout << "  ";
                }

                cout << KUNING << namaUser << RESET;
                if (milikSaya) cout << HIJAU << " (kamu)" << RESET;
                cout << "  " << KUNING << listReview[i].rating << "/10" << RESET << endl;
                cout << "  " << listReview[i].ulasan << endl;
                cetakGaris('-', LEBAR);
                adaReview = true;
            }
        }

        if (adaReview == false) {
            cout << KUNING;
            cetakTengah("belum ada review", LEBAR);
            cout << RESET << endl;
            cetakGaris('-', LEBAR);
        }

        if (isAdmin == false) {
            string labelReview      = indexReviewSaya >= 0 ? "Edit Review"    : "Tulis Review";
            string labelHapusReview = indexReviewSaya >= 0 ? "Hapus Review"   : "---";
            string labelFavorit     = sudahFavorit(userAktif->id, idFilm) ? "Hapus Favorit" : "Tambah Favorit";

            string opsi[4];
            opsi[0] = labelReview;
            opsi[1] = labelHapusReview;
            opsi[2] = labelFavorit;
            opsi[3] = "Kembali";

            int pilihan = pilihMenu(opsi, 4, filmDipilih->judul);

            if (pilihan == 0) {
                system("cls");
                cetakJudul(indexReviewSaya >= 0 ? "Edit Review" : "Tulis Review");

                cetakGarisTabel();
                cetakBarisTabel("Film", filmDipilih->judul);
                if (indexReviewSaya >= 0) {
                    cetakBarisTabel("Rating", to_string(listReview[indexReviewSaya].rating) + "/10  (lama)");
                    cetakBarisTabel("Ulasan", listReview[indexReviewSaya].ulasan + "  (lama)");
                }
                cetakGarisTabel();
                cout << endl;

                int ratingBaru = 0;
                cout << KUNING << " Rating baru (1-10): " << RESET;
                cin >> ratingBaru;

                if (cin.fail() || ratingBaru < 1 || ratingBaru > 10) {
                    cin.clear();
                    cin.ignore(100, '\n');
                    cout << MERAH << " Rating tidak valid!" << RESET << endl;
                    tekanEnter();
                    continue;
                }

                cin.ignore();
                bersihBuffer();
                cout << KUNING << " Ulasan baru       : " << RESET;
                string ulasanBaru = "";
                getline(cin, ulasanBaru);

                if (ulasanBaru.empty()) {
                    cout << MERAH << " Ulasan tidak boleh kosong!" << RESET << endl;
                    tekanEnter();
                    continue;
                }

                if (indexReviewSaya >= 0) {
                    listReview[indexReviewSaya].rating = ratingBaru;
                    listReview[indexReviewSaya].ulasan = ulasanBaru;
                    cout << endl << HIJAU << TEBAL << " Review berhasil diperbarui!" << RESET << endl;
                } else {
                    listReview[totalReview].idUser = userAktif->id;
                    listReview[totalReview].idFilm = idFilm;
                    listReview[totalReview].rating = ratingBaru;
                    listReview[totalReview].ulasan = ulasanBaru;
                    totalReview++;
                    cout << endl << HIJAU << TEBAL << " Review berhasil ditambahkan!" << RESET << endl;
                }
                tekanEnter();

            } else if (pilihan == 1) {
                if (indexReviewSaya < 0) continue;
                string opsiHapus[] = {"Ya, Hapus", "Batal"};
                if (pilihMenu(opsiHapus, 2, "Hapus Review?") == 0) {
                    hapusReviewDi(indexReviewSaya);
                    system("cls");
                    cout << endl << HIJAU << TEBAL << " Review berhasil dihapus!" << RESET << endl;
                    tekanEnter();
                }

            } else if (pilihan == 2) {
                system("cls");
                if (sudahFavorit(userAktif->id, idFilm)) {
                    hapusDariFavorit(userAktif->id, idFilm);
                    cout << endl << KUNING << " Film dihapus dari favorit." << RESET << endl;
                } else {
                    listFavorit[totalFavorit].idUser = userAktif->id;
                    listFavorit[totalFavorit].idFilm = idFilm;
                    totalFavorit++;
                    cout << endl << HIJAU << TEBAL << " Film ditambahkan ke favorit!" << RESET << endl;
                }
                tekanEnter();

            } else {
                break;
            }

        } else {
            if (adaReview == false) {
                string opsi[] = {"Kembali"};
                pilihMenu(opsi, 1, filmDipilih->judul);
                break;
            }

            cout << endl << CYAN;
            cetakGaris('-', LEBAR);
            cout << RESET;
            cout << " 1. Hapus review" << endl;
            cout << " 0. Kembali" << endl;
            cout << KUNING << " Pilihan: " << RESET;

            int pilihan = 0;
            cin >> pilihan;
            bersihBuffer();

            if (pilihan == 1) {
                cout << KUNING << " Nomor review yang dihapus: " << RESET;
                int nomorReview = 0;
                cin >> nomorReview;
                bersihBuffer();

                if (nomorReview >= 1 && nomorReview <= jumlahReviewFilm) {
                    hapusReviewDi(daftarIndexReview[nomorReview - 1]);
                    system("cls");
                    cout << endl << HIJAU << TEBAL << " Review berhasil dihapus!" << RESET << endl;
                    tekanEnter();
                } else {
                    cout << MERAH << " Nomor tidak valid!" << RESET << endl;
                    tekanEnter();
                }
            } else {
                break;
            }
        }
    }
}

#endif