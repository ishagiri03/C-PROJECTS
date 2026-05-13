#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// Project Description:
// This program implements a simple Blackjack game with AI in C++ using Object Oriented Programming.
// A human player plays against a computer controlled dealer (AI).
// The AI decides whether to Hit or Stand based on simple decision rules.
// The program simulates card dealing, score calculation and win/lose conditions.

class Card {
public:
    int value;

    Card(int v) {
        value = v;
    }
};

class Deck {
public:
    vector<Card> cards;

    Deck() {
        // Create a simple deck (values 1 to 10 repeated)
        for (int i = 1; i <= 10; i++) {
            for (int j = 0; j < 4; j++) {
                cards.push_back(Card(i));
            }
        }
        srand(time(0));
    }

    Card drawCard() {
        int index = rand() % cards.size();
        Card c = cards[index];
        cards.erase(cards.begin() + index);
        return c;
    }
};

class Player {
public:
    vector<Card> hand;

    void addCard(Card c) {
        hand.push_back(c);
    }

    int getScore() {
        int sum = 0;
        for (auto &c : hand)
            sum += c.value;
        return sum;
    }

    void showHand(string name) {
        cout << name << " Hand: ";
        for (auto &c : hand)
            cout << c.value << " ";
        cout << " | Score = " << getScore() << endl;
    }
};

class BlackjackGame {
private:
    Deck deck;
    Player player;
    Player dealer;

public:
    void startGame() {
        cout << "------ Welcome to Blackjack with AI ------\n";

        // Initial two cards
        player.addCard(deck.drawCard());
        player.addCard(deck.drawCard());

        dealer.addCard(deck.drawCard());
        dealer.addCard(deck.drawCard());

        player.showHand("Player");
        dealer.showHand("Dealer");

        // Player turn
        playerTurn();

        // Dealer AI turn
        if (player.getScore() <= 21) {
            dealerTurn();
        }

        // Decide winner
        decideWinner();
    }

    // Player manual turn
    void playerTurn() {
        char choice;

        while (true) {
            if (player.getScore() > 21) {
                cout << "Player Busts!\n";
                return;
            }

            cout << "Do you want to Hit (h) or Stand (s)? ";
            cin >> choice;

            if (choice == 'h') {
                player.addCard(deck.drawCard());
                player.showHand("Player");
            }
            else {
                break;
            }
        }
    }

    // Dealer AI logic (simple AI)
    void dealerTurn() {
        cout << "\nDealer AI Turn...\n";

        // AI Strategy:
        // Hit until score >= 17, then Stand
        while (dealer.getScore() < 17) {
            dealer.addCard(deck.drawCard());
            dealer.showHand("Dealer");
        }
    }

    // Decide final result
    void decideWinner() {
        int pScore = player.getScore();
        int dScore = dealer.getScore();

        cout << "\n------ Final Result ------\n";
        player.showHand("Player");
        dealer.showHand("Dealer");

        if (pScore > 21) {
            cout << "😢 Dealer Wins! Player Busted.\n";
        }
        else if (dScore > 21) {
            cout << "🎉 Player Wins! Dealer Busted.\n";
        }
        else if (pScore > dScore) {
            cout << "🎉 Player Wins!\n";
        }
        else if (dScore > pScore) {
            cout << "😢 Dealer Wins!\n";
        }
        else {
            cout << "🤝 It's a Draw!\n";
        }
    }
};

int main() {
    BlackjackGame game;
    game.startGame();
    return 0;
}
