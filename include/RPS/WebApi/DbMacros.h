#ifndef RPS_WebApi_DbMacros_H
#define RPS_WebApi_DbMacros_H

#include <pqxx/pqxx>

#define GET_VALUE(field) \
object.field = row[#field].as<decltype(object.field)>();

#define GET_ARRAY(field) \
decltype(object.field) resultArray; \
auto array = row["innerArray"].as_sql_array<decltype(object.field)::value_type>(); \
object.field = decltype(object.field)(array.cbegin(), array.cend());

#endif