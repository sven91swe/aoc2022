#!/bin/bash
bazel build --copt="-Werror" //...
#bazel test //...

clang-format -i $(find -iname *.cpp -o -iname *.h)