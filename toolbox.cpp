/*
 * Copyright (c) 2020 Dejan Horakovic
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 * OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

//
// Created by noxx on 6/3/19.
//

#include "toolbox.h"

using std::string;
using std::vector;

/**
 *
 * @param str
 * @param delemiter
 * @return
 */
vector<string> styl::string::split( std::string str, char delemiter )
{
    vector<std::string> split_str;
    std::string tmp = "";
    for( int i = 0; i < str.size() + 1; i++ )
    {
        if( str[i] == delemiter && tmp != "" || i == str.size())
        {
            split_str.push_back( tmp );
            tmp = "";
        }
        else if( str[i] != delemiter ) tmp += str[i];
    }
    return split_str;
}

/**
 *
 * @param str
 * @param from
 * @param to
 * @return
 */
std::string styl::string::replace( std::string str, const std::string & from, const std::string & to )
{
    size_t start_pos = 0;
    while((start_pos = str.find( from, start_pos )) != std::string::npos )
    {
        str.replace( start_pos, from.length(), to );
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

/**
 *
 * @param dir_path
 * @return
 */
vector<string> styl::fs::get_files_in_dir( std::string dir_path )
{
    vector<std::string> file_paths;
    for( auto & p: std::experimental::filesystem::directory_iterator( dir_path ))
        file_paths.push_back( p.path());

    std::sort( file_paths.begin(), file_paths.end());
    return file_paths;
}

/**
 *
 * @param dir_path
 * @return
 */
int styl::fs::get_num_files( std::string dir_path )
{
    int num_files = 0;

    for( auto & p: std::experimental::filesystem::directory_iterator( dir_path ))
        num_files++;

    return num_files;
}

/**
 *
 * @param date
 * @return
 */
time_t styl::date::stot( const std::string & date, const std::string & format )
{
    const char * time_details = date.c_str();
    time_t result = 0;
    int year = 0, month = 0, day = 0, hour = 0, min = 0, sec = 0;
    std::string num_format = styl::date::dftnf( format );

    if( sscanf( time_details, num_format.c_str(), &year, &month, &day, &hour, &min, &sec ))
    {
        struct tm breakdown = {0};
        breakdown.tm_year = year - 1900; /* years since 1900 */
        breakdown.tm_mon = month - 1;
        breakdown.tm_mday = day;
        breakdown.tm_hour = hour;
        breakdown.tm_min = min;
        breakdown.tm_sec = sec;
        breakdown.tm_isdst = 1;

        if((result = mktime( &breakdown )) == (time_t) -1 )
        {
            fprintf( stderr, "Could not convert time input to time_t\n" );
            return EXIT_FAILURE;
        }
    }

    return result;
}

/**
 *
 * @param date
 * @return
 */
std::string styl::date::ttos( const time_t & date, const std::string & format )
{
    const char * c_format = format.c_str();
    std::tm * ptm = std::localtime( &date );
    char buffer[100];
    std::strftime( buffer, 100, c_format, ptm );
    std::string oString( buffer );
    return oString;
}

/**
 *
 * @param date_format
 * @return
 */
std::string styl::date::dftnf( std::string date_format )
{
    std::string tmp = date_format;
    tmp = styl::string::replace( tmp, "%Y", "%4d" );
    tmp = styl::string::replace( tmp, "%m", "%2d" );
    tmp = styl::string::replace( tmp, "%d", "%2d" );
    tmp = styl::string::replace( tmp, "%H", "%2d" );
    tmp = styl::string::replace( tmp, "%M", "%2d" );
    tmp = styl::string::replace( tmp, "%S", "%2d" );
    return tmp;
}

time_t styl::date::add_se( const time_t & t, const int & se )
{
    struct tm * tm = localtime( &t );
    tm->tm_sec += se;
    return mktime( tm );
}

time_t styl::date::add_mi( const time_t & t, const int & mi )
{
    struct tm * tm = localtime( &t );
    tm->tm_min += mi;
    return mktime( tm );
}

time_t styl::date::add_hr( const time_t & t, const int & hr )
{
    struct tm * tm = localtime( &t );
    tm->tm_hour += hr;
    return mktime( tm );
}

time_t styl::date::add_da( const time_t & t, const int & da )
{
    struct tm * tm = localtime( &t );
    tm->tm_mday += da;
    return mktime( tm );
}

time_t styl::date::add_wk( const time_t & t, const int & wk )
{
    struct tm * tm = localtime( &t );
    tm->tm_wday += wk;
    return mktime( tm );
}

time_t styl::date::add_mo( const time_t & t, const int & mo )
{
    struct tm * tm = localtime( &t );
    tm->tm_mon += mo;
    return mktime( tm );
}

time_t styl::date::add_yr( const time_t & t, const int & yr )
{
    struct tm * tm = localtime( &t );
    tm->tm_year += yr;
    return mktime( tm );
}


double styl::date::diff_se( const time_t & end, const time_t & start )
{
    return difftime( end, start );
}

double styl::date::diff_mi( const time_t & end, const time_t & start )
{
    int s = difftime( end, start );
    return s / 60;
}

double styl::date::diff_hr( const time_t & end, const time_t & start )
{
    int s = difftime( end, start );
    return s / 3600;
}

double styl::date::diff_da( const time_t & end, const time_t & start )
{
    int s = difftime( end, start );
    return s / 86400;
}

double styl::date::diff_wk( const time_t & end, const time_t & start )
{
    int s = difftime( end, start );
    return s / 604800;
}

double styl::date::diff_mo( const time_t & end, const time_t & start )
{
    int s = difftime( end, start );
    return s / 86400; // todo
}

double styl::date::diff_yr( const time_t & end, const time_t & start )
{
    int s = difftime( end, start );
    return s / 86400; // todo
}