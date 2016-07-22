#include "scam.hh"
#include "catch.hpp"

TEST_CASE("parse quoted symbol") {
    {
        scam::scm a = scam::parse("'a");
        REQUIRE(scam::is_quoted(a));
        REQUIRE(scam::is_symbol(scam::quoted_value(a)));
        REQUIRE(scam::symbol_value(scam::quoted_value(a)) == "a");
    }

    REQUIRE_THROWS(scam::parse("'"));

    {
        scam::scm open_paren = scam::parse("'\\(");
        REQUIRE(scam::is_quoted(open_paren));
        REQUIRE(scam::is_symbol(scam::quoted_value(open_paren)));
        REQUIRE(scam::symbol_value(scam::quoted_value(open_paren)) == "\\(");
    }
    {
        scam::scm close_paren = scam::parse("'\\)");
        REQUIRE(scam::is_quoted(close_paren));
        REQUIRE(scam::is_symbol(scam::quoted_value(close_paren)));
        REQUIRE(scam::symbol_value(scam::quoted_value(close_paren)) == "\\)");
    }

    REQUIRE_THROWS(scam::parse("')"));
    REQUIRE_THROWS(scam::parse("'a)"));
}

TEST_CASE("parse list") {
    {
        scam::scm a = scam::parse("(a)");
        REQUIRE(scam::is_cons(a));
        REQUIRE(scam::is_symbol(scam::car(a)));
        REQUIRE("a" == scam::symbol_value(scam::car(a)));
        REQUIRE(scam::is_nil(scam::cdr(a)));
    }

    {
        scam::scm a_b = scam::parse("(a b)");
        REQUIRE(scam::is_cons(a_b));
        REQUIRE(scam::is_symbol(scam::car(a_b)));
        REQUIRE("a" == scam::symbol_value(scam::car(a_b)));
        REQUIRE(scam::is_symbol(scam::car(scam::cdr(a_b))));
        REQUIRE("b" == scam::symbol_value(scam::car(scam::cdr(a_b))));
        REQUIRE(scam::is_nil(scam::cdr(scam::cdr(a_b))));
    }
}

TEST_CASE("parse string") {
    {
        scam::scm abcd = scam::parse("\"abcd\"");
        REQUIRE(scam::is_string(abcd));
        REQUIRE("abcd" == scam::string_value(abcd));
    }
}

TEST_CASE("parse number") {
    {
        scam::scm n123 = scam::parse("123");
        REQUIRE(scam::is_int(n123));
        REQUIRE(123 == scam::int_value(n123));
    }
}
