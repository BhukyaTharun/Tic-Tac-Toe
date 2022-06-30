#include <stdio.h>
#include <stdlib.h>
#include<time.h>

char board[4][4]; int n=3;
char player[2] = {'O','X'};

void init();
void showconfig(void);
int checkwin(void);
int checkwinPlayer(char);
int checklegal(int, int);
void putsymbol(int,int,char);
void fillup(int,char);
void PvP();
void Easy();
void Moderate();
void Hard();
int checkok();

void PvP(){
    // Assume 1 and 2 are used for O and X.
    int p = 0,count=0;
    while (checkwin() && count<9)
    {
        showconfig();
        printf("Player %c turn : ",player[p]);

        int d;
        printf("Select a number from 1 to 9\n");

        scanf("%d",&d);
        d--;
        int i=d/3,j=d%3;
    // note p+1 is either 1 or 2.
        if (checklegal(i,j) == 0) {
            printf("Invalid move");
            continue;
        }
        putsymbol(i,j,player[p]);
        p = (p+1) % 2;
        count++;
    }
    showconfig();
    if(count==9) printf("Game ended in a draw");
    else printf("Game Over");
}

void Easy(){
    printf("In this game mode you are given symbol 'O' & the first chance to place a symbol\n");

    int p = 0,count=0;
    while (checkwin() && count<9)
    {
        if(p==0){
            showconfig();
            printf("Player %c turn : ",player[p]);

            int d;
            printf("Select a number from 1 to 9\n");

            scanf("%d",&d);
            d--;
            int i=d/3,j=d%3;
            // note p+1 is either 1 or 2.
            if (checklegal(i,j) == 0) {
                printf("Invalid move");
                continue;
            }
            putsymbol(i,j,player[p]);
            p = (p+1) % 2;
            count++;
        }
        else{
            int d=rand()%9;
            int i=d/3,j=d%3;
            while(checklegal(i,j)==0){
                d=rand()%9;
                i=d/3;
                j=d%3;
            }
            putsymbol(i,j,player[p]);
            count++;
            p = (p+1) % 2;
        }
    }
    showconfig();
    if(count==9) printf("Game ended in a draw");
    else printf("Game Over");
}

void Moderate(){
    printf("In this game mode you are given symbol 'O' & the first chance to place a symbol\n");

    int f[10]={0};
    int p = 0,count=0;
    while (checkwin() && count<9)
    {
        if(p==0){
            showconfig();
            printf("Player %c turn : ",player[p]);

            int d;
            printf("Select a number from 1 to 9\n");

            scanf("%d",&d);
            f[d]++;
            d--;
            int i=d/3,j=d%3;
            // note p+1 is either 1 or 2.
            if (checklegal(i,j) == 0) {
                printf("Invalid move");
                continue;
            }
            putsymbol(i,j,player[p]);
            p = (p+1) % 2;
            count++;
        }
        else{
            int r[10]={0};
            int size=0;
            int flag=0;
            for(int i=1;i<=9;i++){
                if(f[i]==0) {
                    r[size]=i;
                    size++;
                }
            }
            for(int i=0;i<=size;i++){
                int d=r[i]-1;
                int x=d/3;
                int y=d%3;
                putsymbol(x,y,'O');
                if(checkwinPlayer('O')){
                    putsymbol(x,y,'X');
                    flag=1;
                    f[d+1]++;
                    break;
                }
                else{
                    putsymbol(x,y,' ');
                }
            }
            if(flag!=1){
                int d=rand()%9;
                int i=d/3,j=d%3;
                while(checklegal(i,j)==0){
                    d=rand()%9;
                    i=d/3;
                    j=d%3;
                }
                f[d+1]++;
                putsymbol(i,j,player[p]);
            }
            p = (p+1) % 2;
            count++;
        }
    }
    showconfig();
    if(count==9) printf("Game ended in a draw");
    else printf("Game Over");
}

