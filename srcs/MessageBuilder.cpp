#include "../headers/MessageBuilder.hpp"
#include "../headers/Server.hpp"
#include "../headers/Channel.hpp"
#include <stdlib.h>

std::string    find_reply(int code, std::string arg1, std::string arg2, std::string arg3, std::string arg4)
{
    switch (code)
    {
        case 1:
            return RPL_WELCOME(arg1, arg2, arg3);
        case 2:
            return RPL_YOURHOST(arg1, arg2);
        case 3:
            return RPL_CREATED(arg1);
        case 4:
            return RPL_MYINFO(arg1, arg2, arg3, arg4);
        case 221:
            return RPL_UMODEIS(arg1);
        case 301:
            return RPL_AWAY(arg1, arg2);
        case 311:
            return RPL_WHOISUSER(arg1, arg2, arg3, arg4);
        case 312:
            return RPL_WHOISSERVER(arg1, arg2, arg3);
        case 313:
            return RPL_WHOISOPERATOR(arg1);
        case 317:
            return RPL_WHOISIDLE(arg1, arg2);
        case 318:
            return RPL_ENDOFWHOIS(arg1);
        case 319:
            return RPL_WHOISCHANNELS(arg1, arg2);
        case 322:
            return RPL_LIST(arg1, arg2, arg3);
        case 323:
            return RPL_LISTEND;
        case 324:
            return RPL_CHANNELMODEIS(arg1, arg2, arg3);
        case 325:
            return RPL_UNIQOPIS(arg1, arg2);
        case 331:
            return RPL_NOTOPIC(arg1);
        case 332:
            return RPL_TOPIC(arg1, arg2);
        case 341:
            return RPL_INVITING(arg1, arg2);
        case 346 :
            return RPL_INVITELIST(arg1, arg2);
        case 347 :
            return RPL_ENDOFINVITELIST(arg1);
        case 348 :
            return RPL_EXCEPTLIST(arg1, arg2);
        case 349 :
            return RPL_ENDOFEXCEPTLIST(arg1);
        case 353:
            return RPL_NAMREPLY(arg1, arg2);
        case 366:
            return RPL_ENDOFNAMES(arg1);
        case 367 :
            return RPL_BANLIST(arg1, arg2);
        case 368 :
            return RPL_ENDOFBANLIST(arg1);
        case 381:
            return RPL_YOUREOPER;
        case 401:
            return ERR_NOSUCHNICK(arg1);
        case 403:
            return ERR_NOSUCHCHANNEL(arg1);
        case 404:
            return ERR_CANNOTSENDTOCHAN(arg1);
        case 407:
            return ERR_TOOMANYTARGETS(arg1, arg2, arg3);
        case 409:
            return ERR_NOORIGIN;
        case 411:
            return ERR_NORECIPIENT(arg1);
        case 412:
            return ERR_NOTEXTTOSEND;
        case 431:
            return ERR_NONICKNAMEGIVEN;
        case 432:
            return ERR_ERRONEUSNICKNAME(arg1);
        case 433:
            return ERR_NICKNAMEINUSE(arg1);
        case 437:
            return ERR_UNAVAILRESOURCE(arg1);
        case 441:
            return ERR_USERNOTINCHANNEL(arg1, arg2);
        case 442:
            return ERR_NOTONCHANNEL(arg1);
        case 443:
            return ERR_USERONCHANNEL(arg1, arg2);
        case 461:
            return ERR_NEEDMOREPARAMS(arg1);
        case 462:
            return ERR_ALREADYREGISTRED;
        case 464:
            return ERR_PASSWDMISMATCH;
        case 467:
            return ERR_KEYSET(arg1);
        case 471:
            return ERR_CHANNELISFULL(arg1);
        case 472:
            return ERR_UNKNOWNMODE(arg1, arg2);
        case 473:
            return ERR_INVITEONLYCHAN(arg1);
        case 474:
            return ERR_BANNEDFROMCHAN(arg1);
        case 475:
            return ERR_BADCHANNELKEY(arg1);
        case 476:
            return ERR_BADCHANMASK(arg1);
        case 481:
            return ERR_NOPRIVILEGES;
        case 482:
            return ERR_CHANOPRIVSNEEDED(arg1);
        case 484:
            return ERR_RESTRICTED;
        case 501:
            return ERR_UMODEUNKNOWNFLAG;
        case 502:
            return ERR_USERSDONTMATCH;
        case 1000:
            return SPE_PONG(arg1);
        default:
            COUT "The response " << code << " is not into the switch yet(find_reply function)" ENDL;
    }
    return (ES);
}

void    Server::send_reply(int fd, int code, std::string arg1, std::string arg2, std::string arg3, std::string arg4) const
{
    std::string user = findMatchingUser(fd)->getNick();
    // std::string user = "randomUser"; //used for debug!!
    std::string str_code;
    char        temp[30];

    sprintf(temp, "%d", code);
    if (code < 10)
		str_code = std::string(2, '0').append(temp);
	else if (code < 100)
		str_code = std::string(1, '0').append(temp);
    else
        str_code = temp;
    std::string message = ":" + user + "!" + getServerName() + "@localhost " + str_code + " " + user + " " + find_reply(code, arg1, arg2, arg3, arg4) + "\r\n";
    DEB "fd : " << fd << " ->reply sent " << message ENDL;
    if (send(fd, message.c_str(), message.length(), 0) < 0)
    // if (write(fd, message.c_str(), message.length()) < 0) //used for debug!!
    {
        perror("send reply");
        exit(1);
    }
}

void    Server::send_reply_no_header(int fd, int code, std::string arg1, std::string arg2, std::string arg3, std::string arg4) const
{
    std::string message = find_reply(code, arg1, arg2, arg3, arg4) + "\r\n";
    DEB "reply sent (no header) " << message ENDL;
    if (send(fd, message.c_str(), message.length(), 0) < 0)
    {
        perror("send");
        exit(1);
    }
}

void    Server::send_chan_message(User *&sender, std::string cmd, std::string chan, std::string message) const
{
    std::string     reply;
    Channel*        curr_chan = findChannel(chan);
    size_t          users = findChannel(chan)->getClientsSize();

	if (curr_chan->getMode().find('a') != std::string::npos && cmd == "PRIVMSG") //channel is anonymous
		reply = ":anonymous!anonymous@anonymous " + cmd;
	else
		reply = ":" + sender->getNick() + "!" + getServerName() + "@localhost " + cmd;
    if (cmd == "JOIN")
        reply += " :" + chan + "\r\n";
    if (cmd == "PRIVMSG")
        reply += " " + chan + " " + message + "\r\n";
    if (cmd == "PART")
        reply += " " + chan + "\r\n";
    for (size_t i = 0; i < users; i++)
    {
        if ((cmd == "PRIVMSG" && sender->getSocket() == curr_chan->getAClient(i)->getSocket()) ||
            (cmd == "JOIN" && curr_chan->getMode().find("q") != std::string::npos && sender->getSocket() != curr_chan->getAClient(i)->getSocket()) || //mode quiet
            (cmd == "PART" && curr_chan->getMode().find("q") != std::string::npos && sender->getSocket() != curr_chan->getAClient(i)->getSocket())) //mode quiet
            continue;
        send_raw_message(curr_chan->getAClient(i)->getSocket(), reply);
    }
}

void    Server::send_raw_message(int fd, std::string message) const
{
    std::string reply = message + "\r\n";
    DEB "fd: " << fd << " ->reply sent (raw) " << reply ENDL;
    if (send(fd, message.c_str(), message.length(), 0) < 0)
    {
        perror("send");
        exit(1);
    }   
}