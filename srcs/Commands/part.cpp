#include "../../headers/Commands.hpp"
#include "../../headers/Channel.hpp"

#define P_ERR_NEEDMOREPARAMS 461

#define	P_ERR_NOSUCHCHANNEL 403

#define P_ERR_NOTONCHANNEL 442

void	part(const std::string &line, int fd, Server& server)
{
    std::vector<std::string>		splited = ft_split(line, ' ');
	User*							client = server.findMatchingUser(fd);
    Channel*						chan;
	std::string						message;
	std::vector<std::string>		chanList;

	if (client && !client->isRegistered())
        return ;

	if (splited.size() == 1)
	{
		server.send_reply(fd, P_ERR_NEEDMOREPARAMS, "part:", ES, ES, ES);
		return ;
	}
	if (splited.size() >= 2 && splited.size() <= 3)
	{
		chanList = ft_split(splited[1].data(), ',');
		for (unsigned int i = 0; i < chanList.size(); i++)
		{
			if ((chan = server.findChannel(chanList[i])) == NULL)
				server.send_reply(fd, P_ERR_NOSUCHCHANNEL, chanList[i], ES, ES, ES);
			else
			{
				if (chan->findClient(client->getNick()) == NULL)
					server.send_reply(fd, P_ERR_NOTONCHANNEL, chan->getName(), ES, ES, ES);
				else
				{
					if (splited.size() == 3)
						message = splited[2];
					else
						message = client->getNick();
					server.send_chan_message(client, "PART", chanList[i], message);
					chan->partWithAClient(client->getNick());
				}
			}
		}
	}
}