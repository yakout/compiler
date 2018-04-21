#include "../lib/catch.hpp"

TEST_CASE("test FIRST")
{
    // TODO

//    E -> TE’
//    E’ -> +TE’ | eps
//    T -> FT’
//    T’ -> *FT’ | eps
//    F -> (E) | id

//    FIRST(F) = {(,id}
//    FIRST(T’) = {*, eps}
//    FIRST(T) = {(,id}
//    FIRST(E’) = {+, eps}
//    FIRST(E) = {(,id}

//    FIRST(TE’) = {(,id}
//    FIRST(+TE’ ) = {+}
//    FIRST(eps) = {eps}
//    FIRST(FT’) = {(,id}
//    FIRST(*FT’) = {*}
//    FIRST(eps) = {eps}
//    FIRST((E)) = {(}
//    FIRST(id) = {id}
}


TEST_CASE("test FOLLOW")
{
    // TODO
//    E -> TE’
//    E’ -> +TE’ | eps
//    T -> FT’
//    T’ -> *FT’ | eps
//    F -> (E) | id

//    FOLLOW(E) = { $, ) }
//    FOLLOW(E’) = { $, ) }
//    FOLLOW(T) = { +, ), $ }
//    FOLLOW(T’) = { +, ), $ }
//    FOLLOW(F) = {+, *, ), $ }

}