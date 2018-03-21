#ifndef CLOAKIFY_LIBRARY_H
#define CLOAKIFY_LIBRARY_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
#include "base64.h"

enum FILES
{
    NONE,
    INPUT,
    CIPHER,
    BOTH
};

std::string Cloak(const std::string Input, const std::string Cipher, const FILES Files);

#endif