#ifndef RPS_WebApi_DbMacros_H
#define RPS_WebApi_DbMacros_H

#include <pqxx/pqxx>

#define GET_VALUE(field) \
object.field = row[#field].as<decltype(object.field)>();

#define GET_ARRAY(field) \
auto array = row["innerArray"].as_sql_array<typename decltype(object.field)::value_type>(); \
object.field = decltype(object.field)(array.cbegin(), array.cend());

#endif