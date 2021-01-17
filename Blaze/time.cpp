#include "pch.h"
#include "time.h"

long milliseconds_to_seconds(cr::milliseconds mill)
{
	return mill.count() / 1000;
}

long milliseconds_to_minutes(cr::milliseconds mill)
{
	return mill.count() / 1000 / 60;
}

long milliseconds_to_hours(cr::milliseconds mill)
{
	return mill.count() / 1000 / 60 / 60;
}

long milliseconds_to_days(cr::milliseconds mill)
{
	return mill.count() / 1000 / 60 / 60 / 24;
}

long milliseconds_to_weeks(cr::milliseconds mill)
{
	return mill.count() / 1000 / 60 / 60 / 24 / 7;
}

long milliseconds_to_months(cr::milliseconds mill)
{
	return mill.count() / 1000 / 60 / 60 / 24 / 7 / 4;
}

long milliseconds_to_years(cr::milliseconds mill)
{
	return mill.count() / 1000 / 60 / 60 / 24 / 7 / 4 / 12;
}

string milliseconds_to_time_string(cr::milliseconds mill)
{
	long mi = mill.count();
	long h = mi / 1000 / 60 / 60;
	mi = mi - 1000 * 60 * 60 * h;
	long m = mi / 1000 / 60;
	mi = mi - 1000 * 60 * m;
	long s = mi / 1000;
	mi = mi - 1000 * s;
	return (to_string(h).length() > 1 ? to_string(h) : "0" + to_string(h)) + ":" + 
		(to_string(m).length() > 1 ? to_string(m) : "0" + to_string(m)) + ":" + 
		(to_string(s).length() > 1 ? to_string(s) : "0" + to_string(s)) + "." + 
		to_string(mi).substr(0, 3);
}

string milliseconds_to_date_string(cr::milliseconds mill)
{
	long mi = mill.count();
	long y = mi / 1000 / 60 / 60 / 4 / 7 / 4 / 12;
	mi = mi - 1000 * 60 * 60 * 24 * 7 * 4 * 12 * y;
	long m = mi / 1000 / 60 / 60 / 24 / 7 / 4;
	mi = mi - 1000 * 60 * 60 * 24 * 7 * 4 * m;
	long d = mi / 1000 / 60 / 60 / 24;
	mi = mi - 1000 * 60 * 60 * 24 * d;
	return (to_string(y).length() > 1 ? to_string(y) : "0" + to_string(y)) + ":" +
		(to_string(m).length() > 1 ? to_string(m) : "0" + to_string(m)) + ":" +
		(to_string(d).length() > 1 ? to_string(d) : "0" + to_string(d)) + "." +
		to_string(mi).substr(0, 3);
}