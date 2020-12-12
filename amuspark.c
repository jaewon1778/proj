#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 100


typedef struct rides {
	char ride[SIZE];
	int person;
	int time;
	struct rides* next;
}rides_t;


int pperson;
void PutP(int *pperson);
int menu();
void AddR(rides_t** list_head, void(*func)(rides_t*),rides_t* (*func2)(rides_t*,char*));
void DelR(rides_t** list_head, void (*func)(rides_t*),rides_t* (*func2)(rides_t*,char*));
void LookR(rides_t* list_head);
rides_t* open(rides_t* list_head);
void ShowR1(rides_t* list_head);
void SearchR(rides_t* list_head, void(*func)(rides_t*),rides_t* (*func2)(rides_t*,char*));
rides_t* Isthere(rides_t* list_head,char ride[SIZE]);
void ModR(rides_t* list_head, void(*func)(rides_t*),rides_t* (*func2)(rides_t*,char*));
void WaitR(rides_t* list_head, void(*func)(rides_t*),rides_t* (*func2)(rides_t*,char*));
int Cul(int num,int person,int time,int pperson);
void SaveR(rides_t* list_head);

int main()
{
	rides_t* list_head=NULL;
	FILE* fp=NULL;
	list_head=open(list_head);
	PutP(&pperson);

	while(1){
	switch(menu()){
		case 0:
			SaveR(list_head);
			printf("프로그램을 종료합니다.\n");
			printf("=========================\n");
			return 0;
		case 1:
			AddR(&list_head,ShowR1,Isthere);
			break;			
		case 2:
			ModR(list_head,ShowR1,Isthere);
			break;			

		case 3:
			DelR(&list_head,ShowR1,Isthere);
			break;			

		case 4:
			LookR(list_head);
			break;
		case 5:
			SearchR(list_head,ShowR1,Isthere);
			break;			

		case 6:
			WaitR(list_head,ShowR1,Isthere);
			break;			
		case 7:
			PutP(&pperson);
			break;
		default:
			printf("잘못된 입력입니다.\n");
			break;
		}
	}

	return 0;
}

void PutP(int *pperson){
	printf("놀이기구 탈사람의 수를 입력하세요: ");
	scanf("%d",pperson);
}

rides_t* open(rides_t* list_head){
	rides_t* new_node;
	FILE* fp=fopen("rides.txt","r+");
	if(fp==NULL){
		printf("파일을 열 수 없습니다.\n");
		return NULL;
	}
	while(1){
		new_node=(rides_t*) malloc (sizeof(rides_t));
		if(feof(fp)!=0)
			break;
		fscanf(fp,"%s %d %d\n", new_node->ride,&new_node->person,&new_node->time);
		new_node->next=list_head;
		list_head=new_node;
	}
	fclose(fp);
	return list_head;
}

void SaveR(rides_t* list_head){
	rides_t* tmp;
	FILE* fp=fopen("rides.txt","w");
	if(fp==NULL){
		printf("파일을 열 수 없습니다.\n");
		return;
	}
	while(list_head!=NULL){
		tmp=list_head;
		fprintf(fp,"%s %d %d\n",tmp->ride,tmp->person,tmp->time);
		list_head=list_head->next;
		free(tmp);
	}
	fclose(fp);
	printf("파일을 저장했습니다.\n");
}

int menu(){
	int cho;
	printf("=========================\n");
	printf("현재 인원: %d\n",pperson);
	printf("-------------------------\n");
	printf("1.놀이기구 추가\n");
	printf("2.놀이기구 수정\n");
	printf("3.놀이기구 삭제\n");
	printf("4.놀이기구 조회\n");
	printf("5.놀이기구 검색\n");
	printf("6.놀이기구 대기시간 조회\n");
	printf("7.현재 인원 변경\n");
	printf("0.저장 후 종료\n");
	printf("-------------------------\n");
	printf("번호를 선택해주세요: ");
	scanf("%d",&cho);
	printf("=========================\n");
	
	return cho;
}


void LookR(rides_t* list_head){
	printf("놀이기구\t 1회수용인원\t 1회운행시간\n");
	while(list_head != NULL){
		if (strlen(list_head->ride) < 12)
			printf("%s\t\t %d명\t\t %d분\n",list_head->ride,list_head->person,list_head->time);
		else
			printf("%s\t %d명\t\t %d분\n",list_head->ride,list_head->person,list_head->time);
		list_head = list_head->next;
	}
}

void AddR(rides_t** list_head, void(*func)(rides_t*),rides_t* (*func2)(rides_t*,char*)){
	char ride[SIZE];
	int person, time;
	rides_t* new_node;

	printf("놀이기구 이름을 입력: ");
	scanf("%s",ride);
	rides_t* tmp=func2(*list_head, ride);	
	if(tmp==NULL){
		printf("1회 수용 인원을 입력: ");
		scanf("%d",&person);
		printf("1회 운행 시간을 입력: ");
		scanf("%d",&time);
		new_node = (rides_t*) malloc (sizeof(rides_t));
		strcpy(new_node->ride, ride);
		new_node->person = person;
		new_node->time = time;

		new_node->next=*list_head;
		*list_head=new_node;
	
		printf("=========================\n");
		func(new_node);
		printf("위와 같이 저장되었습니다.\n");
	}
	else{
		printf("=========================\n");
		printf("중복된 놀이기구입니다.\n");
	}
}

