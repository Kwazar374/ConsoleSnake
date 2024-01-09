
//Kwazar374 2023
//Snake

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define HEIGHT_OF_BOARD 20
#define WIDTH_OF_BOARD 50
#define SIZE_OF_BOARD (HEIGHT_OF_BOARD * WIDTH_OF_BOARD)

#define UP 'w'
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'

#define V_UP 'i'
#define V_DOWN 'k'
#define V_RIGHT 'l'
#define V_LEFT 'j'

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct snake {
    int x_coordinate;
    int y_coordinate;
    char direction; 
    struct snake *next;
};
typedef struct snake snake;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_cursor_position(int x, int y);
void hide_cursor(void);
void clear_screen(void);
void delete_snake_from_memory(snake *snake_head);
void clear_board(char *board);
void display_board(char *board, int raspberry_value, int *active_spells, int spell1, int spell2, int spell5, int spell6, int score);
void spawn_raspberry(char *board, int *raspberry_eaten, int *raspberry_position);
void spawn_dragon_fruit(char *board, int *dragon_fruit_eaten, int *dragon_fruit_position, int *active_spells);
void set_snake_direction(char *snake_direction, char *viper_direction, int dynamic_coefficient, double delta_time, int *active_spells, int is_viper_spawned);
void set_snake_position(snake *snake_head, char *board);
void change_snake_position(snake *snake_head, char snake_direction);
void extend_snake(snake *snake_head, int *length_of_snake);
void is_raspberry_eaten(snake *snake_head, char *board, int *raspberry_eaten, char snake_direction, int raspberry_position, int *score, int *border_crossed, int *length_of_snake, int *raspberry_value);
void change_snake_position_during_crossing_border(snake *snake_head, char snake_direction);
void change_snake_position_during_respawn_of_phoenix(snake *snake_head, int respawn_x_coordinate);
void set_viper_position(snake *viper_head, char *board);
void cast_spell(int *active_spells);
void fontsize(int x ,int y);        
int is_wall_touched(snake *snake_head, char *board, char snake_direction);
int is_dragon_fruit_eaten(snake *snake_head, char *board, int *dragon_fruit_eaten, char snake_direction, int dragon_fruit_position, int *border_crossed);
int is_snake_twisted(snake *snake_head, char snake_direction, int is_border_crossed);
int collision_check(snake *snake_head, snake *viper_head, char snake_direction, char viper_direction, int snake_is_border_crossed, int viper_is_border_crossed);
snake *create_snake(int x_coordinate, char direction);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int raspberry_value = 1;
    int game_over = 0;
    int player_ready = 1;
    int dynamic_coefficient;
    int score;
    int raspberry_position;
    int raspberry_eaten;
    int second_raspberry_position;
    int second_raspberry_eaten;
    int third_raspberry_position;
    int third_raspberry_eaten;
    int dragon_fruit_eaten;
    int dragon_fruit_position;
    int borders;
    int border_crossed;
    int v_border_crossed;
    int bin;
    int flag;
    int v_flag;
    int wall_assist;
    int spell1;
    int spell2;
    int spell3;
    int spell4;
    int spell5;
    int spell6;
    int spell2_prev_val;
    int dynamic_constant;
    int viper_spawned;
    int length_of_snake;
    int number_of_snakes;

    int active_spells[7];

    char decision = 'm';
    char gamemode = '0';
    char board[SIZE_OF_BOARD];
    char snake_direction = RIGHT;
    char viper_direction = LEFT;

    double delta_time;
    
    snake *snake_head = NULL;
    snake *viper_head = NULL;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    clock_t dt_start = 0, dt_end;
    srand(time(NULL));

    fontsize(25, 25);



    while(player_ready == 1) {

        if(game_over == 1) {
            delete_snake_from_memory(snake_head);
            Sleep(2000);
            clear_screen();
                SetConsoleTextAttribute(hConsole, 15);
                printf("\nGAME OVER!\n");
                SetConsoleTextAttribute(hConsole, 3);
                printf("SCORE: ");
                SetConsoleTextAttribute(hConsole, 10);
                printf("%d\n\n", score);
                SetConsoleTextAttribute(hConsole, 10);
                printf(">>CLICK \"R\" TO PLAY AGAIN\n");
                SetConsoleTextAttribute(hConsole, 15);
                printf(">>CLICK \"M\" TO RETURN TO MAIN MENU\n");
                printf(">>CLICK \"E\" TO EXIT\n");
            while(_kbhit() != 0) {
                bin = _getch();
            }
            decision = '0';
            while(decision != 'r' && decision != 'm' && decision != 'e') {
                hide_cursor();
                if(_kbhit() != 0) {
                    decision = _getch();
                }
            }
        }

        //<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//
        main_menu:

        if(decision == 'm') {
            clear_screen();
                SetConsoleTextAttribute(hConsole, 10);
                printf("\nSNAKE\n");
                SetConsoleTextAttribute(hConsole, 15);
                printf("Created");
                SetConsoleTextAttribute(hConsole, 12);
                printf(" by Ecro\n\n");
                SetConsoleTextAttribute(hConsole, 10);
                printf(">>CLICK \"P\" TO PLAY\n");
                SetConsoleTextAttribute(hConsole, 15);
                printf(">>CLICK \"O\" TO LEARN MORE ABOUT THE GAME\n");
                printf(">>CLICK \"E\" TO EXIT");
                SetConsoleTextAttribute(hConsole, 7);
            while(decision != 'p' && decision != 'l' && decision != 'o' && decision != 'e') {
                hide_cursor();
                if(_kbhit() != 0) {
                    decision = _getch();
                }
            }
        }

        //<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//

        if(decision == 'p') {
            clear_screen();
                SetConsoleTextAttribute(hConsole, 10);
                printf("\nSELECT GAME MODE:\n\n");
                SetConsoleTextAttribute(hConsole, 15);
                printf(">>");
                SetConsoleTextAttribute(hConsole, 11);
                printf("DYNAMIC ");
                SetConsoleTextAttribute(hConsole, 15);
                printf("(FASTER GAME & MORE RESPONSIVE SNAKE, recommended for advanced players)");
                printf(" [CLICK \"D\"]\n");
                SetConsoleTextAttribute(hConsole, 15);
                printf(">>");
                SetConsoleTextAttribute(hConsole, 13);
                printf("SLOW ");
                SetConsoleTextAttribute(hConsole, 15);
                printf("(SLOWER GAME & LESS RESPONSIVE SNAKE, recommended for beginners)");
                printf(" [CLICK \"S\"]");
                SetConsoleTextAttribute(hConsole, 7);
            while(decision != 'd' && decision != 's') {
                hide_cursor();
                if(_kbhit() != 0) {
                    decision = _getch();
                }
            }
            if(decision == 'd') {
                dynamic_constant = 45;
                gamemode = 'd';
            }
            else if(decision == 's') {
                dynamic_constant = 180;
                gamemode = 's';
                wall_assist = 1;
            }

            //()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()

            clear_screen();
                
                SetConsoleTextAttribute(hConsole, 10);
                printf("\nSELECT GAME MODE\n\n");
                SetConsoleTextAttribute(hConsole, 7);
                printf(">>");
                SetConsoleTextAttribute(hConsole, 13);
                printf("CLASSIC ");
                SetConsoleTextAttribute(hConsole, 15);
                printf("(ONE SNAKE TO CONTROL) ");
                printf("[CLICK \"F\"]\n");
                SetConsoleTextAttribute(hConsole, 7);
                printf(">>");
                SetConsoleTextAttribute(hConsole, 11);
                printf("CHALLENGING ");
                SetConsoleTextAttribute(hConsole, 15);
                printf("(TWO SNAKES TO CONTROL) ");
                printf("[CLICK \"G\"]\n");
                SetConsoleTextAttribute(hConsole, 7);
            while(decision != 'f' && decision != 'g') {
                hide_cursor();
                if(_kbhit() != 0) {
                    decision = _getch();
                }
            }
            if(decision == 'f') {
                number_of_snakes = 1;
            }
            else if(decision == 'g') {
                number_of_snakes = 2;
            }

            //()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()

            clear_screen();
                
                SetConsoleTextAttribute(hConsole, 10);
                printf("\nSELECT MAP TYPE:\n\n");
                SetConsoleTextAttribute(hConsole, 7);
                printf(">>");
                SetConsoleTextAttribute(hConsole, 13);
                printf("BORDERED ");
                SetConsoleTextAttribute(hConsole, 15);
                printf("[CLICK \"B\"]\n");
                SetConsoleTextAttribute(hConsole, 7);
                printf(">>");
                SetConsoleTextAttribute(hConsole, 11);
                printf("BORDERLESS ");
                SetConsoleTextAttribute(hConsole, 15);
                printf("[CLICK \"V\"]\n");
                SetConsoleTextAttribute(hConsole, 7);
            while(decision != 'b' && decision != 'v') {
                hide_cursor();
                if(_kbhit() != 0) {
                    decision = _getch();
                }
            }
            if(decision == 'b') {
                borders = 1;
            }
            else if(decision == 'v') {
                borders = 0;
            }

            //()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()

            if(borders == 1 && gamemode == 'd') {
                clear_screen();
                    
                    SetConsoleTextAttribute(hConsole, 10);
                    printf("\nDO YOU WANT TO ACTIVATE WALL ASSIST?:\n\n");
                    SetConsoleTextAttribute(hConsole, 7);
                    printf(">>");
                    SetConsoleTextAttribute(hConsole, 10);
                    printf("YES ");
                    SetConsoleTextAttribute(hConsole, 15);
                    printf("[CLICK \"Y\"]\n");
                    SetConsoleTextAttribute(hConsole, 7);
                    printf(">>");
                    SetConsoleTextAttribute(hConsole, 12);
                    printf("NO ");
                    SetConsoleTextAttribute(hConsole, 15);
                    printf("[CLICK \"N\"]\n");
                    SetConsoleTextAttribute(hConsole, 7);
                while(decision != 'y' && decision != 'n') {
                    hide_cursor();
                    if(_kbhit() != 0) {
                        decision = _getch();
                    }
                }
                if(decision == 'y') {
                    wall_assist = 1;
                }
                else if(decision == 'n') {
                    wall_assist = 0;
                }
            }

            //()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()

            clear_screen();
                SetConsoleTextAttribute(hConsole, 15);
                printf("\n>> USE");
                SetConsoleTextAttribute(hConsole, 10);
                printf(" W");
                SetConsoleTextAttribute(hConsole, 15);
                printf(",");
                SetConsoleTextAttribute(hConsole, 10);
                printf(" S");
                SetConsoleTextAttribute(hConsole, 15);
                printf(",");
                SetConsoleTextAttribute(hConsole, 10);
                printf(" A");
                SetConsoleTextAttribute(hConsole, 15);
                printf(",");
                SetConsoleTextAttribute(hConsole, 10);
                printf(" D");
                SetConsoleTextAttribute(hConsole, 15);
                printf(" TO CONTROL THE SNAKE\n");
                if(number_of_snakes == 2) {
                    SetConsoleTextAttribute(hConsole, 15);
                    printf(">> USE");
                    SetConsoleTextAttribute(hConsole, 11);
                    printf(" I");
                    SetConsoleTextAttribute(hConsole, 15);
                    printf(",");
                    SetConsoleTextAttribute(hConsole, 11);
                    printf(" K");
                    SetConsoleTextAttribute(hConsole, 15);
                    printf(",");
                    SetConsoleTextAttribute(hConsole, 11);
                    printf(" J");
                    SetConsoleTextAttribute(hConsole, 15);
                    printf(",");
                    SetConsoleTextAttribute(hConsole, 11);
                    printf(" L");
                    SetConsoleTextAttribute(hConsole, 15);
                    printf(" TO CONTROL THE VIPER\n");
                }
                printf(">> COLLECT AS MANY");
                SetConsoleTextAttribute(hConsole, 12);
                printf(" @ ");
                SetConsoleTextAttribute(hConsole, 15);
                printf("AS POSSIBLE!\n");
                SetConsoleTextAttribute(hConsole, 2);
                printf("START THE GAME [CLICK \"S\"]!\n");
            while(decision != 's' && decision != 'm') {
                    hide_cursor();
                    if(_kbhit() != 0) {
                        decision = _getch();
                    }
            }
            if(decision == 'm') {
                goto main_menu;
            }

        }

        //<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//

        if(decision == 'o') {
            clear_screen();
                SetConsoleTextAttribute(hConsole, 2);
                printf("\nTHE GAME WAS INSPIRED BY THE ORIGINAL SNAKE GAME CREATED BY TANELI ARMANTO\n");
                SetConsoleTextAttribute(hConsole, 10);
                printf("AND ENTIRELY PROGRAMMED IN C LANGUAGE (WITH ELEMENTS OF WINDOWS API)\n");
                SetConsoleTextAttribute(hConsole, 3);
                printf("BY KWAZAR374 IN 2023.\n\n");
                SetConsoleTextAttribute(hConsole, 15);
                printf(">>CLICK \"M\" TO RETURN TO MAIN MENU");
                SetConsoleTextAttribute(hConsole, 7);
            while(decision != 'm') {
                hide_cursor();
                if(_kbhit() != 0) {
                    decision = _getch();
                }
            }
            goto main_menu;
        }

        //<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//

        if(decision == 'e') {
            exit(0);
        }

        //<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//<><>//

        score = 0;
        length_of_snake = 0;
        spell1 = 0;
        spell2 = 0;
        spell3 = 0;
        spell4 = 0;
        spell5 = 0;
        spell6 = 0;
        viper_spawned = 0;
        raspberry_value = 1;
        raspberry_eaten = 1;
        second_raspberry_eaten = 1;
        third_raspberry_eaten = 1;
        dragon_fruit_eaten = 1;
        dynamic_coefficient  = dynamic_constant;
        snake_direction = RIGHT;
        viper_direction = LEFT;
        snake_head = create_snake(1, RIGHT);
        extend_snake(snake_head, NULL);
        extend_snake(snake_head, NULL);
        clear_screen();
        clear_board(board);
        for(int i = 0; i < 7; i++) {
            active_spells[i] = 0;
        }

        if(number_of_snakes == 2) {
            viper_head = create_snake(WIDTH_OF_BOARD - 3, V_LEFT);
            extend_snake(viper_head, NULL);
            extend_snake(viper_head, NULL); 
            viper_spawned = 1;
        }
         
        while(_kbhit() != 0) {
            bin = _getch();
        }



        while(1) {

            border_crossed = 0;
            v_border_crossed = 0;
            flag = 0;
            v_flag = 0;
            
            if(viper_spawned == 1) {
                set_viper_position(viper_head, board);
            }
            set_snake_position(snake_head, board);

            spawn_raspberry(board, &raspberry_eaten, &raspberry_position);
            spawn_raspberry(board, &second_raspberry_eaten, &second_raspberry_position);
            spawn_raspberry(board, &third_raspberry_eaten, &third_raspberry_position);
            spawn_dragon_fruit(board, &dragon_fruit_eaten, &dragon_fruit_position, active_spells);
            set_cursor_position(0, 0);

                if(raspberry_eaten == 0) {
                    board[raspberry_position] = '@';
                }

                if(second_raspberry_eaten == 0) {
                    board[second_raspberry_position] = '@';
                }

                if(third_raspberry_eaten == 0) {
                    board[third_raspberry_position] = '@';
                }

                if(dragon_fruit_eaten == 0) {
                    board[dragon_fruit_position] = '?';
                }

            display_board(board, raspberry_value, active_spells, spell1, spell2, spell5, spell6, score);
            clear_board(board);




                choose_direction:

                if(dt_start != 0) {
                    dt_end = clock();
                    delta_time = dt_end - dt_start;
                }
                else {
                    delta_time = 0;
                }
                
                //snake & viper
                if(viper_spawned == 1) {
                    set_snake_direction(&snake_direction, &viper_direction, dynamic_coefficient, delta_time, active_spells, viper_spawned);
                }
                else {
                    set_snake_direction(&snake_direction, NULL, dynamic_coefficient, delta_time, active_spells, viper_spawned);
                }
                dt_start = clock();

                //status 1 -> effect ready to apply for snake
                //status 2 -> effect applied by (snake) player
                //status 3 -> effect active
                //status 4 -> effect ready to apply for viper
                //status 5 -> effect active (usually for viper)


                //slowdown of time [0]
                if(active_spells[0] == 2) {
                    dynamic_coefficient = dynamic_coefficient * 10;
                    active_spells[0] = 3;
                    spell1 = 10;
                }

                if(spell1 > 0) {
                    if(spell1 <= 1)  {
                        active_spells[0] = 0;
                        dynamic_coefficient = dynamic_coefficient / 10;
                    }
                    dt_start = 0;
                    spell1--;
                }

                //snake - change of colour after eating a dragon fruit [5]
                if(active_spells[5] == 1) {
                    active_spells[5] = 3;
                    spell6 = 30; //remember about if statement in display function
                }

                //viper - change of colour after eating a dragon fruit [5]
                if(active_spells[5] == 4) {
                    active_spells[5] = 5;
                    spell6 = 30; //remember about if statement in display function
                }

                if(spell6 > 0) {
                    if(spell6 <= 1) {
                        active_spells[5] = 0;
                    }

                    spell6--;
                }

                //slowdown of time and choice of direction of snake after respawn of phoenix [2]
                if(spell3 > 0) {
                    if(spell3 <= 1) {
                        if(viper_spawned == 1) {
                            active_spells[2] = spell2_prev_val;
                        } 
                        else {
                            active_spells[2] = 0;
                        }
                        dynamic_coefficient = dynamic_coefficient / 2;
                    }
                    
                    snake_direction = RIGHT;
                    if(viper_spawned == 1) viper_direction = LEFT;
                    dt_start = 0;
                    spell3--;
                }



                //adding of third dimension [1]
                if(active_spells[1] == 2) {
                    active_spells[1] = 3;
                    spell2 = 40;
                }

                if(spell2 > 0) {
                    if(spell2 <= 1)  {
                        active_spells[1] = 0;
                    }
                    spell2--;
                }


                //inversion of keys (snake) [4]
                if(active_spells[4] == 1) {
                    active_spells[4] = 3;
                    spell5 = 40;
                }

                //inversion of keys (viper) [4]
                if(active_spells[4] == 4) {
                    active_spells[4] = 5;
                    spell5 = 40;
                }

                if(spell5 > 0) {
                    if(spell5 <= 1)  {
                        active_spells[4] = 0;
                    }
                    spell5--;
                }



                //invisible snake [3]
                if(active_spells[3] == 1) {
                    active_spells[3] = 3;
                    spell4 = 40;
                }

                //invisible viper [3]
                if(active_spells[3] == 4) {
                    active_spells[3] = 5;
                    spell4 = 40;
                }

                if(spell4 > 0) {
                    if(spell4 <= 1) {
                        active_spells[3] = 0;
                    }
                    spell4--;
                }


                //snake
                if(is_wall_touched(snake_head, board, snake_direction) == 1) {
                    if(borders == 1) {
                        if(wall_assist == 1) {
                            if(flag < 2) {
                                flag++;

                                if(gamemode == 's') {
                                    Sleep(10);
                                } 
                                else if(gamemode == 'd') {
                                    Sleep(5);
                                }

                                goto choose_direction;
                            }
                        }
                        break;
                    }
                    else if(borders == 0) {
                        border_crossed = 1;
                    }
                }
                flag = 0;

                //viper
                if(viper_spawned == 1) {
                    if(is_wall_touched(viper_head, board, viper_direction) == 1) {
                        if(borders == 1) {
                            if(wall_assist == 1) {
                                if(v_flag < 2) {
                                    v_flag++;

                                    if(gamemode == 's') {
                                        Sleep(10);
                                    } 
                                    else if(gamemode == 'd') {
                                        Sleep(5);
                                    }

                                    goto choose_direction;
                                }
                            }
                            break;
                        }
                        else if(borders == 0) {
                            v_border_crossed = 1;
                        }
                    }
                    v_flag = 0;
                }


                //snake
                if(is_snake_twisted(snake_head, snake_direction, border_crossed) == 1 && active_spells[1] != 3) {
                    if(active_spells[3] == 3) {

                        active_spells[3] = 1;

                        set_snake_position(snake_head, board);
                        set_cursor_position(0, 0);

                            if(raspberry_eaten == 0) {
                                board[raspberry_position] = '@';
                            }

                            if(second_raspberry_eaten == 0) {
                                board[second_raspberry_position] = '@';
                            }

                            if(third_raspberry_eaten == 0) {
                                board[third_raspberry_position] = '@';
                            }

                            if(dragon_fruit_eaten == 0) {
                                board[dragon_fruit_position] = '?';
                            }

                        display_board(board, raspberry_value, active_spells, spell1, spell2, spell5, spell6, score);
                    }
                    break;
                }

                //viper
                if(viper_spawned == 1) {
                    if(is_snake_twisted(viper_head, viper_direction, v_border_crossed) == 1 && active_spells[1] != 3) {
                        break;
                    }
                }


                //snake and viper collision
                if(viper_spawned == 1 && active_spells[1] != 3) {
                    if(collision_check(snake_head, viper_head, snake_direction, viper_direction, border_crossed, v_border_crossed) == 1) {
                        break;
                    }
                }


                //snake
                is_raspberry_eaten(snake_head, board, &raspberry_eaten, snake_direction, raspberry_position, &score, &border_crossed, &length_of_snake, &raspberry_value);
                is_raspberry_eaten(snake_head, board, &second_raspberry_eaten, snake_direction, second_raspberry_position, &score, &border_crossed, &length_of_snake, &raspberry_value);
                is_raspberry_eaten(snake_head, board, &third_raspberry_eaten, snake_direction, third_raspberry_position, &score, &border_crossed, &length_of_snake, &raspberry_value);

                //viper
                if(viper_spawned == 1) {
                    is_raspberry_eaten(viper_head, board, &raspberry_eaten, viper_direction, raspberry_position, &score, &v_border_crossed, NULL, &raspberry_value);
                    is_raspberry_eaten(viper_head, board, &second_raspberry_eaten, viper_direction, second_raspberry_position, &score, &v_border_crossed, NULL, &raspberry_value);
                    is_raspberry_eaten(viper_head, board, &third_raspberry_eaten, viper_direction, third_raspberry_position, &score, &v_border_crossed, NULL, &raspberry_value);
                }

                //snake
                if(is_dragon_fruit_eaten(snake_head, board, &dragon_fruit_eaten, snake_direction, dragon_fruit_position, &border_crossed) == 1) {
                    cast_spell(active_spells);
                }

                //viper
                if(viper_spawned == 1) {
                    if(is_dragon_fruit_eaten(viper_head, board, &dragon_fruit_eaten, viper_direction, dragon_fruit_position, &v_border_crossed) == 1) {
                        cast_spell(active_spells);
                        if(active_spells[3] == 1) {
                            active_spells[3] = 4;
                        }
                        if(active_spells[4] == 1) {
                            active_spells[4] = 4;
                        }
                        if(active_spells[5] == 1) {
                            active_spells[5] = 4;
                        }
                    }
                }

                //active_spells[6] raspberry value enhancement
                if(active_spells[6] == 1) {
                    raspberry_value++;
                    active_spells[6] = 0;
                }

                //snake
                if(active_spells[2] == 2) {
                    change_snake_position_during_respawn_of_phoenix(snake_head, 2);
                    board[0] = '#';

                    if(viper_spawned == 0) {
                        active_spells[2] = 3;
                        dynamic_coefficient = dynamic_coefficient * 2;
                        spell3 = 5;
                    }
                }
                else {
                    if(border_crossed == 1) {
                        change_snake_position_during_crossing_border(snake_head, snake_direction);
                    }
                    else if(border_crossed == 0) {
                        change_snake_position(snake_head, snake_direction);
                    }
                }

                //viper
                if(viper_spawned == 1) {
                    if(active_spells[2] == 2) {
                        change_snake_position_during_respawn_of_phoenix(viper_head, WIDTH_OF_BOARD - 3);
                        board[0] = '#';

                        active_spells[2] = 3;
                        dynamic_coefficient = dynamic_coefficient * 2;
                        spell3 = 5;
                    }
                    else {
                        if(v_border_crossed == 1) {
                            change_snake_position_during_crossing_border(viper_head, viper_direction);
                        }
                        else if(v_border_crossed == 0) {
                            change_snake_position(viper_head, viper_direction);
                        }
                    }
                }

            hide_cursor();
            
        }
        game_over = 1;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fontsize(int x, int y) {        
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);        
    CONSOLE_FONT_INFOEX font; font.cbSize = sizeof(font);   
    GetCurrentConsoleFontEx(out, 0, &font);   
    font.dwFontSize.X = x;   
    font.dwFontSize.Y = y;   
    SetCurrentConsoleFontEx(out, 0, &font);   
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_cursor_position(int x, int y) {
   COORD coord;
   coord.X = x;
   coord.Y = y;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clear_screen(void) {
    int i;
    set_cursor_position(0, 0);
    for(i = 0; i < 4*SIZE_OF_BOARD; i++) {
        if(i % (2*WIDTH_OF_BOARD) == 0) {
            printf("\n ");
        }
        else {
            printf(" ");
        }
    }
    set_cursor_position(0, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void delete_snake_from_memory(snake *snake_head) {
    snake *temporary = snake_head;
    snake *buffer;
    while(temporary != NULL) {
        buffer = temporary->next;
        free(temporary);
        temporary = buffer;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void hide_cursor(void) {
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clear_board(char *board) {
    int i;
    for(i = 0; i <= SIZE_OF_BOARD; i++) {
        if(i < WIDTH_OF_BOARD) {
            board[i] = '#';
        }
        else if(i >= (SIZE_OF_BOARD - WIDTH_OF_BOARD)) {
            board[i] = '#';
        }
        else if(i % WIDTH_OF_BOARD == 0) {
            board[i] = '#';
        }
        else if(i % WIDTH_OF_BOARD == (WIDTH_OF_BOARD-1)) {
            board[i] = '#';
        } 
        else {
            board[i] = ' ';
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void display_board(char *board, int raspberry_value, int *active_spells, int spell1, int spell2, int spell5, int spell6, int score) {
    int i;
    int random_number;
    static int j = 1;
    static int k = 1;
    static int l = 1;
    static int m = 1;
    static int z = 1;
    int jcolour;
    int kcolour;
    int lcolour;
    int mcolour;
    int zcolour;
    static int ztext;
    static int flag = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for(i = 0; i < SIZE_OF_BOARD; i++) {
        if(i % (WIDTH_OF_BOARD) == 0) {
            SetConsoleTextAttribute(hConsole, 5);
            printf("\n%c", board[i]);
            SetConsoleTextAttribute(hConsole, 7);
        }
        else {
            switch(board[i]) {
                case 'X': 
                    SetConsoleTextAttribute(hConsole, 10);
                break;
                case 'O':
                    if(active_spells[5] == 3 && (rand() % 3) == 0) {
                        random_number = (rand() % 6) + 9;
                        SetConsoleTextAttribute(hConsole, random_number);
                    }
                    else {
                        SetConsoleTextAttribute(hConsole, 2);
                    }
                break;
                case '@':
                    SetConsoleTextAttribute(hConsole, 12);
                break;
                case '#':
                    SetConsoleTextAttribute(hConsole, 5);
                break;
                case 'Q':
                    SetConsoleTextAttribute(hConsole, 11);
                break;
                case 'G':
                    if(active_spells[5] == 5 && (rand() % 3) == 0) {
                        random_number = (rand() % 6) + 9;
                        SetConsoleTextAttribute(hConsole, random_number);
                    }
                    else {
                        SetConsoleTextAttribute(hConsole, 3);
                    }
                break;
                case '?':
                    if(j < 3) {
                        jcolour = 10;
                        j++;
                    }
                    else if(j >= 3 && j < 6) {
                        jcolour = 11;
                        j++;
                    }
                    else if(j >= 6 && j < 8) {
                        jcolour = 14;
                        j++;
                    }
                    else if(j == 8) {
                        jcolour = 14;
                        j = 1;
                    }
                    SetConsoleTextAttribute(hConsole, jcolour);
                break;
            }
            if(board[i] == 'O' && active_spells[3] == 3) {
               SetConsoleTextAttribute(hConsole, 0); 
            }
            if(board[i] == 'G' && active_spells[3] == 5) {
               SetConsoleTextAttribute(hConsole, 0); 
            }
            printf("%c", board[i]);
            SetConsoleTextAttribute(hConsole, 7);
        }
    }
    printf("\n");


    SetConsoleTextAttribute(hConsole, 15);
    printf("@ x%d\t\t\t\t\t", raspberry_value);


    if(active_spells[0] == 1) {
        if(k < 5) {
            kcolour = 10;
            k++;
        }
        else if(k >= 5 && k < 10) {
            kcolour = 11;
            k++;
        }
        else if(k >= 10 && k < 14) {
            kcolour = 14;
            k++;
        }
        else if(k == 14) {
            kcolour = 14;
            k = 1;
        }
        SetConsoleTextAttribute(hConsole, kcolour);
    }
    else {
        kcolour = 8;
        SetConsoleTextAttribute(hConsole, 8);
    }
    printf("<<  ");



    if(active_spells[1] == 1) {
        if(m < 5) {
            mcolour = 10;
            m++;
        }
        else if(m >= 5 && m < 10) {
            mcolour = 11;
            m++;
        }
        else if(m >= 10 && m < 14) {
            mcolour = 14;
            m++;
        }
        else if(m == 14) {
            mcolour = 14;
            m = 1;
        }
        SetConsoleTextAttribute(hConsole, mcolour);
    }
    else {
        mcolour = 8;
        SetConsoleTextAttribute(hConsole, 8);
    }
    printf("^_  ");



    if(active_spells[2] == 1) {
        if(l < 5) {
            lcolour = 10;
            l++;
        }
        else if(l >= 5 && l < 10) {
            lcolour = 11;
            l++;
        }
        else if(l >= 10 && l < 14) {
            lcolour = 14;
            l++;
        }
        else if(l == 14) {
            lcolour = 14;
            l = 1;
        }
        SetConsoleTextAttribute(hConsole, lcolour);
    }
    else {
        lcolour = 8;
        SetConsoleTextAttribute(hConsole, 8);
    }
    printf("<>  \n");


    SetConsoleTextAttribute(hConsole, 15);
    printf("%d", score);



    if(active_spells[0] == 3) {
        if(spell1 > 5) {
            SetConsoleTextAttribute(hConsole, 10);
            printf("\t\t\t\t\t%2d  ", spell1-1);
        }
        else {
            SetConsoleTextAttribute(hConsole, 12);
            printf("\t\t\t\t\t%2d  ", spell1-1);
        }
    }
    else {
        SetConsoleTextAttribute(hConsole, kcolour);
        printf("\t\t\t\t\t>c  ");
    }


    if(active_spells[1] == 3) {
        if(spell2 > 5) {
            SetConsoleTextAttribute(hConsole, 10);
            printf("%2d  ", spell2-1);
        }
        else {
            SetConsoleTextAttribute(hConsole, 12);
            printf("%2d  ", spell2-1);
        }
    }
    else {
        SetConsoleTextAttribute(hConsole, mcolour);
        printf(">f  ");
    }


    SetConsoleTextAttribute(hConsole, lcolour);
    printf(">r\n");



    





    if(active_spells[0] != 3 && active_spells[1] != 3 && active_spells[2] != 3 &&
        active_spells[3] != 3 && active_spells[3] != 5 && active_spells[4] != 3 &&
        active_spells[4] != 5 && active_spells[5] != 3 && active_spells[5] != 5) {
        if(flag == 0) {
            printf("                                                    ");
            flag = 1;
        }
    }
    
    else if(active_spells[3] == 3) {
        SetConsoleTextAttribute(hConsole, 12);
        printf("SNAKE HAS BECOME INVISIBLE                \t  ");
        if(flag != 0) flag = 0;
    }
    else if(active_spells[3] == 5) {
        SetConsoleTextAttribute(hConsole, 12);
        printf("VIPER HAS BECOME INVISIBLE                \t  ");
        if(flag != 0) flag = 0;
    }
    else if(active_spells[4] == 3) {
        SetConsoleTextAttribute(hConsole, 12);
        printf("SNAKE'S CONTROLS HAS BEEN REVERSED        ");
        printf("\t%2d", spell5-1);
        if(flag != 0) flag = 0;
    }
    else if(active_spells[4] == 5) {
        SetConsoleTextAttribute(hConsole, 12);
        printf("VIPER'S CONTROLS HAS BEEN REVERSED        ");
        printf("\t%2d", spell5-1);
        if(flag != 0) flag = 0;
    }
    else if(active_spells[5] == 3 || active_spells[5] == 5) {
        if(spell6 == 29) ztext = rand() % 3;
        if(z < 5) {
            zcolour = 10;
            z++;
        }
        else if(z >= 5 && z < 10) {
            zcolour = 11;
            z++;
        }
        else if(z >= 10 && z < 14) {
            zcolour = 14;
            z++;
        }
        else if(z == 14) {
            zcolour = 14;
            z = 1;
        }
        SetConsoleTextAttribute(hConsole, zcolour);
        if(ztext == 0) {
            printf("SHINY!!!                               \t  ");
        }
        else if(ztext == 1) {
            if(active_spells[5] == 3) {
                printf("GREEN SCALY SNAKE DANCING ON RAIBOW\t  ");
            }
            else if(active_spells[5] == 5) {
                printf("BLUE SILKY VIPER DANCING ON RAINBOW\t  ");
            }
        }
        else if(ztext == 2) {
            printf("IS THAT POISONOUS?                     \t  ");
        }
        SetConsoleTextAttribute(hConsole, 15);
        if(flag != 0) flag = 0;
    }
    else if(active_spells[0] == 3) {
        SetConsoleTextAttribute(hConsole, 10);
        printf("TIME HAS BEEN SLOWED DOWN                 \t  ");
        if(flag != 0) flag = 0;
    }
    else if(active_spells[1] == 3) {
        SetConsoleTextAttribute(hConsole, 10);
        printf("THIRD DIMENSION HAS BEEN ADDED            \t  ");
        if(flag != 0) flag = 0;
    }
    else if(active_spells[2] == 3) {
        SetConsoleTextAttribute(hConsole, 10);
        printf("RESPAWN OF PHOENIX!!!                     \t  ");
        if(flag != 0) flag = 0;
    }










}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

snake *create_snake(int x_coordinate, char direction) {
    snake *result;
    result = (snake *)malloc(sizeof(snake));
    result->next = NULL;
    result->x_coordinate = x_coordinate;
    result->y_coordinate = (HEIGHT_OF_BOARD / 2);
    result->direction = direction;

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void spawn_raspberry(char *board, int *raspberry_eaten, int *raspberry_position) {
    if(*raspberry_eaten == 1) {
        *raspberry_position = 0;
        while(board[*raspberry_position] != ' ') {
            *raspberry_position = rand() % SIZE_OF_BOARD;
        }
        board[*raspberry_position] = '@';
        *raspberry_eaten = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void spawn_dragon_fruit(char *board, int *dragon_fruit_eaten, int *dragon_fruit_position, int *active_spells) {

    int i = 0;
    int position_correct = 0;
    int fruit_x_cord;
    int fruit_y_cord;
    int temp;
    int is_any_spell_accessible = 0;

    for(int i = 0; i < 7; i++) {
        if(active_spells[i] == 3 || active_spells[i] == 5) {
            return;
        }
        if(active_spells[i] == 0) {
            is_any_spell_accessible++;
        }
    }
    if(active_spells[4] == 1 || active_spells[4] == 4) {
        return;
    }

    if(is_any_spell_accessible == 0) {
        return;
    }

    

    if(*dragon_fruit_eaten == 1 && (rand() % 30) == 0) {
        while(position_correct == 0 || i < 100000) {
            i++;
            *dragon_fruit_position = 0;
            while(board[*dragon_fruit_position] != ' ') {
                *dragon_fruit_position = rand() % SIZE_OF_BOARD;
                fruit_x_cord = *dragon_fruit_position % WIDTH_OF_BOARD;
                fruit_y_cord = (*dragon_fruit_position - fruit_x_cord) / WIDTH_OF_BOARD;
            }

            temp = (WIDTH_OF_BOARD * fruit_y_cord + fruit_x_cord - 1); 
            if(temp >= 0) {
                if(board[temp] == 'X' || board[temp] == 'Q') {
                    continue;
                }
            }

            temp = (WIDTH_OF_BOARD * fruit_y_cord + fruit_x_cord - 2); 
            if(temp >= 0) {
                if(board[temp] == 'X' || board[temp] == 'Q') {
                    continue;
                }
            }

            temp = (WIDTH_OF_BOARD * fruit_y_cord + fruit_x_cord - 3); 
            if(temp >= 0) {
                if(board[temp] == 'X' || board[temp] == 'Q') {
                    continue;
                }
            }

            temp = (WIDTH_OF_BOARD * fruit_y_cord + fruit_x_cord - 4); 
            if(temp >= 0) {
                if(board[temp] == 'X' || board[temp] == 'Q') {
                    continue;
                }
            }

            temp = (WIDTH_OF_BOARD * fruit_y_cord + fruit_x_cord + 1); 
            if(temp >= 0) {
                if(board[temp] == 'X' || board[temp] == 'Q') {
                    continue;
                }
            }

            temp = (WIDTH_OF_BOARD * fruit_y_cord + fruit_x_cord + 2); 
            if(temp >= 0) {
                if(board[temp] == 'X' || board[temp] == 'Q') {
                    continue;
                }
            }

            temp = (WIDTH_OF_BOARD * fruit_y_cord + fruit_x_cord + 3); 
            if(temp >= 0) {
                if(board[temp] == 'X' || board[temp] == 'Q') {
                    continue;
                }
            }

            temp = (WIDTH_OF_BOARD * fruit_y_cord + fruit_x_cord + 4); 
            if(temp >= 0) {
                if(board[temp] == 'X' || board[temp] == 'Q') {
                    continue;
                }
            }


            temp = (WIDTH_OF_BOARD * (fruit_y_cord - 1) + fruit_x_cord); 
            if(temp >= 0) {
                if(board[temp] == 'X' || board[temp] == 'Q') {
                    continue;
                }
            }

            temp = (WIDTH_OF_BOARD * (fruit_y_cord - 2) + fruit_x_cord); 
            if(temp >= 0) {
                if(board[temp] == 'X' || board[temp] == 'Q') {
                    continue;
                }
            }

            temp = (WIDTH_OF_BOARD * (fruit_y_cord - 3) + fruit_x_cord); 
            if(temp >= 0) {
                if(board[temp] == 'X' || board[temp] == 'Q') {
                    continue;
                }
            }

            temp = (WIDTH_OF_BOARD * (fruit_y_cord - 4) + fruit_x_cord); 
            if(temp >= 0) {
                if(board[temp] == 'X' || board[temp] == 'Q') {
                    continue;
                }
            }

            temp = (WIDTH_OF_BOARD * (fruit_y_cord + 1) + fruit_x_cord); 
            if(temp >= 0) {
                if(board[temp] == 'X' || board[temp] == 'Q') {
                    continue;
                }
            }

            temp = (WIDTH_OF_BOARD * (fruit_y_cord + 2) + fruit_x_cord); 
            if(temp >= 0) {
                if(board[temp] == 'X' || board[temp] == 'Q') {
                    continue;
                }
            }

            temp = (WIDTH_OF_BOARD * (fruit_y_cord + 3) + fruit_x_cord); 
            if(temp >= 0) {
                if(board[temp] == 'X' || board[temp] == 'Q') {
                    continue;
                }
            }

            temp = (WIDTH_OF_BOARD * (fruit_y_cord + 4) + fruit_x_cord); 
            if(temp >= 0) {
                if(board[temp] == 'X' || board[temp] == 'Q') {
                    continue;
                }
            }

            position_correct = 1;
        }
        board[*dragon_fruit_position] = '?';
        *dragon_fruit_eaten = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_snake_direction(char *snake_direction, char *viper_direction, int dynamic_coefficient, double delta_time, int *active_spells, int is_viper_spawned) {
    static clock_t dt_start = 0, dt_end = 1;
    char snake_previous_direction = *snake_direction;
    char viper_previous_direction;
    char direction = '\0';
    char decision;
    clock_t pause_start, pause_end;
    static double pause_time;
    if(is_viper_spawned == 1) viper_previous_direction = *viper_direction;
    double smooth_coefficient = dynamic_coefficient;
    double in_fun_delta_time = dt_end - dt_start - pause_time;
    pause_time = 0;
    if(delta_time != 0) {
        smooth_coefficient = (1.0/(delta_time*1.5 + in_fun_delta_time)) * dynamic_coefficient * 100;
    }
    dt_start = clock();
    *snake_direction = '\0';
    if(is_viper_spawned == 1) *viper_direction = '\0';
    clock_t start, end;
    start = clock();
    end = clock();
    if(is_viper_spawned != 1) {
        if(snake_previous_direction == UP || snake_previous_direction == DOWN) {
            while((double)(end - start) < 2 * smooth_coefficient && *snake_direction != 'w' && *snake_direction != 's' && *snake_direction != 'a' && *snake_direction != 'd') {
                if(_kbhit() != 0) {
                    *snake_direction = _getch();
                }
                if(*snake_direction == UP && snake_previous_direction == DOWN) *snake_direction = '\0';
                if(*snake_direction == DOWN && snake_previous_direction == UP) *snake_direction = '\0';

                if(*snake_direction == 'c' && active_spells[0] == 1) {
                    active_spells[0] = 2;
                }

                if(*snake_direction == 'f' && active_spells[1] == 1) {
                    active_spells[1] = 2;
                }

                if(*snake_direction == 'r' && active_spells[2] == 1) {
                    active_spells[2] = 2;
                }

                if(*snake_direction == 'p') {
                    decision = '\0';
                    pause_start = clock();
                    while(decision != 'p') {
                        hide_cursor();
                        if(_kbhit() != 0) {
                            decision = _getch();
                        }
                    }
                    pause_end = clock();
                    pause_time = (double)(pause_end - pause_start);
                }

                end = clock();
            }
        }
        else {
            while((double)(end - start) < smooth_coefficient  && *snake_direction != 'w' && *snake_direction != 's' && *snake_direction != 'a' && *snake_direction != 'd') {
                if(_kbhit() != 0) {
                    *snake_direction = _getch();
                }
                if(*snake_direction == LEFT && snake_previous_direction == RIGHT) *snake_direction = '\0';
                if(*snake_direction == RIGHT && snake_previous_direction == LEFT) *snake_direction = '\0';

                if(*snake_direction == 'c' && active_spells[0] == 1) {
                    active_spells[0] = 2;
                }

                if(*snake_direction == 'f' && active_spells[1] == 1) {
                    active_spells[1] = 2;
                }

                if(*snake_direction == 'r' && active_spells[2] == 1) {
                    active_spells[2] = 2;
                }


                if(*snake_direction == 'p') {
                    decision = '\0';
                    pause_start = clock();
                    while(decision != 'p') {
                        hide_cursor();
                        if(_kbhit() != 0) {
                            decision = _getch();
                        }
                    }
                    pause_end = clock();
                    pause_time = (double)(pause_end - pause_start);
                }

                end = clock();
            }
        }

        if(!(*snake_direction == 'w' || *snake_direction == 's' || *snake_direction == 'a' || *snake_direction == 'd')) {
            *snake_direction = snake_previous_direction;
        }
        else if(active_spells[4] == 3) {
            switch(*snake_direction) {
                case 'w':
                    if(snake_previous_direction != 'w') {
                        *snake_direction = 's';
                    }
                break;
                case 's':
                    if(snake_previous_direction != 's') {
                        *snake_direction = 'w';
                    }
                break;
                case 'd':
                    if(snake_previous_direction != 'd') {
                        *snake_direction = 'a';
                    }
                break;
                case 'a':
                    if(snake_previous_direction != 'a') {
                        *snake_direction = 'd';
                    }
                break;
            }
        }

    }




    if(is_viper_spawned == 1) {

        if((viper_previous_direction == UP || viper_previous_direction == DOWN) && (snake_previous_direction == UP || snake_previous_direction == DOWN)) {
            while((double)(end - start) < 1 * smooth_coefficient && !((*viper_direction == 'i' || *viper_direction == 'k' || *viper_direction == 'j' || *viper_direction == 'l')
                                                                    && (*snake_direction == 'w' || *snake_direction == 's' || *snake_direction == 'a' || *snake_direction == 'd'))) {
                if(_kbhit() != 0) {
                    direction = _getch();
                }

                if(direction == 'i' || direction == 'j' || direction == 'k' || direction == 'l') {
                    *viper_direction = direction;
                }
                else if(direction == 'w' || direction == 's' || direction == 'a' || direction == 'd') {
                    *snake_direction = direction;
                }

                if(*viper_direction == V_UP && viper_previous_direction == DOWN) *viper_direction = '\0';
                if(*viper_direction == V_DOWN && viper_previous_direction == UP) *viper_direction = '\0';

                if(*snake_direction == UP && snake_previous_direction == DOWN) *snake_direction = '\0';
                if(*snake_direction == DOWN && snake_previous_direction == UP) *snake_direction = '\0';

                if(direction == 'c' && active_spells[0] == 1) {
                    active_spells[0] = 2;
                }

                if(direction == 'f' && active_spells[1] == 1) {
                    active_spells[1] = 2;
                }

                if(direction == 'r' && active_spells[2] == 1) {
                    active_spells[2] = 2;
                }

                if(*snake_direction == 'p') {
                    decision = '\0';
                    pause_start = clock();
                    while(decision != 'p') {
                        hide_cursor();
                        if(_kbhit() != 0) {
                            decision = _getch();
                        }
                    }
                    pause_end = clock();
                    pause_time = (double)(pause_end - pause_start);
                }

                end = clock();
            }
        } else if((viper_previous_direction == LEFT || viper_previous_direction == RIGHT) && (snake_previous_direction == LEFT || snake_previous_direction == RIGHT)) {
            while((double)(end - start) < 1 * smooth_coefficient && !((*viper_direction == 'i' || *viper_direction == 'k' || *viper_direction == 'j' || *viper_direction == 'l')
                                                                    && (*snake_direction == 'w' || *snake_direction == 's' || *snake_direction == 'a' || *snake_direction == 'd'))) {
                if(_kbhit() != 0) {
                    direction = _getch();
                }

                if(direction == 'i' || direction == 'j' || direction == 'k' || direction == 'l') {
                    *viper_direction = direction;
                }
                else if(direction == 'w' || direction == 's' || direction == 'a' || direction == 'd') {
                    *snake_direction = direction;
                }

                if(*viper_direction == V_LEFT && viper_previous_direction == RIGHT) *viper_direction = '\0';
                if(*viper_direction == V_RIGHT && viper_previous_direction == LEFT) *viper_direction = '\0';

                if(*snake_direction == LEFT && snake_previous_direction == RIGHT) *snake_direction = '\0';
                if(*snake_direction == RIGHT && snake_previous_direction == LEFT) *snake_direction = '\0';

                if(direction == 'c' && active_spells[0] == 1) {
                    active_spells[0] = 2;
                }

                if(direction == 'f' && active_spells[1] == 1) {
                    active_spells[1] = 2;
                }

                if(direction == 'r' && active_spells[2] == 1) {
                    active_spells[2] = 2;
                }

                if(*snake_direction == 'p') {
                    decision = '\0';
                    pause_start = clock();
                    while(decision != 'p') {
                        hide_cursor();
                        if(_kbhit() != 0) {
                            decision = _getch();
                        }
                    }
                    pause_end = clock();
                    pause_time = (double)(pause_end - pause_start);
                }

                end = clock();
            }
        }
        else if((viper_previous_direction == LEFT || viper_previous_direction == RIGHT) && (snake_previous_direction == UP || snake_previous_direction == DOWN)) {
            while((double)(end - start) < 1 * smooth_coefficient && !((*viper_direction == 'i' || *viper_direction == 'k' || *viper_direction == 'j' || *viper_direction == 'l')
                                                                    && (*snake_direction == 'w' || *snake_direction == 's' || *snake_direction == 'a' || *snake_direction == 'd'))) {
                if(_kbhit() != 0) {
                    direction = _getch();
                }

                if(direction == 'i' || direction == 'j' || direction == 'k' || direction == 'l') {
                    *viper_direction = direction;
                }
                else if(direction == 'w' || direction == 's' || direction == 'a' || direction == 'd') {
                    *snake_direction = direction;
                }

                if(*viper_direction == V_LEFT && viper_previous_direction == RIGHT) *viper_direction = '\0';
                if(*viper_direction == V_RIGHT && viper_previous_direction == LEFT) *viper_direction = '\0';

                if(*snake_direction == UP && snake_previous_direction == DOWN) *snake_direction = '\0';
                if(*snake_direction == DOWN && snake_previous_direction == UP) *snake_direction = '\0';

                if(direction == 'c' && active_spells[0] == 1) {
                    active_spells[0] = 2;
                }

                if(direction == 'f' && active_spells[1] == 1) {
                    active_spells[1] = 2;
                }

                if(direction == 'r' && active_spells[2] == 1) {
                    active_spells[2] = 2;
                }

                if(*snake_direction == 'p') {
                    decision = '\0';
                    pause_start = clock();
                    while(decision != 'p') {
                        hide_cursor();
                        if(_kbhit() != 0) {
                            decision = _getch();
                        }
                    }
                    pause_end = clock();
                    pause_time = (double)(pause_end - pause_start);
                }

                end = clock();
            }
        }
        else if((viper_previous_direction == UP || viper_previous_direction == DOWN) && (snake_previous_direction == LEFT || snake_previous_direction == RIGHT)) {
            while((double)(end - start) < 1 * smooth_coefficient && !((*viper_direction == 'i' || *viper_direction == 'k' || *viper_direction == 'j' || *viper_direction == 'l')
                                                                    && (*snake_direction == 'w' || *snake_direction == 's' || *snake_direction == 'a' || *snake_direction == 'd'))) {
                if(_kbhit() != 0) {
                    direction = _getch();
                }

                if(direction == 'i' || direction == 'j' || direction == 'k' || direction == 'l') {
                    *viper_direction = direction;
                }
                else if(direction == 'w' || direction == 's' || direction == 'a' || direction == 'd') {
                    *snake_direction = direction;
                }

                if(*viper_direction == V_UP && viper_previous_direction == DOWN) *viper_direction = '\0';
                if(*viper_direction == V_DOWN && viper_previous_direction == UP) *viper_direction = '\0';

                if(*snake_direction == LEFT && snake_previous_direction == RIGHT) *snake_direction = '\0';
                if(*snake_direction == RIGHT && snake_previous_direction == LEFT) *snake_direction = '\0';

                if(direction == 'c' && active_spells[0] == 1) {
                    active_spells[0] = 2;
                }

                if(direction == 'f' && active_spells[1] == 1) {
                    active_spells[1] = 2;
                }

                if(direction == 'r' && active_spells[2] == 1) {
                    active_spells[2] = 2;
                }

                if(*snake_direction == 'p') {
                    decision = '\0';
                    pause_start = clock();
                    while(decision != 'p') {
                        hide_cursor();
                        if(_kbhit() != 0) {
                            decision = _getch();
                        }
                    }
                    pause_end = clock();
                    pause_time = (double)(pause_end - pause_start);
                }

                end = clock();
            }
        }


        if(!(*snake_direction == 'w' || *snake_direction == 's' || *snake_direction == 'a' || *snake_direction == 'd')) {
            *snake_direction = snake_previous_direction;
        }
        else if(active_spells[4] == 3) {
            switch(*snake_direction) {
                case 'w':
                    if(snake_previous_direction != 'w') {
                        *snake_direction = 's';
                    }
                break;
                case 's':
                    if(snake_previous_direction != 's') {
                        *snake_direction = 'w';
                    }
                break;
                case 'd':
                    if(snake_previous_direction != 'd') {
                        *snake_direction = 'a';
                    }
                break;
                case 'a':
                    if(snake_previous_direction != 'a') {
                        *snake_direction = 'd';
                    }
                break;
            }
        }

        if(!(*viper_direction == 'i' || *viper_direction == 'k' || *viper_direction == 'j' || *viper_direction == 'l')) {
            *viper_direction = viper_previous_direction;
        }
        else if(active_spells[4] == 5) {
            switch(*viper_direction) {
                case 'i':
                    if(viper_previous_direction != 'w') {
                        *viper_direction = 's';
                    }
                break;
                case 'k':
                    if(viper_previous_direction != 's') {
                        *viper_direction = 'w';
                    }
                break;
                case 'l':
                    if(viper_previous_direction != 'd') {
                        *viper_direction = 'a';
                    }
                break;
                case 'j':
                    if(viper_previous_direction != 'a') {
                        *viper_direction = 'd';
                    }
                break;
            }
        }

        switch(*viper_direction) {
            case V_UP:
                *viper_direction = UP;
            break;
            case V_DOWN:
                *viper_direction = DOWN;
            break;
            case V_LEFT:
                *viper_direction = LEFT;
            break;
            case V_RIGHT:
                *viper_direction = RIGHT;
            break;
        }
    }




    dt_end = clock();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_snake_position(snake *snake_head, char *board) {
    snake *temporary;
    temporary = snake_head;
    while(temporary != NULL) {
        if(temporary == snake_head) {
            board[(temporary->y_coordinate * WIDTH_OF_BOARD + temporary->x_coordinate)] = 'X';
            temporary = temporary->next;
        }
        else {
            if(board[(temporary->y_coordinate * WIDTH_OF_BOARD + temporary->x_coordinate)] != 'X') {
                board[(temporary->y_coordinate * WIDTH_OF_BOARD + temporary->x_coordinate)] = 'O';
            }
            temporary = temporary->next;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_viper_position(snake *viper_head, char *board) {
    snake *temporary;
    temporary = viper_head;
    while(temporary != NULL) {
        if(temporary == viper_head) {
            board[(temporary->y_coordinate * WIDTH_OF_BOARD + temporary->x_coordinate)] = 'Q';
            temporary = temporary->next;
        }
        else {
            if(board[(temporary->y_coordinate * WIDTH_OF_BOARD + temporary->x_coordinate)] != 'Q') {
                board[(temporary->y_coordinate * WIDTH_OF_BOARD + temporary->x_coordinate)] = 'G';
            }
            temporary = temporary->next;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void change_snake_position(snake *snake_head, char snake_direction) {
    snake *temporary = snake_head;
    int temp_y;
    int temp_x;
    int temp_x2;
    int temp_y2;
    while(temporary != NULL) {
        if(temporary == snake_head) {
            temp_y = temporary->y_coordinate;
            temp_x = temporary->x_coordinate;
            switch(snake_direction) {
                case UP:
                    temporary->y_coordinate = temporary->y_coordinate - 1;
                break;
                case DOWN:
                    temporary->y_coordinate = temporary->y_coordinate + 1;
                break;
                case LEFT:
                    temporary->x_coordinate = temporary->x_coordinate - 1;
                break;
                case RIGHT:
                    temporary->x_coordinate = temporary->x_coordinate + 1;
                break;
            }
            temporary = temporary->next;
        }
        else {
            temp_x2 = temporary->x_coordinate;
            temp_y2 = temporary->y_coordinate;
            temporary->x_coordinate = temp_x;
            temporary->y_coordinate = temp_y;
            temp_x = temp_x2;
            temp_y = temp_y2;
            temporary = temporary->next;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void change_snake_position_during_crossing_border(snake *snake_head, char snake_direction) {
    snake *temporary = snake_head;
    int temp_y;
    int temp_x;
    int temp_x2;
    int temp_y2;
    while(temporary != NULL) {
        if(temporary == snake_head) {
            temp_y = temporary->y_coordinate;
            temp_x = temporary->x_coordinate;
            switch(snake_direction) {
                case UP:
                    temporary->y_coordinate = temporary->y_coordinate = (HEIGHT_OF_BOARD-2);
                break;
                case DOWN:
                    temporary->y_coordinate = temporary->y_coordinate = 1;
                break;
                case LEFT:
                    temporary->x_coordinate = temporary->x_coordinate = (WIDTH_OF_BOARD-2);
                break;
                case RIGHT:
                    temporary->x_coordinate = temporary->x_coordinate = 1;
                break;
            }
            temporary = temporary->next;
        }
        else {
            temp_x2 = temporary->x_coordinate;
            temp_y2 = temporary->y_coordinate;
            temporary->x_coordinate = temp_x;
            temporary->y_coordinate = temp_y;
            temp_x = temp_x2;
            temp_y = temp_y2;
            temporary = temporary->next;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void extend_snake(snake *snake_head, int *length_of_snake) {
    if(length_of_snake != NULL) (*length_of_snake)++;
    snake *new_node = (snake *)malloc(sizeof(snake));
    new_node->direction = '0';
    new_node->next = NULL; //Ecro
    new_node->x_coordinate = 0;
    new_node->y_coordinate = 0;
    snake *temporary = snake_head;
    while(temporary->next != NULL) {
        temporary = temporary->next;
    }
    temporary->next = new_node;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void is_raspberry_eaten(snake *snake_head, char *board, int *raspberry_eaten, char snake_direction, int raspberry_position, int *score, int *border_crossed, int *length_of_snake, int *raspberry_value) {
    int snake_next_position;
    if(*border_crossed != 1) {
        switch(snake_direction) {
        case UP:
            snake_next_position = ((snake_head->y_coordinate - 1) * WIDTH_OF_BOARD + snake_head->x_coordinate);
        break;
        case DOWN:
            snake_next_position = ((snake_head->y_coordinate + 1) * WIDTH_OF_BOARD + snake_head->x_coordinate);
        break;
        case LEFT:
            snake_next_position = (snake_head->y_coordinate * WIDTH_OF_BOARD + snake_head->x_coordinate - 1);
        break;
        case RIGHT:
            snake_next_position = (snake_head->y_coordinate * WIDTH_OF_BOARD + snake_head->x_coordinate + 1);
        break;
        }   
    }
    else if(*border_crossed == 1) {
        switch(snake_direction) {
                case UP:
                    snake_next_position = ((HEIGHT_OF_BOARD-2) * WIDTH_OF_BOARD + snake_head->x_coordinate);
                break;
                case DOWN:
                    snake_next_position = (1 * WIDTH_OF_BOARD + snake_head->x_coordinate);
                break;
                case LEFT:
                    snake_next_position = (snake_head->y_coordinate * WIDTH_OF_BOARD + (WIDTH_OF_BOARD-2));
                break;
                case RIGHT:
                    snake_next_position = (snake_head->y_coordinate * WIDTH_OF_BOARD + 1);
                break;
        }
    }
    if(snake_next_position == raspberry_position) {
        *raspberry_eaten = 1;
        extend_snake(snake_head, length_of_snake);
        *score = *score + *raspberry_value;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void cast_spell(int *active_spells) {
    int spell;
    int random_number = rand() % 7;
    while(active_spells[random_number] != 0) {
        random_number = rand() % 7;
    }
    active_spells[random_number] = 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void change_snake_position_during_respawn_of_phoenix(snake *snake_head, int respawn_x_coordinate) {
    snake *temporary = snake_head;

    snake_head->x_coordinate = respawn_x_coordinate;
    snake_head->y_coordinate = (HEIGHT_OF_BOARD / 2);

    while(temporary->next != NULL) {
        temporary = temporary->next;
        temporary->x_coordinate = 0;
        temporary->y_coordinate = 0;
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int is_dragon_fruit_eaten(snake *snake_head, char *board, int *dragon_fruit_eaten, char snake_direction, int dragon_fruit_position, int *border_crossed) {
    int snake_next_position;
    if(*border_crossed != 1) {
        switch(snake_direction) {
        case UP:
            snake_next_position = ((snake_head->y_coordinate - 1) * WIDTH_OF_BOARD + snake_head->x_coordinate);
        break;
        case DOWN:
            snake_next_position = ((snake_head->y_coordinate + 1) * WIDTH_OF_BOARD + snake_head->x_coordinate);
        break;
        case LEFT:
            snake_next_position = (snake_head->y_coordinate * WIDTH_OF_BOARD + snake_head->x_coordinate - 1);
        break;
        case RIGHT:
            snake_next_position = (snake_head->y_coordinate * WIDTH_OF_BOARD + snake_head->x_coordinate + 1);
        break;
        }   
    }
    else if(*border_crossed == 1) {
        switch(snake_direction) {
                case UP:
                    snake_next_position = ((HEIGHT_OF_BOARD-2) * WIDTH_OF_BOARD + snake_head->x_coordinate);
                break;
                case DOWN:
                    snake_next_position = (1 * WIDTH_OF_BOARD + snake_head->x_coordinate);
                break;
                case LEFT:
                    snake_next_position = (snake_head->y_coordinate * WIDTH_OF_BOARD + (WIDTH_OF_BOARD-2));
                break;
                case RIGHT:
                    snake_next_position = (snake_head->y_coordinate * WIDTH_OF_BOARD + 1);
                break;
        }
    }
    if(snake_next_position == dragon_fruit_position) {
        *dragon_fruit_eaten = 1;
        return 1;
    }
    else {
        return 0;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int is_wall_touched(snake *snake_head, char *board, char snake_direction) {
    int snake_next_position;
    switch(snake_direction) {
        case UP:
            snake_next_position = ((snake_head->y_coordinate - 1) * WIDTH_OF_BOARD + snake_head->x_coordinate);
        break;
        case DOWN:
            snake_next_position = ((snake_head->y_coordinate + 1) * WIDTH_OF_BOARD + snake_head->x_coordinate);
        break;
        case LEFT:
            snake_next_position = (snake_head->y_coordinate * WIDTH_OF_BOARD + snake_head->x_coordinate - 1);
        break;
        case RIGHT:
            snake_next_position = (snake_head->y_coordinate * WIDTH_OF_BOARD + snake_head->x_coordinate + 1);
        break;
    }
    if(board[snake_next_position] == '#') {
        return 1;
    }
    else {
        return 0;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int is_snake_twisted(snake *snake_head, char snake_direction, int is_border_crossed) {
    int snake_next_position;
    snake *temporary = snake_head;
    switch(snake_direction) {
        case UP:

            if(is_border_crossed != 1) {
                snake_next_position = ((snake_head->y_coordinate - 1) * WIDTH_OF_BOARD + snake_head->x_coordinate);
            }
            else {
                snake_next_position = ((HEIGHT_OF_BOARD-2) * WIDTH_OF_BOARD + snake_head->x_coordinate);
            }

            while(temporary->next != NULL) {
                if(snake_next_position == (temporary->y_coordinate * WIDTH_OF_BOARD + temporary->x_coordinate)) {
                    return 1;
                }
                temporary = temporary->next;
            }
            return 0;
        case DOWN:

            if(is_border_crossed != 1) {
                snake_next_position = ((snake_head->y_coordinate + 1) * WIDTH_OF_BOARD + snake_head->x_coordinate);
            }
            else {
                snake_next_position = (1 * WIDTH_OF_BOARD + snake_head->x_coordinate);
            }

            while(temporary->next != NULL) {
                if(snake_next_position == (temporary->y_coordinate * WIDTH_OF_BOARD + temporary->x_coordinate)) {
                    return 1;
                }
                temporary = temporary->next;
            }
            return 0;
        case LEFT:

            if(is_border_crossed != 1) {
                snake_next_position = (snake_head->y_coordinate * WIDTH_OF_BOARD + snake_head->x_coordinate - 1);
            }
            else {
                snake_next_position = (snake_head->y_coordinate * WIDTH_OF_BOARD + (WIDTH_OF_BOARD - 2));
            }

            while(temporary->next != NULL) {
                if(snake_next_position == (temporary->y_coordinate * WIDTH_OF_BOARD + temporary->x_coordinate)) {
                    return 1;
                }
                temporary = temporary->next;
            }
            return 0;
        case RIGHT:

            if(is_border_crossed != 1) {
                snake_next_position = (snake_head->y_coordinate * WIDTH_OF_BOARD + snake_head->x_coordinate + 1);
            }
            else {
                snake_next_position = (snake_head->y_coordinate * WIDTH_OF_BOARD + 1);
            }

            while(temporary->next != NULL) {
                if(snake_next_position == (temporary->y_coordinate * WIDTH_OF_BOARD + temporary->x_coordinate)) {
                    return 1;
                }
                temporary = temporary->next;
            }
            return 0;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int collision_check(snake *snake_head, snake *viper_head, char snake_direction, char viper_direction, int snake_is_border_crossed, int viper_is_border_crossed) {
    int snake_next_position;
    int viper_next_position;
    snake *temporary;
    //is snake collided with viper?
    switch(snake_direction) {
        case UP:

            if(snake_is_border_crossed != 1) {
                snake_next_position = ((snake_head->y_coordinate - 1) * WIDTH_OF_BOARD + snake_head->x_coordinate);
            }
            else {
                snake_next_position = ((HEIGHT_OF_BOARD-2) * WIDTH_OF_BOARD + snake_head->x_coordinate);
            }


        break;
        case DOWN:

            if(snake_is_border_crossed != 1) {
                snake_next_position = ((snake_head->y_coordinate + 1) * WIDTH_OF_BOARD + snake_head->x_coordinate);
            }
            else {
                snake_next_position = (1 * WIDTH_OF_BOARD + snake_head->x_coordinate);
            }


        break;
        case LEFT:

            if(snake_is_border_crossed != 1) {
                snake_next_position = (snake_head->y_coordinate * WIDTH_OF_BOARD + snake_head->x_coordinate - 1);
            }
            else {
                snake_next_position = (snake_head->y_coordinate * WIDTH_OF_BOARD + (WIDTH_OF_BOARD - 2));
            }


        break;
        case RIGHT:
            
            if(snake_is_border_crossed != 1) {
                snake_next_position = (snake_head->y_coordinate * WIDTH_OF_BOARD + snake_head->x_coordinate + 1);
            }
            else {
                snake_next_position = (snake_head->y_coordinate * WIDTH_OF_BOARD + 1);
            }


        break;
    }
    
    temporary = viper_head;
    while(temporary->next != NULL && temporary != NULL) {
        if(snake_next_position == (temporary->y_coordinate * WIDTH_OF_BOARD + temporary->x_coordinate)) {
            return 1;
        }
        temporary = temporary = temporary->next;
    }

    //is viper collided with snake?
    switch(viper_direction) {
        case UP:

            if(viper_is_border_crossed != 1) {
                viper_next_position = ((viper_head->y_coordinate - 1) * WIDTH_OF_BOARD + viper_head->x_coordinate);
            }
            else {
                viper_next_position = ((HEIGHT_OF_BOARD-2) * WIDTH_OF_BOARD + viper_head->x_coordinate);
            }


        break;
        case DOWN:

            if(viper_is_border_crossed != 1) {
                viper_next_position = ((viper_head->y_coordinate + 1) * WIDTH_OF_BOARD + viper_head->x_coordinate);
            }
            else {
                viper_next_position = (1 * WIDTH_OF_BOARD + viper_head->x_coordinate);
            }


        break;
        case LEFT:

            if(viper_is_border_crossed != 1) {
                viper_next_position = (viper_head->y_coordinate * WIDTH_OF_BOARD + viper_head->x_coordinate - 1);
            }
            else {
                viper_next_position = (viper_head->y_coordinate * WIDTH_OF_BOARD + (WIDTH_OF_BOARD - 2));
            }


        break;
        case RIGHT:
            
            if(viper_is_border_crossed != 1) {
                viper_next_position = (viper_head->y_coordinate * WIDTH_OF_BOARD + viper_head->x_coordinate + 1);
            }
            else {
                viper_next_position = (viper_head->y_coordinate * WIDTH_OF_BOARD + 1);
            }


        break;
    }
    
    temporary = snake_head;
    while(temporary->next != NULL && temporary != NULL) {
        if(viper_next_position == (temporary->y_coordinate * WIDTH_OF_BOARD + temporary->x_coordinate)) {
            return 1;
        }
        temporary = temporary = temporary->next;
    }


    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//KWAZAR374 2023
