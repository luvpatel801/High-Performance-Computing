/*
 * Author 1 : Luv Patel (201501459)
 * Author 2 : Harshal Khodifad (201501461)
**/

/*
To run for all cases: check README.txt file


To run for singal run:
compile: 	gcc sudoku-omp.c -fopenmp -lm
run:		./a.out filename threads

OUTPUT:
	solved sudoku
	serial time
	parallel time
	speed-up
*/


#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

/* 
 * Global variable declarations
 * Structure definations 
 */

typedef struct matrix {
	short **data;
	short **fixed;
} MATRIX;

struct element {
	MATRIX mat;
	short i, j;
	struct element *next;
};

typedef struct element list;

int l;
int SIZE;
FILE *inputMatrix;
MATRIX solution;
list *head;
list *tail;


/*
print_sudoku(): prints a MATRIX to the  output
 */
void print_sudoku(MATRIX *matrix) 
{
	int i,j;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			printf("%2d ", matrix->data[i][j]);
		}
		printf("\n");
	}
}


/*
read_sudoku(): Reads matrix from txt file
The first line is n of n^2 x n^2 sudoku.
like: for 9x9 sudoku n=3
 */
MATRIX read_sudoku(char *filename) 
{
	int i,j;  
	MATRIX matrix;  
	int element_int;

	inputMatrix = fopen(filename, "rt");

	fscanf(inputMatrix, "%d", &element_int);
	l = element_int;
	SIZE = l*l;

	// allocate memory

	matrix.fixed = (short**) malloc(SIZE * sizeof(short*));
	for (i=0;i<SIZE;i++)
		matrix.fixed[i] = (short*) malloc (SIZE * sizeof (short));




	matrix.data = (short**)malloc(SIZE*sizeof(short*));  
	for (i=0;i<SIZE;i++)
		matrix.data[i] = (short*) malloc (SIZE * sizeof (short));



	// initializing fixed matrix with 0s
	for (i=0; i<SIZE; i++) {
		for (j=0; j<SIZE; j++) {     
			matrix.fixed[i][j] = 0;
		}
	}

	for(i = 0; i < SIZE; i++) {
		for(j = 0; j < SIZE; j++){
			fscanf(inputMatrix, "%d", &element_int);
			matrix.data[i][j] = element_int;
			if (matrix.data[i][j] != 0)
				matrix.fixed[i][j] = 1;
		}
	}

	fclose(inputMatrix);
	return matrix;
}

/*
possible(): Checks if the value at (i_row, j_col) in the sudoku is valid or not. Returns 1 if it is possible and 0 if it is not
 */
short possible(MATRIX matrix, short i_row, short j_col) 
{

	short row, column;
	short value = matrix.data[i_row][j_col];

	// check same column
	for (row = 0; row < SIZE; row++) {
		if (matrix.data[row][j_col] == 0)
			continue;

		if ((i_row != row) && 
				(matrix.data[row][j_col] == value)) 
			return 0;
	}

	// check same row
	for (column = 0; column < SIZE; column++) {
		if (matrix.data[i_row][column] == 0)
			continue;

		if (j_col != column && matrix.data[i_row][column] == value)
			return 0;
	}

	// check group
	short igroup = (i_row / l) * l;
	short jgroup = (j_col / l) * l;
	for (row = igroup; row < igroup+l; row++) {
		for (column = jgroup; column < jgroup+l; column++) {
			if (matrix.data[row][column] == 0)
				continue;

			if ((i_row != row) &&
					(j_col != column) &&
					(matrix.data[row][column] == value)) {
				return 0;
			}
		}
	}

	return 1;
}

/*
go_backward(): Moves the pointer in backward direction to a non-fixed value.
 */
void go_backward(MATRIX* matrix, short* iPointer, short* jPointer)
{
	do {
		if (*jPointer == 0 && *iPointer > 0) {
			*jPointer = SIZE - 1;
			(*iPointer)--;
		} else
			(*jPointer)--;
	} while (*jPointer >= 0 && (*matrix).fixed[*iPointer][*jPointer] == 1);
}


/*
go_forward(): Moves the pointer in forward direction to a non-fixed value.
 */
void go_forward(MATRIX* matrix, short* iPointer, short* jPointer)
{

	do{
		if(*jPointer < SIZE-1)
			(*jPointer)++;
		else {
			*jPointer = 0;
			(*iPointer)++;
		}
	} while (*iPointer < SIZE && (*matrix).fixed[*iPointer][*jPointer]);
}

/*
free_node(): Deallocates memory for the list node  by calling inbuilt free function. 
 */
void free_node(list *node) 
{
	int i;
	for (i = 0; i < SIZE; i++) {
		free(node->mat.data[i]);
		free(node->mat.fixed[i]);
	}
	free(node->mat.data);
	free(node->mat.fixed);
	free(node);
}


