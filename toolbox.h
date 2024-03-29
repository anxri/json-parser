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

#ifndef ANXRI_TOOLBOX_H
#define ANXRI_TOOLBOX_H

#include <string>
#include <vector>
#include <fstream>
#include <experimental/filesystem>
#include <algorithm>

namespace ANXRI
{

    namespace string
    {
        std::vector<std::string> split( std::string str, char delemiter );

        std::string replace( std::string str, const std::string & from, const std::string & to );
        
        bool is_num( const std::string str );
    }

    namespace fs
    {
        std::vector<std::string> get_files_in_dir( std::string dir_path );

        int get_num_files( std::string dir_path );
    }

    namespace date
    {
        // string to time_t
        time_t stot( const std::string & date, const std::string & format );

        // time_t to string
        std::string ttos( const time_t & date, const std::string & format );

        // convert date format to num format
        std::string dftnf( std::string date_format );

        // manipulations
        time_t add_se( const time_t & t, const int & se );

        time_t add_mi( const time_t & t, const int & mi );

        time_t add_hr( const time_t & t, const int & hr );

        time_t add_da( const time_t & t, const int & da );

        time_t add_wk( const time_t & t, const int & wk );

        time_t add_mo( const time_t & t, const int & mo );

        time_t add_yr( const time_t & t, const int & yr );

        double diff_se( const time_t & end, const time_t & start );

        double diff_mi( const time_t & end, const time_t & start );

        double diff_hr( const time_t & end, const time_t & start );

        double diff_da( const time_t & end, const time_t & start );

        double diff_wk( const time_t & end, const time_t & start );

        double diff_mo( const time_t & end, const time_t & start );

        double diff_yr( const time_t & end, const time_t & start );
    }
}

#endif
