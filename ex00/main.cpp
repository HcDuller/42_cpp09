/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:51:13 by hde-camp          #+#    #+#             */
/*   Updated: 2023/03/28 12:44:27 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <string>
#include <iostream>

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