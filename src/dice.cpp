#include "dice.hpp"

void dice::bet(name user, asset number) {
	// require_auth(user);

	// user_index users(_code, _code.value);
	// eosio_assert( users.find(user.value) != users.end(), "unregistered user" );

	// bool result = playdice(number);
}

void dice::notires(name user, asset result, asset profit) {
	
}

void dice::reguser(name user, string nick_name) {
	require_auth(user);

	user_index users(_code, _code.value);
	auto iterator = users.find(user.value);
	eosio_assert(iterator == users.end(), "Already registered");

	users.emplace(user, [&]( auto& row ) {
      row.key = user;
      row.nick_name = nick_name;
    });
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

bool dice::playdice(asset number) {
	return true;
}