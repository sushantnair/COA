#include<stdio.h>
int bits(int);
void main()
{
    int blocks_in_cache, words_per_block, k, ch, prog_ch;
    int block_size, word_size, no_of_blocks_in_memory, mm_size, add_size, tag_size;
    int no_sets, set_size;
    printf("\nProgram to implement Cache Mapping Techniques.");
    do
    {
        printf("\nEnter the number of blocks in cache: ");
        scanf("%d", &blocks_in_cache);
        printf("\nEnter the number of words in each block: ");
        scanf("%d", &words_per_block);
        printf("\nEnter the number of blocks in memory: ");
        scanf("%d", &no_of_blocks_in_memory);
        mm_size = no_of_blocks_in_memory*words_per_block;
        add_size = bits(mm_size);
        printf("\nThe address size is %d bits.", add_size);
        do
        {
            printf("\nEnter:\n'1' for Direct Mapping.\n'2' for Set Associative Mapping.\n'3' to exit.\nEnter your choice: ");
            scanf("%d", &ch);
            switch(ch)
            {
                case 1:
                   block_size = bits(blocks_in_cache);
                   printf("\n(RESULT) Thus, the block size is %d bits.", block_size);
                   word_size = bits(words_per_block);
                   printf("\n(RESULT) Thus, the word size is %d bits.", word_size);
                   tag_size = add_size - block_size - word_size;
                   printf("\n(RESULT) Thus, the tag size is %d bits.", tag_size);
                break;
                case 2:
                    printf("\nEnter value of 'k' for k-way Set Associative Mapping: ");
                    scanf("%d", &k);
                    no_sets = blocks_in_cache/k;
                    printf("\nThe number of sets are %d.", no_sets);
                    word_size = bits(words_per_block);
                    printf("\n(RESULT) Thus, the word size is %d bits.", word_size);
                    set_size = bits(no_sets);
                    printf("\n(RESULT) Thus, the set size is %d bits.", set_size);
                    tag_size = add_size - set_size - word_size;
                    printf("\n(RESULT) Thus, the tag size is %d bits.", tag_size);
                break;
                case 3:
                    printf("\nE\tX\tI\tT\tI\tN\tG\t.\t.\t.");
                break;
                default:
                    printf("\nPlease enter '1', '2' or '3' only and try again!");
            }
        }while(ch!=3);
        printf("\nDo you want to enter another set of Cache data and try with different\nCache Mapping Techniques?, enter '1' otherwise any other character.\nEnter your choice: ");
        scanf("%d", &prog_ch);
        if(prog_ch!=1)
            printf("\nPROGRAM\tEXECUTION\tSTOPS.");
    }while(prog_ch==1);
}
int bits(int a){
    int i, prod = 1, power = 0;
    for(i = 1; i <= a; i++){
        prod = prod*2;
        power = i;
        if(prod >= a)
            break;
    }
    return power;
}
