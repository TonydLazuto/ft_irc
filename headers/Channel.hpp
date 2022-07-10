#pragma once

#include "Irc.hpp"
#include "Server.hpp"

#define ANONYMOUS "a"
#define INVITE_ONLY "i"
#define MODERATED "m"
#define NO_MESSAGE "n"
#define QUIET "q"
#define PRIVATE "p"
#define SECRET "s"
#define REOP "r"
#define TOPIC "t"
#define USER_LIMIT "l"
#define KEY "k"

#define BAN "b"
#define EXCEPTION "e"
#define INVITE_ONLY_OVERRIDE "I"

class Channel
{
	public:

	typedef Server::userVector	Clients;
	// typedef Server::userVector	Operators;

    private:
    
    std::string             	_name;
    std::string             	_topic;
    std::string	            	_mode;
    std::string                 _flags;

    Clients      				_clients;


    bool                        _anonymous;
    bool                        _invite_only;
    bool                        _moderated;
    bool                        _no_msg_outside;
    bool                        _quiet;
    bool                        _private;
    bool                        _secret;
    bool                        _reop;
    bool                        _topic_chanop_only;
    bool                        _keyed;
    bool                        _userLimited;


    std::string             	_key;
    size_t						_user_limit;
    
    std::set<std::string>       _whitelist;
    std::set<std::string>       _banlist;
    std::set<std::string>       _exceptlist;
    std::set<std::string>       _invitelist;
    // Operators                   _operators;

    public:

    Channel(std::string name, std::string key = std::string());
    virtual ~Channel();

    const std::string&			getName(void) const;
    const std::string&			getTopic(void) const;
    const std::string&			getKey(void) const;
    const std::string&			getMode(void) const;
    const std::string&			getFlags(void) const;
    User*			            getAClient(size_t i) const;
    size_t			            getClientsSize(void) const;
	const size_t&				getUserLimit(void) const;


    // const std::string&			getIdentifier(void) const;

    void						setName(std::string const & name);
	void						setTopic(std::string const & topic);
    void						setKey(std::string const & key);
    void                        setUserLimit(unsigned int limit);
    void                        addMode(std::string const mode);
    void                        delMode(std::string const mode);

    bool&                       isAnonymous(void);
    bool&                       isInviteOnly(void);
    bool&                       isModerated(void);
    bool&                       noMessageFromChannel(void);
    bool&                       isQuiet(void);
    bool&                       isPrivate(void);
    bool&                       isSecret(void);
    bool&                       reOp(void);
    bool&                       topicSettableForChanOpOnly(void);
    bool&                       isKeyed(void);
    
    bool&                       isUserLimited(void);
    void                        addWhiteList(std::string const &nick);
    void                        removeWhiteList(std::string const &nick);
    bool                        isInWhiteList(const std::string &nick) const;

    void                        addBanList(std::string const &nick);
    void                        removeBanList(std::string const &nick);
    bool                        isInBanList(const std::string &nick) const;
    std::set<std::string>       getBanList() const;

    void                        addExceptList(std::string const &nick);
    void                        removeExceptList(std::string const &nick);
    bool                        isInExceptList(const std::string &nick) const;
    std::set<std::string>       getExceptList() const;

    void                        addInviteList(std::string const &nick);
    void                        removeInviteList(std::string const &nick);
    bool                        isInInviteList(const std::string &nick) const;
    std::set<std::string>       getInviteList() const;

    int                         joinChannel(User* const user, std::string const & key = ES);
    User*                       findClient(std::string const client);
    int                         partWithAClient(std::string const client);
};