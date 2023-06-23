#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<conio.h>
#define MAX_WORD_LENGTH 32
#define MAX_TOKEN_QUANTITY 1024
#define MAX_STACK_SIZE 2048
#define ACCEPT 100
#define ERROR -100

int stack[MAX_STACK_SIZE];
int stackPointer = -1;
void push(int item)
{
	if(stackPointer >= MAX_STACK_SIZE)
	{
		printf("\nStack Overflow...\n");
		exit(0);
	}
	stackPointer++;
	stack[stackPointer] = item;
	//printf("\nPush -> %d", item);
}
void pop()
{
	if(stackPointer <= -1)
	{
		printf("\nStack Underflow...\n");
		exit(0);
	}
	//printf("\nPop -> %d", stack[stackPointer]);
	stackPointer--;
}
int lookTop()
{
	if(stackPointer <= -1)
	{
		printf("\nStack is Empty...\n");
		exit(0);
	}
	return(stack[stackPointer]);
}


char generateToken(char *word, int length)
{
	char token = '\0';
	
	switch(length)
	{
		case 1:
			if(word[0] == '(') token = 'b';
			else if(word[0] == ')') token = 'c';
			else if(word[0] == '{') token = 'd';
			else if(word[0] == ';') token = 'f';
			else if(word[0] == '}') token = 'g';
			else if(word[0] == ',') token = 'i';
			else if(word[0] == '=') token = 'k';
			else if(word[0] == '?') token = 'l';
			else if(word[0] == ':') token = 'm';
			else if(word[0] == '+') token = 'p';
			else if(word[0] == '-') token = 'p';
			else if(word[0] == '*') token = 'p';
			else if(word[0] == '>') token = 'p';
			else if(word[0] == '<') token = 'p';
			break;
		case 2:
			if(word[0] == '=' && word[1] == '=') token = 'p';
			break;
		case 3:
			if(word[0] == 'i' && word[1] == 'n' && word[2] == 't') token = 'j';
			else if(word[0] == 'g' && word[1] == 'e' && word[2] == 't') token = 'n';
			else if(word[0] == 'p' && word[1] == 'u' && word[2] == 't') token = 'n';
			else if(word[0] == '\'' && word[2] == '\'') token = 'o';
			break;
		case 4:
			if(word[0] == 'm' && word[1] == 'a' && word[2] == 'i' && word[3] == 'n') token = 'a';
			else if(word[0] == 'c' && word[1] == 'h' && word[2] == 'a' && word[3] == 'r') token = 'j';
			break;
		case 5:	token = '\0';
			break;
		case 6:
			if(word[0] == 'r' && word[1] == 'e' && word[2] == 't' && word[3] == 'u' && word[4] == 'r' && word[5] == 'n') token = 'e';
			break;
		default: token = '\0'; break;
	}
	
	if(token == '\0')
	{
	
		if(word[0] >= '0' && word[0] <= '9')		// is constant ?
		{
         token = 'o';
			for(int loopCounter = 1; loopCounter < length; loopCounter++)
			{
				if(!(word[loopCounter] >= '0' && word[loopCounter] <= '9'))
				{
					token = '\0';
					break;
				}
			}
		
		}
		else		// is variable ?
		{
			token = 'h';
			for(int loopCounter = 0; loopCounter < length; loopCounter++)
			{
				if( !( (word[loopCounter] >= 'A' && word[loopCounter] <= 'Z') || (word[loopCounter] >= 'a' && word[loopCounter] <= 'z') || (word[loopCounter] >= '0' && word[loopCounter] <= '9') || word[loopCounter] == '_' ) )
				{
					token = '\0';
					break;
				}
			}
			
		}
	
	}
	if(token == '\0')
	{
		word[length]='\0';
		printf("\nError: invalid token ->  %s \n", word);
		exit(0);
	}
	return token;
}

