#include "scam.hh"
#include "scm.hh"
#include <locale>

#include "assert.hh"

namespace scam {
SCM::SCM()
    : type(e_nil) {}

SCM::~SCM() {
    switch (type) {
        case e_string:
        case e_symbol:
            using std::string;
            _str.~string();
            break;
        case e_cons:
            _cons.car.~scm();
            _cons.cdr.~scm();
            break;
        case e_quoted:
            _quoted.~scm();
            break;
        default:
            break;
    }
}

std::vector<defun_base> defun_list;
std::vector<std::pair<std::string, scm> > var_list;
}
