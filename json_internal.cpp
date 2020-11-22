//
// Created by noxx on 4/6/20.
//

#include "json_internal.h"

using ANXTRI::string::split;
using ANXTRI::string::replace;

ANXTRI::JsonNode::JsonNode()
{
    m_parent = nullptr;
    set_type( T_NULL );
}

ANXTRI::JsonNode::JsonNode( JsonNode * parent, const type & type )
{
    m_parent    = parent;
    m_type      = type;
}

ANXTRI::JsonNode::JsonNode( const JsonNode & other )
{
    m_type      = other.m_type;
    m_parent    = other.m_parent;
    m_number    = other.m_number;
    m_string    = other.m_string;
    m_bool      = other.m_bool;
    m_array     = other.m_array;
    m_object    = other.m_object;
}

ANXTRI::JsonNode::~JsonNode()
{

}

void ANXTRI::JsonNode::set_type( const type & type )
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

const ANXTRI::type & ANXTRI::JsonNode::get_type()
{
    return m_type;
}

// double
ANXTRI::JsonNode & ANXTRI::JsonNode::operator=( const double & value )
{
    m_type = T_NUMBER;
    m_number = value;
    return *this;
}

ANXTRI::JsonNode::operator double()
{
    return m_number;
}

// string
ANXTRI::JsonNode & ANXTRI::JsonNode::operator=( const std::string & value )
{
    m_type = T_STRING;
    m_string = value;
    return *this;
}

ANXTRI::JsonNode & ANXTRI::JsonNode::operator=( const char * value )
{
    m_type = T_STRING;
    m_string = value;
    return *this;
}

ANXTRI::JsonNode::operator std::string()
{
    return m_string;
}

// bool
ANXTRI::JsonNode & ANXTRI::JsonNode::operator=( const bool & value )
{
    m_type = T_BOOLEAN;
    m_bool = value;
    return *this;
}
ANXTRI::JsonNode::operator bool()
{
    return m_bool;
}

ANXTRI::JsonNode * ANXTRI::JsonNode::get_parent()
{
    return m_parent;
}

ANXTRI::JsonNode & ANXTRI::JsonNode::operator[]( const std::string & index )
{
    if( m_object.find( index ) == m_object.end() )
    {
        static JsonNode null_obj = JsonNode();
        m_object[index] = null_obj;
    }
    return m_object[index];
}

ANXTRI::JsonNode & ANXTRI::JsonNode::operator[]( const char * index )
{
    if( m_object.find( index ) == m_object.end() )
    {
        static JsonNode null_obj = JsonNode();
        m_object[index] = null_obj;
    }
    return m_object[index];
}

ANXTRI::JsonNode & ANXTRI::JsonNode::operator[]( const int & index )
{
    if( m_array.size() < index || index < 0 )
    {
        static JsonNode null_obj = JsonNode();
        m_array[index] = null_obj;
    }
    return m_array[index];
}

void ANXTRI::JsonNode::push( const ANXTRI::JsonNode & node )
{
    m_array.push_back( node );
}

void ANXTRI::JsonNode::push( const double & value )
{
    m_array.push_back( JsonNode( this, T_NUMBER ));
    m_array[m_array.size()-1] = value;
}

void ANXTRI::JsonNode::push( const std::string & value )
{
    m_array.push_back( JsonNode( this, T_STRING ));
    m_array[m_array.size()-1] = value;
}

void ANXTRI::JsonNode::push( const bool & value )
{
    m_array.push_back( JsonNode( this, T_BOOLEAN ));
    m_array[m_array.size()-1] = value;
}

void ANXTRI::JsonNode::push()
{
    m_array.push_back( JsonNode( this, T_NULL ));
}

ANXTRI::JsonNode & ANXTRI::JsonNode::get_last_arr_elem()
{
    return m_array[m_array.size()-1];
}
