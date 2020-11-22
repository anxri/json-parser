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

#include <iostream>
#include <fstream>

#include "json.h"

using std::string;
using std::vector;
using std::ifstream;

using ANXTRI::string::replace;
using ANXTRI::string::split;

ANXTRI::Json::Json()
{
}


ANXTRI::Json::~Json()
{

}

ANXTRI::Json::Json( const ANXTRI::Json & other )
{
    m_type      = other.m_type;
    m_parent    = other.m_parent;
    m_number    = other.m_number;
    m_string    = other.m_string;
    m_bool      = other.m_bool;
    m_array     = other.m_array;
    m_object    = other.m_object;
}

/**
 * @brief
 * @param value
 * @return
 */
ANXTRI::Json & ANXTRI::Json::operator=( const double & value )
{
    m_number = value;
    return *this;
}

/**
 * @brief
 * @param value
 * @return
 */
ANXTRI::Json & ANXTRI::Json::operator=( const std::string & value )
{
    m_string = value;
    return *this;
}

/**
 * @brief
 * @param value
 * @return
 */
ANXTRI::Json & ANXTRI::Json::operator=( const bool & value )
{
    m_bool = value;
    return *this;
}

/**
 * @brief
 * @param obj
 * @return
 */
ANXTRI::Json & ANXTRI::Json::operator=( ANXTRI::JsonNode other )
{
    m_type      = other.m_type;
    m_parent    = other.m_parent;
    m_number    = other.m_number;
    m_string    = other.m_string;
    m_bool      = other.m_bool;
    m_array     = other.m_array;
    m_object    = other.m_object;
    return *this;
}

/**
 * @brief
 * @param index
 * @return
 */
ANXTRI::JsonNode & ANXTRI::Json::operator[]( const std::string & index )
{
    if( m_object.find( index ) == m_object.end() )
    {
        static JsonNode null_obj = JsonNode();
        m_object[index] = null_obj;
    }
    return m_object[index];
}

/**
 * @brief
 * @param index
 * @return
 */
ANXTRI::JsonNode & ANXTRI::Json::operator[]( const char * index )
{
    if( m_object.find( index ) == m_object.end() )
    {
        static JsonNode null_obj = JsonNode();
        m_object[index] = null_obj;
    }
    return m_object[index];
}

ANXTRI::JsonNode & ANXTRI::Json::operator[]( const unsigned long & index )
{
    if( m_array.size() <= index || index <= 0 )
    {
        static JsonNode null_obj = JsonNode();
        m_array[index] = null_obj;
    }
    return m_array[index];
}

/**
 * @brief read json file without space and \n
 * @param path
 * @return
 */
std::string ANXTRI::read_json_str( std::string path )
{
    std::string json_str;
    ifstream read_history( path );

    char c;
    bool inside_data_str = false;

    if( read_history )
    {
        while( !read_history.eof() )
        {
            read_history.get( c );

            if( !inside_data_str && c == '"' )
            {
                inside_data_str = true;
            }
            else if( inside_data_str && c == '"' )
            {
                inside_data_str = false;
            }

            if( !inside_data_str && ( c == ' ' || c == '\n' ))
            {
                // do nothing
            }
            else
            {
                json_str += c;
            }
        }
    }
    return ANXTRI::string::replace(json_str, "\r", "");
}

ANXTRI::Json ANXTRI::read_json_obj( std::string path )
{

}

void ANXTRI::write_json_str( std::string path, std::string str )
{

}

void ANXTRI::write_json_obj( std::string path, ANXTRI::Json obj )
{

}

/**
 * @brief converts single obj to string
 * @param obj
 * @return
 */
