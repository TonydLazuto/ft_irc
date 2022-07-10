#include "../../headers/Commands.hpp"

int		checkError(int fd, Server& server,
	std::vector<std::string>& word, std::string& cur_mode)
{
	if (word.size() < 3)
	{
        server.send_reply(fd, 461, "KILL", ES, ES, ES); //ERR_NEEDMOREPARAMSreturn 1;
		return 1;
	}
    if (cur_mode.find('o') == std::string::npos)
	{
        server.send_reply(fd, 481, ES, ES, ES, ES); //ERR_NOPRIVILEGES
		return 1;
	}
    if (server.getUser(word[1]) == NULL)
	{
		DEB "[" << word[1] << "]" ENDL;
        server.send_reply(fd, 401, ES, ES, ES, ES); //ERR_NOSUCHNICK
		return 1;
	}
	return 0;
}

void    kill(const std::string &line, int fd, Server& server)
{
	std::vector<std::string>	word = ft_split(line, ' ');
	User*						cur = server.findMatchingUser(fd);
	std::string					cur_mode;
	User*						target = NULL;
	std::string					message;

    if (cur && !cur->isRegistered())
		return ;
	cur_mode = cur->getMode();
	if (checkError(fd, server, word, cur_mode))
		return ;
	target = server.getUser(word[1]);
	if (target->isOperator())
	{
		DEB "Server Operators can't be killed" ENDL;
		return ;
	}
	for (std::vector<std::string>::const_iterator it = word.begin() + 2; it != word.end(); it++)
		message += *it + " ";
	std::string newline("QUIT ");
	newline += message;
	quit(newline, target->getSocket(), server);
}