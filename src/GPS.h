#if !defined(GPS_H)
#define GPS_H

class GPS {
protected:
    double latitude;
    double longitude;

public :
    inline int get_latitude() const {
        return latitude;
    }
    inline int get_longitude() const {
        return longitude;
    }
};
#endif
