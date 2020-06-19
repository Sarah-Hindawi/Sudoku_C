#include <stdlib.h>
        #include <stdio.h>
        #include <string.h>
        #include <pthread.h>

// the thread that will check each row
        void *checkRows (void *p);
// the thread that will check each column
        void *checkCols (void *p);
// the thread that will check a square
        void *check (void *p);

//methods to deal with the different Sudoku sizes

        void sizeThree ();
        void sizeFour ();

        void displayFour (int *a);


//the size of the Sudoku game
        int n;

//method that will display the elements of the array (for size 2 & 3)
        void display (int *a)
        {
        int j;
        for (j = 0; j < n * n * n * n; j++)
        {
        printf ("%d ", a[j]);
//to print on the next line
        if ((j + 1) % (n * n) == 0 && j != 0)
        {
        printf ("\n");
        }
        }
        }

        int func (const void *n1, const void *n2)
        {
        //compare two integers
        return (*(int *) n1 - *(int *) n2);
        }

        typedef struct st
        {
        int row;
        int col;
        int *array;
        } params;

        int main ()
        {
        int choice;        // user's choice of size
        printf ("Please enter the size of the pattern:\n");
        scanf ("%d", &choice);

        if (3 == choice)
        {
        sizeThree ();
        }
        else
        {
        sizeFour ();
        }
        }

