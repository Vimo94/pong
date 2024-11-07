#include <stdio.h>
/* Объявление функций */
int raket_pos();
void field();
int ball_pos();
/* Объявление переменных с размерами стола, координатами ракеток и мяча */
int x_ball = 40;
int y_ball = 12;
int raket_left = 12;
int raket_right = 12;
int width = 80, hight = 25;

char press;
int x_ball_vect = 1, y_ball_vect = 1;
int left_player = 20;
int right_player = 20;

int main() {
    while (press != 'w') {
        field();
        raket_pos();
        if (press == 'a' || press == ' ' || press == 'z' || press == 'k' || press == 'm' || press == 'A' ||
            press == 'Z' || press == 'K' || press == 'M') {
            ball_pos();
            if (left_player == 21) {
                printf("\e[H\e[2J\e[3J");
                field();
                printf("THE LEFT PLAYER WON!\n");
                break;
            } else if (right_player == 21) {
                printf("\e[H\e[2J\e[3J");
                field();
                printf("THE RIGHT PLAYER WON!\n");
                break;
            }
        }
        /* выводит cls/clear. Это говорит терминалу переместить курсор
        в верхний левый угол ( \e[H), очистить экран ( \e[2J) и очистить
        буфер прокрутки ( \e[3J).*/
        printf("\e[H\e[2J\e[3J");
    }

    return 0;
}
/* Функция отображения поля, мяча, ракеток */
void field() {
    for (int i = 0; i < hight; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == hight - 1) {
                printf("-");  // отображение сторон
            } else if (j == 0 || j == width - 1) {
                printf("#");
            } else if (j == x_ball && i == y_ball) {
                printf("@");  // отображение мяча
            } else if (j == 1 && i == raket_left - 1) {
                printf("|");  // отображение левой ракетки
            } else if (j == 1 && i == raket_left) {
                printf("|");  // отображение левой ракетки
            } else if (j == 1 && i == raket_left + 1) {
                printf("|");  // отображение левой ракетки
            } else if (j == 78 && i == raket_right - 1) {
                printf("|");  // отображение правой ракетки
            } else if (j == 78 && i == raket_right) {
                printf("|");  // отображение правой ракетки
            } else if (j == 78 && i == raket_right + 1) {
                printf("|");  // отображение правой ракетки
            } else if (j == 38 || j == 39) {
                printf(":");  //  отображение сетки
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    for (int i = 0; i < 38; i++) {  // Табло счета
        printf(" ");
        if (i == 35) {
            printf("%d :: %d\n", left_player, right_player);
        }
        if (i == 37) {
            printf("***PRESS W+ENTER FOR EXIT***\n");
        }
    }
}
/* Передвижение мяча */
int ball_pos() {
    if (y_ball == 1 || y_ball == hight - 2) {
        y_ball_vect = -y_ball_vect;
    } else if (x_ball == 77 && (y_ball == raket_right - 1 || y_ball == raket_right ||
                                y_ball == raket_right + 1)) {  // Отскок от левой
        x_ball_vect = -x_ball_vect;
    } else if (x_ball == 1 && (y_ball == raket_left - 1 || y_ball == raket_left ||
                               y_ball == raket_left + 1)) {  // Отскок от правой
        x_ball_vect = -x_ball_vect;
    }

    x_ball += x_ball_vect;  // смещение по оси Х\У
    y_ball += y_ball_vect;
    if (x_ball < 1) {  // если положение мяча по Х меньше 1 , то засчитываются
                       // очки второму игроку
        right_player += 1;
        x_ball = 40;  // возвращает начальное положение мяча по центру
        y_ball = 12;
    }
    if (x_ball > width - 2) {  // при вылете мяча, засчитываются очки первому игроку
        left_player += 1;
        x_ball = 40;  // возвращает начальное положение мяча по центру
        y_ball = 12;
    }

    return 0;
}
/* передвижение ракеток */
int raket_pos() {
    press = getchar();
    if (press == 'a' || press == ' ' || press == 'z' || press == 'k' || press == 'm' || press == 'A' ||
        press == 'Z' || press == 'K' || press == 'M') {
        if (press == 'a') {
            if (raket_left != 2) raket_left--;
        } else if (press == 'z') {
            if (raket_left != hight - 3) raket_left++;
        } else if (press == 'k') {
            if (raket_right != 2) raket_right--;
        } else if (press == 'm') {
            if (raket_right != hight - 3) raket_right++;
        }
        return 0;
    }
    return 0;
}