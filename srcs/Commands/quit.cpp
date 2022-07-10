#include "../../headers/Commands.hpp"

void    quit(const std::string &line, int fd, Server& server)
{
	User* cur = server.findMatchingUser(fd);

    if (cur && !cur->isRegistered())
	{
		server.deleteUserSocket(server.findPosSocket(fd));
		return ;
	}
	if (line.find(' ') != std::string::npos)
	{
		std::string linebis(line.begin() + line.find(' '), line.end());
		error(linebis, fd, server);
	}
	server.deleteUserQuittingChannel(server.findMatchingUser(fd));
	server.deleteUserSocket(static_cast<nfds_t>(server.findPosSocket(fd)));
}