// method to check rows
        void * checkRows (void *p)
        {
        // list of numbers from 1 to n * n (to be used for comparison)
        int original[n * n];
        int i;
        // fill the array
        if (n < 4)
        {
        for (i = 0; i < n * n; i++)
        original[i] = i + 1;
        }
        if (n == 4 || n == 5)
        {
        for (i = 0; i < n * n; i++)
        original[i] = i;
        }
        // the array that will hold each row
        int rows[n * n];
        int j;
        //getting the array game from the argument
        int *a = (int *) p;
        // accessing elements from each row
        for (j = 0; j < n * n; j++)
        {
        // index to be used to get the element
        int in = n * n * j;
        for (i = 0; i < n * n; i++)
        {
        rows[i] = a[in];
        in++;
        }
        //sort row numbers to be compared with the list that contains numbers from 1 to n*n
        qsort (rows, n * n, sizeof (int), func);
        int x;
        //comparing the contents of the row with the list of numbers
        for (x = 0; x < n * n; x++)
        {
        //if an element doesn't have a corresponding equal number in the list the row is invalid
        if (rows[x] != original[x])
        return (void *) -1;
        }
        }
        return (void *) 1;
        }

        void * checkCols (void *p)
        {
        int original[n * n];
        int i;
        if (n < 4)
        {
        for (i = 0; i < n * n; i++)
        original[i] = i + 1;
        }
        if (n == 4 || n == 5)
        {
        for (i = 0; i < n * n; i++)
        original[i] = i;
        }
        // array that will hold each column
        int cols[n * n];
        int *a = (int *) p;
        int j;
        for (i = 0; i < n * n; i++)
        {
        int in;
        for (j = 0; j < n * n; j++)
        {
        in = n * n * j + i;
        cols[j] = a[in];
        }
        qsort (cols, n * n, sizeof (int), func);
        int x;
        for (x = 0; x < n * n; x++)
        {
        if (cols[x] != original[x])
        return (void *) -1;
        }
        }
        return (void *) 1;
        }

        void *check (void *p)
        {
        int original[n * n];
        params * d = (params *) p;
        int r = d->row;
        int c = d->col;
        int *a = d->array;
        int i, j;
        if (n < 4)
        {
        for (i = 0; i < n * n; i++)
        original[i] = i + 1;
        }
// if the size was 4, make values of the array start from 0
        if (n == 4)
        {
        for (i = 0; i < n * n; i++)
        original[i] = i;
        }
        int square[n * n];
        int in = 0;
        for (i = r; i < r + n; i++)
        {
        for (j = c; j < c + n; j++)
        {
        square[in] = a[i * n * n + j];
        in = in + 1;
        }
        }
        qsort (square, n * n, sizeof (int), func);
        int x;
        for (x = 0; x < n * n; x++)
        {
        if (square[x] != original[x])
        return (void *) -1;
        }
        return (void *) 1;
        }


        void sizeThree ()
        {
        pthread_t id, id2, id3, id4, id5, id6, id7, id8, id9, id10, id11;    /* checking the nine squares id's */
        pthread_attr_t at1, at2, at3;    /* thread attributes */
        n = 3;
        printf ("Enter 81 numbers or -1 to use the default pattern:\n");
        int a[81] =
        { 2, 9, 5, 7, 4, 3, 8, 6, 1, 4, 3, 1, 8, 6, 5, 9, 2, 7, 8, 7, 6, 1, 9, 2,
        5, 4, 3, 3, 8, 7, 4, 5, 9, 2, 1, 6, 6, 1, 2, 3, 8, 7, 4, 9, 5, 5, 4, 9, 2,
        1, 6,
        7, 3, 8, 7, 6, 3, 5, 2, 4, 1, 8, 9, 9, 2, 8, 6, 7, 1, 3, 5, 4, 1, 5, 4, 9,
        3, 8,
        6, 7, 2
        };
        int i, j;
        char *ch;
        for (i = 0; i < 81; i++)
        {
        scanf ("%s", &ch);
        int n = atoi (&ch);
        if (n == -1)
        {
        break;
        }
        a[i] = n;
        }
        int *p = &a[0];
        display (p);
        pthread_attr_init (&at1);
        pthread_attr_init (&at2);
        pthread_attr_init (&at3);
        void *r1;
        void *r2;
        void *r3;
        void *r4;
        void *r5;
        void *r6;
        void *r7;
        void *r8;
        void *r9;
        void *r10;
        void *r11;
        params data1;
        data1.row = 0;
        data1.col = 0;
        data1.array = &a[0];
        params data2;
        data2.row = 0;
        data2.col = 3;
        data2.array = &a[0];
        params data3;
        data3.row = 0;
        data3.col = 6;
        data3.array = &a[0];
        params data4;
        data4.row = 3;
        data4.col = 0;
        data4.array = &a[0];
        params data5;
        data5.row = 0;
        data5.col = 6;
        data5.array = &a[0];
        params data6;
        data6.row = 3;
        data6.col = 6;
        data6.array = &a[0];
        params data7;
        data7.row = 6;
        data7.col = 0;
        data7.array = &a[0];
        params data8;
        data8.row = 6;
        data8.col = 3;
        data8.array = &a[0];
        params data9;
        data9.row = 6;
        data9.col = 6;
        data9.array = &a[0];
        pthread_create (&id, &at1, checkRows, (void *) p);
        pthread_create (&id2, &at2, checkCols, (void *) p);
        pthread_create (&id3, &at3, check, &data1);
        pthread_create (&id4, &at3, check, &data2);
        pthread_create (&id5, &at3, check, &data3);
        pthread_create (&id6, &at3, check, &data4);
        pthread_create (&id7, &at3, check, &data5);
        pthread_create (&id8, &at3, check, &data6);
        pthread_create (&id9, &at3, check, &data7);
        pthread_create (&id10, &at3, check, &data8);
        pthread_create (&id11, &at3, check, &data9);
        pthread_join (id, &r1);
        pthread_join (id2, &r2);
        pthread_join (id3, &r3);
        pthread_join (id4, &r4);
        pthread_join (id5, &r5);
        pthread_join (id6, &r6);
        pthread_join (id7, &r7);
        pthread_join (id8, &r8);
        pthread_join (id9, &r9);
        pthread_join (id10, &r10);
        pthread_join (id11, &r11);
        int rowsValid = (int *) r1;
        int colsValid = (int *) r2;
        int squareValid1 = (int *) r3;
        int squareValid2 = (int *) r4;
        int squareValid3 = (int *) r5;
        int squareValid4 = (int *) r6;
        int squareValid5 = (int *) r7;
        int squareValid6 = (int *) r8;
        int squareValid7 = (int *) r9;
        int squareValid8 = (int *) r10;
        int squareValid9 = (int *) r11;
        int isValid =
        squareValid4 + squareValid3 + squareValid2 + squareValid1 +
        squareValid5 + squareValid6 + squareValid7 + squareValid8 +
        squareValid9 +
        rowsValid + colsValid;
        if (isValid != 11)
        {
        printf ("This is not a valid Sudoku pattern\n");
        }
        else
        {
        printf ("This is a valid Sudoku pattern\n");
        }
        }

        void sizeFour ()
        {
        pthread_t id, id2, id3, id4, id5, id6, id7, id8, id9, id10, id11, id12, id13, id14, id15, id16, id17, id18;    /* checking the 16 squares id's */
        pthread_attr_t at1, at2, at3;    /* thread attributes */
        n = 4;
        printf ("Enter 256 numbers! or -1 to use the default pattern:\n");
        int a[256] =
        { 11, 9, 7, 8, 1, 5, 14, 4, 3, 2, 6, 10, 13, 15, 12, 0, 0, 14, 4, 1, 3, 7,
        13, 6, 8, 12, 9, 15, 10, 11, 5, 2, 10, 13, 15, 6, 12, 2, 8, 11, 0, 5, 1,
        4, 3, 7,
        9, 14, 3, 12, 5, 2, 10, 0, 9, 15, 13, 7, 14, 11, 1, 4, 6, 8, 12, 4, 6, 10,
        11, 8,
        2, 1, 5, 14, 0, 7, 9, 3, 15, 13, 8, 2, 14, 3, 7, 12, 0, 10, 6, 9, 15, 13,
        11, 5, 1,
        4, 9, 15, 0, 7, 4, 14, 5, 13, 12, 3, 11, 1, 2, 10, 8, 6, 5, 1, 11, 13, 6,
        15, 3, 9,
        2, 4, 10, 8, 12, 14, 0, 7, 14, 8, 9, 15, 2, 1, 4, 7, 11, 10, 12, 3, 6, 0,
        13, 5, 4,
        7, 13, 11, 5, 3, 6, 12, 1, 8, 2, 0, 15, 9, 14, 10, 2, 3, 10, 0, 9, 13, 15,
        14, 4,
        6, 7, 5, 8, 1, 11, 12, 6, 5, 1, 12, 8, 10, 11, 0, 9, 15, 13, 14, 7, 2, 4,
        3, 7, 10,
        8, 9, 13, 11, 1, 2, 14, 0, 5, 12, 4, 6, 3, 15, 13, 11, 12, 14, 15, 4, 7,
        5, 10, 1,
        3, 6, 0, 8, 2, 9, 1, 0, 2, 4, 14, 6, 10, 3, 15, 13, 8, 9, 5, 12, 7, 11,
        15, 6, 3,
        5, 0, 9, 12, 8, 7, 11, 4, 2, 14, 13, 10, 1
        };
        int i, j;
        char *ch;
        for (i = 0; i < 256; i++)
        {
        scanf ("%s", &ch);
        int n = atoi (&ch);
        if (n == -1)
        {
        break;
        }
        a[i] = n;
        }
        int *p = &a[0];
        displayFour (p);
        pthread_attr_init (&at1);
        pthread_attr_init (&at2);
        pthread_attr_init (&at3);
        void *r1;
        void *r2;
        void *r3;
        void *r4;
        void *r5;
        void *r6;
        void *r7;
        void *r8;
        void *r9;
        void *r10;
        void *r11;
        void *r12;
        void *r13;
        void *r14;
        void *r15;
        void *r16;
        void *r17;
        void *r18;
        params data1;
        data1.row = 0;
        data1.col = 0;
        data1.array = &a[0];
        params data2;
        data2.row = 0;
        data2.col = 4;
        data2.array = &a[0];
        params data3;
        data3.row = 0;
        data3.col = 8;
        data3.array = &a[0];
        params data4;
        data4.row = 0;
        data4.col = 12;
        data4.array = &a[0];
        params data5;
        data5.row = 4;
        data5.col = 0;
        data5.array = &a[0];
        params data6;
        data6.row = 4;
        data6.col = 4;
        data6.array = &a[0];
        params data7;
        data7.row = 4;
        data7.col = 8;
        data7.array = &a[0];
        params data8;
        data8.row = 4;
        data8.col = 12;
        data8.array = &a[0];
        params data9;
        data9.row = 8;
        data9.col = 0;
        data9.array = &a[0];
        params data10;
        data10.row = 8;
        data10.col = 4;
        data10.array = &a[0];
        params data11;
        data11.row = 8;
        data11.col = 8;
        data11.array = &a[0];
        params data12;
        data12.row = 8;
        data12.col = 12;
        data12.array = &a[0];
        params data13;
        data13.row = 12;
        data13.col = 0;
        data13.array = &a[0];
        params data14;
        data14.row = 12;
        data14.col = 4;
        data14.array = &a[0];
        params data15;
        data15.row = 12;
        data15.col = 8;
        data15.array = &a[0];
        params data16;
        data16.row = 12;
        data16.col = 12;
        data16.array = &a[0];
        pthread_create (&id, &at1, checkRows, (void *) p);
        pthread_create (&id2, &at2, checkCols, (void *) p);
        pthread_create (&id3, &at3, check, &data1);
        pthread_create (&id4, &at3, check, &data2);
        pthread_create (&id5, &at3, check, &data3);
        pthread_create (&id6, &at3, check, &data4);
        pthread_create (&id7, &at3, check, &data5);
        pthread_create (&id8, &at3, check, &data6);
        pthread_create (&id9, &at3, check, &data7);
        pthread_create (&id10, &at3, check, &data8);
        pthread_create (&id11, &at3, check, &data9);
        pthread_create (&id12, &at3, check, &data10);
        pthread_create (&id13, &at3, check, &data11);
        pthread_create (&id14, &at3, check, &data12);
        pthread_create (&id15, &at3, check, &data13);
        pthread_create (&id16, &at3, check, &data14);
        pthread_create (&id17, &at3, check, &data15);
        pthread_create (&id18, &at3, check, &data16);
        pthread_join (id, &r1);
        pthread_join (id2, &r2);
        pthread_join (id3, &r3);
        pthread_join (id4, &r4);
        pthread_join (id5, &r5);
        pthread_join (id6, &r6);
        pthread_join (id7, &r7);
        pthread_join (id8, &r8);
        pthread_join (id9, &r9);
        pthread_join (id10, &r10);
        pthread_join (id11, &r11);
        pthread_join (id12, &r12);
        pthread_join (id13, &r13);
        pthread_join (id14, &r14);
        pthread_join (id15, &r15);
        pthread_join (id16, &r16);
        pthread_join (id17, &r17);
        pthread_join (id18, &r18);
        int rowsValid = (int *) r1;
        int colsValid = (int *) r2;
        int squareValid1 = (int *) r3;
        int squareValid2 = (int *) r4;
        int squareValid3 = (int *) r5;
        int squareValid4 = (int *) r6;
        int squareValid5 = (int *) r7;
        int squareValid6 = (int *) r8;
        int squareValid7 = (int *) r9;
        int squareValid8 = (int *) r10;
        int squareValid9 = (int *) r11;
        int squareValid10 = (int *) r12;
        int squareValid11 = (int *) r13;
        int squareValid12 = (int *) r14;
        int squareValid13 = (int *) r15;
        int squareValid14 = (int *) r16;
        int squareValid15 = (int *) r17;
        int squareValid16 = (int *) r18;
        int isValid =
        squareValid4 + squareValid3 + squareValid2 + squareValid1 +
        squareValid5 + squareValid6 + squareValid7 + squareValid8 +
        squareValid9 +
        squareValid14 + squareValid13 + squareValid12 +
        squareValid11 +
        squareValid15 + squareValid16 + squareValid10 +
        rowsValid + colsValid;
        if (isValid != 18)
        {
        printf ("\nThis is not a valid Sudoku pattern\n");
        }
        else
        {
        printf ("\nThis is a valid Sudoku pattern\n");
        }
        }


//method that will display elements when input size is 4
        void displayFour (int *a)
        {
        int j;
        for (j = 0; j < n * n * n * n; j++)
        {
        int num = a[j];
//convert to letters
        if (num == 10)
        {
        printf ("a ");
        }
        else if (num == 11)
        {
        printf ("b ");
        }
        else if (num == 12)
        {
        printf ("c ");
        }
        else if (num == 13)
        {
        printf ("d ");
        }
        else if (num == 14)
        {
        printf ("e ");
        }
        else if (num == 15)
        {
        printf ("f ");
        }
        else
        {
        printf ("%d ", a[j]);
        }
        if ((j + 1) % (n * n) == 0 && j != 0)
        {
        printf ("\n");
        }
        }
        }
