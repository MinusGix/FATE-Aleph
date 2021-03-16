#!/usr/bin/env bash


PATCH_EXECUTABLE=$1
if [ -z "$PATCH_EXECUTABLE" ]; then
    echo "An executable to patch is required!"
    exit 1
fi

if [ ! -f "$PATCH_EXECUTABLE" ]; then
    echo "The executable given does not exist."
    exit 2
fi

THIS_DIR=$(dirname $0)
PARENT_DIR=$THIS_DIR/..

#C_TARGET=i386-pc-win32
C_TARGET=i686-pc-windows-gnu

# TODO: Do more complicated warnings about args depending on system
    # because on linux, if you're using gcc you probably want i686-w64-mingw32-gcc for
    # cross compilation. But, clang supports cross compilation in one executable.

if [ -z $CC ]; then
    echo "CC environment variable not set. Defaulting to clang."
    CC=clang
fi

if [ "$CC" == "clang" ]; then
    extra_c_args="--target=$C_TARGET \
        -Weverything \
        -Wno-newline-eof \
        -Wno-missing-prototypes \
        -Wno-packed"
fi

function compileC { # name start end
    # Ugh, I hate that bash doesn't let you put comments between multiline invocations.

    # Unsure if we should be removing plt and pic

    # We optimize for size because the functions we're patching can be small
    # Esp. if ew do their logic plus our own.

    # We enable lots of warnings, but disable a few that are too absurd.

    $CC \
        -fno-stack-protector \
        -fno-plt \
        -fno-pic \
        -fno-asynchronous-unwind-tables \
        -m32 \
        -Os \
        -Wall \
        -Wno-unused-variable \
        $extra_c_args \
        -c "$THIS_DIR/$1.c" \
        -o "$PARENT_DIR/build/$1.o"
}
function extractTextSection { # name start_in_mem
    # We enable position-independent-code, because we are going to just patch it in place
    # So it shouldn't realy too much on its position.
    
    # We set the max-page-size to 0x4 because 0x1000 (4096) is too large.
    # For any function which causes it to want to create a new for .data
    # (Which I'm still not sure what causes that..)
    # it would result in it being a bit more than four kilobytes large
    # which is absurd and larger than any function, so unfeasible
    # This feels hacky, and probably is.

    # We output as a flat binary because we're just placing it ontop.
    
    # We tell it that the text section will be at a specific place in mem
    # Unsure if this is legitimately needed anymore.

    # This uses elf_i386 because that is just the easiest way to get it to extract it.
    # it complains about pe. I don't think this matters?
    ld \
        "$PARENT_DIR/build/$1.o" \
        -pie \
        -z max-page-size=0x4 \
        --oformat binary \
        -Ttext=0x$2 \
        -melf_i386 \
        -o "$PARENT_DIR/build/$1.bin"
}
function buildCFlat { # name start end start_in_mem
    compileC $1 &&
    extractTextSection $1 $4
}

function buildNASM { # name
    nasm \
        -f bin \
        "$THIS_DIR/$1.asm" \
        -o "$PARENT_DIR/build/$1.bin"
}

function applyPatch { # name start end
    if [[ $DRY_PATCH = 1 ]]; then 
        printf "\t\x1b[1;32m✓ $1 (Dry)\x1b[0;0m\n"
    else
        $PARENT_DIR/build/patch $2 $3 "$PARENT_DIR/build/$1.bin" "$PATCH_EXECUTABLE"
        tmp=$?; if [[ $tmp != 0 ]]; then
            printf "\t\x1b[1;31m✕ $1\x1b[0;0m\n"
            exit 1
        else
            printf "\t\x1b[1;32m✓ $1\x1b[0;0m\n"

        fi
    fi
}
function applyC { # name start end start_in_mem
    buildCFlat $1 $2 $3 $4 &&
    applyPatch $1 $2 $3
}
function applyNASM {
    buildNASM $1 $2 $3 &&
    applyPatch $1 $2 $3
}

printf "\x1b[1mNote\x1b[0m: Warnings that say 'cannot find entry symbol _start' may be safely disregarded.\n"
echo "Applying Patches.."
# === PATCHES SHOULD BE PUT HERE  ====
# The numbers are by _default_ in hexadecimal.
# If possible, patches should not depend on order.

# == Initialization ==
# We initialize Aleph in this function.
applyC init_setting_info1 348E70 34909F 00748e70

# == Performance ==
# Minor perf improvement.
applyC file_readline bd2a0 bd36f 004bd2a0
# Very minor, just one less string copy. More so that if I want to patch it later, I already have it
applyC file_open bd410 bd4cd 004bd410
applyC file_parse bd690 bd88f 004bd690
# Minor. Removes heap alloc and free.
applyC unk48a_constructor b53a0 b546f 004b53a0

# == Random ==
# Removes the exception handling. Mainly to test if I could.
applyNASM llsFrameHandler 275410 27541b
# Slightly shortens the code for loadLocaleString. Mostly initial testing
applyC loadLocaleString b6740 b680f 46b740
# Makes so if I want to, its easier to patch into drawing.
applyC game_update_window 1eac0 1ee0f 0041eac0

# === PATCHES SHOULD BE PUT ABOVE ====
echo "Done applying patches."
