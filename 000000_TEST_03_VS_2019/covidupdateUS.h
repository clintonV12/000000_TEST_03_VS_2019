#pragma once

struct CovidUpdate
{
	std::string province_state;
	std::string last_update; 
	double confirmed;
	double deaths;
	double recovered;
	double active;
};

std::ostream& operator<<  (std::ostream& os, CovidUpdate C) {
	os << std::left << std::setw(30) << C.province_state
		<< std::setw(30) << C.last_update
		<< std::setw(15) << C.confirmed
		<< std::setw(15) << C.deaths
		<< std::setw(15) << C.recovered
		<< std::setw(15) << C.active;
	os << std::endl;
	return os;
}

std::istream& operator>>  (std::istream& is, CovidUpdate& C) {
	is >> C.province_state >> C.last_update >> C.confirmed >> C.deaths >> C.recovered >> C.active;
	return is;
}

bool operator==  (CovidUpdate C, CovidUpdate T) {
	return C.province_state == T.province_state;
}

bool operator!=  (CovidUpdate C, CovidUpdate T) {
	return !(C.province_state == T.province_state);
}

bool operator<  (CovidUpdate C, CovidUpdate T) {
	return C.confirmed < T.confirmed;
}

bool operator> (CovidUpdate C, CovidUpdate T) {
	return C.confirmed > T.confirmed;
}

void initCovidUpdateRec(CovidUpdate &covidUpdate, std::string province_state, std::string last_update, double confirmed, double deaths, double recovered, double active)
{
	covidUpdate.province_state = province_state;
	covidUpdate.last_update = last_update;
	covidUpdate.confirmed = confirmed;
	covidUpdate.deaths = deaths;
	covidUpdate.recovered = recovered;
	covidUpdate.active = active;
}

std::list<CovidUpdate> extractCovidUpdateRecordsFromCSVFileToList(const char* covidDataFile)
{
	std::ifstream covidDataFileStream;
	covidDataFileStream.open(covidDataFile, std::ios::in);

	std::string covidUpdate_str;
	getline(covidDataFileStream, covidUpdate_str);

	char csvSeparatorChar = ',';
	std::list <CovidUpdate> covidUpdateList;

	while (getline(covidDataFileStream, covidUpdate_str))
	{
		std::istringstream covidDataRecLineSS(covidUpdate_str);
		std::string Province_State, Country_Region, Last_Update, Lat, Long_, Confirmed, Deaths, Recovered, Active, FIPS, Incident_Rate, People_Tested, People_Hospitalized, Mortality_Rate, UID, ISO3, Testing_Rate, Hospitalization_Rate;

		getline(covidDataRecLineSS, Province_State, csvSeparatorChar);
		getline(covidDataRecLineSS, Country_Region, csvSeparatorChar);
		getline(covidDataRecLineSS, Last_Update, csvSeparatorChar);
		getline(covidDataRecLineSS, Lat, csvSeparatorChar);
		getline(covidDataRecLineSS, Long_, csvSeparatorChar);
		getline(covidDataRecLineSS, Confirmed, csvSeparatorChar);
		getline(covidDataRecLineSS, Deaths, csvSeparatorChar);
		getline(covidDataRecLineSS, Recovered, csvSeparatorChar);
		getline(covidDataRecLineSS, Active, csvSeparatorChar);
		getline(covidDataRecLineSS, FIPS, csvSeparatorChar);
		getline(covidDataRecLineSS, Incident_Rate, csvSeparatorChar);
		getline(covidDataRecLineSS, People_Tested, csvSeparatorChar);
		getline(covidDataRecLineSS, People_Hospitalized, csvSeparatorChar);
		getline(covidDataRecLineSS, Mortality_Rate, csvSeparatorChar);
		getline(covidDataRecLineSS, UID, csvSeparatorChar);
		getline(covidDataRecLineSS, ISO3, csvSeparatorChar);
		getline(covidDataRecLineSS, Testing_Rate, csvSeparatorChar);
		getline(covidDataRecLineSS, Hospitalization_Rate, csvSeparatorChar);

		std::istringstream confirmed_iss(Confirmed);
		double confirmed = 0.0;
		confirmed_iss >> confirmed;

		std::istringstream deaths_iss(Deaths);
		double deaths = 0.0;
		deaths_iss >> deaths;

		std::istringstream recovered_iss(Recovered);
		double recovered = 0.0;
		recovered_iss >> recovered;

		std::istringstream active_iss(Active);
		double active = 0.0;
		active_iss >> active;
		

		CovidUpdate covidUpdate;
		initCovidUpdateRec(covidUpdate, Province_State, Last_Update, confirmed, deaths, recovered, active);
		covidUpdateList.push_back(covidUpdate);
	}

	covidUpdateList.sort();
	covidUpdateList.unique();

	covidDataFileStream.close();
	return covidUpdateList;
}

