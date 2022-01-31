#include "DataBase.h"


int callbackString(void* data, int argc, char** argv, char** azColName);

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


// db resuests + callbacks

int callbackString(void* data, int argc, char** argv, char** azColName)
{
	std::string* name = (std::string*)data;
	*name = argv[0];
	return 0;
}

// check if user already exist
bool DataBase::doesUserExist(std::string name)
{
	std::string tempName = "";
	char* errorMsg = nullptr;

	std::string query = "SELECT NAME FROM Users WHERE Name = \'" + name + "'\;";
	int result = sqlite3_exec(this->_db, query.c_str(), callbackString, &tempName, &errorMsg);
	if (result != SQLITE_OK)
	{
		std::cout << errorMsg << std::endl;;
	}
	return strcmp(name.c_str(), tempName.c_str()) == 0;
}

// check if the password match the username
bool DataBase::doesPasswordMatch(std::string name, std::string password)
{
	//check if user exist
	if (!doesUserExist(name))
	{
		return false;
	}

	std::string dbPassword = "";
	char* errorMsg = nullptr;
	std::string query = "SELECT PASSWORD FROM Users WHERE Name = \'" + name + "'\;";
	int result = sqlite3_exec(this->_db, query.c_str(), callbackString, &dbPassword, &errorMsg);
	if (result != SQLITE_OK)
	{
		std::cout << errorMsg << std::endl;;
	}
	return strcmp(dbPassword.c_str(), password.c_str()) == 0;
}

// add new user to the DB
bool DataBase::addNewUser(std::string name, std::string password, std::string mail)
{
	char* errorMsg = nullptr;
	std::string query;
	int userResult;
	//check if user exist
	if (doesUserExist(name))
	{
		return false;
	}

	//add the user to the users
	errorMsg = nullptr;
	query = "INSERT INTO Users (Name, Password, Email) VALUES (\'" + name + "\', \'" + password + "\', \'" + mail + "\');";
	userResult = sqlite3_exec(this->_db, query.c_str(), nullptr, nullptr, &errorMsg);

	return (userResult == SQLITE_OK);
}

