clang++ \
    -std=c++17 \
    "$(dirname $0)/patch.cpp" \
    -o "$(dirname $0)/../build/patch"
