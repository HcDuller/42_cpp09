/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:47:16 by hde-camp          #+#    #+#             */
/*   Updated: 2023/03/30 19:57:24 by hde-camp         ###   ########.fr       */
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
#include <ctime>
#include <iomanip>

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
	this->sortList();
	this->sortVector();
	std::cout << "Before:	";
	for (std::deque<unsigned int>::iterator it = this->_inputDeque.begin(); it != this->_inputDeque.end(); it++){
		std:: cout << "[" << *it<< "] ";
	}
	std::cout << std::endl;
	//print content of List
	std::cout << "After:	";
	for (std::list<unsigned int>::iterator it = this->_orderedList.begin(); it != this->_orderedList.end(); it++){
		std:: cout << "[" << *it<< "] ";
	}
	std::cout<< std::endl;
	std::cout << std::setprecision(5) << std::fixed <<  "Time to process a range of 5 elements with std::list " << this->_listTime << "μs" << std::endl;
	std::cout << std::setprecision(5) << std::fixed <<  "Time to process a range of 5 elements with std::vector " << this->_vectorTime << "μs" << std::endl;
	//print Content of Vector
	/*
		std::cout << "After:	";
	for (std::vector<unsigned int>::iterator it = this->_orderedVector.begin(); it != this->_orderedVector.end(); it++){
		std:: cout << "[" << *it<< "] ";
	}
	std::cout<< std::endl;
	*/
};
//Public Member Functions - END
//Private Member Functions - START
void PmergeMe::sortList(){
	std::deque<unsigned int> copy(this->_inputDeque);
	std::deque<std::pair<unsigned int, unsigned int> > K_pairs;
	unsigned int bucket[2];
	std::clock_t start = std::clock();

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
	if (copy.size() == 1)
		this->binaryListInsert(copy.front());
	this->_listTime = std::clock() - start;
}
void PmergeMe::sortVector(){
	std::deque<unsigned int> copy(this->_inputDeque);
	std::deque<std::pair<unsigned int, unsigned int> > K_pairs;
	unsigned int bucket[2];
	this->_orderedVector.reserve(this->_inputDeque.size() + 2);
	std::clock_t start = std::clock(); (void)start;
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
		this->_orderedVector.push_back((*it).second);
	}
	for (std::deque<std::pair<unsigned int, unsigned int> >::iterator it = K_pairs.begin(); it < K_pairs.end(); it++){
		this->binaryVectorInsert((*it).first);
	}
	if (copy.size() == 1)
		this->binaryVectorInsert(copy.front());
	this->_vectorTime = std::clock() - start;
}
;
void PmergeMe::binaryVectorInsert(unsigned int value){
	std::vector<unsigned int>::iterator it = std::lower_bound(this->_orderedVector.begin(), this->_orderedVector.end(), value);
	if (it != this->_orderedVector.end())
		this->_orderedVector.insert(it, value);
	else
		this->_orderedVector.insert(this->_orderedVector.begin(), value);
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