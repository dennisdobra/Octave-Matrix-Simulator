/*Copyright Dobra Dennis - Stefan 313CA 2022 - 2023*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct struct_matrix struct_matrix;
struct struct_matrix {
	int rows, cols;
	int sum;
	int **data;
};

int modulo(int n)
{
	if (n >= 0)
		return n % 10007;
	n = n % 10007;
	return n + 10007;
}

void read_matrix(struct_matrix *matrix)
{
	for (int i = 0; i < matrix->rows; i++)
		for (int j = 0; j < matrix->cols; j++)
			scanf("%d", &matrix->data[i][j]);
}

void print_matrix(struct_matrix *matrix)
{
	for (int i = 0; i < matrix->rows; i++) {
		for (int j = 0; j < matrix->cols; j++)
			printf("%d ", matrix->data[i][j]);
		printf("\n");
	}
}

struct_matrix *create_matrix(int n_rows, int n_cols)
{
	struct_matrix *matrix = malloc(sizeof(struct_matrix));

	if (!matrix) {
		printf("Could not allocate matrix\n");
		exit(1);
	}
	matrix->rows = n_rows;
	matrix->cols = n_cols;

	int **data = malloc(n_rows * sizeof(int *));
	if (!data) {
		printf("Could not allocate matrix\n");
		exit(1);
	}

	for (int i = 0; i < n_rows; i++) {
		data[i] = calloc(n_cols, sizeof(int));
		if (!data[i]) {
			printf("Could not allocate matrix\n");
			exit(1);
		}
	}

	matrix->data = data;
	return matrix;
}

int sum_matrix_elements(struct_matrix *matrix)
{
	int sum = 0;
	for (int i = 0; i < matrix->rows; i++)
		for (int j = 0; j < matrix->cols; j++)
			sum = modulo(sum + matrix->data[i][j]);
	return modulo(sum);
}

struct_matrix *add_matrix(struct_matrix *matrix1, struct_matrix *matrix2)
{
	struct_matrix *new_matrix = create_matrix(matrix1->cols, matrix1->rows);
	for (int i = 0; i < matrix1->rows; i++)
		for (int j = 0; j < matrix1->cols; j++)
			new_matrix->data[i][j] = matrix1->data[i][j] + matrix2->data[i][j];
	return new_matrix;
}

struct_matrix *dif_matrix(struct_matrix *matrix1, struct_matrix *matrix2)
{
	struct_matrix *new_matrix = create_matrix(matrix1->cols, matrix1->rows);
	for (int i = 0; i < matrix1->rows; i++)
		for (int j = 0; j < matrix1->cols; j++)
			new_matrix->data[i][j] = matrix1->data[i][j] - matrix2->data[i][j];
	return new_matrix;
}

struct_matrix *multiply_matrices(struct_matrix *matrix1, struct_matrix *matrix2)
{
	// creez spatiu pentru matricea produs
	struct_matrix *product = create_matrix(matrix1->rows, matrix2->cols);

	for (int i = 0; i < matrix1->rows; i++) {
		for (int j = 0; j < matrix2->cols; j++) {
			// initializez matricea produs cu 0
			product->data[i][j] = 0;
			for (int k = 0; k < matrix1->cols; k++)
				product->data[i][j] =
				modulo(product->data[i][j] +
					modulo(matrix1->data[i][k] * matrix2->data[k][j]));
		}
	}
	product->sum = modulo(sum_matrix_elements(product));
	return product;
}

struct_matrix *multiply(struct_matrix *matrix1, struct_matrix *matrix2)
{
	// creez spatiu pentru matricea produs
	struct_matrix *product = create_matrix(matrix1->rows, matrix2->cols);

	for (int i = 0; i < matrix1->rows; i++) {
		for (int j = 0; j < matrix2->cols; j++) {
			// initializez matricea produs cu 0
			product->data[i][j] = 0;
			for (int k = 0; k < matrix1->cols; k++)
				product->data[i][j] = (product->data[i][j] +
									matrix1->data[i][k] * matrix2->data[k][j]);
		}
	}
	product->sum = modulo(sum_matrix_elements(product));
	return product;
}

void copy_matrices(struct_matrix *matrix1, struct_matrix *matrix2)
{
	// functie care copiaza matricea m2 in matricea m1
	matrix2->rows = matrix1->rows;
	matrix2->cols = matrix1->cols;
	matrix2->sum = matrix1->sum;

	for (int i = 0; i < matrix1->rows; i++)
		for (int j = 0; j < matrix1->cols; j++)
			matrix2->data[i][j] = matrix1->data[i][j];
}

void free_matrix(struct_matrix *matrix)
{
	for (int i = 0; i < matrix->rows; i++)
		free(matrix->data[i]);	//elibereaza fiecare linie din matrice
	free(matrix->data);			//elibereaza matricea
	free(matrix);				//elibereaza structura matricei
}

struct_matrix *transpose_matrix(struct_matrix *matrix)
{
	struct_matrix *transpose = create_matrix(matrix->cols, matrix->rows);

	for (int j = 0; j < matrix->cols; j++) {
		for (int i = 0; i < matrix->rows; i++)
			transpose->data[j][i] = matrix->data[i][j];
	}
	transpose->sum = matrix->sum;
	return transpose;
}

void power_matrix(struct_matrix *b, int p)
{
	struct_matrix *A = create_matrix(b->rows, b->cols);

	for (int i = 0; i < A->rows; i++)
		for (int j = 0; j < A->cols; j++)
			if (i == j)
				A->data[i][j] = 1;
			else
				A->data[i][j] = 0;

	while (p != 0) {
		if (p % 2 != 0) {
			struct_matrix *aux = multiply_matrices(A, b);
			copy_matrices(aux, A);
			free_matrix(aux);
			p--;
		} else {
			struct_matrix *aux = multiply_matrices(b, b);
			copy_matrices(aux, b);
			free_matrix(aux);
			p = p / 2;
		}
	}
	A->sum = sum_matrix_elements(A);
	copy_matrices(A, b);
	free_matrix(A);
}

void cut_matrix(struct_matrix **matrix_storage, int index, int count_matrices)
{
	int *l, dim_l;
	int *c, dim_c;

	scanf("%d", &dim_l);
	l = malloc(dim_l * sizeof(int));
	for (int i = 0; i < dim_l; i++)
		scanf("%d", &l[i]);
	scanf("%d", &dim_c);
	c = malloc(dim_c * sizeof(int));
	for (int i = 0; i < dim_c; i++)
		scanf("%d", &c[i]);

	if (index >= 0 && index < count_matrices) {
		struct_matrix *matrix = create_matrix(dim_l, dim_c);

		matrix->rows = dim_l;
		matrix->cols = dim_c;
		for (int i = 0; i < dim_l; i++)
			for (int j = 0; j < dim_c; j++)
				//creeaza noua matrice(redimensionata)
				matrix->data[i][j] = matrix_storage[index]->data[l[i]][c[j]];
		matrix->sum = sum_matrix_elements(matrix);

		for (int i = 0; i < matrix_storage[index]->rows; i++)
			free(matrix_storage[index]->data[i]);	// free la matricea veche
		free(matrix_storage[index]->data);

		//aloca spatiul nou (mai mic) pt matricea tiata
		matrix_storage[index]->data = (int **)malloc(dim_l * sizeof(int *));
		for (int i = 0; i < dim_l; i++)
			matrix_storage[index]->data[i] =
			(int *)malloc(dim_c * sizeof(int));
		// copiez matricea matrix in matrix_storage
		copy_matrices(matrix, matrix_storage[index]);
		free_matrix(matrix);
	} else {
		printf("No matrix with the given index\n");
	}
	free(l);
	free(c);
}

int compare(const void *pointer_a, const void *pointer_b)
{
	//acesti pointeri se leaga de ceva care e de tipul Matrix **
	struct_matrix **a = (struct_matrix **)pointer_a;
	struct_matrix **b = (struct_matrix **)pointer_b;

	if ((*a)->sum < (*b)->sum) //ordonez crescator dupa suma
		return -1;			   //inseamna ca sunt ordonate bine
	else if ((*a)->sum == (*b)->sum)
		return 0;
	else
		return 1;
}

void resize_matrix(struct_matrix ***matrix_storage, int count_matrices)
{
	*matrix_storage =
		(struct_matrix **)realloc(*matrix_storage,
		count_matrices * sizeof(struct_matrix *));
}

/* FUNCTII PENTRU STRASSEN */