int mapping(char token)
{
	int tokenValue = -1;
	switch(token)
	{
		case 'S': tokenValue = 0; break;
		case 'A': tokenValue = 1; break;
		case 'B': tokenValue = 2; break;
		case 'C': tokenValue = 3; break;
		case 'D': tokenValue = 4; break;
		case 'E': tokenValue = 5; break;
		case 'F': tokenValue = 6; break;
		case 'G': tokenValue = 7; break;
		case 'H': tokenValue = 8; break;
		case 'I': tokenValue = 9; break;
		case '$': tokenValue = 10; break;
		case 'a': tokenValue = 11; break;
		case 'b': tokenValue = 12; break;
		case 'c': tokenValue = 13; break;
		case 'd': tokenValue = 14; break;
		case 'e': tokenValue = 15; break;
		case 'f': tokenValue = 16; break;
		case 'g': tokenValue = 17; break;
		case 'h': tokenValue = 18; break;
		case 'i': tokenValue = 19; break;
		case 'j': tokenValue = 20; break;
		case 'k': tokenValue = 21; break;
		case 'l': tokenValue = 22; break;
		case 'm': tokenValue = 23; break;
		case 'n': tokenValue = 24; break;
		case 'o': tokenValue = 25; break;
		case 'p': tokenValue = 26; break;
		default: printf("\nError in token mapping\n");exit(0);
	}
	return tokenValue;
}


int tokenContainer[MAX_TOKEN_QUANTITY];
int tokenContainerLength = -1;

void lexicalAnalyzer(char *SourceFilePath)
{
	char word[MAX_WORD_LENGTH];
	int length = 0;
	
	FILE *Source = fopen(SourceFilePath, "r");
	if(Source == NULL)
	{
		printf("File does not exist !\n");
		return;
	}
	
	char ch;

	ch = fgetc(Source);
	//printf("%c", ch);
	while(ch != EOF)
	{
		
		if(ch == ' ' || ch == '\n' || ch == '\t')
		{
			if(length > 0)
			{
				char ch = generateToken(word, length);
				tokenContainerLength++;
				tokenContainer[tokenContainerLength] = mapping(ch);
				//printf("%c ", ch);
				//word[length] = '\0'; printf("%s ", word);
				length = 0;
			}
			
		}
		else
		{
			word[length] = ch;
			length++;
		}
		
		
		ch = fgetc(Source);
	}
	
	fclose(Source);
	tokenContainerLength++;
	tokenContainer[tokenContainerLength] = mapping('$');
	
}


int parseTable[62][27];
int reduceTable[24][2]={  0, 2,
	 							  1, 18,
								  1, 20,
								  1, 20,
								  1, 22,
								  2, 4,
								  2, 6,
								  3, 4,
								  4, 2,
								  4, 4,
								  5, 6,
								  5, 8,
								  5, 8,
								  5, 10,
								  6, 6,
								  6, 8,
								  6, 10,
								  6, 12,
								  7, 2,
								  7, 10,
								  8, 2,
								  8, 2,
								  9, 2,
								  9, 6
								     	  };	// [reduce to variable mapping no for reduce to][items to pop]


