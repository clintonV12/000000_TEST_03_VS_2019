#include <iostream>

//include STL
#include <list>
#include <algorithm>

//add utility definitions
#include "utility.h"
//add state definitions
#include "state.h"
//add covidupdateUS definitions
#include "covidupdateUS.h"


//PROTOTYPES
void extractCovidUpdateRecordsFromCSVFile(const char*, std::ostream&);
void showMainMenu();
void showManageDataFileNames();
void showManageStateRecords();
void showManageCovidUpdate();

int main()
{
	std::list<std::string> DataFileNamesList;
	std::list<State> stateList;
	std::list<CovidUpdate> covidUpdateList;

	//start interactive menu
	int main_choice = -1;

	//show main menu and read user input
	showMainMenu();
	std::cin >> main_choice;

	// check if user input is valid 
	//********************************************
	while (std::cin.fail())
	{
		std::cout << "ERROR : Enter an integer digit between 1 and 5" << std::endl;
		system("pause");

		//show main menu
		showMainMenu();

		// clear and ignore invalid user input
		std::cin.clear();
		std::cin.ignore(256, '\n');

		//read choice again
		std::cin >> main_choice;
	}

	while (main_choice != 6) // choice 6 to exit
	{
		switch (main_choice)
		{
			case 1:{
				int submenu_choice = -1;

				//show submenu and read user input
				showManageDataFileNames();
				std::cin >> submenu_choice;
				while (submenu_choice != 4)
				{
					switch (submenu_choice)
					{
						case 1: {
							std::string folder;
							std::cout << "Enter the name of the folder with state data files"<< std::endl;
							std::cin >> folder;
							std::string folder_name = "test_data\\" + folder;
							
							DataFileNamesList = extractCovidDataFileNamesToTable(folder_name.c_str());
							std::cout << "File name extraction done" << std::endl;
							system("pause");

							//read choice again
							showManageDataFileNames();
							std::cin >> submenu_choice;
							break;
						}
						case 2: {
							DataFileNamesList.sort();
							std::cout << "File name sorting done" << std::endl;
							system("pause");

							//read choice again
							showManageDataFileNames();
							std::cin >> submenu_choice;
							break;
						}
						case 3: {
							std::cout << "These are the data file names :" << std::endl;
							DisplayCovidDataFileNameList(DataFileNamesList);
							std::cout << std::endl << std::endl;
							system("pause");

							//read choice again
							showManageDataFileNames();
							std::cin >> submenu_choice;
							break;
						}
					}
				}

				showMainMenu();
				std::cin >> main_choice;
				break;
			}
			
			case 2: {
				int submenu_choice = -1;

				//show submenu and read user input
				showManageStateRecords();
				std::cin >> submenu_choice;
				while (submenu_choice != 3)
				{
					switch (submenu_choice)
					{
						case 1: {
							std::string us_states;
							std::cout << "Enter the name of the states file" << std::endl;
							std::cin >> us_states;
							std::string us_states_file = "test_data\\" + us_states;

							stateList = extractStateRecordsFromCSVFileToList(us_states_file.c_str());
							std::cout << "Record extraction done" << std::endl;
							system("pause");

							//read choice again
							showManageStateRecords();
							std::cin >> submenu_choice;
							break;
						}

						case 2: {
							std::cout << "=====================================================================================================" << std::endl;
							std::cout << std::left << std::setw(15) << "STATE"
								<< std::setw(20) << "POPULATION"
								<< std::setw(20) << "LATITUDE"
								<< std::setw(20) << "LONGITUDE"
								<< std::setw(20) << "POSTAL CODE"
								<< std::setw(10) << "FIPS"<<std::endl;
							std::cout << "=====================================================================================================" << std::endl;
							displayStateData(stateList);
							system("pause");

							//read choice again
							showManageStateRecords();
							std::cin >> submenu_choice;
							break;
						}
					}
				}

				showMainMenu();
				std::cin >> main_choice;
				break;
			}

			case 3: {
				int submenu_choice = -1;

				//show submenu and read user input
				showManageCovidUpdate();
				std::cin >> submenu_choice;
				while (submenu_choice != 3)
				{
					switch (submenu_choice)
					{
					case 1: {
						std::cout << "Enter name of the state data file" << std::endl;
						std::string filename;
						std::cin >> filename;

						std::string fname = "test_data\\csse_covid_19_daily_reports_us\\" + filename;

						covidUpdateList = extractCovidUpdateRecordsFromCSVFileToList(fname.c_str());
						std::cout << "Record extraction done" << std::endl;
						system("pause");

						//read choice again
						showManageCovidUpdate();
						std::cin >> submenu_choice;
						break;
					}

					case 2: {
						std::cout << "===============================================================================================================" << std::endl;
						std::cout << std::left << std::setw(30) << "State"
							<< std::setw(30) << "Last Update"
							<< std::setw(15) << "Confirmed"
							<< std::setw(15) << "Deaths"
							<< std::setw(15) << "Recovered"
							<< std::setw(15) << "Active";
						std::cout << std::endl;
						std::cout << "===============================================================================================================" << std::endl;
						
						displayCovidDataList(covidUpdateList);
						system("pause");

						//read choice again
						showManageCovidUpdate();
						std::cin >> submenu_choice;
						break;
					}
					}
				}

				showMainMenu();
				std::cin >> main_choice;
				break;
			}

			case 4: {
				std::string us_state;
				std::cout << "Enter the state name" << std::endl;
				std::cin >> us_state;
				std::cout << "\n" << std::endl;

				DataFileNamesList = extractCovidDataFileNamesToTable("test_data\\csse_covid_19_daily_reports_us");
				generateSingleStateCovidData(us_state, DataFileNamesList, std::cout);
				system("pause");

				showMainMenu();
				std::cin >> main_choice;
				break;
			}

			case 5: {
				DataFileNamesList = extractCovidDataFileNamesToTable("test_data\\csse_covid_19_daily_reports_us");
				stateList = extractStateRecordsFromCSVFileToList("test_data\\US_States.csv");

				generateAllStateCovidReports(stateList, DataFileNamesList, std::cout);
				system("pause");

				showMainMenu();
				std::cin >> main_choice;
				break;
			}
		}
	}

	std::cout << std::endl << std::endl;
	system("pause");

	return 0;
}

