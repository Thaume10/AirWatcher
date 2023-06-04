#include "Data.h"
#include "User.h"
#include <iostream>
using namespace std;

void unit_tests_precise_position() {
    User u;
    Date start;
    Date end;
    Date proche;
    start.string_to_time("2023-01-01 10:00:00");
    end.string_to_time("2023-01-01  14:00:00");
    cout << endl << endl;
    cout << "Unit test valide avec sensors créés :" << endl;
    auto startTime = chrono::high_resolution_clock::now();
    vector<double> valid =
        u.stats_precise_position(GPS(0.5, 0.5), start, end, proche);
    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = endTime - startTime;
    double elapsedTime = duration.count();
    cout << endl << "Temps écoulé : " << elapsedTime << " ms" << endl;
    cout << "------------------------" << endl;
    cout << "O3\tSO2\tNO2\tPM10" << endl;
    for (const auto &value : valid) {
        cout << value << "\t";
    }
    cout << endl;

    start.string_to_time("2019-01-09 10:00:00");
    end.string_to_time("2019-01-09 14:00:00");
    cout << endl << endl;
    cout << "Unit test valide avec jeux de donée :" << endl;
    startTime = chrono::high_resolution_clock::now();
    vector<double> valid2 =
        u.stats_precise_position(GPS(44.2, 2.4), start, end, proche);
    endTime = chrono::high_resolution_clock::now();
    duration = endTime - startTime;
    elapsedTime = duration.count();
    cout << endl << "Temps écoulé : " << elapsedTime << " ms" << endl;
    cout << "------------------------" << endl;
    cout << "O3\tSO2\tNO2\tPM10" << endl;
    for (const auto &value : valid2) {
        cout << value << "\t";
    }
    cout << endl;

    start.string_to_time("2019-01-09 14:00:00");
    end.string_to_time("2019-01-09 10:00:00");
    cout << endl << endl;
    cout << "Unit test invalide  :" << endl;
    startTime = chrono::high_resolution_clock::now();
    vector<double> valid3 =
        u.stats_precise_position(GPS(44.2, 2.4), start, end, proche);
    endTime = chrono::high_resolution_clock::now();
    duration = endTime - startTime;
    elapsedTime = duration.count();
    cout << endl << "Temps écoulé : " << elapsedTime << " ms" << endl;
    if (valid3.empty()) {
        cout << "L'heure de fin est plus petite que l'heure de début" << endl;
    }

    start.string_to_time("2050-01-01 10:00:00");
    end.string_to_time("2050-01-01  14:00:00");
    cout << endl << endl;
    cout << "Unit test valide dans un interval sans mesures :" << endl;
    startTime = chrono::high_resolution_clock::now();
    vector<double> valid4 =
        u.stats_precise_position(GPS(0.5, 0.5), start, end, proche);
    endTime = chrono::high_resolution_clock::now();
    duration = endTime - startTime;
    elapsedTime = duration.count();
    cout << endl << "Temps écoulé : " << elapsedTime << " ms" << endl;
    if (!proche.to_string().empty()) {
        cout << endl
             << "No data in this period, the closest data available is from : "
             << proche.to_string() << endl;
    }
    cout << "------------------------" << endl;
    cout << "O3\tSO2\tNO2\tPM10" << endl;
    for (const auto &value : valid4) {
        cout << value << "\t";
    }
    cout << endl;
}

void unit_tests_analyze_sensor() {
    Sensor sensor1("Sensor5");
    Date start_date;
    Date measure_date = start_date;
    measure_date.add_days(-10);

    // Set up dates
    start_date.string_to_time("2019-01-09 10:00:00");

    // Test : Le capteur doit être fiable si toutes les mesures sont positives
    // et que la moyenne ne diffère pas de plus de deltaOfReliability
    cout << "\nTest si OK dans des conditionns normales" << endl;
    if (sensor1.analyzeSensor(sensor1, start_date)) {
        cout << "\n---- Test validé ----\n" << endl;
    }

    // Test : Le capteur ne doit pas être fiable si une ou plusieurs mesures
    // sont nulles ou négatives (Sensor36)
    cout << "\nTest si NOK dans le cas où une mesure est negative ou inf à 0"
         << endl;
    Sensor sensor2("Sensor36");

    if (!sensor2.analyzeSensor(sensor2, start_date)) {
        cout << "\n---- Test validé ----\n" << endl;
    }

    // Test : Le capteur ne doit pas être fiable si la moyenne diffère de plus
    // de deltaOfReliability par rapport à la moyenne des capteurs environnants.
    cout << "\nTest si NOK dans le cas où le delta est depassé" << endl;
    Sensor sensor3("Sensor0");

    if (!sensor3.analyzeSensor(sensor3, start_date)) {
        cout << "\n---- Test validé ----\n" << endl;
    }
}

