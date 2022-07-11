#include "../../headers/Commands.hpp"

void	die(const std::string &line, int fd, Server& server)
{
	std::vector<std::string>	word = ft_split(line, ' ');
	User* 						cur_user = server.findMatchingUser(fd);

	if (cur_user && !cur_user->isRegistered())
		return ;
	if (word.size() > 1)
		return ;
	if (!cur_user->isOperator())
	{
		server.send_reply(fd, 481, ES, ES, ES, ES); //ERR_NOPRIVILEGES
		return ;
	}
	word.clear();
	server.clearAll();
	exit(1);
}
