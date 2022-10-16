#include "Master.hpp"
#include "Request.hpp"
#include "conf/Config.hpp"

int	main(int argc, char **argv, char **env) {
	if (argc != 2)
		return 1;
	try {
		std::vector<Block>				serverblocks;	
		std::vector<Block>::iterator	it;
	
		Config conf = Config(argv[1]);
		serverblocks = conf.getServerBlocks();
		for (it = serverblocks.begin(); it != serverblocks.end(); it++)
			it->printBlock();
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	try {
		Master master(env);
		// print env
		// char **envs = master.getEnv();
		// while (envs && *envs) {
		// 	std::cout << *envs << std::endl;
		// 	envs++;
		// }
		master.run();
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
