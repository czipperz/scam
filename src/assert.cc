#include "assert.hh"
#include <stdexcept>

namespace scam {
void assert(bool test, const std::string& message) {
    if (not test) {
        throw std::logic_error(message);
    }
}
}
