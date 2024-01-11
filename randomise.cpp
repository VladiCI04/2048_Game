#include "randomise.h"

#include <random>

unsigned short randomIndexGenerator(unsigned short dimension) {
    // Create a random number engine
    std::random_device random;
    std::mt19937 generator(random());

    // Define a distribution (e.g., uniform distribution between 0 and 9)
    std::uniform_int_distribution<unsigned short> distribution(0, 9);

    // Generate a random number
    unsigned short randomNumber = distribution(generator);
    while (randomNumber >= dimension) {
        randomNumber = distribution(generator);
    }

    return randomNumber;
}

unsigned short randomNumberGenerator(unsigned int moveCount) {
    // Create a random number engine
    std::random_device random;
    std::mt19937 generator(random());

    // Define a distribution (e.g., uniform distribution between 1 and 3)
    std::uniform_int_distribution<unsigned short> distribution(1, 3);

    // Generate a random number
    unsigned short randomNumber = distribution(generator);
    unsigned short num = 0;
    if (randomNumber == 1) {
        num = 2;
    }
    else if (randomNumber == 2) {
        num = 4;
    }
    else if (randomNumber == 3) {
        num = 8;
    }

    return num;
}