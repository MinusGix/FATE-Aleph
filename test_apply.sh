#!/bin/bash
# This file currently is for testing. Applying patch, building aleph, and copying it.
# An actual installation script would likely be nicer.

GAME_DIR=$1
if [ -z "$GAME_DIR" ]; then
    echo "Please give the path to your FATE folder."
    exit 1
fi

if [ ! -d "$GAME_DIR" ]; then
    echo "That is an invalid path."
    exit 2
fi

GAME_MODS_DIR=$GAME_DIR/scripts/
if [ ! -d "$GAME_MODS_DIR" ]; then
    echo "Game directory does not have mods folder. Creating."
    mkdir "$GAME_MODS_DIR"
fi

# Apply patches. We assume that name is Fate.exe, if it isn't always then we can change this.
./patches/apply_patches.sh "$GAME_DIR/Fate.exe" &&
echo "Building aleph" &&
./aleph/build.sh &&
echo "Moving aleph files and mods to game folder" &&
cp ./build/aleph.dll "$GAME_DIR" &&
cp -r ./mods "$GAME_MODS_DIR"