#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"
#define SIZE_OF_NULLCHAR 1

typedef enum {
    up,
    down,
    left,
    right
} direction;
void draw(int x, int y, direction dir, int step, int w, RGB* im, RGB c){
    #define I(i, j) im[(i)*w + j]
        int j;
        if (dir == up){
            for (j = 0; j < step; j++)
                I(x + j, y) = c;
            }       
        if (dir == down){
            for (j = 0; j < step; j++)
                I(x - j, y) = c;
            }
        if (dir == right){
            for (j = 0; j < step; j++)
                I(x, y + j) = c;
            }
        if (dir == left){
            for (j = 0; j < step; j++)
                I(x, y - j) = c;
            }
    #undef I
}

/*I used a forloop here because function calls take up alot of time
and using recusion would probably be a huge time waster*/
char * Make_FibWord(int n){
    /*First two are 1 and 0*/
    char *Prev_Word;
	strcpy(Prev_Word = malloc(2), "1");
	char *Cur_Word;
	strcpy(Cur_Word = malloc(2) , "0");
 
	int i;
	for (i = 2; i <= n; i++) {
		char *Next_Word;
        /*creates the next string with s(i+1) = s(i)+s(i-1)*/
		strcpy(Next_Word = malloc(strlen(Cur_Word) + strlen(Prev_Word) + SIZE_OF_NULLCHAR), Cur_Word); 
		strcat(Next_Word, Prev_Word);
        /*resets s(i-1) and sets to new s for next loop
        s(i) is then set to s(i+1) for next loop*/
		free(Prev_Word);
		Prev_Word = Cur_Word;
		Cur_Word = Next_Word;
	}
 
	free(Prev_Word);
	return (Cur_Word);
}

direction Turn_Right(direction d){
    switch (d){
    case up:
        return right;
    case left:
        return up;
    case down:
        return left;
    case right:
        return down;
    }
}

direction Turn_Left(direction d){
    switch (d){
    case up:
        return left;
    case left:
        return down;
    case down:
        return right;
    case right:
        return up;
    }
}

int fib (int n, int x, int y, int step, RGB bc, RGB fc, int w, int h ,RGB * image ){

    int i;
    char * fibstring = Make_FibWord(n-1);

    for (i = 0; i < w * h; i++)
            image[i] = bc;

    direction cur_dir = up;
    int k = strlen(fibstring);

    for (i = 0; i < k; i ++){
        draw(x, y, cur_dir, step, w, image, fc);

        if (cur_dir == up) x += step;
        if (cur_dir == down) x -= step;
        if (cur_dir == right) y += step;
        if (cur_dir == left) y -= step;

        if (fibstring[i] == '0'){
            if (i%2){
            cur_dir = Turn_Left(cur_dir);
            } else {
            cur_dir = Turn_Right(cur_dir);
            }
        }

    }
    free (fibstring);

return k;
}
