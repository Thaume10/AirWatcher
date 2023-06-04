#if !defined(SENSOR_H)
#define SENSOR_H

#include "Measurement.h"
#include "Date.h"
#include "Device.h"
#include <chrono>
#include <cmath>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

class Sensor : public Device {
public:
    Sensor();

    Sensor(const std::string &id);

    Sensor(const std::string &id,
           bool is_malfunctionning); // Au cas où un user pas trustworthy créee
                                     // un sensor

    std::map<Sensor, double> scoring_similar_sensors();

    bool get_is_malfunctionning() const { return is_malfunctionning; }

    void set_is_malfunctionning(bool malfunctionning);

    void add_measurement(Measurement &measurement) {
        measurements.push_back(measurement);
    }

    friend bool operator<(const Sensor &unSensor, const Sensor &autreSensor);

    bool analyzeSensor(const Sensor &sensor, const Date &start_date);

    std::vector<Measurement> get_measurements() const { return measurements;}

protected:
    bool is_malfunctionning;
    std::vector<Measurement> measurements;
    std::vector<double> calculate_mean(const Sensor &sensor,
                                       const Date &start_date,
                                       const Date &end_date);
    std::vector<double> calculate_mean_surroundings(const GPS &coord,
                                                    const Date &start_date,
                                                    const Date &end_date);
};

bool operator<(const Sensor &unSensor, const Sensor &autreSensor);

#endif
