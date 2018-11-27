cmake_minimum_required(VERSION 3.12)
project(EOSLuckyDice)
find_package(eosio.cdt)


# Variable Setting
SET(CONTRACT_NAME dice)     # SET Contract name
SET(WASM_NAME dice)         # SET WASM name
SET(CPP src/dice.cpp)       # SET Source Code File

INCLUDE_DIRECTORIES (include)

#
add_contract( ${CONTRACT_NAME} ${WASM_NAME} ${CPP})
# add_contract( {Contract Name} {WASM Name} {src/cpp} )
# add_contract( dice dice src/dice.cpp)

