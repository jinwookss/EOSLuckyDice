# EOSLuckyDice
This project is a simple dice game using EOSIO smart contract.

## About
Contract dice includes actions below.
- `bet`        : compare input number with randomly generated number to determine win/lose.
- `notires`    : notify result of the bet action to user.
- `reguser`    : register new user.
- `dereguser`  : deregister existing user.
- `upsertgame` : save result of the bet to DB table.
- `erasegame`  : delete game logs of the user. 
- `history`    : show game logs of the user.

## License
MIT
