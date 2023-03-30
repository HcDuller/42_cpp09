/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:47:16 by hde-camp          #+#    #+#             */
/*   Updated: 2023/03/30 17:09:02 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <deque>
#include <list>
#include <vector>
#include <exception>
#include <stdexcept>
#include <ctime>

#define BLACK  "\033[30m"
#define RED  "\033[31;1m"
#define GREEN  "\033[32;1m"
#define YELLOW  "\033[33;1m"
#define BLUE  "\033[34;1m"
#define MAGENTA  "\033[35;1m"
#define CYAN  "\033[36;1m"
#define WHITE  "\033[37;1m"
#define RESET  "\033[0m"

class PmergeMe
{
public:
	class NegativeInputError : public std::exception
	{
		virtual const char *what() const throw();
	};
	class NonNumericInputError : public std::exception
	{
		virtual const char *what() const throw();
	};
	class NoInputError : public std::exception
	{
		virtual const char *what() const throw();
	};

private:
	std::deque<unsigned int> _inputDeque;
	std::list<unsigned int> _orderedList;
	std::vector<unsigned int> _orderedVector;
	unsigned long int _listTime;
	unsigned long int _vectorTime;
	void binaryListInsert(unsigned int value);
	void binaryVectorInsert(unsigned int value);
	void sortList();
	void sortVector();
public:
	PmergeMe();
	PmergeMe(const PmergeMe &origin);
	PmergeMe &operator=(const PmergeMe &rhe);
	~PmergeMe();
	void sort();
	void loadList(int nargs, char *args[]) throw(NegativeInputError, NonNumericInputError, NoInputError,std::invalid_argument);
};
