#pragma once

struct State
{
	std::string province_state;
	int population;
	double latitude;
	double longitude;
	std::string postal_code;
	int fips;
};

std::ostream& operator<<  (std::ostream& os, State S) {
	os << std::left << std::setw(15) << S.province_state
		<< std::setw(30) << S.population
		<< std::setw(30) << S.latitude
		<< std::setw(30) << S.longitude
		<< std::setw(30) << S.postal_code
		<< std::setw(30) << S.fips;
	os << std::endl;
	return os;
}

std::istream& operator>>  (std::istream& is, State& S) {
	is >> S.province_state >> S.population >> S.latitude >> S.longitude >> S.postal_code >> S.fips;
	return is;
}

bool operator==  (State S, State T) {
	return S.province_state == T.province_state;
}

bool operator!=  (State S, State T) {
	return !(S.province_state == T.province_state);
}

bool operator<  (State S, State T) {
	return S.province_state < T.province_state;
}

bool operator>  (State S, State T) {
	return S.province_state > T.province_state;
}

void initStateRec(State& state, std::string province_state, int population, double latitude, double longitude,std::string postal_code, int fips)
{
	state.province_state = province_state;
	state.population = population;
	state.latitude = latitude;
	state.longitude = longitude;
	state.postal_code = postal_code;
	state.fips = fips;
}

std::list<State> extractStateRecordsFromCSVFileToList(const char* stateDataFile)
{
	std::ifstream covidDataFileStream;
	covidDataFileStream.open(stateDataFile, std::ios::in);

	std::string covidUpdate_str;
	getline(covidDataFileStream, covidUpdate_str);

	char csvSeparatorChar = ',';
	std::list <State> stateList;

	while (getline(covidDataFileStream, covidUpdate_str))
	{
		std::istringstream covidUpdateRecLineSS(covidUpdate_str);
		std::string province_state, population, Lat, Long, postal_code, fips;

		getline(covidUpdateRecLineSS, province_state, csvSeparatorChar);
		getline(covidUpdateRecLineSS, population, csvSeparatorChar);
		getline(covidUpdateRecLineSS, Lat, csvSeparatorChar);
		getline(covidUpdateRecLineSS, Long, csvSeparatorChar);
		getline(covidUpdateRecLineSS, postal_code, csvSeparatorChar);
		getline(covidUpdateRecLineSS, fips, csvSeparatorChar);

		std::istringstream Lat_iss(Lat);
		double latitude = 0.0;
		Lat_iss >> latitude;

		std::istringstream Long_iss(Long);
		double longitude = 0.0;
		Long_iss >> longitude;

		std::istringstream fips_iss(fips);
		int Fips = 0.0;
		fips_iss >> Fips;

		std::istringstream pop_iss(population);
		int pop = 0.0;
		pop_iss >> pop;
		
		State state;
		initStateRec(state, province_state, pop, latitude, longitude, postal_code, Fips);
		stateList.push_back(state);
	}

	covidDataFileStream.close();
	return stateList;
}

void displayStateData(std::list<State> state)
{
	for (auto it = state.begin(); it != state.end(); ++it) 
	{ 
		std::cout << *it << std::endl;
		std::cout << "\n" << std::endl;
	}
}