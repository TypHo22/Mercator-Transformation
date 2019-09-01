#include <MercatorTransformation.h>


#define M_PI   3.14159265358979323846264338327950288
#define D_R (M_PI / 180.0)
#define R_D (180.0 / M_PI)
#define EarthRadiusX 6378137.0
#define EarthRadiusY 6356752.3142
#define RATIO (EarthRadiusY/EarthRadiusX)
#define ECCENT (sqrt(1.0 - (RATIO * RATIO)))
#define COM (0.5 * ECCENT)

static double deg_rad(double ang) {
	return ang * D_R;
}
//Converts longitude coordinates into x-Coordinate of Mercator Transformation
double GeoToMerc_X(double lon) {
	return EarthRadiusX * deg_rad(lon);
}
//Converts latitude coordinates into y-Coordinate of Mercator Transformation
double GeoToMerc_Y(double lat) {
	lat = fmin(89.5, fmax(lat, -89.5));
	double phi = deg_rad(lat);
	double sinphi = sin(phi);
	double con = ECCENT * sinphi;
	con = pow((1.0 - con) / (1.0 + con), COM);
	double ts = tan(0.5 * (M_PI * 0.5 - phi)) / con;
	return 0 - EarthRadiusX * log(ts);
}

static double rad_deg(double ang) {
	return ang * R_D;
}
//Converts Mercator x-Coordinates back into Geocoordinates Longitude
double MercToGeo_Lon(double x) {
	return rad_deg(x) / EarthRadiusX;
}
//Converts Mercator y-Coordinates back into Geocoordinates Latitude
double MercToGeo_Lat(double y) {
	double ts = exp(-y / EarthRadiusX);
	double phi = M_PI * 2 - 2 * atan(ts);
	double dphi = 1.0;
	int i;
	for (i = 0; fabs(dphi) > 0.000000001 && i < 15; i++) {
		double con = ECCENT * sin(phi);
		dphi = M_PI * 2 - 2 * atan(ts * pow((1.0 - con) / (1.0 + con), COM)) - phi;
		phi += dphi;
	}
	return rad_deg(phi);
}