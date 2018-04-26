#include "../../lib/catch.hpp"

TEST_CASE ("multi-line-cfg-test") {

}

TEST_CASE ("single-line-cfg-test") {

}



TEST_CASE ("left factoring test 1") {
    // grammar:
    // S -> if E then S | if E then S else S | a
    // E -> b

    // result:
    // S -> if E then S S' | a
    // S -> else S | eps
    // E -> b
}


TEST_CASE ("left factoring test 2") {
    // grammar:
//    A -> aX | aY

    // result:
//    A -> aZ
//    Z -> X | Y
}


TEST_CASE ("left factoring test 2") {
    // grammar:

//    X -> aE | IXE | (X)E
//    E -> IE | BXE | ϵ
//    I -> ++ | --
//    B -> + | - | ϵ

    // result:
//    A -> aZ
//    Z -> X | Y
}