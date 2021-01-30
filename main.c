/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: abdulmoiz
 *
 * Created on March 19, 2020, 6:46 PM
 */

/*
 TEAM PURPLE PENGUINS MEMBERS
 ABDUL MOIZ AMIR - 217210582
 ABDULAZIZ ASHY 217210628
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
/*
 * 
 */
/* Global declarations */ /* Variables */
int charClass;
char lexeme [100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp, *fopen();

/* Function declarations */ void addChar();
void getChar();
void getNonBlank();
int lex();
/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99
/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define KEYWORD 12
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define LESSTHAN 27
#define GREATERTHAN 28


int main(int argc, char** argv) {
    
    /* Open the input data file and process its contents */ if ((in_fp = fopen("front.in", "r")) == NULL)
    printf("ERROR - cannot open front.in \n"); else {
    getChar(); do {
        lex();
    } while (nextToken != EOF);
    }

    return (EXIT_SUCCESS);
}

/*****************************************************/ /* lookup - a function to lookup operators and parentheses
and return the token */ 
int lookup(char ch) {
    switch (ch) 
    {
        case '(':
            addChar();
            nextToken = LEFT_PAREN; break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN; break;
        case '+':
            addChar(); nextToken = ADD_OP; break;
        case '-':
            addChar(); nextToken = SUB_OP; break;
        case '*':
            addChar(); nextToken = MULT_OP; break;

        case '/':
            addChar(); nextToken = DIV_OP; break;
        case '=':
            addChar(); nextToken = ASSIGN_OP; break;
        case '<':
            addChar(); nextToken = LESSTHAN; break;
        case '>':
            addChar(); nextToken = GREATERTHAN; break;
            
        default: 
            addChar(); 
            nextToken = EOF; 
            break;
        }
        return nextToken; 
    }

/*****************************************************/ /* addChar - a function to add nextChar to lexeme */ 
void addChar() {
    if (lexLen <= 98) { 
        lexeme[lexLen++] = nextChar; 
        lexeme[lexLen] = 0;
    }
    else
        printf("Error - lexeme is too long \n"); 
}

/*****************************************************/ /* getChar - a function to get the next character of
input and determine its character class */ 
void getChar() {
    if ((nextChar = getc(in_fp)) != EOF) { 
        if (isalpha(nextChar) || nextChar == '_')
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    }
    else
        charClass = EOF;
 }

/*****************************************************/ /* getNonBlank - a function to call getChar until it
returns a non-whitespace character */ 
void getNonBlank(){
    while (isspace(nextChar)) 
        getChar();
}
/*****************************************************/ /* lex - a simple lexical analyzer for arithmetic
expressions */ 
int lex()
{
    lexLen = 0; 
    getNonBlank(); 
    switch (charClass) {
        /* Parse identifiers */ 
        case (LETTER):
            addChar();
            getChar();
            
            //if(charClass == DIGIT)
                
            
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar(); }
            
            if(strcmp(lexeme, "if") == 0|| strcmp(lexeme, "then") == 0 || strcmp(lexeme, "else") == 0)
                nextToken = KEYWORD;
            else
                nextToken = IDENT; 
            break;
        /* Parse integer literals */ 
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar(); }
            
            if(charClass == LETTER)
            {
                while(charClass == LETTER || charClass == DIGIT)
                {
                    addChar();
                    getChar();
                }
                printf("Error - Illegal literal or identifier %s\n", lexeme);
                exit(0);
            }
            nextToken = INT_LIT; 
            break;
        /* Parentheses and operators */ 
        case UNKNOWN:
            lookup(nextChar); 
            getChar(); 
            break;
        /* EOF */ 
        case EOF:
            nextToken = EOF; 
            lexeme[0] = 'E'; 
            lexeme[1] = 'O'; 
            lexeme[2] = 'F'; 
            lexeme[3] = 0; 
            break;
    } 
    /* End of switch */
    
    printf("Next token is: %d, Next lexeme is %s\n",
                        nextToken, lexeme);
    return nextToken;
} /* End of function lex */
  
