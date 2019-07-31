#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	// TODO: rewrite this function
	char c;
	c = (char)rand() %256;
	return c;
}

char *inputString()
{
	// TODO: rewrite this function
	int i;
	char s[6];
	char tempS[27];
	memset(s, '\0', sizeof(s));	//clear string of garbage values
	memset(tempS, '\0', sizeof(tempS));
	
	//Fills temp array from a-z. Last char is \0.	    	
	for (i = 0; i < sizeof(tempS) - 1; i++)
	{
		tempS[i] = 97 + i;
	}

	//Fills string with random letters from temp array
	for (i = 0; i < 5; i++)
	{
		s[i] = tempS[rand() % 27];
	}
	return s;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    //printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' ' && state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(0));
    testme();
    return 0;
 }