/* Matricile A1, A2, A3, A4 */
struct_matrix *get_matrix_A1(struct_matrix *matrix)
{
	int n_rows = matrix->rows / 2;
	int n_cols = matrix->cols / 2;

	struct_matrix *A1 = create_matrix(n_rows, n_cols);

	for (int i = 0; i < n_rows; i++)
		for (int j = 0; j < n_cols; j++)
			A1->data[i][j] = matrix->data[i][j];

	A1->sum = modulo(sum_matrix_elements(A1));
	return A1;
}

struct_matrix *get_matrix_A2(struct_matrix *matrix)
{
	int n_rows = matrix->rows / 2;
	int n_cols = matrix->cols / 2;

	struct_matrix *A2 = create_matrix(n_rows, n_cols);

	for (int i = 0; i < n_rows; i++)
		for (int j = 0; j < n_cols; j++)
			A2->data[i][j] = matrix->data[i][j + n_cols];

	A2->sum = modulo(sum_matrix_elements(A2));
	return A2;
}

struct_matrix *get_matrix_A3(struct_matrix *matrix)
{
	int n_rows = matrix->rows / 2;
	int n_cols = matrix->cols / 2;

	struct_matrix *A3 = create_matrix(n_rows, n_cols);

	for (int i = 0; i < n_rows; i++)
		for (int j = 0; j < n_cols; j++)
			A3->data[i][j] = matrix->data[i + n_rows][j];

	A3->sum = modulo(sum_matrix_elements(A3));
	return A3;
}

