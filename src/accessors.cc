#include "scam.hh"
#include "scm.hh"
#include "assert.hh"

namespace scam {
long int_value(const scm& scm) {
    ASSERT(is_int(scm));
    return scm->_int;
}

double double_value(const scm& scm) {
    ASSERT(is_double(scm));
    return scm->_double;
}

bool bool_value(const scm& scm) noexcept {
    return not is_nil(scm);
}

const std::string& symbol_value(const scm& scm) {
    ASSERT(is_symbol(scm));
    return scm->_str;
}

std::string& symbol_value(scm& scm) {
    ASSERT(is_symbol(scm));
    return scm->_str;
}

const std::string& string_value(const scm& scm) {
    ASSERT(is_string(scm));
    return scm->_str;
}

std::string& string_value(scm& scm) {
    ASSERT(is_string(scm));
    return scm->_str;
}

const scm& quoted_value(const scm& scm) {
    ASSERT(is_quoted(scm));
    return scm->_quoted;
}

scm& quoted_value(scm& scm) {
    ASSERT(is_quoted(scm));
    return scm->_quoted;
}

char char_value(const scm& scm) {
    ASSERT(is_char(scm));
    return scm->_char;
}

const scm& car(const scm& scm) {
    ASSERT(is_cons(scm));
    return scm->_cons.car;
}

scm& car(scm& scm) {
    ASSERT(is_cons(scm));
    return scm->_cons.car;
}

const scm& cdr(const scm& scm) {
    ASSERT(is_cons(scm));
    return scm->_cons.cdr;
}

scm& cdr(scm& scm) {
    ASSERT(is_cons(scm));
    return scm->_cons.cdr;
}
}
