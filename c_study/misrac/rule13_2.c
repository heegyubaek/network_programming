/* Rule 13.2: 논리적 상수와의 비교
   논리적 상수와의 비교는 반드시 명시적으로 수행해야 하며, 묵시적인 비교는 피해야 함    
 */

 #include <stdio.h>

 bool func(bool flag) {
    // if(flag) {  //MISRA 위반: 암시적인 true 비교 수행함
    if(flag == true) {  //수정: 명시적인 true 비교 수행해야함
        return true;
    }
    return false;
 }

 int main() {
    bool flag = false;

    func(flag);

    return 1;
 }