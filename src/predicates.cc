#include "scam.hh"
#include "scm.hh"

namespace scam {
bool is_int(const scm& scm) noexcept {
    return scm->type == SCM::e_int;
}

bool is_double(const scm& scm) noexcept {
    return scm->type == SCM::e_double;
}

bool is_nil(const scm& scm) noexcept {
    return scm->type == SCM::e_nil;
}

bool is_t(const scm& scm) noexcept {
    return scm->type == SCM::e_t;
}

bool is_string(const scm& scm) noexcept {
    return scm->type == SCM::e_string;
}

bool is_symbol(const scm& scm) noexcept {
    return scm->type == SCM::e_symbol;
}

bool is_cons(const scm& scm) noexcept {
    return scm->type == SCM::e_cons;
}

bool is_quoted(const scm& scm) noexcept {
    return scm->type == SCM::e_quoted;
}

bool is_char(const scm& scm) noexcept {
    return scm->type == SCM::e_char;
}

bool is_list(const scm& scm) noexcept {
    scam::scm rec = scm;
    while (true) {
        if (is_nil(rec)) {
            return true;
        } else if (is_cons(rec)) {
            rec = cdr(rec);
        } else {
            return false;
        }
    }
}
}
