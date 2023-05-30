#include "Sensor.h"
#include "Date.h"
#include "Measurement.h"
#include "Device.h"
#include <map>
#include <vector>
#include <cmath>
#include <iostream>
#include <chrono>

using namespace std;

Sensor::Sensor(){

}

Sensor::Sensor(string id) {
    this->id = id;
}

Sensor::Sensor(string id, bool is_malfunctionning) : is_malfunctionning(is_malfunctionning) {
    this->id = id;
}

bool operator < (const Sensor & unSensor, const Sensor & autreSensor){
  return unSensor.get_id() < autreSensor.get_id();
}

// bool analyzeSensor(const Sensor& sensor, const Date& start_date) {
//     bool reliable = true;
//     int timeRange = 30; // days
//     double deltaOfReliability = 10;
//     Date today = chrono::system_clock::now();
//     Date end_date = start_date+timeRange;
//
//     vector<Measure> measures_sensor = get_measures_of_sensor(sensor.get_id(), start_date, end_date);
//
//     if ((start_date+timeRange) > today)) {
//         throw invalid_argument("La période de test doit commencer au moins 30 jours avant aujourd'hui");
//     } else {
//         for (auto& m : measures_sensor) {
//             if (m.value == null || m.value <= 0) {
//                 reliable = false;
//                 break;
//             }
//         }
//
//         vector<double> mean_surroundings = calculateMeanSurroundings(sensor->GPS, start_date, end_date);
//         vector<double> mean_sensor = calculateMean(sensor, start_date, end_date);
//
//         for(int c=0; c<4; c++) {
//             if (abs(mean_surroundings[0] - mean_sensor[0]) > deltaOfReliability) {
//                 reliable = false;
//             }
//         }
//     }
//
//     return reliable;
// }

// vector<double> calculateMeanSurroundings(GPS coord, Date start_date, Date end_date) {
//     vector<pair<Sensor,double>> five_nearest_with_double = get_five_nearest_sensors(coo);
//     vector<Sensor> = five_nearest
//
//     for (auto& p : five_nearest_with_double) {
//         five_nearest.push_back(p.first);
//     }
//
//     vector<double> mean;
//
//     for(auto& s : five_nearest) {
//         vector<double> result = calculateMean(s, start_date, end_date);
//         for (int i = 0; i < result.size(); i++) {
//             mean[i] += result[i];
//         }
//     }
//
//     for (int i = 0; i < mean.size(); i++) {
//         mean[i] /= 5;
//     }
//
//     return mean;
// }
//
// vector<double> calculateMean(Sensor sensor, const Date start_date, const Date end_date) {
//     vector<Measure> measures = get_measures_of_sensor(sensor.get_id(), start_date, end_date);
//     vector<double> mean;
//
//     int count_O3 = 0
//     int count_NO2 = 0
//     int count_SO2 = 0
//     int count_PM10 = 0
//

//     for(auto& m : measures){
//         switch (m->attribute.get_id()) {
//             case "O3":
//                 mean[0] += m.value;
//                 count_O3++;
//                 break;
//             case "NO2":
//                 mean[1] += m.value;
//                 count_NO2++;
//                 break;
//             case "SO2":
//                 mean[2] += m.value;
//                 count_SO2++;
//                 break;
//             case "PM10":
//                 mean[3] += m.value;
//                 count_PM10++;
//                 break;
//             default:
//                 break;
//         }
//     }
//

//     mean[0] /= count_O3;
//     mean[1] /= count_NO2;
//     mean[2] /= count_SO2;
//     mean[3] /= count_PM10;
//
//     return mean;
// }
