#include "catch.hpp"
#include "scam.hh"

TEST_CASE("show stuff") {
    REQUIRE("asdf" == scam::show(scam::wrap_symbol("asdf")));
    REQUIRE("123" == scam::show(scam::wrap_int(123)));
    REQUIRE("(a)" ==
            scam::show(scam::wrap_list({scam::wrap_symbol("a")})));
    REQUIRE("(\"asdf\" 123)" ==
            scam::show(scam::wrap_list(
                {scam::wrap_string("asdf"), scam::wrap_int(123)})));
    REQUIRE("(a b)" ==
            scam::show(scam::wrap_list(
                {scam::wrap_symbol("a"), scam::wrap_symbol("b")})));
    REQUIRE("(a . b)" ==
            scam::show(scam::cons(scam::wrap_symbol("a"),
                                  scam::wrap_symbol("b"))));

    REQUIRE("?a" ==
            scam::show(scam::wrap_char(u8"a"[0])));
    REQUIRE("?\\\"" ==
            scam::show(scam::wrap_char(u8"\""[0])));
    REQUIRE("?\\ " ==
            scam::show(scam::wrap_char(u8" "[0])));
    REQUIRE("?\\(" ==
            scam::show(scam::wrap_char(u8"("[0])));
}
