#include <iostream>
#include "spectral_analyzer.h"

int main() {

    SpectralAnalyzer sa;

    std::cout << sa.setBufferSize(1024) << std::endl;
    std::cout << sa.setBufferSize(1023) << std::endl;
    std::cout << sa.getBufferSize() << std::endl;

    return 0;

}
