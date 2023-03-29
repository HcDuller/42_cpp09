/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:47:16 by hde-camp          #+#    #+#             */
/*   Updated: 2023/03/29 20:05:08 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <deque>
#include <list>
#include <vector>
#include <exception>
#include <stdexcept>
#include <sstream>

//Canonical Form - START
PmergeMe::PmergeMe(){};
PmergeMe::PmergeMe(const PmergeMe& origin){*this = origin;};
PmergeMe& PmergeMe::operator=(const PmergeMe& rhe){
	this->_inputDeque = rhe._inputDeque;
	this->_orderedList = rhe._orderedList;
	this->_orderedVector = rhe._orderedVector;
	return (*this);
};
PmergeMe::~PmergeMe(){};
//Canonical Form - END

//Public Member Functions - START
void PmergeMe::loadList(int nargs, char* args[]) throw(NegativeInputError,NonNumericInputError,NoInputError,std::invalid_argument){
	std::stringstream ss;
	int bucket;
	for (int i = 0; i < nargs; i++){
		ss << args[i];
		if (ss.fail())
		{
			std::string errMsg = "Could not extract [";
			errMsg = errMsg + args[i] + "] from args.";
			throw(std::invalid_argument(errMsg.c_str()));
		}
		ss >> bucket;
		if (!ss.eof())
		{
			std::string errMsg = "The argument [";
			errMsg = errMsg + args[i] + "] cannot is invalid.";
			throw(std::invalid_argument(errMsg.c_str()));
		}
		if (ss.fail())
			throw NonNumericInputError();
		if (bucket < 0)
			throw NegativeInputError();
		this->_inputDeque.push_back(static_cast<unsigned int>(bucket));
	}
};
//Public Member Functions - END
//Private Member Functions - START

//Private Member Functions - END
//Member Errors START
const char* PmergeMe::NegativeInputError::what() const throw(){
	return ("Negative numbers are not allowed.");
};
const char* PmergeMe::NonNumericInputError::what() const throw(){
	return ("Non-Numeric values are not allowed.");
};
const char* PmergeMe::NoInputError::what() const throw(){
	return ("No input was found.");
};
//Member Errors END
/*

class PmergeMe
{
private:
	std::deque<unsigned int> _inputList;
	std::list<unsigned int> _orderedList;
	std::vector<unsigned int> _orderedVector;
public:
	class NegativeInputError : public std::exception {
		virtual const char* what() const throw();
	};
	class NonNumericInputError : public std::exception {
		virtual const char* what() const throw();
	};
	class NoInputError : public std::exception {
		virtual const char* what() const throw();
	};
	void loadList(int nargs, char* args[]) throw(NegativeInputError,NonNumericInputError,NoInputError);
};

*/