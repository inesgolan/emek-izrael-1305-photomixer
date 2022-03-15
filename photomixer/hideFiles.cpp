#include "hideFiles.h"

/*
This function run a python script to hide the file
input: filename
output: none
*/
void hideFiles::hide(std::string filename)
{
	system(("python " + filename + " 1").c_str());
}

/*
This function run a python script to show the file
input: filename
output: none
*/
void hideFiles::show(std::string filename)
{
	system(("python " + filename + " 2").c_str());
}
