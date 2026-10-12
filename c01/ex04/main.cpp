#include <iostream>
#include <fstream>
#include <string>

std::string	string_replace(const std::string &s1, const std::string &s2, std::string input)
{
	size_t	pos = 0;

	pos = input.find(s1);
	while (pos != std::string::npos)
	{
		input.erase(pos, s1.length());
		input.insert(pos, s2);
		pos = input.find(s1, pos + s2.length());
	}
	return (input);
}

int	main(int ac, char **av)
{
	if (ac != 4)
	{
		std::cerr << "usage: " << av[0] << " <filename> <s1> <s2>" << std::endl;
		return (1);
	}

	std::string s1 = av[2];
	std::string s2 = av[3];
	std::string filename = std::string(av[1]) + ".replace";
	std::string line;
	std::string content;

	if (s1.empty())
	{
		std::cerr << "error: s1 must not be empty" << std::endl;
		return (1);
	}
	std::ifstream infile(av[1]);
	if (!infile)
	{
		std::cerr << "error opening infile" << std::endl;
		return (1);
	}
	// read the whole file, putting back the '\n' that getline removes
	// (except after the last line if the file did not end with one)
	while (getline(infile, line))
	{
		content += line;
		if (!infile.eof())
			content += '\n';
	}
	if (infile.bad())
	{
		std::cerr << "error reading infile" << std::endl;
		return (1);
	}

	std::ofstream outfile(filename.c_str(), std::ofstream::out);
	if (!outfile)
	{
		std::cerr << "error opening outfile" << std::endl;
		return (1);
	}
	outfile << string_replace(s1, s2, content);
	if (!outfile)
	{
		std::cerr << "error writing to outfile" << std::endl;
		return (1);
	}
	return (0);
}
