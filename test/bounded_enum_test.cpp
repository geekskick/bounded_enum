#define CATCH_CONFIG_MAIN
#include "bounded_enum.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Can default initialise") {
    enum class alphabet { a, b, c, d, e };
    using uut = bounded_enum<alphabet, alphabet::a, alphabet::e>;
    uut a;
}

TEST_CASE("One valid still compiles") {
    enum class alphabet { a, b, c, d, e };
    using uut = bounded_enum<alphabet, alphabet::a, alphabet::a>;
    uut a;
}

TEST_CASE("Can throw if OOR assigned") {
    enum class alphabet { a, b, c, d, e };
    using uut = bounded_enum<alphabet, alphabet::a, alphabet::b>;
    uut a;
    REQUIRE_THROWS(a = alphabet::c);
}

TEST_CASE("Can initialise from an enum") {
    enum class alphabet { a, b, c, d, e };
    using uut = bounded_enum<alphabet, alphabet::a, alphabet::e>;
    uut a;
    REQUIRE(*a == alphabet::a);
    a = alphabet::d;
    REQUIRE(*a == alphabet::d);
}

TEST_CASE("Throws on invalid") {
    enum class alphabet { a, b, c, d, e };
    using uut = bounded_enum<alphabet, alphabet::a, alphabet::e>;
    REQUIRE_NOTHROW(uut{ 0 });
    REQUIRE_NOTHROW(uut{ 1 });
    REQUIRE_NOTHROW(uut{ 2 });
    REQUIRE_NOTHROW(uut{ 3 });
    REQUIRE_NOTHROW(uut{ 4 });
    REQUIRE_THROWS(uut{ 5 });
}

TEST_CASE("Can get enum out, and initialised correctly") {
    enum class alphabet { a, b, c, d, e };
    using uut = bounded_enum<alphabet, alphabet::a, alphabet::e>;
    uut a;

    REQUIRE(a.get() == alphabet::a);
    REQUIRE(*a == alphabet::a);
}

TEST_CASE("Can construct with enum value") {
    enum class alphabet { a, b, c, d, e };
    using uut = bounded_enum<alphabet, alphabet::a, alphabet::e>;

    uut a{ alphabet::c };
    REQUIRE(a.get() == alphabet::c);

    uut b{ 2 };
    REQUIRE(b.get() == alphabet::c);
}

TEST_CASE("This shouldn't compile") {
    // enum class alphabet{a,b,c,d,e};
    // using uut = bounded_enum<alphabet, alphabet::e, alphabet::a>;
    // uut a{alphabet::c};
}

TEST_CASE("Copy ctor") {
    enum class alphabet { a, b, c, d, e };
    using uut = bounded_enum<alphabet, alphabet::a, alphabet::e>;

    uut a{ 4 };
    uut b{ a };

    REQUIRE(b.get() == a.get());
}

TEST_CASE("Copy assign") {
    enum class alphabet { a, b, c, d, e };
    using uut = bounded_enum<alphabet, alphabet::a, alphabet::e>;

    uut a{ 4 };
    uut b = a;

    REQUIRE(b.get() == a.get());
}

TEST_CASE("Move assign") {
    enum class alphabet { a, b, c, d, e };
    using uut = bounded_enum<alphabet, alphabet::a, alphabet::e>;

    uut a{ alphabet::d };
    uut b = std::move(a);

    REQUIRE(a.get() == alphabet::a);
    REQUIRE(b.get() == alphabet::d);
}

TEST_CASE("Move ctor") {
    enum class alphabet { a, b, c, d, e };
    using uut = bounded_enum<alphabet, alphabet::a, alphabet::e>;

    uut a{ alphabet::d };
    uut b{ std::move(a) };

    REQUIRE(a.get() == alphabet::a);
    REQUIRE(b.get() == alphabet::d);
}

TEST_CASE("Can get underlying") {
    enum class alphabet { a, b, c, d, e };
    using uut = bounded_enum<alphabet, alphabet::a, alphabet::e>;

    uut a{ alphabet::d };

    REQUIRE(a.underlying() == 3);
}

