#include "Person.h"
#include "Data.h"
#include <utility>

using namespace std;

Person::Person() {}

vector<double> Person::stats_precise_position(const GPS &position,
                                              const Date &start,
                                              const Date &end, Date &proche) {
    if (start > end) {
        vector<double> vide;
        return vide;
    }
    vector<pair<Sensor, double>> listVector =
        Data::get_five_nearest_sensors(position);
    cout << "top5 : " << endl;
    /*
    for (const auto& element : listVector) {
        const Sensor& sensor = element.first;
        double value = element.second;
        cout << "Sensor: " << sensor.get_id() << ", distance: " << value <<
    endl;
    }
    */
    vector<pair<Sensor, double>>::iterator itDebut = listVector.begin();
    vector<pair<Sensor, double>>::iterator itFin = listVector.end();
    double mfO3 = 0;
    double mfSO2 = 0;
    double mfNO2 = 0;
    double mfPM10 = 0;
    double sumD = 0;
    for (auto it = itDebut; it != itFin; ++it) {
        cout << "Sensor: " << it->first.get_id();
        vector<Measurement> measure = Data::get_measures_of_sensor(
            it->first.get_id(), start, end, proche);
        vector<Measurement>::iterator it2Debut = measure.begin();
        vector<Measurement>::iterator it2Fin = measure.end();
        // cout<<measure.size()<<endl;
        /*
        for (const auto &element : measure) {
            // cout << "mesure: " << element.get_value() << endl;
        }
        */
        double mO3 = 0;
        double mSO2 = 0;
        double mNO2 = 0;
        double mPM10 = 0;
        for (auto it2 = it2Debut; it2 != it2Fin; ++it2) {
            // cout<<" es"<<it2->get_value()<<endl;
            if (it2->get_attribute().get_id() == "O3") {
                mO3 += it2->get_value();
            } else if (it2->get_attribute().get_id() == "SO2") {
                mSO2 += it2->get_value();
            } else if (it2->get_attribute().get_id() == "NO2") {
                mNO2 += it2->get_value();
            } else if (it2->get_attribute().get_id() == "PM10") {
                mPM10 += it2->get_value();
            } else {
                cout << "err Stats_precise_position" << endl;
            }
        }

        mO3 = mO3 * 4.0 / (measure.size());
        // cout<<"MO3 "<<mO3<<endl;
        mSO2 = mSO2 * 4.0 / (measure.size());
        mNO2 = mNO2 * 4.0 / (measure.size());
        mPM10 = mPM10 * 4.0 / (measure.size());
        cout << ", O3: " << mO3;
        cout << ", SO2: " << mSO2;
        cout << ", PM10: " << mPM10;
        cout << ", distance: " << it->second << endl;
        if (it->second == 0) {
            return {mO3, mSO2, mNO2, mPM10};
        } else {
            mfO3 += mO3 / (it->second);
            mfSO2 += mSO2 / (it->second);
            mfNO2 += mNO2 / (it->second);
            mfPM10 += mPM10 / (it->second);
            sumD += 1 / (it->second);
        }
    }
    // cout<<"MFO3 "<<mfO3<<endl;
    mfO3 = mfO3 / sumD;
    mfSO2 = mfSO2 / sumD;
    mfNO2 = mfNO2 / sumD;
    mfPM10 = mfPM10 / sumD;

    return {mfO3, mfSO2, mfNO2, mfPM10};
}
