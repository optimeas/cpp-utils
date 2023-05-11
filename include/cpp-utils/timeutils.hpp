#pragma once

#include <string>

namespace cu
{

std::string getCurrentTimestampUtcIso8601();
std::string getCurrentTimestampUtcString(bool withMilliSeconds = false);

}
