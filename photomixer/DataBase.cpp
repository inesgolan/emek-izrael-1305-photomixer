#include "DataBase.h"

//open the database
DataBase::DataBase()
{
	int result = sqlite3_open(FILE_NAME, &this->_db);
	if (result != SQLITE_OK)
	{
		this->_db = nullptr;
		std::cout << "error ";
	}
}

//close the database
DataBase::~DataBase()
{
	sqlite3_close(this->_db);
	this->_db = nullptr;
}

