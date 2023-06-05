#include "Data.h"
#include "User.h"
#include "Vue.h"
#include <iostream>
#include <unordered_map>
using namespace std;

void unit_tests_precise_position() {
    Date start;
    Date end;
    Date proche;
    start.string_to_time("2023-01-01 10:00:00");
    end.string_to_time("2023-01-01  14:00:00");
    cout << endl << endl;
    cout << "Unit test valide avec sensors créés :" << endl;
    auto startTime = chrono::high_resolution_clock::now();
    vector<double> valid =
        Data::stats_precise_position(GPS(0.5, 0.5), start, end, proche);
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
        Data::stats_precise_position(GPS(44.2, 2.4), start, end, proche);
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
        Data::stats_precise_position(GPS(44.2, 2.4), start, end, proche);
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
        Data::stats_precise_position(GPS(0.5, 0.5), start, end, proche);
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
    auto startTime = chrono::high_resolution_clock::now();
    bool result = sensor1.analyze_sensor(start_date);
    auto endTime = chrono::high_resolution_clock::now();
    if (result) {
        cout << "\n---- Test validé ----\n" << endl;
    }
    auto duration = endTime - startTime;
    long elapsedTime = duration.count();
    cout << endl << "Temps écoulé : " << elapsedTime << " ms" << endl;

    // Test : Le capteur ne doit pas être fiable si une ou plusieurs mesures
    // sont nulles ou négatives (Sensor36)
    cout << "\nTest si NOK dans le cas où une mesure est negative ou inf à 0"
         << endl;
    Sensor sensor2("Sensor36");
    startTime = chrono::high_resolution_clock::now();
    result = !sensor2.analyze_sensor(start_date);
    endTime = chrono::high_resolution_clock::now();
    if (result) {
        cout << "\n---- Test validé ----\n" << endl;
    }
    duration = endTime - startTime;
    elapsedTime = duration.count();
    cout << endl << "Temps écoulé : " << elapsedTime << " ms" << endl;

    // Test : Le capteur ne doit pas être fiable si la moyenne diffère de plus
    // de deltaOfReliability par rapport à la moyenne des capteurs environnants.
    cout << "\nTest si NOK dans le cas où le delta est depassé" << endl;
    Sensor sensor3("Sensor0");

    startTime = chrono::high_resolution_clock::now();
    result = !sensor3.analyze_sensor(start_date);
    endTime = chrono::high_resolution_clock::now();
    if (result) {
        cout << "\n---- Test validé ----\n" << endl;
    }
    duration = endTime - startTime;
    elapsedTime = duration.count();
    cout << endl << "Temps écoulé : " << elapsedTime << " ms" << endl;
}

int main() {
    Data::load_CSV();

    while (!Vue::get_quitter()) {
        Vue::print_menu();

        int opt = 0;
        Vue::entree_int_safe(opt);

        switch (opt) {
        case 0:
            Vue::set_quitter(true);
            break;

        case 1:
            unit_tests_precise_position();
            break;

        case 2:
            unit_tests_analyze_sensor();
            break;

        case 3:
            Vue::afficher_donnees();
            break;

        case 4:
            Vue::afficher_stats_precise_position();
            break;

        case 5:
            Vue::afficher_analyze_sensor();
            break;

        default:
            Vue::print_error();
            break;
        }
    }

    return 0;
}
