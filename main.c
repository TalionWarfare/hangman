/*
 * Shaheer Chaudhry - March 17th, 2025
 * Unique Hangman Game in C
 * Features:
 * - Reads words from word.txt that has engaging pop culture words
 * - Random word selection
 * - ASCII art representation of the hangman
 * - Interactive guessing with limb progression
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_LENGTH 50
#define MAX_ATTEMPTS 6
#define WORD_FILE "words.txt"

const char *WIN_SCREEN = "\n"
    " \\\\\\|||///\n"
    " .  =======\n"
    "/ \\| O   O |\n"
    "\\ / \\  ∧  /\n"
    " #   \\ - /\n"
    "    |  |  |\n"
    "    |___|_|\n"
    "\nYOU WIN!\n";

const char *LOSE_SCREEN = "\n"
    "    ________\n"
    "   |        |\n"
    "   |        |\n"
    "   |       ***\n"
    "   |      *o o*\n"
    "   |      * ∧ *\n"
    "   |     *  -  *\n"
    "   |      *****\n"
    "   |        |\n"
    "   |     RIP\n"
    "   |        |\n"
    "  /|\\      /|\\\n"
    " / | \\    / | \\\n"
    "\nGAME OVER!\n";

// ASCII Art for the hangman stages
const char *HANGMAN_STAGES[] = {
    "\n  +---+\n      |\n      |\n      |\n     ===\n",
    "\n  +---+\n  O   |\n      |\n      |\n     ===\n",
    "\n  +---+\n  O   |\n  |   |\n      |\n     ===\n",
    "\n  +---+\n  O   |\n /|   |\n      |\n     ===\n",
    "\n  +---+\n  O   |\n /|\\  |\n      |\n     ===\n",
    "\n  +---+\n  O   |\n /|\\  |\n /    |\n     ===\n",
    "\n  +---+\n  O   |\n /|\\  |\n / \\  |\n     ===\n"
};

// Function to get a random word from the file
char *get_random_word() {
    static char word[MAX_WORD_LENGTH];
    FILE *file = fopen(WORD_FILE, "r");
    if (!file) {
        printf("Error: Could not open word file.\n");
        exit(1);
    }
    
    char words[100][MAX_WORD_LENGTH];
    int count = 0;
    while (fgets(words[count], MAX_WORD_LENGTH, file)) {
        words[count][strcspn(words[count], "\n")] = 0; // Remove newline
        count++;
    }
    fclose(file);
    
    srand(time(NULL));
    strcpy(word, words[rand() % count]);
    return word;
}

// Function to display the current game state
void display_game(const char *word, const char *guessed, int attempts) {
    printf("%s\n", HANGMAN_STAGES[attempts]);
    
    for (int i = 0; word[i] != '\0'; i++) {
        if (strchr(guessed, word[i])) {
            printf("%c ", word[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n\n");
}

void play_game() {
    char word[MAX_WORD_LENGTH];
    strcpy(word, get_random_word());
    
    char guessed[MAX_WORD_LENGTH] = "";
    int attempts = 0;
    
    while (attempts < MAX_ATTEMPTS) {
        display_game(word, guessed, attempts);
        
        printf("Guess a letter: ");
        char guess;
        scanf(" %c", &guess);
        
        if (strchr(guessed, guess)) {
            printf("You already guessed that letter!\n");
            continue;
        }
        
        strncat(guessed, &guess, 1);
        
        if (!strchr(word, guess)) {
            attempts++;
        }
        
        int won = 1;
        for (int i = 0; word[i] != '\0'; i++) {
            if (!strchr(guessed, word[i])) {
                won = 0;
                break;
            }
        }
        
        if (won) {
            display_game(word, guessed, attempts);
            printf("%s\n", WIN_SCREEN);
            printf("Congratulations! You saved the hangman!\n");
            printf("The word was: %s\n", word);
            return;
        }
    }
    
    display_game(word, guessed, MAX_ATTEMPTS);
    printf("%s\n", LOSE_SCREEN);
    printf("Oh no! The hangman couldn't be saved!\n");
    printf("The word was: %s\n", word);
}

int main() {
    char play_again = 'y';
    
    while (play_again == 'y' || play_again == 'Y') {
        printf("\n=== Shaheer Chaudhry - Hangman Game (March 17th, 2025) ===\n\n");
        play_game();
        
        printf("\nWould you like to play again? (Y/N): ");
        scanf(" %c", &play_again);
        
        // Clear the screen for a new game
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
    
    printf("\nThanks for playing! Goodbye!\n");
    return 0;
}
