#ifndef KOLEKSI_H
#define KOLEKSI_H

#include "film.h"
#include "loginregis.h"
#include <limits>

string keHurufKecil(string teks)
{
    for (int i = 0; i < teks.size(); i++)
    {
        if (teks[i] >= 'A' && teks[i] <= 'Z')
        {
            teks[i] = teks[i] + 32;
        }
    }
    return teks;
}

bool teksKosongAtauSpasiKhusus(const string &teks)
{
    if (teks.empty())
    {
        return true;
    }

    for (int i = 0; i < teks.size(); i++)
    {
        if (teks[i] != ' ' && teks[i] != '\t')
        {
            return false;
        }
    }
    return true;
}

int cariIndexFilmBerdasarkanId(int idFilm)
{
    for (int i = 0; i < totalFilm; i++)
    {
        if (listFilm[i].id == idFilm)
        {
            return i;
        }
    }
    return -1;
}

int cariIndexReviewUserFilm(int idUser, int idFilm)
{
    for (int i = 0; i < totalReview; i++)
    {
        if (listReview[i].idUser == idUser && listReview[i].idFilm == idFilm)
        {
            return i;
        }
    }
    return -1;
}

int cariIndexFavoritUserFilm(int idUser, int idFilm)
{
    for (int i = 0; i < totalFavorit; i++)
    {
        if (listFavorit[i].idUser == idUser && listFavorit[i].idFilm == idFilm)
        {
            return i;
        }
    }
    return -1;
}

int cariIndexUserBerdasarkanUsername(const string &usernameCari)
{
    for (int i = 0; i < totalUser; i++)
    {
        if (listUser[i].username == usernameCari)
        {
            return i;
        }
    }
    return -1;
}

bool usernameSudahDigunakanOlehUserLain(const string &usernameBaru, int idUserSekarang)
{
    for (int i = 0; i < totalUser; i++)
    {
        if (listUser[i].username == usernameBaru && listUser[i].id != idUserSekarang)
        {
            return true;
        }
    }
    return false;
}

void tampilkanDetailReview(int indexReview)
{
    if (indexReview < 0 || indexReview >= totalReview)
    {
        cout << MERAH << " data review tidak valid" << RESET << endl;
        tekanEnter();
        return;
    }

    int indexFilm = cariIndexFilmBerdasarkanId(listReview[indexReview].idFilm);

    system("cls");
    cetakJudul("Detail Review");

    if (indexFilm != -1)
    {
        cout << CYAN << " judul film : " << RESET << listFilm[indexFilm].judul << endl;
        cout << CYAN << " tahun      : " << RESET << listFilm[indexFilm].tahun << endl;
    }
    else
    {
        cout << MERAH << " judul film : data film tidak ditemukan" << RESET << endl;
    }

    cout << CYAN << " rating     : " << RESET << listReview[indexReview].rating << "/10" << endl;
    cout << CYAN << " ulasan     : " << RESET << listReview[indexReview].ulasan << endl;

    tekanEnter();
}

