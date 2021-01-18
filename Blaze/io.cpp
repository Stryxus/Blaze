#include "pch.h"
#include "io.h"

bool file_exists(const string& file_path)
{
	struct stat buffer;
	return stat(file_path.c_str(), &buffer) == 0;
}

void create_file(const string& file_path)
{
	ofstream(file_path).close();
}

//

inline unsigned int				base_bit			= 1;
inline unsigned int				bits_in_kilo		= base_bit					* 1000u;
inline unsigned int				bits_in_mega		= bits_in_kilo				* 1000u;
inline unsigned long			bits_in_giga		= (long)bits_in_mega		* 1000u;
inline unsigned long			bits_in_terra		= bits_in_giga				* 1000u;
inline unsigned long			bits_in_petta		= bits_in_giga				* 1000u;
inline unsigned long long		bits_in_exa			= (long long)bits_in_petta	* 1000u;
inline unsigned long long		bits_in_zetta		= bits_in_exa				* 1000u;
inline unsigned long long		bits_in_yotta		= bits_in_zetta				* 1000u;

inline unsigned int				base_byte			= 8;
inline unsigned int				bytes_in_kilo		= base_byte					* 1000u;
inline unsigned int				bytes_in_mega		= bytes_in_kilo				* 1000u;
inline unsigned long			bytes_in_giga		= (long)bytes_in_mega		* 1000u;
inline unsigned long			bytes_in_terra		= bytes_in_giga				* 1000u;
inline unsigned long			bytes_in_petta		= bytes_in_terra			* 1000u;
inline unsigned long long		bytes_in_exa		= (long long)bytes_in_petta	* 1000u;
inline unsigned long long		bytes_in_zetta		= bytes_in_exa				* 1000u;
inline unsigned long long		bytes_in_yotta		= bytes_in_zetta			* 1000u;

