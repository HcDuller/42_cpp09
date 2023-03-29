/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:34:07 by hde-camp          #+#    #+#             */
/*   Updated: 2023/03/29 19:41:55 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "PmergeMe.hpp"

int main(int argc, char *argv[]){
	if (argc < 2)
	{
		std::cout << RED << "This Program needs at least a argument" << RESET << std::endl;
		return (1);
	}
	PmergeMe sorter;
	sorter.loadList(argc - 1, &argv[1]);
	return (0);
}