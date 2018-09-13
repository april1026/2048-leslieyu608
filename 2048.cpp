#include<iostream>
#include<windows.h>
#include<ctime>
#include<conio.h>
#define DIRECTION 224
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
using namespace std;

void gotoxy(int xpos, int ypos) {
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos; scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput,scrn);
}

void SetColor(int f=7,int b=0) {
    unsigned short ForeColor=f+16*b;
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon,ForeColor);
}

void table();

void clear(int **arr);
void gnrt(int *posX, int *posY, int **arr, int prblty);

void apr(int **arr);
void filling(int x, int y);

void up(int *ptr, int **arr1, int **arr2, int **arr3);
void down(int *ptr, int **arr1, int **arr2, int **arr3);
void left(int *ptr, int **arr1, int **arr2, int **arr3);
void right(int *ptr, int **arr1, int **arr2, int **arr3);

void cmb(int posX1, int posX2, int posY1, int posY2, int **arr1, int **arr2, int situtn);
void mrz(int **arr1, int **arr2);
void cmpr(int *ptr, int **arr1, int **arr2);

int main()
{
    int x = 0, y = 0;
    int *ptrX = &x, *ptrY = &y;
    
    int **num;
    num = new int *[4];
    for (int i = 0; i < 4; i++) {
        *(num+i) = new int [4];
    }
    clear(num);
    
    int **rule;
    rule = new int *[4];
    for (int i = 0; i < 4; i++) {
        *(rule+i) = new int [4];
    }
    clear(rule);
    
    int **old;
    old = new int *[4];
    for (int i = 0; i < 4; i++) {
        *(old+i) = new int [4];
    }
    clear(old);
    
    table();
    int first = 0;
    gnrt(ptrX, ptrY, num, first);
    first++;
    gnrt(ptrX, ptrY, num, first);
    apr(num);
    
    int input = 0, result = 0;
    while (input = getch()) {
        result = 0;
        int *ptrR = &result;
        if (input == DIRECTION) {
            input = getch();
            switch (input) {
                case UP:
                    up(ptrR, num, rule, old);
                    if (result == 0) {
                        continue;
                    } else {
                        gnrt(ptrX, ptrY, num, first);
                        apr(num);
                        cmpr(ptrR, num, old);
                    }
                    break;
                case DOWN:
                    down(ptrR, num, rule, old);
                    if (result == 0) {
                        continue;
                    } else {
                        gnrt(ptrX, ptrY, num, first);
                        apr(num);
                        cmpr(ptrR, num, old);
                    }
                    break;
                case LEFT:
                    left(ptrR, num, rule, old);
                    if (result == 0) {
                        continue;
                    } else {
                        gnrt(ptrX, ptrY, num, first);
                        apr(num);
                        cmpr(ptrR, num, old);
                    }
                    break;
                case RIGHT:
                    right(ptrR, num, rule, old);
                    if (result == 0) {
                        continue;
                    } else {
                        gnrt(ptrX, ptrY, num, first);
                        apr(num);
                        cmpr(ptrR, num, old);
                    }
                    break;
                default:
                    break;
            }
            if (result == 2 || result == 3) {
                break;
            }
        }
    }
    gotoxy(0, 17);
    if (result == 2) {
        cout << "YOU WIN!" << endl;
    } else if (result == 3) {
        cout << "YOU LOSE...TRY AGAIN...?" << endl;
    }
    system("pause");
    return 0;
}

void table() { 
    cout << "╔═══╦═══╦═══╦═══╗" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "║      ║      ║      ║      ║" << endl;
        }
        if (i == 3) {
            cout << "╚═══╩═══╩═══╩═══╝" << endl;
        } else {
            cout << "╠═══╬═══╬═══╬═══╣" << endl;
        }
    }
}

void clear(int **arr) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            *(*(arr+i)+j) = 0;
        }
    }
}

