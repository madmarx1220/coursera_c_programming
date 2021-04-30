#include "future.h"
#include <stdio.h>
#include <stdlib.h>

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr) {
  if(index < fc->n_decks) {
    ((fc->decks[index]).n_cards)++;
    (fc->decks[index]).cards = realloc((fc->decks[index]).cards, (fc->decks[index]).n_cards*sizeof(card_t*));
    ((fc->decks[index]).cards)[(fc->decks[index]).n_cards - 1] = ptr;
  }
  else {
    fc->decks = realloc(fc->decks, (index+1)*sizeof(*(fc->decks)));
    for(size_t i=fc->n_decks; i<index; i++) {
      (fc->decks[i]).n_cards = 0;
      (fc->decks[i]).cards = NULL;
    }
    (fc->decks[index]).n_cards = 1;
    ((fc->decks[index]).cards) = malloc(sizeof(*((fc->decks[index]).cards)));
    *((fc->decks[index]).cards) = ptr;
    fc->n_decks = index+1;
  }
}
    
void future_cards_from_deck(deck_t * deck, future_cards_t * fc) {
  if(fc->n_decks > deck->n_cards) {
    fprintf(stderr, "Not enough cards in the deck\n");
  }
  else {
    for(size_t i=0; i<fc->n_decks; i++) {
      for(size_t j=0; j<(fc->decks[i]).n_cards; j++) {
	*(((fc->decks[i]).cards)[j]) = *(deck->cards[i]);
      }
      free((fc->decks[i]).cards);
    }
    free(fc->decks);
  }
}


