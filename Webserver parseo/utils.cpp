/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasc <hcarrasc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:02:01 by hcarrasc          #+#    #+#             */
/*   Updated: 2024/05/01 14:42:24 by hcarrasc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.hpp"

bool	FtRoot(std::string line) {
	std::string arg1;
	std::string arg2;
	int			i = 0;

	std::istringstream iss(line);
	iss >> arg1 >> arg2;
	
	while (arg2[i] && arg2[i] == '"')
		i++;
	if (arg2.length() >= 1 && arg2[i] == '.')
    {
		i++;
		if (arg2[i] == '/') {
			return	true;
		}
    }
    return false;
}

bool	FirstLocation(std::string line) {
	std::string arg1;
	std::string arg2;
	std::string arg3;
	int			i = 0;

	std::istringstream iss(line);
	iss >> arg1 >> arg2;

	if (arg1 != "location:" || arg2.empty() || !arg3.empty())
		return false;
	while (arg2[i] && arg2[i] == '"')
		i++;
	if (arg2.length() >= 1 && arg2[i] == '/')
    {
		i++;
		if (!arg2[i] || arg2[i] == '"') {
			return	true;
		}
    }
	return false;
}

bool	SecondLocation(void) {
	return true;
}

void	parseError(std::string line, std::string error, int index) {
	std:: cout << line << " <--- " << "[line: " << index << "] ";
	std::cerr << error << std::endl;
}

bool checkPorts(std::vector<int> &Allport)
{
	for(std::vector<int>::size_type i = 0; i < Allport.size(); i++)
	{
		for(std::vector<int>::size_type j = i + 1; j < Allport.size(); j ++)
		{
			if(Allport[i] == Allport[j])
			{
				std::cout << Allport[i] << " <---- ";
				return false;
			}
		}
	}
	return true;
}
