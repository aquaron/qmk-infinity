#!/bin/bash

function getvol() { echo $(grep ' /data ' /proc/self/mountinfo | cut -f 4 -d" "); }
_VOL=$(getvol)

if [ ! "${_VOL}" ]; then
    echo -e "ERROR: you need run Docker with the -v parameter, try:"
    echo "    docker run --rm -v /tmp:/data aquaron/qmk-infinity"
    exit 1
fi

HELP=`cat <<EOT
Usage: docker run --rm -v <local-dir>:/data aquaron/qmk-infinity <file.c> [<keyboard>] [<target>]

Example: docker run --rm -v $_VOL:/data aquaron/qmk-infinity example

 local-dir  - directory on the host system to map to container
 file.c     - custom 'keymap.c' file located in the <local-dir> (create 'aquaron.c' if not exist)
 keyboard   - optional keyboard profile (default: 'infinity60')
 target     - optional, eg: all, dfu, teensy, dfu-util (default: 'all')

Resulting files will be published in the <local-dir> (ex: check $_VOL) directory.
EOT`

if [[ $# -lt 1 ]] || [[ ! "${_VOL}" ]]; then echo "$HELP"; exit 1; fi

_FILE=${1:-"aquaron.c"}
_KEYBOARD=${2:-"infinity60"}
_TARGET=${3:-"all"}
_DATADIR="/data"
_KEYMAP="${_FILE%.*}"
_BIN="${_KEYBOARD}_${_KEYMAP}.bin"
_BINFILE="${_build}/${_BIN}"
_OUTFILE="${_DATADIR}/${_BIN}"
_KEYMAPS_DIR="${_build}/keyboards/${_KEYBOARD}/keymaps"
_SOURCE_FILE="${_DATADIR}/${_FILE}"
_SOURCE_DIR="${_KEYMAPS_DIR}/${_KEYMAP}"

echo "Checking for ${_SOURCE_FILE}..."
if [[ ! -f "${_SOURCE_FILE}" ]]; then
    cp "${_examples}/infinity.c" "${_SOURCE_FILE}"
fi

echo "Checking for ${_SOURCE_DIR}..."
if [[ ! -d "${_SOURCE_DIR}" ]]; then
    mkdir -p ${_SOURCE_DIR}
fi

echo "Copying ${_SOURCE_FILE} -> ${_SOURCE_DIR}/keymap.c"
cp "${_SOURCE_FILE}" "${_SOURCE_DIR}/keymap.c"

cd $_build

echo "Making ${_KEYBOARD}:${_KEYMAP}:${_TARGET}"
make ${_KEYBOARD}:${_KEYMAP}:${_TARGET}

if [[ ! -f "${_BINFILE}" ]]; then
    echo "ERROR: Failed to make ${_BIN}"
    exit 1
fi

mv ${_BINFILE} ${_OUTFILE}

echo "${_VOL}/${_BIN} Created!"

