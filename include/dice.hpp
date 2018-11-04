#pragma once

#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>

class [[eosio::contract]] dice : public eosio::contract {

public:
    [[eosio::action]]
    void bet(name user, asset number);

    [[eosio::action]]
    void notify_result(name user, asset result, asset profit);

    [[eosio::action]]
    
};