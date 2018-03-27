#ifndef CLOAKIFY_SHARED_H
#define CLOAKIFY_SHARED_H

#include <fstream>
#include <vector>
#include <sstream>

std::string FileToString(const std::string FileName);
std::vector<std::string> split(const std::string &s, char delim);

#endif //CLOAKIFY_SHARED_H
