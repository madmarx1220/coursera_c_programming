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

void add_card_to(deck_t * deck, card_t c) {
  deck->n_cards++;
  deck->cards = realloc(deck->cards, deck->n_cards * sizeof(*deck->cards));
  card_t * card = malloc(sizeof(*card));
  *card = c;
  deck->cards[deck->n_cards-1] = card;
}

card_t * add_empty_card(deck_t * deck) {
  card_t c;
  c->value = 0;
  c->suit = 0;
  add_card_to(deck, c);
  return deck->cards[deck->n_cards-1];
}

deck_t * make_deck_exclude(deck_t * excluded_cards) {
  deck_t * deck = malloc(sizeof(*deck));
  card_t c;
  deck->n_cards = 0;
  deck->cards = NULL;
  for(int i=0; i<52; i++) {
    c = card_from_num(i);
    if(deck_contains(excluded_cards, c) == 0) {
      add_card_to(deck, c);
    }
  }
  return deck;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
  deck_t * deck = malloc(sizeof(*deck));
  deck->n_cards = 0;
  deck->cards = NULL;
  for(size_t i=0; i<n_hands; i++) {
    for(size_t j=0; j<(hands[i])->n_cards; j++) {
      if(((((hands[i])->cards)[j])->value != 0)
	 && (!deck_contains(deck, *((hands[i])->cards)[j]))) {
	add_card_to(deck, *((hands[i])->cards)[j]);
      }
    }
  }
  deck_t * d = make_deck_exclude(deck);
  free_deck(deck);
  return d;
}

void free_deck(deck_t * deck) {
  for(size_t i=0; i<deck->n_cards; i++) {
    free(deck->cards[i]);
  }
  free(deck->cards);
  free(deck);
}
