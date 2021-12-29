g++ ../profiler.h ../profiler.cpp neuron.h neuron.cpp nn.h nn.cpp AIFrameworkTest.cpp -c AIFrameworkTest.o
g++ profiler.o neuron.o nn.o AIFrameworkTest.o -o aitest
