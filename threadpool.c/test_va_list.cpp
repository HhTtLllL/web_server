//##################################################################
// File Name: test_va_list.cpp
// File Effect: 
// Author: tttt
// mail: tttt@xiyoulinux.org
// Created Time: 2020年02月19日 星期三 22时00分41秒
//=============================================================
//!/usr/bin/python
#include<stdarg.h>
#include<stdio.h>

int sum(int, ...);

int main(void)
{
   printf("10、20 和 30 的和 = %d\n",  sum( 10, 20, 30) );
   printf("4、20、25 和 30 的和 = %d\n",  sum( 4, 20, 25, 30) );

   return 0;
}

int sum(int num_args, ...)
{
   int val = 0;
   va_list ap;
   int i;

   va_start(ap, num_args);
   printf( "num_args = %d\n",num_args);
   for(i = 0; i < num_args; i++)
   {
      val += va_arg(ap, int);
   }
   va_end(ap);
 
   return val;
}
