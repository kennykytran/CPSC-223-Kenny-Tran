#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define IN 1
#define OUT 0
#define MAX_WORD_LEN 16
#define CHAR_TOTAL 128
#define MAXLINE 1000

//-----------------------------------------------------------
//exercise 1-13
void print_horiz_histogram(int * words){
  printf("--------------------------------------------------\n");

  for (int i = 1; i < MAX_WORD_LEN; ++i){
    printf("%d: ", i);

  for (int j = 0; j < words[i]; ++j){
    printf("*");
    if(j>0 && ((j+1)%5)==0)printf("|");}

  printf("\n");
  if((i+1)%5 == 0) printf("--------------------------------------------------\n");
  }
}

void print_vert_histogram(int * words){
  printf("=================================================================\n");
  for (int i = 1; i < MAX_WORD_LEN; ++i){
    printf(" %d: ",i);}
  printf("\n=================================================================\n");
  for (int j = 1; j < MAX_WORD_LEN; j++){
  for (int k = 1; k <= MAX_WORD_LEN; ++k){
    if(words[k]>=j)printf(" *  ");
    else printf(" .  ");}
  printf("\n");
  if(j%5 == 0) printf("-----------------------------------------------------------------\n");
  }
}

int * count_words(void) {

  char wordbuf[50];
  int index = 0;
  memset(wordbuf, 0, sizeof(wordbuf)); //fills the buffer with zeros

  long  nl, nw, nc;
  int   c, state = OUT;
  nl = nw = nc = 0;
  static int words[MAX_WORD_LEN];
  memset(words, 0, sizeof(words));//ctrl d is EOF

  while ((c = getchar()) != EOF) {
  ++nc;
  if (isalpha(c)){wordbuf[index++] = c;}

  if (c == '\n')++nl;
  if (c == ' ' || c == '\n' || c == '\t')state = OUT;
  else if (state == OUT) {
    state = IN;
    ++nw;
    words[index]++;
    wordbuf[0] = wordbuf[index];
    index = 0;}
  }

  words[1]--; // don't add entering the first word

  if (index > 0) {  // words just before the EOF with no leading whitespace
    ++index;
    words[index]++;
  }

  printf("\n%1ld lines, %1ld words, and %1ld characters\n", nl, nw, nc-1);

  return words;
}

//exercise 1-14
void freq_histogram(void){

  int c, i, j;
  int chars[CHAR_TOTAL];
  memset(chars, 0, sizeof(chars));

  while ((c = getchar()) != EOF) {
    ++chars[c-32];
    if (c == '\n') {
    for (i = 0; i < CHAR_TOTAL; i++)
      if (chars[i] != 0) {
        printf("%c: ", i);
        for (j = 0; j < chars[i]; j++){
          printf("*");
          if(j>0 && ((j+1)%5)==0)printf("|");}

        printf("\n");}
    }
  }
}

//functions for 1-16 to 1-19
int getlines(char *s,int lim){
  int c, i;
  for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
  s[i] = c;
  if (c == '\n') {
    s[i] = c;
    ++i;}
  s[i] = '\0';
  return i;}

void copy(char to[], char from[]){
   int i;
   i = 0;
   while ((to[i] = from[i]) != '\0')++i;}

//exercise 1-16
void longest_line(void){
    char line[MAXLINE];
    char longest[MAXLINE];
    char t[MAXLINE];
    int len, max, pmax, nextchar;

    nextchar = pmax = max = 0;
    while((len = getlines(line, MAXLINE)) > 0){
        if(line[len - 1] != '\n'){
            if(nextchar == 0) copy(t, line);
                pmax += len;
            if(max < pmax) max = pmax;
                nextchar = 1;}
        else{
            if(nextchar == 1){
                if(max < pmax+len){
                    max = pmax+len;
                    copy(longest,t);
                    longest[MAXLINE-2] = '\n';}
                nextchar = 0;}

            else if(max < len){
                max = len;
                copy(longest, line);}
                pmax = 0;}
    }
    if(max > 0)printf("%s", longest);
}

//exercise 1-17
void print_mteighty(void){
  int length;
  char line[MAXLINE];

  while((length=getlines(line,MAXLINE)) > 0){
    if(length > 80) printf("%s", line);
  }
}

//exercise 1-18
void print_notrail(char *line){
  int i;

  for(i=0; line[i] != '\n'; ++i);
  --i;

  for(i = i; ((line[i] == ' ') || (line[i] =='\t'));--i);

  if( i >= 0){
    ++i;
    line[i] = '\n';
    ++i;
    line[i] = '\0';}
}

//exercise 1-19
void reverse(char *line){
  int i,j;
  char t;

  for(i=0;line[i]!='\0';++i);
  --i;

  if(line[i]=='\n')--i;

  j = 0;

  while(j < i){
    t = line[j];
    line[j] = line[i];
    line[i] = t;
    --i;
    ++j;}
  }

//-----------------------------------------------------------
//-----------------------------------------------------------
int main(int argc, const char * argv[]) {
printf("Now testing 1-13, please enter input and press ctrl D after testing\n");
//exercise 1-13
  int * words;
  words = count_words();
  print_horiz_histogram(words);
  print_vert_histogram(words);

printf("Now testing 1-14, please enter input and press ctrl D after testing\n");
//exercise 1-14
  freq_histogram();

printf("Now testing 1-16, please enter input and press ctrl D after testing\n");
//exercise 1-16
  longest_line();

printf("Now testing 1-17, please enter input and press ctrl D after testing\n");
//exercise 1-17
  print_mteighty();

printf("Now testing 1-18, please enter input and press ctrl D after testing\n");
//exercise 1-18
int len;
char line[MAXLINE];

while((len=getlines(line,MAXLINE))>0){
  print_notrail(line);
  printf("%s",line);}

printf("Now testing 1-19, please enter input and press ctrl D after testing\n");
//exercise 1-19
while((len=getlines(line,MAXLINE))>0){
  reverse(line);
  printf("%s",line);}

return 0;
}
