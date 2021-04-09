
#include <iostream>

//include STL
#include <list>
#include <algorithm>

//add utility definitions
#include "utility.h"


//PROTOTYPES
void extractCovidUpdateRecordsFromCSVFile(const char*, std::ostream&);

int main()
{
	//extract filenames from test-data folder to a list
	std::cout << "These are the data file names :" << std::endl;
	std::list<std::string> DataFileNamesList = extractCovidDataFileNamesToTable("test_data\\csse_covid_19_daily_reports_us");
	DisplayCovidDataFileNameList(DataFileNamesList);
	std::cout << std::endl << std::endl;
	system("pause");

	//extract data from first file in data file name list
	std::list<std::string>::iterator it = DataFileNamesList.begin(); //first name in list of covid data file names
	std::string dataFileName = *it;
	extractCovidUpdateRecordsFromCSVFile(dataFileName.c_str(), std::cout);

	std::cout << std::endl << std::endl;
	system("pause");

	return 0;
}

//extract data from single covid-19 data file
void extractCovidUpdateRecordsFromCSVFile(const char* covidDataFileName, std::ostream& OS)
{
	std::ifstream covidDataFileStream;
	covidDataFileStream.open(covidDataFileName, std::ios::in);

	std::string covidUpdate_str;
	getline(covidDataFileStream, covidUpdate_str);

	char csvSeparatorChar = ',';

	OS << "\nCovid-19 Data Filename : " << covidDataFileName << std::endl;
	OS << "============================================================================================================" << std::endl;
	OS << std::setw(30) << std::left << "STATE"
		<< std::setw(20) << "LAST UDATE"
		<< std::setw(15) << "CONFIRMED"
		<< std::setw(15) << "DEATHS"
		<< std::setw(15) << "RECOVERED"
		<< std::setw(15) << "ACTIVE";
	OS << "\n============================================================================================================" << std::endl;

	while (getline(covidDataFileStream, covidUpdate_str))
	{
		std::istringstream covidUpdateRecLineSS(covidUpdate_str);

		std::string
			Province_State, Country_Region, Last_Update, Lat, Long_,
			Confirmed, Deaths, Recovered, Active, FIPS,
			Incident_Rate, Total_Test_Results, People_Hospitalized, Case_Fatality_Ratio, UID,
			ISO3, Testing_Rate, Hospitalization_Rate;

		getline(covidUpdateRecLineSS, Province_State, csvSeparatorChar);
		getline(covidUpdateRecLineSS, Country_Region, csvSeparatorChar);
		getline(covidUpdateRecLineSS, Last_Update, csvSeparatorChar);
		getline(covidUpdateRecLineSS, Lat, csvSeparatorChar);
		getline(covidUpdateRecLineSS, Long_, csvSeparatorChar);


		getline(covidUpdateRecLineSS, Confirmed, csvSeparatorChar);
		getline(covidUpdateRecLineSS, Deaths, csvSeparatorChar);
		getline(covidUpdateRecLineSS, Recovered, csvSeparatorChar);
		getline(covidUpdateRecLineSS, Active, csvSeparatorChar);
		getline(covidUpdateRecLineSS, FIPS, csvSeparatorChar);

		getline(covidUpdateRecLineSS, Incident_Rate, csvSeparatorChar);
		getline(covidUpdateRecLineSS, Total_Test_Results, csvSeparatorChar);
		getline(covidUpdateRecLineSS, People_Hospitalized, csvSeparatorChar);
		getline(covidUpdateRecLineSS, Case_Fatality_Ratio, csvSeparatorChar);
		getline(covidUpdateRecLineSS, UID, csvSeparatorChar);

		getline(covidUpdateRecLineSS, ISO3, csvSeparatorChar);
		getline(covidUpdateRecLineSS, Testing_Rate, csvSeparatorChar);
		getline(covidUpdateRecLineSS, Hospitalization_Rate, csvSeparatorChar);

		//=====================================
		//impute -1 for missing key values 
		if (strlen(Confirmed.c_str()) == 0)
			Confirmed = "-1";
		if (strlen(Deaths.c_str()) == 0)
			Deaths = "-1";
		if (strlen(Recovered.c_str()) == 0)
			Recovered = "-1";
		if (strlen(Active.c_str()) == 0)
			Active = "-1";
		//=====================================


		OS << std::left << std::setw(30) << Province_State
			<< std::setw(20) << extractDateFromString(Last_Update)
			<< std::setw(15) << Confirmed
			<< std::setw(15) << Deaths
			<< std::setw(15) << Recovered
			<< std::setw(15) << Active;
		OS << std::endl;
	}
	OS << "============================================================================================================" << std::endl;
	covidDataFileStream.close();
	return;
}