void DelR(rides_t** list_head, void (*func)(rides_t*),rides_t* (*func2)(rides_t*,char*)){
	
	char ride[SIZE];
	int ans;
	rides_t* imsi=*list_head;

	printf("삭제할 놀이기구의 이름을 입력: ");
	scanf("%s",ride);
	rides_t* tmp=func2(*list_head,ride);
	rides_t* pre;
	printf("=========================\n");
	if (tmp!=NULL){
		func(tmp);
		printf("다음의 놀이기구를 삭제할 것입니까?(1.Yes 2.NO): ");
		scanf("%d",&ans);
		if(ans==1){
			if(*list_head==tmp){
				*list_head=(*list_head)->next;
				free(imsi);
				return;
			}
			else{
			while(1){
				if((*list_head)==tmp){
					pre->next=(*list_head)->next;
					free(*list_head);
					printf("삭제 되었습니다.\n");
					*list_head=imsi;

					return;
				}
				pre=*list_head;
				*list_head=(*list_head)->next;
			}
			}
		}
		else if(ans==2){
			printf("놀이기구 삭제를 취소합니다.\n");
		}
		else{
			printf("잘못된 입력입니다.\n놀이기구 삭제를 취소합니다.\n");
		}
	}
	else
		printf("해당 놀이기구가 없습니다.\n");
}	
	


void ShowR1(rides_t* tmp){
	if (strlen(tmp->ride) < 12){
		printf("놀이기구\t 1회수용인원\t 1회운행시간\n");
		printf("%s\t\t %d명\t\t %d분\n",tmp->ride,tmp->person,tmp->time);
	}
	else{
		printf("놀이기구\t 1회수용인원\t 1회운행시간\n");
		printf("%s\t %d명\t\t %d분\n",tmp->ride,tmp->person,tmp->time);
	}
		
}

void SearchR(rides_t* list_head, void(*func)(rides_t*),rides_t* (*func2)(rides_t*,char*)){
	char ride[SIZE];

	printf("검색할 놀이기구의 이름을 입력하세요: ");
	scanf("%s",ride);
	rides_t* tmp=func2(list_head, ride);
	printf("=========================\n");
	if (tmp!=NULL)
		func(tmp);
	else
		printf("검색된 내용이 없습니다.\n");
}

rides_t* Isthere(rides_t* list_head,char ride[SIZE]){
	while(list_head != NULL){
		if (strcmp(list_head->ride,ride)==0) 
			return list_head;
	list_head = list_head->next;
	}	
	return NULL;
}

void ModR(rides_t* list_head, void(*func)(rides_t*),rides_t* (*func2)(rides_t*,char*)){
	char ride[SIZE],modc[SIZE];
	int num,modi;

	printf("수정할 놀이기구의 이름을 입력하세요: ");
	scanf("%s",ride);
	rides_t* tmp=func2(list_head, ride);
	printf("=========================\n");
	if(tmp!=NULL){
		printf("%s의 현재 정보\n",ride);
		func(tmp);
		printf("=========================\n");
		printf("수정할 내용을 선택하세요(1.이름 2.인원 3.시간): ");
		scanf("%d",&num);
		switch(num){
			case 1:
				printf("수정할 내용을 입력하세요: ");
				scanf("%s",modc);
				strcpy(tmp->ride,modc);
				break;
			case 2:
				printf("수정할 내용을 입력하세요: ");
				scanf("%d",&modi);
				tmp->person=modi;
				break;
			case 3:
				printf("수정할 내용을 입력하세요: ");
				scanf("%d",&modi);
				tmp->time=modi;
				break;
			default:
				printf("잘못 입력하셨습니다.\n");
				break;
		printf("=========================\n");
		printf("다음과 같이 수정되었습니다.\n");
		func(tmp);

		}
		
	}
	else
		printf("해당 놀이기구가 없습니다.\n");
}

void WaitR(rides_t* list_head, void(*func)(rides_t*),rides_t* (*func2)(rides_t*,char*)){
	char ride[SIZE];
	int num,ans,waitt;
	
	printf("현재 추가된 놀이기구\n");
	LookR(list_head);
	printf("=========================\n");
	printf("대기시간을 확인할 놀이기구의 이름을 입력하세요: ");
	scanf("%s",ride);
	rides_t* tmp = func2(list_head,ride);
	if(tmp!=NULL){
		printf("%s의 현재 정보\n",ride);
		func(tmp);
		printf("현재 인원: %d명\n",pperson);
		printf("=========================\n");
		if (pperson/tmp->person==1){
			while(1){
				printf("현재 인원이 1회수용인원보다 많습니다.\n인원을 나누시고 타시겠습니까?(1.Yes 2.No): ");
				scanf("%d",&ans);
				if(ans==1){
					printf("대기인원을 입력하세요: ");
					scanf("%d",&num);
					waitt=Cul(num,tmp->person,tmp->time,pperson%tmp->person);
					printf("=========================\n");
					printf("첫번째 팀의 대기시간: %d분\n두번째 팀의 대기시간: %d분\n",waitt,waitt+tmp->time);
					break;	
				}
				if(ans==2){
					printf("대기시간 조회를 종료합니다.\n");
					break;
				}
				else{
					printf("잘못된 입력입니다.\n");
					break;
				}
			}
		}
		else if(pperson/tmp->person>=2){
			printf("인원이 너무 많습니다.\n");
			printf("대기시간 조회를 종료합니다.\n");
		}
		else{
			printf("대기인원을 입력하세요: ");
			scanf("%d",&num);
			printf("=========================\n");
			printf("대기시간: %d분\n",Cul(num,tmp->person,tmp->time,pperson));
		}
	}
	else
		printf("해당 놀이기구가 없습니다.\n");
		
}

int Cul(int num,int person,int time,int pperson){

	int a,b,d;
	
	a=num/person;
	b=(num+pperson)/person;
	d=(num+pperson)%person;

	if(a==b)
		return a*time;
	else{
		if(d==0)
			return a*time;
		else
			return b*time;
	}
}


