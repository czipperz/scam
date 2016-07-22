#include "scam.hh"
#include "scm.hh"

namespace scam {
scm wrap_int(long v) {
    scm scm = std::make_shared<SCM>();
    new (&scm->_int) long(v);
    scm->type = SCM::e_int;
    return scm;
}

scm wrap_double(double v) {
    scm scm = std::make_shared<SCM>();
    new (&scm->_double) double(v);
    scm->type = SCM::e_double;
    return scm;
}

scm wrap_string(std::string v) {
    scm scm = std::make_shared<SCM>();
    new (&scm->_str) std::string(v);
    scm->type = SCM::e_string;
    return scm;
}

scm wrap_symbol(std::string v) {
    scm scm = std::make_shared<SCM>();
    new (&scm->_str) std::string(v);
    scm->type = SCM::e_symbol;
    return scm;
}

scm cons(scm car, scm cdr) {
    scm scm = std::make_shared<SCM>();
    new (&scm->_cons) cons_t{car, cdr};
    scm->type = SCM::e_cons;
    return scm;
}

scm wrap_char(char v) {
    scm scm = std::make_shared<SCM>();
    new (&scm->_char) char(v);
    scm->type = SCM::e_char;
    return scm;
}

scm wrap(long i) {
    return wrap_int(i);
}

scm wrap(double d) {
    return wrap_double(d);
}

scm wrap(bool is_t) {
    if (is_t)
        return t();
    return nil();
}

scm wrap(std::string string) {
    return wrap_string(std::move(string));
}
}
