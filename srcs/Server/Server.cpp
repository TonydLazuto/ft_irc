#include "../../headers/Server.hpp"

Server::Server(int port, std::string pass)
	: _server_password(pass), _server_name(SERVER_NAME),
	_version(VERSION), _date(std::time(NULL))
{
	COUT "Server waiting on port " << port ENDL;

	struct sockaddr_in  servaddr;
	const int			enable = 1;

	_main_socket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (_main_socket < 0)
		exit(1);
	if (setsockopt(_main_socket, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(enable)) < 0)
    	perror("setsockopt(SO_REUSEADDR) failed");
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family         = AF_INET;
	servaddr.sin_addr.s_addr    = htonl(INADDR_ANY);
	servaddr.sin_port           = htons(port);

	if ((bind(_main_socket, (SA *) &servaddr, sizeof(servaddr))) < 0)
	{
		fprintf(stdout, "bind\n");
		exit(1);
	}

	if ((listen(_main_socket, 0)) < 0)
	{
		fprintf(stdout, "listen\n");
		exit(1);
	};
	addSocket(_main_socket, POLLIN);
	addUser(_main_socket);
	initCommands();

	_operators["John"] = "johnmdp"; //kill message
	_operators["Smith"] = "smithmdp"; //restart message
	_operators["1"] = "1"; //restart message
}

Server::~Server( void )
{
	DEB "Destruct Server." ENDL;
}

void	Server::initCommands(void)
{
	_commands["CAP"] = cap;
	_commands["PASS"] = pass;
	_commands["NICK"] = nick;
	_commands["OPER"] = oper;
	_commands["USER"] = user;
	_commands["MODE"] = mode;
	_commands["WHOIS"] = whois;
	_commands["PING"] = ping;
	_commands["JOIN"] = join;
	_commands["PART"] = part;
	_commands["NAMES"] = names;
	_commands["PRIVMSG"] = privateMessage;
	_commands["NOTICE"] = privateMessage;
	_commands["QUIT"] = quit;
	_commands["TOPIC"] = topic;
	_commands["LIST"] = list;
	_commands["kill"] = kill;
	_commands["KICK"] = kick;
	_commands["INVITE"] = invite;
}

