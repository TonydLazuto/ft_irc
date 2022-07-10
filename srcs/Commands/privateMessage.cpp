#include "../../headers/Commands.hpp"
#include "../../headers/Channel.hpp"

int     checkError(std::vector<std::string>split, int fd, Server& server, User*& receiver)
{
	size_t size = split.size();

	if (size <= 1 || split[1][0] == ':' ) //no recipient
	{
		server.send_reply(fd, 411, split[0], ES, ES, ES);
		return 1;
	}
	if (size <= 2)
	{
		server.send_reply(fd, 412, ES, ES, ES, ES);
		return 1;
	}
	if (size >= 2 && split[2][0] != ':')// too many targets
	{
		server.send_reply(fd, 407, split[1], "407", "Message couldn't be delivered", ES);
		return 1;
	}
	if (receiver == NULL)
	{
		server.send_reply(fd, 401, split[1], ES, ES, ES);
		return 1;
	}
	return 0;
}

int checkChannelError(std::vector<std::string> split, int fd, Server& server, Channel *& channel, User *& sender)
{
	size_t size = split.size();

	if (channel == NULL)//chan doesn't exist
	{
		server.send_reply(fd, 401, split[1], ES, ES, ES);
		return 1;
	}
	if (channel->isModerated() && !sender->isOperator()
		&& !sender->isModeInChannel(channel, 'o')
		&& !sender->isModeInChannel(channel, 'O')
		&& !sender->isModeInChannel(channel, 'v')) //channel is moderated
	{
		server.send_reply(fd, 404, channel->getName(), ES, ES, ES);
		return 1;
	}
	if (size <= 1 || split[1][0] == ':' ) //no recipient
	{
		server.send_reply(fd, 411, split[0], ES, ES, ES);
		return 1;
	}
	if (size <= 2)
	{
		server.send_reply(fd, 412, ES, ES, ES, ES);
		return 1;
	}
	if (size >= 2 && split[2][0] != ':')// too many targets
	{
		server.send_reply(fd, 407, split[1], "407", "Message couldn't be delivered", ES);
		return 1;
	}
	return 0;
}

void	privateMessage(const std::string &line, int fd, Server& server)
{
    User*                       sender = server.findMatchingUser(fd);
    std::vector<std::string>    split = ft_split(line, ' ');
    User*                       receiver;
    std::string                 chan_first = "#&+!";
    std::string                 message;
    Channel*                    channel;
    DEB "Private message function" ENDL;

	if (sender && !sender->isRegistered())
		return ;

    for (size_t i = 2; i < split.size(); i++)
        message += split[i] + " ";
    if (split.size() > 1 && chan_first.find(split[1][0]) != std::string::npos)
    {
        channel = server.findChannel(split[1]);
        if (checkChannelError(split, fd, server, channel, sender) == 1)
            return ;
        server.send_chan_message(sender, "PRIVMSG", split[1], message);
        return ;
    }

    receiver = server.getUser(split[1]);
    if (checkError(split, fd, server, receiver) == 1)
        return ;
    std::string paquet = ":" + sender->getNick() + "!" + server.getServerName() + "@localhost" + " " + line + "\r\n";
    server.send_raw_message(receiver->getSocket(), paquet);
}
