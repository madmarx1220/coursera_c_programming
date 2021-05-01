#include "future.h"
#include "input.h"
#include "cards.h"
#include "deck.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char ** argv) {
  if(argc != 2) {
    fprintf(stderr, "please input a file\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if(f == NULL) {
    perror("can't open the file");
    return EXIT_FAILURE;
  }
  size_t n_hands;
  future_cards_t * fc = malloc(sizeof(*fc));
  fc->n_decks = 0;
  fc->decks = NULL;
  deck_t ** decks = read_input(f, &n_hands, fc);
  deck_t * common_deck = build_remaining_deck(decks, n_hands);
  future_cards_from_deck(common_deck, fc);
  for(size_t i=0; i<n_hands; i++) {
    print_hand(decks[i]);
    printf("\n");
    free_deck(decks[i]);
  }
  print_hand(common_deck);
  printf("\n");
  for(size_t i=0; i<fc->n_decks; i++) {
    free((fc->decks[i]).cards);
  }
  free(fc->decks);
  free(fc);
  free(decks);
  free_deck(common_deck);
  fclose(f);
  return EXIT_SUCCESS;
}
