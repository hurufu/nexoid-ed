{
    user: [.[].user] | add,
    system: [.[].system] | add,
    real: [.[].real] | add
}
|
. + { cpu: ((.user + .system) / .real) }
