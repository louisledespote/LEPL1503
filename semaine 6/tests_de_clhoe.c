#include <CUnit/Basic.h>

#include <CUnit/CUnit.h>

#include <time.h>

#include <math.h>

 

#include "../headers/matrix.h"

#include "../headers/vector.h"

 

#include "../headers/file.h"

 

void test_add_v_v(void) {

    uint64_t m = 300;

    vector *v = init_vector(m);

    vector *w = init_vector(m);

    vector *z = init_vector(m);

    for (uint64_t i = 0; i < m; i++) {

        v->values[i] = (double)rand() / 2.0;

        w->values[i] = (double)rand() / 2.0;

    }

    add_v_v(v, w, z);

    for (uint64_t i = 0; i < m; i++) {

        CU_ASSERT_DOUBLE_EQUAL(z->values[i], v->values[i] + w->values[i], 1e-3);

    }

    free_vector(v);

    free_vector(w);

    free_vector(z);

 

    m = 3;

    v = init_vector(m);

    w = init_vector(m);

    v->values[0] = 1.01;

    v->values[1] = 2.0;

    v->values[2] = 3.0;

    w->values[0] = 1.0;

    w->values[1] = -4.0;

    w->values[2] = 100;

    z = init_vector(m);

    add_v_v(v, w, z);

    CU_ASSERT_DOUBLE_EQUAL(z->values[0],2.01, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(z->values[1],-2.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(z->values[2],103.0, 1e-3);

    free_vector(v);

    free_vector(w);

    free_vector(z);

 

    m = 1;

    v = init_vector(m);

    w = init_vector(m);

    v->values[0] = 1.0;

    w->values[0] = 2.0;

    z = init_vector(m);

    add_v_v(v, w, z);

    CU_ASSERT_DOUBLE_EQUAL(z->values[0],3.0, 1e-3);

    free_vector(v);

    free_vector(w);

    free_vector(z);

 

    m = 4;

    v = init_vector(m);

    w = init_vector(m);

    v->values[0] = 0.0; v->values[1] = -1.3; v->values[2] = 2.5; v->values[3] = 3.0;

    w->values[0] = -3.5; w->values[1] = 0.0; w->values[2] = 0.0; w->values[3] = -3.0;

    z = init_vector(m);

    add_v_v(v,w,z);

    for (uint64_t i = 0; i < m; i++) {

        CU_ASSERT_DOUBLE_EQUAL(z->values[i], v->values[i] + w->values[i], 1e-3);

    }

    free_vector(v);

    free_vector(w);

    free_vector(z);

 

    m = 17;

    v = init_vector(m);

    w = init_vector(m);

    z = init_vector(m);

    add_v_v(v,w,z);

    for (uint64_t i = 0; i < m; i++) {

        CU_ASSERT_DOUBLE_EQUAL(z->values[i], v->values[i] + w->values[i], 1e-3);

    }

    free_vector(v);

    free_vector(w);

    free_vector(z);

}

 

void test_dot_prod(void){

    uint64_t m = 3;

    vector *v = init_vector(m);

    vector *w = init_vector(m);

    double prod = 0;

    double result = 0;

    v->values[0] = 5.6; v->values[1] = 0.0; v->values[2] = -12.61;

    w->values[0] = 0.0; w->values[1] = 3.0; w->values[2] = 0.0;

    dot_prod(v,w);

    for (uint64_t i = 0; i < m; i++) {

        prod = v->values[i]*w->values[i];

        result += prod;

    }

    CU_ASSERT_DOUBLE_EQUAL(dot_prod(v,w),result, 1e-3 );

    free_vector(v);

    free_vector(w);

 

    m = 3;

    v = init_vector(m);

    w = init_vector(m);

    double prod = 0;

    double result = 0;

    v->values[0] = -3.2; v->values[1] = 2.0; v->values[2] = 5.3;

    w->values[0] = -5.0; w->values[1] = -3.7; w->values[2] = 10.0;

    dot_prod(v,w);

    for (uint64_t i = 0; i < m; i++) {

        prod = v->values[i]*w->values[i];

        result += prod;

    }

    CU_ASSERT_DOUBLE_EQUAL(dot_prod(v,w),result, 1e-3 );

    free_vector(v);

    free_vector(w);

 

    m = 3;

    vector *v = init_vector(m);

    vector *w = init_vector(m);

    v->values[0] = 1.01;

    v->values[1] = 2.0;

    v->values[2] = 3.0;

    w->values[0] = 1.0;

    w->values[1] = -4.0;

    w->values[2] = 100;

    CU_ASSERT_DOUBLE_EQUAL(dot_prod(v, w), 293.01, 1e-3);

    free_vector(v);

    free_vector(w);

 

    m = 1;

    vector *v = init_vector(m);

    vector *w = init_vector(m);

    v->values[0] = 1.0;

    w->values[0] = 2.0;

    CU_ASSERT_DOUBLE_EQUAL(dot_prod(v, w), 2.0, 1e-3);

    free_vector(v);

    free_vector(w);

 

   

}

 

void test_norm(void){

    uint64_t m = 3;

    vector * v = init_vector(m);

    v->values[0] = 1.34; v->values[1] = 3.2; v->values[2] = -6.0;

    double a = 0.0;

    norm(v);

    for(uint64_t i=0; i<m; i++){

        a += v->values[i] * v->values[i];

    }

    CU_ASSERT_DOUBLE_EQUAL(norm(v), sqrt(a), 1e-3);

    free_vector(v);

 

    m = 7;

    v = init_vector(m);

    a =0.0;

    norm(v);

    for(uint64_t i=0; i<m; i++){

        a += v->values[i] * v->values[i];

    }

    CU_ASSERT_DOUBLE_EQUAL(norm(v), sqrt(a), 1e-3);

    free_vector(v);

 

    m = 4;

    vector *v = init_vector(m);

    v->values[0] = 0.0;

    v->values[1] = 0.0;

    v->values[2] = 3.0;

    v->values[3] = 4.0;

    CU_ASSERT_DOUBLE_EQUAL(norm(v), 5.0, 1e-3);

    free_vector(v);

 

    m = 2;

    vector *v = init_vector(m);

    v->values[0] = 2;

    v->values[1] = 1.5;

    CU_ASSERT_DOUBLE_EQUAL(norm(v), 2.5, 1e-3);

    free_vector(v);

}

void test_add_m_m(void) {

    uint64_t m = 300;

    uint64_t n = 200;

    matrix *A = init_matrix(m, n);

    matrix *B = init_matrix(m, n);

    for (uint64_t i = 0; i < m; i++) {

        for (uint64_t j = 0; j < n; j++) {

            A->values[i][j] = (double)rand() / 2.0;

            B->values[i][j] = (double)rand() / 2.0;

        }

    }

    matrix *C = init_matrix(m, n);

    add_m_m(A, B, C);

    for (uint64_t i = 0; i < m; i++) {

        for (uint64_t j = 0; j < n; j++) {

            CU_ASSERT_DOUBLE_EQUAL(C->values[i][j],

                                   A->values[i][j] + B->values[i][j], 1e-3);

        }

    }

   

    free_matrix(A);

    free_matrix(B);

    free_matrix(C);

 

    m = 2;

    n = 3;

    A = init_matrix(m, n);

    B = init_matrix(m, n);

 

    A->values[0][0] = 1.0;

    A->values[0][1] = 1.0;

    A->values[0][2] = 7.0;

    A->values[1][0] = -3.0;

    A->values[1][1] = 4.0;

    A->values[1][2] = 3.0;

    B->values[0][0] = 4.03;

    B->values[0][1] = 2.0;

    B->values[0][2] = -7.0;

    B->values[1][0] = 0.0;

    B->values[1][1] = 1.0;

    B->values[1][2] = 1.0;

    C = init_matrix(m, n);

    add_m_m(A, B, C);

    CU_ASSERT_DOUBLE_EQUAL(C->values[0][0],5.03, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[0][1],3.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[0][2],0.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[1][0],-3.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[1][1],5.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[1][2],4.0, 1e-3);

    free_matrix(A);

    free_matrix(B);

    free_matrix(C);

   

}

 

void test_sub_v_v(void){

    uint64_t m = 300;

    vector *v = init_vector(m);

    vector *w = init_vector(m);

    for (uint64_t i = 0; i < m; i++) {

        v->values[i] = (double)rand() / 2.0;

        w->values[i] = (double)rand() / 2.0;

    }

    vector *z = init_vector(m);

    sub_v_v(v, w, z);

    for (uint64_t i = 0; i < m; i++) {

        CU_ASSERT_DOUBLE_EQUAL(z->values[i], v->values[i] - w->values[i], 1e-3);

    }

    free_vector(v);

    free_vector(w);

    free_vector(z);

 

    m = 3;

    v = init_vector(m);

    w = init_vector(m);

    v->values[0] = 1.01;

    v->values[1] = 2.0;

    v->values[2] = 3.0;

    w->values[0] = 1.0;

    w->values[1] = -4.0;

    w->values[2] = 100.0;

    z = init_vector(m);

    sub_v_v(v, w, z);

    CU_ASSERT_DOUBLE_EQUAL(z->values[0],0.01, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(z->values[1],6.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(z->values[2],-97.0, 1e-3);

    free_vector(v);

    free_vector(w);

    free_vector(z);

 

    m = 1;

    v = init_vector(m);

    w = init_vector(m);

    v->values[0] = 1.0;

    w->values[0] = 2.0;

    z = init_vector(m);

    sub_v_v(v, w, z);

    CU_ASSERT_DOUBLE_EQUAL(z->values[0],-1.0, 1e-3);

    free_vector(v);

    free_vector(w);

    free_vector(z);

 

}

 

void test_sub_m_m(void){

    uint64_t m = 300;

    uint64_t n = 200;

    matrix *A = init_matrix(m, n);

    matrix *B = init_matrix(m, n);

    for (uint64_t i = 0; i < m; i++) {

        for (uint64_t j = 0; j < n; j++) {

            A->values[i][j] = (double)rand() / 2.0;

            B->values[i][j] = (double)rand() / 2.0;

        }

    }

 

    A->values[0][0] = 0.0; A->values[0][1] = 3.2; A->values[1][0] = 0.0; A->values[1][1] = 5.2;

    B->values[0][0] = -7.53; B->values[0][1] = 2.521; B->values[1][0] = 0; B->values[1][1] = -7.31;

 

    matrix *C = init_matrix(m, n);

    sub_m_m(A, B, C);

    for (uint64_t i = 0; i < m; i++) {

        for (uint64_t j = 0; j < n; j++) {

            CU_ASSERT_DOUBLE_EQUAL(C->values[i][j],

                                   A->values[i][j] - B->values[i][j], 1e-3);

        }

    }

 

    free_matrix(A);

    free_matrix(B);

    free_matrix(C);

 

    m = 2;

    n = 3;

    A = init_matrix(m, n);

    B = init_matrix(m, n);

 

    A->values[0][0] = 1.0;

    A->values[0][1] = 1.0;

    A->values[0][2] = 7.0;

    A->values[1][0] = -3.0;

    A->values[1][1] = 4.0;

    A->values[1][2] = 3.0;

    B->values[0][0] = 4.03;

    B->values[0][1] = 2.0;

    B->values[0][2] = -7.0;

    B->values[1][0] = 0.0;

    B->values[1][1] = 1.0;

    B->values[1][2] = 1.0;

    C = init_matrix(m, n);

    sub_m_m(A, B, C);

    CU_ASSERT_DOUBLE_EQUAL(C->values[0][0],-3.03, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[0][1],-1.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[0][2],14.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[1][0],-3.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[1][1],3.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[1][2],2.0, 1e-3);

    free_matrix(A);

    free_matrix(B);

    free_matrix(C);

 

}

void test_mult_m_v(void){

    uint64_t m = 2;

    uint64_t n = 3;

    matrix *A = init_matrix(m, n);

    vector *v = init_vector(n);

    vector *w = init_vector(m);

   

    A->values[0][0] = 1.0; A->values[0][1] = 1.0; A->values[0][2] = 7.0;

    A->values[1][0] = -3.0; A->values[1][1] = 4.0; A->values[1][2] = 3.0;

    v->values[0] = 1.01; v->values[1] = 2.0; v->values[2] = 3.0;

    mult_m_v(A, v, w);

    CU_ASSERT_DOUBLE_EQUAL(w->values[0], 24.01, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(w->values[1], 13.97, 1e-3);

    free_matrix(A);

    free_vector(v);

    free_vector(w);

   

    A = init_matrix(m, n);

    v = init_vector(n);

    w = init_vector(m);




    A->values[0][0] = -2.6; A->values[0][1] = 0.0; A->values[0][2] = 1.23; A->values[1][0] = 0.0; A->values[1][1] = 3.45; A->values[1][2] = 0.0;

    v->values[0] = 2.0; v->values[1] = 0.0; v->values[2] = -3.4;

    w = init_vector(m);

    mult_m_v(A, v, w);

    for (uint64_t i = 0; i < m; i++) {

        double a = 0.0;

        for (uint64_t j = 0; j < n; j++) {

            a += v->values[j] * A->values[i][j];

        }

        CU_ASSERT_DOUBLE_EQUAL(w->values[i], a, 1e-3)

    }

    free_matrix(A);

    free_vector(v);

    free_vector(w);

 

    m = 2;

    n = 3;

    A = init_matrix(m, n);

    v = init_vector(n);

    w = init_vector(m);

 

    mult_m_v(A, v, w);

 

    for (uint64_t i = 0; i < m; i++) {

        double a = 0.0;

        for (uint64_t j = 0; j < n; j++) {

            a += v->values[j] * A->values[i][j];

        }

        CU_ASSERT_DOUBLE_EQUAL(w->values[i], a, 1e-3)

    }

    free_matrix(A);

    free_vector(v);

    free_vector(w);

}

void test_mult_m_m (void) {

    uint64_t m = 2;

    uint64_t n = 2;

    matrix *A = init_matrix(m, n);

    matrix *B = init_matrix(n, m);

    A->values[0][0] = 0; A->values[0][1] = 3; A->values[1][0] = -5; A->values[1][1] = 0;

    B->values[0][0] = -2; B->values[0][1] = 0; B->values[1][0] = 0;B->values[1][1] = 10;

    matrix *C = init_matrix(m, n);

    mult_m_m(A, B, C);

    matrix *D = init_matrix(m,n);

    for(uint64_t i = 0; i < m; i++){

        for(uint64_t j = 0; j < m; j++){

            D->values[i][j] = 0.0;

            for(uint64_t k = 0; k< n; k++){

                D->values[i][j] += A->values[i][k] * B->values[k][j];

            }

            CU_ASSERT_DOUBLE_EQUAL(C->values[i][j],D->values[i][j],1e-3);

        }

    }

 

    free_matrix(A);

    free_matrix(B);

    free_matrix(C);

    free_matrix(D);

 

    m = 2;

    n = 3;

    A = init_matrix(m, n);

    B = init_matrix(n, m);

    A->values[0][0] = 0.0; A->values[0][1] = -3.5; A->values[0][2] = 0.0; A->values[1][0] = 2.3; A->values[1][1] = 0.0; A->values[1][2] = 4.0;

    B->values[0][0] = 1.58; B->values[0][1] = 0.0; B->values[1][0] = 0.0;B->values[1][1] = 2.0;B->values[2][0] = 6.42; B->values[1][0] = 0.0;

    C = init_matrix(m, m);

    mult_m_m(A, B, C);

    D = init_matrix(m,m);

    for(uint64_t i = 0; i < m; i++){

        for(uint64_t j = 0; j < m; j++){

            D->values[i][j] = 0.0;

            for(uint64_t k = 0; k< n; k++){

                D->values[i][j] += A->values[i][k] * B->values[k][j];

            }

            CU_ASSERT_DOUBLE_EQUAL(C->values[i][j],D->values[i][j],1e-3);

        }

    }

 

    free_matrix(A);

    free_matrix(B);

    free_matrix(C);

    free_matrix(D);

 

    m = 3;

    n = 3;

    A = init_matrix(m, n);

    B = init_matrix(m, n);

    A->values[0][0] = 0.0;

    A->values[0][1] = 1.0;

    A->values[0][2] = 1.0;

    A->values[1][0] = 7.0;

    A->values[1][1] = 0.0;

    A->values[1][2] = 3.0;

    A->values[2][0] = 1.0;

    A->values[2][1] = 100.0;

    A->values[2][2] = 310.0;

 

    B->values[0][0] = 1.0;

    B->values[0][1] = 2.0;

    B->values[0][2] = 3.0;

    B->values[1][0] = 4.0;

    B->values[1][1] = 3.3;

    B->values[1][2] = 1.0;

    B->values[2][0] = -2.0;

    B->values[2][1] = 1.0;

    B->values[2][2] = 0.0;

    C = init_matrix(m, n);

    mult_m_m(A, B, C);

    CU_ASSERT_DOUBLE_EQUAL(C->values[0][0],2.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[0][1],4.3, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[0][2],1.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[1][0],1.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[1][1],17.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[1][2],21.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[2][0],-219.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[2][1],642.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[2][2],103.0, 1e-3);

    free_matrix(A);

    free_matrix(B);

    free_matrix(C);

 

    m = 2;

    n = 2;

    uint64_t p = 3;

    A = init_matrix(m, n);

    B = init_matrix(n, p);

    A->values[0][0] = 4.03;

    A->values[0][1] = 2.0;

    A->values[1][0] = 0.0;

    A->values[1][1] = 1.0;

    B->values[0][0] = 1.0;

    B->values[0][1] = 1.0;

    B->values[0][2] = 7.0;

    B->values[1][0] = -3.0;

    B->values[1][1] = 4.0;

    B->values[1][2] = 3.0;

    C = init_matrix(m, p);

    mult_m_m(A, B, C);

    CU_ASSERT_DOUBLE_EQUAL(C->values[0][0],-1.97, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[0][1],12.03, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[0][2],34.21, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[1][0],-3.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[1][1],4.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[1][2],3.0, 1e-3);

    free_matrix(A);

    free_matrix(B);

    free_matrix(C);

 

    //tests avec la matrice identité dans un sens puis l'autre

    m = 3;

    n = 3;

    A = init_matrix(m, n);

    B = init_matrix(m, n);

 

    A->values[0][0] = 1.0;

    A->values[0][1] = 0.0;

    A->values[0][2] = 0.0;

    A->values[1][0] = 0.0;

    A->values[1][1] = 1.0;

    A->values[1][2] = 0.0;

    A->values[2][0] = 0.0;

    A->values[2][1] = 0.0;

    A->values[2][2] = 1.0;

 

    B->values[0][0] = 1.0;

    B->values[0][1] = 2.0;

    B->values[0][2] = 3.0;

    B->values[1][0] = 4.0;

    B->values[1][1] = 3.3;

    B->values[1][2] = 1.0;

    B->values[2][0] = -2.0;

    B->values[2][1] = 1.0;

    B->values[2][2] = 0.0;

 

    C = init_matrix(m, n);

    mult_m_m(A, B, C);

 

    CU_ASSERT_DOUBLE_EQUAL(C->values[0][0], 1.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[0][1], 2.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[0][2], 3.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[1][0], 4.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[1][1], 3.3, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[1][2], 1.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[2][0], -2.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[2][1], 1.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[2][2], 0.0, 1e-3);

 

    free_matrix(A);

    free_matrix(B);

    free_matrix(C);

 

    m = 3;

    n = 3;

    A = init_matrix(m, n);

    B = init_matrix(m, n);

 

    A->values[0][0] = 1.0;

    A->values[0][1] = 0.0;

    A->values[0][2] = 0.0;

    A->values[1][0] = 0.0;

    A->values[1][1] = 1.0;

    A->values[1][2] = 0.0;

    A->values[2][0] = 0.0;

    A->values[2][1] = 0.0;

    A->values[2][2] = 1.0;

 

    B->values[0][0] = 1.0;

    B->values[0][1] = 2.0;

    B->values[0][2] = 3.0;

    B->values[1][0] = 4.0;

    B->values[1][1] = 3.3;

    B->values[1][2] = 1.0;

    B->values[2][0] = -2.0;

    B->values[2][1] = 1.0;

    B->values[2][2] = 0.0;

 

    C = init_matrix(m, n);

    mult_m_m(B, A, C);

 

    CU_ASSERT_DOUBLE_EQUAL(C->values[0][0], 1.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[0][1], 2.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[0][2], 3.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[1][0], 4.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[1][1], 3.3, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[1][2], 1.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[2][0], -2.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[2][1], 1.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[2][2], 0.0, 1e-3);

 

    free_matrix(A);

    free_matrix(B);

    free_matrix(C);

}

 

void test_transp(void){

 

   

    uint64_t m = 3;

    uint64_t n = 3;

    matrix *A = init_matrix(m, n);

    matrix *B = init_matrix(m, n);

    matrix *C = init_matrix(n, m);

 

    A->values[0][0] = 1.0;

    A->values[0][1] = 0.0;

    A->values[0][2] = 0.0;

    A->values[1][0] = 0.0;

    A->values[1][1] = 1.0;

    A->values[1][2] = 0.0;

    A->values[2][0] = 0.0;

    A->values[2][1] = 0.0;

    A->values[2][2] = 1.0;

 

    transp(A, C);

    CU_ASSERT_DOUBLE_EQUAL(C->values[0][0], 1.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[0][1], 0.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[0][2], 0.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[1][0], 0.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[1][1], 1.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[1][2], 0.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[2][0], 0.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[2][1], 0.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[2][2], 1.0, 1e-3);

    free_matrix(A);

    free_matrix(C);

 

    m = 3;

    n = 3;

    B = init_matrix(m, n);

    C = init_matrix(n, m);

 

    B->values[0][0] = 1.0;

    B->values[0][1] = 2.0;

    B->values[0][2] = 3.0;

    B->values[1][0] = 4.0;

    B->values[1][1] = 3.3;

    B->values[1][2] = 1.0;

    B->values[2][0] = -2.0;

    B->values[2][1] = 1.0;

    B->values[2][2] = 0.0;

 

    transp(B, C);

    CU_ASSERT_DOUBLE_EQUAL(C->values[0][0], 1.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[0][1], 4.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[0][2], -2.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[1][0], 2.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[1][1], 3.3, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[1][2], 1.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[2][0], 3.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[2][1], 1.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[2][2], 0.0, 1e-3);

    free_matrix(B);

    free_matrix(C);

 

    m = 2;

    n = 4;

    A = init_matrix(m, n);

    C = init_matrix(n, m);

 

    A->values[0][0] = 1.0;

    A->values[0][1] = 2.0;

    A->values[0][2] = 3.0;

    A->values[0][3] = 4.0;

    A->values[1][0] = -1.0;

    A->values[1][1] = -2.0;

    A->values[1][2] = -3.0;

    A->values[1][3] = -4.1;

 

    transp(A, C);

    CU_ASSERT_DOUBLE_EQUAL(C->values[0][0], 1.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[0][1], -1.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[1][0], 2.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[1][1], -2.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[2][0], 3.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[2][1], -3.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[3][0], 4.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(C->values[3][1], -4.1, 1e-3);

    free_matrix(A);

    free_matrix(C);




    A = init_matrix(m, n);

    B = init_matrix(n, m);

 

    A->values[0][0] = -5; A->values[0][1] = -3; A->values[1][0] = 3; A->values[1][1] = 5;

   

    transp(A, B);

    for (uint64_t i = 0; i < n; i++){

        for (uint64_t j = 0; j < m; j++){

            CU_ASSERT_DOUBLE_EQUAL(B->values[i][j], A->values[j][i], 1e-3);

        }

    }

    free_matrix(A);

    free_matrix(B);

   

 

}

 

void test_back_sub() {

    uint64_t m = 2;

 

    matrix *U = init_matrix(m, m);

    U->values[0][0] = 1;

    U->values[0][1] = 2;

    U->values[1][0] = 0;

    U->values[1][1] = 3;

 

    vector *b = init_vector(m);

    b->values[0] = 5;

    b->values[1] = 3;

 

    vector *x = init_vector(m);

 

    back_sub(U, b, x);

 

    double x_true[2] = { 3, 1 };

 

    for (uint64_t i = 0; i < m; i++) {

//        printf("%lu) %f ?= %f",i,x->values[i],x_true[i]);

        CU_ASSERT_DOUBLE_EQUAL(x->values[i], x_true[i], 1e-3);

    }

 

    free_vector(x);

    free_vector(b);

    free_matrix(U);

 

}

 

int main(int argc, char **argv) {

    srand(time(NULL));

 

   

    if (CUE_SUCCESS != CU_initialize_registry()) {

        return CU_get_error();

    }

 

    CU_pSuite test_basic_op = CU_add_suite("test_basic_op", NULL, NULL);

    if (test_basic_op == NULL) {

        CU_cleanup_registry();

        return CU_get_error();

    }

 

    if ((CU_add_test(test_basic_op, "add_v_v", test_add_v_v) == NULL) ||

        (CU_add_test(test_basic_op, "add_m_m", test_add_m_m) == NULL) ||

        (CU_add_test(test_basic_op, "sub_v_v", test_sub_v_v) == NULL) ||

        (CU_add_test(test_basic_op, "sub_m_m", test_sub_m_m) == NULL) ||

        (CU_add_test(test_basic_op, "dot_prod", test_dot_prod) == NULL) ||

        (CU_add_test(test_basic_op, "norm", test_norm) == NULL) ||

        (CU_add_test(test_basic_op, "mult_m_v", test_mult_m_v) == NULL) ||

        (CU_add_test(test_basic_op, "mult_m_m", test_mult_m_m) == NULL) ||

        (CU_add_test(test_basic_op, "transp", test_transp) == NULL) ||

        (CU_add_test(test_basic_op, "back_sub", test_back_sub) == NULL)) {

 

        CU_cleanup_registry();

        return CU_get_error();

    }

 

    CU_basic_set_mode(CU_BRM_VERBOSE);

    CU_basic_run_tests();

    CU_basic_show_failures(CU_get_failure_list());

 

    int failed_tests = CU_get_number_of_failures();

    CU_cleanup_registry();

 

    return (failed_tests > 0) ? 1 : 0;

}