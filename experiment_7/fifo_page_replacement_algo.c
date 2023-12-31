#include<stdio.h>
int main()
{
    int i, j, k, num_p, orig_num_p, pg[100], fr[10], num_f, avail, miss, hit;
    float miss_ratio, hit_ratio;
    char ch;
    do
    {
        miss = 0;
        printf("\nEnter the number of pages (maximum 100): ");
        scanf("%d", &num_p);
        orig_num_p = num_p;
        for(i = 1; i <= num_p; i++)
        {
            printf("\nFor page %d, enter data: ", i);
            scanf("%d", &pg[i]);
        }
        printf("\nEnter the number of frames (maximum 10): ");
        scanf("%d", &num_f);
        for(i = 0; i < num_f; i++)
            fr[i] = -1;
        j = 0;
        printf("\nReference String\tPage Frame\n");
        for(i = 1; i <= num_p; i++)
        {
            printf("%d\t\t\t", pg[i]);
            avail = 0;
            for(k = 0; k < num_f; k++)
                if(fr[k] == pg[i])
                avail = 1;
                if(avail == 0)
                {
                    fr[j] = pg[i];
                    j = (j+1)%num_f;
                    miss++;
                    for(k = 0; k < num_f; k++)
                        printf("%d\t", fr[k]);
                }
                printf("\n");
        }
        printf("\nThe number of Cache Miss is %d.", miss);
        hit = orig_num_p - miss;
        printf("\nThe number of Cache Hit is %d.", hit);
        miss_ratio = (miss*100)/orig_num_p;
        printf("\nThe Miss Ratio is %f.", miss_ratio);
        hit_ratio = 100 - miss_ratio;
        printf("\nThe Hit Ratio is %f.", hit_ratio);
        printf("\nDo you want to try again?\nIf so, then press 'Y' otherwise press any other character.\nEnter your choice: ");
        scanf("%s", &ch);
    }while(ch=='Y');
}
