#include "koleksi.h"
#include "kelolafilm.h"
#include "kelolauser.h"

void menuAdmin()
{
    while (true)
    {
        string opsi[] = {"kelola film", "kelola user", "logout"};
        int pil = pilihMenu(opsi, 3, "Admin, " + userAktif->username + "!");

        if (pil == 0)
        {
            menuKelolaFilm();
        }
        else if (pil == 1)
        {
            menuKelolaUser();
        }
        else
        {
            system("cls");
            cout << endl
                 << HIJAU << TEBAL << " sampai jumpa, " << userAktif->username << "!" << RESET << endl;
            userAktif = nullptr;
            tekanEnter();
            break;
        }
    }
}

int main()
{
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

    menuAwal();
    return 0;
}