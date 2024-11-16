# using-cmake

Example of using CMake to build C projects

## Compile

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release\   # or Debug
    -S ..\                          # Specify the source directory
    -B .\                           # Specify the build directory
    -G "Unix Makefiles"             # Specify the generator
cmake --build .                     # Build the project
```

## Run

Open a terminal and run the server:

```bash
./src/whoisserver
```

Open another terminal and run the client:

```bash
./src/whoisclient localhost:10496 whois google.com
```

## Clean

```bash
rm -rf build
```
