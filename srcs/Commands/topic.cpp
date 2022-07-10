#include "../../headers/Commands.hpp"
#include "../../headers/Channel.hpp"

void	topic(const std::string &line, int fd, Server& server)
{
	std::vector<std::string>    split = ft_split(line, ' ');
	User                        *sender = server.findMatchingUser(fd);
	Channel                     *chan;

    if (sender && !sender->isRegistered())
        return ;
    if (split.size() <= 1)
    {
        server.send_reply(fd, 461, "TOPIC", ES, ES, ES);
        return ;
    }
    chan = server.findChannel(split[1]);
    if (chan == NULL)
        return ;
    if (chan->isSecret()) //channel is hidden in topic command
        return ;
    if (chan->findClient(sender->getNick()) == NULL)
    {
        server.send_reply(fd, 442, split[1], ES, ES, ES);
        return ;
    }
    if (chan->topicSettableForChanOpOnly() == true && sender->isOperator() == false)
    {
        server.send_reply(fd, 482, chan->getName(), ES, ES, ES);
        return ;
    }
    split[2].erase(0, 1);
    if (split.size() >= 2)
        chan->setTopic(split[2]);
    if (chan->getTopic().empty() == 1)
        server.send_reply(fd, 331, split[1], ES, ES, ES);
    else
        server.send_reply(fd, 332, split[1], split[2], ES, ES);
}
