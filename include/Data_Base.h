#ifndef DATA_BASE_H
#define DATA_BASE_H

#include "../sqlite/sqlite3.h"
#include <string>

using namespace std;

class Database {
    public:
        Database(const string &db_name);
        ~Database();
        bool execute(const string &query);
        sqlite3* getDB() const { return db; }

        void createTables();
        void insertUser(const string &name, const string &email);
        void insertGame(const string &title, const string &genre);
        void listUsers();
        void listGames();
        void associateUserGame(int userId, int gameId);
        void desassociateUserGame(int userId, int gameId);
        bool listGamesByUser(int userId);
        bool listUsersByGame(int gameId);

    private: 
        sqlite3 *db;
};

#endif
