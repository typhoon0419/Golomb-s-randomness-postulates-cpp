#include<stdio.h>
#include<math.h>

#define LENGTH 15
#define MAX_RUN_LENGTH 4

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

void found_runs_needed(int total_runs, int array[]){
    for (int i = 0; i < LENGTH / 2; ++i) {
        if(total_runs == 1){
            array[i]=1;
            break;
        }
        array[i]=total_runs/2;
        total_runs = total_runs/2;
    }
}

bool check_total_runs(int total_runs, int array[]){
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
    //printf("\ncount_of_runs = %d\n", count_of_runs);

    if(total_runs == count_of_runs)
        return true;
    else
        return false;
}

bool found_runs(int array[]){
    int pre;
    int count = 0;

    for (int i = 0; i < LENGTH; ++i) {
        if (i==0)
            pre = array[i];

        if(array[i] != pre){
            count = 0;
            pre = array[i];
        }

        count++;

        if(count == MAX_RUN_LENGTH)
            return true;
    }
    return false;
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
    if(LENGTH % 2)
        total_runs = (LENGTH + 1) / 2;
    else
        total_runs = LENGTH / 2;

    //printf("%d", total_runs);
    //found_runs_needed(total_runs,runs);

    for (int j = 0; j < pow(2, LENGTH); ++j) {
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
            if(check_total_runs(total_runs, a)&& found_runs(a)){ //
                if(function_C(a, shift_array)){
                    printf("\n%6d: ", j);
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