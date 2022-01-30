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

};