void gnrt(int *posX, int *posY, int **arr, int prblty) {
    int random;
    while (1) {
        srand(time(0));
        *posX = rand() % 4;
        *posY = rand() % 4;
        if (prblty == 0) {
            random = rand() % 3;
        } else if (prblty == 1) {
            random = rand() % 4;
        }
        if (*(*(arr+*posY)+*posX) != 0) {
            continue;
        } else if (*(*(arr+*posY)+*posX) == 0 && random == 0) {
            *(*(arr+*posY)+*posX) = 4;
            break;
        } else if (*(*(arr+*posY)+*posX) == 0){
            *(*(arr+*posY)+*posX) = 2;
            break;
        }
    }
}

void apr(int **arr) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            gotoxy(2+j*8, 1+i*4);
            switch (*(*(arr+i)+j)) {
                case 0:
                    SetColor();
                    filling(j, i);
                    cout << "  " << *(*(arr+i)+j) << "   ";
                    break;
                case 2:
                    SetColor(15, 4);
                    filling(j, i);
                    cout << "  " << *(*(arr+i)+j) << "   ";
                    break;
                case 4:
                    SetColor(15, 12);
                    filling(j, i);
                    cout << "  " << *(*(arr+i)+j) << "   ";
                    break;
                case 8:
                    SetColor(15, 6);
                    filling(j, i);
                    cout << "  " << *(*(arr+i)+j) << "   ";
                    break;
                case 16:
                    SetColor(0, 14);
                    filling(j, i);
                    cout << "  " << *(*(arr+i)+j) << "  ";
                    break;
                case 32:
                    SetColor(15, 2);
                    filling(j, i);
                    cout << "  " << *(*(arr+i)+j) << "  ";
                    break;
                case 64:
                    SetColor(0, 10);
                    filling(j, i);
                    cout << "  " << *(*(arr+i)+j) << "  ";
                    break;
                case 128:
                    SetColor(15, 3);
                    filling(j, i);
                    cout << " " << *(*(arr+i)+j) << "  ";
                    break;
                case 256:
                    SetColor(0, 11);
                    filling(j, i);
                    cout << " " << *(*(arr+i)+j) << "  ";
                    break;
                case 512:
                    SetColor(15, 1);
                    filling(j, i);
                    cout << " " << *(*(arr+i)+j) << "  ";
                    break;
                case 1024:
                    SetColor(15, 9);
                    filling(j, i);
                    cout << " " << *(*(arr+i)+j) << " ";
                    break;
                case 2048:
                    SetColor(15, 21);
                    filling(j, i);
                    cout << " " << *(*(arr+i)+j) << " ";
                    break;
                default:
                    break;
            }
        }
    }
    SetColor();
    gotoxy(0, 17);
}

void filling(int x, int y) {
    cout << "      ";
    gotoxy(2+x*8, 3+y*4);
    cout << "      ";
    gotoxy(2+x*8, 2+y*4);
}

void up(int *ptr, int **arr1, int **arr2, int **arr3) {
    mrz(arr1, arr3);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (j == 0) {
                continue;
            } else if (*(*(arr1+j)+i) != 0) {
                for (int k = j; k > 0; k--) {
                    int decide = 0;
                    if (*(*(arr1+k-1)+i) == 0) {
                        decide = 0;
                        cmb(i, i, k, k-1, arr1, arr2, decide);
                    } else if (*(*(arr2+k)+i) == 1) {
                        continue;
                    } else if (*(*(arr1+k-1)+i) == *(*(arr1+k)+i)) {
                        decide = 1;
                        cmb(i, i, k, k-1, arr1, arr2, decide);
                    }
                }
            }
        }
    }
    clear(arr2);
    cmpr(ptr, arr1, arr3);
}

