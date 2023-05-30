//
// Created by Léo Aimonetto on 09/05/2023.
//

#ifndef SENSOR_ANALYZER_H
#define SENSOR_ANALYZER_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;


struct Sensor {
    string sensorID;
    double latitude;
    double longitude;
};

class SensorAnalyzer {
public:
    SensorAnalyzer();
    bool analyzeSensor(const Sensor& sensor, const Date& start_date);
private:
    double calculateMeanSurroundings(GPS coord, Date start_date, Date end_date);
    calculateMean(Sensor sensor, const Date start_date, const Date end_date);
};

#endif // SENSOR_ANALYZER_H