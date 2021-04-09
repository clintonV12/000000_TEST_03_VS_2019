#pragma once
/*
* CSC213 - APRIL 2021 -- utilitty functions file
* Do not change the contents of this file. Use the functions as they are given
* DO NOT ADD OR REMOVE CODE HERE
* Author : Enock Lukhetfo Dube
*/

#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

//need to include list STL
#include <list>
#include <iterator>


#include <dirent.h>
//NOTES
/*To manage files, you need to include directory entry package
 * Copy the provided dirent.h file to the include folder in your
 * Microsoft Visual Studio Installtion folder. The folder contains a lot of other necessary .h files.
 * DO NOT CHANGE ANYTHING, JUST COPY AND PASTE THE dirent.h FILE HERE:
 *
 * In 2019 version the path to the include folder could be like
 * C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.27.29110\include
 *
 *  In 2017 version the path to the include folder could be
 * C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.16.27023\include
 *
*/



/*****************************************************************************************************/
/*                                        UTILITY FUNCTIONS                                          */
/*****************************************************************************************************/
/* Extract filenames from given folder to a list. The specified folder/directory must be in the
*  project folder -- otherwise need to specify whole path.
*/
std::list<std::string> extractCovidDataFileNamesToTable(const char* dataDirectoryName)
{
	std::list<std::string> covidDataFileNameTable;
	DIR* dir;
	struct dirent* ent;
	//*******************************************
	std::stringstream dnameSS;
	dnameSS << ".\\" << dataDirectoryName << "\\";
	std::string dirName = dnameSS.str();
	//*******************************************
	if ((dir = opendir(dirName.c_str())) != NULL) { //open specified directory/folder
		while ((ent = readdir(dir)) != NULL) {
			std::string dataFilename = dirName + ent->d_name;
			covidDataFileNameTable.push_back(dataFilename);
		}
		closedir(dir);
	}
	else {
		/* could not open directory --return EXIT_FAILURE;*/
		perror("");

	}
	covidDataFileNameTable.remove(dirName + ".");
	covidDataFileNameTable.remove(dirName + "..");
	covidDataFileNameTable.sort();
	return covidDataFileNameTable;
}

//display file names from given list
void DisplayCovidDataFileNameList(std::list<std::string> CovidDataFileNameList)
{
	std::list<std::string>::iterator it;
	for (it = CovidDataFileNameList.begin(); it != CovidDataFileNameList.end(); ++it)
		std::cout << *it << std::endl;
}

//function to format date strings
std::string extractDateFromString(std::string dateString) {
	//date string format: yyyy-mm-dd hour:min:sec

	std::string result;
	std::tm tm = {};
	std::stringstream ss(dateString);
	ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
	std::stringstream resultSS;
	resultSS << tm.tm_mday << "/" << tm.tm_mon + 1 << "/" << tm.tm_year + 1900;
	resultSS >> result;
	return result;
}


#endif //UTILITY_H