#include "Db.h"

const char *sqlCreateTable[2] = {
	"CREATE TABLE IF NOT EXISTS RFIDControler (id INTEGER PRIMARY KEY, name STRING, secondname STRING, date STRING, time STRING);",
    "CREATE TABLE IF NOT EXISTS Information(id INTEGER PRIMARY KEY, idNrf STRING, name STRING, secondname STRING, login STRING, password STRING);"};

Db::Db(string db)
{
	dbName = db;
	this->db = NULL;
}

DbError Db::open()
{
	int rc;
	char *error;


	rc = sqlite3_open(dbName.c_str(), &db);
	if (rc && !db)
	{
		sqlite3_close(db);
        return DbErrorOpenDb;
	}

	return DbErrorOk;
}


DbError Db::create()
{
	char *error;
	int rc;

	for (int i = 0; i < 3; i++) {
		rc = sqlite3_exec(db, sqlCreateTable[i], NULL, NULL, &error);
		if (rc)
		{
			sqlite3_free(error);
			sqlite3_close(db);
			return DbErrorCreateTable;
		}
	}

	return DbErrorOk;
}

DbError Db::subFunc(string id, string name, string secondname, string login, string password)
{
	char *error;
	int rc;

	string sqlInsert = "INSERT INTO ";
	sqlInsert += "Information";
	sqlInsert += " VALUES(";
	sqlInsert += "NULL";
	sqlInsert += ",'";
	sqlInsert += id;
	sqlInsert += "','";
	sqlInsert += name;
	sqlInsert += "','";
	sqlInsert += secondname;
    sqlInsert += "','";
    sqlInsert += login;
    sqlInsert += "','";
    sqlInsert += password;
	sqlInsert += "');";

	rc = sqlite3_exec(db, sqlInsert.c_str(), NULL, NULL, &error);

	if (rc)
	{
		sqlite3_free(error);
		sqlite3_close(db);
		return DbErrorWriteTable;
	}
	return DbErrorOk;
}

 
DbError Db::select(string id, string &name, string &secondname, string& login, string& password)
{
    string table;
	char *error;
	int rc;
	sqlite3_stmt *ppStmt;

	string sqlInsert = "SELECT * FROM ";
	sqlInsert += "Information WHERE idNrf = '";
	sqlInsert += id;
    sqlInsert += "'";

	if (sqlite3_prepare_v2(db, sqlInsert.c_str(), -1, &ppStmt, NULL) != SQLITE_OK)
	{
		sqlite3_close(db);
		return DbErrorWriteTable;			
	}

	sqlite3_step(ppStmt);

	for (int jj = 0; jj < sqlite3_column_count(ppStmt); jj++) {
		switch (sqlite3_column_type(ppStmt, jj))
		{
		case SQLITE_INTEGER: cout << sqlite3_column_int(ppStmt, jj) << endl;
			break;
		case SQLITE_FLOAT:   cout << sqlite3_column_double(ppStmt, jj) << endl;
			break;
		case SQLITE_TEXT:    
			
			cout << sqlite3_column_text(ppStmt, jj) << endl;
			name = (char*)sqlite3_column_text(ppStmt, 2);
			secondname = (char*)sqlite3_column_text(ppStmt, 3);
            login = (char*)sqlite3_column_text(ppStmt, 4);
            password = (char*)sqlite3_column_text(ppStmt, 5);

			break;
		case SQLITE_BLOB:    cout << "BLOB " << endl;
			cout << "Size of blob: " << sqlite3_column_bytes(ppStmt, jj) << endl;
			struct tm *blobRetreived;
			blobRetreived = (struct tm *) sqlite3_column_blob(ppStmt, jj);
			cout << "Year retrieved from blob: " << blobRetreived->tm_year + 1900 << endl;
			break;
		case SQLITE_NULL:    cout << "NULL " << endl;
			break;
		default: cout << "default " << endl;
			break;
		}
	}
	return DbErrorOk;
}

DbError Db::mainFunc( string name, string secondname, string date, string time)
{
	char *error;
	int rc;

	string sqlInsert = "INSERT INTO ";
	sqlInsert += "RFIDControler";
	sqlInsert += " VALUES(";
	sqlInsert += "NULL"; 
	sqlInsert += ",'";
	sqlInsert += name;
	sqlInsert += "','";
	sqlInsert += secondname;
	sqlInsert += "','";
	sqlInsert += date;
	sqlInsert += "','";
	sqlInsert += time;
	sqlInsert += "');";	 

	rc = sqlite3_exec(db, sqlInsert.c_str(), NULL, NULL, &error);

	if (rc)
	{
		sqlite3_free(error);
		sqlite3_close(db);
		return DbErrorWriteTable;
	}
	return DbErrorOk;
}
                 
