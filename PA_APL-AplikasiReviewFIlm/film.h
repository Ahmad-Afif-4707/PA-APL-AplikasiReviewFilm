#ifndef FILM_H
#define FILM_H

#include "detailfilm.h"

void menuDaftarFilm() {
    while (true) {
        system("cls");
        cetakJudul("Daftar Film");

        if (totalFilm == 0) {
            cout << KUNING << " belum ada film" << RESET << endl;
        } else {
            // UBAH tampilan daftar film, hapus pencarian nama user pemilik film
            // cukup tampilkan nomor, judul, tahun, dan rata-rata rating
            for (int i = 0; i < totalFilm; i++) {
                cout << CYAN << " [" << i+1 << "] " << RESET
                     << listFilm[i].judul << " (" << listFilm[i].tahun << ")"
                     << KUNING << " - " << rataRating(listFilm[i].id) << "/10" << RESET << endl;
            }
        }

        // HAPUS opsi "tambah film" dari menu ini
        // kurangi jumlah opsi dan sesuaikan penomoran pilihan di bawah
        string opsi[] = {"tambah film", "cari film", "pilih dari list", "kembali"};
        int pil = pilihMenu(opsi, 4, "Daftar Film");

        // HAPUS seluruh blok if (pil == 0) tambah film beserta isinya
        // sesuaikan kembali penomoran blok else if di bawahnya
        if (pil == 0) {
            system("cls"); cetakJudul("Tambah Film");
            string judulBaru, studioBaru;
            int tahunBaru;

            cin.ignore(); bersihBuffer();
            cout << KUNING << " judul : " << RESET; getline(cin, judulBaru);
            if (judulBaru.empty()) { cout << MERAH << " tidak boleh kosong" << RESET << endl; tekanEnter(); continue; }

            bersihBuffer();
            cout << KUNING << " tahun : " << RESET; cin >> tahunBaru;
            if (cin.fail()) { cin.clear(); cin.ignore(100,'\n'); cout << MERAH << " harus angka" << RESET << endl; tekanEnter(); continue; }

            cin.ignore(); bersihBuffer();
            cout << KUNING << " studio: " << RESET; getline(cin, studioBaru);
            if (studioBaru.empty()) { cout << MERAH << " tidak boleh kosong" << RESET << endl; tekanEnter(); continue; }

            listFilm[totalFilm].id     = idFilmBaru++;
            listFilm[totalFilm].judul  = judulBaru;
            listFilm[totalFilm].tahun  = tahunBaru;
            listFilm[totalFilm].studio = studioBaru;
            listFilm[totalFilm].idUser = userAktif->id;
            totalFilm++;

            cout << endl << HIJAU << TEBAL << " film ditambahkan!" << RESET << endl;
            tekanEnter();

        } else if (pil == 1) {
            system("cls"); cetakJudul("Cari Film");
            cin.ignore(); bersihBuffer();
            cout << KUNING << " ketik judul: " << RESET;
            string kataCari; getline(cin, kataCari);

            int indexHasil[MAX];
            int totalHasil = 0;

            for (int i = 0; i < totalFilm; i++) {
                string judulKecil = listFilm[i].judul;
                string cariKecil  = kataCari;
                for (int j = 0; j < judulKecil.size(); j++) judulKecil[j] = tolower(judulKecil[j]);
                for (int j = 0; j < cariKecil.size();  j++) cariKecil[j]  = tolower(cariKecil[j]);

                if (judulKecil.find(cariKecil) != string::npos)
                    indexHasil[totalHasil++] = i;
            }

            if (totalHasil == 0) {
                // UBAH bagian ini, jika film tidak ditemukan tawarkan opsi untuk mengusulkan
                // film tersebut ke admin, simpan usulan ke listUsulan jika user setuju
                cout << endl << KUNING << " film tidak ditemukan" << RESET << endl;
                tekanEnter();
            } else {
                system("cls"); cetakJudul("Hasil Cari");
                for (int i = 0; i < totalHasil; i++)
                    cout << CYAN << " [" << i+1 << "] " << RESET
                         << listFilm[indexHasil[i]].judul
                         << " (" << listFilm[indexHasil[i]].tahun << ")" << endl;

                cout << endl << KUNING << " pilih nomor (0 batal): " << RESET;
                int pilihanNomor; cin >> pilihanNomor; bersihBuffer();
                if (pilihanNomor >= 1 && pilihanNomor <= totalHasil)
                    lihatDetailFilm(listFilm[indexHasil[pilihanNomor-1]].id);
            }

        } else if (pil == 2) {
            if (totalFilm == 0) { cout << MERAH << " belum ada film" << RESET << endl; tekanEnter(); continue; }
            cout << KUNING << " pilih nomor (0 batal): " << RESET;
            int pilihanNomor; cin >> pilihanNomor; bersihBuffer();

            // HAPUS seluruh blok pengecekan milikku dan opsi edit/hapus film
            // user tidak lagi bisa edit atau hapus film, langsung masuk ke lihatDetailFilm
            if (pilihanNomor >= 1 && pilihanNomor <= totalFilm) {
                int indexPilih = pilihanNomor - 1;
                bool milikku = (listFilm[indexPilih].idUser == userAktif->id);

                if (milikku) {
                    string opsiFilm[] = {"lihat detail", "edit film", "hapus film", "kembali"};
                    int pilihanFilm = pilihMenu(opsiFilm, 4, listFilm[indexPilih].judul);

                    if (pilihanFilm == 0) {
                        lihatDetailFilm(listFilm[indexPilih].id);
                    } else if (pilihanFilm == 1) {
                        system("cls"); cetakJudul("Edit Film");
                        cout << KUNING << " (kosong = tidak diubah)" << RESET << endl << endl;
                        cin.ignore(); bersihBuffer();
                        string inputBaru;

                        cout << KUNING << " judul  [" << listFilm[indexPilih].judul  << "]: " << RESET;
                        getline(cin, inputBaru);
                        if (!inputBaru.empty()) listFilm[indexPilih].judul = inputBaru;

                        bersihBuffer();
                        cout << KUNING << " studio [" << listFilm[indexPilih].studio << "]: " << RESET;
                        getline(cin, inputBaru);
                        if (!inputBaru.empty()) listFilm[indexPilih].studio = inputBaru;

                        bersihBuffer();
                        cout << KUNING << " tahun  [" << listFilm[indexPilih].tahun  << "]: " << RESET;
                        getline(cin, inputBaru);
                        if (!inputBaru.empty()) {
                            try { listFilm[indexPilih].tahun = stoi(inputBaru); } catch (...) {}
                        }

                        cout << endl << HIJAU << TEBAL << " film diupdate!" << RESET << endl;
                        tekanEnter();
                    } else if (pilihanFilm == 2) {
                        string opsiHapus[] = {"ya hapus", "batal"};
                        if (pilihMenu(opsiHapus, 2, "Hapus Film?") == 0) {
                            hapusFilm(listFilm[indexPilih].id);
                            system("cls");
                            cout << endl << HIJAU << TEBAL << " film dihapus" << RESET << endl;
                            tekanEnter();
                        }
                    }
                } else {
                    lihatDetailFilm(listFilm[indexPilih].id);
                }
            }
        } else break;
    }
}

#endif