void menuFavorit()
{
    while (true)
    {
        system("cls");
        cetakJudul("Film Favorit");

        Film filmFav[MAX * 4];
        int totalFav = 0;

        for (int i = 0; i < totalFavorit; i++)
        {
            if (listFavorit[i].idUser == userAktif->id)
            {
                int indexFilm = cariIndexFilmBerdasarkanId(listFavorit[i].idFilm);
                if (indexFilm != -1)
                {
                    bool sudahMasuk = false;
                    for (int j = 0; j < totalFav; j++)
                    {
                        if (filmFav[j].id == listFilm[indexFilm].id)
                        {
                            sudahMasuk = true;
                            break;
                        }
                    }

                    if (!sudahMasuk)
                    {
                        filmFav[totalFav] = listFilm[indexFilm];
                        totalFav++;
                    }
                }
            }
        }

        for (int i = 0; i < totalFav - 1; i++)
        {
            for (int j = 0; j < totalFav - i - 1; j++)
            {
                if (keHurufKecil(filmFav[j].judul) > keHurufKecil(filmFav[j + 1].judul))
                {
                    Film temp = filmFav[j];
                    filmFav[j] = filmFav[j + 1];
                    filmFav[j + 1] = temp;
                }
            }
        }

        if (totalFav == 0)
        {
            cout << KUNING << " belum ada favorit" << RESET << endl;
        }
        else
        {
            for (int i = 0; i < totalFav; i++)
            {
                cout << CYAN << " [" << i + 1 << "] " << RESET
                    << filmFav[i].judul << " (" << filmFav[i].tahun << ")"
                    << KUNING << " - " << rataRating(filmFav[i].id) << "/10" << RESET << endl;
            }
        }

        string opsi[] = {"buka detail film", "kembali"};
        int pil = pilihMenu(opsi, 2, "Film Favorit");

        if (pil == 0)
        {
            if (totalFav == 0)
            {
                cout << MERAH << " belum ada favorit" << RESET << endl;
                tekanEnter();
                continue;
            }

            cout << KUNING << " nomor film: " << RESET;

            string input;
            getline(cin, input);

            if (teksKosongAtauSpasiKhusus(input))
            {
                cout << MERAH << " input tidak boleh kosong" << RESET << endl;
                tekanEnter();
                continue;
            }

            bool validAngka = true;

            for (int i = 0; i < input.length(); i++)
            {
                if (!isdigit(input[i]))
                {
                    validAngka = false;
                    break;
                }
            }

            if (!validAngka)
            {
                cout << MERAH << " input harus berupa angka" << RESET << endl;
                tekanEnter();
                continue;
            }

            int nomorPilih = stoi(input);

            if (nomorPilih >= 1 && nomorPilih <= totalFav)
            {
                lihatDetailFilm(filmFav[nomorPilih - 1].id);
            }
            else
            {
                cout << MERAH << " nomor tidak valid" << RESET << endl;
                tekanEnter();
            }
        }
        else
        {
            break;
        }
    }
}

void menuHistory()
{
    while (true)
    {
        system("cls");
        cetakJudul("History Review");

        int indexHistory[MAX * 4];
        int totalHistory = 0;

        for (int i = 0; i < totalReview; i++)
        {
            if (listReview[i].idUser == userAktif->id)
            {
                indexHistory[totalHistory] = i;
                totalHistory++;
            }
        }

        if (totalHistory == 0)
        {
            cout << KUNING << " belum ada history review" << RESET << endl;
        }
        else
        {
            for (int i = 0; i < totalHistory; i++)
            {
                int indexFilm = cariIndexFilmBerdasarkanId(listReview[indexHistory[i]].idFilm);

                cout << CYAN << " [" << i + 1 << "] " << RESET;

                if (indexFilm != -1)
                {
                    cout << listFilm[indexFilm].judul;
                }
                else
                {
                    cout << "film tidak ditemukan";
                }

                cout << KUNING << " - " << listReview[indexHistory[i]].rating << "/10" << RESET << endl;
            }
        }

        string opsi[] = {"lihat detail review", "kembali"};
        int pil = pilihMenu(opsi, 2, "History Review");

        if (pil == 0)
        {
            if (totalHistory == 0)
            {
                cout << MERAH << " belum ada history review" << RESET << endl;
                tekanEnter();
                continue;
            }

            cout << KUNING << " nomor review: " << RESET;
                    
            string input;
            getline(cin, input);
                    
            if (teksKosongAtauSpasiKhusus(input))
            {
                cout << MERAH << " input tidak boleh kosong" << RESET << endl;
                tekanEnter();
                continue;
            }
            
            bool validAngka = true;
            
            for (int i = 0; i < input.length(); i++)
            {
                if (!isdigit(input[i]))
                {
                    validAngka = false;
                    break;
                }
            }
            
            if (!validAngka)
            {
                cout << MERAH << " input harus berupa angka" << RESET << endl;
                tekanEnter();
                continue;
            }
            
            int nomorPilih = stoi(input);

            if (nomorPilih >= 1 && nomorPilih <= totalHistory)
            {
                tampilkanDetailReview(indexHistory[nomorPilih - 1]);
            }
            else
            {
                cout << MERAH << " nomor tidak valid" << RESET << endl;
                tekanEnter();
            }
        }
        else
        {
            break;
        }
    }
}

