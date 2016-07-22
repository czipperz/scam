#include "scam.hh"
#include "scm.hh"
#include <cstring>

namespace scam {
static std::string escape_string(std::string string) {
    for (size_t index = 0; index != string.size(); ++index) {
        if (string[index] == '"' or string[index] == '\\') {
            string.insert(string.begin() + index, '\\');
            ++index;
        }
    }
    string.insert(string.begin(), '"');
    string.insert(string.end(), '"');
    return string;
}

static std::string escape_char(char ch) {
    std::string result;
    result += '?';
    if (ch >= u8"a"[0] and ch <= u8"z"[0] or
        ch >= u8"0"[0] and ch <= u8"9"[0] or
        std::strchr("!@#$%^&*-_=+/?,<.>~|", ch)) {
    } else {
        result += '\\';
    }
    result += ch;
    return result;
}

std::string show(const scm& scm) {
    switch (scm->type) {
        case SCM::e_int:
            return std::to_string(scm->_int);
        case SCM::e_double:
            return std::to_string(scm->_double);
        case SCM::e_nil:
            return "nil";
        case SCM::e_t:
            return "t";
        case SCM::e_char:
            return escape_char(scm->_char);
        case SCM::e_cons: {
            std::string result;
            result += '(';
            if (is_list(scm)) {
                result += show(car(scm));
                for (scam::scm rec = cdr(scm); not is_nil(rec);
                     rec = cdr(rec)) {
                    result += ' ';
                    result += show(car(rec));
                }
            } else {
                scam::scm rec = scm;
                result += show(car(rec));
                result += " . ";
                result += show(cdr(rec));
            }
            result += ')';
            return result;
        }
        case SCM::e_string:
            return escape_string(scm->_str);
        case SCM::e_symbol:
            return scm->_str;
        case SCM::e_quoted:
            return '\'' + show(scm->_quoted);
    }
}

std::string show_function_call(const std::string& name,
                               const std::vector<scm>& args) {
    std::string result = "(";
    result += name;
    if (not args.empty()) {
        result += ' ';
        result += show(*args.begin());
        for (auto i = ++args.begin(); i != args.end(); ++i) {
            result += ' ';
            result += show(*i);
        }
    }
    result += ")";
    return result;
}
}
