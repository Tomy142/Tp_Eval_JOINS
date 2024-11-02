#include <iostream>
#include "../include/MenuFunctions.h"

using namespace std;

void insertUser(Database &db, const string &name, const string &email) {
    db.insertUser(name, email);
}

void insertGame(Database &db, const string &title, const string &genre) {
    db.insertGame(title, genre);
}

void listUsers(Database &db) {
    db.listUsers();
}

void listGames(Database &db) {
    db.listGames();
}

void associateUserGame(Database &db, int userId, int gameId) {
    db.associateUserGame(userId, gameId);
}

void desassociateUserGame(Database &db, int userId, int gameId) {
    db.desassociateUserGame(userId, gameId);
}

bool listGamesByUser(Database &db, int userId) {
    return db.listGamesByUser(userId);
}

bool listUsersByGame(Database &db, int gameId) {
    return db.listUsersByGame(gameId);
}

// g++ -Wall -std=c++17 -I.\include -o .\build\ms_windows\dbh_example.exe main.cpp src\Menu.cpp src\MenuFunctions.cpp src\Data_Base.cpp -L.\lib -lsqlite3