/*
create_node(): creates an list for the matrix and returns it 
 */
list* create_node(MATRIX matrix, short i, short j)
{
	list * curr = (list *)malloc(sizeof(list));
	int m;
	short x, y;

	/* allocate memory for new copy */
	curr->mat.data = (short**)malloc(SIZE*sizeof(short*));
	for (m=0;m<SIZE;m++)
		curr->mat.data[m] = (short*) malloc (SIZE * sizeof (short));

	curr->mat.fixed = (short**) malloc(SIZE * sizeof(short*));
	for (m=0;m<SIZE;m++)
		curr->mat.fixed[m] = (short*) malloc (SIZE * sizeof (short));


	//copy matrix 
	for(x = 0; x < SIZE; x++){
		for(y = 0; y < SIZE; y++){
			curr->mat.data[x][y] = matrix.data[x][y];
			curr->mat.fixed[x][y] = matrix.fixed[x][y]; 
		}
	}


	curr->i = i;
	curr->j = j;
	curr->next = NULL;

	return curr;
}

/*
push_node(): adds an list to the tail of the linked list 
 */
void push_node(list* newItem)
{

	if(head == NULL){
		head = newItem;
		tail = newItem;
	}
	else {
		tail->next = newItem;
		tail = newItem;
	}
}

/*
 * pop_node(): removes an list from the head of the linked list and returns it
 */
list* pop_node()
{
	list* result = NULL;
	if(head != NULL){
		result = head;
		head = result->next;
		if(head == NULL){
			tail = NULL;
		}
	}
	return result;
}

/*
 * create_list(): creates a list of possible sudoku with filling some first blanks upto total SIZE number
 */
void create_list(MATRIX* matrix)
{

	short i = 0;
	short j = 0;

	if ((*matrix).fixed[i][j] == 1)
		go_forward(matrix, &i, &j);

	short num=0;

	list* current = NULL;

	while(1) {
		((*matrix).data[i][j])++; 

		//adding the matrix to the list only if the value is possible
		if (matrix->data[i][j] <= SIZE && possible(*matrix, i, j) == 1) {
			list* newPath = create_node(*matrix, i, j);
			push_node(newPath);
			num++;
		} else if(matrix->data[i][j] > SIZE) {
			if(current != NULL){
				free_node(current);
			}

			if(num >= SIZE){
				break;
			}

			list* current = pop_node();

			if(current == NULL){
				break;
			}

			matrix = &(current->mat);
			i = current->i;
			j = current->j;

			if(i == SIZE-1 && j == SIZE-1){
				push_node(current);
				break;
			}

			num--;

			go_forward(matrix, &i, &j);
		}
	}

	if(current != NULL){
		free_node(current);
	}
}

/*
 * solve_parallel(): In this function threads will take matrix (sudoku) from list created by function create_list()
 * and then executes in parallel as solve_serial() function
 */
short solve_parallel(MATRIX matrix) {

	head = NULL;
	tail = NULL;

	create_list(&matrix); 
	short found = 0;
	short i, j;
	list* current;
	int level;

    #pragma omp parallel shared(found) private(i,j, current, level)
	{
        #pragma omp critical
		current = pop_node();
		while(current != NULL && found == 0){
			MATRIX currMat = current->mat;
			i = current->i;
			j = current->j;
			go_forward(&currMat, &i, &j);
			level = 1;
			//Found ==0 is important as if found ==1 then exit
			while (level > 0 && i < SIZE && found == 0) {
				if (currMat.data[i][j] < SIZE) {    
					// increase cell value, and check if new value is possible
					currMat.data[i][j]++;
					if (possible(currMat, i, j) == 1) {
						go_forward(&currMat, &i, &j);
						level++;
					}
				}
				else {
					// goes back to the previous non-fixed cell
					currMat.data[i][j] = 0;
					go_backward(&currMat, &i, &j);
					level--;
				}
			}

			if(i == SIZE){
				found = 1;
				solution = currMat;
				continue;
			}
			free(current);
            #pragma omp critical
			current = pop_node();
		}
	}  // End of parallel block  

	return found;
}

