#include <errno.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/file.h"
#include "../headers/matrix.h"
#include "../headers/vector.h"

typedef struct {
    bool verbose;
    uint8_t nb_threads;
    FILE *output_stream;
    uint8_t deg;
    char *op;
    FILE *input_file_A;
    FILE *input_file_B;
} args_t;

void usage(char *prog_name) {
    fprintf(stderr, "UTILISATION :\n");
    fprintf(stderr, "   %s [OPTIONS] name_op input_file_A [input_file_B]\n",
            prog_name);
    fprintf(stderr, "   name_op : nom de l'opération à effectuer.\n");
    fprintf(stderr,
            "   input_file_A : chemin relatif ou absolu vers le fichier "
            "contenant le "
            "premier vecteur/matrice de l'opération, au format binaire.\n");
    fprintf(stderr,
            "   input_file_B : optionnel ; chemin relatif ou absolu vers "
            "le fichier contenant le second vecteur/matrice de "
            "l'opération s'il y en a deux, au format binaire.\n");
    fprintf(stderr, "   -v : autorise les messages de debug sur la sortie "
                    "d'erreur standard. Défaut : false.\n");
    fprintf(stderr,
            "   -n n_threads : spécifie le nombre de threads qui peuvent "
            "être utilisés. Défaut : 1.\n");
    fprintf(stderr,
            "   -f output_stream : chemin relatif ou absolu vers le "
            "fichier qui contiendra le vecteur ou la matrice résultante "
            "au format binaire. Défaut : stdout.\n");
    fprintf(stderr, "   -d degree (juste pour lstsq) : degré du polynôme "
                    "d'interpolation (uint8_t). Défaut : 1.\n");
}

