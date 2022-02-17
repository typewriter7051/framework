#include "circular_buffer.h"
#include <iostream> // For debug.
using namespace DSPCore;

//=========================
// Constructors

CircularBuffer::CircularBuffer() {

}

CircularBuffer::CircularBuffer(unsigned int s) {

    size = s;
    array = new float[size]; // Jank af
    head = 0;

}

CircularBuffer::~CircularBuffer() {

    delete[] array;

}

//=========================
// Getters & Setters

void CircularBuffer::printData() {

    for (int i = 0; i < size; i++) {

        std::cout << at(i) << ", ";

    }

    std::cout << std::endl;

}

unsigned int CircularBuffer::getSize() {

    return size;

}

void CircularBuffer::resize(int s) {

    // Already same size, no need to do anything.
    if (s == size) return;

    // This function works by moving the head to the start and
    // copying the old array onto the new one in a right justified manner
    // (end of old array is at end of new array with extra space/space cut out
    // at the start).

    float *newArray = new float[s];

    for (int i = 0; i < s; i++) std::cout << "VAL: " << newArray[i] << std::endl;

    // Copy values from old array to end of new array.
    for (int i = 0; i < size; i++) {

        int newArrayIndex = s - size + i;
        if (newArrayIndex >= 0)
            newArray[newArrayIndex] = at(i);

        //if (newArray[newArrayIndex] < 0.1)
            //std::cout <<  << ", " << newArray[newArrayIndex] << std::endl;

    }

    // Free old array.
    delete[] array;
    array = newArray;

    // Update array size.
    size = s;
    head = 0;

}

// Automatically wraps around bounds (i.e. [-1] same as [last]).
float CircularBuffer::at(int index) {

    return array[(index + head) % size];

}

// Pushes the buffer forwards with new data.
void CircularBuffer::push(float* data, int s) {

    for (int i = 0; i < s; i++) {

        int arrayIndex = (head + i) % size;

        array[arrayIndex] = data[i];

    }

    // Update the head position;
    head += s;
    head %= size;

}
