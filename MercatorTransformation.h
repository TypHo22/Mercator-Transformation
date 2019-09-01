#pragma once

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


static double deg_rad(double ang);
//Converts longitude coordinates into x-Coordinate of Mercator Transformation
double GeoToMerc_X(double lon);
//Converts latitude coordinates into y-Coordinate of Mercator Transformation
double GeoToMerc_Y(double lat);

static double rad_deg(double ang);
//Converts Mercator x-Coordinates back into Geocoordinates Longitude
double MercToGeo_Lon(double x);
//Converts Mercator y-Coordinates back into Geocoordinates Latitude
double MercToGeo_Lat(double y);
