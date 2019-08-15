#include<stdio.h>
#include<time.h>
#include<conio.h>
#include<windows.h>

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

int score=0;
int board[4][4]= {
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
};

void Wait(int seconds);
void Countdown(void);
void AD(void);
void Draw(void);
void NewNum(void);
void CheckGameOver(void);
void TextColor(int foreground, int background);


int main (void) {
    int i, j, r, key, move;

    Countdown();
    AD();
    NewNum();
    NewNum();
    Draw();

    while(1) {
        key=getch();
        if(key==0xE0||key==0) {
            key=getch();
            switch(key) {
                case LEFT:
                    for (i=0,move=0;i<4;i++) {
                        for (j=1;j<=3;j++) {
                            for (r=j;r>0;r--) {
                                if(board[i][r]==0||board[i][r]>10000) break;
                                if(board[i][r-1]!=0&&board[i][r-1]!=board[i][r]) break;

                                if(board[i][r-1]==0) board[i][r-1]=board[i][r];
                                else if(board[i][r] == board[i][r-1]) {
                                    board[i][r-1]*=2;
                                    board[i][r-1]+=10000;
                                    score+=2*(board[i][r]);
                                }

                                board[i][r]=0;
                                move++;
                            }
                        }
                    }
                    break;
                case RIGHT:
                    for (i=0,move=0;i<4;i++) {
                        for (j=2;j>=0;j--) {
                            for (r=j;r<3;r++) {
                                if(board[i][r]==0||board[i][r]>10000) break;
                                if(board[i][r+1]!=0&&board[i][r+1]!=board[i][r]) break;

                                if(board[i][r+1]==0) board[i][r+1]=board[i][r];
                                else if(board[i][r]==board[i][r+1]) {
                                    board[i][r+1]*=2;
                                    board[i][r+1]+=10000;
                                    score+=2*(board[i][r]);
                                }

                                board[i][r]=0;
                                move++;
                            }
                        }
                    }
                    break;
                case UP:
                    for (j=0,move=0;j<4;j++) {
                        for (i=1;i<=3;i++) {
                            for (r=i;r>0;r--) {
                                if(board[r][j]==0||board[r][j]>10000) break;
                                if(board[r-1][j]!=0&&board[r-1][j]!=board[r][j]) break;

                                if(board[r-1][j]==0) board[r-1][j]=board[r][j];
                                else if(board[r][j]==board[r-1][j]) {
                                    board[r-1][j]*=2;
                                    board[r-1][j]+=10000;
                                    score+=2*(board[r][j]);
                                }

                                board[r][j]=0;
                                move++;
                            }
                        }
                    }
                    break;
                case DOWN:
                    for (j=0,move=0;j<4;j++) {
                        for (i=2;i>=0;i--) {
                            for (r=i;r<3;r++) {
                                if(board[r][j]==0||board[r][j]>10000) break;
                                if(board[r+1][j]!=0&&board[r+1][j]!=board[r][j]) break;

                                if(board[r+1][j]==0) board[r+1][j]=board[r][j];
                                else if(board[r][j] == board[r+1][j]) {
                                    board[r+1][j]*=2;
                                    board[r+1][j]+=10000;
                                    score+=2*(board[r][j]);
                                }

                                board[r][j]=0;
                                move++;
                            }
                        }
                    }
                    break;
            }
        }
        for (i=0;i<4;i++)
            for (j=0;j<4;j++)
                if(board[i][j]>10000) board[i][j]-=10000;

        if(move>0) {
            NewNum();
            Draw();
            CheckGameOver();
        }
    }
}

void Wait(int seconds) {
    clock_t endwait;
    endwait = clock() + seconds * CLOCKS_PER_SEC;

    while (clock() < endwait);
}

void Countdown(void) {
    int n;

    printf("  Starting countdown...\n ");
    for (n = 10; n > 0; n--) {
        printf("%d ", n)
        Wait(1);
    }
}

void AD(void) {
    printf("\n\n\n");

    TextColor(YELLOW, BLACK); {
        printf("   ■■■■   ■■■■      ■    ■■■■ \n");
        printf("         ■   ■    ■    ■■    ■    ■ \n");
        printf("   ■■■■   ■    ■   ■ ■    ■■■■ \n");
        printf("   ■         ■    ■  ■■■■  ■    ■ \n");
        printf("   ■■■■   ■■■■      ■    ■■■■ \n");
    }

    Wait(1);
}

void Draw(void) {
    int i, j;

    TextColor(WHITE, BLACK);
    system("cls");
    printf("\n\n");

    for (i=0;i<4;i++) {
        for (j=0;j<4;j++) {
            if (board[i][j] == 0) printf("    .");
            else printf("%5d", board[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");
    TextColor(GREEN, BLACK);
    printf("   Score : %d \n", score);
}

void NewNum(void) {
    int i, j, cnt;
    int* p0[16]= {0};

    for (i=0, cnt=0;i<4;i++)
        for (j=0;j<4;j++)
            if(board[i][j] == 0) {
                p0[cnt]=&board[i][j];
                cnt++;

    *p0[rand()%(cnt)] =(rand()%100<80)?2:4;
}

void CheckGameOver(void) {
    int i, j;

    for (i=0;i<4;i++)
        for (j=0;j<4;j++)
            if(board[i][j]==0) return;

    for (i=0;i<3;i++)
        for (j=0;j<3;j++)
            if(board[i][j]==board[i+1][j]||board[i][j]==board[i][j+1]) return;

    for (i=0;i<3;i++) if(board[i][3]==board[i+1][3]) return;

    for (j=0;j<3;j++) if(board[3][j]==board[3][j+1]) return;

    Wait(1);
    system("cls");
    TextColor(RED, BLACK);
    printf("\n  Game Over..");
    exit(0);
}

void TextColor(int foreground, int background) {
    int color=foreground+background*16;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}