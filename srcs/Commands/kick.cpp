#include "../../headers/Commands.hpp"
#include "../../headers/Channel.hpp"

void    kickOne(Server &server, User *& tokick, Channel *& channel, std::string message)
{
	error(message, tokick->getSocket(), server);
	server.send_chan_message(tokick, "PART", channel->getName(), message);
	channel->partWithAClient(tokick->getNick());
}

void     oneChan(int fd, Server& server, std::string chan, User* sender, std::vector<std::string> users, std::string message)
{
	Channel*	cur_chan = server.findChannel(chan);
	User*       target = NULL;

	if (cur_chan == NULL)
	{
		server.send_reply(fd, 403, chan, ES, ES, ES);// ERR_NOSUCHCHANNEL
		return ;
	}
	if (cur_chan->findClient(sender->getNick()) == NULL)
	{
		server.send_reply(fd, 442, chan, ES, ES, ES);// ERR_NOTONCHANNEL
		return ;
	}
	if (!sender->isOperator()
		&& !sender->isModeInChannel(cur_chan, 'o')
		&& !sender->isModeInChannel(cur_chan, 'O'))
	{
		server.send_reply(fd, 482, "cur_channel", ES, ES, ES); //ERR_CHANOPRIVSNEEDED
		return ;
	}
	for (size_t i = 0; i < users.size(); i++)
	{
		target = cur_chan->findClient(users[i]);
		if (target == NULL)
		{
			server.send_reply(fd, 441, users[i], chan, ES, ES);// ERR_USERNOTINCHANNEL
			continue;
		}
		kickOne(server, target, cur_chan, message);
	}
}

int     check_each_error(int fd, Server& server, std::string chan, User* sender, std::string user)
{
	Channel*	cur_chan = server.findChannel(chan);
	User*		target = NULL;

	if (cur_chan == NULL)
	{
		server.send_reply(fd, 403, chan, ES, ES, ES);// ERR_NOSUCHCHANNEL
		return 1;
	}
	if (cur_chan->findClient(sender->getNick()) == NULL)
	{
		server.send_reply(fd, 442, chan, ES, ES, ES);// ERR_NOTONCHANNEL
		return 1;
	}
	target = cur_chan->findClient(user);
	if (target == NULL)
	{
		server.send_reply(fd, 441, user, chan, ES, ES);// ERR_USERNOTINCHANNEL
		return 1;
	}
	if (!sender->isOperator()
		&& !sender->isModeInChannel(cur_chan, 'o')
		&& !sender->isModeInChannel(cur_chan, 'O'))
	{
		server.send_reply(fd, 482, "cur_channel", ES, ES, ES); //ERR_CHANOPRIVSNEEDED
		return 1;
	}
	return 0;
}

void	kick(const std::string &line, int fd, Server& server)
{
	User*						sender = server.findMatchingUser(fd);
	User*						target = NULL;
	std::string					message;
	std::vector<std::string>	channels;
	Channel*					cur_chan = NULL;
	std::vector<std::string>	users;

	if (sender && !sender->isRegistered())
		return ;

	std::vector<std::string>split = ft_split(line, ' ');
	if (split.size() < 3)
	{
		server.send_reply(fd, 461, "KICK", ES, ES, ES);//ERR_NEEDMOREPARAMS
		return ;
	}
	for (size_t i = 2; i < split.size(); i++)
		message += split[i] + " ";
		
	channels = ft_split(split[1], ',');
	users = ft_split(split[2], ',');
	
	if (channels.size() != 1 && channels.size() != users.size())//ERR_BADCHANMASK
	{
		server.send_reply(fd, 476, split[1], ES, ES, ES);
		return ;
	}
	if (channels.size() == 1)
		return oneChan(fd, server, channels[0], sender, users, message);
	for (size_t i = 0; i < channels.size(); i++)
	{
		if (check_each_error(fd, server, channels[i], sender, users[i]) == 1)
			continue;
		cur_chan = server.findChannel(channels[i]);
		target = server.getUser(users[i]);
		kickOne(server, target, cur_chan, message);
	}
	return ;
}