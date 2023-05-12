#pragma once

#include <string>

namespace cu
{

std::string getCurrentTimestampUtcIso8601(bool withNanoSeconds = false);
std::string getCurrentTimestampUtcFilename(bool withMilliSeconds = false);

}
