#ifndef COMMANDS_HPP
# define COMMANDS_HPP

#include "Irc.hpp"
#include "Server.hpp"

class Server;

std::vector<std::string> ft_split(std::string tosplit, char delimiter);
std::vector<std::string> ft_split(std::string tosplit, std::string delimiter);

bool    is_in_set(const std::string& str, const std::string& str2);
bool    is_in_set(const char& character, const std::string& str2);
bool    is_in_set(const std::string& str, const std::string& str2, size_t size);

void	cap(const std::string &line, int fd, Server& server);
void	pass(const std::string &line, int fd, Server& server);
void	nick(const std::string &line, int fd, Server& server);
void	oper(const std::string &line, int fd, Server& server);
void	user(const std::string &line, int fd, Server& server);
void	mode(const std::string &line, int fd, Server& server);
void	channel_mode(const std::string &line, int fd, Server& server);
void	whois(const std::string &line, int fd, Server& server);
void	ping(const std::string &line, int fd, Server& server);
void	join(const std::string &line, int fd, Server& server);
void	part(const std::string &line, int fd, Server& server);
void	names(const std::string &line, int fd, Server& server);
void	privateMessage(const std::string &line, int fd, Server& server);
void	quit(const std::string &line, int fd, Server& server);
void	error(const std::string &line, int fd, Server& server);
void	topic(const std::string &line, int fd, Server& server);
void	list(const std::string &line, int fd, Server& server);
void	kill(const std::string &line, int fd, Server& server);
void	kick(const std::string &line, int fd, Server& server);
void	invite(const std::string &line, int fd, Server& server);

#endif