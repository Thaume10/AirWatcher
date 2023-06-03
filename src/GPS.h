#if !defined(GPS_H)
#define GPS_H

class GPS {
protected:
    double latitude;
    double longitude;

public:
    GPS();

    GPS(double latitude, double longitude);

    inline double get_latitude() const { return latitude; }
    inline double get_longitude() const { return longitude; }
};
#endif
