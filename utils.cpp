#include "utils.h"
#include <ctime>
#include <sstream>
#include <iomanip>

std::string getCurrentDate() {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    std::stringstream ss;
    ss << std::put_time(now, "%d/%m/%Y");
    return ss.str();
}