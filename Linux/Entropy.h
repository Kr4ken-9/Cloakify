#ifndef CLOAKIFY_ENTROPY_H
#define CLOAKIFY_ENTROPY_H

#include <fstream>

enum FILES
{
    NONE,
    INPUT,
    NOISE,
    BOTH
};

enum NOISE
{
    ALPHANUMERIC,
    SPECIAL,
    PREPEND,
    SUFFIX
};

#endif //CLOAKIFY_ENTROPY_H
