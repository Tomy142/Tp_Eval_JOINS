g++ -Wall -std=c++17 -I.\include -I.\sqlite -o .\build\ms_windows\dbh_example.exe main.cpp src\Menu.cpp src\MenuFunctions.cpp src\Data_Base.cpp -L.\lib -lsqlite3


cd build\ms_windows\
dbh_example.exe
