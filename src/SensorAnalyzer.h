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

struct Measurement {
    string timestamp;
    string sensorID;
    string attributeID;
    double value;
};

class SensorAnalyzer {
public:
    SensorAnalyzer();
    bool analyzeSensor(const string& userID, const string& sensorID, const vector<Sensor>& sensors, const vector<Measurement>& measurements);
private:
    double calculateMeanSurroundings(double localisation, double zone, const vector<Sensor>& sensors, const vector<Measurement>& measurements);
    double calculateMean(const string& sensorID, const string& start_date, int timeRange, const vector<Measurement>& measurements);
};

#endif // SENSOR_ANALYZER_H