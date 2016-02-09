#include <stdio.h>
#include <stdlib.h>

// source for mergesort algorithm: http://www.thelearningpoint.net/computer-science/arrays-and-sorting-merge-sort--with-c-program-source-code

typedef struct  listnode{
	int num;
	struct listnode *next;

}list;


typedef struct node* Node;
struct node {
	int comb_arr[1001];
	int mes_arr[44];
	int count; // saves how many zeros comb_arr has
	int i;     // saves the combination from which the node was created so as to be able to find each children 
		   // it's needed when we 'll search **forbidden array
    	Node next;
    	Node prev;
};

struct doubly_linked_list {
    Node head;
    Node tail;
};
typedef struct doubly_linked_list* queue;


//****GLOBAL VARIABLES*****

int N,M;
int flag=0; 

//****END OF GLOBAL VARIABLES****


//*****MERGESORT******

/* Merge functions merges the two sorted parts. Sorted parts will be from [left, mid] and [mid+1, right].
 */
void Merge(int *array,list *forbidden[], int left, int mid, int right)
{
        /*We need a Temporary array to store the new sorted part*/

	int *tempArray;
	list **tempArray2;
	tempArray = malloc(M*sizeof(int));
	tempArray2 = malloc(M*sizeof(list));

        int pos=0,lpos = left,rpos = mid + 1;
        while(lpos <= mid && rpos <= right)
        {
                if(array[lpos] < array[rpos])
                {
                        tempArray[pos] = array[lpos];
			tempArray2[pos] = forbidden[lpos];
			lpos++;
                }
                else
                {
                        tempArray[pos] = array[rpos];
			tempArray2[pos] = forbidden[rpos];
			rpos++;
                }
		pos++;
        }
        while(lpos <= mid){
		 tempArray[pos] = array[lpos];
		tempArray2[pos] = forbidden[lpos];
		pos++;
		lpos++;
	}
        while(rpos <= right){
		tempArray[pos] = array[rpos];
		tempArray2[pos] = forbidden[rpos];
		pos++;
		rpos++;
	}
        int iter;
        /* Copy back the sorted array to the original array */
        for(iter = 0;iter < pos; iter++)
        {
                array[iter+left] = tempArray[iter];
		forbidden[iter+left] = tempArray2[iter];
        }
	free(tempArray);
	free(tempArray2);
        return;
}

void MergeSort(int *array,list *forbidden[], int left, int right)
{
        int mid = (left+right)/2;
        /* We have to sort only when left<right because when left=right it is anyhow sorted*/
        if(left<right)
        {
                /* Sort the left part */
                MergeSort(array,forbidden,left,mid);
                /* Sort the right part */
                MergeSort(array,forbidden,mid+1,right);
                /* Merge the two sorted parts */
                Merge(array,forbidden,left,mid,right);
        }
}



//****** BASIC FUNCTIONS RELEVANT TO QUEUE AND ITS NODES*********

int isEmpty(queue q) {
    return q->head==NULL;
}


queue createQ() {
	queue q;
	q = malloc(sizeof(queue)); 
	q->head = NULL;
	q->tail = NULL;
	return q;
}

void push(queue q,Node new) {
    if (isEmpty(q)) {
        q->head = new;
        q->tail = new;
        return; 
    }
    new->next = q->head;
    q->head->prev = new;
    q->head = new;
}


void pop(queue q) {
	if (isEmpty(q)) return;
	else if (q->head == q->tail) {
		free(q->head);
	        q->head = NULL;
	        q->tail = NULL;
	        return;
	    }
	Node temp = q->tail;
	q->tail = q->tail->prev;
	if (q->tail != NULL) {
		q->tail->next = NULL;
		free(temp);
	}	
}
	

void deleteFirst(queue q) {
    if (isEmpty(q)) return;
    else if (q->head == q->tail) {
        free(q->head);
        q->head = NULL;
        q->tail = NULL;
        return;
    }
    Node temp = q->head;
    q->head = q->head->next;
    if (q->head != NULL) 
        q->head->prev = NULL;
    free(temp);
}


