#include <stdio.h> //include C language standard library

double absolute(double num) { //create a function to return the inputs absoluete value
    if (num < 0) {
        return (num * -1); //if the number if negative, multiply it by -1
    } else {
        return num; //if it is not negative, return the number as in 
    }
}

double PowerTen(int num){ //create a function to calculate the power of 10's
    double result = 1.0; //initlaize the vairbale as 1
    if (num >= 0) //if the input is more than 0, 
    {
        for (int i = 0; i < num; i++) //implement a for loop for repeated action
        {
            result *= 10; //multiply the number by 10 the same number of times as the input dictates
        }
        
    }
    else{
        for (int i = 0; i < -num; i++) //if the input is a negative, implement for loop for repeated action
        {
            result /=  10; //divide the number by 10 the same number of times as the input dictates
        }
    }
    return result; //return the result of the loop
}

double sqrtUser(double number, int n) { //main funcion that will take the inputs
    double difference = PowerTen(-n); //this will call the PowerTen function to calculate the precision
    double Current_guess = number / 2; //an initial guess for the newtons method
    double previous_guess; //initlaize the vairable of previous guess

    do {
        previous_guess = Current_guess; //the prevoius guess now becomes the current guess
        Current_guess = 0.5 * (Current_guess + number / Current_guess); //do the newtons method equation
    } while (absolute(Current_guess - previous_guess) > difference); //keep going untill the aboslute 
    //difference of current guess and previous guess is more than the differnece 

    double factor = PowerTen(n); //find the power of ten of the deicaml place input
    Current_guess = (int)(Current_guess * factor) / factor; // multiply the current guess by factor, and 
    //then turn it into an integer, earsing any decimals, and then divide by factor to return the decimal place

    return Current_guess; //return the final result
}

int main() { //start the program
    double num; //inital vairable num as the number you want to root
    int num_decimals; //inital the vaiable num_deciamls as the number of decimals yoou want as an integer

    printf("Enter the number you would like the square root of: ");//Print a statment to ask for the number to square root
    scanf("%lf", &num); //take the input from user, scan it and store it in the vairable num
    
    printf("Enter the number of deciamals you would like: ");//Print a statment to ask for the number of deicmals
    scanf("%d", &num_decimals);//take the input from user, scan it and store it in the vairable num_decimals

    double result = sqrtUser(num, num_decimals); //execute the square root function using the user inputs

    if (result > 0) {
        printf("The square root of %.15f to %d decimals places is %.15f" ,num,num_decimals ,result);//as long as the result is more than 0
        // print it with respect to 15 deicmals
    }

}
