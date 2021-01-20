#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){
  card_t ** ptr = hand->cards;
  for(int i=0; i < hand->n_cards; i++) {
    print_card(**ptr);
    printf(" ");
    ptr++;
  }
}

int deck_contains(deck_t * d, card_t c) {
  card_t ** ptr = d->cards;
  for(int i=0; i < d->n_cards; i++) {
    if(((**ptr).value == c.value) && ((**ptr).suit == c.suit)) {
      return 1;
    }
    ptr++;
  }
  return 0;
}

void shuffle(deck_t * d){
  card_t ** ptr = d->cards;
  card_t * temp;
  int idx;
  for(int i=0; i < d->n_cards; i++) {
    temp = ptr[i];
    idx = random() % (d->n_cards);
    ptr[i] = ptr[idx];
    ptr[idx] = temp;
  }
}

void assert_full_deck(deck_t * d) {
  for(int i=0; i < 52; i++) {
    card_t c = card_from_num(i);
    assert(deck_contains(d, c));
  }
}
