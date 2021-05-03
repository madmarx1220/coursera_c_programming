#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"



int main(int argc, char ** argv) {
  unsigned num_trials;
  size_t n_hands;
  if(argc == 2) {
    num_trials = 10000;
  }
  else if(argc == 3) {
    num_trials = (unsigned)atoi(argv[2]);
  }
  else {
    fprintf(stderr, "please input a correct number of arguments");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if(f == NULL) {
    perror("can't open the file");
  }
  future_cards_t * fc = malloc(sizeof(*fc));
  fc->n_decks = 0;
  fc->decks = NULL;
  deck_t ** decks = read_input(f, &n_hands, fc);
  unsigned win_array[n_hands+1];
  for(size_t i=0; i<n_hands+1; i++) {
    win_array[i] = 0;
  }
  deck_t * remain = build_remaining_deck(decks, n_hands);
  for(int i=0; i<num_trials; i++) {
    shuffle(remain);
    future_cards_from_deck(remain, fc);
    size_t max = 0;
    unsigned draw = 0;
    for(size_t j=1; j<n_hands; j++) {
      if(compare_hands(decks[j], decks[max]) > 0) {
	max = j;
	draw = 0;
      }
      else if(compare_hands(decks[j], decks[max]) == 0) {
	draw++;
      }
      else {
	draw = 0;
      }
    }
    if(draw == n_hands-1) {
      (win_array[n_hands])++;
    }
    else {
      (win_array[max])++;
    }
  }
  for(size_t i=0; i<n_hands; i++) {
    printf("Hand %zu won %u / %u times (%.2f%%)\n", i, win_array[i], num_trials, (float)win_array[i]/num_trials*100);
    free_deck(decks[i]);
  }
  printf("And there were %u ties\n", win_array[n_hands]);
  free(decks);
  for(size_t i=0; i<fc->n_decks; i++) {
    free((fc->decks[i]).cards);
  }
  free(fc->decks);
  free(fc);
  free_deck(remain);
  fclose(f);
  return EXIT_SUCCESS;
}
