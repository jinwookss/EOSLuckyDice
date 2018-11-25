#pragma once

#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>

#include <string>
#include <list>

using namespace std;
using namespace eosio;

CONTRACT dice : public eosio::contract {

public:
    using contract::contract;

    dice(name s, name code, eosio::datastream<const char*> ds) : contract(s, code, ds) {}

    ACTION bet(name user, uint32_t number);

    ACTION notires(name user, uint32_t number, uint32_t result, uint32_t profit);

    ACTION reguser(name user, string nick_name);

    ACTION dereguser(name user);

    ACTION upsertgame(name user, string date, uint32_t number, uint32_t result, uint32_t profit);

    ACTION erasegame(name user);

    ACTION history(name user);

private:
    void send_result(name user, uint32_t number, uint32_t result, uint32_t profit);

    TABLE person {
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

    TABLE usergamelog {
        name key;
        vector<gamelog> gamelogs;

        uint64_t primary_key() const { return key.value; }
    };
    typedef eosio::multi_index<"games"_n, usergamelog> game_index;
};