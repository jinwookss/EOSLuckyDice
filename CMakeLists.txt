cmake_minimum_required(VERSION 3.12)
project(EOSLuckyDice)
find_package(eosio.cdt)


# Variable Setting
set(CONTRACT_NAME dice)     # SET Contract name
set(WASM_NAME dice)         # SET WASM name
set(CPP src/dice.cpp)       # SET Source Code File

include_directories(include)

#
add_contract( ${CONTRACT_NAME} ${WASM_NAME} ${CPP})
# add_contract( {Contract Name} {WASM Name} {src/cpp} )
# add_contract( dice dice src/dice.cpp)



add_custom_target(${WASM_NAME}.abi ALL)
set(ABI_FILE "${CMAKE_CURRENT_BINARY_DIR}/${WASM_NAME}.abi")
add_custom_command(TARGET ${WASM_NAME}.abi POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${ABI_FILE} "${CMAKE_CURRENT_SOURCE_DIR}/abi/${WASM_NAME}.abi")