struct_matrix *get_matrix_A4(struct_matrix *matrix)
{
	int n_rows = matrix->rows / 2;
	int n_cols = matrix->cols / 2;

	struct_matrix *A4 = create_matrix(n_rows, n_cols);

	for (int i = 0; i < n_rows; i++)
		for (int j = 0; j < n_cols; j++)
			A4->data[i][j] = matrix->data[i + n_rows][j + n_cols];

	A4->sum = modulo(sum_matrix_elements(A4));
	return A4;
}

/* Matricile B1, B2, B3, B4 */
struct_matrix *get_matrix_B1(struct_matrix *matrix)
{
	int n_rows = matrix->rows / 2;
	int n_cols = matrix->cols / 2;

	struct_matrix *B1 = create_matrix(n_rows, n_cols);

	for (int i = 0; i < n_rows; i++)
		for (int j = 0; j < n_cols; j++)
			B1->data[i][j] = matrix->data[i][j];

	B1->sum = modulo(sum_matrix_elements(B1));
	return B1;
}

struct_matrix *get_matrix_B2(struct_matrix *matrix)
{
	int n_rows = matrix->rows / 2;
	int n_cols = matrix->cols / 2;

	struct_matrix *B2 = create_matrix(n_rows, n_cols);

	for (int i = 0; i < n_rows; i++)
		for (int j = 0; j < n_cols; j++)
			B2->data[i][j] = matrix->data[i][j + n_cols];

	B2->sum = modulo(sum_matrix_elements(B2));
	return B2;
}

struct_matrix *get_matrix_B3(struct_matrix *matrix)
{
	int n_rows = matrix->rows / 2;
	int n_cols = matrix->cols / 2;

	struct_matrix *B3 = create_matrix(n_rows, n_cols);

	for (int i = 0; i < n_rows; i++)
		for (int j = 0; j < n_cols; j++)
			B3->data[i][j] = matrix->data[i + n_rows][j];

	B3->sum = modulo(sum_matrix_elements(B3));
	return B3;
}

