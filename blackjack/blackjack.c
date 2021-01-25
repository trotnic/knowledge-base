#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <memory.h>
#include <time.h>

#include "../structs/stack.h"
#include "blackjack.h"

// -

static Stack *cards;
static UserSession *session;

int main(int argc, char const *argv[])
{   
    show_menu();
    return 0;
}

void print_card(Card *card) {
    printf("%s%s%s%s%s%s%s\n", top_left_corner, horizontal_dash, horizontal_dash, horizontal_dash, horizontal_dash, horizontal_dash, top_right_corner);
    printf("%s%s%7s\n", vertical_dash, card->suite, vertical_dash);
    printf("%s%3s%5s\n", vertical_dash, card->mark, vertical_dash);
    printf("%s%9s%4s\n", vertical_dash, card->suite, vertical_dash);
    printf("%s%s%s%s%s%s%s\n", bot_left_corner, horizontal_dash, horizontal_dash, horizontal_dash, horizontal_dash, horizontal_dash, bot_right_corner);
}

void game_cycle(void) {
    setup();
    int choice;
    do {
        printf("Current count is %d\n", session->total);
        puts("Make your choice:");
        puts("1. Pull a card");
        puts("2. Stop");
        scanf("%d", &choice);
        if (choice == 1) {
            Card *card = (Card *)pop(cards);
            if (card == NULL) {
                puts("No cards remained");
                break;
            }
            session->total += card->value;
            puts("Your drop is:");
            print_card(card);
        } else if (choice == 2) {
            break;
        }
        if (session->total > 21) {
            break;
        }
    } while(true);
    printf("Your final goal is %d\n", session->total);
    if (session->total > 21) {
        puts("You lost 😟");
    } else if (session->total == 21) {
        puts("You won 🤩");
    }
}

void setup() {
    Card *setup_cards[52];

    session = malloc(sizeof(UserSession));
    session->cards = malloc(sizeof(*setup_cards));
    session->total = 0;

    for (size_t i = 0; i < 52; i++) {
        Card *card = malloc(sizeof(Card));
        if (card == NULL) {
            printf("NULL\n");
        }
        card->suite = suite(i / 13);
        card->mark = mark(i % 13);
        card->value = i % 13 == 0 ? 10 : i % 13;
        setup_cards[i] = card;
        
    }
    shuffle(setup_cards, time(0), 0, 52, sizeof(*setup_cards));
    for (size_t i = 0; i < 52; i++)
    {
        if (cards == NULL) {
            init(&cards, setup_cards[i]);
        } else {
            push(cards, setup_cards[i]);
        }
    }
}

void show_menu() {
    int choice;
    do {        
        puts("Black Jack game menu:");
        puts("1. Start game");
        puts("2. Quit game");
        scanf("%d", &choice);
        if (choice == 1) {
            game_cycle();
        } else if (choice == 2) return;
    } while(true);       
}

const char *suite(Suites suite) {
    switch (suite) {
    case SPADE:     return spade;
    case HEART:     return heart;
    case DIAMOND:   return diamond;
    case CLUB:      return club;
    default: return NULL;
    }
}

const char *mark(int value) {
    switch (value) {
    case 0:     return ace;
    case 1:     return two;
    case 2:     return three;
    case 3:     return four;
    case 4:     return five;
    case 5:     return six;
    case 6:     return seven;
    case 7:     return eight;
    case 8:     return nine;
    case 9:     return ten;
    case 10:    return jack;
    case 11:    return queen;
    case 12:    return king;
    default: return NULL;
    }
}

void swappy(void * a, void * b, size_t size)
{
	void * temp = malloc(size);
	memcpy(temp, a, size);
	memcpy(a, b, size);
	memcpy(b, temp, size);
	free(temp);
}

void * shuffle(void * array, int seed, int index, int len, size_t size)
{
	int result;
	if(index == len) return array;
	srand(seed);
	result = rand();
	swappy((array + index * size), (array + result%len * size), size);
	return shuffle(array, result, index + 1, len, size);
}