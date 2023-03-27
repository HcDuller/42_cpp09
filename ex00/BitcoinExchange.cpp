/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:28:52 by hde-camp          #+#    #+#             */
/*   Updated: 2023/03/27 17:09:25 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <sstream>
#include <fstream>
#include <map>
#include <exception>
#include <string>
#include <ctime>
#include <utility>

bool readEvalHeader(std::istream& fs){
	std::string f_line;
	std::string f_part;
	std::string s_part;
	std::stringstream line_stream;
	// Header must be: str|str, there is no definition fot str pattern, so, anything goes.
	std::getline(fs, f_line);
	if (f_line.length() < 3)
		throw std::length_error("Header too short");
	line_stream.str(f_line);
	std::getline(line_stream, f_part, '|');
	std::getline(line_stream, s_part);
	return(true);
}
double strToDouble(std::string& input){
	std::stringstream ss(input);
	double res;
	ss >> res;
	return (res);
}
std::time_t strDateToTimeT(std::string& strDate){
	std::stringstream ss;
	std::stringstream res;
	std::string line;
	std::string year;
	std::string month;
	std::string day;
	int i_year;
	int i_month;
	int i_day;
	ss.str(strDate);
	std::getline(ss, year, '-');
	std::getline(ss, month, '-');
	std::getline(ss, day, '-');
	res << year << ' ' << month << ' ' << day;
	res >> i_year >> i_month >> i_day;
	std::tm tm = {};
	tm.tm_sec = 0;
	tm.tm_min = 0;
	tm.tm_hour = 0;
	tm.tm_mday = i_day;
	tm.tm_mon = i_month - 1;
	tm.tm_year = i_year - 1900;
	tm.tm_isdst = 0;
	return (std::mktime(&tm));

}
//Canonical class declaration START***************************************************
BitcoinExchange::BitcoinExchange(): _databaseFile("data.csv"){
	loadDataBase(this->_databaseFile);
}
BitcoinExchange::~BitcoinExchange(){};
BitcoinExchange::BitcoinExchange(BitcoinExchange& origin): _databaseFile("data.csv"),_rates(origin._rates){};
BitcoinExchange& BitcoinExchange::operator=(BitcoinExchange& origin){
	this->_rates = origin._rates;
	return (*this);
};
//Canonical class declaration END*****************************************************

//Additional Methods******************************************************************
void BitcoinExchange::addRecord(std::string& formattedDate,std::string& formatedValue) throw(){
	//pending
	(void)formattedDate;
	(void)formatedValue;
};
double BitcoinExchange::parseRate(std::string& origin){
	//pending
	(void)origin;
	return 2.0;
};
std::time_t BitcoinExchange::parseDate(std::string& origin){
	//pending
	std::time_t a = 0;
	(void)origin;
	return a;
};
void BitcoinExchange::loadDataBase(const char* dbPath){
	std::fstream fs;
	fs.open(dbPath, std::fstream::in);
	if (!fs.is_open())
		throw BitcoinExchange::NoDatabaseFoundError();
	std::string current_read;
	std::getline(fs, current_read); //read header lines (discarted!)
	std::time_t* datePart = new std::time_t();
	double valuePart;
	while (!fs.eof()){
		std::getline(fs, current_read, ','); // datepart
		*datePart = strDateToTimeT(current_read);
		std::getline(fs, current_read); // valuepart
		valuePart = strToDouble(current_read);
		this->_rates.insert(std::make_pair<std::time_t, double>(*datePart, valuePart));
	}
	delete datePart;
};

//Custom Errors***********************************************************************
const char* BitcoinExchange::ProhibitedInstantiation::what() const throw() {
	return ("Tried to instantiate BitcoinExchange class improperly.");
};
const char* BitcoinExchange::CorruptedDatabaseError::what() const throw() {
	return ("BitcoinExchange database is corrupted.");
};
const char* BitcoinExchange::NoDatabaseFoundError::what() const throw() {
	return ("BitcoinExchange database wasn't found.");
};

/*
 
class BitcoinExchange {
	public:
	private:
		std::map<std::time_t,double> _rates;
};

 */