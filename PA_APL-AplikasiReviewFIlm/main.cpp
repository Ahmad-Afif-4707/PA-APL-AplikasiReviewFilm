#include "koleksi.h"
#include "usulan.h"

int main()
{
    // === DATA DUMMY USER ===
    if (totalUser == 0)
    {
        listUser[totalUser].id = idUserBaru++;
        listUser[totalUser].username = "admin";
        listUser[totalUser].password = "admin123";
        listUser[totalUser].role = "admin";
        totalUser++;

        listUser[totalUser].id = idUserBaru++;
        listUser[totalUser].username = "user";
        listUser[totalUser].password = "user123";
        listUser[totalUser].role = "user";
        totalUser++;
    }

    // === DATA DUMMY FILM ===
    listFilm[totalFilm++] = {idFilmBaru++, "Star Wars: A New Hope",              1977, "Lucasfilm"};
    listFilm[totalFilm++] = {idFilmBaru++, "The Lord of the Rings: Fellowship",  2001, "New Line Cinema"};
    listFilm[totalFilm++] = {idFilmBaru++, "The Hobbit: An Unexpected Journey",  2012, "New Line Cinema"};
    listFilm[totalFilm++] = {idFilmBaru++, "Avengers: Endgame",                  2019, "Marvel Studios"};
    listFilm[totalFilm++] = {idFilmBaru++, "Harry Potter and the Sorcerer Stone",2001, "Warner Bros"};

    // === DATA DUMMY REVIEW ===
    listReview[totalReview++] = {2, 1, 9, "Klasik banget, fondasi semua sci-fi!"};
    listReview[totalReview++] = {2, 2, 10, "Sinematografi dan ceritanya luar biasa!"};
    listReview[totalReview++] = {2, 3, 8, "Seru tapi agak lebih ringan dari LOTR."};
    listReview[totalReview++] = {2, 4, 10, "Ending yang memuaskan untuk saga Avengers!"};
    listReview[totalReview++] = {2, 5, 9, "Magis dan nostalgik, selalu enak ditonton."};

    menuAwal();
    return 0;
}