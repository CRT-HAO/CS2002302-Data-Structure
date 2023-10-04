# CS2002302-Data-Structure



## Build

Use `clang` or `gcc` to build c++ code.

```bash
clang++ ./main.cpp -std=c++11 -o ./main
```

### Build multiple files to single cpp file

Use [cg-singlefile-for-cpp](https://github.com/aangairbender/cg-singlefile-for-cpp) to build multiple cpp files to single file.

```bash
cg-singlefile-for-cpp "main.cpp" -o "bundled.cpp"
```

