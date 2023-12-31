#include<stdio.h>
int LRU(int Time[], int num_f)
{
    int pos = 0, i, min = Time[0];
    for(i = 1; i < num_f; i++)
    {
        if(Time[i] < min)
        {
            min = Time[i];
            pos = i;
        }
    }
    return pos;
}
void main()
{
    int i, j, num_p, orig_num_p, num_f, pg[100], fr[10], Time[10], c = 0, flag1, flag2, miss = 0, hit, pos;
    float miss_ratio, hit_ratio;
    char ch;
    do
    {
        printf("\nEnter the number of pages (maximum 100): ");
        scanf("%d", &num_p);
        orig_num_p = num_p;
        for(i = 0; i < num_p; i++)
        {
            printf("\nFor page %d, enter data: ", (i+1));
            scanf("%d", &pg[i]);
        }
        printf("\nEnter the number of frames (maximum 10): ");
        scanf("%d", &num_f);
        for(i = 0; i < num_f; i++)
            fr[i] = -1;
        for(i = 0; i < num_p; i++)
        {
            flag1 = flag2 = 0;
            for(j = 0; j < num_f; j++)
            {
                if(fr[j] == pg[i])
                {
                    c++;
                    Time[j] = c;
                    flag1 = flag2 = 1;
                    break;
                }
            }
            if(flag1 == 0)
            {
                for(j = 0; j < num_f; j++)
                {
                    if(fr[j] == -1)
                    {
                        c++;
                        miss++;
                        fr[j] = pg[i];
                        Time[j] = c;
                        flag2 = 1;
                        break;
                    }
                }
            }
            if(flag2 == 0)
            {
                pos = LRU(Time, num_f);
                c++;
                miss++;
                fr[pos] = pg[i];
                Time[pos] = c;
            }
            printf("\n");
            for(j = 0; j < num_f; j++)
                printf("%d\t", fr[j]);
        }
        printf("\nThe number of Cache Miss is %d.", miss);
        hit = orig_num_p - miss;
        printf("\nThe number of Cache Hit is %d.", hit);
        miss_ratio = (100*miss)/orig_num_p;
        printf("\nThe Miss Ratio is %f.", miss_ratio);
        hit_ratio = 100 - miss_ratio;
        printf("\nThe Hit Ratio is %f.", hit_ratio);
        printf("\nDo you want to try again?\nPress 'Y' otherwise press any other character.\nEnter your choice: ");
        scanf("%s", &ch);
    }while(ch=='Y');
}
