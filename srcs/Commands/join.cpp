#include "../../headers/Commands.hpp"
#include "../../headers/Channel.hpp"

#define J_ERR_NEEDMOREPARAMS 461
#define J_ERR_INVITEONLYCHAN 473
#define J_ERR_CHANNELISFULL 471
#define J_ERR_NOSUCHCHANNEL 403
#define J_ERR_TOOMANYTARGETS 407
#define J_ERR_CHANNELISFULL 471
#define J_ERR_INVITEONLYCHAN 473
#define J_ERR_BANNEDFROMCHAN 474
#define J_ERR_BADCHANNELKEY 475
#define J_ERR_BADCHANMASK 476
#define J_ERR_TOOMANYCHANNELS 405
#define J_ERR_UNAVAILRESOURCE 437
#define J_RPL_TOPIC 332
#define J_RPL_NAMREPLY 353
#define J_RPL_ENDOFNAMES 366

void	not_enough_parameters(int fd, Server& server)
{
	server.send_reply(fd, J_ERR_NEEDMOREPARAMS, "join:", ES, ES, ES);
}

void	joinChannel_and_send_replies(int fd, Server& server, std::string& chaname, const std::string& key)
{
	if (server.check_first_char_channel(chaname) != 0)
		return ;

	Channel*	chan = server.findChannel(chaname);
	User*		user = server.findMatchingUser(fd);
	int			joined = chan->joinChannel(user, key);
	DEB "joined = " << joined ENDL;

	if (joined == 0)//join autorized
	{
		server.send_chan_message(user, "JOIN", chaname, ES);
		if (chan->getTopic() != ES)
			server.send_reply(fd, J_RPL_TOPIC, chan->getName(), chan->getTopic(), ES, ES);
		server.parseCmd("NAMES " + chan->getName(), fd);
	}
	else if (joined == 2)
		server.send_reply(fd, J_ERR_BADCHANNELKEY, chan->getName(), ES, ES, ES);
	else if (joined == 3)
		server.send_reply(fd, J_ERR_CHANNELISFULL, chan->getName(), ES, ES, ES);
	else if (joined == 4)
		server.send_reply(fd, J_ERR_INVITEONLYCHAN, chan->getName(), ES, ES, ES);
	else if (joined == 5)
		server.send_reply(fd, J_ERR_BANNEDFROMCHAN, chan->getName(), ES, ES, ES);
}

void	ft_handle_two_tabs(std::vector<std::string> & tab1,
			std::vector<std::string> const & tab2, int fd, Server& server)
{
	User *cur = server.findMatchingUser(fd);
	for (unsigned int i = 0; i < tab1.size(); i++)
	{
		if (server.findChannel(tab1[i]) == NULL)
		{
			if (cur->isRestricted())
			{
				DEB "User is restricted and can't create server";
				return ;
			}
			server.addChannel(new Channel(tab1[i], tab2[i]));
			Channel *chan = server.findChannel(tab1[i]);
			cur->addChanAndMode(chan, 'O');
		}
		if (i < tab2.size())
			joinChannel_and_send_replies(fd, server, tab1[i], tab2[i]);
		else
			joinChannel_and_send_replies(fd, server, tab1[i], ES);
	}
}

void	ft_handle_one_tab(std::vector<std::string> & tab, int fd, Server& server)
{
	User *cur = server.findMatchingUser(fd);
	for (unsigned int i = 0; i < tab.size(); i++)
	{
		if (server.findChannel(tab[i]) == NULL)
		{
			if (cur->isRestricted())
			{
				DEB "User is restricted and can't create server";
				return ;
			}
			server.addChannel(new Channel(tab[i]));
			Channel *chan = server.findChannel(tab[i]);
			cur->addChanAndMode(chan, 'O');
		}
		joinChannel_and_send_replies(fd, server, tab[i], ES);
	}
}

void     join(const std::string &line, int fd, Server& server)
{
    std::vector<std::string>	tab = ft_split(line, ' ');
	User*						cur = server.findMatchingUser(fd);

    if (cur && !cur->isRegistered())
		return ;

	DEB "join == " << line ENDL;
    if (tab.size() == 1)
	{
		return not_enough_parameters(fd, server);
	}
	std::vector<std::string> tab1 = ft_split(tab[1].data(), ',');
	if (tab.size() == 2)
	{
		return ft_handle_one_tab(tab1, fd, server);
	}
	if (tab.size() == 3)
	{
		std::vector<std::string> tab2 = ft_split(tab[2].data(), ',');
		if (tab2.size() > tab1.size())
			return not_enough_parameters(fd, server);
		return ft_handle_two_tabs(tab1, tab2, fd, server);
	}
}