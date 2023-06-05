#include "Vue.h"

#include "Data.h"
#include <iostream>
#include <limits>
using namespace std;

bool Vue::quitter = false;

void Vue::entree_int_safe(int &entree) {
    while (!(cin >> entree) && !cin.eof()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        print_error();
    }
}

void Vue::entree_double_safe(double &entree) {
    while (!(cin >> entree) && !cin.eof()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        print_error();
    }
}

void Vue::print_error() { cerr << "Erreur : Entrée invalide." << endl; }

void Vue::print_menu() {
    cout << endl
         << endl
         << "Choisissez l'option souhaitée en entrant un nombre :" << endl
         << "0) Quitter l'application ;" << endl
         << "1) Unit test precise position ;" << endl
         << "2) Unit test analyze sensor ;" << endl
         << "3) Afficher les données ;" << endl
         << "4) Afficher stats precise position ;" << endl
         << "5) Afficher analyze sensor." << endl;
}

void Vue::afficher_donnees() {
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
}

void Vue::afficher_analyze_sensor() {
    cout << "\nEntrer l'id du sensor\n";
    string sensor_id;
    cin >> sensor_id;

    auto it = Data::get_sensors().find(sensor_id);

    if (it != Data::get_sensors().end()) {
        Date date;
        date.string_to_time("2019-01-09 10:00:00");
        if (it->second.analyze_sensor(date)) {
            cout << "\nLe sensor est valide\n";
        } else {
            cout << "\nSensor invalide\n";
        }
    } else {
        cerr << "\nErreur : sensor introuvable\n";
    }
}

void Vue::afficher_stats_precise_position() {
    cout << "\nFormat date : 2019-01-31 14:00:00\n";
    cout << "\nEntrer date début\n";
    string deb;
    cin >> ws;
    getline(cin, deb, '\n');

    cout << "\nEntrer date fin\n";
    string fin;
    cin >> ws;
    getline(cin, fin, '\n');

    double lat = 0;
    double longitude = 0;

    Date start;
    start.string_to_time(deb);
    Date end;
    end.string_to_time(fin);
    Date proche;

    cout << "\nEntrer latitude\n";
    entree_double_safe(lat);
    cout << "\nEntrer longitude\n";
    entree_double_safe(longitude);

    vector<double> stats =
        Data::stats_precise_position(GPS(lat, longitude), start, end, proche);

    cout << "O3 : " << stats[0] << endl;
    cout << "SO2 :" << stats[1] << endl;
    cout << "NO2 : " << stats[2] << endl;
    cout << "PM10 : " << stats[3] << endl;
}
