#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    std::ofstream file;
    file.open("2.in");
    srand(time(NULL));
    int v = rand() % 101;
    for (unsigned int i = 0; i < 11; ++i) {
        for (unsigned int j = 0; j < 11; ++j) {
            file << v;
            if (j < 10) 
                file << " ";
            v = rand() % 101;
        }
        file << std::endl;
    }

    return 0;
}