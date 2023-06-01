#include "Sensor.h"
#include "Date.h"
#include "Data.h"
#include "GPS.h"
#include "Measurement.h"
#include <sstream>

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

vector<double> Sensor::calculateMean(const Sensor& sensor, const Date start_date, const Date end_date) {
    Date proche;
    vector<Measurement> measures = Data::get_measures_of_sensor(sensor.get_id(), start_date, end_date,proche);
    vector<double> mean(4, 0.0);

    int count_O3 = 0;
    int count_NO2 = 0;
    int count_SO2 = 0;
    int count_PM10 = 0;

    for(auto& m : measures){
        if(m.get_attribute().get_id() == "O3") {
            mean[0] += m.get_value();
            count_O3++;
        }else if(m.get_attribute().get_id() == "NO2") {
            mean[1] += m.get_value();
            count_NO2++;
        }else if(m.get_attribute().get_id() == "SO2") {
            mean[2] += m.get_value();
            count_SO2++;
        }else if(m.get_attribute().get_id() == "PM10") {
            mean[3] += m.get_value();
            count_PM10++;
        }
    }

    mean[0] /= count_O3;
    mean[1] /= count_NO2;
    mean[2] /= count_SO2;
    mean[3] /= count_PM10;

    return mean;
}

vector<double> Sensor::calculateMeanSurroundings(GPS coord, Date start_date, Date end_date) {
    vector<pair<Sensor,double>> five_nearest_with_double = Data::get_five_nearest_sensors(coord);
    vector<Sensor> five_nearest;

    for (auto& p : five_nearest_with_double) {
        five_nearest.push_back(p.first);
    }

    vector<double> mean(4, 0.0);

    for(auto& s : five_nearest) {
        vector<double> result = calculateMean(s, start_date, end_date);
        for (size_t i = 0; i < result.size(); i++) {
            mean[i] += result[i];
        }
    }

    for (size_t i = 0; i < mean.size(); i++) {
        mean[i] /= 5;
    }

    return mean;
}

bool Sensor::analyzeSensor(const Sensor& sensor, const Date& start_date) {
    bool reliable = true;
    int timeRange = 30;  //days
    double deltaOfReliability = 10;
    Date proche;

    std::time_t now = std::time(nullptr);
    std::tm *timeinfo = std::localtime(&now);

    std::stringstream ss;
    ss << std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S");

    Date today;
    today.String_to_time(ss.str());

    Date end_date = start_date;
    end_date.add_days(timeRange);

    vector<Measurement> measures_sensor = Data::get_measures_of_sensor(sensor.get_id(), start_date, end_date, proche);

    if ((end_date) > today) {
        /*string toPrint = today.To_string();
        cout << "date test" << endl;
        cout << toPrint << endl;*/
        throw invalid_argument("\nLa période de test doit commencer au moins 30 jours avant aujourd'hui\n");
    } else {
        for (auto& m : measures_sensor) {
            if (m.get_value() <= 0) {
                reliable = false;
                break;
            }
        }

        vector<double> mean_surroundings = calculateMeanSurroundings(sensor.get_coord(), start_date, end_date);
        vector<double> mean_sensor = calculateMean(sensor, start_date, end_date);


        for(int c=0; c<4; c++) {
            if (abs(mean_surroundings[0] - mean_sensor[0]) > deltaOfReliability) {
                reliable = false;
            }
        }
    }

    return reliable;
}
