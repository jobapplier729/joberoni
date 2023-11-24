# joberoni
Measurement Processor
This GitHub repository contains a C++ implementation of a Measurement Processor, along with unit tests and an example application that demonstrates its usage. The Measurement Processor is designed to sample and process measurements based on a specified sampling interval.

Contents
MeasurementProcessor.h: Header file containing the class declarations for MeasurementProcessor, Measurement, and Instant.
MeasurementProcessor.cpp: Implementation file for the MeasurementProcessor class.
test_main.cpp: Unit tests for the MeasurementProcessor class using the Google Test framework.
main.cpp: Example application that demonstrates how to use the MeasurementProcessor class. It includes input measurements and prints both the input and the sampled measurements.

How to Run Example Application
To run the example application:

```g++ -o app main.cpp MeasurementProcessor.cpp && ./app```
This will compile the example application and execute it, displaying the input measurements and the corresponding sampled measurements.

How to Build and Run Tests
To compile and run the tests, use the following commands:

```g++ -o tests test_main.cpp MeasurementProcessor.cpp -lgtest -lgtest_main -pthread && ./tests```
This will compile the test file, link it with the necessary Google Test libraries, and execute the tests. Ensure that the necessary dependencies are installed on your system.