void showMainMenu()
{
	system("CLS");

	std::cout << "\t" << std::endl;
	std::cout << "\t MAIN MENU" << std::endl;
	std::cout << "\t ==========" << std::endl << std::endl;
	std::cout << "\t 1. Manage Data File Names" << std::endl << std::endl;;
	std::cout << "\t 2. Manage State Records" << std::endl << std::endl;
	std::cout << "\t 3. Manage Covid Update Information" << std::endl << std::endl;
	std::cout << "\t 4. Generate Single State Covid Data" << std::endl << std::endl;
	std::cout << "\t 5. Generate All States Covid Reports" << std::endl << std::endl;
	std::cout << "\t 6. Exit" << std::endl << std::endl;
	std::cout << "\t =====================================" << std::endl << std::endl;

	std::cout << "\t ENTER YOUR CHOICE  :  ";
}

void showManageDataFileNames()
{
	system("CLS");
	std::cout << "\t MANAGE DATA FILE NAMES SUB-MENU " << std::endl;
	std::cout << "\t ==================================" << std::endl << std::endl;
	std::cout << "\t 1. Extract data filenames from folder to a list" << std::endl << std::endl;
	std::cout << "\t 2. Sort list of filenames" << std::endl << std::endl;
	std::cout << "\t 3. View file names in extracted list" << std::endl << std::endl;
	std::cout << "\t 4. Return to Main Menu" << std::endl << std::endl;
	std::cout << "\t" << "========================================================" << std::endl << std::endl;

	std::cout << "\t" << "\t ENTER YOUR CHOICE  :  ";
}

void showManageStateRecords()
{
	system("CLS");
	std::cout << "\t MANAGE STATES RECORDS SUB-MENU " << std::endl;
	std::cout << "\t ==================================" << std::endl << std::endl;
	std::cout << "\t 1. Load states records from a file into list" << std::endl << std::endl;
	std::cout << "\t 2. View states records in list" << std::endl << std::endl;
	std::cout << "\t 3. Return to Main Menu" << std::endl << std::endl;
	std::cout << "\t" << "========================================================" << std::endl << std::endl;

	std::cout << "\t" << "\t ENTER YOUR CHOICE  :  ";
}

void showManageCovidUpdate()
{
	system("CLS");
	std::cout << "\t MANAGE COVID UPDATE INFORMITION " << std::endl;
	std::cout << "\t ==================================" << std::endl << std::endl;
	std::cout << "\t 1. Extract Covid update records from a file into a list" << std::endl << std::endl;
	std::cout << "\t 2. View Covid update records in list" << std::endl << std::endl;
	std::cout << "\t 3. Return to Main Menu" << std::endl << std::endl;
	std::cout << "\t" << "========================================================" << std::endl << std::endl;

	std::cout << "\t" << "\t ENTER YOUR CHOICE  :  ";
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



