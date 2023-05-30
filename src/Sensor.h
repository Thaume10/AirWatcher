#if ! defined ( SENSOR_H )
#define SENSOR_H

#include <map>
#include <vector>
#include <utility>
#include "Device.h"
#include "Date.h"
#include <cmath>
#include <iostream>
#include <chrono>

class Sensor : public Device{
public:
    Sensor();

    Sensor(std::string id);

    Sensor(std::string id, bool is_malfunctionning); //Au cas où un user pas trustworthy créee un sensor

    std::map<Sensor, double> scoring_similar_sensors();



    inline bool get_is_malfunctionning() const {
        return is_malfunctionning;
    }

   

    void set_is_malfunctionning(bool malfunctionning);

    //void add_measurement(Measurement measurement);

    friend bool operator < (const Sensor & unSensor, const Sensor & autreSensor);

    bool analyzeSensor(const Sensor& sensor, const Date& start_date);
    

protected:
    bool is_malfunctionning;
    std::vector<double> calculateMean(const Sensor& sensor, const Date start_date, const Date end_date);
    std::vector<double> calculateMeanSurroundings(GPS coord, Date start_date, Date end_date);
    
};

bool operator < (const Sensor & unSensor, const Sensor & autreSensor);

#endif
