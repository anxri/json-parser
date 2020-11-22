//
// Created by noxx on 3/18/20.
//

#ifndef ANXTRI_CPP_LIB_JSON_H
#define ANXTRI_CPP_LIB_JSON_H

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <regex>
#include <chrono>
#include <cstdlib>

#include "toolbox.h"
#include "json_internal.h"

namespace ANXTRI
{
    class Json : public JsonNode
    {
        public:

            Json();
            Json( const Json & other );
            ~Json();

            Json & operator=( const double & value );
            Json & operator=( const std::string & value );
            Json & operator=( const bool & value );

            Json & operator=( JsonNode obj );

            JsonNode & operator[]( const unsigned long & value );
            JsonNode & operator[]( const std::string & value );
            JsonNode & operator[]( const char * value );
        };


        // read
        std::string read_json_str( std::string path );
        Json read_json_obj( std::string path );


        // write
        void write_json_str( std::string path, std::string str );
        void write_json_obj( std::string path, Json obj );


        // encode / decode
        std::string encode_json( JsonNode & obj );
        Json decode_json( const std::string & json_str );
}

#endif //ANXTRI_CPP_LIB_JSON_H
