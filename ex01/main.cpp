/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:36:34 by hde-camp          #+#    #+#             */
/*   Updated: 2023/03/28 16:26:20 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "RPN.hpp"

int main(int argc,char* argv[]){
	if (argc != 2)
	{
		std::cout << "Incorrect number of arguments." << std::endl;
		return (1);
	}
	RPN calculator;
	calculator.calculate(argv[1]);
	return (0);
}