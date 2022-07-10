#include "../headers/User.hpp"
#include "../headers/Channel.hpp"

User::User( void ) : _serv_op(false), _chan_op(false), _socket(0), _nick(ES),
	_user_name(ES), _real_name("Server"),
	_pass(ES), _mode(ES) , _registered(false),
	_passOK(false)
{
	DEB  "Construct User " ENDL;
}
User::User( int socket, std::string nick, std::string user_name,
		std::string pass, std::string mode)
		: _socket(socket), _buffer(ES), _nick(nick), _user_name(user_name),
			_real_name("Server"), _pass(pass), _mode(mode),
			_registered(false), _passOK(false)
			{
				if (DEBUG == 2)
					COUT "Construct User " << this->_nick ENDL;
			}

User::~User( void )
{
	COUT "Destruct User." ENDL;
}

bool    User::isOperator(void) const
{
	return _serv_op;
}

int		User::getSocket(void) const
{
	return _socket;
}

const std::string	User::getNick(void) const
{
	return this->_nick;
}
const std::string	User::getUserName(void) const
{
	return this->_user_name;
}
const std::string	User::getRealName(void) const
{
	return this->_real_name;
}
const std::string	User::getPass(void) const
{
	return this->_pass;
}
const std::string	User::getMode(void) const
{
	return this->_mode;
}
bool	User::isRegistered(void) const
{
	return this->_registered;
}

bool	User::isRestricted(void) const
{
	if (getMode().find('r') != std::string::npos)
		return true;
	return false;
}

void	User::setSocket(int socket)
{
	_socket = socket;
}

void	User::setNick(std::string nick)
{
	_nick = nick;
}
void	User::setUserName(std::string user_name)
{
	_user_name = user_name;
}
void	User::setRealName(std::string real_name)
{
	_real_name = real_name;
}
void	User::setPass(std::string pass)
{
	_pass = pass;
}
void	User::setRegister(void)
{
	_registered = true;
}
void	User::setServOp(bool status)
{
	_serv_op = status;
}

void	User::setChanOp(bool status)
{
	_chan_op = status;
}

void	User::addMode(char toadd, bool isOperator)
{
	if (isOperator)
	{
		if (_mode.find(toadd) == std::string::npos)
		{
			if (toadd == 'o')
				setServOp(true);
			_mode += toadd;
		}
		return ;
	}
	if (_mode.find(toadd) == std::string::npos &&
			(toadd == 'r' || toadd == 'i'))
		_mode += toadd;
}

void	User::delMode(char todel, bool isOperator)
{
	size_t i = _mode.find(todel);
	if (isOperator)
	{
		if (i != std::string::npos)
		{
			if (todel == 'o')
				setServOp(false);
			_mode.erase(i, 1);
		}
		return ;
	}
	if (i != std::string::npos && todel == 'i')
		_mode.erase(i, 1);
}

void	User::updateMode(char sign, char mode, bool isOperator)
{
	if (sign == '+')
		addMode(mode, isOperator);
	else
		delMode(mode, isOperator);
}

bool	User::operator==(User* user) const
{
	if (this->_nick == user->_nick)
		return true;
	return false;
}

void	User::addBuffer(std::string toadd)
{
	if (!toadd.empty())
		_buffer += toadd;
}

bool	User::containsCommand() const
{
	if (_buffer.find("\r\n") != std::string::npos)
		return true;
	return false;
}

std::string User::getCommand() const
{
	return _buffer.substr(0, _buffer.find("\r\n"));
}

void	User::eraseCommand()
{
	_buffer.erase(0, _buffer.find("\r\n") + 2);
}

std::string	User::getChannelList() const
{
	std::string list;
	for (std::map <Channel*, std::set<char> >::const_iterator it = _chan_and_modes.begin();
	it != _chan_and_modes.end(); it++)
	{
		if (!it->first->isPrivate() && !it->first->isSecret())//chan is not private nor secret
			list += it->first->getName() + " ";
	}
	return list;
}

void	User::setPassOK(void)
{
	_passOK = true;
}
bool	User::getPassOK() const
{
	return _passOK;
}

void	User::addChanAndMode(Channel *chan, const char &mode)
{
	_chan_and_modes[chan].insert(mode);
}

void	User::removeModeChannel(Channel *chan, const char &mode)
{
	_chan_and_modes[chan].erase(mode);
}

bool	User::isModeInChannel(Channel *chan, const char &mode)
{
	std::map<Channel*,std::set<char> >::iterator it;
	it = _chan_and_modes.find(chan);
	if (it != _chan_and_modes.end())
	{
		std::set<char>::iterator it2 = _chan_and_modes[chan].find(mode);
		if (it2 != _chan_and_modes[chan].end())
			return true;
	}
	return false;
}

