#include "../headers/Commands.hpp"

int find_a_delimiter(std::string tosplit, std::string delimiter)
{
	for (unsigned int i = 0; i < tosplit.length(); i++)
	{
		for (unsigned int j = 0; j < delimiter.length(); j++)
		{
			if (delimiter[j] == tosplit[i])
				return i;
		}
	}
	return -1;
}

int find_a_delimiter_at_beginning(std::string tosplit, std::string delimiter)
{
	for (unsigned int j = 0; j < delimiter.length(); j++)
	{
		if (delimiter[j] == tosplit[0])
			return j;
	}
	return -1;
}

std::vector<std::string> ft_split(std::string tosplit, std::string delimiter)
{
	std::vector<std::string>res;

	while(!tosplit.empty())
	{
		int pos = find_a_delimiter(tosplit, delimiter);

		if (pos == -1)
			pos = tosplit.size();
		res.push_back(std::string(tosplit.begin(), tosplit.begin() + pos));
		tosplit.erase(0, pos);
		while (find_a_delimiter_at_beginning(tosplit, delimiter) != -1 && !tosplit.empty())
		{
			tosplit.erase(0, 1);
		}
	}
	return res;
}

std::vector<std::string> ft_split(std::string tosplit, char delimiter)
{
	std::vector<std::string>res;

	while(!tosplit.empty())
	{
		size_t pos = tosplit.find(delimiter);

		if (pos == std::string::npos)
			pos = tosplit.size();
		res.push_back(std::string(tosplit.begin(), tosplit.begin() + pos));
		tosplit.erase(0, pos);
		while (tosplit[0] == delimiter && !tosplit.empty())
			tosplit.erase(0, 1);
	}
	return res;
}

bool    is_in_set(const std::string& str, const std::string& str2)
{
	for (std::string::const_iterator it = str.begin(); it != str.end(); ++it)
	{
		if (str2.find(*it) == std::string::npos)
			return false;
	}
	return true;
}

bool    is_in_set(const std::string& str, const std::string& str2, size_t size)
{
	size_t i = 0;

	for (std::string::const_iterator it = str.begin(); it != str.end() && i < size; ++it)
	{
		if (str2.find(*it) == std::string::npos)
			return false;
	}
	return true;
}

bool    is_in_set(const char& character, const std::string& str2)
{
	if (str2.find(character) == std::string::npos)
		return false;
	return true;
}