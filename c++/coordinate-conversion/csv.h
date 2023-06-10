// Copyright © 2020 R. Scott Gustafson. All rights reserved.

#if !defined(CSV_H)
#define CSV_H

#include <vector>
#include <string>

class csv {
    public:
        csv(void);
        ~csv() = default;

        struct format {
            double time;    // Time since the Unix epoch [seconds]
            double lat;     // WGS84 Latitude [degrees]
            double lon;     // WGS84 Longitude [degrees]
            double alt;     // WGS84 Altitude [kilometers]
        };

        std::vector<format> m_data;

        format split(std::string line);
};

#endif // CSV_H