/*
 * solve_serial(): Working explained below


	This is the serial implementation of our code as explained in our report but the summary of how the code actually works is as follows:
		The algorithm uses recursive calls on a test-and-backtrack approach. All the cells of the board will be visited.
1.	Upon arriving, if the cell is not empty, it is skipped. Otherwise, a temporary value is assigned from 1 to 9. In figure 2, we can observe that the first cell (0,0) got skipped and that the value of ‘1’ has been assigned to the next cell (0,1)  

 MATRIX IS 
			1 1 0	0 0 0	0 0 2 
			0 9 0	4 0 0	0 5 0	
			0 0 6	0 0	0	7 0 0

			0 5 0	9 0 3	0 0 0
			0 0 0	0 7 0	0 0	0
			0 0 0	8 5 0	0 4	0

			7 0 0 	0 0 0	6 0 0
			0 3 0	0 0	9	0 8 0
			0 0 2   0 0 0	0 0 0

TESTING THE LEGALITY OF 1 at (0,1)

2.	Afterwards, a test is performed to see if the attempted value is allowed there. By scanning the 3 dimensions of neighbors, the new value is compared to all the elements contained in its row, its column and its sub square. If the same element is encountered, the next value is tested and the algorithm repeats the test. If all the values have been exhausted, the algorithm backtracks to the previous cell.
3.	This process is repeated until the program finds an element that could potentially exist at that location 
 

 MATRIX IS 
			1 3 0	0 0 0	0 0 2 
			0 9 0	4 0 0	0 5 0	
			0 0 6	0 0	0	7 0 0

			0 5 0	9 0 3	0 0 0
			0 0 0	0 7 0	0 0	0
			0 0 0	8 5 0	0 4	0

			7 0 0 	0 0 0	6 0 0
			0 3 0	0 0	9	0 8 0
			0 0 2   0 0 0	0 0 0

 ‘3’ is the first ‘legal’ value we can leave at position (0,1) before moving on to the next position
4.	 Once this condition is satisfied, the function is recursively called to the next location. To optimize the software, when the function is called a second time, the first element it looks at is the previous element incremented by 1. For example here, there since we just guessed ‘3 to be at location (0,1), the algorithm will guess ‘4’ the next location
5.	Once the depth of the recursion reaches 81, we know that all the cells have been visited, so if no solution was found, we backtrack one cell  making the current cell reset to 0 and keep trying all the possibilities on that one by recalling the recursion.
6.	This keeps happening until all the possibilities have been tried out. If no solution was bound in the mean time, an error message is printed on the board (for the purpose of this experiment, we know that there is a solution so it is always found sooner or later)
*/
short solve_serial(MATRIX matrix) {

	head = NULL;
	tail = NULL;

	create_list(&matrix);

	short found = 0;
	short i, j;
	list* current = pop_node();
	while(current != NULL && found == 0){
		MATRIX currMat = current->mat;

		i = current->i;
		j = current->j;

		go_forward(&currMat, &i, &j);

		int level = 1;

		while (level > 0 && i < SIZE && found == 0) {   //Found ==0 is important as if found ==1 then exit
			if (currMat.data[i][j] < SIZE) {    
				// increase cell value, and check if new value is possible
				currMat.data[i][j]++;

				if (possible(currMat, i, j) == 1) {
					go_forward(&currMat, &i, &j);
					level++;
				}

			} else {
				// goes back to the previous non-fixed cell
				currMat.data[i][j] = 0;
				go_backward(&currMat, &i, &j);
				level--;
			}
		}

		if(i == SIZE){
			found = 1;
			solution = currMat;
			continue;
		}

		free(current);

		current = pop_node();
	}
	return found;
}







int main(int argc, char* argv[]) {


	double startTime;
	double endTime;
	double serial=0,parallel;
	short hasSolution;

	if(argc!=3) {
		printf("\n\n Usage:%s filename thread\n\n", argv[0]);
		exit(1);
	}


	int num_thread=atoi(argv[2]);
	omp_set_num_threads(num_thread);


	//BEGIN SERIAL

	
		startTime = omp_get_wtime();

		MATRIX m1 = read_sudoku(argv[1]);
		//sending the input matrix to the solve_serial method which would return 1 if a solution is found
		hasSolution = solve_serial(m1);

		endTime = omp_get_wtime();
		serial=endTime-startTime;

		printf("SerialTime: %lf \n", serial);


		if(hasSolution == 0){
			printf("No Serial result!\n");
		}
	// END SERIAL
	

	//BEGIN PARALLEL
		
	startTime = omp_get_wtime();

	MATRIX m = read_sudoku(argv[1]);
	//sending the input matrix to the solve_parallel method which would return 1 if a solution is found
	hasSolution = solve_parallel(m);


	endTime = omp_get_wtime();
	parallel=endTime-startTime;

	printf("ParallelTime: %lf \n",parallel );


	if(hasSolution == 0){
		printf("No Parallel result!\n");
	}

	//PRINTING SPEEDUP

		double speedup=serial/parallel;
		printf("Speedup :%lf \n",speedup);
	
	//END PARALLEL
	
	
	
	//TO PRINT THE output solved sudolu to output uncomment the below line 
	printf("Solved sudoku is: \n");	print_sudoku(&solution);

	//BEGIN CLEANUP AND CLOSE

	
	//deallocating memory
	list* node = head;
	while (node != NULL) {
		list* next = node->next;
		free_node(node);
		node = next;
	}
	printf("\n");
	return 0;
}
