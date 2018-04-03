#ifndef CLOAKIFY_ENTROPY_H
#define CLOAKIFY_ENTROPY_H

#include <ctime>
#include <stdio.h> // NOLINT
#include <stdlib.h> // NOLINT
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
    SUFFIX,
    FAF
};

std::string AddEntropy(const std::string &Input, const std::string &Entropy, FILES Files, NOISE Noise);
std::string RemoveEntropy(const std::string &Input, FILES Files, NOISE Noise);

#endif //CLOAKIFY_ENTROPY_H
