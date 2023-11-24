#include <gtest/gtest.h>
#include <chrono>
#include <iostream>
#include "MeasurementProcessor.h" 

TEST(MeasurementProcessorTest, TestEmpty) {
    Instant startOfSampling = {std::chrono::system_clock::from_time_t(1483430000)};

    std::vector<Measurement> unsampledMeasurements = {};

    MeasurementProcessor processor;
    auto sampledMeasurements = processor.sample(startOfSampling, unsampledMeasurements);

    ASSERT_EQ(sampledMeasurements.size(), 0) ;

    ASSERT_EQ(sampledMeasurements[MeasurementType::TEMP].size(), 0);
    ASSERT_EQ(sampledMeasurements[MeasurementType::SPO2].size(), 0);
}


TEST(MeasurementProcessorTest, TestEdge) {
    Instant startOfSampling = {std::chrono::system_clock::from_time_t(1483430000)};


    std::vector<Measurement> edgeCaseMeasurements = {
        {Instant{startOfSampling.time}, MeasurementType::TEMP, 37.0},
        {Instant{startOfSampling.time + std::chrono::minutes(5)}, MeasurementType::SPO2, 99.5},
        {Instant{startOfSampling.time + std::chrono::minutes(5) + std::chrono::seconds(1)}, MeasurementType::TEMP, 99.5},
        {Instant{startOfSampling.time + std::chrono::minutes(10)}, MeasurementType::TEMP, 36.8},
    };

    MeasurementProcessor processor;
    auto edgeCaseSampledMeasurements = processor.sample(startOfSampling, edgeCaseMeasurements);


    ASSERT_EQ(edgeCaseSampledMeasurements.size(), 2	);

	ASSERT_EQ(edgeCaseSampledMeasurements[MeasurementType::TEMP].size(), 2);
    ASSERT_EQ(edgeCaseSampledMeasurements[MeasurementType::SPO2].size(), 1);

    ASSERT_EQ(edgeCaseSampledMeasurements[MeasurementType::TEMP][0].measurementValue, 37.0);
    ASSERT_EQ(edgeCaseSampledMeasurements[MeasurementType::TEMP][1].measurementValue, 36.8);

    ASSERT_EQ(edgeCaseSampledMeasurements[MeasurementType::SPO2][0].measurementValue, 99.5);
}

TEST(MeasurementProcessorTest, TestOutOfOrder) {

    Instant startOfSampling = {std::chrono::system_clock::from_time_t(1483430000)};

    std::vector<Measurement> edgeCaseMeasurements = {
		{Instant{startOfSampling.time + std::chrono::minutes(5) + std::chrono::seconds(1)}, MeasurementType::TEMP, 99.5},
        {Instant{startOfSampling.time}, MeasurementType::TEMP, 37.0},
        {Instant{startOfSampling.time + std::chrono::minutes(10)}, MeasurementType::TEMP, 36.8},
        {Instant{startOfSampling.time + std::chrono::minutes(5)}, MeasurementType::SPO2, 99.5},        
        
    };

    MeasurementProcessor processor;
    auto edgeCaseSampledMeasurements = processor.sample(startOfSampling, edgeCaseMeasurements);


    ASSERT_EQ(edgeCaseSampledMeasurements.size(), 2	);

	ASSERT_EQ(edgeCaseSampledMeasurements[MeasurementType::TEMP].size(), 2);
    ASSERT_EQ(edgeCaseSampledMeasurements[MeasurementType::SPO2].size(), 1);

    ASSERT_EQ(edgeCaseSampledMeasurements[MeasurementType::TEMP][0].measurementValue, 37.0);
    ASSERT_EQ(edgeCaseSampledMeasurements[MeasurementType::TEMP][1].measurementValue, 36.8);

    ASSERT_EQ(edgeCaseSampledMeasurements[MeasurementType::SPO2][0].measurementValue, 99.5);
}

TEST(MeasurementProcessorTest, TestBeforeLol) {

    Instant startOfSampling = {std::chrono::system_clock::from_time_t(1483430000)};

    std::vector<Measurement> edgeCaseMeasurements = {
		{Instant{startOfSampling.time - std::chrono::minutes(5)}, MeasurementType::TEMP, 99.5},
		{Instant{startOfSampling.time - std::chrono::minutes(5) + std::chrono::seconds(1)}, MeasurementType::TEMP, 99.6},
		{Instant{startOfSampling.time - std::chrono::seconds(1)}, MeasurementType::SPO2, 99.7},
    };

    MeasurementProcessor processor;
    auto edgeCaseSampledMeasurements = processor.sample(startOfSampling, edgeCaseMeasurements);


    ASSERT_EQ(edgeCaseSampledMeasurements.size(), 2	);

	ASSERT_EQ(edgeCaseSampledMeasurements[MeasurementType::TEMP].size(), 1);
    ASSERT_EQ(edgeCaseSampledMeasurements[MeasurementType::SPO2].size(), 1);

    ASSERT_EQ(edgeCaseSampledMeasurements[MeasurementType::TEMP][0].measurementValue, 99.6);
    ASSERT_EQ(edgeCaseSampledMeasurements[MeasurementType::SPO2][0].measurementValue, 99.7);
}

TEST(MeasurementProcessorTest, TestOnStartingTime) {

    Instant startOfSampling = {std::chrono::system_clock::from_time_t(1483430000)};

    std::vector<Measurement> edgeCaseMeasurements = {
		{Instant{startOfSampling.time}, MeasurementType::TEMP, 99.5},
    };

    MeasurementProcessor processor;
    auto edgeCaseSampledMeasurements = processor.sample(startOfSampling, edgeCaseMeasurements);


    ASSERT_EQ(edgeCaseSampledMeasurements.size(), 1);

	ASSERT_EQ(edgeCaseSampledMeasurements[MeasurementType::TEMP].size(), 1);
    ASSERT_EQ(edgeCaseSampledMeasurements[MeasurementType::SPO2].size(), 0);

    ASSERT_EQ(edgeCaseSampledMeasurements[MeasurementType::TEMP][0].measurementValue, 99.5);

}

TEST(MeasurementProcessorTest, TestBeforeStartingTime) {

    Instant startOfSampling = {std::chrono::system_clock::from_time_t(1483430000)};

    std::vector<Measurement> edgeCaseMeasurements = {
		{Instant{startOfSampling.time -  std::chrono::minutes(10)}, MeasurementType::TEMP, 99.5},
    };

    MeasurementProcessor processor;
    auto edgeCaseSampledMeasurements = processor.sample(startOfSampling, edgeCaseMeasurements);


    ASSERT_EQ(edgeCaseSampledMeasurements.size(), 0	);

	ASSERT_EQ(edgeCaseSampledMeasurements[MeasurementType::TEMP].size(), 0);
    ASSERT_EQ(edgeCaseSampledMeasurements[MeasurementType::SPO2].size(), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
