# qmk-infinity
Uses QMK to build the data file to flash Input Club's Infinity 60%.

## Syntax

    docker run --rm -v <local-dir>:/data aquaron/qmk-infinity <file.c> [<keyboard>] [<target>]

`<file.c>` is the name of the keymap file that contains the mapping to customize your keyboard layout.
See [qmk_firmware] for detailed information on how to customize the layout.
Create a `keymap.c` file and put it in `<local-dir>` and issue this command to run:

    docker run --rm -v /tmp:/data aquaron/qmk-infinity keymap.c


## Examples

### Build Example Keyboard

To check out a custom layout that uses VI-style cursor using dual-role semi-colon key as a layer switch run
the command below and check out `aquaron.c` in `/tmp`.

    docker run --rm -v /tmp:/data aquaron/qmk-infinity aquaron.c

[qmk_firmware]: https://github.com/qmk/qmk_firmware/tree/master/keyboards/infinity60
