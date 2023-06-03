#include "Provider.h"

using namespace std;

Provider::Provider() {}

Provider::Provider(const string &id) : id(id) {}

void Provider::add_cleaner(const Cleaner &cleaner) {
    cleaners.push_back(cleaner);
}

bool operator<(const Provider &unProvider, const Provider &autreProvider) {
    return (unProvider.id < autreProvider.id);
}
