#!/bin/sh
set -eu

KSOURCE_ROOT=$(pwd)

display_usage() {
    echo "Usage: $0 [--cleanup | <commit-or-tag>]"
    echo "  --cleanup:              Cleans up previous modifications made by the script."
    echo "  -h, --help:             Displays this usage information."
    echo "  (no args):              Sets up gore driver to your kernel source."
}

initialize_variables() {
    if test -d "$KSOURCE_ROOT/common/drivers"; then
         DRIVER_DIR="$KSOURCE_ROOT/common/drivers"
    elif test -d "$KSOURCE_ROOT/drivers"; then
         DRIVER_DIR="$KSOURCE_ROOT/drivers"
    else
         echo '[ERROR] "drivers/" directory not found.'
         exit 127
    fi

    DRIVER_MAKEFILE=$DRIVER_DIR/Makefile
    DRIVER_KCONFIG=$DRIVER_DIR/Kconfig
}

delete() {
    echo "[+] Removing gore driver..."
    sed -i '/obj-$(CONFIG_GORE)		+= gore/d' "$DRIVER_MAKEFILE"
    sed -i '/source "drivers\/gore\/Kconfig"/d' "$DRIVER_KCONFIG"
    rm -rf "$DRIVER_DIR/gore"
}

setup() {
    #yes gore, but should work
    mkdir -p "$DRIVER_DIR/gore"

    sed -i '15i \
obj-$(CONFIG_GORE)		+= gore/' "$DRIVER_MAKEFILE"

    sed -i '15i \
source "drivers/gore/Kconfig"' "$DRIVER_KCONFIG"

    echo "obj-y := gore.o" > "$DRIVER_DIR/gore/Makefile"
    curl -o "$DRIVER_DIR/gore/Kconfig" https://raw.githubusercontent.com/nedokaka/linux-gore-driver/main/linux/Kconfig
    curl -o "$DRIVER_DIR/gore/gore.c" https://raw.githubusercontent.com/nedokaka/linux-gore-driver/main/gore.c
    echo '[+] Done.'
}

# Process command-line arguments
if [ "$#" -eq 0 ]; then
    initialize_variables
    setup
elif [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
    display_usage
elif [ "$1" = "--cleanup" ]; then
    initialize_variables
    delete
else
    initialize_variables
    setup "$@"
fi