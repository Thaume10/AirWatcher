#include "Cleaner.h"
using namespace std;

Cleaner::Cleaner(string cleaner_id){
  this->id = cleaner_id;
}

void Cleaner::set_timestamp_start(Date date){
  timestamp_start = date;
}

void Cleaner::set_timestamp_stop(Date date){
  timestamp_stop = date;
}
