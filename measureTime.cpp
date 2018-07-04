#include <time.h>
#include <stdio.h>

time_t start,end;
time (&start);
.
.
.
<your code>
.
.
.
time (&end);
double dif = difftime (end,start);
printf ("Elasped time is %.2lf seconds.", dif );
