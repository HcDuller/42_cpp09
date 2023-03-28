/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:51:27 by hde-camp          #+#    #+#             */
/*   Updated: 2023/03/28 12:14:27 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <map>
#include <exception>
#include <string>
#include <ctime>

class BitcoinExchange {
	public:
		BitcoinExchange();
		~BitcoinExchange();
		void readPrintInput(const char* input);
	private:
		BitcoinExchange(BitcoinExchange& origin);
		BitcoinExchange& operator=(BitcoinExchange& origin);
		const char* _databaseFile;
		std::map<std::time_t,double> _rates;
		double parseRate(std::string& doubleString);
		void loadDataBase(const char* dbPath);
		std::pair<std::string,std::string> getLineParts(std::string& line);
		std::time_t parseDateStr(std::string& dateString);
		static void evalValidChars(const char& c);
		double getValueByDate(std::time_t date);
		class NoDatabaseFoundError : public std::exception {
			public:
				virtual const char* what() const throw();
		};
		class CorruptedDatabaseError : public std::exception {
			public:
				virtual const char* what() const throw();
		};
		class ProhibitedInstantiation : public std::exception {
			public:
				virtual const char* what() const throw();
		};
		class InputFileNotFoundError : public std::exception {
			public:
				virtual const char* what() const throw();
		};
		class DatelessRecordError : public std::exception {
			public:
				virtual const char* what() const throw();
		};
		class ValuelessRecordError : public std::exception {
			public:
				virtual const char* what() const throw();
		};
		class InvalidDateError : public std::exception {
			public:
				virtual const char* what() const throw();
		};
		class InvalidValueError : public std::exception {
			public:
				virtual const char* what() const throw();
		};
		class OutOfRangeValue : public std::exception {
			public:
				virtual const char* what() const throw();
		};
};