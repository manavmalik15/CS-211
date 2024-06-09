/*
Project: WORD LADDER
Author: Manav Malik
Date: 4 april 2024
Coding platform: Xcode
Class: CS 211, 4 pm
Professor: Scott Reckinger
Description:
A word ladder is a bridge between one word and another,
formed by changing one letter at a time to reach the final
word in fixed moves, with the constraint that at each step
the sequence of letters still forms a valid word.
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct WordNode_struct {
    char* myWord;
    struct WordNode_struct* next;
} WordNode;





typedef struct LadderNode_struct {
    WordNode* topWord;
    struct LadderNode_struct* next;
} LadderNode;

int countWordsOfLength(char* filename, int wordSize) {
    FILE* fileTry = fopen(filename,"r");
    
    while (fileTry == NULL) {
        return -1;
    }
    
    int sum = 0;
    
    char data[100];
    do {
        fgets(data ,100, fileTry );
        if (!feof(fileTry)){
            data[(int)strlen(data)-1]='\0';
            };
        if ((int)strlen(data)== (wordSize)){
            sum++;
        }
     
    }while(!feof(fileTry));
    fclose(fileTry);
    return sum;
};

bool buildWordArray(char* filename, char** words, int numWords, int wordSize) {
    FILE* fileTry = fopen(filename,"r");
    
    while (fileTry == NULL) {
        return false;
    }
    
    int sum = 0;
    
    char data[100];
    do {
        fgets(data ,100, fileTry );
        
        if (!feof(fileTry)){
            data[(int)strlen(data)-1]='\0';
            };
        
        if ((int)strlen(data)== (wordSize)){
            strcpy(words[sum], data);
            sum++;
        }
     
    }while(!feof(fileTry));
    fclose(fileTry);
    
    return (sum==numWords);
};

int findWord(char** words, char* aWord, int loInd, int hiInd) {
    if (hiInd >= loInd) {
        int mid = loInd + (hiInd - loInd) / 2;

        int check = strcmp(aWord, words[mid]);

        if (check == 0) {
            return mid;
        }
        
        if (check > 0) {
            return findWord(words, aWord, mid + 1, hiInd);
        }

        return findWord(words, aWord, loInd, mid - 1);
    }

    return -1;
};

void freeWords(char** words, int numWords) {
    for (int i=0 ; i< numWords ; i++){
        free(words[i]);
    }
    free(words);
};

void insertWordAtFront(WordNode** ladder, char* newWord) {

    WordNode* newNode = (WordNode*)malloc(sizeof(WordNode));
    
    newNode->myWord = newWord;
    newNode->next = *ladder;
    *ladder = newNode;
    
};


int getLadderHeight(WordNode* ladder) {

    int i=0;
    WordNode* current = ladder;
    while(current){
        current =current->next;
        i++;
    }
    
    return i; // modify this line
};

WordNode* copyLadder(WordNode* ladder) {
    
    if (!ladder) {
        return NULL;
    }

    WordNode* new_ladder = (WordNode*)malloc(sizeof(WordNode));
    new_ladder->myWord = ladder->myWord;
    new_ladder->next = NULL;

    WordNode* new_curr = new_ladder;
    WordNode* old_curr = ladder->next;

    while (old_curr) {
        new_curr->next = (WordNode*)malloc(sizeof(WordNode));
        new_curr = new_curr->next;
        new_curr->myWord = old_curr->myWord;
        new_curr->next = NULL;
        old_curr = old_curr->next;
    }

    return new_ladder;
    

};

void freeLadder(WordNode* ladder) {

    WordNode* current = ladder;
    while(current){
        WordNode* temp = current;
        current =current->next;
        //free(temp->myWord);
        free(temp);
    };
    
};

void insertLadderAtBack(LadderNode** list, WordNode* newLadder) {
    
    LadderNode* newNode = (LadderNode*)malloc(sizeof(LadderNode));
    newNode->topWord = newLadder;
    newNode->next = NULL;
    if (*list == NULL ) {
        *list = newNode;
        return;
    }
    LadderNode* cur = *list;
    while(cur->next !=NULL){
        cur = cur->next;
    }
    cur->next = newNode;
}

WordNode* popLadderFromFront(LadderNode** list) {
    if (*list == NULL){
        return NULL;
    };
    LadderNode* tobe = *list;
    WordNode* ret = tobe->topWord;
    *list = ((*list)->next);
    free(tobe);
    return ret;
}

void freeLadderList(LadderNode* myList) {
    //---------------------------------------------------------
    // TODO - write freeLadderList()
    //          free up all heap-allocated space for <myList>;
    //          for each ladder in <myList>:
    //           - free the space allocated for each [WordNode]
    //                  in the ladder using freeLadder()
    //           - then, free the space allocated for the
    //                  [LadderNode] itself
    //---------------------------------------------------------
    
    LadderNode* current = myList;
    while(current){
        freeLadder(popLadderFromFront(&current));
    };

    
}



//num diffrent char in 2 strings
int strNumMods(char* str1, char* str2) {
    unsigned long diffrence = 0;
    int i=0;
    while(str1[i] !='\0' && str2[i] !='\0'  ){
        if (str1[i]!=str2[i]){
            diffrence++;
        };
        i++;
    }
    if (strlen(str2)>strlen(str1)){
    diffrence = diffrence + strlen(str2)-strlen(str1);
    }else {
        diffrence = diffrence + strlen(str1)-strlen(str2);
    }
    
    return ((int)diffrence);
}


// helpful debugging function to print a single Ladder
void printLadder(WordNode* ladder) {
    WordNode* currNode = ladder;
    while (currNode != NULL) {
        printf("\t\t\t%s\n",currNode->myWord);
        currNode = currNode->next;
    }
}






bool recursionsmall(char** words,
                   bool* usedWord,
                   int numWords,
                   int wordSize,
                   char* startWord,
                   char* finalWord,
                   WordNode** ladder
                   ){
    
    
    if (strcmp(startWord,finalWord) == 0){
            return true;
        }
    
    char* w_tobe[numWords];
    int num_tobe = 0;
    for (int i=0;i<numWords;i++){
        if ((strNumMods(startWord,words[i])==1 ) && (!usedWord[i]) ){
            usedWord[i] = true;
            w_tobe[num_tobe] = words[i];
            printf("%s\n", words[i]);
            num_tobe++;
        }
    }
    
    printf("bbbbddddddddddd\n");
    
    
    WordNode* preveous = NULL;
    for( int i=0 ; i<num_tobe; i++){
        
        
        
        
        
        bool* usedWord_copy = (bool*)malloc(numWords*sizeof(bool));
        for (int i = 0; i < numWords; ++i) {
            usedWord_copy[i] = usedWord[i];
        }
        
        
        
        WordNode* temp = copyLadder(*ladder);
        insertWordAtFront(&temp, w_tobe[i]);
        
        if ( recursionsmall(words,usedWord,numWords, wordSize, w_tobe[i],finalWord,&temp)){
            if (preveous== NULL || (getLadderHeight(preveous) > getLadderHeight(temp))){
                
                printLadder(temp);
                printf("\n\n");
                
                if (preveous!=NULL){freeLadder(preveous);}
                
                preveous = copyLadder(temp);
                
                
                
            }else{
                freeLadder(temp);
            }
            
        }
        free(usedWord_copy);
    }
    if (preveous==NULL){return false;}
    
    freeLadder(*ladder);
    *ladder = copyLadder(preveous);
    freeLadder(preveous);
    
    return true;
}
//
//int recursionsmall(char** words,
//                   bool* usedWord,
//                   int numWords,
//                   int wordSize,
//                   char* startWord,
//                   char* finalWord,
//                   WordNode** ladder
//                   ){
//    
//    // break
//    if (strcmp(startWord,finalWord) == 0){
//        return 2;
//    }
//
//    char* groupofwords[numWords];
//    
//    LadderNode* group_of_laders = NULL; // add momization
//    int numWords_tobe = 0;
//    for (int i=0;i<numWords;i++){
//        // find all the words that are 1 diffrent from the start and are not used;
//        if ((strNumMods(startWord,words[i])==1 ) && (!usedWord[i]) ){
//            usedWord[i] = true;
//            groupofwords[numWords_tobe] = words[i];
//            numWords_tobe++;
//        };
//    };
//    
//    
//    
//    
//    for (int i=0;i<numWords_tobe;i++){
//        WordNode* temp = copyLadder(*ladder);
//        insertWordAtFront(&temp,groupofwords[i]);
//        printf("%s\n",groupofwords[i]);
//        
//        int with_word = recursionsmall(words,usedWord,numWords, wordSize, groupofwords[i],finalWord,&temp);
//        if (with_word!= -1){
//            insertLadderAtBack(&group_of_laders,temp);
//        };
//        
//        
//        freeLadder(temp);
//        
//    }
//    printf("\n");
//    
//    
//    
//    LadderNode* curr = group_of_laders;
//    
//    if (curr == NULL){
//        return -1;
//    };
//    
//    int iff=0;
//    WordNode* small = copyLadder(curr->topWord);
//    while(curr){
//        iff++;
//        if (getLadderHeight(small)>getLadderHeight(curr->topWord)){
//            small = copyLadder(curr->topWord);
//        };
//        curr = curr->next;
//    }
//    
//    *ladder = copyLadder(small);
//    
//    freeLadderList(group_of_laders);
//    
//    
//    printf("%d",iff);
//    
//    return 2;
//}







WordNode* findlongestWordLadder(char** words,bool* usedWord,int numWords,int wordSize, char* startWord,char* finalWord) {
//WordNode* findShortestWordLadder(char** words,bool* usedWord,int numWords,int wordSize, char* startWord,char* finalWord) {

    for (int i=0;i<numWords;i++){
        usedWord[i]=false;
    };
    //---------------------------------------------------------
    // TODO - write findShortestWordLadder()
    //          run algorithm to find the shortest word ladder
    //          from <startWord> to <finalWord> in the <words>
    //          word array, where each word is <wordSize> long
    //          and there are <numWords> total words;
    //          <usedWord> also has size <numWords>, such that
    //          usedWord[i] is only true if words[i] has
    //          previously be entered into a ladder, and should
    //          therefore not be added to any other ladders;
    //          the algorithm creates partial word ladders,
    //          which are [WordNode] linked lists, and stores
    //          them in a [LadderNode] linked list.
    //              return a pointer to the shortest ladder;
    //              return NULL if no ladder is possible;
    //                  before return, free all heap-allocated
    //                  memory that is created here that is not
    //                  the returned ladder
    //---------------------------------------------------------

    WordNode* ladder = NULL;
    insertWordAtFront(&ladder, startWord);
    
    if (! recursionsmall(words, usedWord, numWords, wordSize, startWord, finalWord, &ladder) ) {
        freeLadder(ladder);
        return NULL;
    }
    
    return ladder;
    
};







//
WordNode* findShortestWordLadder(char** words, bool* usedWord, int numWords, int wordSize, char* startWord, char* finalWord) {
    LadderNode* myList = NULL;
    WordNode* myLadder = NULL;
    insertWordAtFront(&myLadder, startWord);
    insertLadderAtBack(&myList, myLadder);
    
    
    int In = findWord(words, startWord, 0, numWords-1);
    if (In >= 0) {
        usedWord[In] = true;
    }
    
    
    while (myList != NULL) {
        
        WordNode* myLadder = popLadderFromFront(&myList);
        char* topWord = myLadder->myWord;
        
        if (strcmp(topWord, finalWord) == 0) {
            
            freeLadderList(myList);
            return myLadder;
        }
        for (int i = 0; i < wordSize; ++i) {
            for (char chr = 'a'; chr <= 'z'; ++chr) {
                
                if (topWord[i] != chr) {
                    char newWord[wordSize + 1];
                    
                    strcpy(newWord, topWord);
                    
                    newWord[i] = chr;
                    int newIndex = findWord(words, newWord, 0, numWords - 1);
                        if (newIndex >= 0 && !usedWord[newIndex]) {
                            
                            usedWord[newIndex] = true;
                            
                            WordNode* anotherLadder = copyLadder(myLadder);
                            insertWordAtFront(&anotherLadder, words[newIndex]);
                            insertLadderAtBack(&myList, anotherLadder);
                        }
                }
                
            }
        }
        freeLadder(myLadder);
    }
    return NULL;
}







// interactive user-input to set a word;
//  ensures sure the word is in the dictionary word array
void setWord(char** words, int numWords, int wordSize, char* aWord) {
    bool valid = false;
    printf("  Enter a %d-letter word: ", wordSize);
    int count = 0;
    while (!valid) {
        scanf("%s",aWord);
        count++;
        valid = (strlen(aWord) == wordSize);
        if (valid) {
            int wordInd = findWord(words, aWord, 0, numWords-1);
            if (wordInd < 0) {
                valid = false;
                printf("    Entered word %s is not in the dictionary.\n",aWord);
                printf("  Enter a %d-letter word: ", wordSize);
            }
        } else {
            printf("    Entered word %s is not a valid %d-letter word.\n",aWord,wordSize);
            printf("  Enter a %d-letter word: ", wordSize);
        }
        if (!valid && count >= 5) { //too many tries, picking random word
            printf("\n");
            printf("  Picking a random word for you...\n");
            strcpy(aWord,words[rand()%numWords]);
            printf("  Your word is: %s\n",aWord);
            valid = true;
        }
    }
}



// helpful debugging function to print the entire list of Ladders
void printList(LadderNode* list) {
    printf("\n");
    printf("Printing the full list of ladders:\n");
    LadderNode* currList = list;
    while (currList != NULL) {
        printf("  Printing a ladder:\n");
        printLadder(currList->topWord);
        currList = currList->next;
    }
    printf("\n");
}


//-----------------------------------------------------
// The primary application is fully provided in main();
//  no changes should be made to main()
//-----------------------------------------------------
int main(void) {
    srand((int)time(0));
    
    printf("\nWelcome to the CS 211 Word Ladder Generator!\n\n");
    
    // set word length using interactive user-input
    int wordSize;
    printf("Enter the word size for the ladder: ");
    scanf("%d",&wordSize);
    printf("\n");
    
    printf("This program will make the shortest possible\n");
    printf("word ladder between two %d-letter words.\n\n",wordSize);
    
    // interactive user-input sets the dictionary file;
    //  check that file exists; if not, user enters another file
    //  if file exists, count #words of desired length [wordSize]
    char dict[100] = "dictionary.txt";
    printf("Enter filename for dictionary: ");
    //scanf("%s", dict);
    printf("\n");
    int numWords = countWordsOfLength(dict,wordSize);
    while (numWords < 0) {
        printf("  Dictionary %s not found...\n",dict);
        printf("Enter filename for dictionary: ");
        scanf("%s", dict);
        printf("\n");
        numWords = countWordsOfLength(dict,wordSize);
    }
    
    // allocate heap memory for the word array; only words with desired length
    char** words = (char**)malloc(numWords*sizeof(char*));
    for (int i = 0; i < numWords; ++i) {
        words[i] = (char*)malloc((wordSize+1)*sizeof(char));
    }
    
    // end program if file does not have at least two words of desired length
    if (numWords < 2) {
        printf("  Dictionary %s contains insufficient %d-letter words...\n",dict,wordSize);
        printf("Terminating program...\n");
        return -1;
    }
    
    // [usedWord] bool array has same size as word array [words];
    //  all elements initialized to [false];
    //  later, usedWord[i] will be set to [true] whenever
    //      words[i] is added to ANY partial word ladder;
    //      before adding words[i] to another word ladder,
    //      check for previous usage with usedWord[i]
    bool* usedWord = (bool*)malloc(numWords*sizeof(bool));
    for (int i = 0; i < numWords; ++i) {
        usedWord[i] = false;
    }
    
    // build word array (only words with desired length) from dictionary file
    printf("Building array of %d-letter words... ", wordSize);
    bool status = buildWordArray(dict,words,numWords,wordSize);
    if (!status) {
        printf("  ERROR in building word array.\n");
        printf("  File not found or incorrect number of %d-letter words.\n",wordSize);
        printf("Terminating program...\n");
        return -1;
    }
    printf("Done!\n");
    
    // set the two ends of the word ladder using interactive user-input
    //  make sure start and final words are in the word array,
    //  have the correct length (implicit by checking word array), AND
    //  that the two words are not the same
    char startWord[30];
    char finalWord[30];
    printf("Setting the start %d-letter word... \n", wordSize);
    setWord(words, numWords, wordSize, startWord);
    printf("\n");
    printf("Setting the final %d-letter word... \n", wordSize);
    setWord(words, numWords, wordSize, finalWord);
    while (strcmp(finalWord,startWord) == 0) {
        printf("  The final word cannot be the same as the start word (%s).\n",startWord);
        printf("Setting the final %d-letter word... \n", wordSize);
        setWord(words, numWords, wordSize, finalWord);
    }
    printf("\n");
    
    // run the algorithm to find the shortest word ladder
    WordNode* myLadder = findlongestWordLadder(words, usedWord, numWords, wordSize, startWord, finalWord);
    
    // display word ladder and its height if one was found
    if (myLadder == NULL) {
        printf("There is no possible word ladder from %s to %s\n",startWord,finalWord);
    } else {
        printf("Shortest Word Ladder found!\n");
        printLadder(myLadder);
    }
    printf("Word Ladder height = %d\n",getLadderHeight(myLadder));
    
    // free the heap-allocated memory for the shortest ladder
    freeLadder(myLadder);
    // free the heap-allocated memory for the words array
    freeWords(words,numWords);
    free(usedWord);
    
    
    return 0;
}
