#include "Provider.h"

using namespace std;

Provider::Provider(){

}

Provider::Provider(string id) : id(id) {
}

void Provider::add_cleaner(Cleaner cleaner){
  cleaners.push_back(cleaner); 
}

bool operator < (const Provider & unProvider, const Provider & autreProvider){
  return (unProvider.get_id() < autreProvider.get_id());
}
