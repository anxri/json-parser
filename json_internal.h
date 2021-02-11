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
// Created by noxx on 4/6/20.
//

#ifndef ANXRI_CPP_LIB_JSON_INTERNAL_H
#define ANXRI_CPP_LIB_JSON_INTERNAL_H

#include <string>
#include <vector>
#include <map>

#include "toolbox.h"

namespace ANXRI
{
    enum type
    {
        T_NUMBER,
        T_STRING,
        T_BOOLEAN,
        T_ARRAY,
        T_OBJECT,
        T_NULL
    };

    class JsonNode
    {
        public:
            type m_type;

            JsonNode *                          m_parent;

            static const int                    m_null = 0;
            double                              m_number;
            std::string                         m_string;
            bool                                m_bool;
            std::vector<JsonNode>               m_array;
            std::map<std::string, JsonNode>     m_object;

            JsonNode * get_parent();

            void set_type( const type & type );
            const type & get_type();


        public:
            JsonNode();
            JsonNode( JsonNode * parent, const type & type );
            JsonNode( const JsonNode & other );
            ~JsonNode();

            // number
            JsonNode & operator=( const double & value );
            operator double();

            // string
            JsonNode & operator=( const std::string & value );
            JsonNode & operator=( const char * value );
            operator std::string();

            // boolean
            JsonNode & operator=( const bool & value );
            operator bool();

            JsonNode & operator[]( const int & value );
            JsonNode & operator[]( const std::string & value );
            JsonNode & operator[]( const char * value );

            // object

            // array
            void push( const JsonNode & node );
            void push( const double & value );
            void push( const std::string & value );
            void push( const bool & value );
            void push();

            /*
             * todo
             * - size()
             * - delete(i)
             * - empty()
             * - swap(i,j)
             *
             */
            
            JsonNode & get_last_arr_elem();
    };
}

#endif //ANXRI_CPP_LIB_JSON_INTERNAL_H
