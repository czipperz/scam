#include "scam.hh"
#include "scm.hh"

namespace scam {
scm nil() {
    scm scm = std::make_shared<SCM>();
    scm->type = SCM::e_nil;
    return scm;
}

scm t() {
    scm scm = std::make_shared<SCM>();
    scm->type = SCM::e_t;
    return scm;
}
}
