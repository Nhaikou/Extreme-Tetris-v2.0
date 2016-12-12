#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>
#include "sqlite/sqlite3.h"
#include <string>
#include <sstream>
#include <iostream>
#include "Player.h"

class DataBase
{
public:
	DataBase();
	~DataBase();

	void openDataBase();
	void insertToDataBase(std::vector<Player*> *players);
	void closeDataBase();
	static int callBack(void *data, int argc, char **argv, char **azColName);

private:
	sqlite3 *dataBase;
	char *errorMsg = 0;
	char *sql;
	int rc = 0;

};
#endif;

