#include <bits/stdc++.h>
using namespace std;

const int NUMBER_OF_CARDS = 52;

std::string dealCards(deque<char>& player, deque<char>& dealer);
void printWinner(int winner, int numberOfCards);

int nextPlayerTurn(int turn);
void playerTakesAllTheCardsInTheTable(int last_face, deque<char> p[2], deque<char>& deck);

char putACardOnTheTable(int turn, deque<char> p[2], deque<char>& theCasinoTable);
int playBeggarMyNeighbour(deque<char> *players);

int main() {
    while(true)
    {
        deque<char> players[2]; // players[0] is player, players[1] is dealer

        auto dealCard = dealCards(players[0], players[1]);
        if (dealCard == "#") { break; }

        auto turn = playBeggarMyNeighbour(players);

        auto winner = nextPlayerTurn(turn);
        printWinner( winner, static_cast<int>( players[winner].size() ) );
    }
    return 0;
}

std::string dealCards(deque<char> &player, deque<char> &dealer)
{
    string card;
    for (int i = 1; i <= NUMBER_OF_CARDS; ++i) {
        cin >> card;
        if (card == "#") { break; }

        if (i % 2 == 0) { player.push_front(card[1]); }
        else { dealer.push_front(card[1]); }
    }
    return card;
}

void printWinner(int winner, int numberOfCards) { printf("%d%3d\n", winner + 1, numberOfCards); }

int nextPlayerTurn(int turn) { return (turn + 1) % 2; }

void playerTakesAllTheCardsInTheTable(int last_face, deque<char> *p, deque<char> &deck)
{
    while (!deck.empty())
    {
        p[last_face].push_back(deck.back());
        deck.pop_back();
    }
}

char putACardOnTheTable(int turn, deque<char> *p, deque<char> &theCasinoTable) {
    char card = p[turn].front();
    p[turn].pop_front();
    theCasinoTable.push_front(card);
    return card;
}

int playBeggarMyNeighbour(deque<char> *players) {
    map<char, int> faceCards;
    faceCards['A'] = 4;
    faceCards['K'] = 3;
    faceCards['Q'] = 2;
    faceCards['J'] = 1;
    deque<char> theCasinoTable; int turn = 1;
    int last_face = -1; int cover_count = 0;
    while (!players[turn].empty())
    {
        auto card = putACardOnTheTable(turn, players, theCasinoTable);

        if (faceCards.find(card) != faceCards.end()) {
            last_face = turn;
            cover_count = faceCards[card] + 1;
            turn = nextPlayerTurn(turn);
        }

        if (cover_count) {
            --cover_count;
            if (!cover_count) {
                playerTakesAllTheCardsInTheTable(last_face, players, theCasinoTable);
                turn = last_face;
            }
        } else {
            turn = nextPlayerTurn(turn);
        }
    }
    return turn;
}
