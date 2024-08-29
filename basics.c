#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *data;
    int rows;
    int cols;
} Mat;

Mat *matadd(const Mat *mat1, const Mat *mat2) // const means the function will not modify the input matrices
{
    if (mat1->rows != mat2->rows || mat1->cols != mat2->cols)
    {
        perror("Mats that are not of the same size cannot be matadded!\n");
        return NULL;
    }

    Mat *result = (Mat *)malloc(sizeof(Mat));
    if (result == NULL)
    {
        perror("Memory allocation failed!\n");
        return NULL;
    }
    result->rows = mat1->rows;
    result->cols = mat1->cols;
    result->data = (int *)malloc(sizeof(int) * result->rows * result->cols);

    if (result->data == NULL)
    {
        perror("Memory allocation failed!\n");
        free(result);
        return NULL;
    }
    for (int i = 0; i < result->rows; i++)
    {
        for (int j = 0; j < result->cols; j++)
        {
            int idx = i * result->cols + j; // row-major order
            result->data[idx] = mat1->data[idx] + mat2->data[idx];
        }
    }
    return result;
}

Mat *matmul(const Mat *mat1, const Mat *mat2)
{
    if (mat1->cols != mat2->rows)
    {
        perror("Mats that are not of the same size cannot be matmuled!\n");
        return NULL;
    }

    Mat *result = (Mat *)malloc(sizeof(Mat));
    if (result == NULL)
    {
        perror("Memory allocation failed!\n");
        return NULL;
    }
    result->rows = mat1->rows;
    result->cols = mat2->cols;
    result->data = (int *)malloc(sizeof(int) * result->rows * result->cols);
    if (result->data == NULL)
    {
        perror("Memory allocation failed!\n");
        free(result);
        return NULL;
    }

    for (int i = 0; i < result->rows; i++)
    {
        for (int j = 0; j < result->cols; j++)
        {
            result->data[i * result->cols + j] = 0;
            for (int k = 0; k < mat1->cols; k++)
            {
                result->data[i * result->cols + j] += mat1->data[i * mat1->cols + k] * mat2->data[k * mat2->cols + j];
            }
        }
    }
    return result;
}

Mat *transpose(const Mat *mat)
{
    Mat *result = (Mat *)malloc(sizeof(Mat));
    if (result == NULL)
    {
        perror("Memory allocation failed!\n");
        return NULL;
    }
    result->rows = mat->cols;
    result->cols = mat->rows;
    result->data = (int *)malloc(sizeof(int) * result->rows * result->cols);
    if (result->data == NULL)
    {
        perror("Memory allocation failed!\n");
        free(result);
        return NULL;
    }

    for (int i = 0; i < result->rows; i++)
    {
        for (int j = 0; j < result->cols; j++)
        {
            result->data[i * result->cols + j] = mat->data[j * mat->rows + i];
        }
    }
    return result;
}

int main(void)
{
    // ^ arrays
    int arr[3] = {1, 2, 3}; // array of 3 integers (each int is 4 bytes)
    int arr2[3] = {4, 5, 6};
    Mat mat1 = {.data = arr, .rows = 1, .cols = 3}; // 1x3 custom matrix
    Mat mat2 = {.data = arr2, .rows = 1, .cols = 3}; // 1x3 custom matrix
    // matadd is an element-wise operation
    Mat *result = matadd(&mat1, &mat2); // the result should be: [5 7 9]
    for (int i = 0; i < result->rows; i++)
    {
        printf("%d ", result->data[i]);
    }
    printf("\n");
    free(result); // heap that was allocated for the result must be freed
    mat1 = *transpose(&mat1);
    mat2 = *transpose(&mat2);
    printf("%d", mat1.rows);
    Mat *result2 = matmul(&mat1, &mat2); // the result should be: [4 10 18]
    for (int i = 0; i < result2->rows; i++)
    {
        printf("%d ", result2->data[i]);
    }
    printf("\n");
    free(result2);
}
