#include "../headers/Irc.hpp"
#include "../headers/Server.hpp"

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

#define N_RPL_NAMREPLY 353

#define N_RPL_ENDOFNAMES 366

#define J_ERR_NEEDMOREPARAMS 461

#define J_ERR_INVITEONLYCHAN 473

#define J_ERR_CHANNELISFULL 471

#define J_ERR_NOSUCHCHANNEL 403

#define J_ERR_TOOMANYTARGETS 407

#define J_ERR_BANNEDFROMCHAN 474

#define J_ERR_BADCHANNELKEY 475

#define J_ERR_BADCHANMASK 476

#define J_ERR_TOOMANYCHANNELS 405

#define J_ERR_UNAVAILRESOURCE 437

#define J_RPL_TOPIC 332

#define J_RPL_NAMREPLY 353

#define J_RPL_ENDOFNAMES 366

#define P_ERR_NEEDMOREPARAMS 461

#define	P_ERR_NOSUCHCHANNEL 403

#define P_ERR_NOTONCHANNEL 442

#define C_RPL_UMODEIS 221

#define	C_ERR_NOSUCHCHANNEL 403

#define C_ERR_USERNOTINCHANNEL 441

#define C_ERR_NEEDMOREPARAMS 461

#define C_ERR_UNKNOWNMODE 472

#define C_ERR_CHANOPRIVSNEEDED 482

#define C_RPL_CHANNELMODEIS 324

#define C_RPL_UNIQOPIS 325

#define C_RPL_INVITELIST 346
#define C_RPL_ENDOFINVITELIST 347

#define C_RPL_EXCEPTLIST 348
#define C_RPL_ENDOFEXCEPTLIST 349

#define C_RPL_BANLIST 367
#define C_RPL_ENDOFBANLIST 368

#define C_ERR_NOSUCHCHANNEL 403

#define C_ERR_USERNOTINCHANNEL 441

#define C_ERR_NEEDMOREPARAMS 461

#define C_ERR_KEY_SET 467

#define C_ERR_UNKNOWNMODE 472

#define C_ERR_CHANOPRIVSNEEDED 482

