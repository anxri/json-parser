//
// Created by noxx on 6/3/19.
//

#ifndef QUAGGA_TOOLBOX_H
#define QUAGGA_TOOLBOX_H

#include <string>
#include <vector>
#include <fstream>
#include <experimental/filesystem>
#include <algorithm>

namespace ANXTRI
{

    namespace string
    {
        std::vector<std::string> split( std::string str, char delemiter );

        std::string replace( std::string str, const std::string & from, const std::string & to );

        bool is_num( const std::string & str );
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
#endif //QUAGGA_TOOLBOX_H
