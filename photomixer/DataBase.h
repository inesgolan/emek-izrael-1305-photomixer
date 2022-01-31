#include <iostream>
#include <io.h>
#include <fstream>

#include "sqlite3.h"

#define DB_NAME "DB.sqlite"
#define OUTPUT_FILE_NAME "Output.txt"

class DataBase
{
private:
	sqlite3* _db;
	std::ofstream _outputFile;

public:
	DataBase();
	~DataBase();

	bool doesUserExist(std::string name);
	bool doesPasswordMatch(std::string name, std::string password);
	bool addNewUser(std::string name , std::string password, std::string mail);

};

