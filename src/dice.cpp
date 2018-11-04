#include "dice.hpp"

void dice::bet(name user, asset number) {

}

void dice::notires(name user, asset result, asset profit) {

}

void dice::reguser(name user, string nick_name) {

}

void dice::dereguser(name user) {

}

void dice::upsertgame(name user, string date, asset number, asset result, asset profit) {

}

void dice::erasegame(name user) {

}

void dice::history(name user) {

}

EOSIO_DISPATCH( dice, 
    (bet)(notires)
    (reguser)(dereguser)
    (upsertgame)(erasegame)(history)
)