#include <stdio.h>

float roun(float x) {

   // Rounds to the nearest integer.
   // .5 and above is rounded up
   // below .5 is rounded down

   float modX = mod(x, 1);

   if (modX > 0) {
      if (modX >= 0.5) {
         x = x + 1 - modX;
      } else if (modX < 0.5) {
         x = x - modX;
      }
   } else if (modX < 0) {
      if (modX <= -0.5) {
         x = x - (1 + modX);
      } else if (modX > -0.5) {
         x = x - modX;
      }      
   }

   return x;
}

double min(double x, double y) {

    // Returns the smaller value.
    
    if (x > y) {
        x = y;
    }
    
    return x;
}

double max(double x, double y) {

   // Returns the bigger value

    if (x < y) {
        x = y;
    }

    return x;
}

float power(float x, int y) {

   // custom power function to allow for floats to be raised to an int power

   float temp = x;

   if (y > 1) {
      for (int i = 0; i < y - 1; ++i) {
         x = x * temp;
      }
   } else if (y == 1) {
      x = x;
   } else if (y == 0) {
      x = 1;
   } else if (y == -1) {
      x = ((float) 1) / x;
   } else {
      x = ((float) 1) / x;

      for (int i = 0; i > y; i--) {
         x = x * ((float) 1) / temp;
      }
   }

   return x;
}