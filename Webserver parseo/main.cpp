/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasc <hcarrasc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:51:51 by hcarrasc          #+#    #+#             */
/*   Updated: 2024/05/01 14:36:16 by hcarrasc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.hpp"

int	spacesVerify(std::string line) {
	int space = 0;
	while (line[space] == '\t' || line[space] == ' ') {
		space++;
	}
	return (space);
}

int		listenFunction(std::string line) {
	int					i = 0;
	size_t				auxi;
	std::string			auxs;
	std::string 		arg1;
	std::string 		arg2;
	std::string			arg3;
	std::istringstream 	iss(line);

	iss >> arg1 >> arg2 >> arg3;
	if(arg1 != "listen:" || arg2.empty() || !arg3.empty())
		return false;

	auxi = arg2.find(":");
	if (auxi != std::string::npos) {
		auxs = arg2.substr(auxi + 1);
		
		while (auxs[i]) {
			if (auxs[i] < '0' || auxs[i] > '9')
				return (0);
			i++;
		}
		int port = std::stoi(auxs);
        if (port > 0 && port <= 65535) {
            return port;
        }
	}
	return (0);
}


bool	checkLine(std::string line, int &servCont) {
	std::string arg1;
	std::string arg2;
	std::string arg3;
	std::istringstream iss(line);
	if (spacesVerify(line) == 0) {
		iss >> arg1 >> arg2;
		if (arg1 != "server:" || !arg2.empty())
			return false;
		servCont++;
		return true;
	} else if (spacesVerify(line) == 1) {
		if (servCont == 0) {
			std::cerr << "Error: No 'server'" << std::endl;
			return false; 
		}
		iss >> arg1 >> arg2 >> arg3;
		if(line.find("listen:") != std::string::npos)
		{
			if(arg1 != "listen:" || arg2.empty() || !arg3.empty())
				return false;
			return true;
		}
		else if(line.find("root:") != std::string::npos)
		{
			if(arg1 != "root:" || !arg3.empty() || !FtRoot(line))
				return false;
			return true;
		}
		else if(line.find("servername:") != std::string::npos)
		{
			if(arg1 != "servername:" || arg2.empty() || !arg3.empty())
				return false;
			return true;
		}
	}
	return true;
}

bool	verifyConf(const std::string &fileName) {
	std::ifstream file(fileName);
	if (!file.is_open()) {
		std::cerr << "Error: No se pudo abrir el archivo" << fileName << std::endl;
		return false;
	}

	std::vector<int> 			Ports;

	bool						first = true;
	std::string 				line;
	std::string 				currentLocation;
	int							servCont = 0;
	int							liseCont = 0;
	int							locaCont = 0;
	int							port = 0;
	int							index = 1;
	
	while (std::getline(file, line)) {
		if (line.empty() || line[0] == '#') {
			continue ;
		}
		if (!checkLine(line, servCont)) {
			parseError(line, "checkLine error", index);
			file.close();
			return(false);
		}
		if (line.find("listen:") != std::string::npos && spacesVerify(line) == 1) {
			if ((port = checkPort(line)) == 0) {
				parseError(line, "checkPort Error", index);
				file.close();
				return(false);
			}
			liseCont++;
			Ports.push_back(port);
		}
		if(line.find("location:") != std::string::npos && spacesVerify(line) == 1)
		{
			if (locaCont == 0) {
				if (!FirstLocation(line)) {
					parseError(line, "FirstLocation Error", index);
					file.close();
					return(false);
				}
				locaCont++;
			} else {
				if (!SecondLocation()) {
					parseError(line, "FirstLocation Error", index);
					file.close();
					return(false);
				}
				locaCont++;
			}
		}
		if (line.find("server:") != std::string::npos && spacesVerify(line) == 0) {
			if (!first) {
				if (liseCont == 0 || locaCont == 0) {
					parseError(line, "Error with server", index);
					file.close();
					return(false);
				}
				servCont = 0;
				liseCont = 0;
				locaCont = 0;
			}
			first = false;
		}
		index++;
	}
	file.close();
	return true;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "Error: Invalid arguments cantity" << std::endl;
	}
    verifyConf(argv[1]);
    return 0;
}

// std::istringstream es una clase que proporciona una interfaz para tratar cadenas de texto
// como flujos de entrada, similar a std::cin o un archivo.
