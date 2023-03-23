/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:51:27 by hde-camp          #+#    #+#             */
/*   Updated: 2023/03/23 20:02:14 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <map>
#include <exception>
#include <string>
#include <ctime>

class BitcoinExchange {
	public:
		BitcoinExchange(const char* databeseFile);
		~BitcoinExchange();
		void addRecord(std::string& formattedDate,std::string& formatedValue) throw();
	private:
		BitcoinExchange();
		BitcoinExchange(BitcoinExchange& origin);
		BitcoinExchange& operator=(BitcoinExchange& origin);
		std::map<std::time_t,double> _rates;
		std::time_t parseDate(std::string& origin);
		double parseRate(std::string& origin);
		void loadDataBase(std::string& dbPath);
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
};