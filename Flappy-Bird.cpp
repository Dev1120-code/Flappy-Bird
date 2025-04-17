#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<thread>
#include<chrono>
int highScore=0;

#ifdef _WIN32
#include<conio.h>
#include<windows.h>
#define CLEAR "cls"
#else
#include<unistd.h>
#include<termios.h>
#include<sys/ioctl.h>
#define CLEAR "clear"
#endif

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
#define MENU_WIDTH 20
#define GAP_SIZE 7
#define PIPE_DIF 45

using namespace std;

#ifdef _WIN32
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
#endif

int pipePos[3];
int gapPos[3];
int pipeFlag[3];
char bird[2][6] = { '/','-','-','o','\\',' ',
                    '|','','','_',' ','>' };
int birdPos = 6;
int score = 0;
void loadHighScore() {
    FILE* file = fopen("highscore.txt", "r");
    if (file) {
        fscanf(file, "%d", &highScore);
        fclose(file);
    } else {
        highScore = 0;
    }
}
void saveHighScore() {
    FILE* file = fopen("highscore.txt", "w");
    if (file) {
        fprintf(file, "%d", highScore);
        fclose(file);
    }
}


// Color functions
void red()     { cout << "\033[1;31m"; }
void green()   { cout << "\033[1;32m"; }
void yellow()  { cout << "\033[1;33m"; }
void blue()    { cout << "\033[1;34m"; }
void magenta() { cout << "\033[1;35m"; }
void cyan()    { cout << "\033[1;36m"; }
void reset()   { cout << "\033[0m"; }

void gotoxy(int x, int y) {
#ifdef _WIN32
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
#else
    cout << "\033[" << y+1 << ";" << x+1 << "H";
#endif
}

#ifdef _WIN32
void setcursor(bool visible, DWORD size) {
    if(size == 0)
        size = 20;    

    CONSOLE_CURSOR_INFO lpCursor;    
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console,&lpCursor);
}
#else
void setcursor(bool visible, int size) {
    // Not implemented for Linux
}
#endif