void displayCovidDataList(std::list<CovidUpdate> covidUpdate)
{
	for (auto it = covidUpdate.begin(); it != covidUpdate.end(); ++it)
	{
		std::cout << *it << std::endl;
		std::cout << "\n" << std::endl;
	}
}

void generateSingleStateCovidData(std::string stateName, std::list<std::string> filenames, std::ostream& OS) {
	std::list<CovidUpdate> covidUpdateList;
	std::list<CovidUpdate> covidUpdateList2;

	for (auto it = filenames.begin(); it != filenames.end(); ++it)
	{
		std::ifstream covidDataFileStream;
		covidDataFileStream.open(*it, std::ios::in);
		
		std::string filename = *it;
		covidUpdateList = extractCovidUpdateRecordsFromCSVFileToList(filename.c_str());
		
		for(auto it2 = covidUpdateList.begin(); it2 != covidUpdateList.end(); ++it2)
		{
			CovidUpdate cu = *it2;
			if (cu.province_state == stateName) {
				covidUpdateList2.push_back(cu);
			}
		}

	}
	OS << std::left << std::setw(30) << "STATE"
		<< std::setw(30) << "LAST UPDATE"
		<< std::setw(15) << "CONFIRMED"
		<< std::setw(15) << "DEATHS"
		<< std::setw(15) << "RECOVERED"
		<< std::setw(15) << "ACTIVE";
	OS << std::endl;
	for (auto it = covidUpdateList2.begin(); it != covidUpdateList2.end(); ++it)
	{
		OS << *it << std::endl;
	}
}

void generateAllStateCovidReports(std::list<State> states, std::list<std::string> filenames, std::ostream& OS) {
	
	for (auto it = states.begin(); it != states.end(); ++it)
	{
		std::list<CovidUpdate> covidUpdateList;
		std::list<CovidUpdate> covidUpdateList2;
		State state = *it;

		std::string province_state = state.province_state;
		int population = state.population;
		double latitude = state.latitude;
		double longitude = state.longitude;
		std::string postal_code = state.postal_code;
		int fips = state.fips;
		OS << "\n";
		OS <<std::left << std::setw(15) << "STATE" << std::setw(10) << ":" << province_state <<std::endl;
		OS << std::setw(15) << "POPULATION" << std::setw(10) << ":" << population << std::endl;
		OS << std::setw(15) << "LATITUDE" << std::setw(10) << ":" << latitude << std::endl;
		OS << std::setw(15) << "LONGITUDE" << std::setw(10) << ":" << longitude << std::endl;
		OS << std::setw(15) << "POSTAL CODE" << std::setw(10) << ":" << postal_code << std::endl;
		OS << std::setw(15) << "FIPS" << std::setw(10) << ":" << fips << std::endl;

		for (auto it2 = filenames.begin(); it2 != filenames.end(); ++it2)
		{
			std::ifstream covidDataFileStream;
			covidDataFileStream.open(*it2, std::ios::in);

			std::string filename = *it2;
			covidUpdateList = extractCovidUpdateRecordsFromCSVFileToList(filename.c_str());

			for (auto it3 = covidUpdateList.begin(); it3 != covidUpdateList.end(); ++it3)
			{
				CovidUpdate cu = *it3;
				if (cu.province_state == state.province_state) {
					covidUpdateList2.push_back(cu);
				}
			}
		}

		OS << "===================================================================================================================" << std::endl;
		OS << std::left << std::setw(30) << "STATE"
			<< std::setw(30) << "LAST UPDATE"
			<< std::setw(15) << "CONFIRMED"
			<< std::setw(15) << "DEATHS"
			<< std::setw(15) << "RECOVERED"
			<< std::setw(15) << "ACTIVE";
		OS << std::endl;
		OS << "===================================================================================================================" << std::endl;
		double total_confirmed = 0.0;
		double total_deaths = 0.0;
		double total_recovered = 0.0;
		double total_active = 0.0;

		for (auto it4 = covidUpdateList2.begin(); it4 != covidUpdateList2.end(); ++it4)
		{
			OS << *it4 << std::endl;
			CovidUpdate temp = *it4;

			total_confirmed = total_confirmed + temp.confirmed;
			total_deaths = total_deaths + temp.deaths;
			total_recovered = total_recovered + temp.recovered;
			total_active = total_active + temp.active;
		}
		OS << "===================================================================================================================" << std::endl;
		OS << std::left << std::setw(30) << "TOTAL"
			<< std::setw(30) << ""
			<< std::setw(15) << total_confirmed
			<< std::setw(15) << total_deaths
			<< std::setw(15) << total_recovered
			<< std::setw(15) << total_active;
		OS << std::endl;
		OS << "===================================================================================================================" << std::endl;
	}
}
