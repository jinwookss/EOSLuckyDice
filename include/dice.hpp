#pragma once

#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>

#include <string>
#include <list>

using std::string;
using std::list;
using eosio::asset;
using eosio::name;
using eosio::contract;

class [[eosio::contract]] dice : public contract {

public:
    dice(name s, name code, eosio::datastream<const char*> ds) : contract::contract(s, code, ds) {}

    [[eosio::action]]
    void bet(name user, asset number);

    [[eosio::action]]
    void notires(name user, asset result, asset profit);

    [[eosio::action]]
    void reguser(name user, string nick_name);

    [[eosio::action]]
    void dereguser(name user);

    [[eosio::action]]
    void upsertgame(name user, string date, asset number, asset result, asset profit);

    [[eosio::action]]
    void erasegame(name user);

    [[eosio::action]]
    void history(name user);

private:
    struct [[eosio::table]] person {
        name key;
        string nick_name;

        uint64_t primary_key() const { return key.value; }
    };
    typedef eosio::multi_index<"users"_n, person> user_index;

    struct game {
        string date;
        asset number;
        asset result;
        asset profit;
    };

    struct [[eosio::table]] game_info {
        name key;
        list<game> games;

        uint64_t primary_key() const { return key.value; }
    };
    typedef eosio::multi_index<"games"_n, game_info> game_index;
};