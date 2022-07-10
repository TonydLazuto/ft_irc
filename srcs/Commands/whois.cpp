#include "../../headers/Commands.hpp"

#define WI_RPL_AWAY 301
#define WI_RPL_WHOISUSER 311
#define WI_RPL_WHOISSERVER 312
#define WI_RPL_WHOISOPERATOR 313
#define WI_RPL_WHOISIDLE 317
#define WI_RPL_ENDOFWHOIS 318
#define WI_RPL_WHOISCHANNELS 319
#define WI_ERR_NOSUCHNICK 401
#define WI_ERR_NOSUCHSERVER 402
#define WI_ERR_NONICKNAMEGIVEN 431

void	whois(const std::string &line, int fd, Server& server)
{
	DEB "pointer whois" ENDL;
	std::vector<std::string>    tab = ft_split(line, " ,");
	User*                       cur = server.findMatchingUser(fd);
	User*                       target;
	if (cur && !cur->isRegistered())
		return ;
	if (tab.size() == 1)
	{
		server.send_reply(fd, WI_ERR_NONICKNAMEGIVEN, ES, ES, ES, ES);
		return ;
	}
	for (unsigned int i = 1; i < tab.size(); i++)
	{
		target = server.getUser(tab[i]);
		if (target == NULL || target->getMode().find('i') != std::string::npos)
			server.send_reply(fd, WI_ERR_NOSUCHNICK, tab[i], ES, ES, ES);
		else
		{
			server.send_reply(fd, WI_RPL_WHOISUSER, target->getNick(), target->getUserName(), server.getServerName(), target->getRealName());
			server.send_reply(fd, WI_RPL_WHOISSERVER, target->getNick(), server.getServerName(), server.getServerInfos(), ES);
            if (target->isOperator())
                server.send_reply(fd, WI_RPL_WHOISOPERATOR, target->getNick(), ES, ES, ES);
            server.send_reply(fd, WI_RPL_WHOISIDLE, target->getNick(), "0", ES, ES);
            server.send_reply(fd, WI_RPL_WHOISCHANNELS, target->getNick(), target->getChannelList(), ES, ES);
            if (target->getMode().find("a") != std::string::npos)
                server.send_reply(fd, WI_RPL_AWAY, target->getNick(), " is away", ES, ES);
        }
    }
    server.send_reply(fd, WI_RPL_ENDOFWHOIS, tab[1], ES, ES, ES);
}