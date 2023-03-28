/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:03:00 by hde-camp          #+#    #+#             */
/*   Updated: 2023/03/28 16:40:44 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <cctype>
#include <sstream>

void evalChars(char c){
	std::string symbols = "+-*/";
	if (!(std::isdigit(c) || std::isspace(c) || symbols.find(c) != std::string::npos))
	{
		std::string errMsg = "[";
		errMsg= errMsg + c + "] is not a valid argument.";
		throw std::invalid_argument(errMsg.c_str());
	}
}
//Canonical declaration START
RPN::RPN(){
	this->_operatorChar[0] = '+';
	this->_operatorChar[1] = '-';
	this->_operatorChar[2] = '/';
	this->_operatorChar[3] = '*';
	this->_operators[0] = &RPN::sum;
	this->_operators[1] = &RPN::sub;
	this->_operators[2] = &RPN::div;
	this->_operators[3] = &RPN::mult;
};
RPN::RPN(const RPN& origin){
	*this = origin;
};
RPN& RPN::operator=(const RPN& rhe){
	for (int i = 0; i < 4; i++)
	{
		this->_operatorChar[i] = rhe._operatorChar[i];
		this->_operators[i] = rhe._operators[i];
	}
	this->_vals = rhe._vals;
	return (*this);
};
RPN::~RPN(){};
//Canonical decalration END


//member functions START
void RPN::sum(){
	if (this->_vals.size() < 2)
		throw std::invalid_argument("Tried to perform operation over a single value.");
	int top,bot;
	top = this->_vals.top();
	this->_vals.pop();
	bot = this->_vals.top();
	this->_vals.pop();
	this->_vals.push(bot + top);
};
void RPN::sub(){
	if (this->_vals.size() < 2)
		throw std::invalid_argument("Tried to perform operation over a single value.");
	int top,bot;
	top = this->_vals.top();
	this->_vals.pop();
	bot = this->_vals.top();
	this->_vals.pop();
	this->_vals.push(bot - top);
};
void RPN::div(){
	if (this->_vals.size() < 2)
		throw std::invalid_argument("Tried to perform operation over a single value.");
	int top,bot;
	top = this->_vals.top();
	this->_vals.pop();
	bot = this->_vals.top();
	this->_vals.pop();
	this->_vals.push(bot / top);
};
void RPN::mult(){
	if (this->_vals.size() < 2)
		throw std::invalid_argument("Tried to perform operation over a single value.");
	int top,bot;
	top = this->_vals.top();
	this->_vals.pop();
	bot = this->_vals.top();
	this->_vals.pop();
	this->_vals.push(bot * top);
};
void RPN::executeOperator(char const& c){
	RPN::fnPtr f = NULL;
	for (int i = 0; i < 3; i++){
		if (this->_operatorChar[i] == c)
			f = this->_operators[i];
	}
	if (f == NULL)
		throw std::invalid_argument("Operation not found.");
	(this->*f)();
}
void RPN::calculate(char * rpn_ex){
	try{
		std::string expression(rpn_ex);
		std::for_each(expression.begin(), expression.end(), evalChars); //must be executed in a try/catch
		std::stringstream ss(expression);
		int exp_val;
		while (!ss.eof()){
			while (std::isspace(ss.peek()))
				ss.get();
			if (ss.eof())
				break;
			if (std::isdigit(ss.peek()))
			{
				ss >> exp_val;
				this->_vals.push(exp_val);
			}
			else
			{
				exp_val = ss.get();
				this->executeOperator(static_cast<char>(exp_val));
			}
		}
		if (this->_vals.size() != 1)
			throw std::invalid_argument("Expression does not coaslesce into a single value.");
		std::cout << this->_vals.top() << std::endl;
	}catch(std::exception& e){
		std::cout << e.what() << std::endl;
	}
}
