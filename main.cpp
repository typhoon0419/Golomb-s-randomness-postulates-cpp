#include<stdio.h>
#include<math.h>

#define LENGTH 3

int found_one(int array[]){
    int count=0;
    for (int i = 0; i < LENGTH; ++i)
        if(array[i]==1)
            count++;
    return count;
}
void initial_a(int array[]){
    for (int i = 0; i < LENGTH; ++i)
        array[i] = 0;
}
void print_array(int array[]){
    for(int n = LENGTH; n > 0; n--)
        printf("%d",array[n - 1]);
    //printf("\n");
}

int found_run(int array[]){
    int pre;
    int count_of_runs = 0;
    for (int i = 0; i < LENGTH; ++i) {
        if(i == 0){
            pre = array[i];
            count_of_runs++;
            continue;
        }
        if(array[i] != pre){
            pre = array[i];
            count_of_runs++;
        }
    }
    return count_of_runs;
}

int get_runs_max_amount(int total_runs, int length){
    return ceil(total_runs/ pow(2,length));
}

bool check_runs(int total_runs, int array[]){
    int pre;
    int len_count, amounts_count = 0;//算run長
    int max_amounts;
    int gap, block; //0, 1

    for (int i = 1; i <= LENGTH / 2; ++i) {
        gap = 0;
        block = 0;
        max_amounts = get_runs_max_amount(total_runs, i);
        len_count = 0;
        pre = array[0];
        for (int j = 0; j < LENGTH; ++j) {
            if (j == LENGTH -1){
                if (pre != array[j]){
                    if (len_count == i){
                        amounts_count ++;
                        if (array[j-1] == 1)
                            block ++;
                        else
                            gap ++;
                    }
                    len_count = 1;
                    if (len_count == i){
                        amounts_count ++;
                        if (array[j] == 1)
                            block ++;
                        else
                            gap ++;
                    }
                } else{
                    len_count++;
                    if (len_count == i){
                        amounts_count ++;
                        if (array[j-1] == 1)
                            block ++;
                        else
                            gap ++;
                    }
                }
            }
            else if (pre == array[j]){
                len_count ++;
            }
            else{
                if (len_count == i){
                    amounts_count ++;
                    if (array[j-1] == 1)
                        block ++;
                    else
                        gap ++;
                }
                len_count = 1;
            }
            pre = array[j];
        }
        if (abs((gap - block)) >= 2){
            return false;
        }
        //printf("%d:%d ", i,amounts_count);
        if ( total_runs % int(pow(2,i)) == 0 && max_amounts == amounts_count){
            amounts_count = 0;
        }
        else if(max_amounts == amounts_count || max_amounts - 1 == amounts_count){
            amounts_count = 0;
        }
        else
            return false;
    }
    return true;
}

void shift(int array[], int target[], int shift_len){
    for (int i = 0; i < LENGTH; ++i) {
        target[i] = array[((i+shift_len) % LENGTH)];
    }
}

bool function_C(int array[], int shift_array[]){
    int answer_of_all_C = 0;
    int answer;
    //printf("\nC(t) of shift i\n   t: ");

    /*for (int k = 1; k < LENGTH; ++k)
        printf("%2d ", k);
    printf("\nC(t): ");
     */
    for (int i = 1; i < LENGTH; ++i) {
        answer = 0;
        shift(array, shift_array, i);
        for (int j = 0; j < LENGTH; ++j) {
            if(array[j] == shift_array[j])
                answer ++;
            else
                answer --;
        }
        //printf("%d ", answer);
        if(i == 1)
            answer_of_all_C = answer;
        else if (answer!=answer_of_all_C){
            //printf("Fail when shift %d\n\n", i);
            return false;
        }
    }
    //printf("\n");
    return true;
}

bool print_function_C(int array[], int shift_array[]){
    int answer_of_all_C = 0;
    int answer;
    printf("\nC(t) of shift i\n   t: ");

    for (int k = 1; k < LENGTH; ++k)
        printf("%3d ", k);
    printf("\nC(t): ");

    for (int i = 1; i < LENGTH; ++i) {

        answer = 0;
        shift(array, shift_array, i);
        for (int j = 0; j < LENGTH; ++j) {
            if(array[j] == shift_array[j])
                answer ++;
            else
                answer --;
        }
        printf("%3d ", answer);
        if(i == 1)
            answer_of_all_C = answer;
        else if (answer!=answer_of_all_C){
            printf("Fail when shift %d\n\n", i);
            return false;
        }
    }
    printf("\n\n");
    return true;
}

int main(void)
{
    int i=0;
    int n;
    int a[LENGTH];
    //int runs[LENGTH / 2];
    int count;
    int R1count = 0;
    int R2count = 0;
    int R3count = 0;
    int shift_array[LENGTH];

    int total_runs;


    //printf("%d", total_runs);
    //found_runs_needed(total_runs,runs);

    for (long j = 0; j < pow(2, LENGTH); ++j) {
        initial_a(a);
        i=0;
        n = j;
        while (n > 0) {
            a[i] = n % 2;
            i = i + 1;
            n = n/2;
        }
        count = found_one(a);
        if(count==(LENGTH/2) || count==((LENGTH+1)/2)){
            total_runs = found_run(a);
            if(check_runs(total_runs, a)){
                if(function_C(a, shift_array)){
                    printf("%3d: ", j);
                    print_array(a);
                    print_function_C(a, shift_array);
                    R3count++;
                }
                R2count++;
            }
            R1count++;
        }
    }

    printf("\nAmounts of conform to R1 = %d\nAmounts of conform to R2 = %d\nAmounts of conform to R3 = %d\n", R1count, R2count, R3count);

    return 0;
}
