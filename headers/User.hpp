#ifndef USER_HPP
# define USER_HPP

#include <iostream>
#include <string>
#include <map>
#include <set>
#include "Irc.hpp"
# define USER_MODE "iroO"

class Channel;

class User
{
protected:
	bool									_serv_op;
	bool									_chan_op;
	int										_socket;
	std::string								_buffer;
	std::string								_nick;
	std::string								_user_name;
	std::string								_real_name;
	std::string								_pass;
	std::string								_mode;
	bool									_registered;
	std::map <Channel*, std::set<char> >	_chan_and_modes;
	bool									_passOK;
	
public:
	User( void );
	virtual ~User( void );

	User( int socket, std::string nick, std::string user,
		std::string pass, std::string mode);

	bool    isOperator(void) const; // isServOp()

	int					getSocket(void) const;
	const std::string	getNick(void) const;
	const std::string	getUserName(void) const;
	const std::string	getPass(void) const;
	const std::string	getMode(void) const;
	const std::string	getRealName(void) const;
	bool				isRegistered(void) const;
	bool				isRestricted(void) const;

	void	setNick(std::string nick);
	void	setSocket(int socket);
	void	setUserName(std::string user);
	void	setRealName(std::string user);
	void	setPass(std::string pass);
	void	updateMode(char sign, char mode, bool isOperator);
	void	addMode(char mode, bool isOperator);
	void	delMode(char mode, bool isOperator);
	void	setRegister(void);
	void	setServOp(bool status);
	void	setChanOp(bool status);

	void		addBuffer(std::string toadd);
	bool		containsCommand() const;
	std::string	getCommand() const;
	void		eraseCommand();

	void	setPassOK(void);
	bool	getPassOK() const;
	void	addChanAndMode(Channel *chan, const char &mode);
	void	removeModeChannel(Channel *chan, const char &mode);
	bool	isModeInChannel(Channel *chan, const char &mode);

	bool	operator==(User* user) const;

	std::string	getChannelList() const;

};

#endif

