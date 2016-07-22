#ifndef HEADER_GUARD_SCM_H
#define HEADER_GUARD_SCM_H

#include "scam.hh"

namespace scam {
struct cons_t {
    scm car, cdr;
};

struct SCM {
    enum type {
        e_int, e_double, e_char, e_nil, e_t,
        e_string, e_symbol, e_cons, e_quoted,
    } type;
    union {
        long _int;
        double _double;
        char _char;
        /// used to represent e_string and e_symbol
        std::string _str;
        cons_t _cons;
        scm _quoted;
    };

    SCM();
    ~SCM();
};

extern std::vector<defun_base> defun_list;
extern std::vector<std::pair<std::string, scm> > var_list;
}

#endif
