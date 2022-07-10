#include "../headers/Channel.hpp"

Channel::Channel(std::string name, std::string key) :
	_name(name), _topic(ES), _mode(ES), _flags("aimnqpsrtlk"),
	_anonymous(false), _invite_only(false), _moderated(false),
	_no_msg_outside(false), _quiet(false), _private(false),
	_secret(false), _topic_chanop_only(false), _keyed(false),
	_userLimited(false), _key(key), _user_limit(0)
{
	DEB "Construct Channel " << this->_name ENDL;
	if (_key != ES)
	{
		this->isKeyed() = true;
		this->addMode(KEY);
	}
}

Channel::~Channel()
{
	DEB "Destruct Channel." ENDL;
}

const std::string&		Channel::getName(void) const
{
	return _name;
}

const std::string&		Channel::getTopic(void) const
{
	return _topic;
}

const std::string&		Channel::getKey(void) const
{
	return _key;
}

const std::string&		Channel::getMode(void) const
{
	return _mode;
}

const size_t&			Channel::getUserLimit(void) const
{
	return _user_limit;
}

void					Channel::setName(std::string const & name)
{
	_name = name;
}

void					Channel::setTopic(std::string const & topic)
{
	_topic = topic;
}

void					Channel::setKey(std::string const & key)
{
	_key = key;
}

void					Channel::setUserLimit(unsigned int limit)
{
	_user_limit = limit;
}


bool&					Channel::isAnonymous(void)
{
	return _anonymous;
}

bool&					Channel::isInviteOnly(void)
{
	return _invite_only;
}

bool&					Channel::isModerated(void)
{
	return _moderated;
}

bool&					Channel::noMessageFromChannel(void)
{
	return _no_msg_outside;
}

bool&					Channel::isQuiet(void)
{
	return _quiet;
}

bool&					Channel::isPrivate(void)
{
	return _private;
}

bool&					Channel::isSecret(void)
{
	return _secret;
}

bool&					Channel::reOp(void)
{
	return _reop;
}

bool&					Channel::topicSettableForChanOpOnly(void)
{
	return _topic_chanop_only;
}

bool&					Channel::isKeyed(void)
{
	return _keyed;
}

bool&					Channel::isUserLimited(void)
{
	return _userLimited;
}

void					Channel::addMode(std::string mode)
{
	for (std::string::iterator it = mode.begin(); it != mode.end(); ++it)
	{
		if (_mode.empty())
			_mode = *it;
		else if (_mode.find(*it) == std::string::npos)
			_mode += *it;
	}
}

void					Channel::delMode(std::string mode)
{
	for (std::string::iterator it = mode.begin(); it != mode.end(); ++it)
	{
		if (_mode.empty())
			return ;
		size_t pos = _mode.find(*it);
		if (pos != std::string::npos)
			_mode.erase(pos, 1);
	}
}

int						Channel::joinChannel(User* const user, std::string const & key)
{
	if (this->findClient(user->getNick()) != NULL)
	{
		return 1;
	}
	if (isInWhiteList(user->getNick()) || user->isOperator())
	{
		_clients.push_back(user);
		return 0;
	}
	if (this->isKeyed() && this->getKey() != key)
	{
		return 2;
	}
	if (this->isUserLimited() && this->getClientsSize() + 1 > this->getUserLimit())
	{
		return 3;
	}
	if (this->isInviteOnly() && !isInInviteList(user->getNick()))
	{
		return 4;
	}
	if (isInBanList(user->getNick()) && !isInExceptList(user->getNick()))
	{
		return 5;
	}
	_clients.push_back(user);
	return 0;
}

int						Channel::partWithAClient(std::string const client)
{
	Clients::iterator it = _clients.begin();
	for (; it != _clients.end(); it++)
	{
		if ((*it)->getNick() == client)
			break;
	}
	if (it == _clients.end())
		return 1;
	_clients.erase(it);
	return 0;
}

User*					Channel::findClient(std::string const client)
{
	Clients::iterator it = _clients.begin();
	for (; it != _clients.end(); it++)
	{
		if ((*it)->getNick() == client)
			return *it;
	}
	return NULL;
}

size_t					Channel::getClientsSize(void) const
{
	return _clients.size();
}

User*					Channel::getAClient(size_t i) const
{
	if (i >= _clients.size())
		return NULL;
	return (_clients[i]);
}

void					Channel::addWhiteList(const std::string &nick)
{
	_whitelist.insert(nick);
}

void					Channel::removeWhiteList(const std::string &nick)
{
	_whitelist.erase(nick);
}

bool					Channel::isInWhiteList(const std::string &nick) const
{
	std::set<std::string>::iterator it = _whitelist.find(nick);
	if (it == _whitelist.end())
		return false;
	return true;
}

void					Channel::addBanList(const std::string &nick)
{
	_banlist.insert(nick);
}

void					Channel::removeBanList(const std::string &nick)
{
	_banlist.erase(nick);
}

bool					Channel::isInBanList(const std::string &nick) const
{
	std::set<std::string>::iterator it = _banlist.find(nick);
	if (it == _banlist.end())
		return false;
	return true;
}

std::set<std::string>	Channel::getBanList() const
{
	return _banlist;
}

void					Channel::addExceptList(const std::string &nick)
{
	_exceptlist.insert(nick);
}

void					Channel::removeExceptList(const std::string &nick)
{
	_exceptlist.erase(nick);
}

bool					Channel::isInExceptList(const std::string &nick) const
{
	std::set<std::string>::iterator it = _exceptlist.find(nick);
	if (it == _exceptlist.end())
		return false;
	return true;
}

std::set<std::string>	Channel::getExceptList() const
{
	return _exceptlist;
}

void					Channel::addInviteList(const std::string &nick)
{
	_invitelist.insert(nick);
}

void					Channel::removeInviteList(const std::string &nick)
{
	_invitelist.erase(nick);
}

bool					Channel::isInInviteList(const std::string &nick) const
{
	std::set<std::string>::iterator it = _invitelist.find(nick);
	if (it == _invitelist.end())
		return false;
	return true;
}

std::set<std::string>	Channel::getInviteList() const
{
	return _invitelist;
}
