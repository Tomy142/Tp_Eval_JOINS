#include <iostream>
#include "../include/Menu.h"
#include "../include/MenuFunctions.h"
#include "Data_Base.h"  


using namespace std;

void Menu::displayMenu(Database &db) {
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add User\n";
        cout << "2. Add Game\n";
        cout << "3. List Users\n";
        cout << "4. List Games\n";
        cout << "5. Associate User with Game\n";
        cout << "6. Disassociate User from Game\n";
        cout << "7. List Games by User\n";
        cout << "8. List Users by Game\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string name, email;
                cout << "Enter name: ";
                getline(cin, name);
                cout << "Enter email: ";
                getline(cin, email);
                insertUser(db, name, email);
                system("pause");
                system("cls");
                break;
                
            }
            case 2: {
                string title, genre;
                cout << "Enter title: ";
                getline(cin, title);
                cout << "Enter genre: ";
                getline(cin, genre);
                insertGame(db, title, genre);
                system("pause");
                system("cls");
                break;
            }
            case 3:
                listUsers(db);
                system("pause");
                system("cls");
                break;
            case 4:
                listGames(db);
                system("pause");
                system("cls");
                break;
            case 5: {
                int userId, gameId;
                cout << "Enter user ID: ";
                cin >> userId;
                cout << "Enter game ID: ";
                cin >> gameId;
                associateUserGame(db, userId, gameId);
                system("pause");
                system("cls");
                break;
            }
            case 6: {
                int userId, gameId;
                cout << "Enter user ID: ";
                cin >> userId;
                cout << "Enter game ID: ";
                cin >> gameId;
                desassociateUserGame(db, userId, gameId);
                system("pause");
                system("cls");
                break;
            }
            case 7: {
                int userId;
                cout << "Enter user ID: ";
                cin >> userId;
                listGamesByUser(db, userId);
                system("pause");
                system("cls");
                break;
            }
            case 8: {
                int gameId;
                cout << "Enter game ID: ";
                cin >> gameId;
                listUsersByGame(db, gameId);
                system("pause");
                system("cls");
                break;
            }
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid option. Try again." << endl;
        }
    } while (choice != 0);
}
