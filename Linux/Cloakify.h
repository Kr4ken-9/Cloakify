#ifndef CLOAKIFY_LIBRARY_H
#define CLOAKIFY_LIBRARY_H

#include <iostream>
#include <sstream>
#include <fstream>
#include "base64.h"

std::string Cloak(std::string Input, bool File = false);

#endif