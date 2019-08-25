#include <math.h>

/*
 The Mercator map projection is a special limiting case of the Lambert Conic Conformal map projection with
the equator as the single standard parallel. All other parallels of latitude are straight lines and the meridians
are also straight lines at right angles to the equator, equally spaced. It is the basis for the transverse and
oblique forms of the projection. It is little used for land mapping purposes but is in almost universal use for
navigation charts. As well as being conformal, it has the particular property that straight lines drawn on it are
lines of constant bearing. Thus navigators may derive their course from the angle the straight course line
makes with the meridians.
In the few cases in which the Mercator projection is used for terrestrial applications or land mapping, such as
in Indonesia prior to the introduction of the Universal Transverse Mercator, a scale factor may be applied to
the projection. This has the same effect as choosing two standard parallels on which the true scale is
maintained at equal north and south latitudes either side of the equator.
Further Information in "Map Projections - A working Manual" can be find on www.epsg.org.

Andreas Bernatzky 25.08.2019
 */
 
#define D_R (M_PI / 180.0)
#define R_D (180.0 / M_PI)
#define EarthRadiusX 6378137.0
#define EarthRadiusY 6356752.3142
#define RATIO (EarthRadiusY/EarthRadiusX)
#define ECCENT (sqrt(1.0 - (RATIO * RATIO)))
#define COM (0.5 * ECCENT)

static double deg_rad (double ang) {
        return ang * D_R;
}
//Converts longitude coordinates into x-Coordinate of Mercator Transformation
double GeoToMerc_X (double lon) {
        return EarthRadiusX * deg_rad (lon);
}
//Converts latitude coordinates into y-Coordinate of Mercator Transformation
double GeoToMerc_Y (double lat) {
        lat = fmin (89.5, fmax (lat, -89.5));
        double phi = deg_rad(lat);
        double sinphi = sin(phi);
        double con = ECCENT * sinphi;
        con = pow((1.0 - con) / (1.0 + con), COM);
        double ts = tan(0.5 * (M_PI * 0.5 - phi)) / con;
        return 0 - EarthRadiusX * log(ts);
}

static double rad_deg (double ang) {
        return ang * R_D;
}
//Converts Mercator x-Coordinates back into Geocoordinates Longitude
double MercToGeo_Lon (double x) {
        return rad_deg(x) / EarthRadiusX;
}
//Converts Mercator y-Coordinates back into Geocoordinates Latitude
double MercToGeo_Lat (double y) {
        double ts = exp ( -y / EarthRadiusX);
        double phi = M_PI_2 - 2 * atan(ts);
        double dphi = 1.0;
        int i;
        for (i = 0; fabs(dphi) > 0.000000001 && i < 15; i++) {
                double con = ECCENT * sin (phi);
                dphi = M_PI_2 - 2 * atan (ts * pow((1.0 - con) / (1.0 + con), COM)) - phi;
                phi += dphi;
        }
        return rad_deg (phi);
}