TEST_CASE("Max and min correct") {
    enum class alphabet { a, b, c, d, e };
    using uut = bounded_enum<alphabet, alphabet::a, alphabet::e>;
    REQUIRE(uut::max_enum() == alphabet::e);
    REQUIRE(uut::min_enum() == alphabet::a);
    REQUIRE(uut::max_underlying() == 4);
    REQUIRE(uut::min_underlying() == 0);
}

TEST_CASE("Count correct") {
    enum class alphabet { a, b, c, d, e };
    using uut = bounded_enum<alphabet, alphabet::a, alphabet::e>;
    REQUIRE(uut::count() == 5);
}

TEST_CASE("Postfix increment") {
    enum class alphabet { a, b, c, d, e };
    using uut = bounded_enum<alphabet, alphabet::a, alphabet::e>;
    uut a{};

    REQUIRE(a.get() == alphabet::a);
    a++;
    REQUIRE(a.get() == alphabet::b);
    a++;
    REQUIRE(a.get() == alphabet::c);
    a++;
    REQUIRE(a.get() == alphabet::d);
    a++;
    REQUIRE(a.get() == alphabet::e);
    REQUIRE_THROWS(a++);
}

TEST_CASE("Prefix increment") {
    enum class alphabet { a, b, c, d, e };
    using uut = bounded_enum<alphabet, alphabet::a, alphabet::e>;
    uut a{};

    REQUIRE(a.get() == alphabet::a);
    ++a;
    REQUIRE(a.get() == alphabet::b);
    ++a;
    REQUIRE(a.get() == alphabet::c);
    ++a;
    REQUIRE(a.get() == alphabet::d);
    ++a;
    REQUIRE(a.get() == alphabet::e);
    REQUIRE_THROWS(++a);
}

TEST_CASE("Postfix decrement") {
    enum class alphabet { a, b, c, d, e };
    using uut = bounded_enum<alphabet, alphabet::a, alphabet::e>;
    uut a{ alphabet::e };

    REQUIRE(a.get() == alphabet::e);
    a--;
    REQUIRE(a.get() == alphabet::d);
    a--;
    REQUIRE(a.get() == alphabet::c);
    a--;
    REQUIRE(a.get() == alphabet::b);
    a--;
    REQUIRE(a.get() == alphabet::a);
    REQUIRE_THROWS(a--);
}

TEST_CASE("Prefix decrement") {
    enum class alphabet { a, b, c, d, e };
    using uut = bounded_enum<alphabet, alphabet::a, alphabet::e>;
    uut a{ alphabet::e };

    REQUIRE(a.get() == alphabet::e);
    --a;
    REQUIRE(a.get() == alphabet::d);
    --a;
    REQUIRE(a.get() == alphabet::c);
    --a;
    REQUIRE(a.get() == alphabet::b);
    --a;
    REQUIRE(a.get() == alphabet::a);
    REQUIRE_THROWS(--a);
}

TEST_CASE("== and !=") {
    enum class alphabet { a, b, c, d, e };
    using uut = bounded_enum<alphabet, alphabet::a, alphabet::e>;
    uut a{ alphabet::d };
    REQUIRE(a == alphabet::d);
    REQUIRE(a == uut{ alphabet::d });

    REQUIRE(a != alphabet::e);
    REQUIRE(a != uut{ alphabet::e });
}

TEST_CASE("Iterate") {
    enum class alphabet { a, b, c, d, e };
    using uut = bounded_enum<alphabet, alphabet::a, alphabet::e>;
    uut a{ alphabet::d };
    int i{};
    for (const auto& it : a) {
        REQUIRE(uut{ it }.underlying() == i++);
    }
}

TEST_CASE("Conversions") {
    enum class alphabet { a, b, c, d, e };
    using uut = bounded_enum<alphabet, alphabet::a, alphabet::e>;
    uut a{};
    using uut_truncated = bounded_enum<alphabet, alphabet::b, alphabet::e>;
    uut_truncated c{};
    REQUIRE(a != c);
    a = alphabet::b;
    REQUIRE(a == c);
}