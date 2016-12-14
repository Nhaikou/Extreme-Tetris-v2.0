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
	errorMessages();
}

void DataBase::insertToDataBase(std::vector<Player*> *players)
{
	/*Insert in to database*/

	std::stringstream ss;

	for (int i = 0; i < players->size(); i++)
	{
		deleteFromDataBase(players->at(i)->playerName);
		ss << "INSERT INTO HIGHSCORE (PLAYER, SCORE)" << "VALUES ('" << players->at(i)->playerName << "', " << players->at(i)->score.y << ");";
	}

	/* Execute SQL statement */
	rc = sqlite3_exec(dataBase, ss.str().c_str(), callBack, 0, &errorMsg);
	errorMessages();
}

void DataBase::updateDataBase(Player *player)
{
	/*Update database*/

	std::stringstream ss;

	ss << "UPDATE HIGHSCORE set SCORE = " << player->score.y << " where PLAYER='" << player->playerName << "'; SELECT * from HIGHSCORE";

	/* Execute SQL statement */
	rc = sqlite3_exec(dataBase, ss.str().c_str(), callBack, (void*)data, &errorMsg);
	errorMessages();
}

void DataBase::deleteFromDataBase(std::string name)
{
	/*Delete from database*/

	std::stringstream ss;

	ss << "DELETE from HIGHSCORE where PLAYER='" << name << "'; SELECT * from HIGHSCORE";

	/* Execute SQL statement */
	rc = sqlite3_exec(dataBase, ss.str().c_str(), callBack, (void*)data, &errorMsg);
	errorMessages();
}

void DataBase::errorMessages()
{
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", errorMsg);
		sqlite3_free(errorMsg);
	}
	else
	{
		fprintf(stdout, "Operation done successfully\n");
	}
}

void DataBase::closeDataBase()
{
	sqlite3_close(dataBase);
}

int DataBase::callBack(void *data, int argc, char **argv, char **azColName)
{
	fprintf(stderr, "%s: ", (const char*)data);
	for (int i = 0; i < argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}