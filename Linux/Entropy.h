#ifndef CLOAKIFY_ENTROPY_H
#define CLOAKIFY_ENTROPY_H

#include <ctime>
#include <stdio.h>
#include <stdlib.h>


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

#endif //CLOAKIFY_ENTROPY_H
