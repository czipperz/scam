#ifndef HEADER_GUARD_SCAM_H
#define HEADER_GUARD_SCAM_H

#include <memory>
#include <string>
#include <vector>

namespace scam {
/**
 * Internal representation is for internal use only.  Use accessors.
 */
struct SCM;

/**
 * Representation of a Lisp Object.
 */
using scm = std::shared_ptr<SCM>;

/**
 * Parse the string, returning an unevaluated Lisp Object.
 */
scm parse(const std::string&);

/**
 * Evaluate a Lisp Object, returning the result.
 */
scm eval(const scm&);

/**
 * Call a function with arguments.
 */
scm fcall(scm function, const std::vector<scm>& args);

/**** Predicates ****/
bool is_int    (const scm&) noexcept;
bool is_double (const scm&) noexcept;
bool is_nil    (const scm&) noexcept;
bool is_t      (const scm&) noexcept;
bool is_string (const scm&) noexcept;
bool is_symbol (const scm&) noexcept;
bool is_cons   (const scm&) noexcept;
bool is_quoted (const scm&) noexcept;
bool is_char   (const scm&) noexcept;

/**
 * Walk the cons list, test if the last cdr yields nil.
 */
bool is_list   (const scm&) noexcept;

/**** Accessors ****/
/**
 * Get the integral representation of the Lisp Object.
 *
 * @pre is_int(scm)
 */
long int_value                  (const scm&);

/**
 * Get the floating point representation of the Lisp Object.
 *
 * @pre is_double(scm) || is_int(scm)
 */
double double_value             (const scm&);

/**
 * Test if the Lisp Object is not nil.
 */
bool bool_value                 (const scm&) noexcept;

/**
 * Get the value of the symbol represented by the Lisp Object.
 */
const std::string& symbol_value (const scm&);
/**
 * Get the value of the symbol represented by the Lisp Object.
 */
std::string& symbol_value       (scm&);

/**
 * Get the value of the string represented by the Lisp Object.
 *
 * This is not the same as `show`, which shows all kinds of data.
 * This only gets the string representation when `is_string()` is true.
 */
const std::string& string_value (const scm&);
/**
 * Get the value of the string represented by the Lisp Object.
 *
 * This is not the same as `show`, which shows all kinds of data.
 * This only gets the string representation when `is_string()` is true.
 */
std::string& string_value       (scm&);

/**
 * Get the value that the Lisp Object quoted.
 */
const scm& quoted_value         (const scm&);
/**
 * Get the value that the Lisp Object quoted.
 */
scm& quoted_value               (scm&);

/**
 * Get the character represented by the Lisp Object.
 */
char char_value                 (const scm&);

/**
 * Get the first element in the pair.
 */
const scm& car                  (const scm&);
/**
 * Get the first element in the pair.
 */
scm& car                        (scm&);

/**
 * Get the second element in the pair.
 */
const scm& cdr                  (const scm&);
/**
 * Get the second element in the pair.
 */
scm& cdr                        (scm&);

/**
 * Create a string representation of a Lisp Object.
 */
std::string show(const scm&);

/**
 * Create a string representation of a function call.
 */
std::string show_function_call(const std::string& name,
                               const std::vector<scm>& args);

/**** Values ****/
/**
 * The value `nil`.
 *
 * `nil` is the only value that is false.
 * Use `not is_nil(Lisp Object)` to test if something is truthy.
 */
scm nil();

/**
 * The value `t`.
 *
 * `t` is always true.
 */
scm t();

/**** Wrappers ****/
scm wrap_int    (long);
scm wrap_double (double);
scm wrap_string (std::string);
scm wrap_symbol (std::string);
scm cons        (scm car, scm cdr);
scm wrap_pair   (const std::pair<scm, scm>&);
scm wrap_char   (char);

/**
 * Generic way to wrap `cons()` around each element in `[first, last)`.
 */
template <class Iterator>
scm wrap_list(Iterator first, Iterator last) {
    scm result = nil();
    scm* append_place = &result;
    for (; first != last; ++first) {
        *append_place = cons(*first, *append_place);
        append_place = &cdr(*append_place);
    }
    return result;
}

/**
 * Generic way to wrap `cons()` around each element in a container.
 */
template <class Container>
scm wrap_list(Container&& container) {
    return wrap_list(std::begin(container), std::end(container));
}

/**
 * Custom overload for `std::vector` so that
 * `wrap_list({scam::wrap_int(1)})` works.
 * Wraps `cons()` around each element in the vector.
 */
inline static
scm wrap_list(const std::vector<scm>& container) {
    return wrap_list(container.begin(), container.end());
}

/**** General Functions ****/
/**
 * Create a deep copy of the Lisp Object, returning a unique
 * pointer.
 */
scm copy(scm);

/**** Register functions ****/
/**
 * Base class for function definitions: safely wraps a virtual call so
 * that argument counts can be checked.
 */
class defun_base {
public:
    const std::string documentation, name;
    const size_t required_args, optional_args;
    const bool rest_args, eval_args;

    /**
     * Define what the requirements are for the function to be called.
     */
    defun_base(scm (*definition)(const std::vector<scm>&),
               std::string name,
               std::string documentation, size_t required_args,
               size_t optional_args = 0, bool rest_args = false,
               bool eval_args = true);

    /**
     * Checks `args` matches criteria then calls `definition`.
     */
    scm call_handler(const std::vector<scm>&);

private:
    scm (*definition)(const std::vector<scm>&);
};

struct static_defun {
    static_defun(defun_base);
};
void defun(defun_base);

#define INTERNAL_SCAM_UNIQUE_NAME_LINE2(name, line) name##line
#define INTERNAL_SCAM_UNIQUE_NAME_LINE(name, line)                   \
    INTERNAL_SCAM_UNIQUE_NAME_LINE2(name, line)
#define INTERNAL_SCAM_UNIQUE_NAME(name)                              \
    INTERNAL_SCAM_UNIQUE_NAME_LINE(name, __LINE__)

#define DEFUN(name, ...)                                             \
    scam::scm name(const std::vector<scam::scm>&);                   \
    static scam::static_defun INTERNAL_SCAM_UNIQUE_NAME(             \
        DEFUN_VALUE) = scam::defun_base(name, __VA_ARGS__);          \
    scam::scm name
}

#endif
