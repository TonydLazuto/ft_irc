#include "../../headers/Commands.hpp"

void    ping(const std::string &line, int fd, Server& server)
{
	std::vector<std::string>	split = ft_split(line, ' ');
	User*						cur = server.findMatchingUser(fd);
	DEB "Tried ping" ENDL;

	if (cur && !cur->isRegistered())
		return ;
	if (split.size() < 2)
	{
		server.send_reply(fd, 409, ES, ES, ES, ES);
		return ;		
	}
	server.send_reply_no_header(fd, 1000, server.getServerName(), split[1], ES, ES);
}
