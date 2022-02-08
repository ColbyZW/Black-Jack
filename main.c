#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct Deck {
    int cards[52];
    int cardsLeft;
};

struct Player {
    int totalHandValue;
    int cards[16];
    int cardIndex;
    int cardsInHand;
};

struct Dealer {
    int totalHandValue;
    int cards[16];
    int cardIndex;
    int cardsInHand;
};


void dealDealer(struct Dealer* deal, struct Deck* d) {
    int deckIndex = (rand()%d->cardsLeft+1);
    //Checks if the index in the array is empty, if so rerolls
    while(d->cards[deckIndex] == 0) {
        deckIndex = (rand()%d->cardsLeft+1);
    }
    //Adds the card from the deck into the player hand
    deal->cards[deal->cardIndex] = d->cards[deckIndex];
    deal->totalHandValue += deal->cards[deal->cardIndex];
    //Sets the card in deck array to 0
    d->cards[deckIndex] = 0;
    d->cardsLeft -= 1;
    //Increments the card index and cards in hand for the player
    deal->cardIndex += 1;
    deal->cardsInHand += 1;
}

void dealPlayer(struct Player* p, struct Deck* d) {
    int deckIndex = (rand()%d->cardsLeft+1);
    //Checks if the index in the array is empty, if so rerolls
    while(d->cards[deckIndex] == 0) {
        deckIndex = (rand()%d->cardsLeft+1);
    }
    //Adds the card from the deck into the player hand
    p->cards[p->cardIndex] = d->cards[deckIndex];
    p->totalHandValue += p->cards[p->cardIndex];
    //Sets the card in deck array to 0
    d->cards[deckIndex] = 0;
    d->cardsLeft -= 1;
    //Increments the card index and cards in hand for the player
    p->cardIndex += 1;
    p->cardsInHand += 1;
}

void initDeck(struct Deck* d) {
    d->cardsLeft = 52;
    int cardCount = 0;
    int suitCount = 0;
    int cardVal = 1;
    int acePresent = 0;
    while(cardCount < 52) {
        if(suitCount == 4) {
            if(cardVal == 11) {
                acePresent = 1;
            }
            suitCount = 0;
            cardVal += 1;
        }
        switch (cardVal) {
            case 11:
                if(acePresent == 1) {
                    cardVal = 10;
                }
                break;
            case 12:
                cardVal = 10;
                break;
            default:
                break;
        }

        d->cards[cardCount] = cardVal;
        cardCount += 1;
        suitCount += 1;
    }
}

void displayDeck(struct Deck* d) {
    for(int i = 0; i < 52; i++) {
        printf("%i, ",d->cards[i]);
    }
}

void run() {
    printf("Welcome to Black Jack, would you like to play? (y/n)\n");
    char choice;
    scanf(" %c", &choice);
    struct Player play;
    play.cardIndex = 0;
    play.cardsInHand = 0;
    play.totalHandValue = 0;
    struct Dealer deal;
    deal.cardIndex = 0;
    deal.cardsInHand = 0;
    deal.totalHandValue = 0;
    struct Deck currDeck;
    initDeck(&currDeck);
    displayDeck(&currDeck);
    if(choice == 'y') {
        dealDealer(&deal,&currDeck);
        dealPlayer(&play,&currDeck);
    } else {
        return;
    }

}

int main() {
    srand(time(0));
    run();
    return 0;
}
