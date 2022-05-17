#include<stdio.h>
int count_6=0,i=1,n,ns,nl,*snake_pos,*snake_len,*ladder_pos,*ladder_len,*pos,*f;
void dice_input()
{
    if(f[i-1]==0)
        printf("Its player %d turn\n",i);
	int dice_roll;
    if(f[i-1]==0)
    {
        printf("Player %d, Enter the number on dice\n",i);
        scanf("%d",&dice_roll);
        if(dice_roll==6)
        {
            count_6++;
            if(count_6<3)
                printf("You have rolled a six, you play again!\n");
        }
        if(count_6<3)
        pos_increment(dice_roll);
        else
        {
            printf("You have given input of 3 consecutive sixes, you miss a turn!\n");
            f[i-1]=1;
        }
    }
    else
    {
        printf("Player %d is missing this turn\n",i);
        f[i-1]=0;
    }
	return;
}
void pos_increment(int d)
{
	int old_pos;
	if((pos[i-1]+d)<=100)
    {
		pos[i-1]+=d;
		old_pos=pos[i-1];
		printf("You have moved to position %d\n",pos[i-1]);
        snake(pos[i-1]);                     //function 'snake' is being called
		if(old_pos!=pos[i-1])
        {
			printf("Oops, you have landed in the mouth of a snake!!!\n");
			printf("Your position dropped down to %d\n",pos[i-1]);
		}
		else
		{
			ladder(pos[i-1]);                   //function 'ladder' is being called
			if(old_pos!=pos[i-1])
			{
				printf("Yay, you have reached the base of a ladder!!!\n");
				printf("You climbed the ladder and reached position %d\n",pos[i-1]);
			}
		}
	}
	else
		printf("You have crossed position 100,so you remain in position %d try again in your next turn\n",pos[i-1]);
    return;
}
void snake(int position)
{
    for(int j=0; j<ns; j++)
    {
        if(position == snake_pos[j])
        {
            pos[i-1] = position - snake_len[j];
            break;
        }
    }
    return;
}
void ladder(int position)
{
    for(int j=0; j<nl; j++)
    {
        if(position == ladder_pos[j])
        {
            pos[i-1] = position + ladder_len[j];
            break;
        }
    }
    return;
}
void display()
{
    printf("\n\n");
    for(int j=1;j<=n;j++)
        printf("Player %d is at %d\n",j,pos[j-1]);
    printf("\n\n");
}
int main()
{
    printf("\t\t\t\t\t\tWELCOME TO THE GAME OF SNAKES AND LADDERS\n");
    printf("RULES OF THE GAME:\n");
    printf("1. Input by user should be greater than 0 and less than 7\n");
    printf("2. If the input by the user is six, the player gets the chance to input again.If the user inputs three consecutive sixes the player will have to lose a turn \n");
    printf("3. If a snake is encountered, then the player will have to move to the tail position of the snake and if a ladder is encountered, then the player will move to the top of the ladder \n");
    printf("4. First player to reach 100 will be declared as the winner \n\n\n");
    printf("Enter number of players\n");
    scanf("%d",&n);
    pos=(int*)malloc(n*sizeof(int));
    f=(int*)malloc(n*sizeof(int));
    for(int j=0;j<n;j++)
    {
        f[j]=0;
        pos[j]=0;
    }
    FILE *f1;
    f1 = fopen("G:\snakes.txt", "r");
    fseek(f1,18,SEEK_SET);
    fscanf(f1,"%d\n",&ns);
    snake_pos=(int*)malloc(ns*sizeof(int));
    snake_len=(int*)malloc(ns*sizeof(int));
    int j;
    for(j=0;j<ns;j++)
        fscanf(f1,"%d %d\n",&snake_pos[j],&snake_len[j]);
    fclose(f1);
    FILE *f2;
    f2 = fopen("G:\ladder.txt", "r");
    fseek(f2,19,SEEK_SET);
    fscanf(f2,"%d\n",&nl);
    ladder_len=(int*)malloc(nl*sizeof(int));
    ladder_pos=(int*)malloc(nl*sizeof(int));
    for(j=0;j<nl;j++)
        fscanf(f2,"%d %d\n",&ladder_pos[j],&ladder_len[j]);
    fclose(f2);
    while(1)
    {
        dice_input();
        if(count_6==1)
            dice_input();
        if(count_6==2)
            dice_input();
        if(pos[i-1]==100)
		{
		    printf("Congratulations Player %d, you are the Winner!!\n\n\n",i);
		    printf("\t      ________\n");
            printf("\t     / ^^  ^^ \\\n");
            printf("\t    /  <>  <>  \\\n");
            printf("\t _ /            \\ _\n");
            printf("\t{ |      /\\      | }\n");
            printf("\t{_|              |_}\n");
            printf("\t   \\   \\    /   /\n");
            printf("\t    \\   \\__/   /\n");
            printf("\t     \\________/\n\n\n");
            printf("Thank you for playing, hope you had fun!!\n\n");
		    break;
		}
		i++;
        if(i>n)
		{
		    display();
		    i=1;
		}
		count_6=0;
    }
free(snake_len);
free(f);
free(pos);
free(ladder_pos);
free(ladder_len);
free(snake_pos);
return 0;
}
