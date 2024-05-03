#include "include.hpp"

int		spacesCount(std::string line) {
	int space;

	space = 0;
	while (line[space] == '\t' || line[space] == ' ') {
		space++;
	}
	return (space);
}

bool		listenFunction(std::string line, std::vector<int> &ports) {
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
				return false;
			i++;
		}
		int port = std::stoi(auxs);
        if (port > 0 && port <= 65535) {
            ports.push_back(port);
			if (!checkPorts(ports))
				return false;
        }
	}
	return true;
}

bool 	serverFunction(std::string line, int &servCount, int &listCount, int &locaCount, int &first) {
	std::string arg1;
	std::string arg2;
	std::istringstream iss(line);

	iss >> arg1 >> arg2;
	if(arg1 != "server:" || !arg2.empty())
		return false;
	if (servCount == 0) {
		servCount++;
	} else {
		if (listCount == 0 || locaCount == 0)
			return false;
		first = 0;
		listCount = 0;
		locaCount = 0;
	}
	return true;
}

bool	paramsFunction(std::vector<int> &ports, std::string line, int &listCount, int &locaCount) {
	std::string arg1;
	std::string arg2;
	std::string arg3;
	std::istringstream iss(line);

	iss >> arg1 >> arg2 >> arg3;
	if(line.find("servername:") != std::string::npos) {
		if(arg1 != "servername:" || arg2.empty() || !arg3.empty())
			return false;
		return true;
	}
	else if (line.find("listen:") != std::string::npos) {
		if(!listenFunction(line, ports))
			return false;
		listCount++;
		return true;
	}
	else if(line.find("root:") != std::string::npos) {
		if(arg1 != "root:" || !arg3.empty() || !FtRoot(line))
			return false;
		return true;
	}
	else if (line.find("location:") != std::string::npos) {
		locaCount++;
	}
	return true;
}

bool	verifyConf(const std::string &fileName) {
	std::ifstream file(fileName);
	if (!file.is_open()) {
		std::cerr << "Error: No se pudo abrir el archivo" << fileName << std::endl;
		return false;
	}

	std::string 		line;
	std::vector	<int>	ports;

	int					index = 1;
	int					first = 0;
	int					servCount = 0;
	int					listCount = 0;
	int					locaCount = 0;
	
	while (std::getline(file, line)) {
		if (line.empty() || line[0] == '#') {
			continue ;
		}
		if (spacesCount(line) == 0) {
			if (!serverFunction(line, servCount, listCount, locaCount, first)) {
				parseError(line, "Server Error", index);
				file.close();
				return false;
			}
		} else if (spacesCount(line) == 1) {
				if (!paramsFunction(ports, line, listCount, locaCount)) {
					parseError(line, "Params Error", index);
					file.close();
					return false;
				}
				first = servCount;
		} else {
			parseError(line, "Space Error", index);
			file.close();
			return false;
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
