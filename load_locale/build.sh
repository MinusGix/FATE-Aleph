THIS_DIR=$(dirname $0)
i686-w64-mingw32-gcc \
    -m32 \
    -O3 \
    -Wall \
    -std=c17 \
    "$THIS_DIR/load_locale.c" \
    -o "$THIS_DIR/../build/load_locale.exe"
