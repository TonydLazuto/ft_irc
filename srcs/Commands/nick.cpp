#include "../../headers/Commands.hpp"

int	checkNickInSet(const std::string &nick)
{
	if (nick.size() > 9)
		return 1;
	if (is_in_set(nick, NICK_CHAR, 8) == false || is_in_set(nick, NICK_LAST_CHAR, 9) == false)
		return 1;
	return 0;
}

int	checkNickDoublon(const std::string &nick, Server& server)
{
	return (!server.isUserUnique(nick));
}

int	checkNickDelay(User *newUser)
{
	if (newUser == NULL)
		return 0;
	return 0;
}

int	checkNickRestricted(User *newUser)
{
	if (newUser == NULL)
		return 0;
	if (newUser->isRestricted() == true)
		return 1;
	return 0;
}

int		checkNickErrors(const std::string &nick, int fd, Server& server, int size)
{
	User* cur = server.findMatchingUser(fd);

	if (!cur)
	{
		DEB "not exists" ENDL;
		return 1;
	}
	if (size < 2)//nick not provided
	{
		server.send_reply(fd, 431, ES, ES, ES, ES);
		return 1;
	}
	if (checkNickInSet(nick) == true) //nick respect nickname allowed characters
	{
		server.send_reply(fd, 432, nick, ES, ES, ES);
		return 1;
	}
	if (checkNickDoublon(nick, server) == true)//nick is not doublon
	{
		server.send_reply(fd, 433, nick, ES, ES, ES);
		return 1;
	}
	if (checkNickDelay(cur) == true)//user has no delay to change nick again
	{
		server.send_reply(fd, 437, nick, ES, ES, ES);
		return 1;
	}
	if (checkNickRestricted(cur) == true)//user is allowed to change (mode)
	{
		server.send_reply(fd, 484, ES, ES, ES, ES);
		return 1;
	}
	if (nick == "anonymous")
	{
		DEB "anonymous is a protected nick" ENDL;
		return 1;
	}
	if (cur->getPassOK() == false)
	{
		DEB "Pass not set yet" ENDL;
		return 1;
	}
	cur->setNick(nick);
	if (!cur->getUserName().empty())
	{
		server.send_reply(fd, 001, cur->getNick(), cur->getUserName(), server.getServerName(), ES);
		if(!cur->isRegistered())
		{		
			server.send_reply(fd, 002, server.getServerName(), server.getVersion(), ES, ES);
			server.send_reply(fd, 003, server.getDate(), ES, ES, ES);
			server.send_reply(fd, 004, server.getServerName(), server.getVersion(), USER_MODE, CHANNEL_MODE);
			cur->setRegister();
		}
	}

	return 0;
}

void		nick(const std::string &line, int fd, Server& server)
{
	DEB "Pointeur nick fonction, line : " << line ENDL;
	std::vector<std::string>split = ft_split(line, ' ');
	checkNickErrors(split[1], fd, server, split.size());
}
