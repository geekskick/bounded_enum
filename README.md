# bounded_enum
I made this because whenever I am using enums in c++ I always want extra functionality, such as iterating over them, and incrementing, and casting to/from an integer

This header hopefully makes a step towards providing that, since the magic enum library is C++17 only.

## Functionality
Create an enum with defined upper and lower bounds.
```
enum class alphabet { a, b, c, d };
using alphabet_bt = bounded_enum<alphabet, alphabet::a, alphabet::d>;
```

Create from an integer or an enum
```
alphabet_bt letter { alphabet::d };
alphabet_bt other_letter { 0 };
REQUIRE(other_letter == alphabet::a);
```

Get the underlying type
```
auto ul = letter.underlying();
REQUIRE(ul == 3);
```

Get the enum value out
```
auto e = letter.get();
auto p = *letter;
REQUIRE(p == e);
REQUIRE(p == alphabet::d);
```

Convert to/from the enum and underlying type
```
REQUIRE(alphabet_bt::to_underlying(alphabet_bt::type::b) == alphabet_bt::from_underlying(1));
```

Compare between two differently bounded enums
```
using smaller_bt = bounded_enum<alphabet, alphabet::b, alphabet::c>;
smaller_bt more_restrictive_letter{};
letter = alphabet_bt::type::b;
REQUIRE(more_restrictive_letter == letter);
REQUIRE_THROWS(more_restictive_letter = alphabet_bt::type::d);
```

Find out how many enum values there are
```
std::cout << "There are " << alphabet_bt::count << " options to choose from\n"
```

Move to the next enum value (works the same way with subtraction
```
letter++;
++letter;
letter = alphabet_bt::max_enum();
REQUIRE_THROWS(++letter);
REQUIRE_THROWS(letter++);
```

## Getting
```
pushd .
git clone https://github.com/geekskick/bounded_enum.git
cd bounded_enum
cmake -B build -H.
cmake --build build --target test
cmake --build build --target install
popd
```

## Testing
If you want to test this you can use
```
pushd .
git clone https://github.com/geekskick/bounded_enum.git
cd bounded_enum
cmake -B build
cmake --build build
cmake --build build --target test
popd 
```
