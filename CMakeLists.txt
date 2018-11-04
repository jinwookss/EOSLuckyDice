cmake_minimum_required(VERSION 3.12)
project(EOSLuckyDice)

find_package(eosio.cdt)
add_contract( hello hello src/hello.cpp)

