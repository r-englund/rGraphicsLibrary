#ifndef __DIRECTORY_H_
#define __DIRECTORY_H_

#include <string>
#include <vector>

class Directory{
public:
	static std::vector<std::string> getAllFilesInFolder(std::string dir);
	static std::vector<std::string> getAllFilesInFolder(std::string dir,std::string pattern);

	static void createFolder(std::string dir);

	static bool exists(std::string path);

};

#endif