#include "scam.hh"
#include "scm.hh"

namespace scam {
scm copy(scm other) {
    scm ret = std::make_shared<SCM>();
    switch (other->type) {
        case SCM::e_int:
            new (&ret->_int) int(other->_int);
            break;
        case SCM::e_double:
            new (&ret->_double) double(other->_double);
            break;
        case SCM::e_char:
            new (&ret->_char) char(other->_char);
            break;
        case SCM::e_nil:
        case SCM::e_t:
            break;
        case SCM::e_string:
        case SCM::e_symbol:
            new (&ret->_str) std::string(other->_str);
            break;
        case SCM::e_cons:
            // force exception safety
            // if copy(cdr) fails then we still correctly delete car
            ret->type = SCM::e_cons;
            new (&ret->_cons) cons_t{nullptr, nullptr};
            ret->_cons.car = copy(other->_cons.car);
            ret->_cons.cdr = copy(other->_cons.cdr);
            break;
        case SCM::e_quoted:
            new (&ret->_quoted) scm(copy(other->_quoted));
            break;
    }
    ret->type = other->type;
    return ret;
}
}
