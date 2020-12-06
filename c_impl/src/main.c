#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_SPLIT_LIST_SIZE 8
#define INIT_INPUT_LIST_SIZE 8
#define INIT_OUTPUT_LIST_SIZE 8

void print_help() {
    puts("./program <comma_separated_split_list> <comma_separtaed_input_list>");
}

void print_l(unsigned int size, int *list) {
    for(unsigned int i = 0; i < size; ++i) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

void push_l(unsigned int *size, unsigned int *capacity, int **list, int new) {
    if(*size == *capacity) {
        int *new_list = (int*)malloc(*capacity * sizeof(int) * 2);
        memcpy(new_list, *list, *capacity * sizeof(int));
        free(*list);
        *list = new_list;
        *capacity = *capacity * 2;
    }

    (*list)[*size] = new;
    *size = *size + 1;
}

int main(int argc, char **argv) {
    if(argc != 3) {
        puts("ERROR: Requires two arguments:");
        print_help();
        return 1;
    }

    unsigned int sl_size = 0;
    unsigned int sl_capacity = INIT_SPLIT_LIST_SIZE;
    int *split_list = (int*)malloc(sl_capacity * sizeof(int));

    unsigned int il_size = 0;
    unsigned int il_capacity = INIT_INPUT_LIST_SIZE;
    int *input_list = (int*)malloc(il_capacity * sizeof(int));

    int temp = 0;
    for(unsigned int i = 0; argv[1][i] != 0; ++i) {
        if(argv[1][i] != ',') {
            temp = temp * 10 + (int)(argv[1][i] - '0');
        } else {
            push_l(&sl_size, &sl_capacity, &split_list, temp);
            temp = 0;
        }
    }
    push_l(&sl_size, &sl_capacity, &split_list, temp);
    temp = 0;

    for(unsigned int i = 0; argv[2][i] != 0; ++i) {
        if(argv[2][i] != ',') {
            temp = temp * 10 + (int)(argv[2][i] - '0');
        } else {
            push_l(&il_size, &il_capacity, &input_list, temp);
            temp = 0;
        }
    }
    push_l(&il_size, &il_capacity, &input_list, temp);

    puts("Got input:");
    print_l(sl_size, split_list);
    print_l(il_size, input_list);

    unsigned int *out_sizes = (unsigned int*)calloc(
        sl_size, sizeof(unsigned int));
    unsigned int *out_capacities = (unsigned int*)malloc(
        sl_size * sizeof(unsigned int));
    for(unsigned int i = 0; i < sl_size; ++i) {
        out_capacities[i] = INIT_OUTPUT_LIST_SIZE;
    }
    int **out_lists = (int**)malloc(
        sl_size * sizeof(int*));
    for(unsigned int i = 0; i < sl_size; ++i) {
        out_lists[i] = (int*)malloc(
            INIT_OUTPUT_LIST_SIZE * sizeof(int));
    }

    unsigned int il_idx = 0;
    for(unsigned int i = 0; i < sl_size; ++i) {
        for(unsigned int j = 0; j < split_list[i]; ++j) {
            if(il_idx >= il_size) {
            } else {
                push_l(out_sizes + i, out_capacities + i, out_lists + i,
                    input_list[il_idx++]);
            }
        }
    }

    puts("Output lists:");
    for(unsigned int i = 0; i < sl_size; ++i) {
        print_l(out_sizes[i], out_lists[i]);
    }

    free(split_list);
    free(input_list);
    free(out_sizes);
    free(out_capacities);
    for(unsigned int i = 0; i < sl_size; ++i) {
        free(out_lists[i]);
    }
    free(out_lists);
    return 0;
}
