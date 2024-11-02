#include "include/Data_Base.h"
#include "include/Menu.h"

int main() {
    Database db("games.db");
    db.createTables();

    Menu::displayMenu(db);  // Solo se llama al menú

    return 0;
}
