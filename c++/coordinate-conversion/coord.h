// Copyright © 2020 R. Scott Gustafson. All rights reserved.

#if !defined(COORD_H)
#define COORD_H


class coord {
    public:
        coord(double m1 = 0.0, double m2 = 0.0, double m3 = 0.0) : m_1(m1), m_2(m2), m_3(m3) {;}
        virtual ~coord(void) = default;

        double m1(void) {return m_1;}
        double m2(void) {return m_2;}
        double m3(void) {return m_3;}

    protected:
        double m_1;
        double m_2;
        double m_3;
};

// Earth Centered Earth Fixed
class coordECEF : public coord {
    public:
        coordECEF(double x, double y, double z) : coord(x, y, z) {;}
        virtual ~coordECEF(void) = default;

        double x(void) {return m_1;}    // meters
        double y(void) {return m_2;}    // meters
        double z(void) {return m_3;}    // meters
        double distanceTo(coordECEF point);
};

// native format is WGS84
class coordLLA : public coord {
    public:
        coordLLA(double lat, double lon, double alt) : coord(lat, lon, alt) {;}
        virtual ~coordLLA(void) = default;

        double latitude(void) {return m_1;}     // degrees
        double longitude(void) {return m_2;}    // degrees
        double altitude(void) {return m_3;}     // kilometers
        
        coordECEF ecef(void); //convertToECEF
};

#endif