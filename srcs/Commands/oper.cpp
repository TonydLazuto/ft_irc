#include "../../headers/Commands.hpp"

int checkError(int fd, Server &server, std::vector<std::string> word)
{
	Server::operMap				cur_operators = server.getOperators();
	Server::operMap::iterator	it = cur_operators.find(word[1]);

	if (word.size() != 3)
	{
		server.send_reply(fd, 461, "OPER", ES, ES, ES); // ERR_NEEDMOREPARAMS
		return 1;
	}
	if (it == cur_operators.end())
		return 1;
	if (it->second.compare(word[2]) != 0)
	{
		server.send_reply(fd, 464, ES, ES, ES, ES); // ERR_PASSWDMISMATCH
		return 1;
	}
	return 0;
}

void oper(const std::string &line, int fd, Server &server)
{
	std::vector<std::string>	word = ft_split(line, ' ');
	User*						cur = server.findMatchingUser(fd);

	if (cur && !cur->isRegistered())
        return ;

	if (checkError(fd, server, word))
		return ;
	cur->setServOp(true);
	server.send_reply(fd, 381, ES, ES, ES, ES); // RPL_YOUREOPER
	std::string modeLine = "MODE " + cur->getNick() + " +o";
	mode(modeLine, fd, server);
}
