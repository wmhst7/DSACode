#include <stdlib.h>
#include <stdio.h>
int main()
{
    FILE *fp = NULL;
    fp = fopen("input.txt", "w");
    int n = 400000, k = 5000;
    int t;
    fprintf(fp, "%d %d\n", n, k);
    for(int i=0;i<n;i++){
        //fprintf(fp, "00");
        for(int j=0;j<64;j++){
            fprintf(fp, "%d", rand()%2);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}