void down(int *ptr, int **arr1, int **arr2, int **arr3) {
    mrz(arr1, arr3);
    for (int i = 0; i < 4; i++) {
        for (int j = 3; j > -1; j--) {
            if (j == 3) {
                continue;
            } else if (*(*(arr1+j)+i) != 0) {
                for (int k = j; k < 3; k++) {
                    int decide = 0;
                    if (*(*(arr1+k+1)+i) == 0) {
                        decide = 0;
                        cmb(i, i, k, k+1, arr1, arr2, decide);
                    } else if (*(*(arr2+k)+i) == 1) {
                        continue;
                    } else if (*(*(arr1+k+1)+i) == *(*(arr1+k)+i)) {
                        decide = 1;
                        cmb(i, i, k, k+1, arr1, arr2, decide);
                    }
                }
            }
        }
    }
    clear(arr2);
    cmpr(ptr, arr1, arr3);
}

void left(int *ptr, int **arr1, int **arr2, int **arr3) {
    mrz(arr1, arr3);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (j == 0) {
                continue;
            } else if (*(*(arr1+i)+j) != 0) {
                for (int k = j; k > 0; k--) {
                    int decide = 0;
                    if (*(*(arr1+i)+k-1) == 0) {
                        decide = 0;
                        cmb(k, k-1, i, i, arr1, arr2, decide);
                    } else if (*(*(arr2+i)+k) == 1) {
                        continue;
                    } else if (*(*(arr1+i)+k-1) == *(*(arr1+i)+k)) {
                        decide = 1;
                        cmb(k, k-1, i, i, arr1, arr2, decide);
                    }
                }
            }
        }
    }
    clear(arr2);
    cmpr(ptr, arr1, arr3);
}

void right(int *ptr, int **arr1, int **arr2, int **arr3) {
    mrz(arr1, arr3);
    for (int i = 0; i < 4; i++) {
        for (int j = 3; j > -1; j--) {
            if (j == 3) {
                continue;
            } else if (*(*(arr1+i)+j) != 0) {
                for (int k = j; k < 3; k++) {
                    int decide = 0;
                    if (*(*(arr1+i)+k+1) == 0) {
                        decide = 0;
                        cmb(k, k+1, i, i, arr1, arr2, decide);
                    } else if (*(*(arr2+i)+k) == 1) {
                        continue;
                    } else if (*(*(arr1+i)+k+1) == *(*(arr1+i)+k)) {
                        decide = 1;
                        cmb(k, k+1, i, i, arr1, arr2, decide);
                    }
                }
            }
        }
    }
    clear(arr2);
    cmpr(ptr, arr1, arr3);
}

void cmb(int posX1, int posX2, int posY1, int posY2, int **arr1, int **arr2, int situtn) {
    int blank = 0;
    if (situtn == 0) {
        blank = *(*(arr1+posY2)+posX2);
        *(*(arr1+posY2)+posX2) = *(*(arr1+posY1)+posX1);
        *(*(arr1+posY1)+posX1) = blank;
    } else if (situtn == 1) {
        *(*(arr1+posY2)+posX2) = *(*(arr1+posY1)+posX1)*2;
        *(*(arr1+posY1)+posX1) = 0;
        *(*(arr2+posY1)+posX1) = 1;
        *(*(arr2+posY2)+posX2) = 1;
    }
}

void mrz(int **arr1, int **arr2) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            *(*(arr2+i)+j) = *(*(arr1+i)+j);
        }
    }
}

void cmpr(int *ptr, int **arr1, int **arr2) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (*(*(arr1+i)+j) == *(*(arr1+i)+j+1) || *(*(arr1+j)+i) == *(*(arr1+j+1)+i)) {
                *ptr = 0;
                break;
            } else if (*(*(arr1+i)+j) != *(*(arr1+i)+j+1) && *(*(arr1+j)+i) != *(*(arr1+j+1)+i)) {
                *ptr = 3;
            }
        }
        if (*ptr != 3) {
            break;
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (*(*(arr1+i)+j) == 0 || *(*(arr1+j)+i) == 0) {
                *ptr = 0;
                break;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (*(*(arr1+i)+j) == 2048) {
                *ptr = 2;
                break;
            } else if (*ptr == 3) {
                break;
            } else if (*(*(arr2+i)+j) != *(*(arr1+i)+j)) {
                *ptr = 1;
            } 
        }
        if (*ptr == 2 || *ptr == 3) {
            break;
        }
    }
}
