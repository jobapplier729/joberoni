#include "MeasurementProcessor.h"
#include <iostream>

std::map<MeasurementType, std::vector<Measurement>> MeasurementProcessor::sample(Instant startOfSampling, std::vector<Measurement>& unsampledMeasurements) {
	if (unsampledMeasurements.empty()){
		return {};
	}
    std::map<MeasurementType, std::vector<Measurement>> sampledMeasurements;
    std::map<MeasurementType, Instant> lastSampledTime;
		
	auto actualStart = Instant{(startOfSampling.time - std::chrono::seconds(300))};
	

    
    std::sort(unsampledMeasurements.begin(), unsampledMeasurements.end(), [](const Measurement& a, const Measurement& b) {
    return a.measurementTime.time > b.measurementTime.time; //reversed
	});
	
	auto lastTime = Instant{(unsampledMeasurements.front().measurementTime.time + std::chrono::seconds(301))};

	for (const auto& measurement : unsampledMeasurements) {
        lastSampledTime[measurement.type] = lastTime;
    }
    
    auto getAdjustedSamplingTime = [&](Instant measurementTime) {
        auto timeSinceStart = measurementTime.time.time_since_epoch();
        auto secondsSinceStart = std::chrono::duration_cast<std::chrono::seconds>(timeSinceStart).count();

        auto initialSamplingSeconds = std::chrono::duration_cast<std::chrono::seconds>(actualStart.time.time_since_epoch()).count();
        auto adjustedInterval = (((secondsSinceStart - initialSamplingSeconds) + 299) / (5 * 60)) * (5 * 60) + initialSamplingSeconds;
        
        return Instant{std::chrono::system_clock::time_point(std::chrono::seconds(adjustedInterval))};
    };

    for (const auto& measurement : unsampledMeasurements) {

        if (measurement.measurementTime.time <= actualStart.time) {
            continue;
        }

        Instant samplingTime = getAdjustedSamplingTime(measurement.measurementTime);

        if (samplingTime.time < lastSampledTime[measurement.type].time) {	
            sampledMeasurements[measurement.type].emplace_back(samplingTime, measurement.type, measurement.measurementValue);
            lastSampledTime[measurement.type] = samplingTime;
        }
    }

    for (auto& entry : sampledMeasurements) {
        std::sort(entry.second.begin(), entry.second.end(), [](const Measurement& a, const Measurement& b) {
            return a.measurementTime.time < b.measurementTime.time;
        });
    }

    return sampledMeasurements;
}