void initParseTable()
{
	for(int i = 0; i < 62 ; i++)
	{
		for(int j = 0; j < 27; j++)
			parseTable[i][j] = ERROR; 
	}
	
	parseTable[0][mapping('A')] = 1;
	parseTable[0][mapping('j')] = 2;
	
	parseTable[1][mapping('$')] = ACCEPT;
	
	parseTable[2][mapping('a')] = 3;
	
	parseTable[3][mapping('b')] = 4;
	
	parseTable[4][mapping('c')] = 5;
	parseTable[4][mapping('B')] = 6;
	parseTable[4][mapping('j')] = 7;
	
	parseTable[5][mapping('d')] = 8;
	
	parseTable[6][mapping('c')] = 9;
	
	parseTable[7][mapping('h')] = 10;
	
	parseTable[8][mapping('e')] = 11;
	parseTable[8][mapping('D')] = 12;
	parseTable[8][mapping('F')] = 13;
	parseTable[8][mapping('j')] = 14;
	
	parseTable[9][mapping('d')] = 15;
	
	parseTable[10][mapping('c')] = -5;
	parseTable[10][mapping('C')] = 16;
	parseTable[10][mapping('i')] = 17;
	
	parseTable[11][mapping('H')] = 18;
	parseTable[11][mapping('o')] = 19;
	parseTable[11][mapping('h')] = 20;
	
	parseTable[12][mapping('e')] = 21;
	
	parseTable[13][mapping('e')] = -8;
	parseTable[13][mapping('E')] = 22;
	parseTable[13][mapping('n')] = 23;
	parseTable[13][mapping('h')] = 24;
	
	parseTable[14][mapping('h')] = 25;
	
	parseTable[15][mapping('e')] = 26;
	parseTable[15][mapping('D')] = 27;
	parseTable[15][mapping('F')] = 13;
	parseTable[15][mapping('j')] = 14;
	
	parseTable[16][mapping('c')] = -6;
	
	parseTable[17][mapping('B')] = 28;
	parseTable[17][mapping('j')] = 7;
	
	parseTable[18][mapping('f')] = 29;
	
	parseTable[19][mapping('f')] = -20;
	parseTable[19][mapping('p')] = -20;
	parseTable[19][mapping('l')] = -20;
	parseTable[19][mapping('m')] = -20;
	
	parseTable[20][mapping('f')] = -21;
	parseTable[20][mapping('p')] = -21;
	parseTable[20][mapping('l')] = -21;
	parseTable[20][mapping('m')] = -21;
	
	parseTable[21][mapping('H')] = 30;
	parseTable[21][mapping('o')] = 19;
	parseTable[21][mapping('h')] = 20;
	
	parseTable[22][mapping('e')] = -9;
	
	parseTable[23][mapping('h')] = 31;
	
	parseTable[24][mapping('k')] = 32;
	
	parseTable[25][mapping('f')] = 33;
	parseTable[25][mapping('k')] = 34;
	
	parseTable[26][mapping('H')] = 35;
	parseTable[26][mapping('o')] = 19;
	parseTable[26][mapping('h')] = 20;
	
	parseTable[27][mapping('e')] = 36;
	
	parseTable[28][mapping('c')] = -7;
	
	parseTable[29][mapping('g')] = 37;
	
	parseTable[30][mapping('f')] = 38;
	
	parseTable[31][mapping('f')] = 39;
	
	parseTable[32][mapping('G')] = 40;
	parseTable[32][mapping('I')] = 41;
	parseTable[32][mapping('H')] = 42;
	parseTable[32][mapping('o')] = 19;
	parseTable[32][mapping('h')] = 20;
	
	
	parseTable[33][mapping('e')] = -14;
	parseTable[33][mapping('n')] = -14;
	parseTable[33][mapping('h')] = -14;
	parseTable[33][mapping('F')] = 43;
	parseTable[33][mapping('j')] = 14;
	
	parseTable[34][mapping('G')] = 44;
	parseTable[34][mapping('I')] = 41;
	parseTable[34][mapping('H')] = 42;
	parseTable[34][mapping('o')] = 19;
	parseTable[34][mapping('h')] = 20;
	
	parseTable[35][mapping('f')] = 45;
	
	parseTable[36][mapping('H')] = 46;
	parseTable[36][mapping('o')] = 19;
	parseTable[36][mapping('h')] = 20;
	
	parseTable[37][mapping('$')] = -1;
	
	parseTable[38][mapping('g')] = 47;
	
	parseTable[39][mapping('e')] = -10;
	parseTable[39][mapping('E')] = 48;
	parseTable[39][mapping('n')] = 23;
	parseTable[39][mapping('h')] = 24;
	
	parseTable[40][mapping('f')] = 49;
	
	parseTable[41][mapping('f')] = -18;
	parseTable[41][mapping('l')] = 50;
	
	parseTable[42][mapping('l')] = -22;
	parseTable[42][mapping('m')] = -22;
	parseTable[42][mapping('f')] = -22;
	parseTable[42][mapping('p')] = 51;
	
	parseTable[43][mapping('e')] = -15;
	parseTable[43][mapping('n')] = -15;
	parseTable[43][mapping('h')] = -15;
	
	parseTable[44][mapping('f')] = 52;
	
	parseTable[45][mapping('g')] = 53;
	
	parseTable[46][mapping('f')] = 54;
	
	parseTable[47][mapping('$')] = -2;
	
	parseTable[48][mapping('e')] = -11;
	
	parseTable[49][mapping('e')] = -12;
	parseTable[49][mapping('E')] = 55;
	parseTable[49][mapping('n')] = 23;
	parseTable[49][mapping('h')] = 24;
	
	parseTable[50][mapping('I')] = 56;
	parseTable[50][mapping('H')] = 42;
	parseTable[50][mapping('o')] = 19;
	parseTable[50][mapping('h')] = 20;
	
	parseTable[51][mapping('I')] = 57;
	parseTable[51][mapping('H')] = 42;
	parseTable[51][mapping('o')] = 19;
	parseTable[51][mapping('h')] = 20;
	
	parseTable[52][mapping('e')] = -16;
	parseTable[52][mapping('n')] = -16;
	parseTable[52][mapping('h')] = -16;
	parseTable[52][mapping('F')] = 58;
	parseTable[52][mapping('j')] = 14;
	
	parseTable[53][mapping('$')] = -3;
	
	parseTable[54][mapping('g')] = 59;
	
	parseTable[55][mapping('e')] = -13;
	
	parseTable[56][mapping('m')] = 60;
	
	parseTable[57][mapping('l')] = -23;
	parseTable[57][mapping('m')] = -23;
	parseTable[57][mapping('f')] = -23;
	
	parseTable[58][mapping('e')] = -17;
	parseTable[58][mapping('n')] = -17;
	parseTable[58][mapping('h')] = -17;
	
	parseTable[59][mapping('$')] = -4;
	
	parseTable[60][mapping('I')] = 61;
	parseTable[60][mapping('H')] = 42;
	parseTable[60][mapping('o')] = 19;
	parseTable[60][mapping('h')] = 20;
	
	parseTable[61][mapping('f')] = -19;
	
	
}



