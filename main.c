#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int movie_size,tag_size;
int error_num;
typedef struct Movie Movie;
struct Movie
{
   int  movie_ID;
   char movie_name[100];
   char move_genre[200];
};
Movie *movie;

typedef struct TAG_Alpha TAG_Alpha;
struct TAG_Alpha
{
   int  user_ID;
   int movie_ID;
   char tag [50];
   long long timestamp ;
};
TAG_Alpha *tag_alpha;

typedef struct tag_ID tag_ID;
struct tag_ID
{
   int  user_ID;
   int movie_ID;
   char tag [50];
   long long timestamp ;
};
tag_ID *TAG_ID;

void Movie_Structure();
void Tag_Structure();
void tag_to_movie();
void movie_to_tag();
void additional_function();

void init(){
    printf("-----��ȭ, �±� �˻� ���α׷��� �����մϴ�-----\n\n");
    printf("�˻� �� �ڵ� �ϼ� ����� �����ϴµ�, ������ ������ �����Ͻÿ�(��ҹ��� ���� �����ϴ�): ");
    scanf("%d", &error_num);
    printf("\n\n\n");
    select_menu();

}

void select_menu() {
    int menu_num;
    printf("1. ��ȭ ������ ó��\n");
    printf("2. �±� ������ ó��\n");
    printf("3. tag�� ��ȭ �˻��ϱ�\n");
    printf("4. moive�� �±� �˻��ϱ�\n");
    printf("5. �ΰ� ���\n");
    printf("0. ������\n\n\n");
    printf("���ϴ� �޴��� ������: ");
    scanf("%d", &menu_num);
    printf("\n");
    if ( (menu_num < 0) || (menu_num>5) )
        printf("������ �޴��� �ش��ϴ� ���ڸ� �ٽ� Ȯ���� �ּ���.\n");
    switch (menu_num) {
        case 1: Movie_Structure(); break;
        case 2: Tag_Structure(); break;
        case 3: tag_to_movie(); break;
        case 4: movie_to_tag(); break;
    }
}


void Movie_Structure()
{
//��ȭ���� �ҷ����� ����ü�� ���� - �±�
char line[1000];
FILE *fp;
fp = fopen("movies.dat","r");
int i=0,num=0;
while (fgets(line, sizeof(line)-1, fp) != NULL)
{
   i++;
}
movie_size = i+1;
movie = (Movie *) malloc (sizeof(Movie)*(i+1));
i=0;
rewind(fp);
while (fgets(line, sizeof(line)-1, fp) != NULL)
{
   char seps[] = ":";

    char *ptr = strtok(line, seps);
    num = atoi(ptr);
    movie[i].movie_ID = num;
    ptr = strtok(NULL,"(")+1;
    strncpy(movie[i].movie_name, ptr, strlen(ptr)-1);
    ptr = strtok(NULL, seps);
    ptr = strtok(NULL,"\n")+1;
    strcpy(movie[i].move_genre,ptr);
    i++;
}
fclose(fp);
select_menu();
}


void Tag_Structure()
{
//�±����� �ҷ����� ����ü�� ���� - �±�
char line2[1000];
FILE *fp;
fp = fopen("tags.dat","r");
int i=0,u_num=0, m_num=0;
long long t_num;
while (fgets(line2, sizeof(line2)-1, fp) != NULL)
{
   i++;
}
tag_size = i+1;
tag_alpha = (TAG_Alpha *) malloc (sizeof(TAG_Alpha)*(i+1));
i=0;
rewind(fp);
while (fgets(line2, sizeof(line2)-1, fp) != NULL)
{
    char seps[] = ":";
    char *ptr = strtok(line2, seps);
    u_num = atoi(ptr);
    tag_alpha[i].user_ID = u_num;
    ptr = strtok(NULL,seps);
    m_num = atoi(ptr);
    tag_alpha[i].movie_ID = m_num;
    ptr = strtok(NULL,":");
    strcpy(tag_alpha[i].tag, ptr);
    ptr = strtok(NULL, "\n")+1;
    t_num = atoll(ptr);
    tag_alpha[i].timestamp = t_num;
    i++;
}
fclose(fp);
select_menu();
}

int additional_function1(char* search_name, char* real_name){
    int sum = 0;
    for(int i=0; i<strlen(search_name); i++){
        if(search_name[i]==real_name[i]){
            sum++;
        }
    }
    return sum;

}


