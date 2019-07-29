BEGIN {
    FS = ","
    offset = 0x555555554000
}
{
    printf "%s %#06x\n", $1, $2 - offset
}
