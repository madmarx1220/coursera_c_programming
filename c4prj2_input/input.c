#include "input.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

deck_t * hand_from_string(const char * str, future_cards_t *fc) {
  deck_t * deck = malloc(sizeof(*deck));
  deck->n_cards = 0;
  deck->cards = NULL;
  size_t unknown;
  char value, suit;
  card_t card;
  const char * ptr = str;
  while(*ptr != '\0') {
    if(*ptr == '?') {
      ptr++;
      unknown = *ptr - '0';
      add_future_card(fc, unknown, add_empty_card(deck));
      ptr++;
    }
    if(*ptr == ' ') {
      ptr++;
    }
    else {
      value = *ptr;
      ptr++;
      suit = *ptr;
      ptr++;
      card = card_from_letters(value, suit);
      assert_card_valid(card);
      add_card_to(deck, card);
    }
  }
  if(deck->n_cards < 5) {
    fprintf(stderr, "less than 5 cards per hand");
    exit(EXIT_FAILURE);
  }
  return deck;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t *fc) {
  char * line = NULL;
  size_t sz = 0;
  char * ptr;
  deck_t ** decks = NULL;
  *n_hands = 0;
  while(getline(&line, &sz, f) >=0) {
    ptr = strchr(line, '\n');
    *ptr = '\0';
    (*n_hands) += 1;
    decks = realloc(decks, *n_hands * sizeof(*decks));
    decks[*n_hands - 1] = hand_from_string(line, fc);
  }
  free(line);
  return decks;
}
    
int main() {
  return 1;
}