void executeParser()
{
	int IBCounter = 0;
	int token = tokenContainer[IBCounter];
	int value;
	bool flag = false;
	int popCounter;
	push(0);
	
	while(true)
	{
		 value = parseTable[lookTop()][token];
		 if(value == 100)
		 {
		 	printf("\n Parse Completed !\n Language Accepted. ");
		 	break;
		 }
		 else if(value == -100)
		 {
		 	printf("\n Parse Incomplete !\n Language is not Accepted. ");
		 	//printf("\n%d %d", lookTop(), token);
		 	break;
		 }
		 else if(value > -1)
		 {
		 	push(token);
		 	push(value);
		 	if(flag)
		 	{
		 		flag = false;
		 		token = tokenContainer[IBCounter];
		   }
		   else
		   {
		   	IBCounter++;
		   	token = tokenContainer[IBCounter];
			}
		 }
		 else
		 {
		 	value = value * -1;
		   popCounter = reduceTable[value][1];
		   for(int i = 0; i < popCounter; i++) pop();
		   token = reduceTable[value][0];
		   flag = true;
		   
	    } 
	}
	
	
}

int main()
{
	char path[1024];
	gets(path);
	lexicalAnalyzer(path);
	initParseTable();
	executeParser();
	//getch();
	return 0;
}
