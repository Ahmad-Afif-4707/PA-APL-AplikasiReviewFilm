#ifndef FILM_H
#define FILM_H

#include "detailfilm.h"

string ubahKeHurufKecil(string teks)
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

bool teksKosongAtauSpasi(const string &teks)
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

bool filmSudahAdaJudul(const string &judulDicari)
{
    string judulCariKecil = ubahKeHurufKecil(judulDicari);

    for (int i = 0; i < totalFilm; i++)
    {
        if (ubahKeHurufKecil(listFilm[i].judul) == judulCariKecil)
        {
            return true;
        }
    }
    return false;
}

bool usulanSudahAda(int idUserPengusul, const string &judulDicari)
{
    string judulCariKecil = ubahKeHurufKecil(judulDicari);

    for (int i = 0; i < totalUsulan; i++)
    {
        if (listUsulan[i].idUser == idUserPengusul &&
            ubahKeHurufKecil(listUsulan[i].judul) == judulCariKecil)
        {
            return true;
        }
    }
    return false;
}

void simpanUsulanFilm(const string &judulUsulan)
{
    if (teksKosongAtauSpasi(judulUsulan))
    {
        cout << MERAH << " judul usulan tidak boleh kosong" << RESET << endl;
        tekanEnter();
        return;
    }

    if (totalUsulan >= MAX)
    {
        cout << MERAH << " data usulan sudah penuh" << RESET << endl;
        tekanEnter();
        return;
    }

    if (filmSudahAdaJudul(judulUsulan))
    {
        cout << KUNING << " film itu sudah ada di daftar film" << RESET << endl;
        tekanEnter();
        return;
    }

    int idPengusul = 0;
    if (userAktif != nullptr)
    {
        idPengusul = userAktif->id;
    }

    if (usulanSudahAda(idPengusul, judulUsulan))
    {
        cout << KUNING << " usulan film yang sama sudah pernah kamu kirim" << RESET << endl;
        tekanEnter();
        return;
    }

    listUsulan[totalUsulan].id = idUsulanBaru++;
    listUsulan[totalUsulan].judul = judulUsulan;
    listUsulan[totalUsulan].idUser = idPengusul;
    totalUsulan++;

    cout << endl
         << HIJAU << TEBAL << " usulan film berhasil disimpan!" << RESET << endl;
    tekanEnter();
}

void menuDaftarFilm()
{
    while (true)
    {
        system("cls");
        cetakJudul("Daftar Film");

        if (totalFilm == 0)
        {
            cout << KUNING << " belum ada film" << RESET << endl;
        }
        else
        {
            for (int i = 0; i < totalFilm; i++)
            {
                cout << CYAN << " [" << i + 1 << "] " << RESET
                     << listFilm[i].judul << " (" << listFilm[i].tahun << ")"
                     << KUNING << " - " << rataRating(listFilm[i].id) << "/10" << RESET << endl;
            }
        }

        string opsi[] = {"cari film", "pilih dari list", "kembali"};
        int pil = pilihMenu(opsi, 3, "Daftar Film");

        if (pil == 0)
        {
            system("cls");
            cetakJudul("Cari Film");

            cout << KUNING << " ketik judul: " << RESET;
            string kataCari = bacaInputBaris();

            if (teksKosongAtauSpasi(kataCari))
            {
                cout << MERAH << " judul pencarian tidak boleh kosong" << RESET << endl;
                tekanEnter();
                continue;
            }

            int indexHasil[MAX];
            int totalHasil = 0;
            string kataCariKecil = ubahKeHurufKecil(kataCari);

            for (int i = 0; i < totalFilm; i++)
            {
                string judulKecil = ubahKeHurufKecil(listFilm[i].judul);

                if (judulKecil.find(kataCariKecil) != string::npos)
                {
                    indexHasil[totalHasil] = i;
                    totalHasil++;
                }
            }

            if (totalHasil == 0)
            {
                system("cls");
                cetakJudul("Film Tidak Ditemukan");

                cout << KUNING << " film tidak ditemukan" << RESET << endl << endl;

                string opsiUsulan[] = {"ya, usulkan film ini", "tidak"};
                int pilUsulan = pilihMenu(opsiUsulan, 2, "Usulkan ke Admin");

                if (pilUsulan == 0)
                {
                    system("cls");
                    cetakJudul("Usulkan Film");

                    cout << KUNING << " judul usulan [" << kataCari << "]: " << RESET;
                    string judulUsulan = bacaInputBaris();

                    if (teksKosongAtauSpasi(judulUsulan))
                    {
                        judulUsulan = kataCari;
                    }

                    simpanUsulanFilm(judulUsulan);
                }
                else
                {
                    cout << endl << KUNING << " usulan dibatalkan" << RESET << endl;
                    tekanEnter();
                }
            }
            else
            {
                system("cls");
                cetakJudul("Hasil Cari");

                for (int i = 0; i < totalHasil; i++)
                {
                    cout << CYAN << " [" << i + 1 << "] " << RESET
                         << listFilm[indexHasil[i]].judul
                         << " (" << listFilm[indexHasil[i]].tahun << ")" << endl;
                }

                cout << endl << KUNING << " pilih nomor (0 batal): " << RESET;
                int pilihanNomor = 0;

                if (!(cin >> pilihanNomor))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << MERAH << " input tidak valid" << RESET << endl;
                    tekanEnter();
                    continue;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (pilihanNomor == 0)
                {
                    continue;
                }

                if (pilihanNomor >= 1 && pilihanNomor <= totalHasil)
                {
                    lihatDetailFilm(listFilm[indexHasil[pilihanNomor - 1]].id);
                }
                else
                {
                    cout << MERAH << " nomor tidak valid" << RESET << endl;
                    tekanEnter();
                }
            }
        }
        else if (pil == 1)
        {
            if (totalFilm == 0)
            {
                cout << MERAH << " belum ada film" << RESET << endl;
                tekanEnter();
                continue;
            }

            cout << KUNING << " pilih nomor (0 batal): " << RESET;
            int pilihanNomor = 0;

            if (!(cin >> pilihanNomor))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << MERAH << " input tidak valid" << RESET << endl;
                tekanEnter();
                continue;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (pilihanNomor == 0)
            {
                continue;
            }

            if (pilihanNomor >= 1 && pilihanNomor <= totalFilm)
            {
                lihatDetailFilm(listFilm[pilihanNomor - 1].id);
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

#endif