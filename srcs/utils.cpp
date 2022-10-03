#include "utils.hpp"

std::vector<std::string> split(const std::string &str, std::string delim) {
	std::vector<std::string>	splitedMessage;
	std::size_t 				index;
	std::string					tmp = str;
	std::string					s;

	while (FT_TRUE) {
		if (tmp.find(delim) == 0)
			tmp = tmp.substr(delim.length(), std::string::npos);
		index = tmp.find(delim);
		s = tmp.substr(0, index);
		splitedMessage.push_back(s);
		if (index == std::string::npos)
			break ;
		tmp = tmp.substr(index, std::string::npos);
	}
	return splitedMessage;
}

ft_bool isFileExist(const std::string &filePath)
{
    std::ifstream file(filePath);
    return file.good();
}

std::string fileToString(const std::string &filePath) {
	std::string		str = "";
	std::ifstream	openFile(filePath);

	if(openFile.is_open()) {
		std::string line;
		while(std::getline(openFile, line)) {
			str += line + "\n";
		}
		openFile.close();
	}
	return str;
}

ft_bool isIncluded(const std::string &value, const std::vector<std::string> &array)
{
	return (std::find(array.begin(), array.end(), value) != array.end());
}

ft_bool isDirectory(const std::string &filePath)
{
	struct stat	buffer;

	if (stat(filePath.c_str(), &buffer) == -1)
		return FT_FALSE;
	if (buffer.st_mode & S_IFDIR)
		return FT_TRUE;
	return FT_FALSE;
}

ft_bool	isCgi(const std::string &filePath) {
	if (filePath.length() < 3)
		return FT_FALSE;
	if (filePath.substr(filePath.length() - 3, std::string::npos) == ".py")
		return FT_TRUE;
	return FT_FALSE;
}