std::string ANXTRI::encode_json( ANXTRI::JsonNode & obj )
{
    std::string encoded_string              = "";
    std::string comma                       = "";

    JsonNode & json_node_pointer            = obj;
    type current_type                       = json_node_pointer.get_type();

    unsigned int iteration_count            = 0;        // counts finished iterations
    unsigned int object_count               = 1;        // counts nested objects
    std::map<unsigned int, ANXTRI::JsonNode>  obj_stack;  //
    std::map<unsigned int, std::string>     str_stack;  //

    /*
     * set first char
     */
    if( current_type == T_OBJECT )
        encoded_string += "{";

    else if( current_type == T_ARRAY )
        encoded_string += "[";

    else if( current_type == T_STRING )
        encoded_string += "\"";


    /*
     * loop as long childs existing
     */
    int i = 0;
    do
    {
        /*
         * Object
         */
        if( current_type == T_OBJECT )
        {
            for( auto it = json_node_pointer.m_object.begin(); it != json_node_pointer.m_object.end(); ++it )
            {
                auto next_obj = std::next( it, 1 );

                if( next_obj == json_node_pointer.m_object.end() )
                    comma = "";
                else
                    comma = ",";


                if( it->second.get_type() == T_NULL )
                {
                    encoded_string += "\"" + it->first + "\":null" + comma;
                }

                else if( it->second.get_type() == T_BOOLEAN )
                {
                    if( it->second.m_bool == true )
                        encoded_string += "\"" + it->first + "\":true" + comma;
                    else
                        encoded_string += "\"" + it->first + "\":false" + comma;
                }

                else if( it->second.get_type() == T_NUMBER )
                {
                    encoded_string += "\"" + it->first + "\":" + std::to_string( it->second.m_number ) + comma;
                }

                else if( it->second.get_type() == T_STRING )
                {
                    encoded_string += "\"" + it->first + "\":\"" + it->second.m_string + "\"" + comma;
                }

                else if( it->second.get_type() == T_OBJECT )
                {
                    encoded_string += "\"" + it->first + "\":{ADR_" + std::to_string( object_count ) + "}" + comma;
                    obj_stack[object_count++] = it->second;
                }

                else if( it->second.get_type() == T_ARRAY )
                {
                    encoded_string += "\"" + it->first + "\":[ADR_" + std::to_string( object_count ) + "]" + comma;
                    obj_stack[object_count++] = it->second;
                }
            }
        }

        /*
         * Array
         */
        else if( current_type == T_ARRAY )
        {
            for( auto it = json_node_pointer.m_array.begin(); it != json_node_pointer.m_array.end(); ++it )
            {
                auto next_obj = std::next( it, 1 );

                if( next_obj == json_node_pointer.m_array.end() )
                    comma = "";
                else
                    comma = ",";


                if( it->get_type() == T_NULL ) // null
                {
                    encoded_string += "null" + comma;
                }

                else if( it->get_type() == T_BOOLEAN ) // bool
                {
                    if( it->m_bool == true )
                        encoded_string += "true" + comma;

                    else
                        encoded_string += "false" + comma;
                }

                else if( it->get_type() == T_NUMBER ) // number
                {
                    encoded_string += std::to_string( it->m_number ) + comma;
                }

                else if( it->get_type() == T_STRING ) // string
                {
                    encoded_string += "\"" + it->m_string + "\"" + comma;
                }

                else if( it->get_type() == T_OBJECT ) // object
                {
                    encoded_string += "{ADR_" + std::to_string( object_count ) + "}" + comma;
                    obj_stack[object_count++] = *it;
                }

                else if( it->get_type() == T_ARRAY ) // array
                {
                    encoded_string += "[ADR_" + std::to_string( object_count ) + "]" + comma;
                    obj_stack[object_count++] = *it;
                }
            }
        }

        str_stack[iteration_count++] = encoded_string;
        encoded_string = "";

        if( obj_stack.size() > 0 )
        {
            json_node_pointer = obj_stack.begin()->second;
            obj_stack.erase( obj_stack.begin() );
            current_type = json_node_pointer.get_type();
        }

    } while ( iteration_count < object_count );

    encoded_string = str_stack[0];

    for( unsigned int i = 0; i < object_count; i++ )
    {
        std::string placeholder = "ADR_" + std::to_string( i );
        std::string str = str_stack[i];
        encoded_string = ANXTRI::string::replace( encoded_string, placeholder, str );
    }

    /*
     * set last char
     */
    if( current_type == T_OBJECT )
        encoded_string += "}";

    else if( current_type == T_ARRAY )
        encoded_string += "]";

    else if( current_type == T_STRING )
        encoded_string += "\"";

    return encoded_string;
}

/**
 * @brief
 * @param json_str
 * @return
 */
