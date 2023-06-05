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

void Vue::print_error() { cerr << "Erreur : Entrée invalide." << endl; }

void Vue::print_menu() {
    cout << endl
         << endl
         << "Choisissez l'option souhaitée en entrant un nombre :" << endl
         << "0) Quitter l'application ;" << endl
         << "1) Unit test precise position ;" << endl
         << "2) Unit test analyze sensor ;" << endl
         << "3) Afficher les données." << endl;
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
