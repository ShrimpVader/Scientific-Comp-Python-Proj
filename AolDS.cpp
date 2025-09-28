#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//libraries for syntax

struct trie{
	char chr;
	char desc[255];
	int word;
	struct trie *edge[128];
}*root = NULL ;
//the struct for the main structure of the trie

struct trie *newnode(char x){
	struct trie *root = (struct trie*)malloc(sizeof(struct trie));	
	root->chr = x;
	root->word = 0;
	root->desc[0] = '\0';
	for(int i=0;i < 128;i++){
		root->edge[i] = NULL;
	}	
	return root;	
}
//function for making a newnode when there are no nodes existing

void insert(struct trie *curr, char *c, char *sdesc,int *wcount){
	if(*c == '\0') {
        if(curr->word) {
        	strcpy(curr->desc, sdesc);
        	*wcount = 1;
        	printf("\nCongrats! slang word updated.\n");
		}
		else {
			curr->word = 1;
			strcpy(curr->desc, sdesc);
			printf("\nCongrats! slang word released.\n");
		}
		return;
    }
    if(curr->edge[*c] == NULL) {
        curr->edge[*c] = newnode(*c);
    }
    insert(curr->edge[*c], c + 1, sdesc, wcount);
}
//function to insert a desired slang

int find(struct trie *curr, char *c, char *sdesc) {
	if(curr == NULL){
		return 0;
	} 
	if( *c == 0 ){
		strcpy(sdesc, curr->desc);
		return curr->word;
	}else{
		return find(curr->edge[*c],c+1, sdesc);
	}
}
//function to find certain slangs
int precount = 0;
//global variable

void findPrefix(struct trie *curr, char *prefix, char *word) {
    if (curr == NULL) return;

    if (*prefix == '\0') {
        if (curr->word) {
            printf("%d. %s\n",precount+1, word);
            precount++;
        }

        for (int i = 0; i < 128; i++) {
            if (curr->edge[i] != NULL) {
                char newWord[256];
                strcpy(newWord, word);
                newWord[strlen(word)] = curr->edge[i]->chr;
                newWord[strlen(word) + 1] = '\0';
                findPrefix(curr->edge[i], prefix, newWord);
            }
        }
    } else {
        char nextChar = *prefix;
        if (curr->edge[nextChar] != NULL) {
            char newPrefix[256];
            strcpy(newPrefix, prefix + 1);
            findPrefix(curr->edge[nextChar], newPrefix, word);
        }
    }
}
	


void printAll(struct trie *curr, char allslangs[],int idx,int *wcount){
	if(curr == NULL){
		return;
	}

	if(curr->word){
		allslangs[idx] = '\0';
		printf("%d. %s\n", *wcount + 1, allslangs);
		(*wcount)++;
	}
	
	for(int i = 0; i < 128; i++){
		if(curr->edge[i] != NULL){
			allslangs[idx] = curr->edge[i]->chr;
			printAll(curr->edge[i], allslangs, idx + 1, wcount);
		}
	}
}

void menu(){
	puts("1. Release a new slang word");
	puts("2. Search a slang word");
	puts("3. View all slang words starting with a certain prefix word");
	puts("4. View all slang words");
	puts("5. Exit");
	printf(">>");
}

int validate(const char *input){
	int n = strlen(input);
	if(n < 2){
		return 0;
	}
	for(int i = 0 ; i < n; i++){
		if(input[i] == ' '){
			printf("Please enter the correct word.\n");
			return 0;
		}
	}
	return 1;
}

int dVal(const char *input){
	int count = 0;
	int n = strlen(input);
	int flag = 0;
	
	if(n <= 2){
		return 0;
	}
	for(int i = 0 ; i < n; i++){
		if(input[i] == ' '){
			if(flag){
				count++;
				flag = 0;
			}
		}else{
			flag = 1;
		}
	}
	if(flag){
		count++;
	}
	if(count <= 2){
		return 0;
	}
	return 1;
}

int main(){
	system("cls");
	int user;
	char word[255];
	int wcount = 0;
	char c[55];
	char sdesc[255];
	char allslangs[255];
	char search[101];
	int len = strlen(search);
	trie *curr = (struct trie*)malloc(sizeof(struct trie));
	root = newnode(' ');
	
	while(user != 5){
		
		menu();
		scanf("%d",&user);getchar();
		if(user == 1){
			
			do{
				
				printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
				scanf("%[^\n]",c);getchar();
			}while(!validate(c));
			
			do{
				printf("Input a new slang word description [Must be more than 2 words]: ");
				scanf(" %[^\n]", sdesc);getchar();
			}while(!dVal(sdesc));
			
			insert(root,c,sdesc,&wcount);
			wcount = 0;
			puts("Press ENTER to continue");
			getchar();
			user = 0;
			system("cls");
		}else if(user == 2){
			printf("Input a slang word to be searched [Must be more than 1 characters and contains no space]: ");
			scanf("%s", c);
			if(find(root, c, sdesc)){
				printf("Slang word: %s\n", c);
				printf("Description: %s\n",sdesc);
			}else{
				printf("There is no word \"%s\" in the dictionary\n",c);
			}
			printf("Press ENTER to continue");getchar();
			getchar();
			system("cls");
		}else if(user == 3){
			printf("Input a prefix to be searched: ");
  			scanf("%s", search);
  			printf("Words starting with prefix \"%s\":\n", search);
 			findPrefix(root, search, search);
 			precount=0;
  		  	puts("Press ENTER to continue");
  			getchar();
   			getchar();
   			system("cls");
		}else if(user == 4){
			wcount = 0;
			printf("List of all slang words in the dictionary: \n");
			printAll(root, allslangs, 0, &wcount);
			if(wcount == 0){
				printf("There is no slang word yet in the dictionary\n");
			}
			printf("Press ENTER to continue\n");
			getchar();
			system("cls");
		}else if(user == 5){
			puts("Thank you for using this program");getchar();
		}else{
			puts("Please enter a valid choice [1 - 5]\n");
		}
	}
	
	return 0;
}