struct_matrix *get_matrix_B4(struct_matrix *matrix)
{
	int n_rows = matrix->rows / 2;
	int n_cols = matrix->cols / 2;

	struct_matrix *B4 = create_matrix(n_rows, n_cols);

	for (int i = 0; i < n_rows; i++)
		for (int j = 0; j < n_cols; j++)
			B4->data[i][j] = matrix->data[i + n_rows][j + n_cols];

	B4->sum = modulo(sum_matrix_elements(B4));
	return B4;
}

void free_A_matrices(struct_matrix *A1, struct_matrix *A2,
					 struct_matrix *A3, struct_matrix *A4)
{
	free_matrix(A1);
	free_matrix(A2);
	free_matrix(A3);
	free_matrix(A4);
}

void free_B_matrices(struct_matrix *B1, struct_matrix *B2,
					 struct_matrix *B3, struct_matrix *B4)
{
	free_matrix(B1);
	free_matrix(B2);
	free_matrix(B3);
	free_matrix(B4);
}

void free_M_matrices(struct_matrix *M1, struct_matrix *M2,
					 struct_matrix *M3, struct_matrix *M4,
					 struct_matrix *M5, struct_matrix *M6,
					 struct_matrix *M7)
{
	free_matrix(M1);
	free_matrix(M2);
	free_matrix(M3);
	free_matrix(M4);
	free_matrix(M5);
	free_matrix(M6);
	free_matrix(M7);
}

void free_C_matrices(struct_matrix *C1, struct_matrix *C2,
					 struct_matrix *C3, struct_matrix *C4)
{
	free_matrix(C1);
	free_matrix(C2);
	free_matrix(C3);
	free_matrix(C4);
}

void complete_strassen_matrix(struct_matrix *strassen_mat, int n_rows,
							  int n_cols, struct_matrix *C1,
							  struct_matrix *C2, struct_matrix *C3,
							  struct_matrix *C4)
{
	for (int i = 0; i < n_rows / 2; i++)
		for (int j = 0; j < n_cols / 2; j++)
			strassen_mat->data[i][j] = modulo(C1->data[i][j]);

	for (int i = 0; i < n_rows / 2; i++)
		for (int j = 0; j < n_cols / 2; j++)
			strassen_mat->data[i][j + n_rows / 2] = modulo(C2->data[i][j]);

	for (int i = 0; i < n_rows / 2; i++)
		for (int j = 0; j < n_cols / 2; j++)
			strassen_mat->data[i + n_cols / 2][j] = modulo(C3->data[i][j]);

	for (int i = 0; i < n_rows / 2; i++)
		for (int j = 0; j < n_cols / 2; j++)
			strassen_mat->data[i + n_cols / 2][j + n_cols / 2] =
											modulo(C4->data[i][j]);
}

/* EXECUTE COMMANDS */
void execute_command_L(struct_matrix ***matrix_storage, int *count_matrices)
{
	int m;
	int n;
	scanf("%d%d", &m, &n);

	(*count_matrices)++;
	resize_matrix(matrix_storage, *count_matrices);
	(*matrix_storage)[(*count_matrices) - 1] = create_matrix(m, n);
	read_matrix((*matrix_storage)[(*count_matrices) - 1]);
	(*matrix_storage)[(*count_matrices) - 1]->sum =
		sum_matrix_elements((*matrix_storage)[(*count_matrices) - 1]);
}

void execute_command_D(struct_matrix **matrix_storage, int count_matrices)
{
	int index;
	scanf("%d", &index);

	if (index >= 0 && index < count_matrices)
		printf("%d %d\n", matrix_storage[index]->rows,
			   matrix_storage[index]->cols);
	else
		printf("No matrix with the given index\n");
}

void execute_command_P(struct_matrix **matrix_storage, int count_matrices)
{
	int index;
	scanf("%d", &index);

	if (index >= 0 && index < count_matrices)
		print_matrix(matrix_storage[index]);
	else
		printf("No matrix with the given index\n");
}

void execute_command_C(struct_matrix **matrix_storage, int count_matrices)
{
	int index;
	scanf("%d", &index);

	if (index >= 0 && index < count_matrices)
		cut_matrix(matrix_storage, index, count_matrices);
	else
		printf("No matrix with the given index\n");
}

