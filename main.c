#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int movie_size,tag_size;
int error_num;
char *enter = "\n";
typedef struct Movie Movie;
struct Movie
{
   int  movie_ID;
   char movie_name[100];
   char move_genre[200];
};
Movie *movie;

typedef struct TAG TAG;
struct TAG
{

   int  user_ID;
   int movie_ID;
   char tag [50];
   long long timestamp ;
};
TAG *tag;

void Movie_Structure();
void Tag_Structure();
void tag_to_movie();
void movie_to_tag();
void additional_function();
void select_menu();
void ID_Search_m();
void ID_Search_t();

void check()
{
   FILE *fp1,*fp2,*fp3,*fp4;
   fp1 = fopen("movies.dat","r");
   if(fp1 == NULL)
   {
      printf("영화 데이터 파일을 찾을 수 없습니다. 영화 파일을 프로그램이 있는 폴더에 넣은 후 실행해 주세요.\n");
      fclose(fp1);
      exit(0);
   }
   else
   fp2 = fopen("tags.dat","r");
   if(fp2 == NULL)
   {
      printf("태그 데이터 파일을 찾을 수 없습니다. 태그 파일을 프로그램이 있는 폴더에 넣은 후 실행해 주세요.\n");
      fclose(fp2);
      exit(0);
   }
   else
   fp3 = fopen("searchingrecord-tag.txt","a");
   fp4 = fopen("searchingrecord-movie.txt","a");
   fclose(fp1);
   fclose(fp2);
   fclose(fp3);
}

void init(){
    printf("-----영화, 태그 검색 프로그램을 시작합니다-----\n\n");
    printf("검색 시 자동 완성 기능을 실행하는데, 오차의 범위를 설정하시오(대소문자 구분 없습니다): ");
    scanf("%d", &error_num);
    printf("\n\n\n");
}

void select_menu() {
    int menu_num;
    printf("1. 영화 데이터 처리\n");
    printf("2. 태그 데이터 처리\n");
    printf("3. tag로 영화 검색하기\n");
    printf("4. moive로 태그 검색하기\n");
    printf("5. movie_ID로 영화 검색하기\n");
    printf("6. movie_ID로 태그 검색하기\n");
    printf("0. 나가기\n\n\n");
    printf("원하는 메뉴를 고르세요: ");
    scanf("%d", &menu_num);
    printf("\n");
    if ( (menu_num < 0) || (menu_num>6) )
    {
        printf("선택할 메뉴에 해당하는 숫자를 다시 확인해 주세요.\n\n");
      select_menu();
   }
    switch (menu_num) {
        case 1: Movie_Structure(); break;
        case 2: Tag_Structure(); break;
        case 3: tag_to_movie(); break;
        case 4: movie_to_tag(); break;
        case 5: ID_Search_m(); break;
        case 6: ID_Search_t(); break;

    }
}


void Movie_Structure()
{
//영화파일 불러오고 구조체에 저장 - 태규
char line[1000];
FILE *fp;
fp = fopen("movies.dat","r");
int i=0,num=0;
while (fgets(line, sizeof(line)-1, fp) != NULL)
{
   i++;
}
movie_size = i;
movie = (Movie *) malloc (sizeof(Movie)*i);
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
printf(" movies.dat 파일의 데이터를 구조체에 저장했습니다. \n\n");
select_menu();
}


void Tag_Structure()
{
//태그파일 불러오고 구조체에 저장 - 태규
char line2[1000];
FILE *fp;
fp = fopen("tags.dat","r");
int i=0,u_num=0, m_num=0;
long long t_num;
while (fgets(line2, sizeof(line2)-1, fp) != NULL)
{
   i++;
}
tag_size = i;
tag = (TAG *) malloc (sizeof(TAG)*(i));
i=0;
rewind(fp);
while (fgets(line2, sizeof(line2)-1, fp) != NULL)
{
    char seps[] = ":";
    char *ptr = strtok(line2, seps);
    u_num = atoi(ptr);
    tag[i].user_ID = u_num;
    ptr = strtok(NULL,seps);
    m_num = atoi(ptr);
    tag[i].movie_ID = m_num;
    ptr = strtok(NULL,":");
    strcpy(tag[i].tag, ptr);
    ptr = strtok(NULL, "\n")+1;
    t_num = atoll(ptr);
    tag[i].timestamp = t_num;
    i++;
}
fclose(fp);
printf(" tags.dat 파일의 데이터를 구조체에 저장했습니다. \n\n");
select_menu();
}

int additional_function1(char* search_name, char* real_name){
    int sum = 0;
    int i=0;
    for(; i<strlen(search_name); i++){
        if(search_name[i]==real_name[i]){
            sum++;
        }
    }
    return sum;

}


