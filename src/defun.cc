#include "scam.hh"
#include "scm.hh"
#include "assert.hh"

namespace scam {
defun_base::defun_base(scm (*definition)(const std::vector<scm>&),
                       std::string name,
                       std::string documentation,
                       size_t required_args, size_t optional_args,
                       bool rest_args, bool eval_args)
    : documentation(std::move(documentation))
    , name(std::move(name))
    , required_args(required_args)
    , optional_args(optional_args)
    , rest_args(rest_args)
    , eval_args(eval_args)
    , definition(definition) {}

scm defun_base::call_handler(const std::vector<scm>& args) {
    assert(args.size() >= required_args,
           "Not enough arguments given to function call:\n" + name +
               " requires at least " + std::to_string(required_args) +
               " arguments.\nContext:\n" +
               show_function_call(name, args));
    return definition(args);
}

static_defun::static_defun(defun_base db) {
    defun(std::move(db));
}

void defun(defun_base db) {
    defun_list.push_back(std::move(db));
}

DEFUN(For, "or", "", 0, 0, true, false)
    (const std::vector<scm>& args) {
    scm result = nil();

    return result;
}
}
