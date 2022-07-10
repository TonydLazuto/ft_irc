#ifndef MESSAGEBUILDER_HPP
# define MESSAGEBUILDER_HPP

# include "Irc.hpp"


# define RPL_WELCOME(nickname, user, localhost) ("Welcome to the Internet Relay Network " + nickname + "!" + user + "@" + localhost)
# define RPL_YOURHOST(servername, ver) ("Your host is " + servername + " running version " + ver)
# define RPL_CREATED(date) ("This server was created " + date)
# define RPL_MYINFO(servername, version, usr_mod, chan_mod) (servername + " " + version + " " + usr_mod + " " + chan_mod)
# define RPL_UMODEIS(usr_mod) (usr_mod)
# define RPL_WHOISUSER(nickname, user, host, realname) (nickname + " " + user + " " + host + " * :" + realname)
# define RPL_WHOISSERVER(nickname, server, serverInfo) (nickname + " " + server + " :" + serverInfo)
# define RPL_WHOISIDLE(nickname, time) (nickname + " " + time + " :seconds idle")
# define RPL_ENDOFWHOIS(nickname) (nickname + " :End of WHOIS list")
# define RPL_WHOISCHANNELS(nickname, chanlist) (nickname + " " + chanlist)
# define RPL_AWAY(nickname, message)( nickname + " :" + message)
# define RPL_WHOISOPERATOR(nickname) (nickname + " :is an IRC operator")
# define RPL_YOUREOPER ":You are now an IRC operator"
# define RPL_NAMREPLY(channel, nicklist) ("= " + channel + " :" + nicklist)
# define RPL_ENDOFNAMES(channel) (channel + " :End of NAMES list")
# define RPL_TOPIC(channel, topic) (channel + " :" + topic)
# define RPL_NOTOPIC(channel) (channel + " :No topic is set")
# define RPL_LIST(channel, visible, topic) (channel + " " + visible + " :" + topic)
# define RPL_LISTEND ":End of LIST"
# define RPL_INVITING(channel, nickname) (channel + " " + nickname)

# define ERR_UMODEUNKNOWNFLAG ":Unknown MODE flag"
# define ERR_USERSDONTMATCH ":Cannot change mode for other users"
# define ERR_NOSUCHNICK(nickname) (nickname + " :No such nick/channel")
# define ERR_NEEDMOREPARAMS(command) (command + " :Not enough parameters")
# define ERR_ALREADYREGISTRED ":Unauthorized command (already registered)"
# define ERR_NOORIGIN ":No origin specified"
# define ERR_NONICKNAMEGIVEN ":No nickname given"
# define ERR_ERRONEUSNICKNAME(nickname) (nickname + " :Erroneous nickname")
# define ERR_NICKNAMEINUSE(nickname) (nickname + " :Nickname is already in use")
# define ERR_UNAVAILRESOURCE(nickname) (nickname + " :Nick is temporarily unavailable")
# define ERR_RESTRICTED ":Your connection is restricted!"
# define ERR_PASSWDMISMATCH ":Password incorrect"
# define ERR_NORECIPIENT(command) (":No recipient given " + command)
# define ERR_NOTEXTTOSEND ":No text to send"
# define ERR_TOOMANYTARGETS(target, code, abort_message) (target + " :" + code + " recipients. " + abort_message)
# define ERR_BADCHANNELKEY(channel) (channel + " :Cannot join channel (+k)")
# define ERR_NOSUCHCHANNEL(channel) (channel + " :No such channel")
# define ERR_NOTONCHANNEL(channel) (channel + " :You're not on that channel")
# define ERR_CHANOPRIVSNEEDED(channel) (channel + " :You're not channel operator")
# define SPE_PONG(sender) ("PONG :" + arg1)
# define ERR_USERNOTINCHANNEL(nick, channel) (nick + " " + channel + " :They aren't on that channel")
# define ERR_BADCHANMASK(channel) (channel + " :Bad Channel Mask")
# define ERR_NOPRIVILEGES ":Permission Denied- You're not an IRC operator"
# define ERR_UNKNOWNMODE(char, channel) (char + " :is unknown mode char to me for " + channel)
# define ERR_USERONCHANNEL(user, channel) (user + " " + channel + " :is already on channel")
# define ERR_INVITEONLYCHAN(channel) (channel + " :Cannot join channel (+i)")
# define ERR_CHANNELISFULL(channel) (channel + " :Cannot join channel (+l)")
# define ERR_BANNEDFROMCHAN(channel) ( channel + " :Cannot join channel (+b)")
# define ERR_CANNOTSENDTOCHAN(channel) ( channel + " :Cannot send to channel")

# define RPL_UNIQOPIS(channel, nickname) (channel + " " + nickname)
# define ERR_KEYSET(channel) ( channel + " :Channel key already set")
# define RPL_INVITELIST(channel, list) (channel + " " + list)
# define RPL_ENDOFINVITELIST(channel) (channel + " :End of channel invite list")
# define RPL_EXCEPTLIST(channel, list) (channel + " " + list)
# define RPL_ENDOFEXCEPTLIST(channel) (channel + " :End of channel exception list")
# define RPL_BANLIST(channel, list) (channel + " " + list)
# define RPL_ENDOFBANLIST(channel) (channel + " :End of channel ban list")
# define RPL_CHANNELMODEIS(channel, mode, mode_params) (channel + " " + mode + " " + mode_params)
// void    send_reply(int fd, int code, std::string arg1, std::string arg2, std::string arg3, std::string arg4);
#endif