#include "../../headers/Commands.hpp"

void    error(const std::string &line, int fd, Server& server)
{
	User*   cur = server.findMatchingUser(fd);

	if (cur && !cur->isRegistered())
		return ;	
	if (line.find(" ") == std::string::npos)
		return ;
	std::string message(line.begin() + line.find(" "), line.end());
	message += "\r\n";
	server.send_raw_message(fd, message);
	return ;
}