void	test_reply(int fd, Server & server)
{

	server.send_reply(fd, C_ERR_NOSUCHCHANNEL, "tab[1]", ES, ES, ES);
	server.send_reply(fd, C_ERR_NEEDMOREPARAMS, "MODE", ES, ES, ES);
	// 	server.send_reply(fd, C_ERR_CHANOPRIVSNEEDED, "chan->getName()", ES, ES, ES);
	server.send_reply(fd, C_ERR_NEEDMOREPARAMS, "MODE", ES, ES, ES);
	server.send_reply(fd, C_ERR_UNKNOWNMODE, "character", ES, ES, ES);
	server.send_reply(fd, C_RPL_UMODEIS, "chan->getMode()", ES, ES, ES);
	server.send_reply(fd, 461, "INVITE", ES, ES, ES); //
	server.send_reply(fd, 401, "word[1]", ES, ES, ES);
	server.send_reply(fd, 443, "word[1]", "word[2]", ES, ES);
	server.send_reply(fd, 442, "word[2]", ES, ES, ES);
	server.send_reply(fd, 482, "word[2]", ES, ES, ES);
	server.send_reply(fd, 341, "word[2]", "word[1]", ES, ES); //RPL_INVITING
	server.send_reply(fd, J_ERR_NEEDMOREPARAMS, "join:", ES, ES, ES);
	server.send_reply(fd, J_RPL_TOPIC, "chan->getName()", "chan->getTopic()", ES, ES);
	server.send_reply(fd, J_ERR_BADCHANNELKEY, "chan->getName()", ES, ES, ES);
	server.send_reply(fd, J_ERR_INVITEONLYCHAN, "chan->getName()", ES, ES, ES);
	server.send_reply(fd, J_ERR_CHANNELISFULL, "chan->getName()", ES, ES, ES);
	server.send_reply(fd, J_ERR_BANNEDFROMCHAN, "chan->getName()", ES, ES, ES);
	server.send_reply(fd, J_ERR_CHANNELISFULL, "chan->getName()", ES, ES, ES);
	server.send_reply(fd, 403," chan", ES, ES, ES);// ERR_NOSUCHCHANNEL
	server.send_reply(fd, 442, "chan", ES, ES, ES);// ERR_NOTONCHANNEL
	server.send_reply(fd, 441, "users[i]", "chan", ES, ES);// ERR_USERNOTINCHANNEL
	server.send_reply(fd, 403, "chan", ES, ES, ES);// ERR_NOSUCHCHANNEL
	server.send_reply(fd, 442, "chan", ES, ES, ES);// ERR_NOTONCHANNEL
	server.send_reply(fd, 441, "user", "chan", ES, ES);// ERR_USERNOTINCHANNEL
	server.send_reply(fd, 461, "KICK", ES, ES, ES);//ERR_NEEDMOREPARAMS
	server.send_reply(fd, 482, "split[2]", ES, ES, ES); //ERR_CHANOPRIVSNEEDED
	server.send_reply(fd, 476, "split[1]", ES, ES, ES);
	server.send_reply(fd, 461, "KILL", ES, ES, ES); //ERR_NEEDMOREPARAMSreturn 1;
	server.send_reply(fd, 481, ES, ES, ES, ES); //ERR_NOPRIVILEGES
	server.send_reply(fd, 401, ES, ES, ES, ES); //ERR_NOSUCHNICK
	server.send_reply(fd, 322, "cur->getName()", "visible", "cur->getTopic()", ES);
	server.send_reply(fd, 323, ES, ES, ES, ES);
	server.send_reply(fd, 322, "cur->getName()", "visible", "cur->getTopic()", ES);
	server.send_reply(fd, 323, ES, ES, ES, ES);
	server.send_reply(fd, 431, ES, ES, ES, ES);
	server.send_reply(fd, 432, "nick", ES, ES, ES);
	server.send_reply(fd, 433, "nick", ES, ES, ES);
	server.send_reply(fd, 437, "nick", ES, ES, ES);
	server.send_reply(fd, 484, ES, ES, ES, ES);
	server.send_reply(fd, 001, "cur->getNick()", "cur->getUserName()", "server.getServerName()", ES);
	server.send_reply(fd, 002, "server.getServerName()", "server.getVersion()", ES, ES);
	server.send_reply(fd, 003, "server.getDate()", ES, ES, ES);
	server.send_reply(fd, 004, "server.getServerName()", "server.getVersion()", USER_MODE, CHANNEL_MODE);
	server.send_reply(fd, 461, "OPER", ES, ES, ES); // ERR_NEEDMOREPARAMS
	server.send_reply(fd, 464, ES, ES, ES, ES); // ERR_PASSWDMISMATCH
	server.send_reply(fd, 381, ES, ES, ES, ES); // RPL_YOUREOPER
	server.send_reply(fd, P_ERR_NEEDMOREPARAMS, "part:", ES, ES, ES);
	server.send_reply(fd, P_ERR_NOSUCHCHANNEL, "tab1[i]", ES, ES, ES);
	server.send_reply(fd, P_ERR_NOTONCHANNEL, "chan->getName()", ES, ES, ES);
	server.send_reply(fd, 461, "PASS", ES, ES, ES);
	server.send_reply(fd, 462, ES, ES, ES, ES);
	server.send_reply(fd, 409, ES, ES, ES, ES);
	server.send_reply(fd, 411, "split[0]", ES, ES, ES);
	server.send_reply(fd, 412, ES, ES, ES, ES);
	server.send_reply(fd, 407, "split[1]", "407", "Message couldn't be delivered", ES);
	server.send_reply(fd, 401, "split[1]", ES, ES, ES);
	server.send_reply(fd, 401, "split[1]", ES, ES, ES);
	server.send_reply(fd, 404, "channel->getName()", ES, ES, ES);
	server.send_reply(fd, 411, "split[0]", ES, ES, ES);
	server.send_reply(fd, 412, ES, ES, ES, ES);
	server.send_reply(fd, 407, "split[1]", "407", "Message couldn't be delivered", ES);
	server.send_reply(fd, 461, "TOPIC", ES, ES, ES);
	server.send_reply(fd, 442, "split[1]", ES, ES, ES);
	server.send_reply(fd, 482, "chan->getName()", ES, ES, ES);
	server.send_reply(fd, 331, "split[1]", ES, ES, ES);
	server.send_reply(fd, 332, "split[1]", "split[2]", ES, ES);
	server.send_reply(fd, 461, "USER", ES, ES, ES);
	server.send_reply(fd, 462, ES, ES, ES, ES);
	server.send_reply(fd, 001, "cur->getNick()", "cur->getUserName()", "server.getServerName()", ES);
	server.send_reply(fd, 002, "server.getServerName()", "server.getVersion()", ES, ES);
	server.send_reply(fd, 003, "server.getDate()", ES, ES, ES);
	server.send_reply(fd, 004, "server.getServerName()", "server.getVersion()", USER_MODE, CHANNEL_MODE);
	server.send_reply(fd, 461, "MODE", ES, ES, ES); //ERR_NEEDMOREPARAMS
	server.send_reply(fd, 501, ES, ES, ES, ES); //ERR_UMODEUNKNOWNFLAG
	server.send_reply(fd, 502, ES, ES, ES, ES); //ERR_USERSDONTMATCH
	server.send_reply(fd, 221, "cur->getMode()", ES, ES, ES); // RPL_UMODEIS
	server.send_reply(fd, WI_ERR_NONICKNAMEGIVEN, ES, ES, ES, ES);
	server.send_reply(fd, WI_ERR_NOSUCHNICK, "tab[i]", ES, ES, ES);
	server.send_reply(fd, WI_RPL_WHOISUSER, "user->getNick()", "user->getUserName()", "server.getServerName()", "user->getRealName()");
	server.send_reply(fd, WI_RPL_WHOISSERVER, "user->getNick()", "server.getServerName()", "server.getServerInfos()", ES);
	server.send_reply(fd, WI_RPL_WHOISOPERATOR, "user->getNick()", ES, ES, ES);
	server.send_reply(fd, WI_RPL_WHOISIDLE, "user->getNick()", "0", ES, ES);
	server.send_reply(fd, WI_RPL_WHOISCHANNELS, "user->getNick()", "make_function_to_get_user_channel", ES, ES);
	server.send_reply(fd, WI_RPL_AWAY, "user->getNick()", " is away", ES, ES);
	server.send_reply(fd, WI_RPL_ENDOFWHOIS, "tab[1]", ES, ES, ES);
	server.send_reply(fd, 322, "(*it)->getName()", "visible", "(*it)->getTopic()", ES);
	server.send_reply(fd, 323, ES, ES, ES, ES);

	server.send_reply(fd, C_ERR_NOSUCHCHANNEL, "tab[1]", ES, ES, ES);
	server.send_reply(fd, C_ERR_NEEDMOREPARAMS, "MODE", ES, ES, ES);
	server.send_reply(fd, C_ERR_CHANOPRIVSNEEDED, "chan->getName()", ES, ES, ES);
	server.send_reply(fd, C_ERR_NEEDMOREPARAMS, "MODE", ES, ES, ES);
	server.send_reply(fd, C_ERR_KEY_SET, "chan->getName()", ES, ES, ES);
	server.send_reply(fd, C_RPL_BANLIST, "chan->getName()", ES, ES, ES);
	server.send_reply(fd, C_RPL_ENDOFBANLIST, "chan->getName()", ES, ES, ES);
	server.send_reply(fd, C_ERR_NEEDMOREPARAMS, "MODE", ES, ES, ES);
	server.send_reply(fd, C_RPL_EXCEPTLIST, "chan->getName()", ES, ES, ES);
	server.send_reply(fd, C_RPL_ENDOFBANLIST, "chan->getName()", ES, ES, ES);
	server.send_reply(fd, C_ERR_NEEDMOREPARAMS, "MODE", ES, ES, ES);
	server.send_reply(fd, C_RPL_INVITELIST, "chan->getName()", ES, ES, ES);
	server.send_reply(fd, C_RPL_ENDOFINVITELIST, "chan->getName()", ES, ES, ES);
	server.send_reply(fd, C_ERR_NEEDMOREPARAMS, "MODE", ES, ES, ES);
	server.send_reply(fd, C_ERR_NEEDMOREPARAMS, "MODE", ES, ES, ES);
	server.send_reply(fd, C_ERR_USERNOTINCHANNEL, "tab[2 + j]", "chan->getName()", ES, ES);
	server.send_reply(fd, C_ERR_UNKNOWNMODE, "character", ES, ES, ES);
	server.send_reply(fd, C_RPL_CHANNELMODEIS, "chan->getMode()", ES, ES, ES);
	COUT "End of replies test, Bye.." ENDL;
	exit(1);
}

