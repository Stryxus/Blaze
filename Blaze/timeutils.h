#pragma once

long milliseconds_to_seconds(cr::milliseconds mill);

long milliseconds_to_minutes(cr::milliseconds mill);

long milliseconds_to_hours(cr::milliseconds mill);

long milliseconds_to_days(cr::milliseconds mill);

long milliseconds_to_weeks(cr::milliseconds mill);

long milliseconds_to_months(cr::milliseconds mill);

long milliseconds_to_years(cr::milliseconds mill);

string milliseconds_to_time_string(cr::milliseconds mill);

string milliseconds_to_date_string(cr::milliseconds mill);