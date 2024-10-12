#ifndef RPS_WebApi_DbMacros_H
#define RPS_WebApi_DbMacros_H

#include <pqxx/pqxx>

#define GET_VALUE(field) \
object->field = row[#field].as<decltype(object->field)>()

#define GET_ENUM(field) \
FromString(object->field, row[#field].as<std::string>())

#endif
