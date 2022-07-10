#include "../../headers/Commands.hpp"
#include "../../headers/Channel.hpp"

#define N_RPL_NAMREPLY 353

#define N_RPL_ENDOFNAMES 366

void	names(const std::string &line, int fd, Server& server)
{
	std::vector<std::string>    splited = ft_split(line, ' ');
	std::string                 user_list;
	User*                       cur = server.findMatchingUser(fd);
	std::vector<std::string>    chanList;
	Channel*                    chan;

	if (cur && !cur->isRegistered())
		return ;    
	if (splited.size() == 1)
		return ;
	chanList = ft_split(splited[1], ',');
	for (unsigned int i = 0; i < chanList.size(); i++)
	{
		DEB chanList[i] ENDL;
		if ((chan = server.findChannel(chanList[i])) == NULL)
			continue;
		if (chan->isSecret()) //chan is hidden for the names command
			continue;
		for (unsigned int i = 0; i < chan->getClientsSize(); i++)
			user_list += chan->getAClient(i)->getNick() + " ";
		server.send_reply(fd, N_RPL_NAMREPLY, chan->getName(), user_list, ES, ES);
		server.send_reply(fd, N_RPL_ENDOFNAMES, chan->getName(), ES, ES, ES);
		user_list.clear();
	}
}