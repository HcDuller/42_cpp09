/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:28:52 by hde-camp          #+#    #+#             */
/*   Updated: 2023/03/28 12:45:57 by hde-camp         ###   ########.fr       */
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
#include <iostream>
#include <algorithm>
#include <iomanip>

double strToDouble(std::string& input){
	std::stringstream ss(input);
	double res;
	ss >> res;
	return (res);
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
std::time_t BitcoinExchange::parseDateStr(std::string& dateString){
	if (dateString.length() == 0)
		throw BitcoinExchange::DatelessRecordError();
	if (dateString.length() < 10)
		throw BitcoinExchange::InvalidDateError();
	if (std::count(dateString.begin(),dateString.end(), '-') != 2)
		throw BitcoinExchange::InvalidDateError();
	std::replace(dateString.begin(), dateString.end(), '-', ' ');
	std::stringstream ss;
	ss.str(dateString);
	int ymd[3];
	for (int i = 0 ; i < 3; i++){
		ss >> ymd[i];
		if (ss.fail())
			throw BitcoinExchange::InvalidDateError();
	}
	if (ymd[2] < 1 || ymd[2] > 31)//day 1-31
		throw BitcoinExchange::InvalidDateError();
	if (ymd[1] < 1 || ymd[1] > 12)//month 0-11
		throw BitcoinExchange::InvalidDateError();
	std::tm tm;
	tm.tm_year = ymd[0] - 1900;
	tm.tm_mon = ymd[1] - 1;
	tm.tm_mday = ymd[2];
	tm.tm_hour = 0;
	tm.tm_min = 0;
	tm.tm_sec = 0;
	tm.tm_isdst = 0;
	return (std::mktime(&tm));
};
void BitcoinExchange::evalValidChars(const char& c){
	if (!(std::isdigit(c) || c != '.'))
		throw BitcoinExchange::InvalidValueError();
}
double BitcoinExchange::parseRate(std::string& doubleString){
	if (std::count(doubleString.begin(),doubleString.end(), '.') > 1)
		throw BitcoinExchange::InvalidValueError();
	std::for_each(doubleString.begin(), doubleString.end(), BitcoinExchange::evalValidChars);
	std::stringstream ss(doubleString);
	double value;
	ss >> value;
	if (ss.fail())
		throw BitcoinExchange::InvalidValueError();
	if (value < 0 || value > 1000)
		throw BitcoinExchange::OutOfRangeValue();
	return (value);
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
		try{
			if (current_read.length() > 0)
				*datePart = parseDateStr(current_read);
		}catch(std::exception& e){
			std::cout << "Read Line " << current_read.length() << std::endl;
			std::cout << e.what() << std::endl;
		}
		std::getline(fs, current_read); // valuepart
		valuePart = strToDouble(current_read);
		this->_rates.insert(std::make_pair<std::time_t, double>(*datePart, valuePart));
	}
	delete datePart;
};
double BitcoinExchange::getValueByDate(std::time_t date){
	std::map<std::time_t,double>::iterator it;
	it = this->_rates.begin();
	if (date < (*it).first)
		return (0);
	it = this->_rates.find(date);
	if (it == this->_rates.end()){
		it = this->_rates.lower_bound(date);
		it--;
	}
	return ((*it).second);
}
void BitcoinExchange::readPrintInput(const char* input){
	std::fstream fs;
	std::string current_line;
	fs.open(input, std::fstream::in);
	if (!fs.is_open())
		throw BitcoinExchange::InputFileNotFoundError();
	std::pair<std::string,std::string> temp("","");
	std::getline(fs,current_line);
	try{
		temp = getLineParts(current_line);
		std::cout << (temp).first << "|" << (temp).second << std::endl;
	}catch(std::exception& e){
		std::cout << "Error: " << e.what() << std::endl;
	}
	while (!fs.eof())
	{
		std::getline(fs,current_line);
		try{
			temp = getLineParts(current_line);
			std::cout << temp.first << "=>" << temp.second << "_btc = ";
			std::time_t inputDate = BitcoinExchange::parseDateStr(temp.first);
			double value = BitcoinExchange::parseRate(temp.second);
			double rate = this->getValueByDate(inputDate);
			std::cout << std::setprecision(3) << std::fixed << rate * value << std::endl;
		}catch(std::exception& e){
			std::cout << "Error: " << e.what() << std::endl;
		}
	}
}
std::pair<std::string,std::string> BitcoinExchange::getLineParts(std::string& line){
	std::stringstream ss;
	std::string f_part;
	std::string s_part;
	ss.str(line);
	std::getline(ss, f_part, '|');
	if (f_part.length() == 0)
		throw BitcoinExchange::DatelessRecordError();
	std::getline(ss, s_part);
	return (std::make_pair<std::string,std::string>(f_part,s_part));
}

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
const char* BitcoinExchange::InputFileNotFoundError::what() const throw() {
	return ("Input file not found.");
};
const char* BitcoinExchange::DatelessRecordError::what() const throw() {
	return ("Record has no date.");
};
const char* BitcoinExchange::ValuelessRecordError::what() const throw() {
	return ("Record has no value.");
};
const char* BitcoinExchange::InvalidDateError::what() const throw() {
	return ("Record date is invalid.");
};
const char* BitcoinExchange::OutOfRangeValue::what() const throw() {
	return ("Record has negative or over 1000 value.");
};
const char* BitcoinExchange::InvalidValueError::what() const throw() {
	return ("Record has invalid value.");
};
/*
 
class BitcoinExchange {
	public:
	private:
		std::map<std::time_t,double> _rates;
};

 */