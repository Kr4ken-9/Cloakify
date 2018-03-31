#ifndef CLOAKIFY_ENTROPY_H
#define CLOAKIFY_ENTROPY_H

#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "Shared.h"
enum FILES
{
    NONE,
    INPUT,
    ENTROPY,
    BOTH
};

enum NOISE
{
    ALPHANUMERIC,
    SYMBOL,
    PREPEND,
    SUFFIX
};

std::string AddEntropy(const std::string &Input, const std::string &Entropy, const FILES Files, const NOISE Noise);

#endif //CLOAKIFY_ENTROPY_H
