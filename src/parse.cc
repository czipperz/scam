#include "scam.hh"
#include "scm.hh"
#include "assert.hh"
#include <algorithm>
#include <cstring>
#include <cmath>

namespace scam {
static std::string
parse_string(const char*& str, std::size_t len_hint) {
    std::string string;
    string.reserve(len_hint);
    ASSERT(str[0] == u8"\""[0]);
    ++str;
    while (*str) {
        if (*str == u8"\\"[0]) {
            scam::assert(str[1],
                         u8"Backslash found at end of buffer");
            if (str[1] == u8"\\"[0]) {
                string += u8"\\"[0];
            } else if (str[1] >= u8"a"[0] and str[1] <= u8"z"[0]) {
                // control keys
                string += str[1] + u8"\a"[0] - u8"a"[0];
            } else {
                scam::assert(false,
                             std::string(u8"Backslash escape "
                                         u8"unrecognized: \\") +
                                 str[1]);
            }
            str += 2;
        } else if (*str == u8"\""[0]) {
            ++str;
            break;
        } else {
            string += *str;
            ++str;
        }
    }
    ASSERT(str[-1] == u8"\""[0]);
    return string;
}

static std::string parse_symbol(const char*& str, std::size_t len) {
    std::string string;
    string.reserve(len);
    while (*str) {
        if (*str == u8"\\"[0]) {
            scam::assert(str[1],
                         u8"Quote has backslash at end of buffer");
            string += str[0];
            string += str[1];
            str += 2;
            continue;
        } else if (*str == u8"["[0] or *str == u8"{"[0] or
                   *str == u8"("[0] or *str == u8"]"[0] or
                   *str == u8"}"[0] or *str == u8")"[0] or
                   std::isspace(*str)) {
            break;
        } else {
            string += *str;
            ++str;
        }
    }
    scam::assert(not string.empty(), u8"Empty symbol found");
    return string;
}

static constexpr const char* const numbers = u8"0123456789";

static scm parse_trailing_double(const char* backup,
                                 const char*& str, double result) {
    std::puts("Trailing double");
    ++str;
    double multiplier = 1;
    while (true) {
        if (std::strchr(numbers, *str)) {
        } else {
            return wrap_string(parse_symbol(backup, 0));
        }
        ++str;
    }
    return wrap_double(result);
}

static scm parse_double(const char*& str) {
    const char* backup = str;
    double result = 0;
    // double power = 0;
    bool negative = false;
    bool started = false;

    if (*str == u8"-"[0]) {
        negative = true;
        ++str;
    }
    while (true) {
        if (not *str) {
            break;
        } else if (*str == u8"."[0]) {
            return parse_trailing_double(backup, str, result);
        } else if (std::strchr(numbers, *str)) {
            result *= 10;
            result += *str - u8"0"[0];
            started = true;
        } else {
            break;
        }
        ++str;
    }

    if (started) {
        if (negative) {
            result *= -1;
        }
        // result *= std::pow(10, power);
        if (std::find(backup, str, u8"."[0]) == str) {
            return wrap_int(result);
        } else {
            return wrap_double(result);
        }
    } else {
        return wrap_string(parse_symbol(backup, 0));
    }
}

static void forward_over_space(const char*& str) {
    while (std::isspace(*str)) {
        ++str;
    }
}

static scm internal_parse(const char*& str, const char*& end,
                          bool recursive = true) {
    forward_over_space(str);
    scam::assert(str != end, u8"Empty buffer");

    // string
    if (str[0] == u8"\""[0]) {
        auto scm = std::make_shared<SCM>();
        new (&scm->_str) std::string(parse_string(str, end - str));
        scm->type = SCM::e_string;
        scam::assert(recursive or str == end,
                     u8"More than one ast to parse");
        return scm;
    }

    // quoted
    if (str[0] == u8"'"[0]) {
        auto scm = std::make_shared<SCM>();
        ++str;
        scam::assert(not std::isspace(str[0]), u8"Empty quote");
        new (&scm->_quoted) scam::scm(internal_parse(str, end));
        scm->type = SCM::e_quoted;
        scam::assert(recursive or str == end,
                     u8"More than one ast to parse");
        return scm;
    }

    // number
    if (std::strchr("-0123456789.", str[0]) or str[0] == u8"."[0]) {
        // It could actually be a symbol, so let parse_double return a
        // Scheme Object instead of a double.

        // Ex: -fun? or .hi
        return parse_double(str);
    }

    // list (cons linked list)
    if (str[0] == u8"("[0]) {
        std::vector<scm> list;
        ++str;
        forward_over_space(str);
        // | input   | list           |
        // |---------|----------------|
        // | ()      | nil            |
        // | (a)     | {a, nil}       |
        // | (a b)   | {a, b, nil}    |
        // | (a b c) | {a, b, c, nil} |
        // etc...
        while (str[0] != u8")"[0]) {
            list.push_back(internal_parse(str, end));
            forward_over_space(str);
        }
        scm result = nil();
        for (auto i = list.rbegin(); i != list.rend(); ++i) {
            result = cons(*i, result);
        }
        return result;
    }
    // symbol
    {
        return wrap_symbol(parse_symbol(str, end - str));
    }
}

scm parse(const std::string& text) {
    const char* str = text.c_str();
    const char* end = text.c_str() + text.size();
    // whitespace removal
    while (str != end and std::isspace(*end)) {
        --end;
    }
    return internal_parse(str, end, false);
}
}
