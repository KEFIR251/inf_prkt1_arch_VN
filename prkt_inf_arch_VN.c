#include <stdio.h>
#define MEM 256
// var0
// Сделать уровни 4, 5 и предотчёт!

int main(void) {
    int cpu_state[8] = {6, 0, 0, 0, 0, 0, 0, 0};
    int memory[MEM] = {0};
    
    scanf("%d", &memory[0]);
    cpu_state[3] = memory[0];

    int index = 1;
    while(index < MEM && scanf("%d", &memory[index]) != EOF) {index++;}
    
    int re_bug = 0;
    while(cpu_state[4] == 0) {
        if (cpu_state[0] >= MEM || cpu_state[0] < 0) {
            printf("Ошибка: pc за границами памяти!\n");
            cpu_state[5] = cpu_state[0];
            cpu_state[0] = cpu_state[3];
            if (re_bug == 1) {
                printf("(Повторное прерывание)\n");
                printf("Программа завершенна с ошибкой.\n");
                cpu_state[4] = 1;
                break;
            } else {
                re_bug = 1;
                continue;
            }
        }

        cpu_state[2] = memory[cpu_state[0]];
        if (cpu_state[0] + 1 >= MEM) {
            printf("Ошибка: Операнд команды за границами памяти!\n");
            cpu_state[5] = cpu_state[0];
            cpu_state[0] = cpu_state[3];
            if (re_bug == 1) {
                printf("(Повторное прерывание)\n");
                printf("Программа завершенна с ошибкой.\n");
                cpu_state[4] = 1;
                break;
            } else {
                re_bug = 1;
                continue;
            }
        }
        
        int op_ad = memory[cpu_state[0] + 1];
        if (op_ad < 0 || op_ad >= MEM) {
            printf("Ошибка: Адрес операнда за границами памяти!\n");
            cpu_state[5] = cpu_state[0];
            cpu_state[0] = cpu_state[3];
            if (re_bug == 1) {
                printf("(Повторное прерывание)\n");
                printf("Программа завершенна с ошибкой.\n");
                cpu_state[4] = 1;
                break;
            } else {
                re_bug = 1;
                continue;
            }
        }

        switch(cpu_state[2]) {
            case 0:
                printf("pc=%d: команда %d, Стоп\n", cpu_state[0], cpu_state[2]);
                cpu_state[4] = 1;
                break;
            case 1:
                cpu_state[1] = memory[op_ad];
                printf("pc=%d: команда %d, operand=%d, acc=%d\n", cpu_state[0], cpu_state[2], op_ad,  cpu_state[1]);
                cpu_state[0] += 2;
                break;
            case 2:
                cpu_state[1] += memory[op_ad];
                printf("pc=%d: команда %d, operand=%d, acc=%d\n", cpu_state[0], cpu_state[2], op_ad,  cpu_state[1]);
                cpu_state[0] += 2;
                break;
            case 3:
                cpu_state[1] -= memory[op_ad];
                printf("pc=%d: команда %d, operand=%d, acc=%d\n", cpu_state[0], cpu_state[2], op_ad,  cpu_state[1]);
                cpu_state[0] += 2;
                break;
            default:
                printf("Ошибка: Неизвестный код команды!\n");
                cpu_state[5] = cpu_state[0];
                cpu_state[0] = cpu_state[3];
                if (re_bug == 1) {
                    printf("(Повторное прерывание)\n");
                    printf("Программа завершенна с ошибкой.\n");
                    cpu_state[4] = 1;
                    goto unknow_code_bug_break;
                } else {
                    re_bug = 1;
                    continue;
                }
        }
            re_bug = 0;
    }
            unknow_code_bug_break:
    
    return 0;
}