void convert_data_magnitude_to_bits(double value, BYTE_MAGNITUDE from_magnitude, BIT_MAGNITUDE to_magnitude)
{
	try
	{
		if (from_magnitude == BYTE_MAGNITUDE::BYTE)
		{
				 if (to_magnitude == BIT_MAGNITUDE::BIT)			value = value * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		value = (value / bytes_in_kilo) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		value = (value / bytes_in_mega) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		value = (value / bytes_in_giga) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		value = (value / bytes_in_terra) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		value = (value / bytes_in_petta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		value = (value / bytes_in_exa) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		value = (value / bytes_in_zetta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		value = (value / bytes_in_yotta) * base_byte;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::KILO_BYTE)
		{
				 if (to_magnitude == BIT_MAGNITUDE::BIT)			value = value * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		value = (value / bytes_in_kilo) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		value = (value / bytes_in_mega) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		value = (value / bytes_in_giga) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		value = (value / bytes_in_terra) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		value = (value / bytes_in_petta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		value = (value / bytes_in_exa) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		value = (value / bytes_in_zetta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		value = (value / bytes_in_yotta) * base_byte;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)
		{
				 if (to_magnitude == BIT_MAGNITUDE::BIT)			value = value * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		value = (value / bytes_in_kilo) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		value = (value / bytes_in_mega) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		value = (value / bytes_in_giga) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		value = (value / bytes_in_terra) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		value = (value / bytes_in_petta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		value = (value / bytes_in_exa) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		value = (value / bytes_in_zetta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		value = (value / bytes_in_yotta) * base_byte;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)
		{
				 if (to_magnitude == BIT_MAGNITUDE::BIT)			value = value * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		value = (value / bytes_in_kilo) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		value = (value / bytes_in_mega) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		value = (value / bytes_in_giga) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		value = (value / bytes_in_terra) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		value = (value / bytes_in_petta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		value = (value / bytes_in_exa) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		value = (value / bytes_in_zetta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		value = (value / bytes_in_yotta) * base_byte;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)
		{
				 if (to_magnitude == BIT_MAGNITUDE::BIT)			value = value * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		value = (value / bytes_in_kilo) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		value = (value / bytes_in_mega) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		value = (value / bytes_in_giga) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		value = (value / bytes_in_terra) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		value = (value / bytes_in_petta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		value = (value / bytes_in_exa) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		value = (value / bytes_in_zetta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		value = (value / bytes_in_yotta) * base_byte;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)
		{
				 if (to_magnitude == BIT_MAGNITUDE::BIT)			value = value * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		value = (value / bytes_in_kilo) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		value = (value / bytes_in_mega) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		value = (value / bytes_in_giga) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		value = (value / bytes_in_terra) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		value = (value / bytes_in_petta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		value = (value / bytes_in_exa) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		value = (value / bytes_in_zetta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		value = (value / bytes_in_yotta) * base_byte;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::EXA_BYTE)
		{
				 if (to_magnitude == BIT_MAGNITUDE::BIT)			value = value * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		value = (value / bytes_in_kilo) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		value = (value / bytes_in_mega) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		value = (value / bytes_in_giga) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		value = (value / bytes_in_terra) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		value = (value / bytes_in_petta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		value = (value / bytes_in_exa) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		value = (value / bytes_in_zetta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		value = (value / bytes_in_yotta) * base_byte;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)
		{
				 if (to_magnitude == BIT_MAGNITUDE::BIT)			value = value * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		value = (value / bytes_in_kilo) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		value = (value / bytes_in_mega) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		value = (value / bytes_in_giga) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		value = (value / bytes_in_terra) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		value = (value / bytes_in_petta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		value = (value / bytes_in_exa) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		value = (value / bytes_in_zetta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		value = (value / bytes_in_yotta) * base_byte;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)
		{
				 if (to_magnitude == BIT_MAGNITUDE::BIT)			value = value * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		value = (value / bytes_in_kilo) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		value = (value / bytes_in_mega) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		value = (value / bytes_in_giga) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		value = (value / bytes_in_terra) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		value = (value / bytes_in_petta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		value = (value / bytes_in_exa) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		value = (value / bytes_in_zetta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		value = (value / bytes_in_yotta) * base_byte;
		}
	}
	catch (const char* msg)
	{
		Logger::log_error(msg);
	}
}

void convert_data_magnitude_to_bytes(unsigned long long value, BIT_MAGNITUDE from_magnitude, BYTE_MAGNITUDE to_magnitude)
{
	try
	{
		if (from_magnitude == BIT_MAGNITUDE::BIT)
		{
				 if (to_magnitude == BYTE_MAGNITUDE::BYTE)			value = value / base_byte;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		value = (value / base_byte) / bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		value = (value / base_byte) / bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		value = (value / base_byte) / bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	value = (value / base_byte) / bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	value = (value / base_byte) / bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		value = (value / base_byte) / bytes_in_exa;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	value = (value / base_byte) / bytes_in_zetta;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	value = (value / base_byte) / bytes_in_yotta;
		}
		else if (from_magnitude == BIT_MAGNITUDE::KILO_BIT)
		{
				 if (to_magnitude == BYTE_MAGNITUDE::BYTE)			value = (value / base_byte) * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		value = value / base_byte;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		value = (value / base_byte) / bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		value = (value / base_byte) / bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	value = (value / base_byte) / bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	value = (value / base_byte) / bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		value = (value / base_byte) / bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	value = (value / base_byte) / bytes_in_exa;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	value = (value / base_byte) / bytes_in_zetta;
		}
		else if (from_magnitude == BIT_MAGNITUDE::MEGA_BIT)
		{
				 if (to_magnitude == BYTE_MAGNITUDE::BYTE)			value = (value / base_byte) * bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		value = (value / base_byte) * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		value = value / base_byte;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		value = (value / base_byte) / bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	value = (value / base_byte) / bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	value = (value / base_byte) / bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		value = (value / base_byte) / bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	value = (value / base_byte) / bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	value = (value / base_byte) / bytes_in_exa;
		}
		else if (from_magnitude == BIT_MAGNITUDE::GIGA_BIT)
		{
				 if (to_magnitude == BYTE_MAGNITUDE::BYTE)			value = (value / base_byte) * bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		value = (value / base_byte) * bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		value = (value / base_byte) * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		value = value / base_byte;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	value = (value / base_byte) / bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	value = (value / base_byte) / bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		value = (value / base_byte) / bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	value = (value / base_byte) / bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	value = (value / base_byte) / bytes_in_petta;
		}
		else if (from_magnitude == BIT_MAGNITUDE::TERRA_BIT)
		{
				 if (to_magnitude == BYTE_MAGNITUDE::BYTE)			value = (value / base_byte) * bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		value = (value / base_byte) * bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		value = (value / base_byte) * bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		value = (value / base_byte) * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	value = value / base_byte;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	value = (value / base_byte) / bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		value = (value / base_byte) / bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	value = (value / base_byte) / bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	value = (value / base_byte) / bytes_in_terra;
		}
		else if (from_magnitude == BIT_MAGNITUDE::PETTA_BIT)
		{
				 if (to_magnitude == BYTE_MAGNITUDE::BYTE)			value = (value / base_byte) * bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		value = (value / base_byte) * bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		value = (value / base_byte) * bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		value = (value / base_byte) * bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	value = (value / base_byte) * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	value = value / base_byte;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		value = (value / base_byte) / bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	value = (value / base_byte) / bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	value = (value / base_byte) / bytes_in_giga;
		}
		else if (from_magnitude == BIT_MAGNITUDE::EXA_BIT)
		{
				 if (to_magnitude == BYTE_MAGNITUDE::BYTE)			value = (value / base_byte) * bytes_in_exa;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		value = (value / base_byte) * bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		value = (value / base_byte) * bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		value = (value / base_byte) * bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	value = (value / base_byte) * bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	value = (value / base_byte) * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		value = value / base_byte;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	value = (value / base_byte) / bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	value = (value / base_byte) / bytes_in_mega;
		}
		else if (from_magnitude == BIT_MAGNITUDE::ZETTA_BIT)
		{
				 if (to_magnitude == BYTE_MAGNITUDE::BYTE)			value = (value / base_byte) * bytes_in_zetta;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		value = (value / base_byte) * bytes_in_exa;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		value = (value / base_byte) * bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		value = (value / base_byte) * bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	value = (value / base_byte) * bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	value = (value / base_byte) * bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		value = (value / base_byte) * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	value = value / base_byte;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	value = (value / base_byte) / bytes_in_yotta;
		}
		else if (from_magnitude == BIT_MAGNITUDE::YOTTA_BIT)
		{
				 if (to_magnitude == BYTE_MAGNITUDE::BYTE)			value = (value / base_byte) * bytes_in_yotta;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		value = (value / base_byte) * bytes_in_zetta;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		value = (value / base_byte) * bytes_in_exa;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		value = (value / base_byte) * bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	value = (value / base_byte) * bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	value = (value / base_byte) * bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		value = (value / base_byte) * bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	value = (value / base_byte) * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	value = value / base_byte;
		}
	}
	catch (const char* msg)
	{
		Logger::log_error(msg);
	}
}

void convert_data_magnitude_in_bits(double value, BIT_MAGNITUDE from_magnitude, BIT_MAGNITUDE to_magnitude)
{
	try
	{
		if (from_magnitude == BIT_MAGNITUDE::BIT)
		{
				 if (to_magnitude == BIT_MAGNITUDE::BIT)			throw;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		value = value / bits_in_kilo;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		value = value / bits_in_mega;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		value = value / bits_in_giga;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		value = value / bits_in_terra;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		value = value / bits_in_petta;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		value = value / bits_in_exa;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		value = value / bits_in_zetta;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		value = value / bits_in_yotta;
		}
		else if (from_magnitude == BIT_MAGNITUDE::KILO_BIT)
		{
				 if (to_magnitude == BIT_MAGNITUDE::BIT)			value = value * bits_in_kilo;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		throw;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		value = value / bits_in_mega;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		value = value / bits_in_giga;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		value = value / bits_in_terra;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		value = value / bits_in_petta;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		value = value / bits_in_exa;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		value = value / bits_in_zetta;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		value = value / bits_in_yotta;
		}
		else if (from_magnitude == BIT_MAGNITUDE::MEGA_BIT)
		{
				 if (to_magnitude == BIT_MAGNITUDE::BIT)			value = value * bits_in_kilo;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		value = value * bits_in_mega;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		throw;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		value = value / bits_in_giga;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		value = value / bits_in_terra;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		value = value / bits_in_petta;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		value = value / bits_in_exa;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		value = value / bits_in_zetta;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		value = value / bits_in_yotta;
		}
		else if (from_magnitude == BIT_MAGNITUDE::GIGA_BIT)
		{
				 if (to_magnitude == BIT_MAGNITUDE::BIT)			value = value * bits_in_kilo;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		value = value * bits_in_mega;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		value = value * bits_in_giga;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		throw;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		value = value / bits_in_terra;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		value = value / bits_in_petta;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		value = value / bits_in_exa;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		value = value / bits_in_zetta;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		value = value / bits_in_yotta;
		}
		else if (from_magnitude == BIT_MAGNITUDE::TERRA_BIT)
		{
				 if (to_magnitude == BIT_MAGNITUDE::BIT)			value = value * bits_in_kilo;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		value = value * bits_in_mega;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		value = value * bits_in_giga;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		value = value * bits_in_terra;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		throw;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		value = value / bits_in_petta;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		value = value / bits_in_exa;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		value = value / bits_in_zetta;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		value = value / bits_in_yotta;
		}
		else if (from_magnitude == BIT_MAGNITUDE::PETTA_BIT)
		{
				 if (to_magnitude == BIT_MAGNITUDE::BIT)			value = value * bits_in_kilo;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		value = value * bits_in_mega;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		value = value * bits_in_giga;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		value = value * bits_in_terra;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		value = value * bits_in_petta;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		throw;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		value = value / bits_in_exa;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		value = value / bits_in_zetta;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		value = value / bits_in_yotta;
		}
		else if (from_magnitude == BIT_MAGNITUDE::EXA_BIT)
		{
				 if (to_magnitude == BIT_MAGNITUDE::BIT)			value = value * bits_in_kilo;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		value = value * bits_in_mega;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		value = value * bits_in_giga;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		value = value * bits_in_terra;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		value = value * bits_in_petta;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		value = value * bits_in_exa;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		throw;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		value = value / bits_in_zetta;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		value = value / bits_in_yotta;
		}
		else if (from_magnitude == BIT_MAGNITUDE::ZETTA_BIT)
		{
				 if (to_magnitude == BIT_MAGNITUDE::BIT)			value = value * bits_in_kilo;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		value = value * bits_in_mega;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		value = value * bits_in_giga;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		value = value * bits_in_terra;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		value = value * bits_in_petta;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		value = value * bits_in_exa;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		value = value * bits_in_zetta;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		throw;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		value = value / bits_in_yotta;
		}
		else if (from_magnitude == BIT_MAGNITUDE::YOTTA_BIT)
		{
				 if (to_magnitude == BIT_MAGNITUDE::BIT)			value = value * bits_in_kilo;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		value = value * bits_in_mega;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		value = value * bits_in_giga;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		value = value * bits_in_terra;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		value = value * bits_in_petta;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		value = value * bits_in_exa;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		value = value * bits_in_zetta;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		value = value * bits_in_yotta;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		throw;
		}
	}
	catch (const char* msg)
	{
		Logger::log_error(msg);
	}
}

void convert_data_magnitude_in_bytes(double value, BYTE_MAGNITUDE from_magnitude, BYTE_MAGNITUDE to_magnitude)
{
	try
	{
		if (from_magnitude == BYTE_MAGNITUDE::BYTE)
		{
				 if (to_magnitude == BYTE_MAGNITUDE::BYTE)			throw;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		value = value / bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		value = value / bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		value = value / bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	value = value / bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	value = value / bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		value = value / bytes_in_exa;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	value = value / bytes_in_zetta;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	value = value / bytes_in_yotta;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::KILO_BYTE)
		{
				 if (to_magnitude == BYTE_MAGNITUDE::BYTE)			value = value * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		throw;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		value = value / bytes_in_zetta;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		value = value / bytes_in_exa;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	value = value / bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	value = value / bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		value = value / bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	value = value / bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	value = value / bytes_in_kilo;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)
		{
				 if (to_magnitude == BYTE_MAGNITUDE::BYTE)			value = value * bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		value = value * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		throw;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		value = value / bytes_in_exa;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	value = value / bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	value = value / bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		value = value / bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	value = value / bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	value = value / bytes_in_kilo;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)
		{
				 if (to_magnitude == BYTE_MAGNITUDE::BYTE)			value = value * bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		value = value * bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		value = value * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		throw;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	value = value / bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	value = value / bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		value = value / bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	value = value / bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	value = value / bytes_in_kilo;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)
		{
				 if (to_magnitude == BYTE_MAGNITUDE::BYTE)			value = value * bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		value = value * bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		value = value * bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		value = value * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	throw;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	value = value / bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		value = value / bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	value = value / bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	value = value / bytes_in_kilo;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)
		{
				 if (to_magnitude == BYTE_MAGNITUDE::BYTE)			value = value * bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		value = value * bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		value = value * bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		value = value * bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	value = value * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	throw;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		value = value / bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	value = value / bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	value = value / bytes_in_kilo;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::EXA_BYTE)
		{
				 if (to_magnitude == BYTE_MAGNITUDE::BYTE)			value = value * bytes_in_yotta;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		value = value * bytes_in_zetta;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		value = value * bytes_in_exa;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		value = value * bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	value = value * bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	value = value * bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		throw;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	value = value / bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	value = value / bytes_in_mega;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)
		{
				 if (to_magnitude == BYTE_MAGNITUDE::BYTE)			value = value * bytes_in_zetta;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		value = value * bytes_in_exa;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		value = value * bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		value = value * bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	value = value * bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	value = value * bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		value = value * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	throw;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	value = value / bytes_in_kilo;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)
		{
				 if (to_magnitude == BYTE_MAGNITUDE::BYTE)			value = value * bytes_in_yotta;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		value = value * bytes_in_zetta;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		value = value * bytes_in_exa;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		value = value * bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	value = value * bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	value = value * bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		value = value * bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	value = value * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	throw;
		}
	}
	catch (const char* msg)
	{
		Logger::log_error(msg);
	}
}

double convert_data_magnitude_to_bits_copy(double value, BYTE_MAGNITUDE from_magnitude, BIT_MAGNITUDE to_magnitude)
{
	try
	{
		if (from_magnitude == BYTE_MAGNITUDE::BYTE)
		{
			if (to_magnitude == BIT_MAGNITUDE::BIT)					return value * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		return (value / bytes_in_kilo) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		return (value / bytes_in_mega) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		return (value / bytes_in_giga) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		return (value / bytes_in_terra) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		return (value / bytes_in_petta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		return (value / bytes_in_exa) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		return (value / bytes_in_zetta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		return (value / bytes_in_yotta) * base_byte;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::KILO_BYTE)
		{
			if (to_magnitude == BIT_MAGNITUDE::BIT)					return value * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		return (value / bytes_in_kilo) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		return (value / bytes_in_mega) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		return (value / bytes_in_giga) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		return (value / bytes_in_terra) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		return (value / bytes_in_petta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		return (value / bytes_in_exa) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		return (value / bytes_in_zetta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		return (value / bytes_in_yotta) * base_byte;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)
		{
			if (to_magnitude == BIT_MAGNITUDE::BIT)					return value * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		return (value / bytes_in_kilo) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		return (value / bytes_in_mega) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		return (value / bytes_in_giga) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		return (value / bytes_in_terra) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		return (value / bytes_in_petta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		return (value / bytes_in_exa) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		return (value / bytes_in_zetta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		return (value / bytes_in_yotta) * base_byte;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)
		{
			if (to_magnitude == BIT_MAGNITUDE::BIT)					return value * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		return (value / bytes_in_kilo) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		return (value / bytes_in_mega) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		return (value / bytes_in_giga) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		return (value / bytes_in_terra) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		return (value / bytes_in_petta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		return (value / bytes_in_exa) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		return (value / bytes_in_zetta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		return (value / bytes_in_yotta) * base_byte;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)
		{
			if (to_magnitude == BIT_MAGNITUDE::BIT)					return value * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		return (value / bytes_in_kilo) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		return (value / bytes_in_mega) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		return (value / bytes_in_giga) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		return (value / bytes_in_terra) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		return (value / bytes_in_petta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		return (value / bytes_in_exa) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		return (value / bytes_in_zetta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		return (value / bytes_in_yotta) * base_byte;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)
		{
			if (to_magnitude == BIT_MAGNITUDE::BIT)					return value * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		return (value / bytes_in_kilo) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		return (value / bytes_in_mega) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		return (value / bytes_in_giga) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		return (value / bytes_in_terra) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		return (value / bytes_in_petta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		return (value / bytes_in_exa) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		return (value / bytes_in_zetta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		return (value / bytes_in_yotta) * base_byte;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::EXA_BYTE)
		{
			if (to_magnitude == BIT_MAGNITUDE::BIT)					return value * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		return (value / bytes_in_kilo) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		return (value / bytes_in_mega) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		return (value / bytes_in_giga) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		return (value / bytes_in_terra) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		return (value / bytes_in_petta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		return (value / bytes_in_exa) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		return (value / bytes_in_zetta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		return (value / bytes_in_yotta) * base_byte;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)
		{
			if (to_magnitude == BIT_MAGNITUDE::BIT)					return value * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		return (value / bytes_in_kilo) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		return (value / bytes_in_mega) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		return (value / bytes_in_giga) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		return (value / bytes_in_terra) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		return (value / bytes_in_petta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		return (value / bytes_in_exa) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		return (value / bytes_in_zetta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		return (value / bytes_in_yotta) * base_byte;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)
		{
			if (to_magnitude == BIT_MAGNITUDE::BIT)					return value * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		return (value / bytes_in_kilo) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		return (value / bytes_in_mega) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		return (value / bytes_in_giga) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		return (value / bytes_in_terra) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		return (value / bytes_in_petta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		return (value / bytes_in_exa) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		return (value / bytes_in_zetta) * base_byte;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		return (value / bytes_in_yotta) * base_byte;
		}
		else return 0L;
	}
	catch (const char* msg)
	{
		Logger::log_error(msg);
		return 0L;
	}
	return 0L;
}

double convert_data_magnitude_to_bytes_copy(double value, BIT_MAGNITUDE from_magnitude, BYTE_MAGNITUDE to_magnitude)
{
	try
	{
		if (from_magnitude == BIT_MAGNITUDE::BIT)
		{
			if (to_magnitude == BYTE_MAGNITUDE::BYTE)				return value / base_byte;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		return (value / base_byte) / bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		return (value / base_byte) / bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		return (value / base_byte) / bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	return (value / base_byte) / bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	return (value / base_byte) / bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		return (value / base_byte) / bytes_in_exa;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	return (value / base_byte) / bytes_in_zetta;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	return (value / base_byte) / bytes_in_yotta;
		}
		else if (from_magnitude == BIT_MAGNITUDE::KILO_BIT)
		{
			if (to_magnitude == BYTE_MAGNITUDE::BYTE)				return (value / base_byte) * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		return value / base_byte;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		return (value / base_byte) / bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		return (value / base_byte) / bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	return (value / base_byte) / bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	return (value / base_byte) / bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		return (value / base_byte) / bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	return (value / base_byte) / bytes_in_exa;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	return (value / base_byte) / bytes_in_zetta;
		}
		else if (from_magnitude == BIT_MAGNITUDE::MEGA_BIT)
		{
			if (to_magnitude == BYTE_MAGNITUDE::BYTE)				return (value / base_byte) * bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		return (value / base_byte) * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		return value / base_byte;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		return (value / base_byte) / bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	return (value / base_byte) / bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	return (value / base_byte) / bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		return (value / base_byte) / bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	return (value / base_byte) / bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	return (value / base_byte) / bytes_in_exa;
		}
		else if (from_magnitude == BIT_MAGNITUDE::GIGA_BIT)
		{
			if (to_magnitude == BYTE_MAGNITUDE::BYTE)				return (value / base_byte) * bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		return (value / base_byte) * bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		return (value / base_byte) * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		return value / base_byte;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	return (value / base_byte) / bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	return (value / base_byte) / bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		return (value / base_byte) / bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	return (value / base_byte) / bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	return (value / base_byte) / bytes_in_petta;
		}
		else if (from_magnitude == BIT_MAGNITUDE::TERRA_BIT)
		{
			if (to_magnitude == BYTE_MAGNITUDE::BYTE)				return (value / base_byte) * bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		return (value / base_byte) * bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		return (value / base_byte) * bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		return (value / base_byte) * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	return value / base_byte;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	return (value / base_byte) / bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		return (value / base_byte) / bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	return (value / base_byte) / bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	return (value / base_byte) / bytes_in_terra;
		}
		else if (from_magnitude == BIT_MAGNITUDE::PETTA_BIT)
		{
			if (to_magnitude == BYTE_MAGNITUDE::BYTE)				return (value / base_byte) * bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		return (value / base_byte) * bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		return (value / base_byte) * bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		return (value / base_byte) * bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	return (value / base_byte) * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	return value / base_byte;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		return (value / base_byte) / bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	return (value / base_byte) / bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	return (value / base_byte) / bytes_in_giga;
		}
		else if (from_magnitude == BIT_MAGNITUDE::EXA_BIT)
		{
			if (to_magnitude == BYTE_MAGNITUDE::BYTE)				return (value / base_byte) * bytes_in_exa;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		return (value / base_byte) * bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		return (value / base_byte) * bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		return (value / base_byte) * bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	return (value / base_byte) * bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	return (value / base_byte) * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		return value / base_byte;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	return (value / base_byte) / bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	return (value / base_byte) / bytes_in_mega;
		}
		else if (from_magnitude == BIT_MAGNITUDE::ZETTA_BIT)
		{
			if (to_magnitude == BYTE_MAGNITUDE::BYTE)				return (value / base_byte) * bytes_in_zetta;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		return (value / base_byte) * bytes_in_exa;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		return (value / base_byte) * bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		return (value / base_byte) * bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	return (value / base_byte) * bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	return (value / base_byte) * bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		return (value / base_byte) * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	return value / base_byte;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	return (value / base_byte) / bytes_in_yotta;
		}
		else if (from_magnitude == BIT_MAGNITUDE::YOTTA_BIT)
		{
			if (to_magnitude == BYTE_MAGNITUDE::BYTE)				return (value / base_byte) * bytes_in_yotta;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		return (value / base_byte) * bytes_in_zetta;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		return (value / base_byte) * bytes_in_exa;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		return (value / base_byte) * bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	return (value / base_byte) * bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	return (value / base_byte) * bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		return (value / base_byte) * bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	return (value / base_byte) * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	return value / base_byte;
		}
		else return 0L;
	}
	catch (const char* msg)
	{
		Logger::log_error(msg);
		return 0L;
	}
	return 0L;
}

double convert_data_magnitude_in_bits_copy(double value, BIT_MAGNITUDE from_magnitude, BIT_MAGNITUDE to_magnitude)
{
	try
	{
		if (from_magnitude == BIT_MAGNITUDE::BIT)
		{
			if (to_magnitude == BIT_MAGNITUDE::BIT)					throw;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		return value / bits_in_kilo;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		return value / bits_in_mega;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		return value / bits_in_giga;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		return value / bits_in_terra;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		return value / bits_in_petta;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		return value / bits_in_exa;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		return value / bits_in_zetta;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		return value / bits_in_yotta;
		}
		else if (from_magnitude == BIT_MAGNITUDE::KILO_BIT)
		{
			if (to_magnitude == BIT_MAGNITUDE::BIT)					return value * bits_in_kilo;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		throw;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		return value / bits_in_mega;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		return value / bits_in_giga;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		return value / bits_in_terra;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		return value / bits_in_petta;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		return value / bits_in_exa;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		return value / bits_in_zetta;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		return value / bits_in_yotta;
		}
		else if (from_magnitude == BIT_MAGNITUDE::MEGA_BIT)
		{
			if (to_magnitude == BIT_MAGNITUDE::BIT)					return value * bits_in_kilo;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		return value * bits_in_mega;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		throw;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		return value / bits_in_giga;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		return value / bits_in_terra;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		return value / bits_in_petta;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		return value / bits_in_exa;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		return value / bits_in_zetta;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		return value / bits_in_yotta;
		}
		else if (from_magnitude == BIT_MAGNITUDE::GIGA_BIT)
		{
			if (to_magnitude == BIT_MAGNITUDE::BIT)					return value * bits_in_kilo;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		return value * bits_in_mega;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		return value * bits_in_giga;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		throw;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		return value / bits_in_terra;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		return value / bits_in_petta;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		return value / bits_in_exa;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		return value / bits_in_zetta;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		return value / bits_in_yotta;
		}
		else if (from_magnitude == BIT_MAGNITUDE::TERRA_BIT)
		{
			if (to_magnitude == BIT_MAGNITUDE::BIT)					return value * bits_in_kilo;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		return value * bits_in_mega;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		return value * bits_in_giga;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		return value * bits_in_terra;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		throw;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		return value / bits_in_petta;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		return value / bits_in_exa;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		return value / bits_in_zetta;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		return value / bits_in_yotta;
		}
		else if (from_magnitude == BIT_MAGNITUDE::PETTA_BIT)
		{
			if (to_magnitude == BIT_MAGNITUDE::BIT)					return value * bits_in_kilo;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		return value * bits_in_mega;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		return value * bits_in_giga;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		return value * bits_in_terra;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		return value * bits_in_petta;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		throw;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		return value / bits_in_exa;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		return value / bits_in_zetta;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		return value / bits_in_yotta;
		}
		else if (from_magnitude == BIT_MAGNITUDE::EXA_BIT)
		{
			if (to_magnitude == BIT_MAGNITUDE::BIT)					return value * bits_in_kilo;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		return value * bits_in_mega;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		return value * bits_in_giga;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		return value * bits_in_terra;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		return value * bits_in_petta;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		return value * bits_in_exa;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		throw;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		return value / bits_in_zetta;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		return value / bits_in_yotta;
		}
		else if (from_magnitude == BIT_MAGNITUDE::ZETTA_BIT)
		{
			if (to_magnitude == BIT_MAGNITUDE::BIT)					return value * bits_in_kilo;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		return value * bits_in_mega;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		return value * bits_in_giga;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		return value * bits_in_terra;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		return value * bits_in_petta;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		return value * bits_in_exa;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		return value * bits_in_zetta;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		throw;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		return value / bits_in_yotta;
		}
		else if (from_magnitude == BIT_MAGNITUDE::YOTTA_BIT)
		{
			if (to_magnitude == BIT_MAGNITUDE::BIT)					return value * bits_in_kilo;
			else if (to_magnitude == BIT_MAGNITUDE::KILO_BIT)		return value * bits_in_mega;
			else if (to_magnitude == BIT_MAGNITUDE::MEGA_BIT)		return value * bits_in_giga;
			else if (to_magnitude == BIT_MAGNITUDE::GIGA_BIT)		return value * bits_in_terra;
			else if (to_magnitude == BIT_MAGNITUDE::TERRA_BIT)		return value * bits_in_petta;
			else if (to_magnitude == BIT_MAGNITUDE::PETTA_BIT)		return value * bits_in_exa;
			else if (to_magnitude == BIT_MAGNITUDE::EXA_BIT)		return value * bits_in_zetta;
			else if (to_magnitude == BIT_MAGNITUDE::ZETTA_BIT)		return value * bits_in_yotta;
			else if (to_magnitude == BIT_MAGNITUDE::YOTTA_BIT)		throw;
		}
		else return 0L;
	}
	catch (const char* msg)
	{
		Logger::log_error(msg);
		return 0L;
	}
	return 0L;
}

double convert_data_magnitude_in_bytes_copy(double value, BYTE_MAGNITUDE from_magnitude, BYTE_MAGNITUDE to_magnitude)
{
	try
	{
		if (from_magnitude == BYTE_MAGNITUDE::BYTE)
		{
			if (to_magnitude == BYTE_MAGNITUDE::BYTE)				throw;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		return value / bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		return value / bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		return value / bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	return value / bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	return value / bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		return value / bytes_in_exa;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	return value / bytes_in_zetta;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	return value / bytes_in_yotta;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::KILO_BYTE)
		{
			if (to_magnitude == BYTE_MAGNITUDE::BYTE)				return value * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		throw;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		return value / bytes_in_zetta;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		return value / bytes_in_exa;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	return value / bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	return value / bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		return value / bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	return value / bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	return value / bytes_in_kilo;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)
		{
			if (to_magnitude == BYTE_MAGNITUDE::BYTE)				return value * bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		return value * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		throw;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		return value / bytes_in_exa;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	return value / bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	return value / bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		return value / bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	return value / bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	return value / bytes_in_kilo;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)
		{
			if (to_magnitude == BYTE_MAGNITUDE::BYTE)				return value * bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		return value * bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		return value * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		throw;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	return value / bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	return value / bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		return value / bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	return value / bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	return value / bytes_in_kilo;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)
		{
			if (to_magnitude == BYTE_MAGNITUDE::BYTE)				return value * bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		return value * bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		return value * bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		return value * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	throw;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	return value / bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		return value / bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	return value / bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	return value / bytes_in_kilo;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)
		{
			if (to_magnitude == BYTE_MAGNITUDE::BYTE)				return value * bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		return value * bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		return value * bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		return value * bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	return value * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	throw;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		return value / bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	return value / bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	return value / bytes_in_kilo;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::EXA_BYTE)
		{
			if (to_magnitude == BYTE_MAGNITUDE::BYTE)				return value * bytes_in_yotta;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		return value * bytes_in_zetta;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		return value * bytes_in_exa;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		return value * bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	return value * bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	return value * bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		throw;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	return value / bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	return value / bytes_in_mega;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)
		{
			if (to_magnitude == BYTE_MAGNITUDE::BYTE)				return value * bytes_in_zetta;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		return value * bytes_in_exa;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		return value * bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		return value * bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	return value * bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	return value * bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		return value * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	throw;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	return value / bytes_in_kilo;
		}
		else if (from_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)
		{
			if (to_magnitude == BYTE_MAGNITUDE::BYTE)				return value * bytes_in_yotta;
			else if (to_magnitude == BYTE_MAGNITUDE::KILO_BYTE)		return value * bytes_in_zetta;
			else if (to_magnitude == BYTE_MAGNITUDE::MEGA_BYTE)		return value * bytes_in_exa;
			else if (to_magnitude == BYTE_MAGNITUDE::GIGA_BYTE)		return value * bytes_in_petta;
			else if (to_magnitude == BYTE_MAGNITUDE::TERRA_BYTE)	return value * bytes_in_terra;
			else if (to_magnitude == BYTE_MAGNITUDE::PETTA_BYTE)	return value * bytes_in_giga;
			else if (to_magnitude == BYTE_MAGNITUDE::EXA_BYTE)		return value * bytes_in_mega;
			else if (to_magnitude == BYTE_MAGNITUDE::ZETTA_BYTE)	return value * bytes_in_kilo;
			else if (to_magnitude == BYTE_MAGNITUDE::YOTTA_BYTE)	throw;
		}
		else return 0L;
	}
	catch (const char* msg)
	{
		Logger::log_error(msg);
		return 0L;
	}
	return 0L;
}

//