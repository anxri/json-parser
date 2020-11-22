//
// Created by noxx on 4/6/20.
//

#ifndef ANXTRI_CPP_LIB_JSON_INTERNAL_H
#define ANXTRI_CPP_LIB_JSON_INTERNAL_H

#include <string>
#include <vector>
#include <map>

#include "toolbox.h"

namespace ANXTRI
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

#endif //ANXTRI_CPP_LIB_JSON_INTERNAL_H
