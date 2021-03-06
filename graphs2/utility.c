#include<stdio.h>
#include<stdlib.h>
#include<string.h>
# include "utility.h"

char *getLine(void){
    char *line;
    int size;   /* how much space do I have in the line? */
    int length; /* how many characters have i used ?*/
    int c;
    size = INITIAL_LINE_LENGTH;
    line = malloc(size);
    if(line == 0) {
        /* malloc failed */
        printf("getLine() : failed to allocate memory for the input.");
        return 0;
    }
    length = 0;
    while ((c = getchar()) != EOF && c != '\n') {
        /* code */
        if(length >= size-1){
            /* need more space */
            size*=2;
            /* make length equal to new size*/
            /* copy contents if necessary */
            line = realloc(line , size);
        }
        line[length++] = c;
    }
    line[length] = '\0';
    return line;
}

/* free2d: frees a 2D array created by malloc2d */
void free2d(void **a){
    void **row;
    /*first free rows */
    for (row = a; *row !=0 ; row++){
        free(*row);
    }
    free(a);
}

/*
malloc2d :
returns a two-dimensional array with numRows rows and
rowSize bytes per row, or 0 on allocation failure.
The caller is responsible for freeing the result with free2d.
Note: it returns a void** pointer on sucessfull allocation therefore one to typecast it explicitly for further usage.
*/

void **malloc2d(size_t numRows , size_t rowSize){
    void **a;
    size_t i;
    a = malloc(sizeof(void *) * (numRows+1));   /* one extra for sentinel */
    if (a==0){
        /* malloc failed */
        printf("malloc2d(size_t numRows , size_t rowSize) : failed to allocate memory for the input.");
        return 0;
    }

    /* now allocate the actual rows */
    for (i=0; i<numRows ; ++i){
        a[i] = malloc(rowSize);
        if(a[i]==0){
            free2d(a);
            return 0;
        }
    }
    /* intialize the sentinel value */
    a[numRows] = 0;
    return a;
}

void print2Dint( int **arr, size_t rows , size_t cols){
    printf("\n");
    for (size_t i=0; i<rows; i++){
        for (size_t j =0; j<cols ; j++){
            printf("%d\t" , arr[i][j]);
        }
        printf("\n");
    }
}

/* Read numbers from the terminal until an other type of data is entered */
/* I need to generalize this so as to handle any other type of numbers, eg., float , long , etc. */
/* You need to supply an address of the variable which will count the the numbers of integer read. */
/* Return data will be a dynamically allocated array. You must free the data using saferFree() or free. */
int *readNumbers(int *count /* RETVAL */){
    int mycount=0;    /* number of numbers read */
    int size=1;       /* size of block allocated so far */
    int *a;         /* block */
    int n;          /* number read */

    a = malloc(sizeof(int)*size);   /* allocating zero bytes is tricky */
    if( a == 0 ) return 0;

    while(scanf("%d", &n) == 1){
        /* Do we have empty space? */
        while (mycount >= size) {
            size*=2 ;
            a = realloc(a, sizeof(int) * size);
            if(a==0) return 0;
        }

        /* put the new number in */
        a[mycount++] = n;
        printf("%d %d\n", a[mycount-1] , n );
    }
    /* trim off any excess space */
    a = realloc(a, sizeof(int) * mycount);
    /* note: if a == 0 at this point we'll just return it anyway */
    /* save out to mycount */
    *count = mycount;
    *count++;
    return a;
}
