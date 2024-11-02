#ifndef MENUFUNCTIONS_H
#define MENUFUNCTIONS_H

#include "Data_Base.h"
#include <string>

void insertUser(Database &db, const std::string &name, const std::string &email);
void insertGame(Database &db, const std::string &title, const std::string &genre);
void listUsers(Database &db);
void listGames(Database &db);
void associateUserGame(Database &db, int userId, int gameId);
void desassociateUserGame(Database &db, int userId, int gameId);
bool listGamesByUser(Database &db, int userId);
bool listUsersByGame(Database &db, int gameId);

#endif