int* tag_to_ID(char* tag_name, TAG* tag){
    int i=0;
    int j=0;

    int temp_ID_num[1000];


    while(i<tag_size){


        if(stricmp(tag_name, tag[i].tag)==0){
            temp_ID_num[j] = tag[i].movie_ID;
            j++;
            i++;
        }

      else{

          if(strlen(tag[i].tag)>error_num && strlen(tag_name) == strlen(tag[i].tag)){
                int same_num = additional_function1(tag_name, tag[i].tag);
                if(strlen(tag[i].tag) - same_num <= error_num){
                    temp_ID_num[j] = tag[i].movie_ID;
                    j++;
                }
                i++;
            }
            else{
                i++;
            }
        }
    }
    int *tag_ID_num = (int*)malloc(sizeof(int)*j);

    memcpy(tag_ID_num, temp_ID_num, j*sizeof(int));

    return tag_ID_num;
}
int tag_to_size(char* tag_name, TAG* tag){
    int i=0;
    int j=0;


    while(i<tag_size){
        if(stricmp(tag_name, tag[i].tag)==0){
            j++;
            i++;
        }
        else{
            if(strlen(tag[i].tag)>error_num && strlen(tag_name) == strlen(tag[i].tag)){
                int same_num = additional_function1(tag_name, tag[i].tag);
                if(strlen(tag_name) - same_num <= error_num){
                    j++;
                }
                i++;
            }
            else{
                i++;
            }
        }
    }
    return j;
}
void tag_to_movie(){
//태그로 영화 검색 - 동재
   FILE *fp;
    char input_tag[30];
    printf("태그 이름을 입력하세요: ");
    scanf(" %[^\n]s", input_tag);
    //부가기능 2 - 태규
    fp = fopen("searchingrecord-tag.txt","a");
    fputs(input_tag,fp);
    fputs(enter,fp);
    printf("\n\n");
    int tag_ID_size = tag_to_size(input_tag, tag);
    if(tag_ID_size == 0){
        printf("해당 태그가 없습니다. 다시 입력하세요. \n\n");
    }
    int* temp_search_tag_ID;
    int* search_tag_ID;

    temp_search_tag_ID = (int*)malloc(sizeof(int)*tag_ID_size);
    temp_search_tag_ID = tag_to_ID(input_tag, tag);

    search_tag_ID = (int*)malloc(sizeof(int)*tag_ID_size);
    memcpy(search_tag_ID, temp_search_tag_ID, tag_ID_size*sizeof(int));


    int j,i;
    for(j=0; j<tag_ID_size; j++){
        for(i=0; i<movie_size; i++){

            if(search_tag_ID[j] == movie[i].movie_ID){
                printf("영화 이름: %s\t", &movie[i].movie_name);
                printf("영화 ID: %d\t", movie[i].movie_ID);
                printf("영화 장르: %s\n\n\n", &movie[i].move_genre);
            }
        }
    }
    free(search_tag_ID);
    select_menu();
   fclose(fp);
}

void ID_Search_m()
{
   int i=0,search_movie_ID;
   printf("검색할 영화의 movie_ID를 입력해 주세요 : ");
   scanf("%d",&search_movie_ID);
   printf("\n\n");
   for(;i<movie_size;i++)
   {
      if(search_movie_ID == movie[i].movie_ID){
         printf("영화 이름: %s\t", &movie[i].movie_name);
            printf("영화 ID: %d\t", movie[i].movie_ID);
            printf("영화 장르: %s\n\n\n", &movie[i].move_genre);
        }
   }
   select_menu();
}

void ID_Search_t()
{
   int i=0,search_movie_ID;
   printf("검색할 영화의 movie_ID를 입력해 주세요 : ");
   scanf("%d",&search_movie_ID);
   printf("\n\n");
   for(;i<movie_size;i++)
   {
      if(search_movie_ID == movie[i].movie_ID)
      printf("검색할 영화는 \"%s\" 입니다.\n\n",movie[i].movie_name);
   }
   for(i=0;i<tag_size;i++)
   {
      if(search_movie_ID == tag[i].movie_ID){
         printf("태그 이름: %s\t\t", &tag[i].tag);
           printf("태그 유저 ID: %d\t\t", tag[i].user_ID);
           printf("태그 영화 ID: %d\t\t", tag[i].movie_ID);
           printf("태그 시간: %u\n\n\n", &tag[i].timestamp);
        }
   }
   select_menu();
}

int name_to_ID(char* movie_name, Movie* movie){
   int i = 0;
   while (i<movie_size) {
      if (stricmp(movie_name, movie[i].movie_name)==0){
         //부가기능1
         return movie[i].movie_ID;
      }
      else {
         if(strlen(movie[i].movie_name)>error_num && strlen(movie_name) == strlen(movie[i].movie_name)){
             int same_num = additional_function1(movie_name, movie[i].movie_name);
             if(strlen(movie_name) - same_num <= error_num){
                printf("자동 완성 기능에 따라 다음 영화로 검색합니다: %s\n\n", movie[i].movie_name);
            return movie[i].movie_ID;
             }
         }
         i++;
      }
   }
   return -1;
}

void movie_to_tag(){
//영화로 태그 검색 - 동재
   FILE *fp;
    int search_movie_ID;
    char input_movie_name[30];
    printf("영화 이름을 입력하세요: ");
    scanf(" %[^\n]s", input_movie_name);
    //부가기능 2 - 태규
    fp = fopen("searchingrecord-movie.txt","a");
    fputs(input_movie_name,fp);
    fputs(enter,fp);
    printf("\n\n");
    search_movie_ID = name_to_ID(input_movie_name, movie);
    if(search_movie_ID == -1){
        printf("해당 영화가 없습니다. 다시 입력하세요. \n\n");
    }
    int i=0;
    for(; i<tag_size; i++){
       if(search_movie_ID == tag[i].movie_ID){

           printf("태그 이름: %s\t\t", &tag[i].tag);
           printf("태그 유저 ID: %d\t\t", tag[i].user_ID);
           printf("태그 영화 ID: %d\t\t", tag[i].movie_ID);
           printf("태그 시간: %u\n\n\n", &tag[i].timestamp);
       }
    }
    select_menu();
   fclose(fp);
}

int main()
{
   check();
    init();
    select_menu();
    free(movie);
    free(tag);
    return 0;
}
