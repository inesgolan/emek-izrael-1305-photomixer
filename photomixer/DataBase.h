#include <iostream>
#include <io.h>

#include "sqlite3.h"

#define FILE_NAME "DB.sqlite"

class DataBase
{
private:
	sqlite3* _db;

public:
	DataBase();
	~DataBase();

	bool doesUserExist(std::string name);
	bool doesPasswordMatch(std::string name, std::string password);
	bool addNewUser(std::string name , std::string password, std::string mail);

};

