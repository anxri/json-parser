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

#include "json_internal.h"


using ANXRI::string::split;
using ANXRI::string::replace;

ANXRI::JsonNode::JsonNode()
{
    m_parent = nullptr;
    set_type( T_NULL );
}

ANXRI::JsonNode::JsonNode( JsonNode * parent, const type & type )
{
    m_parent    = parent;
    m_type      = type;
}

ANXRI::JsonNode::JsonNode( const JsonNode & other )
{
    m_type      = other.m_type;
    m_parent    = other.m_parent;
    m_number    = other.m_number;
    m_string    = other.m_string;
    m_bool      = other.m_bool;
    m_array     = other.m_array;
    m_object    = other.m_object;
}

ANXRI::JsonNode::~JsonNode()
{

}

void ANXRI::JsonNode::set_type( const type & type )
{
    m_type = type;

    if( type == T_NULL )
    {
        m_type      = T_NULL;
        m_bool      = 0;
        m_number    = 0;
        m_string    = "";
        m_array.clear();
        m_object.clear();
    }
}

const ANXRI::type & ANXRI::JsonNode::get_type()
{
    return m_type;
}

// double
ANXRI::JsonNode & ANXRI::JsonNode::operator=( const double & value )
{
    m_type = T_NUMBER;
    m_number = value;
    return *this;
}

ANXRI::JsonNode::operator double()
{
    return m_number;
}

// string
ANXRI::JsonNode & ANXRI::JsonNode::operator=( const std::string & value )
{
    m_type = T_STRING;
    m_string = value;
    return *this;
}

ANXRI::JsonNode & ANXRI::JsonNode::operator=( const char * value )
{
    m_type = T_STRING;
    m_string = value;
    return *this;
}

ANXRI::JsonNode::operator std::string()
{
    return m_string;
}

// bool
ANXRI::JsonNode & ANXRI::JsonNode::operator=( const bool & value )
{
    m_type = T_BOOLEAN;
    m_bool = value;
    return *this;
}
ANXRI::JsonNode::operator bool()
{
    return m_bool;
}

ANXRI::JsonNode * ANXRI::JsonNode::get_parent()
{
    return m_parent;
}

ANXRI::JsonNode & ANXRI::JsonNode::operator[]( const std::string & index )
{
    if( m_object.find( index ) == m_object.end() )
    {
        static JsonNode null_obj = JsonNode();
        m_object[index] = null_obj;
    }
    return m_object[index];
}

ANXRI::JsonNode & ANXRI::JsonNode::operator[]( const char * index )
{
    if( m_object.find( index ) == m_object.end() )
    {
        static JsonNode null_obj = JsonNode();
        m_object[index] = null_obj;
    }
    return m_object[index];
}

ANXRI::JsonNode & ANXRI::JsonNode::operator[]( const int & index )
{
    if( m_array.size() < index || index < 0 )
    {
        static JsonNode null_obj = JsonNode();
        m_array[index] = null_obj;
    }
    return m_array[index];
}

void ANXRI::JsonNode::push( const ANXRI::JsonNode & node )
{
    m_array.push_back( node );
}

void ANXRI::JsonNode::push( const double & value )
{
    m_array.push_back( JsonNode( this, T_NUMBER ));
    m_array[m_array.size()-1] = value;
}

void ANXRI::JsonNode::push( const std::string & value )
{
    m_array.push_back( JsonNode( this, T_STRING ));
    m_array[m_array.size()-1] = value;
}

void ANXRI::JsonNode::push( const bool & value )
{
    m_array.push_back( JsonNode( this, T_BOOLEAN ));
    m_array[m_array.size()-1] = value;
}

void ANXRI::JsonNode::push()
{
    m_array.push_back( JsonNode( this, T_NULL ));
}

ANXRI::JsonNode & ANXRI::JsonNode::get_last_arr_elem()
{
    return m_array[m_array.size()-1];
}
