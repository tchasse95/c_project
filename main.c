//
//  main.c
//  approximating
//
//  Created by TCHASSE ODJAC on 07.06.17.
//  Copyright © 2017 TCHASSE ODJAC. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define PI 3.141592654

/** HELPER FUNCTIONS **/
//POWER
double power(double x,double exp){
    double result = 1;
    int i = 0;
    if(exp == 0){
        return 1;
    }
    else if(exp < 0){
        result = 1 / power(x,(exp*(-1)));
    }
    else{
        for(i = 1; i <= exp; i++){
            result = result * x;
        }
    }
    return result;
}


//ABSOLUTE VALUE
double absolutevalue(double term){
    if (term < 0)
        return (term*(-1));
    else
        return term;
}


//FACTORIAL
double factorial(double number){
    int i = 0;
    double help = number;
    if(number == 0)
        return 1;
    else{
        for(i = number; i > 1; i--){
            help = help - 1;
            number = number * help;
        }
    }
    return number;
}



/** SERIES FUNCTIONS **/

//BERNOULLI NUMBERS (n = number of even Bernoulli numbers
//e.g. if n = 3 then the result is the 6th Bernoulli number
double bernoulliInnerSeries(double n, double eps){
    double sum = 0;
    double term = 0;
    int r = 1;
    
    do{
        term = power((2*PI*r), (-2 * n));
        sum = sum + term;
        r++;
    }while(term >= eps);
    
    return sum;
}

double bernoulliEven(double n, double eps){
    double result = 0;
    result = 2 * power((-1),(n+1)) * factorial(2*n) * bernoulliInnerSeries(n, eps);
    return result;
}


//ARSINH
double arsinhapprox(float x, float epsilon){
    float sum = 0;
    float term = 0;
    float numerator = 0;
    float denominator = 0;
    int n = 0;
    int sign = 1;
    
    do{
        numerator = factorial(2*n) * sign;
        denominator = power(4, n) * power(factorial(n), 2) * (2*n + 1);
        term = numerator / denominator;
        term = term * power(x, ((2*n) + 1));
        sum += term;
        n++;
        sign = sign * -1;
    }while(absolutevalue(term) > epsilon);
    
    return sum;
}


//TANGENT
double tanapprox(double x, double epsilon){
    double sum = 0;
    double term = 0;
    double numerator = 0;
    double denominator = 0;
    int n = 1;
    int sign = 1;
    
    do{
        numerator = power(4, n) * sign * ((power(4, n))-1) * bernoulliEven(n, 0.00000000001) * power(x, (2*n)-1);
        denominator = factorial(2*n);
        term = numerator / denominator;
        sum += term;
        n++;
        sign = sign * -1;
    }while(absolutevalue(term) >= epsilon);
    
    return sum;
}


//NATURAL LOGARITHM
double naturallog(double x, double epsilon){
    double sum = 0;
    double term = 0;
    double numerator = 0;
    double denominator = 0;
    int n = 1;
    int sign = 1;
    
    do{
        numerator = power(x, n) * sign;
        denominator = n;
        term = numerator / denominator;
        sum += term;
        n++;
        sign = sign * -1;
    }while(absolutevalue(term) >= epsilon);
    
    return sum;
}



// ARCSINE domain [-1,1]
double arcsin(double x, double epsilon){
    double sum = 0;
    double term = 1;
    double numerator = 0;
    double denominator = 0;
    int n = 0;
    
    do{
        numerator = factorial(2*n);
        denominator = power(2, 2*n) * power(factorial(n), 2) * ((2* n) + 1);
        term = numerator / denominator;
        term = term * power(x, ((2*n)+1));
        sum = sum + term;
        n++;
    }while(absolutevalue(term) >= epsilon);
    
    return sum;
}


// ARCTANGENT domain |x| < PI/2
float arctan(float x, float epsilon){
    float sum = x;
    float term = 0;
    float numerator = -1;
    float denominator = 0;
    int n = 1;
    
    do{
        denominator = ((2*n) + 1);
        term = numerator / denominator;
        term = term * power(x, ((2*n)+1));
        sum = sum + term;
        n++;
        numerator *= -1;
    }while(absolutevalue(term) >= epsilon);
    
    return sum;
}


// PI APPROXIMATION
double approxPi(double eps){
    
    double sum = 0.0;
    double term = 0.0;
    double numerator = 0.0;
    double denomiator = 0.0;
    int n = 1;
    
    do{
        numerator = n*power(2,n)*power(factorial(n),2);
        denomiator = factorial(2*n);
        term = numerator / denomiator;
        sum = sum + term;
        n++;
    }while((numerator/denomiator) > eps);
    return (sum-3);
}


// ARCCOS
void arccos(){
    float sum = 0.0;
    float term = 0.0;
    float numerator = 0.0;
    float denomiator = 0.0;
    int n = 0;
    float x = 0.0;
    float eps = 0.0;
    
    printf("Please enter a value for x: ");
    scanf("%f", &x);
    printf("Please enter the exactness for the calculation: ");
    scanf("%f", &eps);
    
    do{
        numerator = factorial(2*n);
        denomiator = power(4,n) * power(factorial(n),2) * (2*n + 1);
        term = (numerator / denomiator) ;
        term = term * pow(x,(2*n + 1));
        sum = sum + term;
        n++;
    }while(absolutevalue(term) > eps);
    
    sum = (approxPi(eps)/2) - sum;
    
    printf("Arccos(%f): %.10f \n\n", x, sum);
    
}


/** MAIN **/
int main(){
    int selection = 0;
    float x = 0;
    float eps = 0;
    double result = 0;
    
    do{
        printf("SERIES EXPANSION\n=================\n\n");
        printf("Choose a Series you would like to calculate.\n");
        printf("(1) Arctan(x)\n");
        printf("(2) Pi\n");
        printf("(3) Arccos(x)\n\n");
        printf("To exit press (0).\n\n");
        printf("Your selection: ");
        scanf("%i", &selection);
        
        if(selection == 0){
            printf("Good Bye!\n");
        }
        else{
            switch(selection){
                case 1 :
                    printf("Please enter a value for x: ");
                    scanf("%f", &x);
                    printf("Please enter the exactness for the calculation: ");
                    scanf("%f", &eps);
                    result = arctan(x, eps);
                    printf("Arctan(%f): %.10f", x, result);
                    printf("\n\n");
                    break;
                    
                case 2 :
                    printf("Please enter the exactness for the calculation: ");
                    scanf("%f", &eps);
                    result = approxPi(eps);
                    printf("Your result is: %.10f", result);
                    printf("\n\n");
                    break;
                    
                case 3 :
                    arccos();
                    printf("\n\n");
                    break;
                    
                default : printf("\nInvalid input!\n\n");
            }
        }
    }while(selection != 0);
    return 0;
}
