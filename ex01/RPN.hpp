/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:37:40 by hde-camp          #+#    #+#             */
/*   Updated: 2023/03/28 16:21:28 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <stack>

class RPN
{
private:
 	typedef void (RPN::*fnPtr)(void);
  	fnPtr _operators[4];
	char _operatorChar[4];
	std::stack<int> _vals;
	void sum();
	void sub();
	void div();
	void mult();
	void executeOperator(char const& c);
public:
	void calculate(char * rpn_ex);
	RPN();
	RPN(const RPN& origin);
	RPN& operator=(const RPN& rhe);
	~RPN();
};