int main()
{
    init();

    printf("Welcome to the world of Tic-Tac-Toe\n");
    printf("How would you like to the play the game\n");
    printf("1. With a friend\n");
    printf("2. With me (computer)\n");
    printf("Enter 1 or 2 accordingly\n");
    
    int option;

    scanf("%d",&option);

    printf("Sorry to interrupt you but since it is a normal C program\n");
    printf("You have to select the box you would like to place your symbol by entering a number as below\n");

    printf("\n-------------\n");
    for (int i=0; i<n; i++)
    {
      for (int j=0; j<n; j++)
        printf("| %d ",i*3+j+1);
      printf("|\n-------------\n");
    }

    printf("Since it is much similar to a phone dialpad, I hope it is ok :)\n");

    if(option==2){
        printf("Please select the difficutly that you want\n");
        printf("1. Easy\n");
        printf("2. Moderate\n");
        printf("3. Hard (Under process)\n");
        printf("This is not a touch screen, please enter the number accordingly\n");

        int op;

        scanf("%d",&op);

        if(op==1){
            Easy();
        }

        else if(op==2){
            Moderate();
        }
        else{
            Hard();
        }
    }
    else if(option==1){
        PvP();
    }
    else{
        printf("Only play smart in the game, not with me -_-");
    }
    return 0;
}

void init()
{
    for(int i=0;i<n;i++)
      for(int j=0;j<n;j++)
        board[i][j]=' ';
}

void showconfig()
{
    printf("\n-------------\n");
    for (int i=0; i<n; i++)
    {
      for (int j=0; j<n; j++)
        printf("| %c ",board[i][j]);
      printf("|\n-------------\n");
    }
}

int checkok(int d){
    d--;
    int i=d/3;
    int j=d%3;
    if(board[i][j]!=' ') return 0;
    else return 1;
}

int checklegal(int i,int j){
    if(board[i][j]==' ') return 1;
    else return 0;
}

void fillup(int d,char c){
    d--;
    int i=d/3;
    int j=d%3;
    board[i][j]=c;
}

void putsymbol(int i,int j,char c){
    board[i][j]=c;
}

int checkwin()
{   
    int o,x;
    o=checkwinPlayer('O');
    if(o==1) {
        printf("Player O won\n");
        return 0;
    }
    x=checkwinPlayer('X');
    if(x==1){
        printf("Player X won\n");
        return 0;
    }
    return 1;
}

int checkwinPlayer(char sym)
{
    int flag=0;
    for(int i=0;i<3;i++){
        if(board[i][0]==sym && board[i][1]==sym && board[i][2]==sym) flag=1;
    }
    for(int j=0;j<3;j++){
        if(board[0][j]==sym && board[1][j]==sym && board[2][j]==sym) flag=1;
    }
    if(board[0][0]==sym && board[1][1]==sym && board[2][2]==sym) flag=1;
    if(board[0][2]==sym && board[1][1]==sym && board[2][0]==sym) flag=1;
    return flag;
}

