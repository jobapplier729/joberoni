#ifndef MEASUREMENTPROCESSOR_H
#define MEASUREMENTPROCESSOR_H

#include <vector>
#include <map>
#include <algorithm>
#include <chrono>

enum class MeasurementType {
    TEMP,
    SPO2,

};

struct Instant {
    std::chrono::system_clock::time_point time;
};

class Measurement {
public:
    Instant measurementTime;
    double measurementValue;
    MeasurementType type;

    Measurement(Instant time, MeasurementType type, double value)
        : measurementTime(time), type(type), measurementValue(value) {}
};

class MeasurementProcessor {
public:
    std::map<MeasurementType, std::vector<Measurement>> sample(Instant startOfSampling, std::vector<Measurement>& unsampledMeasurements);
};

#endif 