void destroyQ(queue q) {
    while (!isEmpty(q))
        deleteFirst(q);
    free(q);
}




Node createNode(int mes_arr[], int comb_arr[], int count, int i) {
	
	int j;

	Node new = malloc(sizeof(*new));
	new->count=count;
	new->i=i;
	for (j=1;j<=N;j++) 
		new->mes_arr[j]= mes_arr[j];
	for (j=0;j<M;j++) 
		new->comb_arr[j]= comb_arr[j];
		
	new->next = NULL;
	new->prev = NULL;
	return new;
}

//*****END OF BESIC FUNCTIONS RELEVANT TO QUEUE******


// create list node and put it at the end of the list
list * createlist(int forbid, list* first) {

	list * new;
	new = malloc(sizeof(*new));
  	new->num = forbid;
  	new->next = NULL;


	if (first == NULL)
	{
       		first = new;
	}
	else
	{
	        list * temp = first;
	        while (temp->next != NULL)
	            temp = temp->next;
	        temp->next = new;
	}
	return first;
}



int main(int argc,char *argv[]) {

	int i,j,k,forbid,*mes_arr,*comb_arr, count=0;
	queue q;
	Node nd,copy;
	list *apagoreumeno, *start;

	FILE *fp;

	fp=fopen(argv[1],"r");

	if (fp == NULL)
	{
		printf("Could not open command file: %s",argv[1]);
	        return 0;
	}


	fscanf(fp,"%d ",&N);
	fscanf(fp,"%d",&M);


	mes_arr=malloc((N+2)*sizeof(int));
	comb_arr=malloc((M+1)*sizeof(int));
	

	 list *first;
	first = malloc(sizeof(list));

	// create an array of lists. each list has the elements of the forbidden combination 
	//Each array element has one forbidden combination 
	list **forbidden;
	forbidden = malloc((M+2)*(sizeof(*forbidden)));
	int *howmany = malloc((M+2)*(sizeof(int)));

	for (i=0;i<M; i++)
	{
		first=NULL;
		fscanf(fp,"%d ",&howmany[i]);
		forbidden[i] = malloc(howmany[i]*sizeof(*forbidden[i]));
		for (j=1;j<=howmany[i]; j++) 
		{
			fscanf(fp,"%d ",&forbid);
			first = createlist(forbid,first);
		}
		forbidden[i]=first;

	}	

	fclose(fp);
	//END of reading


	MergeSort(howmany,forbidden,0,M-1); //mergesort howmany[] and *forbidden[]


	for (i=1;i<=N; i++) {
		mes_arr[i]=1;
	}
	
	for (i=0;i<M; i++) {
		comb_arr[i]=1;
	}

	q=createQ();
	nd= createNode(mes_arr, comb_arr,count,0);
	push(q,nd); //insert father node to list
	free(mes_arr);
	free(comb_arr);

	
	while (flag==0) {
		if (q->tail->comb_arr[q->tail->i]==1) {
			apagoreumeno = forbidden[q->tail->i];
			for (j=0;j<howmany[q->tail->i]; j++) {
				//create a copy of the father node
				copy=createNode(q->tail->mes_arr,q->tail->comb_arr,q->tail->count,q->tail->i+1);

				for (k=0;k<M;k++) {  //start searching	
						start = forbidden[k];				
						while ((start!=NULL) && (copy->comb_arr[k]==1)) { 
							if (start->num==apagoreumeno->num) {
								copy->comb_arr[k]=0;
								copy->count++;							
							}
							start=start->next;
						}
				}		//finish searching

				copy->mes_arr[apagoreumeno->num]=0;

				if (copy->count==M) {
					flag=0;
					for (i=1;i<=N; i++) {
						if (copy->mes_arr[i]==1) {
							printf("%d ",i);
						}
						
					}
					printf("\n");
					destroyQ(q);
					free(forbidden);
					free(howmany);
					return 0;
				}
				else {
					push(q,copy);
					apagoreumeno=apagoreumeno->next;			
				}	
			}
			pop(q);		
		}
		else 
			q->tail->i++;
	}
					
	destroyQ(q);
	free(forbidden);
	free(howmany);		
				
	return 0;		
}
