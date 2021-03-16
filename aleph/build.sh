THIS_DIR=$(dirname $0)

warnings="-Weverything \
    -Wno-c++98-compat-pedantic \
    -Wno-newline-eof \
    -Wno-zero-as-null-pointer-constant \
    -Wno-packed \
    -Wno-missing-prototypes \
    -Wno-padded \
"

# Build the dll as 32 bit. We statically link libgcc so that it isn't depended on (was getting
# errors that it couldn't be found').
# We enable stdcall fixup because it wanted me to, but unsure if that is needed.
clang++ \
    -static-libgcc \
    -static-libstdc++ \
    -Wl,--enable-stdcall-fixup \
    -static \
    $warnings \
    -shared \
    --target=i686-pc-windows-gnu \
    -m32 \
    -O3 \
    -o "$THIS_DIR/../build/aleph.dll" \
    "$THIS_DIR/aleph.cpp" "$THIS_DIR/helper.cpp" \
    "$THIS_DIR/aleph.def" \
    -Wl,-Bdynamic "$THIS_DIR/../include/lua/lua54.dll" \
    -Wl,-Bstatic -pthread \
    -lm
