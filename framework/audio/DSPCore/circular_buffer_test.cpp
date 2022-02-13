#include "circular_buffer.h"
#include <iostream>
using namespace std;

int main() {

    DSPCore::CircularBuffer cb(4);

    float data[] = {1, 2, 3, 4};
    cb.push(data, 4);
    cb.printData();

    cb.resize(8);
    cb.printData();

    float data2[] = {5, 6, 7, 8};
    cb.push(data2, 4);
    cb.printData();

    cb.resize(4);
    cb.printData();

    return 0;

}
