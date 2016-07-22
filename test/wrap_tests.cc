#include "catch.hpp"
#include "scam.hh"

TEST_CASE("wrap int") {
    scam::scm n123 = scam::wrap_int(123);
    REQUIRE(scam::is_int(n123));
    REQUIRE(123 == scam::int_value(n123));
}

TEST_CASE("wrap double") {
    scam::scm n123_03 = scam::wrap_double(123.03);
    REQUIRE(scam::is_double(n123_03));
    REQUIRE(123.03 == Approx(scam::double_value(n123_03)));
}

TEST_CASE("wrap string") {
    scam::scm str = scam::wrap_string("str");
    REQUIRE(scam::is_string(str));
    REQUIRE("str" == scam::string_value(str));
}

TEST_CASE("wrap symbol") {
    scam::scm str = scam::wrap_symbol("str");
    REQUIRE(scam::is_symbol(str));
    REQUIRE("str" == scam::symbol_value(str));
}
