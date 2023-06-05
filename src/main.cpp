#include "Data.h"
#include "User.h"
#include <iostream>
#include <unordered_map>
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
    for (const auto &user : Data::get_users()) {
        cout << "User : " << user.second.get_id() << endl;
        unordered_map<string, Sensor *> sensors = user.second.get_sensors();
        for (const auto &sensor : sensors) {
            cout << "\tSensor : " << sensor.second->get_id()
                 << " coordonnees : "
                 << sensor.second->get_coord().get_latitude() << " : "
                 << sensor.second->get_coord().get_longitude() << endl;
        }
    }

    cout << "----------------SENSORS--------------" << endl;

    /*
    for (const auto &sensor : Data::get_sensors()) {
        cout << "Sensor : " << sensor.second.get_id() << " coordonnees : " <<
        sensor.second.get_coord().get_latitude() << " " <<
        sensor.second.get_coord().get_longitude() << endl;
    }
    */

    cout << "----------------CLEANERS--------------" << endl;
    for (const auto &cleaner : Data::get_cleaners()) {
        cout << "Cleaner : " << cleaner.second.get_id()
             << " coord : " << cleaner.second.get_coord().get_latitude()
             << " : " << cleaner.second.get_coord().get_longitude()
             << " Debut : " << cleaner.second.get_timestamp_start().to_string()
             << " Fin : " << cleaner.second.get_timestamp_stop().to_string()
             << endl;
    }

    cout << "----------------MEASUREMENTS--------------" << endl;
    /*
    for (const auto &measure : Data::get_measurements()) {
        cout << "Measurement value : " << measure.get_value() << " timestamp : "
    << measure.get_timestamp().to_string() << " attribute : " <<
    measure.get_attribute_id() << endl;
    }
    */

    cout << "----------------PROVIDERS--------------" << endl;
    for (const auto &itProvider : Data::get_providers()) {
        cout << "Provider id : " << itProvider.second.get_id() << endl;
        auto cleaners = itProvider.second.get_cleaners();
        for (const auto &itCleaner : cleaners) {
            cout << "Cleaner : " << itCleaner.second->get_id()
                 << " coord : " << itCleaner.second->get_coord().get_latitude()
                 << " : " << itCleaner.second->get_coord().get_longitude()
                 << " Debut : "
                 << itCleaner.second->get_timestamp_start().to_string()
                 << " Fin : "
                 << itCleaner.second->get_timestamp_stop().to_string() << endl;
        }
    }

    cout << "\n--------------TEST PRECISE POSITION--------------\n";
    unit_tests_precise_position();
    cout << "\n--------------TEST ANALYZE SENSOR--------------\n";
    unit_tests_analyze_sensor();
    return 0;
}
