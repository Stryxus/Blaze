#include "pch.h"
#include "time.h"

long long milliseconds_to_seconds(cr::milliseconds mill)
{
	return mill.count() / 1000L;
}

long long milliseconds_to_minutes(cr::milliseconds mill)
{
	return mill.count() / 1000L / 60L;
}

long long milliseconds_to_hours(cr::milliseconds mill)
{
	return mill.count() / 1000L / 60L / 60L;
}

long long milliseconds_to_days(cr::milliseconds mill)
{
	return mill.count() / 1000L / 60L / 60L / 24L;
}

long long milliseconds_to_weeks(cr::milliseconds mill)
{
	return mill.count() / 1000L / 60L / 60L / 24L / 7L;
}

long long milliseconds_to_months(cr::milliseconds mill)
{
	return mill.count() / 1000L / 60L / 60L / 24L / 7L / 4L;
}

long long milliseconds_to_years(cr::milliseconds mill)
{
	return mill.count() / 1000L / 60L / 60L / 24L / 7L / 4L / 12L;
}

string milliseconds_to_time_string(cr::milliseconds mill)
{
	long long mi = mill.count();
	long long h = mi / 1000L / 60L / 60L;
	mi = mi - 1000L * 60L * 60L * h;
	long long m = mi / 1000L / 60L;
	mi = mi - 1000L * 60L * m;
	long long s = mi / 1000L;
	mi = mi - 1000L * s;
	return (to_string(h).length() > 1 ? to_string(h) : "0" + to_string(h)) + ":" + 
		(to_string(m).length() > 1 ? to_string(m) : "0" + to_string(m)) + ":" + 
		(to_string(s).length() > 1 ? to_string(s) : "0" + to_string(s)) + "." + 
		to_string(mi).substr(0, 3);
}

string milliseconds_to_date_string(cr::milliseconds mill)
{
	long long mi = mill.count();
	long long y = mi / 1000L / 60L / 60L / 4L / 7L / 4L / 12L;
	mi = mi - 1000L * 60L * 60L * 24L * 7L * 4L * 12L * y;
	long long m = mi / 1000L / 60L / 60L / 24L / 7L / 4L;
	mi = mi - 1000L * 60L * 60L * 24L * 7L * 4L * m;
	long long d = mi / 1000 / 60L / 60L / 24L;
	mi = mi - 1000L * 60L * 60L * 24L * d;
	return (to_string(y).length() > 1 ? to_string(y) : "0" + to_string(y)) + ":" +
		(to_string(m).length() > 1 ? to_string(m) : "0" + to_string(m)) + ":" +
		(to_string(d).length() > 1 ? to_string(d) : "0" + to_string(d)) + "." +
		to_string(mi).substr(0, 3);
}