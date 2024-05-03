/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasc <hcarrasc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:00:25 by hcarrasc          #+#    #+#             */
/*   Updated: 2024/05/01 14:42:30 by hcarrasc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_HPP
#define INCLUDE_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

bool		SecondLocation(void);
bool		FtRoot(std::string line);
bool		FirstLocation(std::string line);
bool 		checkPorts(std::vector<int> &Allport);

void		parseError(std::string line, std::string error, int index);

#endif
