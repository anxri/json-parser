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