int* tag_to_ID(char* tag_name, TAG_Alpha* tag_alpha){
    int i=0;
    int j=0;

    int temp_ID_num[1000];

    while(i<tag_size){
        if(strcmp(tag_name, tag_alpha[i].tag)==0){
            temp_ID_num[j] = tag_alpha[i].movie_ID;
            j++;
            i++;
        }
        else{
            if(strlen(tag_alpha[i].tag)>error_num){
                int same_num = additional_function1(tag_name, tag_alpha[i].tag);
                if(strlen(tag_alpha[i].tag) - same_num <= error_num){
                    temp_ID_num[j] = tag_alpha[i].movie_ID;
                    j++;
                }
            }
            i++;
        }
    }
    int *tag_ID_num = (int*)malloc(sizeof(int)*j);

    memcpy(tag_ID_num, temp_ID_num, j*sizeof(int));

    return tag_ID_num;
}
int tag_to_size(char* tag_name, TAG_Alpha* tag_alpha){
    int i=0;
    int j=0;

    int temp_ID_num[1000];

    while(i<tag_size){
        if(stricmp(tag_name, tag_alpha[i].tag)==0){
            temp_ID_num[j] = tag_alpha[i].movie_ID;
            j++;
            i++;
        }
        else{
            if(strlen(tag_alpha[i].tag)>error_num){
                int same_num = additional_function1(tag_name, tag_alpha[i].tag);
                if(strlen(tag_name) - same_num <= error_num){
                    temp_ID_num[j] = tag_alpha[i].movie_ID;
                    j++;
                }
            }
            i++;
        }
    }
    return j;
}
void tag_to_movie(){
//�±׷� ��ȭ �˻� - ����
    char input_tag[30];
    printf("�±� �̸��� �Է��ϼ���: ");
    scanf(" %[^\n]s", input_tag);
    printf("\n\n");
    int tag_ID_size = tag_to_size(input_tag, tag_alpha);
    if(tag_ID_size == 0){
        printf("�ش� �±װ� �����ϴ�. �ٽ� �Է��ϼ���: \n\n");
        select_menu();
    }
    int* temp_search_tag_ID;
    int* search_tag_ID;

    temp_search_tag_ID = (int*)malloc(sizeof(int)*tag_ID_size);
    temp_search_tag_ID = tag_to_ID(input_tag, tag_alpha);

    search_tag_ID = (int*)malloc(sizeof(int)*tag_ID_size);
    memcpy(search_tag_ID, temp_search_tag_ID, tag_ID_size*sizeof(int));


   // int* search_tag_ID = (int*)malloc(sizeof(int)*tag_ID_size);
   // search_tag_ID = tag_to_ID(input_tag, tag_alpha);
   // for(int k =0; k<tag_ID_size; k++){
     //   search_tag_ID[k] = tag_to_ID(input_tag, tag_alpha)[k];
       // printf("%d\n", search_tag_ID[k]);
   // }
    for(int j=0; j<tag_ID_size; j++){
        for(int i=0; i<movie_size; i++){

            if(search_tag_ID[j] == movie[i].movie_ID){
                printf("��ȭ �̸�: %s\t", &movie[i].movie_name);
                printf("��ȭ ID: %d\t", movie[i].movie_ID);
                printf("��ȭ �帣: %s\n\n\n", &movie[i].move_genre);
            }
        }
    }
    free(search_tag_ID);
    select_menu();

}


int name_to_ID(char* movie_name, Movie* movie){
   int i = 0;
   while (i<movie_size) {
      if (stricmp(movie_name, movie[i].movie_name)==0){
         //�ΰ����1
         return movie[i].movie_ID;
      }
      else {
         if(strlen(movie[i].movie_name)>error_num){
             int same_num = additional_function1(movie_name, movie[i].movie_name);
             if(strlen(movie_name) - same_num <= error_num){
                return movie[i].movie_ID;
             }
         }
         i++;
      }
   }
   return -1;
}

void movie_to_tag(){
//��ȭ�� �±� �˻� - ����
    int search_movie_ID;
    char input_movie_name[30];
    printf("��ȭ �̸��� �Է��ϼ���: ");
    scanf(" %[^\n]s", input_movie_name);
    printf("\n\n");
    search_movie_ID = name_to_ID(input_movie_name, movie);
    if(search_movie_ID == -1){
        printf("�ش� ��ȭ�� �����ϴ�. �ٽ� �Է��ϼ���: \n\n");
        select_menu();
    }
    int i=0;
    for(; i<tag_size; i++){
       if(search_movie_ID == tag_alpha[i].movie_ID){

           printf("�±� �̸�: %s\t", &tag_alpha[i].tag);
           printf("�±� ���� ID: %d\t", tag_alpha[i].user_ID);
           printf("�±� ��ȭ ID: %d\t", tag_alpha[i].movie_ID);
           printf("�±� �ð�: %u\n\n\n", &tag_alpha[i].timestamp);
       }
    }
    select_menu();

}







int main()
{
    init();
    free(movie);
    free(tag_alpha);
    return 0;
}
