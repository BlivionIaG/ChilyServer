#include "cmdFormat.hpp"

cmdFormat::cmdFormat cmdFormat::parseCommand(std::string entry)
{
	cmdFormat out;

	std::vector<std::string> tmp;
	std::string stmp;

	tmp = split(entry, ' ');
	stmp = tmp[0];
	tmp.erase(tmp.begin());
	out.args = tmp;
	tmp.clear();

	tmp = split(stmp, '@');
	if (tmp.size() > 0)
		out.id = tmp[0];
	if (tmp.size() > 1)
		out.command = tmp[1];
	tmp.clear();

	tmp = split(out.command, ':');
	if (tmp.size() > 0)
		out.command = tmp[0];
	if (tmp.size() > 1)
		out.arglen = std::atoi(tmp[1].c_str());
	tmp.clear();

    if (out.id.length() < 1 || out.command.length() < 1)
	{
		out.valid = false;
	}
	else
	{
		out.valid = true;
	}

	//Arglen correction

	if (out.arglen < out.args.size())
	{
		for (auto i{out.arglen}; i < out.args.size() - 1; ++i)
		{
			out.args[out.arglen - 1] += out.args[i];
		}
		for (auto i{out.arglen}; i < out.args.size() - 1; ++i)
		{
			out.args.erase(out.args.begin() + i);
		}
	}

	return out;
}

void cmdFormat::printCommand(cmdFormat cmd)
{
	if (cmd.valid)
	{
		std::cout << "id : " << cmd.id << std::endl;
		std::cout << "command : " << cmd.command << std::endl;
		std::cout << "arglen : " << cmd.arglen << std::endl;
		for (auto &ref : cmd.args)
		{
			std::cout << ref << "\t";
		}
		std::cout << std::endl;
	}
	else
	{
		std::cout << "Not a valid Command format" << std::endl;
	}
}

void cmdFormat::clearCommand(cmdFormat &cmd)
{
	cmd.args.clear();
	cmd.arglen = -1;
	cmd.command.clear();
	cmd.id.clear();
	cmd.valid = false;
}

std::vector<std::string> cmdFormat::split(const std::string &in, const char &token)
{
	std::vector<std::string> out;
	std::string buffer;

	for (const auto &n : in)
	{
		if (n != token)
			buffer += n;
		else if (n == token && buffer != "")
		{
			out.push_back(buffer);
			buffer = "";
		}
	}
	if (buffer != "")
		out.push_back(buffer);

	return out;
}

std::string cmdFormat::toString(cmdFormat &entry)
{
	auto out = entry.id + "@" + entry.command + ":" + std::to_string(entry.arglen);
	for (const auto &i : entry.args)
	{
		out += " " + i;
	}

	return out;
}
