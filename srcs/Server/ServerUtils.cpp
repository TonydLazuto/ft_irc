#include "../../headers/Server.hpp"

bool    	Server::isUserUnique(User* user) const
{
	for (userVector::const_iterator it = _user_tab.begin(); it != _user_tab.end(); it++)
	{
		if ((*it)->getNick() == user->getNick())
		{
			DEB "NICK EQUAL: "<< (*it)->getNick() ENDL;
			return false;
		}
	}
	return true;
}

bool    	Server::isUserUnique(const std::string &nick) const
{
	for (std::vector<User*>::const_iterator it = _user_tab.begin(); it != _user_tab.end(); it++)
	{
		if ((*it)->getNick() == nick)
		{
			DEB "NICK EQUAL: "<< (*it)->getNick() ENDL;
			return false;
		}
	}
	return true;
}

void		Server::addUser(int fd)
{
	User *user = new User();

	user->setSocket(fd);
	if (fd == _main_socket)
	{
		user->setPass("Server");
		user->setNick("Server");
		user->setUserName("Server");
	}
	_user_tab.push_back(user);
}

void		Server::addSocket(int fd, short events)
{
	t_pollfd fd_new;

	fd_new.fd = fd;
	fd_new.events = events;
	fd_new.revents = 0;
	_socket_tab.push_back(fd_new);
}

void		Server::deleteUserSocket(nfds_t i)
{
	close(_socket_tab[i].fd);
	_socket_tab.erase(_socket_tab.begin() + i);
	_user_tab.erase(_user_tab.begin() + i);
}

User*		Server::findMatchingUser(int socket) const
{
	pollfdVector::const_iterator	res;
	t_pollfd 						temp;

	temp.fd = socket;

	res = find(_socket_tab.begin(), _socket_tab.end(), temp);
	if (res == _socket_tab.end())
	{
		DEB "not found" ENDL;
		return (NULL);
	}
	return _user_tab[res - _socket_tab.begin()];
}

t_pollfd	Server::findMatchingSocket(std::string user) const
{
	userVector::const_iterator	it = _user_tab.begin();

	for (int i = 0; it != _user_tab.end(); it++, i++)
	{
		if ((*it)->getNick() == user)
			return _socket_tab[i];
	}
	return _socket_tab[0];
}

int			Server::findPosSocket(int fd) const 
{
	size_t pos = 0;

	for (; pos < _socket_tab.size(); pos++)
	{
		if (_socket_tab[pos].fd == fd)
			break ;
	}
	return pos;
}

std::string	Server::getPackage(int fd)
{
	char		recvline[MAXLINE + 1];
	int			n = 0;
	std::string buffer;

	memset(recvline, 0, MAXLINE);
	n = recv(fd, recvline, MAXLINE - 1, MSG_DONTWAIT);
	buffer = recvline;
	while (n > 0 && buffer.find("\r\n") == std::string::npos)
	{
		n = recv(fd, recvline, MAXLINE - 1, MSG_DONTWAIT);
		buffer += recvline;
	}
	if (n == -1 && errno != EAGAIN)
	{
		perror("recv");
		exit(1);
	}
	if (n == 0)
	{
		DEB "Socket close by client" ENDL;
		if (findMatchingUser(fd))
		{
			deleteUserQuittingChannel(findMatchingUser(fd));
			deleteUserSocket(findPosSocket(fd));
		}
		// quit("QUIT socket closed", fd, *this);
		close(fd);
		return (ES);
	}
	DEB "Line read is " << buffer ENDL;
	DEB std::endl << "###########" ENDL;
	return (buffer);
}

bool	operator==(const t_pollfd &pollfd1, const t_pollfd &pollfd2)
{
	return (pollfd1.fd == pollfd2.fd);
}
