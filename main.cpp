#include <iostream>
#include <string>

#include "json.h"

using namespace std;

int main()
{
    std::string json_str = ANXTRI::read_json_str( "./json_files/canada.json" );
    cout << json_str << endl;

    ANXTRI::Json json_obj = ANXTRI::decode_json( json_str );
    string a = json_obj["type"];
    cout << a << endl;

    return 0;
}