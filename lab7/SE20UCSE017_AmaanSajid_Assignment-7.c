#include <stdio.h>
#include <stdlib.h>
int main() {
    int N, j;
    printf("Enter the number of frames to be transmitted: ");
    scanf("%d", &N);
    time_t t;
          srand((unsigned)time(&t));
    for(int i=1; i<N+1;i++)
    {
        printf("Frame Number: %d\n", i);
        printf("Data= %d\n", rand());
        j=rand()%6;
        printf("time= %d", j);
        if(j==0)
        {
            printf("time= %d", j);
        }
        else if(j<3)
        {
            printf("Time= ");
            for(int x=1;x<j;x++)
        printf("%d, ", x);
        }
        else{
            printf("Time= ");
            for(int x=1;x<=3;x++)
        printf("%d, ", x);
        }
        printf("\n");
        if(j>=3)
        {
           printf("Ack: No\nResend: Yes");
    }
        else
        {
            printf("Ack: Yes\nResend: No");
        }
        printf("\n");
    }
   
}