# Golomb's randomness postulates

IDE: CLion  
compiler: MinGW

The homework for finding n bits sequences that satisfy Golomb's randomness postulates.  

You can change seqeunce length in the top of `main.cpp`.  

![This image is the top of main.cpp.](/img/01_define.png "This is the top of main.cpp.")  

## You can try these combinations:

 | LENGTH  |
 | :-------------: |
 | 3      |
 | 7      |
 | 15      |

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

After running, you will get something below (the result is running in `LENGTH`=3):  

![This image is the result when LENGTH=3.](/img/02_result_example.png "This image is the result when LENGTH=3.") 


## How do I let it work
The goal is to find all `s` that conform to the Golomb's randomness postulates rules.  


* **Rule 1**: In the cycle of `s`, the number of 1's differs from the number of 0's by **at most 1**. 
  * If `s` is a 7 bits sequence, the amounts of 1 can be 3 or 4.
* **Rule 2**: In the cycle of `s`, at least **1/2** of runs have length 1, at least **1/4** have length 2, at least **1/8** have length 3, etc. In addition, for each lengths, the amounts of blocks (with run of 1's) differs from the gaps (with run of 0's) by **at most 1**. 
  * If `s` is a 7 bits sequence, and have total runs of `5`, there are atleast 2 runs of length 1, atleast 1 run of length 2, atleast 0 run of length 3. So for the 5 runs sequence, the amounts of each runs could be {2, 1, 1} or {3, 2, 0}, for {length 1, length 2, length 3}.
* **Rule 3**: The autocorrelation function C(t).
  * In this code, we do the C(t) in the way that show below. That when meet the same number, do **+1**, else do **-1**. The value should be the same no matter how many times to shift. 
 
![This image is the C(t) fuction.](/img/03_CT.png "This image is the C(t) fuction.")

To meet the **rule 1**, I use **`found_one`** function to find the amount of 1 in `s`. Then check the amounts in line 211.  

To meet the **rule 2**, I use **`check_runs`** function to check the each lengths of runs in `s` have fit the rule, and record the amounts of gaps and blocks to make sure there differs is passed. Then check if it fit the rule in line 213.

To meet the **rule 3**, I use **`function_C`** function to calculate the value, and check is the value the same when **shift 1 to LENGTH-1**. Then check if it fit the rule in line 214.

At last, I print the `s` that conform to all the rules. 

## Discussion
I have no idea that I do it 100% right, but when s=7 I can get the completely right answers. If there are any questions, you can contact me here.

## 給所有有修資訊安全的同學們
抱歉了我的英文真的PRO到不行, 如果有問題可以在這邊問我, 我有能力就盡量回答.
S=7的情況下我確認過應該是對的, 總共會有24個sequences符合作業的需求, 如果再往上我就不是很確定了.
