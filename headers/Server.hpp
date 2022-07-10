#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <utility>
#include <algorithm>

#include "Irc.hpp"
#include "User.hpp"
#include "Commands.hpp"
#include <poll.h>

class Channel;

class Server;

typedef struct pollfd t_pollfd;
typedef void (*commandFunction)(const std::string &line, int fd, Server& server); // function pointer type

class Server
{
public:
	
	typedef std::map<std::string, commandFunction>		commandMap;
	typedef	std::vector<t_pollfd>						pollfdVector;
	typedef	std::vector<User*>							userVector;
	typedef	std::vector<Channel*>						channelVector;
	typedef std::map <std::string, std::string>			operMap;

private:
	int				_main_socket;
	std::string		_server_password;
	std::string		_server_name;
	std::string		_version;
	std::time_t		_date;
	

	pollfdVector	_socket_tab;
	userVector		_user_tab;
	channelVector	_channel_tab;

	commandMap		_commands;
	operMap			_operators;
	
	void			initCommands(void);

public:
	Server(int port, std::string pass);
	virtual ~Server( void );

	bool			isUserUnique(User* user) const;
	bool			isUserUnique(const std::string &nick) const;
	void			addUser(int fd);

	t_pollfd*		getSocket(nfds_t i);
	User*			getUser(std::string nick) const;
	nfds_t			getSocketSize(void) const;
	int				getMainSocket(void) const;
	std::string		getServerName(void) const;
	std::string		getServerPassword(void) const;
	std::string		getVersion(void) const;
	std::string		getDate(void) const;
	std::string		getServerInfos(void) const;
	Server::operMap	getOperators(void) const;

	void			addSocket(int fd, short events);
	void			deleteUserSocket(nfds_t i);

	User*			findMatchingUser(int fd) const;
	t_pollfd		findMatchingSocket(std::string user) const ; 
	int				findPosSocket(int fd) const ;

	void			parseCmd(std::string line, int fd);
	std::string     getPackage(int fd);

	void			send_reply(int fd, int code, std::string arg1, std::string arg2, std::string arg3, std::string arg4) const;
	void			send_reply_no_header(int fd, int code, std::string arg1, std::string arg2, std::string arg3, std::string arg4) const;
	void			send_raw_message(int fd, std::string message) const;
	void			send_chan_message(User *&sender, std::string cmd, std::string chan, std::string message) const;
	
	bool			addChannel(Channel *channel);
	Channel*		findChannel(std::string const & channel) const;
	void			deleteUserQuittingChannel(User *user);
	int				check_first_char_channel(std::string &name) const;
	void			listChannel(int fd) const;
	const char&		findUnknownChannelMode(const std::string& mode) const;
};

bool	operator==(const t_pollfd &pollfd1, const t_pollfd &pollfd2);


#endif
