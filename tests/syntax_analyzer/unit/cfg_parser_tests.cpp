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


TEST_CASE ("left factoring test 3") {
    // grammar:

//    X -> aE | IXE | (X)E
//    E -> IE | BXE | ϵ
//    I -> ++ | --
//    B -> + | - | ϵ

    // result:
//    steps:
//    X -> aE ∣ ++XE ∣ --XE ∣ (X)E
//    E -> ++E ∣ --E ∣ +XE ∣ -XE ∣ XE | eps // sub x

//    X -> aE ∣ ++XE ∣ --XE ∣ (X)E
//    E -> ++E ∣ --E ∣ +XE ∣ -XE ∣ aEE ∣ ++XEE ∣ --XEE ∣ (X)EE | eps

//     X -> aE ∣ ++XE ∣ --XE ∣ (X)E
//     E -> +E1 | -E2 | aEE | (X)EE | eps
//     E1 -> +E | XE | +XEE
//     E2 -> -E | XE | -XEE
    // we can sub X again and keep doing so we will find that this grammar is not even LL

}


TEST_CASE ("left factoring test 4") {
//    F -> FBa ∣ cDS ∣ c
//
}