ANXTRI::Json ANXTRI::decode_json( const std::string & json_str )
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    // set root type
    static Json root = Json();
    JsonNode * json_node_pointer = &root;

    if( json_str[0] == '\"' && json_str[json_str.size()-1] == '\"' ) // string
    {
        std::string str_val = ANXTRI::string::replace( json_str, "\"", "" );
        root = str_val;
        return root;
    }

    else if( json_str == "true" ) // bool
    {
        root = true;
        return root;
    }

    else if( json_str == "false" ) // bool
    {
        root = false;
        return root;
    }

    else if( ANXTRI::string::is_num( json_str )) // number
    {
        root = stod( json_str );
        return root;
    }

    else if( json_str[0] == '{' && json_str[json_str.size() - 1] == '}' ) // object
    {
        json_node_pointer->set_type( T_OBJECT );
    }

    else if( json_str[0] == '[' && json_str[json_str.size() - 1] == ']' ) // array
    {
        json_node_pointer->set_type( T_ARRAY );
    }

    else // null
    {
        root.set_type( T_NULL );
        return root;
    }

    int last_entry      = 1;
    std::string tmp_str = "";

    enum action {
        NONE,       // do nothing
        CRT_OBJ,    // create object
        CRT_ARR,    // create array
        JMP_PRNT    // jump to parent
    };

    action current_action;
    vector<std::string> key_value;

    for( int i = 1; i < json_str.size(); i++ )
    {
        if( json_str[i] == '{' ||
            json_str[i] == '[' ||
            json_str[i] == ']' ||
            json_str[i] == '}' ||
            json_str[i] == ',' )
        {
            tmp_str = json_str.substr( last_entry, i - last_entry ); // substr
        }

        switch ( json_str[i] )
        {
            case '{':   current_action = CRT_OBJ; break;
            case '[':   current_action = CRT_ARR; break;
            case ']':   current_action = JMP_PRNT; break;
            case '}':   current_action = JMP_PRNT; break;
            default:    current_action = NONE;
        }

        if( tmp_str.size() > 0 && ( json_str[i] == ',' || current_action == JMP_PRNT ))
        {
            key_value = split( tmp_str, ':' );

            /*
             * check object pattern
             */
            if( json_node_pointer->get_type() == T_OBJECT )
            {
                if( key_value[0][0] == '\"' && key_value[0][key_value[0].size()-1] == '\"' )
                {
                    if( key_value[1][0] == '\"' && key_value[1][key_value[1].size()-1] == '\"' ) // string
                    {
                        key_value[0] = replace( key_value[0], "\"", "" );
                        key_value[1] = replace( key_value[1], "\"", "" );
                        (*json_node_pointer)[key_value[0]] = key_value[1];
                    }

                    else if( ANXTRI::string::is_num( key_value[1] )) // number
                    {
                        key_value[0] = replace( key_value[0], "\"", "" );
                        (*json_node_pointer)[key_value[0]] = stod( key_value[1] );
                    }

                    else if( key_value[1] == "true" ) // boolean
                    {
                        key_value[0] = replace( key_value[0], "\"", "" );
                        (*json_node_pointer)[key_value[0]] = true;
                    }

                    else if( key_value[1] == "false")
                    {
                        key_value[0] = replace( key_value[0], "\"", "" );
                        (*json_node_pointer)[key_value[0]] = false;
                    }

                    else if( key_value[1] == "null" ) // null
                    {
                        key_value[0] = replace( key_value[0], "\"", "" );
                        (*json_node_pointer)[key_value[0]].set_type( T_NULL );
                    }
                }
            }

            if( json_node_pointer->get_type() == T_ARRAY )
            {
                /*
                 * check array pattern
                 */
                if( key_value[0][0] == '\"' && key_value[0][key_value[0].size()-1] == '\"' ) // string
                {
                    key_value[0] = replace( key_value[0], "\"", "" );
                    (*json_node_pointer).push( key_value[0] );
                }

                else if( ANXTRI::string::is_num( key_value[0] )) // number
                {
                    (*json_node_pointer).push( stod( key_value[0] ));
                }

                else if( key_value[0] == "true" ) // boolean
                {
                    (*json_node_pointer).push( true );
                }

                else if( key_value[0] == "false" )
                {
                    (*json_node_pointer).push( false );
                }

                else if( key_value[0] == "null" ) // null
                {
                    (*json_node_pointer).push();
                }
            }
        }

        /*
         * create obj/arr
         * jump to parent
         */
        if( current_action == CRT_OBJ && (*json_node_pointer).get_type() == T_OBJECT ) // object in object
        {
            key_value = split( tmp_str, ':' );
            key_value[0] = replace( key_value[0], "\"", "" );
            (*json_node_pointer)[key_value[0]] = JsonNode( json_node_pointer, T_OBJECT );
            json_node_pointer = &(*json_node_pointer)[key_value[0]];
        }

        else if( current_action == CRT_OBJ && (*json_node_pointer).get_type() == T_ARRAY ) // object in array
        {
            (*json_node_pointer).push( JsonNode( json_node_pointer, T_OBJECT ));
            json_node_pointer = &json_node_pointer->get_last_arr_elem();
        }

        else if( current_action == CRT_ARR && (*json_node_pointer).get_type() == T_ARRAY ) // array in array
        {
            (*json_node_pointer).push( JsonNode( json_node_pointer, T_ARRAY ));
            json_node_pointer = &json_node_pointer->get_last_arr_elem();
        }

        else if( current_action == CRT_ARR && (*json_node_pointer).get_type() == T_OBJECT ) // array in object
        {
            key_value = split( tmp_str, ':' );
            key_value[0] = replace( key_value[0], "\"", "" );
            (*json_node_pointer)[key_value[0]] = JsonNode( json_node_pointer, T_ARRAY );
            json_node_pointer = &(*json_node_pointer)[key_value[0]];
        }

        else if( current_action == JMP_PRNT && json_node_pointer->m_parent != NULL )
        {
            json_node_pointer = json_node_pointer->get_parent();
        }


        if( json_str[i] == '{' ||
            json_str[i] == '[' ||
            json_str[i] == ']' ||
            json_str[i] == '}' ||
            json_str[i] == ',' )
        {
            last_entry = i + 1;
        }
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

    return root;
}