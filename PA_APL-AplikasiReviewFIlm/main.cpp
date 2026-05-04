#include "koleksi.h"

int main() {
    listUser[totalUser].id       = idUserBaru++;
    listUser[totalUser].username = "user";
    listUser[totalUser].password = "user123";
    totalUser++;

    while (true) {
        string opsi[] = {"login", "keluar"};
        int pil = pilihMenu(opsi, 2, "Review Film & Serial");

        if (pil == 0) {
            userAktif = prosesLogin();
            if (userAktif != nullptr)
                menuUser();

        } else {
            system("cls");
            cout << endl << CYAN;
            cetakGaris('=', 42);
            cout << " " << KUNING << "makasih sudah pake aplikasinya!" << RESET << endl;
            cout << CYAN; cetakGaris('=', 42);
            cout << RESET << endl << endl;
            break;
        }
    }
    return 0;
}