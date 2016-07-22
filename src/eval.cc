#include "scam.hh"
#include "scm.hh"

namespace scam {
scm eval(const scm& scm) {
    switch (scm->type) {
        case SCM::e_int:
        case SCM::e_double:
        case SCM::e_string:
        case SCM::e_symbol:
        case SCM::e_char:
        case SCM::e_nil:
        case SCM::e_t:
            // values should be copied
            return copy(scm);
        case SCM::e_quoted:
            // unquote quoted values
            return quoted_value(scm);
        case SCM::e_cons:
            // function call
            ;
    }
}
}
