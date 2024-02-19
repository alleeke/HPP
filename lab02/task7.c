#include <stdio.h>
#include <math.h>

/* An integer is a palindrome if the reverse of that number is equal to the original
number. Check if the number entered by the user is a palindrome.
Example:
Input: 12345
Output: it is not a palindrome
Input: 46364
 */

int main() {
    int a; int flipped_a = 0;
    printf("Input integer: ");
    scanf("%d", &a);

    if (a < 0) {
        printf("Please enter a non-negative integer.\n");
        return 1;
    }

    int i = 1;
    size_t count = 0;
    int a_array[100];

    while (i <= a) {
        int b = (a / i) % 10;
        a_array[count] = b;
        i *= 10;
        count++;
    }


    for (size_t i = 0; i < count; i++)
    {   
        int k = pow(10,count-1-i);
        
        flipped_a += a_array[i]*k;
     }
    

    if(a - flipped_a == 0){
        printf("Output: %d is a palindrome",a);
    }
    else{
        printf("Output: %d is not a palindrome",a);

    } 
    
    
    return 0;
}
