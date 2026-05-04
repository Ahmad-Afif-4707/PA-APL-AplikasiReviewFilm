#ifndef KOLEKSI_H
#define KOLEKSI_H

#include "film.h"
#include "loginregis.h"

void menuFavorit() {
    while (true) {
        system("cls");
        cetakJudul("Film Favorit");

        Film filmFav[MAX * 4];
        int totalFav = 0;
        sortFavoritAZ(filmFav, totalFav);

        if (totalFav == 0) {
            cout << KUNING << " belum ada favorit" << RESET << endl;
        } else {
            for (int i = 0; i < totalFav; i++)
                cout << CYAN << " [" << i+1 << "] " << RESET
                     << filmFav[i].judul << " (" << filmFav[i].tahun << ")"
                     << KUNING << " - " << rataRating(filmFav[i].id) << "/10" << RESET << endl;
        }

        string opsi[] = {"buka detail film", "kembali"};
        int pil = pilihMenu(opsi, 2, "Film Favorit");

        if (pil == 0) {
            if (totalFav == 0) { cout << MERAH << " belum ada favorit" << RESET << endl; tekanEnter(); continue; }
            cout << KUNING << " nomor film: " << RESET;
            int nomorPilih; cin >> nomorPilih; bersihBuffer();
            if (nomorPilih >= 1 && nomorPilih <= totalFav)
                lihatDetailFilm(filmFav[nomorPilih-1].id);
            else { cout << MERAH << " nomor tidak valid" << RESET << endl; tekanEnter(); }
        } else break;
    }
}

// TAMBAHKAN fungsi menuHistory di sini
// fungsi ini menampilkan semua film yang pernah direview oleh userAktif
// kumpulkan index review milik userAktif dari listReview ke array lokal
// tampilkan judul film dan ratingnya (cari judul film pakai loop ke listFilm berdasarkan idFilm, tidak perlu pointer)
// user bisa memilih nomor untuk melihat detail rating dan ulasannya

// TAMBAHKAN fungsi menuAkun di sini
// fungsi ini menampilkan username dan role userAktif
// user bisa memilih ganti username atau ganti password
// ganti username: minta input username baru, cek duplikat dengan loop ke listUser
// ganti password: minta password lama dulu, jika cocok baru minta password baru dan konfirmasi

// TAMBAHKAN fungsi menuKoleksi di sini
// fungsi ini menampilkan sub-menu dengan dua pilihan: favorit dan history review
// masing-masing memanggil menuFavorit() dan menuHistory()

void menuUser() {
    // UBAH daftar opsi, tambahkan "koleksi saya" dan "akun saya"
    // sesuaikan jumlah opsi dan penomoran pilihan di bawahnya
    string opsi[] = {"daftar film", "favorit saya", "logout"};
    while (true) {
        int pil = pilihMenu(opsi, 3, "Halo, " + userAktif->username + "!");
        if (pil == 0) menuDaftarFilm();
        else if (pil == 1) menuFavorit();
        // UBAH pil == 1 panggil menuKoleksi() bukan menuFavorit()
        // TAMBAHKAN pil == 2 panggil menuAkun()
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