int parse_args(args_t *args, int argc, char **argv) {
    // Valeurs par défaut
    args->verbose = false;
    args->nb_threads = 1;
    args->output_stream = stdout;
    args->deg = 1;
    args->op = NULL;
    args->input_file_A = NULL;
    args->input_file_B = NULL;

    int opt;
    while ((opt = getopt(argc, argv, "hn:vf:d:")) != -1) {
        switch (opt) {
        case 'n':
            args->nb_threads = atoi(optarg);
            if (args->nb_threads == 0) {
                fprintf(stderr,
                        "Le nombre de threads doit être supérieur à 0 !\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'v':
            args->verbose = true;
            break;
        case 'f':
            if (NULL == (args->output_stream = fopen(optarg, "w+"))) {
                fprintf(stderr,
                        "Impossible d'ouvrir le fichier de sortie %s : %s\n",
                        optarg, strerror(errno));
                exit(EXIT_FAILURE);
            }
            break;
        case 'd':
            args->deg = atoi(optarg);
            if (args->deg < 0) {
                fprintf(stderr,
                        "Le degré de l'approximation doit être positif !\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'h':
            usage(argv[0]);
            exit(EXIT_SUCCESS);
        default:
            usage(argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (argc == optind || argc == optind + 1) {
        fprintf(stderr, "Vous devez fournir une opération et les fichiers "
                        "d'instances correspondant.\n");
        exit(EXIT_FAILURE);
    }

    args->op = argv[optind++];
    if (NULL == (args->input_file_A = fopen(argv[optind++], "r"))) {
        fprintf(stderr,
                "Impossible d'ouvrir le premier fichier d'entrée %s : %s\n",
                argv[optind - 1], strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (strcmp(args->op, "add_v_v") == 0 || strcmp(args->op, "sub_v_v") == 0 ||
        strcmp(args->op, "dot_prod") == 0 || strcmp(args->op, "add_m_m") == 0 ||
        strcmp(args->op, "sub_m_m") == 0 || strcmp(args->op, "mult_m_v") == 0 ||
        strcmp(args->op, "mult_m_m") == 0 ||
        strcmp(args->op, "back_sub") == 0 || strcmp(args->op, "lstsq") == 0) {
        if (optind == argc) {
            fprintf(stderr,
                    "Vous devez fournir un second fichier d'instance pour "
                    "cette opération.\n");
            exit(EXIT_FAILURE);
        }
        if (NULL == (args->input_file_B = fopen(argv[optind], "r"))) {
            fprintf(stderr,
                    "Impossible d'ouvrir le second fichier d'entrée %s : %s\n",
                    argv[optind], strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}

int main(int argc, char **argv) {
    args_t *args = (args_t *)malloc(sizeof(args_t));
    if (args == NULL) {
        exit(EXIT_FAILURE);
    }
    parse_args(args, argc, argv);

    if (strcmp(args->op, "add_v_v") == 0) {
        vector *x = read_vector(args->input_file_A);
        if (args->verbose) {
            printf("vector x : \n");
            print_vector(x);
        }
        vector *y = read_vector(args->input_file_B);
        if (args->verbose) {
            printf("vector y : \n");
            print_vector(y);
        }
        vector *z = init_vector(x->m);
        add_v_v(x, y, z);
        if (args->output_stream == stdout) {
            print_vector(z);
        } else {
            write_vector(z, args->output_stream);
        }
        free_vector(x);
        free_vector(y);
        free_vector(z);
    } else if (strcmp(args->op, "sub_v_v") == 0) {
        vector *x = read_vector(args->input_file_A);
        if (args->verbose) {
            printf("vecteur x : \n");
            print_vector(x);
        }
        vector *y = read_vector(args->input_file_B);
        if (args->verbose) {
            printf("vecteur y : \n");
            print_vector(y);
        }
        vector *z = init_vector(x->m);
        sub_v_v(x, y, z);
        if (args->output_stream == stdout) {
            print_vector(z);
        } else {
            write_vector(z, args->output_stream);
        }
        free_vector(x);
        free_vector(y);
        free_vector(z);
    } else if (strcmp(args->op, "add_m_m") == 0) {
        matrix *A = read_matrix(args->input_file_A);
        if (args->verbose) {
            printf("matrix A : \n");
            print_matrix(A);
        }
        matrix *B = read_matrix(args->input_file_B);
        if (args->verbose) {
            printf("matrix B : \n");
            print_matrix(B);
        }
        matrix *C = init_matrix(A->m, A->n);
        add_m_m(A, B, C);
        if (args->output_stream == stdout) {
            print_matrix(C);
        } else {
            write_matrix(C, args->output_stream);
        }
        free_matrix(A);
        free_matrix(B);
        free_matrix(C);
    } else if (strcmp(args->op, "sub_m_m") == 0) {
        matrix *A = read_matrix(args->input_file_A);
        if (args->verbose) {
            printf("matrix A : \n");
            print_matrix(A);
        }
        matrix *B = read_matrix(args->input_file_B);
        if (args->verbose) {
            printf("matrix B : \n");
            print_matrix(B);
        }
        matrix *C = init_matrix(A->m, A->n);
        sub_m_m(A, B, C);
        if (args->output_stream == stdout) {
            print_matrix(C);
        } else {
            write_matrix(C, args->output_stream);
        }
        free_matrix(A);
        free_matrix(B);
        free_matrix(C);
    } else if (strcmp(args->op, "dot_prod") == 0) {
        vector *x = read_vector(args->input_file_A);
        if (args->verbose) {
            printf("vecteur x : \n");
            print_vector(x);
        }
        vector *y = read_vector(args->input_file_B);
        if (args->verbose) {
            printf("vecteur y : \n");
            print_vector(y);
        }
        double z = 0;
        z = dot_prod(x,y);
        if (args->output_stream == stdout) {
            printf("%lf\n", z);
        } else {
            write_double(z, args->output_stream);
        }
        free_vector(x);
        free_vector(y);
    } else if (strcmp(args->op, "mult_m_v") == 0) {
        matrix *A = read_matrix(args->input_file_A);
        if (args->verbose) {
            printf("matrix A : \n");
            print_matrix(A);
        }
        vector *x = read_vector(args->input_file_B);
        if (args->verbose) {
            printf("vecteur x : \n");
            print_vector(x);
        }
        vector *y = init_vector(A->m);
        mult_m_v(A, x, y);
        if (args->output_stream == stdout) {
            print_vector(y);
        } else {
            write_vector(y, args->output_stream);
        }
        free_matrix(A);
        free_vector(x);
        free_vector(y);
    } else if (strcmp(args->op, "mult_m_m") == 0) {
        matrix *A = read_matrix(args->input_file_A);
        if (args->verbose) {
            printf("matrix A : \n");
            print_matrix(A);
        }
        matrix *B = read_matrix(args->input_file_B);
        if (args->verbose) {
            printf("matrix B : \n");
            print_matrix(B);
        }
        matrix *C = init_matrix(A->m, B->n);
        mult_m_m(A, B, C);
        if (args->output_stream == stdout) {
            print_matrix(C);
        } else {
            write_matrix(C, args->output_stream);
        }
        free_matrix(A);
        free_matrix(B);
        free_matrix(C);
    }
    else if (strcmp(args->op, "back_sub") == 0) {
        matrix *U = read_matrix(args->input_file_A);
        if (args->verbose) {
            printf("matrix U : \n");
            print_matrix(U);
        }
        vector *b = read_vector(args->input_file_B);
        if (args->verbose) {
            printf("vecteur b : \n");
            print_vector(b);
        }
        vector *x = init_vector(b->m);
        mult_m_v(U, b, x);
        if (args->output_stream == stdout) {
            print_vector(x);
        } else {
            write_vector(x, args->output_stream);
        }
        free_matrix(U);
        free_vector(x);
        free_vector(b);
    } else if (strcmp(args->op, "lstsq") == 0) {
        matrix *A = read_matrix(args->input_file_A);
        if (args->verbose) {
            printf("Matrix A : \n");
            print_matrix(A);
        }
        vector *b = read_vector(args->input_file_B);
        if (args->verbose) {
            printf("vecteur b : \n");
            print_vector(b);
        }
        vector *x = init_vector(b->m);
        lstsq(A, b, x);
        if (args->output_stream == stdout) {
            print_vector(x);
        } else {
            write_vector(x, args->output_stream);
        }
        free_vector(x);
        free_matrix(A);
        free_vector(b);
    } else {
        fprintf(stderr, "Cette opération n'est pas implémentée...\n");
        exit(EXIT_FAILURE);
    }

    fclose(args->input_file_A);
    if (strcmp(args->op, "add_v_v") == 0 || strcmp(args->op, "sub_v_v") == 0 ||
        strcmp(args->op, "dot_prod") == 0 || strcmp(args->op, "add_m_m") == 0 ||
        strcmp(args->op, "sub_m_m") == 0 || strcmp(args->op, "mult_m_v") == 0 ||
        strcmp(args->op, "mult_m_m") == 0 ||
        strcmp(args->op, "back_sub") == 0 || strcmp(args->op, "lstsq") == 0) {
        fclose(args->input_file_B);
    }
    if (args->output_stream != stdout) {
        fclose(args->output_stream);
    }
    
    exit(EXIT_SUCCESS);
}