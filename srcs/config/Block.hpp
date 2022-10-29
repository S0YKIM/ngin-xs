#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__

#include "../types.hpp"
#include <cstdlib> 
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include "../macro.hpp"
#include "../utils.hpp"

#define directivesMap std::map<std::string, void (Block::*)(std::vector<std::string>)>

class Block {
private:
	std::vector<Block>	locationBlocks_;
	directivesMap		directivesMap_;
	setString			supportedExtensions_;
	std::string			host_;
	int					port_;
	setString			serverNames_;
	std::string			webRoot_;
	setString			allowedMethods_;
	std::size_t			clientMaxBodySize_;
	mapIntString		errorPages_;
	std::string			uri_;
	std::string			index_;
	std::string			autoIndex_;
	std::string			cgi_;

	ft_bool			checkParentUri(std::string uri);
	ft_bool			checkValidation(vectorString &tokens, int &index, std::string &directive);
	ft_bool			validateSemiColon(ft_bool &hasSemiColonPrev) const;
	vectorString	parseHostPort(const std::string &arg);
	ft_bool			isExtension(const std::string &uri, int &i) const;
	ft_bool			isCgiExtension(const std::string &uri, int &i) const;
	void			addSupportedExtension(const std::string &token);
	void			deleteBlocks();

public:
	static Block	defaultBlock_;

	Block();
	Block(const Block &origin);
	~Block();
	Block &operator=(const Block &origin);

	static void					setDefaultBlock(const char *file);
	void						setDefaultServerDirectivesMap();
	void						setServerDirectivesMap();
	void						setLocationDirectivesMap();
	void						setChildLocationBlock(const Block &parent);
	directivesMap				getDirectivesMap();
	
	ft_bool						hasSemiColon(vectorString &tokens, int &index, vectorString *args, std::string &directive);
	void						parseServerBlock(vectorString &tokens, int &index);
	void						parseLocationBlock(vectorString &tokens, int &i);
	
	// ServerBlock 만 해당
	void						setHostPort(vectorString args);
	void						setHost(std::string host);
	void						setPort(int port);
	void						setServerNames(vectorString args);
	// ServerBlock, LocationBlock 공통
	void						setWebRoot(vectorString args);
	void						setAllowedMethods(vectorString args);
	void						setClientMaxBodySize(int size);
	void						setClientMaxBodySize(vectorString args);
	void						setErrorPages(vectorString args);
	// LocationBlock 만 해당
	void						setUri(std::string uri);
	void						setIndex(vectorString args);
	void						setAutoIndex(vectorString args);
	void						setCgi(vectorString args);

	const setString				&getSupportedExtensions() const;
	const std::vector<Block>	&getLocationBlocks() const;
	std::string					getHost() const;
	const int					&getPort() const;
	const setString				&getServerNames() const;
	const std::string			&getWebRoot() const;
	const setString				&getAllowedMethods() const;
	const std::size_t			&getClientMaxBodySize() const;
	const mapIntString			&getErrorPages() const;
	std::string					getErrorPage(int num) const;

	const std::string			&getUri() const;
	const std::string			&getIndex() const; 
	ft_bool						getAutoIndex() const;
	const std::string			&getCgi() const;

	void						applyWildCard(std::string &uri, int &dot) const;
	void						removeFileName(std::string &uri, int &dot) const;
	const Block					&getLocationBlockRecursive(std::string uri) const;
	Block						getLocationBlock(std::string uri) const;
	void						gatherSupportedExtensions();
	void						printBlock() const;

	class InvalidConfigFileException : public std::exception {
	private:
		std::string	message_;

	public:
		InvalidConfigFileException(const std::string msg);
		~InvalidConfigFileException() throw();
		virtual const char	*what() const throw();
	};

	class InvalidLocationBlockException : public std::exception {
		virtual const char	*what() const throw();
	};

};

#endif