void Hard(){
    printf("In this game mode I take the symbol 'O' and also the first chance");
    printf("Be careful while giving input because in this hard level I don't give another chance if you make mistake\n");
    printf("And I will win the game\n");
    board[1][1]='O';
    showconfig();
    int d;
    printf("Player X turn:\n");
    printf("Enter a number from 1 to 9\n");
    scanf("%d",&d);
    if(!checkok(d)){
        printf("YOU LOST due to silly mistake LOSER\n");
        return;
    }
    if(d%2==0){
        fillup(d,'X');
        board[0][0]='O';
        showconfig();
        if(d==2){
            printf("Player X turn:\n");
            printf("Enter a number from 1 to 9\n");
            scanf("%d",&d);

            if(!checkok(d)){
                printf("YOU LOST due to silly mistake LOSER\n");
                return;
            }

            if(d==9){
                fillup(9,'X');
                fillup(7,'O');
                showconfig();

                printf("Player X turn:\n");
                printf("Enter a number from 1 to 9\n");
                scanf("%d",&d);

                
                if(!checkok(d)){
                    printf("YOU LOST due to silly mistake LOSER\n");
                    return;
                }

                if(d==3){
                    fillup(3,'X');
                    fillup(4,'O');

                }
                else{
                    fillup(d,'X');
                    fillup(3,'O');
                }
                showconfig();
                printf("I won and I will take over the world\n");
                printf("GameOver");
            }
            else{
                fillup(d,'X');
                fillup(9,'O');
                showconfig();
                printf("I won and I will take over the world\n");
                printf("GameOver");
            }
        }
        else if(d==4){
            printf("Player X turn:\n");
            printf("Enter a number from 1 to 9\n");
            scanf("%d",&d);

            
            if(!checkok(d)){
                printf("YOU LOST due to silly mistake LOSER\n");
                return;
            }

            if(d==9){
                fillup(9,'X');
                fillup(3,'O');
                showconfig();

                printf("Player X turn:\n");
                printf("Enter a number from 1 to 9\n");
                scanf("%d",&d);

                
                if(!checkok(d)){
                    printf("YOU LOST due to silly mistake LOSER\n");
                    return;
                }

                if(d==7){
                    fillup(7,'X');
                    fillup(2,'O');

                }
                else{
                    fillup(d,'X');
                    fillup(7,'O');
                }
                showconfig();
                printf("I won and I will take over the world\n");
                printf("GameOver");
            }
            else{
                fillup(d,'X');
                fillup(9,'O');
                showconfig();
                printf("I won and I will take over the world\n");
                printf("GameOver");
            }
        }
        else if(d==6){
            printf("Player X turn:\n");
            printf("Enter a number from 1 to 9\n");
            scanf("%d",&d);

            
            if(!checkok(d)){
                printf("YOU LOST due to silly mistake LOSER\n");
                return;
            }

            if(d==9){
                fillup(9,'X');
                fillup(3,'O');
                showconfig();

                printf("Player X turn:\n");
                printf("Enter a number from 1 to 9\n");
                scanf("%d",&d);

                
                if(!checkok(d)){
                    printf("YOU LOST due to silly mistake LOSER\n");
                    return;
                }

                if(d==7){
                    fillup(7,'X');
                    fillup(2,'O');

                }
                else{
                    fillup(d,'X');
                    fillup(7,'O');
                }
                showconfig();
                printf("I won and I will take over the world\n");
                printf("GameOver");
            }
            else{
                fillup(d,'X');
                fillup(9,'O');
                showconfig();
                printf("I won and I will take over the world\n");
                printf("GameOver");
            }
        }
        else{
            printf("Player X turn:\n");
            printf("Enter a number from 1 to 9\n");
            scanf("%d",&d);

            
            if(!checkok(d)){
                printf("YOU LOST due to silly mistake LOSER\n");
                return;
            }

            if(d==9){
                fillup(9,'X');
                fillup(7,'O');
                showconfig();

                printf("Player X turn:\n");
                printf("Enter a number from 1 to 9\n");
                scanf("%d",&d);

                
                if(!checkok(d)){
                    printf("YOU LOST due to silly mistake LOSER\n");
                    return;
                }

                if(d==3){
                    fillup(3,'X');
                    fillup(4,'O');

                }
                else{
                    fillup(d,'X');
                    fillup(3,'O');
                }
                showconfig();
                printf("I won and I will take over the world\n");
                printf("GameOver");
            }
            else{
                fillup(d,'X');
                fillup(9,'O');
                showconfig();
                printf("I won and I will take over the world\n");
                printf("GameOver");
            }
        }
    }
    else{ 
        int f[10]={0};
        f[5]=1;
        int p = 0,count=2;
        
        if(!checkok(d)){
            printf("YOU LOST due to silly mistake LOSER\n");
            return;
        }
        else fillup(d,'X');
        f[d]++;
        showconfig();
        while (checkwin() && count<9)
        {
            if(p==1){
                showconfig();
                printf("Player %c turn : ",player[p]);

                int d;
                printf("Select a number from 1 to 9\n");

                scanf("%d",&d);
                f[d]++;
                d--;
                int i=d/3,j=d%3;
                // note p+1 is either 1 or 2.
                if (checklegal(i,j) == 0) {
                printf("Invalid move");
                continue;
            }
            putsymbol(i,j,player[p]);
            p = (p+1) % 2;
            count++;
        }
        else{
            int r[10]={0};
            int size=0;
            int flag=0;
            for(int i=1;i<=9;i++){
                if(f[i]==0) {
                    r[size]=i;
                    size++;
                }
            }
            for(int i=0;i<=size;i++){
                int d=r[i]-1;
                int x=d/3;
                int y=d%3;
                putsymbol(x,y,'X');
                if(checkwinPlayer('X')){
                    putsymbol(x,y,'O');
                    flag=1;
                    f[d+1]++;
                    break;
                }
                else{
                    putsymbol(x,y,' ');
                }
            }
            if(flag!=1){
                int d=rand()%9;
                int i=d/3,j=d%3;
                while(checklegal(i,j)==0){
                    d=rand()%9;
                    i=d/3;
                    j=d%3;
                }
                f[d+1]++;
                putsymbol(i,j,'O');
            }
            p = (p+1) % 2;
            count++;
        }
    }
    showconfig();
    if(count==9) printf("Game ended in a draw");
    else printf("Game Over");  
    }
}
