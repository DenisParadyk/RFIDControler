#pragma once
#include <string>
#include <iostream>
#include "sqlite3.h"

using namespace std;

enum DbError
{
	DbErrorOk,
	DbErrorCreateDb,
	DbErrorOpenDb,
	DbErrorCreateTable,
	DbErrorWriteTable
};

class Db
{
public:
	Db(string db);

	DbError open();
	DbError create();
	DbError mainFunc(string name, string secondname, string date, string time);
    DbError subFunc(string id, string name, string secondname, string login, string password);
    DbError select(string id, string& name, string& secondname, string& login, string& password);
private:
	string dbName;
	sqlite3 *db;

};
