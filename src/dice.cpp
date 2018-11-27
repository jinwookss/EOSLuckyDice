#include "dice.hpp"
#include "random_gen.hpp"
#include <eosiolib/print.h>

void dice::bet(name user, uint32_t number) {
	require_auth(user);
	
	user_index users(_code, _code.value);
	eosio_assert(users.find(user.value) != users.end(), "User does not exist");

	eosio_assert(number > 0 && number < 100, "Invalid range of number");
	
	uint32_t result = random_gen::get_instance(user).range(99) + 1; // 1~99
	uint32_t profit = 0;

	if (number <= result) {
		profit = 100;
	}

	upsertgame(user, "2018-11-08", number, result, profit);
	
	send_result(user, number, result, profit);
}

void dice::notires(name user, uint32_t number, uint32_t result, uint32_t profit) {
	require_auth(get_self());
    require_recipient(user);
}

void dice::reguser(name user, string nick_name) {
	require_auth(user);

	user_index users(_code, _code.value);
	auto iterator = users.find(user.value);
	if (iterator == users.end()) {
		users.emplace(user, [&]( auto& row ) {
			row.key = user;
			row.nick_name = nick_name;
		});
	} else {
		users.modify(iterator, user, [&]( auto& row ) {
			row.key = user;
			row.nick_name = nick_name;
		});
	}
}

void dice::dereguser(name user) {
	require_auth(user);

	user_index users(_code, _code.value);
	auto iterator = users.find(user.value);
	eosio_assert(iterator != users.end(), "User does not exist");
	users.erase(iterator);
}

void dice::upsertgame(name user, string date, uint32_t number, uint32_t result, uint32_t profit) {
	require_auth(user);
	gamelog newgame {
		date,
		number,
		result,
		profit
	};

	game_index games(_code, _code.value);
	auto iterator = games.find(user.value);
	if (iterator == games.end()) {
		games.emplace(user, [&]( auto& row ) {
			row.key = user;
			row.gamelogs.push_back(newgame);
		});
	} else {
		games.modify(iterator, user, [&]( auto& row ) {
			row.key = user;
			row.gamelogs.push_back(newgame);
		});
	}
}

void dice::erasegame(name user) {
	require_auth(user);

	game_index games(_code, _code.value);
	auto iterator = games.find(user.value);
	eosio_assert(iterator != games.end(), "User does not exist");
	games.erase(iterator);
}

void dice::history(name user) {
	require_auth(user);

	user_index users(_code, _code.value);
	eosio_assert(users.find(user.value) != users.end(), "User does not exist");

	game_index games(_code, _code.value);
	auto iterator = games.find(user.value);
	eosio_assert(iterator != games.end(), "Gamelog does not exist");

	eosio::print(name(user), " \n ");
	for (auto itr = iterator->gamelogs.begin(); itr != iterator->gamelogs.end(); ++itr) {
		eosio::print("game : ", itr->date, ", ", itr->number, ", ", itr->result, ", ", itr->profit, " \n ");
	}
}

void dice::send_result(name user, uint32_t number, uint32_t result, uint32_t profit) {
	action(
		permission_level{get_self(), "active"_n},
		get_self(),
		"notires"_n,
		make_tuple(user, number, result, profit)
	).send();
}

EOSIO_DISPATCH( dice, 
    (bet)(notires)
    (reguser)(dereguser)
    (upsertgame)(erasegame)(history)
)