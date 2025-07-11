#include <iostream>
#include <string>

#include <vector>
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Chess.h"
#include "Knight.h"
#include "Pawn.h"
#include "User.h"

using namespace std;

int main() {
    Chess chess;
    chess.initialize();
    chess.printBoard();
    while (true) {
        // cout << "Enter command: "<< endl;
        string input;
        getline(cin, input);


        stringstream ss(input);
        vector<string> parts;
        string part;

        while (ss >> part) {
            parts.push_back(part);
        }

        if (parts.empty()) {
            continue;
        }


        if (parts[0] == "help") {
            if (chess.getWhiteUser().getUserName().empty() && chess.getBlackUser().getUserName().empty()) {
                cout << R"(register [username] [password]
login [username] [password]
remove [username] [password]
list_users
help
exit)" << endl;
            } else if (!chess.getWhiteUser().getUserName().empty() && chess.getBlackUser().getUserName().empty()) {
                cout << R"(new_game [username] [limit]
scoreboard
list_user
help
logout)" << endl;
            } else if (!chess.getWhiteUser().getUserName().empty() && !chess.getBlackUser().getUserName().empty()) {
                cout << R"(select [x],[y]
move [x],[y]
next_turn
show_turn
undo
undo_number
show_moves [-all]
show_killed [-all]
help
forfeit)" << endl;
            }
        } else if (parts[0] == "register") {
            if (parts.size() == 3) {
                User::registerUser(parts[1], parts[2]);
            } else {
                std::cout << "invalid command";
            }
        } else if (parts[0] == "list_users") {
            for (User user: User::users) {
                cout << user.getUserName() << endl;
            }
        } else if (parts[0] == "login") {
            if (parts.size() == 3) {
                User u = User::login(parts[1], parts[2]);
                if (u.isValid()) {
                    chess.setWhiteUser(u);
                }
            } else {
                std::cout << "invalid command" << std::endl;
            }
        } else if (parts[0] == "remove") {
            if (parts.size() == 3) {
                User::removeUser(parts[1], parts[2]);
            } else {
                std::cout << "invalid command" << std::endl;
            }
        } else if (!chess.getWhiteUser().getUserName().empty() && chess.getBlackUser().getUserName().empty() && parts[0]
                   == "new_game") {
            chess.newGame(parts[1], stoi(parts[2]));
        } else if (parts[0] == "scoreboard") {
            chess.showScoreboard();
        } else if (parts[0] == "logout") {
            chess.setWhiteUser(User());
            chess.setBlackUser(User());
            std::cout << "logout successful" << std::endl;
        } else if (parts[0] == "select") {
            chess.selectPiece(stoi(parts[1]), stoi(parts[2]));
        } else if (parts[0] == "deselect") {
            chess.deselectPiece();
        }else if (parts[0] == "move") {
            chess.movePiece(stoi(parts[1]), stoi(parts[2]));


        }

    }


    return 0;
}
