#ifndef CLOAKIFY_LIBRARY_H
#define CLOAKIFY_LIBRARY_H

#include <iostream>
#include <iterator>
#include <algorithm>
#include "base64.h"
#include "Shared.h"

enum FILES
{
    NONE,
    INPUT,
    CIPHER,
    BOTH
};

std::string Cloak(const std::string Input, const std::string Cipher, const FILES Files);
std::string Uncloak(const std::string &Input, const std::string &Cipher, const FILES Files);
#endif