void menuAkun()
{
    while (true)
    {
        system("cls");
        cetakJudul("Akun Saya");

        cout << CYAN << " username : " << RESET << userAktif->username << endl;
        cout << CYAN << " role     : " << RESET << userAktif->role << endl << endl;

        string opsi[] = {"ganti username", "ganti password", "kembali"};
        int pil = pilihMenu(opsi, 3, "Akun Saya");

        if (pil == 0)
        {
            system("cls");
            cetakJudul("Ganti Username");

            cout << KUNING << " username baru: " << RESET;
            string usernameBaru = bacaInputBaris();

            if (teksKosongAtauSpasiKhusus(usernameBaru))
            {
                cout << MERAH << " username tidak boleh kosong" << RESET << endl;
                tekanEnter();
                continue;
            }

            if (usernameSudahDigunakanOlehUserLain(usernameBaru, userAktif->id))
            {
                cout << MERAH << " username sudah dipakai" << RESET << endl;
                tekanEnter();
                continue;
            }

            userAktif->username = usernameBaru;

            cout << HIJAU << TEBAL << " username berhasil diganti" << RESET << endl;
            tekanEnter();
        }
        else if (pil == 1)
        {
            system("cls");
            cetakJudul("Ganti Password");

            cout << KUNING << " password lama: " << RESET;
            string passwordLama = bacaInputBaris();

            if (passwordLama != userAktif->password)
            {
                cout << MERAH << " password lama salah" << RESET << endl;
                tekanEnter();
                continue;
            }

            cout << KUNING << " password baru: " << RESET;
            string passwordBaru = bacaInputBaris();

            if (teksKosongAtauSpasiKhusus(passwordBaru))
            {
                cout << MERAH << " password tidak boleh kosong" << RESET << endl;
                tekanEnter();
                continue;
            }

            cout << KUNING << " konfirmasi password baru: " << RESET;
            string konfirmasiPassword = bacaInputBaris();

            if (passwordBaru != konfirmasiPassword)
            {
                cout << MERAH << " password baru dan konfirmasi tidak sama" << RESET << endl;
                tekanEnter();
                continue;
            }

            userAktif->password = passwordBaru;

            cout << HIJAU << TEBAL << " password berhasil diganti" << RESET << endl;
            tekanEnter();
        }
        else
        {
            break;
        }
    }
}

void menuKoleksi()
{
    while (true)
    {
        string opsi[] = {"favorit saya", "history review", "kembali"};
        int pil = pilihMenu(opsi, 3, "Koleksi Saya");

        if (pil == 0)
        {
            menuFavorit();
        }
        else if (pil == 1)
        {
            menuHistory();
        }
        else
        {
            break;
        }
    }
}

void menuUser()
{
    string opsi[] = {"daftar film", "koleksi saya", "akun saya", "logout"};

    while (true)
    {
        int pil = pilihMenu(opsi, 4, "Halo, " + userAktif->username + "!");

        if (pil == 0)
        {
            menuDaftarFilm();
        }
        else if (pil == 1)
        {
            menuKoleksi();
        }
        else if (pil == 2)
        {
            menuAkun();
        }
        else
        {
            system("cls");
            cout << endl << HIJAU << TEBAL << " sampai jumpa, " << userAktif->username << "!" << RESET << endl;
            userAktif = nullptr;
            tekanEnter();
            break;
        }
    }
}

#endif