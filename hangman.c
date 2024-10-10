// hangman game

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_ERRORS 5

#define WORD_COUNT 167


char* word_list[WORD_COUNT] = {
    "AATROX", "AHRI", "AKALI", "AKSHAN", "ALISTAR", 
    "AMUMU", "ANIVIA", "ANNIE", "APHELIOS", "ASHE", 
    "AUSOL", "AURORA", "AZIR", "BARD", "BELVETH", 
    "BLITZCRANK", "BRAND", "BRAUM", "BRIAR", "CAITLYN", 
    "CAMILLE", "CASSIOPEIA", "CHOGATH", "CORKI", "DARIUS", 
    "DIANA", "MUNDO", "DRAVEN", "EKKO", "ELISE", 
    "EVELYNN", "EZREAL", "FIDDLESTICKS", "FIORA", "FIZZ",
    "GALIO", "GANGPLANK", "GAREN", "GNAR", "GRAGAS", 
    "GRAVES", "GWEN", "HECARIM", "HEIMERDINGER", "HWEI", 
    "ILLAOI", "IRELIA", "IVERN", "JANA", "JARVAN", "JAX", 
    "JAYCE", "JHIN", "JINX", "KSANTE", "KAISA", "KALISTA", 
    "KARMA", "KARTHUS", "KASSADIN", "KATARINA", "KAYLE", 
    "KAYN", "KENNEN", "KHAZIX", "KINDRED", "KLED", "KOGMAW", 
    "LEBLANC", "LEESIN", "LEONA", "LILLIA", "LISSANDRA", 
    "LUCIAN", "LULU", "LUX", "MALPHITE", "MALZAHAR", 
    "MAOKAI", "MASTERYI", "MILIO", "MISSFORTUNE", 
    "MORDEKAISER", "MORGANA", "NAAFIRI", "NAMI", "NASUS", 
    "NAUTILUS", "NEEKO", "NIDALEE", "NILAH", "NOCTURNE", 
    "NUNU", "OLAF", "ORIANNA", "ORNN", "PANTHEON", "PYKE", 
    "QIYANA", "QUINN", "RAKAN", "RAMMUS", "REKSAI", 
    "RELL", "RENATA", "RENEKTON", "RENGAR", "RIVEN", 
    "RUMBLE", "RYZE", "SAMIRA", "SEJUANI", "SENNA", 
    "SERAPHINE", "SETT", "SHACO", "SHEN", "SHYVANA", 
    "SINGED", "SION", "SIVIR", "SKARNER", "SMOLDER", 
    "SONA", "SORAKA", "SWAIN", "SYLAS", "SYNDRA", 
    "TAHMKENCH", "TALIYAH", "TALON", "TARIC", "TEEMO", 
    "THRESH", "TRISTANA", "TRUNDLE", "TRYNDAMERE", 
    "TWISTEDFATE", "TWITCH", "UDYR", "URGOT", "VARUS", 
    "VAYNE", "VEIGAR", "VELKOZ", "VEX", "VI", "VIEGO", 
    "VIKTOR", "VLADIMIR", "VOLIBEAR", "WARWICK", 
    "WUKONG", "XAYAH", "XERATH", "XINZHAO", "YASUO", 
    "YONE", "YORICK", "YUUMI", "ZAC", "ZED", "ZERI", 
    "ZIGGS", "ZILEAN", "ZOE", "ZYRA"
};
bool chosen_words[WORD_COUNT] = {false};

char* chooseWord() {
    int n;
    do {
    n = rand() % WORD_COUNT;
    } while (chosen_words[n]);

    chosen_words[n] = true;
    return word_list[n];
}

void resetChosenWords() {
    memset(chosen_words, 0, sizeof(chosen_words));
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void printWord(char array[], int length){
    for (int i = 0; i<length; i++){
        printf("%c ", array[i]);
    }
    printf("\n");
}

char playerChoice() {
    char guess = ' ';
    do 
    {
        printf("Guess a letter: ");
        scanf(" %c", &guess); 
        clearInputBuffer();

        guess = toupper(guess); 
    } while (!isalpha(guess)); 

    return guess; 
}

int compareGuess(int m, char arr1[], char arr2[], int k){
    int found_letter_count = 0;
    for (int i = 0; i<k; i++){
        if (m == arr1[i] && arr2[i] == '_'){
            arr2[i] = m;
            found_letter_count++;
        }
    }

    if (found_letter_count == 1){
        printf("\nYou have found a letter in the word!\n");
    } else if (found_letter_count > 0) {
        printf("\nYou have found %d letters in the word!\n", found_letter_count);
    } else {
        printf("\nYour letter was not in the word\n");
        return 1;
    }
    return 0;
}

static char used_letters[26] = {0};

void resetUsedLetters(){
    memset(used_letters, 0, sizeof(used_letters));
}

int checkForRepetition(char c){
    for (int i = 0; i< 26; i++){
        if (c == used_letters[i]){
            return 1;
        }
        if (used_letters[i] == '\0'){ 
            used_letters[i] = c;
            return 0;
        }
    }
    return 0;
}

int startGame() {
    srand((unsigned int)time(NULL));

    // variables
    char* chosen_word = chooseWord();
    int word_length = strlen(chosen_word);
    int errors = 0;

    char display_word[word_length];
        for (int i = 0; i<word_length; i++){
            display_word[i] = '_';                  
        }
    int guessed_correctly = 0;

    //game loop
    while (errors < MAX_ERRORS && guessed_correctly < word_length) 
    {
        guessed_correctly = 0;
        printWord(display_word, word_length);
        char guess = playerChoice();
        if (checkForRepetition(guess)) {
            printf("\nYou have guessed that letter already! \n");
            continue;
        }

        errors+=compareGuess(guess, chosen_word, display_word, word_length);
        for (int i = 0; i < word_length; i++){
            if (display_word[i] != '_') {
                guessed_correctly++;
                //printf("%d \n", guessed_correctly);
            }
        }
        printf("Remaining guesses: %d/%d\n", (MAX_ERRORS - errors), MAX_ERRORS);
    }
    
    if (guessed_correctly == word_length) {
        printf("You win! The word was: %s\n", chosen_word);
        return 1;
    } else {
        printf("You lose! The word was: %s\n", chosen_word);
    } 
    
    return 0;
}


int main(){
    printf("** Welcome to Hangman! ** \n Try to guess the letters with less than %d mistakes \n", MAX_ERRORS);
    char play_again = 'Y';
    int highscore = 0;
    int wins = 0;
    while (play_again == 'Y' && wins < 167)
    {   
        resetUsedLetters();
        int game_result = startGame();

        if (game_result){
            wins += game_result;
            if (highscore < wins){
                highscore = wins;
                }
        } else {
            wins = 0;
            resetChosenWords();
        }    
        
        printf("Highscore: %d\n", highscore);
        printf("Wins: %d\n", wins);
        do
        {
        printf("Play again? Y/n: ");
        scanf(" %c", &play_again);
        clearInputBuffer();
        play_again = toupper(play_again);
        } while (play_again != 'Y' && play_again != 'N');
    } 

    printf("Thanks for playing!\n");
    printf("Highscore: %d\n", highscore);
}