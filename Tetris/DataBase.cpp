#include "DataBase.h"


DataBase::DataBase()
{
}


DataBase::~DataBase()
{
}

void DataBase::openDataBase()
{
	/* Open database */
	rc = sqlite3_open("Highscore.db", &dataBase);
	if (rc)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(dataBase));
		return;
	}
	else
	{
		fprintf(stdout, "Opened database successfully\n");
	}

	/* Create SQL statement */
	sql = "CREATE TABLE HIGHSCORE("  \
		"PLAYER		      TEXT    NOT NULL," \
		"SCORE            INT     NOT NULL );";

	/* Execute SQL statement */
	rc = sqlite3_exec(dataBase, sql, callBack, 0, &errorMsg);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", errorMsg);
		sqlite3_free(errorMsg);
	}
	else
	{
		fprintf(stdout, "Table created successfully\n");
	}
}

void DataBase::insertToDataBase(std::vector<Player*> *players)
{
	/*Insert in to database*/

	std::stringstream ss;

	for (int i = 0; i < players->size(); i++)
	{
		ss << "INSERT INTO HIGHSCORE (PLAYER, SCORE)" << "VALUES ('" << players->at(i)->playerName << "', " << players->at(i)->score.y << ");";
	}

	sql = "INSERT INTO HIGHSCORE (PLAYER, SCORE)"
		"VALUES ('Player1', 1400);";

	/* Execute SQL statement */
	rc = sqlite3_exec(dataBase, ss.str().c_str(), callBack, 0, &errorMsg);
	if (rc != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", errorMsg);
		sqlite3_free(errorMsg);
	}
	else{
		fprintf(stdout, "Records created successfully\n");
	}
}

void DataBase::closeDataBase()
{
	sqlite3_close(dataBase);
}

int DataBase::callBack(void *data, int argc, char **argv, char **azColName)
{
	for (int i = 0; i < argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}