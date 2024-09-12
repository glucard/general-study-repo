#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>

#include <iostream>
#include <fstream>
using namespace std;

void int_vector_file_generator(int length, int range_start, int range_end){
    ofstream myfile;
    myfile.open ("numbers.txt");

    int interval = range_end - range_start;

    if (interval < 1) throw std::invalid_argument("The operation (range_end - range_start) result value must be greater than zero.");

    for(int i = 0; i < length; i++) {
        int rand_n = rand() % interval + range_start;
        myfile << rand_n << std::endl;
    }
    myfile.close();
}

int main(int argc, char **argv) {

    std::cout << argc << std::endl;
    if (argc != 4) throw std::invalid_argument("The script must receive exact 3 arguments (int length, int range_start, int range_end)");

    int length = strtol(argv[1], NULL, 10);
    int range_start = strtol(argv[2], NULL, 10);
    int range_end = strtol(argv[3], NULL, 10);

    int_vector_file_generator(length, range_start, range_end);
    return 0;
}