void execute_command_M(struct_matrix ***matrix_storage, int *count_matrices)
{
	int matrix1_index, matrix2_index;
	scanf("%d%d", &matrix1_index, &matrix2_index);

	// int nr_of_matrices = (*count_matrices);

	if ((matrix1_index >= 0 && matrix1_index < (*count_matrices)) &&
		(matrix2_index >= 0 && matrix2_index < (*count_matrices))) {
		int matrix1_cols = (*matrix_storage)[matrix1_index]->cols;
		int matrix2_rows = (*matrix_storage)[matrix2_index]->rows;

		if (matrix1_cols == matrix2_rows) {
			(*count_matrices)++;
			resize_matrix(matrix_storage, *count_matrices);
			(*matrix_storage)[(*count_matrices) - 1] =
				multiply_matrices((*matrix_storage)[matrix1_index],
								  (*matrix_storage)[matrix2_index]);
		} else {
			printf("Cannot perform matrix multiplication\n");
		}
	} else {
		printf("No matrix with the given index\n");
	}
}

void execute_command_O(struct_matrix **matrix_storage, int count_matrices)
{
	qsort(matrix_storage, count_matrices, sizeof(*matrix_storage), compare);
}

void execute_command_T(struct_matrix **matrix_storage, int count_matrices)
{
	int index;
	scanf("%d", &index);

	if (index >= 0 && index < count_matrices) {
		struct_matrix *aux = matrix_storage[index];
		matrix_storage[index] =
			transpose_matrix(matrix_storage[index]);
		free_matrix(aux);
	} else {
		printf("No matrix with the given index\n");
	}
}

void execute_command_R(struct_matrix **matrix_storage, int count_matrices)
{
	int index;
	int p;	// p = puterea
	scanf("%d%d", &index, &p);

	if (index >= 0 && index < count_matrices) {
		if (p < 0) {
			printf("Power should be positive\n");
		} else {
			if (matrix_storage[index]->rows != matrix_storage[index]->cols)
				printf("Cannot perform matrix multiplication\n");
			else
				power_matrix(matrix_storage[index], p);
		}
	} else {
		printf("No matrix with the given index\n");
	}
}

void execute_command_F(struct_matrix ***matrix_storage, int *count_matrices)
{
	int index;
	scanf("%d", &index);

	if (index >= 0 && index < (*count_matrices)) {
		struct_matrix *aux = (*matrix_storage)[index];

		for (int i = index; i < (*count_matrices) - 1; i++)
			(*matrix_storage)[i] = (*matrix_storage)[i + 1];
		(*matrix_storage)[(*count_matrices) - 1] = aux;

		free_matrix(aux);
		struct_matrix **temp = realloc((*matrix_storage),
			((*count_matrices) - 1) * sizeof(struct_matrix *));

		(*count_matrices)--;
		(*matrix_storage) = temp;
	} else {
		printf("No matrix with the given index\n");
	}
}

