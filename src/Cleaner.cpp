#include "Cleaner.h"
using namespace std;

Cleaner::Cleaner(const string &cleaner_id) { this->id = cleaner_id; }

void Cleaner::set_timestamp_start(Date date) { timestamp_start = date; }

void Cleaner::set_timestamp_stop(Date date) { timestamp_stop = date; }

Date Cleaner::get_timestamp_start() const { return timestamp_start; }

Date Cleaner::get_timestamp_stop() const { return timestamp_stop; }
