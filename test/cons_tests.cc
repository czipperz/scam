#include "catch.hpp"
#include "scam.hh"

TEST_CASE("cons and unwrap") {
    scam::scm c = scam::cons(scam::wrap_int(3), scam::wrap_int(6));
    REQUIRE(scam::is_cons(c));
    REQUIRE(scam::is_int(scam::car(c)));
    REQUIRE(3 == scam::int_value(scam::car(c)));
    REQUIRE(scam::is_int(scam::cdr(c)));
    REQUIRE(6 == scam::int_value(scam::cdr(c)));
}

TEST_CASE("wrap list") {
    scam::scm empty = scam::wrap_list({});
    REQUIRE(scam::is_nil(empty));
    scam::scm one = scam::wrap_list({scam::wrap_int(3)});
    REQUIRE(scam::is_cons(one));
    REQUIRE(scam::is_int(scam::car(one)));
    REQUIRE(3 == scam::int_value(scam::car(one)));
    REQUIRE(scam::is_nil(scam::cdr(one)));
}
