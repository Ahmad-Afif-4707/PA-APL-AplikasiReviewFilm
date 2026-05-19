#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <limits>
using namespace std;

#define RESET "\033[0m"
#define HIJAU "\033[32m"
#define KUNING "\033[33m"
#define CYAN "\033[36m"
#define MERAH "\033[31m"
#define TEBAL "\033[1m"

#define MAX 50

struct User
{
    int id;
    string username;
    string password;
    string role;
};

struct Film
{
    int id;
    string judul;
    int tahun;
    string studio;
};

struct Review
{
    int idUser;
    int idFilm;
    int rating;
    string ulasan;
};

struct Favorit
{
    int idUser;
    int idFilm;
};

struct Usulan
{
    int id;
    string judul;
    int idUser;
};

User listUser[MAX];
Film listFilm[MAX];
Review listReview[MAX * 4];
Favorit listFavorit[MAX * 4];
Usulan listUsulan[MAX];

int totalUser = 0;
int totalFilm = 0;
int totalReview = 0;
int totalFavorit = 0;
int totalUsulan = 0;

int idUserBaru = 1;
int idFilmBaru = 1;
int idUsulanBaru = 1;

User *userAktif = nullptr;

void bersihBuffer()
{
    cin.clear();
    cin.sync();
}

string bacaInputBaris()
{
    if (cin.peek() == '\n')
    {
        cin.get();
    }

    string input;
    getline(cin, input);
    return input;
}

bool hanyaAngka(const string &teks)
{
    if (teks.empty())
    {
        return false;
    }

    for (int i = 0; i < teks.size(); i++)
    {
        if (!isdigit(teks[i]))
        {
            return false;
        }
    }
    return true;
}

void updateTeksJikaDiisi(string &target)
{
    string inputBaru = bacaInputBaris();
    if (!inputBaru.empty())
    {
        target = inputBaru;
    }
}

bool updateAngkaJikaDiisi(int &target)
{
    string inputBaru = bacaInputBaris();
    if (inputBaru.empty())
    {
        return true;
    }

    if (!hanyaAngka(inputBaru))
    {
        return false;
    }

    target = stoi(inputBaru);
    return true;
}

Film *cariFilm(int id)
{
    for (int i = 0; i < totalFilm; i++)
    {
        if (listFilm[i].id == id)
        {
            return &listFilm[i];
        }
    }
    return nullptr;
}

int rataRating(int idFilm)
{
    int total = 0;
    int jumlah = 0;
    for (int i = 0; i < totalReview; i++)
    {
        if (listReview[i].idFilm == idFilm)
        {
            total = total + listReview[i].rating;
            jumlah++;
        }
    }
    if (jumlah == 0)
        return 0;
    return total / jumlah;
}

bool sudahFavorit(int idUser, int idFilm)
{
    for (int i = 0; i < totalFavorit; i++)
    {
        if (listFavorit[i].idUser == idUser && listFavorit[i].idFilm == idFilm)
        {
            return true;
        }
    }
    return false;
}

void hapusDariFavorit(int idUser, int idFilm)
{
    for (int i = 0; i < totalFavorit; i++)
    {
        if (listFavorit[i].idUser == idUser && listFavorit[i].idFilm == idFilm)
        {
            for (int g = i; g < totalFavorit - 1; g++)
            {
                listFavorit[g] = listFavorit[g + 1];
            }
            totalFavorit--;
            return;
        }
    }
}

void hapusReviewDi(int idx)
{
    for (int g = idx; g < totalReview - 1; g++)
    {
        listReview[g] = listReview[g + 1];
    }
    totalReview--;
}

void hapusFilm(int idFilm)
{
    for (int i = 0; i < totalReview;)
    {
        if (listReview[i].idFilm == idFilm)
        {
            hapusReviewDi(i);
        }
        else
        {
            i++;
        }
    }
    for (int i = 0; i < totalFavorit;)
    {
        if (listFavorit[i].idFilm == idFilm)
        {
            for (int g = i; g < totalFavorit - 1; g++)
            {
                listFavorit[g] = listFavorit[g + 1];
            }
            totalFavorit--;
        }
        else
        {
            i++;
        }
    }
    for (int i = 0; i < totalFilm; i++)
    {
        if (listFilm[i].id == idFilm)
        {
            for (int g = i; g < totalFilm - 1; g++)
            {
                listFilm[g] = listFilm[g + 1];
            }
            totalFilm--;
            return;
        }
    }
}

void hapusUser(int idUser)
{
    for (int i = 0; i < totalReview;)
    {
        if (listReview[i].idUser == idUser)
        {
            hapusReviewDi(i);
        }
        else
        {
            i++;
        }
    }
    for (int i = 0; i < totalFavorit;)
    {
        if (listFavorit[i].idUser == idUser)
        {
            for (int g = i; g < totalFavorit - 1; g++)
            {
                listFavorit[g] = listFavorit[g + 1];
            }
            totalFavorit--;
        }
        else
        {
            i++;
        }
    }
    for (int i = 0; i < totalUsulan;)
    {
        if (listUsulan[i].idUser == idUser)
        {
            for (int g = i; g < totalUsulan - 1; g++)
            {
                listUsulan[g] = listUsulan[g + 1];
            }
            totalUsulan--;
        }
        else
        {
            i++;
        }
    }
    for (int i = 0; i < totalUser; i++)
    {
        if (listUser[i].id == idUser)
        {
            for (int g = i; g < totalUser - 1; g++)
            {
                listUser[g] = listUser[g + 1];
            }
            totalUser--;
            return;
        }
    }
}
#endif
