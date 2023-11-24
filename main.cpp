#include <iostream>
#include <iomanip>
#include "MeasurementProcessor.h"


int main() {
    Instant startOfSampling =  {std::chrono::system_clock::from_time_t(1483437000)};
    
    std::cout << "-------------------INPUT----------------------" << std::endl;
                      
    std::vector<Measurement> unsampledMeasurements = {
        {Instant{std::chrono::system_clock::from_time_t(1483437885)}, MeasurementType::TEMP, 35.79},
        {Instant{std::chrono::system_clock::from_time_t(1483437678)}, MeasurementType::SPO2, 98.78},
        {Instant{std::chrono::system_clock::from_time_t(1483438147)}, MeasurementType::TEMP, 35.01},
        {Instant{std::chrono::system_clock::from_time_t(1483437814)}, MeasurementType::SPO2, 96.49},
        {Instant{std::chrono::system_clock::from_time_t(1483437721)}, MeasurementType::TEMP, 35.82},
        {Instant{std::chrono::system_clock::from_time_t(1483437900)}, MeasurementType::SPO2, 97.17},
        {Instant{std::chrono::system_clock::from_time_t(1483437901)}, MeasurementType::SPO2, 95.08},
    };
    
	for (const auto& measurement : unsampledMeasurements) {
       
            std::time_t time = std::chrono::system_clock::to_time_t(measurement.measurementTime.time);
            std::tm tm_time = *std::localtime(&time);

            std::cout << "{ " << std::put_time(&tm_time, "%Y-%m-%d %H:%M:%S")
                      << ", " << static_cast<int>(measurement.type)
                      << ", " << measurement.measurementValue << " }" << std::endl;
        
    }
    std::cout << "-------------------OUTPUT----------------------" << std::endl;

    MeasurementProcessor processor;
    auto sampledMeasurements = processor.sample(startOfSampling, unsampledMeasurements);

    for (const auto& entry : sampledMeasurements) {
        for (const auto& measurement : entry.second) {
            std::time_t time = std::chrono::system_clock::to_time_t(measurement.measurementTime.time);
            std::tm tm_time = *std::localtime(&time);

            std::cout << "{ " << std::put_time(&tm_time, "%Y-%m-%d %H:%M:%S")
                      << ", " << static_cast<int>(measurement.type)
                      << ", " << measurement.measurementValue << " }" << std::endl;
        }
    }

    return 0;
}
