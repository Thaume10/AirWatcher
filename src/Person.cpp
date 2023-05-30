#include "Person.h"
#include "Data.h"
#include <utility>

using namespace std;

Person::Person() {
}

vector<double> Stats_precise_position(GPS position , Date start, Date end)
{
    Data data;
    vector<pair<Sensor, double>> listVector =data.get_five_nearest_sensors(position);
    vector<pair<Sensor, double>>::iterator itDebut = listVector.begin();
    vector<pair<Sensor, double>>::iterator itFin = listVector.end();
    double mfO3 = 0, mfSO2 = 0, mfNO2 = 0, mfPM10 = 0, sumD = 0;
    for (auto it = itDebut; it != itFin; ++it) {
        vector<Measurement> measure =data.get_measures_of_sensor(it->first.get_id(),  start, end);
        vector<Measurement>::iterator it2Debut = measure.begin();
        vector<Measurement>::iterator it2Fin = measure.end();
        double mO3=0;
        double mSO2=0;
        double mNO2=0;
        double mPM10=0;
        for (auto it2 = it2Debut; it2 != it2Fin; ++it2) {
            if (it2->get_attribute().get_id()=="O3") {
                mO3 += it2->get_value();
            }else if(it2->get_attribute().get_id()=="SO2"){
                mSO2 += it2->get_value();
            }else if(it2->get_attribute().get_id()=="NO2"){
                mNO2 += it2->get_value();
            }else if(it2->get_attribute().get_id()=="PM10"){
                mPM10 += it2->get_value();
            }else{
                cout<<"err Stats_precise_position"<<endl;
            }
            
            
        }
        mO3=mO3/(measure.size()*4.0);
        mSO2=mSO2/(measure.size()*4.0);
        mNO2=mNO2/(measure.size()*4.0);
        mPM10=mPM10/(measure.size()*4.0);
        mfO3+=mO3*it->second;
        mfSO2+=mSO2*it->second;
        mfNO2+=mNO2*it->second;
        mfPM10+=mPM10*it->second;
        sumD+=it->second;
    }
    mfO3=mfO3/sumD;
    mfSO2=mfSO2/sumD;
    mfNO2=mfNO2/sumD;
    mfPM10=mfPM10/sumD;

   return {mfO3, mfSO2, mfNO2, mfPM10};;
}
