#include <iostream>
#include "../include/Data_Base.h"
#include "../sqlite/sqlite3.h"  


using namespace std;

Database::Database(const string &db_name) {
    if (sqlite3_open(db_name.c_str(), &db) != SQLITE_OK) {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        db = nullptr;
    }
}

Database::~Database() {
    if (db) {
        sqlite3_close(db);
    }
}

bool Database::execute(const string &query) {
    char *errMsg = nullptr;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

void Database::createTables() {
    string createUsersTable = "CREATE TABLE IF NOT EXISTS Users ("
                                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                    "name TEXT NOT NULL, "
                                    "email TEXT NOT NULL UNIQUE);";

    string createGamesTable = "CREATE TABLE IF NOT EXISTS Games ("
                                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                    "title TEXT NOT NULL UNIQUE, "
                                    "genre TEXT NOT NULL);";

    string createUsersGamesTable = "CREATE TABLE IF NOT EXISTS Users_Games ("
                                        "user_id INTEGER, "
                                        "game_id INTEGER, "
                                        "FOREIGN KEY(user_id) REFERENCES Users(id), "
                                        "FOREIGN KEY(game_id) REFERENCES Games(id));";

    if (execute(createUsersTable) &&
        execute(createGamesTable) &&
        execute(createUsersGamesTable)) {
        cout << "Tables created successfully." << endl;
    } else {
        cout << "Error creating tables." << endl;
    }
}

void Database::insertUser(const string &name, const string &email) {
    string query = "INSERT INTO Users (name, email) VALUES ('" + name + "', '" + email + "');";
    if (execute(query)) {
        cout << "User added successfully." << endl;
    } else {
        cout << "Error adding user." << endl;
    }
}

void Database::insertGame(const string &title, const string &genre) {
    string query = "INSERT INTO Games (title, genre) VALUES ('" + title + "', '" + genre + "');";
    if (execute(query)) {
        cout << "Game added successfully." << endl;
    } else {
        cout << "Error adding game." << endl;
    }
}

void Database::listUsers() {
    string query = "SELECT * FROM Users;";
    sqlite3_stmt *stmt;
    
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char *name = sqlite3_column_text(stmt, 1);
            const unsigned char *email = sqlite3_column_text(stmt, 2);
            cout << "ID: " << id << ", Name: " << name << ", Email: " << email << endl;
        }
        sqlite3_finalize(stmt);
    } else {
        cerr << "Error listing users." << endl;
    }
}

void Database::listGames() {
    string query = "SELECT * FROM Games;";
    sqlite3_stmt *stmt;
    
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char *title = sqlite3_column_text(stmt, 1);
            const unsigned char *genre = sqlite3_column_text(stmt, 2);
            cout << "ID: " << id << ", Title: " << title << ", Genre: " << genre << endl;
        }
        sqlite3_finalize(stmt);
    } else {
        cerr << "Error listing games." << endl;
    }
}

void Database::associateUserGame(int userId, int gameId) {
    string query = "INSERT INTO Users_Games (user_id, game_id) VALUES (" +
                        to_string(userId) + ", " + to_string(gameId) + ");";
    if (execute(query)) {
        cout << "User associated with game successfully." << endl;
    } else {
        cout << "Error associating user with game." << endl;
    }
}

void Database::desassociateUserGame(int userId, int gameId) {
    string query = "DELETE FROM Users_Games WHERE user_id = " + to_string(userId) +
                    " AND game_id = " + to_string(gameId) + ";";
    if (execute(query)) {
        cout << "User disassociated from game successfully." << endl;
    } else {
        cout << "Error disassociating user from game." << endl;
    }
}

bool Database::listGamesByUser(int userId) {
    string query = "SELECT Users.name, Games.title, Games.genre "
                        "FROM Users "
                        "JOIN Users_Games ON Users.id = Users_Games.user_id "
                        "JOIN Games ON Games.id = Users_Games.game_id "
                        "WHERE Users.id = " + to_string(userId) + ";";

    char *errMsg = nullptr;
    auto callback = [](void*, int argc, char **argv, char **colName) -> int {
        for (int i = 0; i < argc; i++) {
            cout << colName[i] << ": " << (argv[i] ? argv[i] : "NULL") << "\n";
        }
        cout << endl;
        return 0;
    };

    if (sqlite3_exec(db, query.c_str(), callback, nullptr, &errMsg) != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

bool Database::listUsersByGame(int gameId) {
    string query = "SELECT Games.title, Users.name, Users.email "
                        "FROM Games "
                        "JOIN Users_Games ON Games.id = Users_Games.game_id "
                        "JOIN Users ON Users.id = Users_Games.user_id "
                        "WHERE Games.id = " + to_string(gameId) + ";";

    char *errMsg = nullptr;
    auto callback = [](void*, int argc, char **argv, char **colName) -> int {
        for (int i = 0; i < argc; i++) {
            cout << colName[i] << ": " << (argv[i] ? argv[i] : "NULL") << "\n";
        }
        cout << endl;
        return 0;
    };

    if (sqlite3_exec(db, query.c_str(), callback, nullptr, &errMsg) != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}
