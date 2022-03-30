# Golomb's randomness postulates

IDE: CLion  
compiler: MinGW

The homework for finding n bits sequences that satisfy Golomb's randomness postulates.  

You can change seqeunce length and the max run length of the sequence in the top of `main.cpp`.  

![This image is the top of main.cpp.](/img/01_define.png "This is the top of main.cpp.")  

## You can try these combinations:

 | LENGTH  | MAX_RUN_LENGTH |
 | ------------- |:-------------:|
 | 7      | 3     |
 | 15      | 4     |
 | 31      | 5     |

When LENGTH is up to 31, you will get poor effect. Maybe I will fix it in future.

## Result
The output include:
1. The sequence in decimal.
1. The sequence in binary.
1. The count of shift **`t`**. 
1. The value of **`C(t)`**. (**`t`** is in range of `1` to `LENGTH-1`)
1. The amounts of conform to **Rule 1**.
1. The amounts of conform to **Rule 2**.
1. The amounts of conform to **Rule 3**.

After running, you will get something like this:
![This image is the result when LENGTH=3 and MAX_RUN_LENGTH=2.](/img/02_result_example.png "This image is the result when LENGTH=3 and MAX_RUN_LENGTH=2.") 


## How do I let it work
```0 to 2^LENGTH-1``` is be checked that did it conform to the rules of Golomb's randomness postulates.

* **Rule 1**: In the cycle of `s`, the number of 1's differs from the number of 0's by **at most 1**. 
  * If `s` is a 7 bits sequence, the amounts of 1 can be 3 or 4.
* **Rule 2**: In the cycle of `s`, at least **1/2** of runs have length 1, at least **1/4** have length 2, at least **1/8** have length 3, etc. 
  * If `s` is a 7 bits sequence, there are 2 runs of length 1, 1 of length 2, 1 of length 3. The total run is 4 runs.
* **Rule 3**: The autocorrelation function C(t).
  * In this code, we do the C(t) in the way that show below. That when meet the same number, do **+1**, else do **-1**. The value should be the same no matter how many times to shift. 
 
![This image is the C(t) fuction.](/img/03_CT.png "This image is the C(t) fuction.")

To meet the **rule 1**, I use **`found_one`** function to find the amount of 1 in `s`. Then check the amounts in line 179.  

To meet the **rule 2**, I use **`check_total_runs`** function to check is the `s`'s total runs is equal to the correct one. And use **`found_runs`** function to check is the `MAX_RUN_LENGTH` exist?  
I found out that when the total runs is correct and `MAX_RUN_LENGTH` exist, the `s` must meet the **rule 2**.  Then check if it fit the rule in line 180.

To meet the **rule 3**, I use **`function_C`** function to calculate the value, and check is the value the same when **shift 1 to LENGTH-1**.

At last, I print the `s` that conform to all the rules. 

各位有修資安的朋朋可以參考, 但請不要直接拿原始碼去影印喔! :D
