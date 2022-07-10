#include "../../headers/Commands.hpp"
#include "../../headers/Channel.hpp"

void	list(const std::string &line, int fd, Server& server)
{
	std::vector<std::string>    split = ft_split(line, ' ');
	Channel*                    cur;
	User*                       user = server.findMatchingUser(fd);
	std::vector<std::string>    all_chans;

	if (user && !user->isRegistered())
		return ;
	if (split.size() <= 1)
	{
		server.listChannel(fd);
		return ;
	}
	all_chans = ft_split(split[1], ',');
	for (std::vector<std::string>::iterator it = all_chans.begin(); it != all_chans.end(); it++)
	{
		cur = server.findChannel(*it);
		if (cur != NULL && !cur->isSecret()) //channel exists and is not secret
			server.send_reply(fd, 322, cur->getName(), "visible", cur->getTopic(), ES);
	}
	server.send_reply(fd, 323, ES, ES, ES, ES);
}