int main() {
    Data::load_CSV();

    cout << "----------------USERS--------------" << endl;
    vector<User> users = Data::get_users();
    for (vector<User>::iterator itUsers = users.begin(); itUsers != users.end();
         ++itUsers) {
        cout << "User : " << itUsers->get_id() << endl;
        vector<Sensor> sensors = itUsers->get_sensors();
        for (vector<Sensor>::iterator itSensor = sensors.begin();
             itSensor != sensors.end(); ++itSensor) {
            cout << "\tSensor : " << itSensor->get_id()
                 << " coordonnees : " << itSensor->get_coord().get_latitude()
                 << " : " << itSensor->get_coord().get_longitude() << endl;
        }
    }

    cout << "----------------SENSORS--------------" << endl;
    vector<Sensor> sensors = Data::get_sensors();
    /*
    for (vector<Sensor>::iterator itSensor = sensors.begin();
         itSensor != sensors.end(); ++itSensor) {
        cout << "Sensor : " << itSensor->get_id() << " coordonnees : " <<
        itSensor->get_coord().get_latitude() << " " <<
        itSensor->get_coord().get_longitude() << endl;
    }
    */

    cout << "----------------CLEANERS--------------" << endl;
    vector<Cleaner> cleaners = Data::get_cleaners();
    for (vector<Cleaner>::iterator itCleaners = cleaners.begin();
         itCleaners != cleaners.end(); ++itCleaners) {
        cout << "Cleaner : " << itCleaners->get_id() << " coord : " <<
        itCleaners->get_coord().get_latitude() << " : " <<
        itCleaners->get_coord().get_longitude() << " Debut : " <<
        itCleaners->get_timestamp_start().to_string() <<  " Fin : " <<
        itCleaners->get_timestamp_stop().to_string() << endl;
    }

    cout << "----------------MEASUREMENTS--------------" << endl;
    vector<Measurement> measurements = Data::get_measurements();
    /*
    for (vector<Measurement>::iterator itMeasurements = measurements.begin();
         itMeasurements != measurements.end(); ++itMeasurements) {
        cout << "Measurement value : " << itMeasurements->get_value() << "
        timestamp : " << itMeasurements->get_timestamp().to_string() << "
        attribute : " << itMeasurements->get_attribute().get_id() << endl;
    }
    */

    cout << "----------------PROVIDERS--------------" << endl;
    vector<Provider> providers = Data::get_providers();
    for (vector<Provider>::iterator itProvider = providers.begin();
         itProvider != providers.end(); ++itProvider) {
        cout << "Provider id : " << itProvider->get_id() << endl;
        cleaners = itProvider->get_cleaners();
        for (vector<Cleaner>::iterator itCleaner = cleaners.begin();
             itCleaner != cleaners.end(); ++itCleaner) {
            cout << "Cleaner : " << itCleaner->get_id()
                 << " coord : " << itCleaner->get_coord().get_latitude()
                 << " : " << itCleaner->get_coord().get_longitude()
                 << " Debut : " << itCleaner->get_timestamp_start().to_string()
                 << " Fin : " << itCleaner->get_timestamp_stop().to_string()
                 << endl;
        }
    }

    cout << "\n--------------TEST PRECISE POSITION--------------\n";
    unit_tests_precise_position();
    cout << "\n--------------TEST ANALYZE SENSOR--------------\n";
    unit_tests_analyze_sensor();
    return 0;
}
