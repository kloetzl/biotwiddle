# Biotwiddle

This repository contains the LaTeX files and sources for my note on [Bit-twiddling on Nucleotides](http://biorxiv.org/content/early/2016/10/20/082214). It is an not peer-reviewed preprint. Comments are welcome.

## Building

Prerequisites: GCC, Clang, [Google Benchmark](https://github.com/google/benchmark/) and Python 3.

```
git clone https://github.com/kloetzl/biotwiddle
cd biotwiddle
make
```

This compiles the code, runs unit tests, benchmarks and uses those results for figures in the LaTeX files.

## Maintenance Warning

Though the findings reported in the paper are still mostly valid, this repository has been superseeded by [libdna](https://github.com/kloetzl/libdna). Consider biotwiddle unmaintained.

