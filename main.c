/*
 * Shaheer Chaudhry - March 17th, 2025
 * Pop Culture Hangman Game in C
 * Features:
 * - Randomly selects words from 'words.txt'
 * - Interactive guessing with ASCII visuals
 * - Tracks incorrect guesses with a hangman progression
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_LENGTH 50
#define MAX_ATTEMPTS 6
#define WORD_FILE "words.txt"

// ASCII art for game stages
const char *HANGMAN_STAGES[] = {
    "\n  +---+\n      |\n      |\n      |\n     ===\n",
    "\n  +---+\n  O   |\n      |\n      |\n     ===\n",
    "\n  +---+\n  O   |\n  |   |\n      |\n     ===\n",
    "\n  +---+\n  O   |\n /|   |\n      |\n     ===\n",
    "\n  +---+\n  O   |\n /|\\  |\n      |\n     ===\n",
    "\n  +---+\n  O   |\n /|\\  |\n /    |\n     ===\n",
    "\n  +---+\n  O   |\n /|\\  |\n / \\  |\n     ===\n"
};

// Retrieves a random word from the file
char *get_random_word() {
    FILE *file = fopen(WORD_FILE, "r");
    if (!file) {
        printf("Error: Could not open word file.\n");
        exit(1);
    }

    char **words = malloc(100 * sizeof(char *));
    int count = 0;
    char buffer[MAX_WORD_LENGTH];

    while (fgets(buffer, MAX_WORD_LENGTH, file)) {
        buffer[strcspn(buffer, "\n")] = 0;
        words[count] = strdup(buffer);
        count++;
    }
    fclose(file);

    srand(time(NULL));
    char *selected_word = strdup(words[rand() % count]);

    for (int i = 0; i < count; i++) free(words[i]);
    free(words);
    return selected_word;
}

// Displays the current game state
void display_game(const char *word, const char *guessedLetters, int attempts) {
    printf("%s\n", HANGMAN_STAGES[attempts]);
    for (int i = 0; word[i] != '\0'; i++) {
        printf("%c ", strchr(guessedLetters, word[i]) ? word[i] : '_');
    }
    printf("\n\n");
}

// Main game logic
void play_game() {
    char *word = get_random_word();
    char guessedLetters[MAX_WORD_LENGTH] = "";
    int attempts = 0;

    while (attempts < MAX_ATTEMPTS) {
        display_game(word, guessedLetters, attempts);
        printf("Guess a letter: ");
        char guess;
        scanf(" %c", &guess);

        if (strchr(guessedLetters, guess)) {
            printf("You already guessed that letter!\n");
            continue;
        }

        strncat(guessedLetters, &guess, 1);
        if (!strchr(word, guess)) attempts++;

        if (strspn(word, guessedLetters) == strlen(word)) {
            printf("\nCongrats! The word was: %s\n", word);
            free(word);
            return;
        }
    }
    printf("\nGame Over! The word was: %s\n", word);
    free(word);
}

int main() {
    char playAgain;
    do {
        printf("\n=== Hangman Game - Pop Culture Edition ===\n\n");
        play_game();
        printf("\nPlay again? (Y/N): ");
        scanf(" %c", &playAgain);
    } while (playAgain == 'y' || playAgain == 'Y');
    printf("\nThanks for playing!\n");
    return 0;
}
