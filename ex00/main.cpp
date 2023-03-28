/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:51:13 by hde-camp          #+#    #+#             */
/*   Updated: 2023/03/28 11:26:51 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <sstream>
#include <algorithm>
#include <map>

bool isValidDate(std::string& date){
	if (date.length() != 10)
		return (false);
	std::string::iterator it = date.begin();
	for (std::string::iterator local_it = it; it - local_it < 4; it++)
	{
		if (!std::isdigit(static_cast<int>(*it)))
			return (false);
	}
	if (!(*it == '-'))
		return (false);
	it++;
	for (std::string::iterator local_it = it; it - local_it < 2; it++)
	{
		if (!std::isdigit(static_cast<int>(*it)))
			return (false);
	}
	if (!(*it == '-'))
		return (false);
	it++;
	for (std::string::iterator local_it = it; it - local_it < 2; it++)
	{
		if (!std::isdigit(static_cast<int>(*it)))
			return (false);
	}
	return (true);
}
bool isValidNumber(std::string& value){
	if (std::count(value.begin(), value.end(), '.') > 1)
		return (false);
	if (!std::isdigit(static_cast<int>(value.at(0))))
		return (false);
	for (std::string::iterator it = value.begin(); it < value.end(); it++)
	{
		if (!(std::isdigit(static_cast<int>(*it)) || static_cast<char>(*it) == '.'))
			return (false);
	}
	return (true);
}

void getHeaders(std::istream& in, std::string& f_header, std::string& s_header){
	std::getline(in, f_header, '|');
	std::getline(in, s_header);
	std::cout << f_header << " | " << s_header << std::endl;
}
void readRest(std::istream& in, std::string& date, std::string& value){
	std::getline(in, date, ',');
	std::getline(in, value);
	isValidDate(date);
	std::cout << date << " | " << value << std::endl;
}
int main(int argc, char *argv[]){
	std::fstream fs;
	std::string tmpLine;
	if (argc != 2)
	{
		std::cout << "Incorrect number of arguments" << std::endl;
		return (1);
	}
	BitcoinExchange db;
	db.readPrintInput(argv[1]);
	(void)argv;
	return (0);
}