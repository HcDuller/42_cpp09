/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:28:52 by hde-camp          #+#    #+#             */
/*   Updated: 2023/03/23 20:17:09 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <sstream>
#include <fstream>
#include <map>
#include <exception>
#include <string>
#include <ctime>

bool readEvalHeader(std::istream& fs){
	std::string f_line;
	std::string f_part;
	std::string s_part;
	std::getline(fs, f_line);
	std::getline(fs, f_part, '|');
	std::getline(fs, s_part);

	
}
//Canonical class declaration START***************************************************
BitcoinExchange::BitcoinExchange(){
	throw(BitcoinExchange::ProhibitedInstantiation());
}
BitcoinExchange::~BitcoinExchange(){};
BitcoinExchange::BitcoinExchange(BitcoinExchange& origin): _rates(origin._rates){};
BitcoinExchange& BitcoinExchange::operator=(BitcoinExchange& origin){
	this->_rates = origin._rates;
	return (*this);
};
//Canonical class declaration END*****************************************************


//Custom Constructor --pending
BitcoinExchange::BitcoinExchange(const char* databeseFile){
	
};

//Additional Methods******************************************************************
void BitcoinExchange::addRecord(std::string& formattedDate,std::string& formatedValue) throw(){
	//pending
};
double BitcoinExchange::parseRate(std::string& origin){};
std::time_t BitcoinExchange::parseDate(std::string& origin){};
void BitcoinExchange::loadDataBase(std::string& dbPath){
	std::fstream fs;
	const char* c_Path = dbPath.c_str();
	fs.open(c_Path, std::fstream::in);
	if (!fs.is_open())
		throw BitcoinExchange::NoDatabaseFoundError();
	
};

//Custom Errors***********************************************************************
const char* BitcoinExchange::ProhibitedInstantiation::what() const {
	return ("Tried to instantiate BitcoinExchange class improperly.");
};
const char* BitcoinExchange::CorruptedDatabaseError::what() const {
	return ("BitcoinExchange database is corrupted.");
};
const char* BitcoinExchange::NoDatabaseFoundError::what() const {
	return ("BitcoinExchange database wasn't found.");
};

/*
 
class BitcoinExchange {
	public:
	private:
		std::map<std::time_t,double> _rates;
};

 */