#ifdef linux
int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (!initialized) {
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

char _getch() {
    char ch;
    read(STDIN_FILENO, &ch, 1);
    return ch;
}
#endif

void drawBorder(){ 
    blue();
    for(int i=0; i<SCREEN_WIDTH; i++){
        gotoxy(i,0); cout<<"±";
        gotoxy(i,SCREEN_HEIGHT); cout<<"±";
    }

    for(int i=0; i<SCREEN_HEIGHT; i++){
        gotoxy(0,i); cout<<"±";
        gotoxy(SCREEN_WIDTH,i); cout<<"±";
    }
    for(int i=0; i<SCREEN_HEIGHT; i++){
        gotoxy(WIN_WIDTH,i); cout<<"±";
    }
    reset();
}

void genPipe(int ind){
    gapPos[ind] = 3 + rand()%14; 
}

void drawPipe(int ind) {
    if (pipeFlag[ind] == true) {
        green();
        for (int i = 0; i < gapPos[ind]; i++) {
            gotoxy(WIN_WIDTH - pipePos[ind], i + 1);
            cout << "***";
        }
        for (int i = gapPos[ind] + GAP_SIZE; i < SCREEN_HEIGHT - 1; i++) {
            gotoxy(WIN_WIDTH - pipePos[ind], i + 1);
            cout << "***";
        }
        reset();
    }
}

void erasePipe(int ind){
    if( pipeFlag[ind] == true ){
        for(int i=0; i<gapPos[ind]; i++){ 
            gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout<<"   "; 
        }
        for(int i=gapPos[ind]+GAP_SIZE; i<SCREEN_HEIGHT-1; i++){ 
            gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout<<"   "; 
        }
    }
}

void drawBird(){
    red();
    for(int i=0; i<2; i++){
        for(int j=0; j<6; j++){
            gotoxy(j+2,i+birdPos); cout<<bird[i][j];
        }
    }
    reset();
}

void eraseBird(){
    for(int i=0; i<2; i++){
        for(int j=0; j<6; j++){
            gotoxy(j+2,i+birdPos); cout<<" ";
        }
    }
}

int collision(){
    if( pipePos[0] >= 61  ){
        if( birdPos<gapPos[0] || birdPos >gapPos[0]+GAP_SIZE ){
            return 1;
        }
    }
    return 0;
}

void debug(){ }

void gameover(){
    if (score > highScore) {
        highScore = score;
        saveHighScore();
    }
    system(CLEAR);
    red();
    cout<<endl;
    cout<<"\t\t--------------------------"<<endl;
    cout<<"\t\t-------- Game Over -------"<<endl;
    cout<<"\t\t--------------------------"<<endl<<endl;
    reset();
    cout<<"\t\tPress any key to go back to menu.";
#ifdef _WIN32
    getch();
#else
    _getch();
#endif
}

void updateScore(){
    yellow();
    gotoxy(WIN_WIDTH + 7, 5);cout<<"Score: "<<score<<endl;
    gotoxy(WIN_WIDTH + 7, 6); cout << "High:  " << highScore<<endl;
    reset();
}

void instructions(){
    system(CLEAR);
    cyan();
    cout<<"Instructions";
    cout<<"\n----------------";
    cout<<"\n Press spacebar to make bird fly";
    cout<<"\n\nPress any key to go back to menu";
    reset();
#ifdef _WIN32
    getch();
#else
    _getch();
#endif
}

void play(){
    birdPos = 6;
    score = 0;
    pipeFlag[0] = 1; 
    pipeFlag[1] = 0;
    pipePos[0] = pipePos[1] = 4;

    system(CLEAR); 
    drawBorder();
    genPipe(0);
    updateScore();

    magenta();
    gotoxy(WIN_WIDTH + 5, 2);cout<<"FLAPPY BIRD";
    gotoxy(WIN_WIDTH + 6, 4);cout<<"----------";
    gotoxy(WIN_WIDTH + 6, 6);cout<<"----------";
    gotoxy(WIN_WIDTH + 7, 12);cout<<"Control ";
    gotoxy(WIN_WIDTH + 7, 13);cout<<"-------- ";
    gotoxy(WIN_WIDTH + 2, 14);cout<<" Spacebar = jump";
    reset();

    gotoxy(10, 5);cout<<"Press any key to start";
#ifdef _WIN32
    getch();
#else
    _getch();
#endif
    gotoxy(10, 5);cout<<"                      ";

    while(1){
#ifdef _WIN32
        if(kbhit()){
            char ch = getch();
#else
        if(_kbhit()){
            char ch = _getch();
#endif
            if(ch==32){
                if( birdPos > 3 ) birdPos-=3;
            } 
            if(ch==27){
                break;
            }
        }

        drawBird();
        drawPipe(0);
        drawPipe(1);
        debug();
        if( collision() == 1 ){
            gameover();
            return;
        }

#ifdef _WIN32
        Sleep(100);
#else
        usleep(100000); // microseconds
#endif

        eraseBird();
        erasePipe(0);
        erasePipe(1);
        birdPos += 1;

        if( birdPos > SCREEN_HEIGHT - 2 ){
            gameover();
            return;
        }

        if( pipeFlag[0] == 1 )
            pipePos[0] += 2;

        if( pipeFlag[1] == 1 )
            pipePos[1] += 2;

        if( pipePos[0] >= 40 && pipePos[0] < 42 ){
            pipeFlag[1] = 1;
            pipePos[1] = 4;
            genPipe(1);
        }
        if( pipePos[0] > 68 ){
            score++;
            updateScore();
            pipeFlag[1] = 0;
            pipePos[0] = pipePos[1];
            gapPos[0] = gapPos[1];
        }
    }
}

int main() {
    setcursor(0,0); 
    srand( (unsigned)time(NULL)); 
    loadHighScore();

    do{
        system(CLEAR);
        magenta();
        gotoxy(10,5); cout<<" -------------------------- "; 
        gotoxy(10,6); cout<<" |      Flappy Bird       | "; 
        gotoxy(10,7); cout<<" --------------------------";
        reset();
        gotoxy(10,9); yellow();cout<<"1. Start Game";
        gotoxy(10,10); yellow();cout<<"2. Instructions";     
        gotoxy(10,11); yellow();cout<<"3. Quit";
        gotoxy(10,13); yellow();cout<<"Select option: ";
#ifdef _WIN32
        char op = getche();
#else
        char op = _getch();
        cout << op;
#endif

        if( op=='1') play();
        else if( op=='2') instructions();
        else if( op=='3') exit(0);

    }while(1);

    return 0;
}
