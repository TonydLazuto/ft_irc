#include "../../headers/Server.hpp"
#include "../../headers/Channel.hpp"

bool		Server::addChannel(Channel *channel)
{
	_channel_tab.push_back(channel);
	return true;
}

Channel*	Server::findChannel(std::string const & namechannel) const
{
	if (_channel_tab.empty())
		return (NULL);
	for (channelVector::const_iterator it = _channel_tab.begin(); it != _channel_tab.end(); it++)
	{
		if ((*it)->getName() == namechannel)
			return _channel_tab[it - _channel_tab.begin()];
	}
	return (NULL);
}

void		Server::deleteUserQuittingChannel(User *client)
{
	for (channelVector::iterator it = _channel_tab.begin(); it != _channel_tab.end(); it++)
	{
		send_chan_message(client, "PART", (*it)->getName(), ES);
		(*it)->partWithAClient(client->getNick());
	}
}

int			Server::check_first_char_channel(std::string &name) const
{
	if (name[0] == '#' || name[0] == '+' || name[0] == '!' || name[0] == '&')
		return 0;
	return 1;
}

void		Server::listChannel(int fd) const
{
	for(std::vector<Channel*>::const_iterator it = _channel_tab.begin(); it != _channel_tab.end(); it++)
		send_reply(fd, 322, (*it)->getName(), "visible", (*it)->getTopic(), ES);
    send_reply(fd, 323, ES, ES, ES, ES);
}

const char&	Server::findUnknownChannelMode(const std::string& mode) const
{
	std::string channelmodes = CHANNEL_MODE;
	std::string::const_iterator it = mode.begin();
	for (; it != mode.end(); ++it)
    {
        if (channelmodes.find(*it) == std::string::npos)
            break;
    }
	return *it;
}