#ifndef HEADER_GUARD_ASSERT_H
#define HEADER_GUARD_ASSERT_H

#include <string>

namespace scam {
#define ASSERT(x) ::scam::assert(x, "Assertion failed: " #x)

/*!
 * \brief Throw an exception if TEST is false, with the message MESSAGE.
 *
 * Throws an `std::runtime_exception`.
 */
void assert(bool test, const std::string& message);
}

#endif