void    launch_serv(std::string port, std::string password)
{
	Server		server(atoi(port.c_str()), password);
	User		*cur = NULL;
	int			ret_poll;
	std::string	recvline;
	std::string	separatedline;
	int			fd;
	
	// test_reply(1, server);
	while(1)
	{
		ret_poll = poll(server.getSocket(0), server.getSocketSize(), 15000);
		if (ret_poll == -1)
		{
			perror("poll");
			exit (1);
		}
		else if (ret_poll == 0)
			continue ;
		for (nfds_t i = 0; i < server.getSocketSize(); i++)
		{
			if ((server.getSocket(i)->revents & POLLIN) == POLLIN)
			{
				server.getSocket(i)->revents = 0;
				if (i == 0)
				{
					fd = accept(server.getMainSocket(), (SA*) NULL, NULL);
					if (fd == -1)
					{
						perror("accept");
						exit(1);
					}
					server.addSocket(fd, POLLIN);
					server.addUser(fd);
				}
				else
				{
					fd = server.getSocket(i)->fd;
				}
				cur = server.findMatchingUser(fd);
				recvline = server.getPackage(fd);
				if (recvline.empty())
					continue ;
				cur->addBuffer(recvline);
				while (cur->containsCommand())
				{
					separatedline = cur->getCommand();
					server.parseCmd(separatedline, fd);
					cur->eraseCommand();
				}
				recvline.clear();
			}
		}
	}
}
