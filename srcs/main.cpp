#include "../headers/Irc.hpp"
#include "../headers/Server.hpp"
#include "../headers/User.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char **argv)
{
	if (argc != 3)
	{
		CERR "./ircserv <port> <password>" ENDL;
		exit(1);
	}
	launch_serv(argv[1], argv[2]);
}