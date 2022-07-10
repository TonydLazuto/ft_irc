#include "../../headers/Server.hpp"

t_pollfd*	Server::getSocket(nfds_t i)
{
	if (_socket_tab.empty())
		return (NULL);
	return (&_socket_tab[i]);
}

User*	Server::getUser(std::string nick) const
{
	if (_user_tab.empty())
		return (NULL);
	for (userVector::const_iterator it = _user_tab.begin(); it != _user_tab.end(); it++)
	{
		if ((*it)->getNick() == nick)
		{
			return _user_tab[it - _user_tab.begin()];
		}
	}
	return (NULL);
}

nfds_t		Server::getSocketSize(void) const
{
	return _socket_tab.size();
}

int	Server::getMainSocket(void) const
{
	return _main_socket;
}

std::string Server::getServerName(void) const
{
	return _server_name;
}

Server::operMap	Server::getOperators(void) const
{
	return (_operators);
}

std::string Server::getServerPassword(void) const
{
	return _server_password;
}

std::string Server::getVersion(void) const
{
	return _version;
}

std::string Server::getDate(void) const
{
	char mbstr[100];
    std::strftime(mbstr, sizeof(mbstr), "%A %c", std::localtime(&_date));
	return mbstr;
}
std::string Server::getServerInfos(void) const
{
	return "Server : " + getServerName() + " :" + getVersion() + ", created on " + getDate();
}