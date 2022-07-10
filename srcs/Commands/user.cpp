#include "../../headers/Commands.hpp"

int		checkUserErrors(const std::vector<std::string> & split, int fd, Server& server)
{
	User	*cur = server.findMatchingUser(fd);

	if (cur == NULL)
		return 1;
	if (split.size() < 5) //not enough arguments
	{
		server.send_reply(fd, 461, "USER", ES, ES, ES);
		return 1;
	}
	if (cur->getPassOK() == false)
	{
		DEB "Pass not set yet" ENDL;
		return 1;
	}
	if (cur->isRegistered()) //user is already registered
	{
		server.send_reply(fd, 462, ES, ES, ES, ES);
		return 1;
	}
	return 0;
}

void	user(const std::string &line, int fd, Server& server)
{
	std::vector<std::string>	split = ft_split(line, ' ');
	std::string					real_name;
	User						*cur;

	DEB "Pointeur user fonction" ENDL;

	if (checkUserErrors(split, fd, server) == 1)
		return ;
	real_name = split[4];
	real_name.erase(real_name.begin());

	cur = server.findMatchingUser(fd);
	if (cur == NULL)//user is not made to create a new user, just add infos during connection
		return ;
	cur->setUserName(split[1]);
	for (std::vector<std::string>::iterator it = split.begin() + 5; it != split.end(); it++)
		real_name += " " + *it;
	cur->setRealName(real_name);
	if (!cur->getNick().empty())
	{
		cur->setRegister();
		server.send_reply(fd, 001, cur->getNick(), cur->getUserName(), server.getServerName(), ES);
		server.send_reply(fd, 002, server.getServerName(), server.getVersion(), ES, ES);
		server.send_reply(fd, 003, server.getDate(), ES, ES, ES);
		server.send_reply(fd, 004, server.getServerName(), server.getVersion(), USER_MODE, CHANNEL_MODE);
	}
}