void execute_command_S(struct_matrix ***matrix_storage, int *count_matrices)
{
	int index1, index2;
	scanf("%d%d", &index1, &index2);

	if (index1 >= 0 && index1 < (*count_matrices) &&
		index2 >= 0 && index2 < (*count_matrices)) {
		struct_matrix *A1 = get_matrix_A1((*matrix_storage)[index1]);
		struct_matrix *A2 = get_matrix_A2((*matrix_storage)[index1]);
		struct_matrix *A3 = get_matrix_A3((*matrix_storage)[index1]);
		struct_matrix *A4 = get_matrix_A4((*matrix_storage)[index1]);

		struct_matrix *B1 = get_matrix_B1((*matrix_storage)[index2]);
		struct_matrix *B2 = get_matrix_B2((*matrix_storage)[index2]);
		struct_matrix *B3 = get_matrix_B3((*matrix_storage)[index2]);
		struct_matrix *B4 = get_matrix_B4((*matrix_storage)[index2]);

		struct_matrix *first = add_matrix(A1, A4);
		struct_matrix *second = add_matrix(B1, B4);
		struct_matrix *M1 = multiply(first, second);
		free_matrix(first); free_matrix(second);

		struct_matrix *aux = add_matrix(A3, A4);
		struct_matrix *M2 = multiply(aux, B1);
		free_matrix(aux);

		aux = dif_matrix(B2, B4);
		struct_matrix *M3 = multiply(A1, aux);
		free_matrix(aux);

		aux = dif_matrix(B3, B1);
		struct_matrix *M4 = multiply(A4, aux);
		free_matrix(aux);

		aux = add_matrix(A1, A2);
		struct_matrix *M5 = multiply(aux, B4);
		free_matrix(aux);

		first = dif_matrix(A3, A1);
		second = add_matrix(B1, B2);
		struct_matrix *M6 = multiply(first, second);
		free_matrix(first); free_matrix(second);

		first = dif_matrix(A2, A4);
		second = add_matrix(B3, B4);
		struct_matrix *M7 = multiply(first, second);
		free_matrix(first); free_matrix(second);

		first = add_matrix(M1, M4);
		second = dif_matrix(M5, M7);
		struct_matrix *C1 = dif_matrix(first, second);
		free_matrix(first); free_matrix(second);

		struct_matrix *C2 = add_matrix(M3, M5);

		struct_matrix *C3 = add_matrix(M2, M4);

		first = dif_matrix(M1, M2);
		second = add_matrix(M3, M6);
		struct_matrix *C4 = add_matrix(first, second);
		free_matrix(first); free_matrix(second);

		// construiesc matricea mare
		int n_rows = (*matrix_storage)[index1]->rows;
		int n_cols = (*matrix_storage)[index1]->cols;
		struct_matrix *strassen_mat = create_matrix(n_rows, n_cols);

		complete_strassen_matrix(strassen_mat, n_rows, n_cols, C1, C2, C3, C4);
		// adaug matricea strassen_mat in matrix_storage
		(*count_matrices)++;
		resize_matrix(matrix_storage, *count_matrices);
		(*matrix_storage)[(*count_matrices) - 1] = strassen_mat;

		// free la toate matricile auxiliare
		free_A_matrices(A1, A2, A3, A4);
		free_B_matrices(B1, B2, B3, B4);
		free_M_matrices(M1, M2, M3, M4, M5, M6, M7);
		free_C_matrices(C1, C2, C3, C4);
	} else {
		printf("No matrix with the given index\n");
	}
}

void execute_command_Q(struct_matrix **matrix_storage, int count_matrices)
{
	for (int i = 0; i < count_matrices; i++)
		free_matrix(matrix_storage[i]);
	free(matrix_storage);
}

int main(void)
{
	char instruction_type;
	int count_matrices = 0;
	struct_matrix **matrix_storage = malloc(sizeof(struct_matrix *));

	while (scanf("%c", &instruction_type) && instruction_type != 'Q') {
		if (instruction_type == ' ' || instruction_type == '\n' ||
			strchr("0123456789", instruction_type) != 0)
			continue;

		if (instruction_type == 'L')
			execute_command_L(&matrix_storage, &count_matrices);
		else if (instruction_type == 'D')
			execute_command_D(matrix_storage, count_matrices);
		else if (instruction_type == 'P')
			execute_command_P(matrix_storage, count_matrices);
		else if (instruction_type == 'C')
			execute_command_C(matrix_storage, count_matrices);
		else if (instruction_type == 'M')
			execute_command_M(&matrix_storage, &count_matrices);
		else if (instruction_type == 'O')
			execute_command_O(matrix_storage, count_matrices);
		else if (instruction_type == 'T')
			execute_command_T(matrix_storage, count_matrices);
		else if (instruction_type == 'R')
			execute_command_R(matrix_storage, count_matrices);
		else if (instruction_type == 'F')
			execute_command_F(&matrix_storage, &count_matrices);
		else if (instruction_type == 'S')
			execute_command_S(&matrix_storage, &count_matrices);
		else
			printf("Unrecognized command\n");
	}

	if (instruction_type == 'Q')
		execute_command_Q(matrix_storage, count_matrices);

	return 0;
}