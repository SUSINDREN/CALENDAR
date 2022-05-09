#include<stdio.h>
#include<conio.h>
#define SPACE 32
#define DIM 7
#define TOTCOLS 80
#define TOTROWS 25
#define LT 218
#define RT 191
#define LB 192
#define RB 217
#define TT 194
#define BT 193
#define LST 195
#define RST 180
#define CROSS 197
#define VL 179
#define HL 196
#define WIDTH 5
#define HEIGHT 1
#define BS 8
#define ESC 283
#define UP 18432
#define DOWN 20480
#define LEFT 19200
#define RIGHT 19712
#define HOME 18176
#define END 20224

void drawBox(void)
{
    int ctr1, ctr2, ctr3, ctr4;
    int row, col;

    clrscr();
    col = ( TOTCOLS - ( (DIM * WIDTH) + (DIM + 1) ) ) / 2;
    row = ( TOTROWS - ( (DIM * HEIGHT) + (DIM + 1) ) ) / 2;
    gotoxy(col, row);
    printf("%c", LT);
    
    for(ctr2 = 0; ctr2 < DIM ; ctr2++)
    {
        for(ctr1 = 0; ctr1 < WIDTH; ctr1++)
        printf("%c", HL);

        printf("%c", TT);
    }
    printf("%c%c", BS, RT);
    
    for(ctr3 = 0; ctr3 < DIM; ctr3+=1)
    {
        row++;
        gotoxy(col, row);

        for(ctr2 = 0; ctr2 <= DIM; ctr2++)
        {
            printf("%c", VL);
            for(ctr1 = 0; ctr1 < WIDTH; ctr1++)
            printf("%c", SPACE);
        }
        row++;
        gotoxy(col, row);
        printf("%c", LST);
        
        for(ctr2 = 0; ctr2 < DIM; ctr2+=1)
        {
            for(ctr1 = 0; ctr1 < WIDTH; ctr1++)
            printf("%c", HL);
            printf("%c", CROSS);
        }
        printf("%c%c", BS, RST);
    }
    
    gotoxy(col, row);
    printf("%c", LB);
    for(ctr2 = 0; ctr2 < DIM ; ctr2++)
    {
        for(ctr1 = 0; ctr1 < WIDTH; ctr1++)
        printf("%c", HL);
        printf("%c", BT);
    }
    printf("%c%c", BS, RB);


}

void colHeadings(void)
{
    int row, col,ctr;
    col = ( TOTCOLS - ( (DIM * WIDTH) + (DIM + 1) ) ) / 2;
    row = ( TOTROWS - ( (DIM * HEIGHT) + (DIM + 1) ) ) / 2;
    row+=1;
    col+=2;
    
    for(ctr =0; ctr < DIM; ctr+=1)
    {
        gotoxy(col + ctr * (WIDTH+1),row);
        switch(ctr)
        {
            case 0 : printf("SUN"); break;
            case 1 : printf("MON"); break;
            case 2 : printf("TUE"); break;
            case 3 : printf("WED"); break;
            case 4 : printf("THU"); break;
            case 5 : printf("FRI"); break;
            case 6 : printf("SAT"); break;

        }
    }
}

int isLeap(int yr)
{
    if((yr%4==0&&yr%100!=0)||(yr%400==0))
    return 1;
    return 0;
}

int dow(int y, int m, int d)
{
    static int leftout[] = {0,3,2,5,0,3,5,1,4,6,2,4};
    y-=m<3;
    return ( ( y + y /4 - y/100 + y/400 + leftout[m-1] + d) % 7);
}

void printCalendar(int mon,int yr)
{
    int row, col,dayNum, dayCtr;
    int days_in_month ;
    col = ( TOTCOLS - ( (DIM * WIDTH) + (DIM + 1) ) ) / 2;
    row = ( TOTROWS - ( (DIM * HEIGHT) + (DIM + 1) ) ) / 2;
    row+=3;
    col+=3;
    gotoxy(31, 3);
    
    switch(mon )
    {
        case 1 : printf("%10s , %d", "January", yr); break;
        case 2 : printf("%10s , %d", "Febryary", yr); break;
        case 3 : printf("%10s , %d", "March", yr); break;
        case 4 : printf("%10s , %d", "April", yr); break;
        case 5 : printf("%10s , %d", "MAy", yr); break;
        case 6 : printf("%10s , %d", "June", yr); break;
        case 7 : printf("%10s , %d", "July", yr); break;
        case 8 : printf("%10s , %d", "August", yr); break;
        case 9 : printf("%10s , %d", "September", yr); break;
        case 10 : printf("%10s , %d", "October", yr); break;
        case 11 : printf("%10s , %d", "November", yr); break;
        case 12 : printf("%10s , %d", "December", yr); break;
    }
    
    switch(mon)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            days_in_month=31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            days_in_month=30;
            break;
        case 2:
            days_in_month=28+isLeap(yr);
            break;
    }

    for(dayNum=1, dayCtr=dow(yr,mon,1); dayNum <= days_in_month; dayNum+=1, dayCtr+=1)
    {
        if(dayCtr==DIM)
        {
            dayCtr = 0;
            row+=2;
        }
        gotoxy(col + dayCtr * (WIDTH+1),row);
        printf("%02d", dayNum);
    }
}

int main()
{
    int key;
    int month, year;
    month = 3;
    year = 2022;
    
    do
    {
        drawBox();
        colHeadings();
        printCalendar(month, year);
        while(bioskey(1) == 0);
        key = bioskey(0);
        
        switch(key)
        {
            case LEFT : month --; break;
            case RIGHT : month ++; break;
            case UP : year-=1; break;
            case DOWN : year += 1; break;
            case HOME : month = 1; break;
            case END : month = 12;
        }
        if(month > 12)
        {
            month = 1;
            year+=1;
        }
        else if( month < 1)
        {
            month = 12;
            year -=1;
        }
    }
    while(key!= ESC);
    getch();
    
    return 0;
}
