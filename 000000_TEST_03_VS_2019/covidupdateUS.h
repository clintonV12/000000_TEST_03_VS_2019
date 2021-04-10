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
	os << std::left << std::setw(15) << C.province_state
		<< std::setw(30) << C.last_update
		<< std::setw(30) << C.confirmed
		<< std::setw(30) << C.deaths
		<< std::setw(30) << C.recovered
		<< std::setw(30) << C.active;
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
		std::istringstream covidUpdateRecLineSS(covidUpdate_str);
		std::string province_state, last_update, confirmed, deaths, recovered, active = "-1";

		getline(covidUpdateRecLineSS, province_state, csvSeparatorChar);
		getline(covidUpdateRecLineSS, last_update, csvSeparatorChar);
		getline(covidUpdateRecLineSS, confirmed, csvSeparatorChar);
		getline(covidUpdateRecLineSS, deaths, csvSeparatorChar);
		getline(covidUpdateRecLineSS, recovered, csvSeparatorChar);
		getline(covidUpdateRecLineSS, active, csvSeparatorChar);

		std::istringstream confirmed_iss(confirmed);
		double Confirmed = 0.0;
		confirmed_iss >> Confirmed;

		std::istringstream deaths_iss(deaths);
		double Deaths = 0.0;
		deaths_iss >> Deaths;

		std::istringstream recovered_iss(recovered);
		double Recovered = 0.0;
		recovered_iss >> Recovered;

		std::istringstream active_iss(active);
		double Active = 0.0;
		active_iss >> Active;

		CovidUpdate covidUpdate;
		initCovidUpdateRec(covidUpdate, province_state, last_update, Confirmed, Deaths, Recovered, Active);
		covidUpdateList.push_back(covidUpdate);
	}

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