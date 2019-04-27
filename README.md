# bounded_enum
I made this because whenever I am using enums in c++ I always want extra functionality, such as iterating over them, and incrementing, and casting to/from an integer

This header hopefully makes a step towards providing that.

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