/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:47:16 by hde-camp          #+#    #+#             */
/*   Updated: 2023/03/30 15:44:49 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <deque>
#include <list>
#include <vector>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <utility>
#include <iostream>
#include <algorithm>

//Auxiliar functions prototypes START
bool Pair_compare(std::pair<unsigned int, unsigned int> a, std::pair<unsigned int, unsigned int> b);
//Auxiliar functions prototypes END

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
		ss.clear();
	}
};
void PmergeMe::sort(){
	this->parseList();
	std::cout << "Before:	";
	for (std::deque<unsigned int>::iterator it = this->_inputDeque.begin(); it != this->_inputDeque.end(); it++){
		std:: cout << "[" << *it<< "] ";
	}
	std::cout << std::endl;
	std::cout << "After:	";
	for (std::list<unsigned int>::iterator it = this->_orderedList.begin(); it != this->_orderedList.end(); it++){
		std:: cout << "[" << *it<< "] ";
	}
	std::cout<< std::endl;
};
//Public Member Functions - END
//Private Member Functions - START
void PmergeMe::parseList(){
	std::deque<unsigned int> copy(this->_inputDeque);
	std::deque<std::pair<unsigned int, unsigned int> > K_pairs;
	unsigned int bucket[2];

	while (copy.size() > 1){ //create pairs (already inner-ordered), if odd, there will be a leftover value.;
		bucket[0] = copy.front();
		copy.pop_front();
		bucket[1] = copy.front();
		copy.pop_front();
		if (bucket[0] < bucket[1])
			K_pairs.push_back(std::make_pair(bucket[0],bucket[1]));
		else
			K_pairs.push_back(std::make_pair(bucket[1],bucket[0]));
	}
	std::sort(K_pairs.begin(), K_pairs.end(), Pair_compare);
	for (std::deque<std::pair<unsigned int, unsigned int> >::iterator it = K_pairs.begin(); it < K_pairs.end(); it++){
		this->_orderedList.push_back((*it).second);
	}
	for (std::deque<std::pair<unsigned int, unsigned int> >::iterator it = K_pairs.begin(); it < K_pairs.end(); it++){
		this->binaryListInsert((*it).first);
	}
	
}
void PmergeMe::binaryListInsert(unsigned int value){
	std::list<unsigned int>::iterator it = std::lower_bound(this->_orderedList.begin(), this->_orderedList.end(), value);
	if (it != this->_orderedList.end())
		this->_orderedList.insert(it, value);
	else
		this->_orderedList.push_front(value);
}
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

//Auxiliar functions
bool Pair_compare(std::pair<unsigned int, unsigned int> a, std::pair<unsigned int, unsigned int> b){
	return (a.second < b.second);
}