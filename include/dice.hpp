#pragma once

#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>

#include <string>
#include <list>

using namespace std;
using namespace eosio;

class [[eosio::contract]] dice : public eosio::contract {

public:
    using contract::contract;

    dice(name s, name code, eosio::datastream<const char*> ds) : contract(s, code, ds) {}

    [[eosio::action]]
    void bet(name user, uint32_t number);

    [[eosio::action]]
    void notires(name user, uint32_t number, uint32_t result, uint32_t profit);

    [[eosio::action]]
    void reguser(name user, string nick_name);

    [[eosio::action]]
    void dereguser(name user);

    [[eosio::action]]
    void upsertgame(name user, string date, uint32_t number, uint32_t result, uint32_t profit);

    [[eosio::action]]
    void erasegame(name user);

    [[eosio::action]]
    void history(name user);

private:
    void send_result(name user, uint32_t number, uint32_t result, uint32_t profit);

    struct [[eosio::table]] person {
        name key;
        string nick_name;

        uint64_t primary_key() const { return key.value; }
    };
    typedef eosio::multi_index<"users"_n, person> user_index;

    struct gamelog {
        string date;
        uint32_t number;
        uint32_t result;
        uint32_t profit;
    };

    struct [[eosio::table]] usergamelog {
        name key;
        vector<gamelog> gamelogs;

        uint64_t primary_key() const { return key.value; }
    };
    typedef eosio::multi_index<"games"_n, usergamelog> game_index;
};