namespace DSPCore {

class CircularBuffer {
public:

    //-------------------------
    // Constructors

    CircularBuffer();
    CircularBuffer(unsigned int s);

    ~CircularBuffer();

    //-------------------------
    // Getters & Setters

    // For debug.
    void printData();

    unsigned int getSize();
    void resize(int s);

    // Automatically wraps around bounds (i.e. [-1] same as [last]).
    float at(int index);

    // Pushes the buffer forwards with new data.
    void push(float* data, int s);

private:

    int head, size;

    // Allocated block of memory to hold elements.
    // Note that the start of array[] might not be the head of the buffer.
    float *array;

};

}
