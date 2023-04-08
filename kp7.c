#include <stdio.h>

int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);
    int matrix[n][m];
    int count = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &matrix[i][j]);
            if (matrix[i][j] != 0) {
                ++count;
            }
        }
    }
    int M[n];
    for (int i = 0; i < n; ++i) {
        M[i] = 0;
    }
    int A[count][3];
    int index = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (matrix[i][j] != 0) {
                A[index][0] = j;
                A[index][1] = matrix[i][j];
                A[index][2] = index + 1;
                ++index;
                if (M[i] == 0) {
                    M[i] = index;
                }
            }
        }
        if (A[index - 1][2] != 0) {
            A[index - 1][2] = 0;
        }
    } 
    int n2, m2;
    scanf("%d %d", &n2, &m2);
    if (n2 != n || m2!= m) {
        printf("Операция сложения матриц не определена.\n");
    } else {
        int matrix2[n2][m2];
        int count2 = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                scanf("%d", &matrix2[i][j]);
                if (matrix2[i][j] != 0) {
                    ++count2;
                }
            }
        }
        int M2[n];
        for (int i = 0; i < n; ++i) {
            M2[i] = 0;
        }
        int A2[count2][3];
        index = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (matrix2[i][j] != 0) {
                    A2[index][0] = j;
                    A2[index][1] = matrix2[i][j];
                    A2[index][2] = index + 1;
                    ++index;
                    if (M2[i] == 0) {
                        M2[i] = index;
                    }
                }
            }
            if (A2[index - 1][2] != 0) {
                A2[index - 1][2] = 0;
            }
        }
        
        int M_res[n];
        int A_res[n * m][3];
        int index_res = 0;
        int index1 = 0;
        int index2 = 0;
        for (int i = 0; i < n; ++i) {
            M_res[i] = index_res + 1;
            index1 = M[i] - 1;
            index2 = M2[i] - 1;
            int isEnd1 = 0;
            int isEnd2 = 0;
            if (index1 < 0) {
                isEnd1 = 1;
            }
            if (index2 < 0) {
                isEnd2 = 1;
            }
            while (isEnd1 == 0 || isEnd2 == 0) {
                if (isEnd1 == 1) {
                    A_res[index_res][0] = A2[index2][0];
                    A_res[index_res][1] = A2[index2][1];
                    A_res[index_res][2] = index_res + 1;
                    ++index_res;
                    ++index2;
                } else if (isEnd2 == 1) {
                    A_res[index_res][0] = A[index1][0];
                    A_res[index_res][1] = A[index1][1];
                    A_res[index_res][2] = index_res + 1;
                    ++index_res;
                    ++index1;
                } else if (A[index1][0] == A2[index2][0]) {
                    A_res[index_res][0] = A[index1][0];
                    A_res[index_res][1] = A[index1][1] + A2[index2][1];
                    A_res[index_res][2] = index_res + 1;
                    ++index_res;
                    ++index1;
                    ++index2;
                } 
                else if (A[index1][0] < A2[index2][0]) {
                    A_res[index_res][0] = A[index1][0];
                    A_res[index_res][1] = A[index1][1];
                    A_res[index_res][2] = index_res + 1;
                    ++index_res;
                    ++index1;
                } 
                else {
                    A_res[index_res][0] = A2[index2][0];
                    A_res[index_res][1] = A2[index2][1];
                    A_res[index_res][2] = index_res + 1;
                    ++index_res;
                    ++index2;
                }
                if (A[index1 - 1][2] == 0) {
                    isEnd1 = 1;
                }
                if (A2[index2 - 1][2] == 0) {
                    isEnd2 = 1;
                }
            }
            A_res[index_res - 1][2] = 0;
        }
        
        for (int i = 0; i < index_res; ++i) {
            for (int j = 0; j < 3; ++j) {
                printf("%d ", A_res[i][j]);
            }
            printf("\n");
        }
        for (int i = 0; i < n; ++i) {
            printf("%d ", M_res[i]);
        }
        printf("\n\n");
        
        for (int i = 0; i < n; ++i) {
            if (M_res[i] == 0) {
                for (int j = 0; j < m; ++j) {
                    printf("0 ");
                }
                printf("\n");
            } else {
                int ii = M_res[i] - 1;
                int isNull = 0;
                for (int j = 0; j < m; ++j) {
                    if (isNull == 1) {
                        printf("0 ");
                    } else if (A_res[ii][0] == j) {
                        printf("%d ", A_res[ii][1]);
                        ++ii;
                        if (A_res[ii - 1][2] == 0) {
                            isNull = 1;
                        }
                    } else {
                        printf("0 ");
                    }
                }
                printf("\n");
            }
        }
        printf("\n");
        
        if (n != m) {
            printf("Симметричность определить нельзя.\n");
        } else {
            int sym = 1;
            for (int i = 0; i < n; ++i) {
                if (M_res[i] == 0) {
                    continue;
                }
                int j = M_res[i] - 1;
                while (1 == 1) {
                    int jj = M_res[A_res[j][0]] - 1;
                    int t = A_res[j][1];
                    while (1 == 1) {
                        if (A_res[jj][0] == j) {
                            if (A_res[jj][1] != t) {
                                sym = 0;
                                break;
                            } else {
                                break;
                            }
                            if (A_res[jj][2] == 0) {
                                sym = 0;
                                break;
                            }
                        }
                        ++jj;
                    }
                    if (A_res[j][2] == 0) {
                        break;
                    }
                    ++j;
                }
            }
            if (sym == 1) {
                printf("yes\n");
            } else {
                printf("no\n");
            }
        }
    }
    return 0;
}
