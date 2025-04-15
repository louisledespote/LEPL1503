#include "real_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <arpa/inet.h>

#define FILENAME "datas/reals.dat"

/**
 * Calcule la moyenne des nombres réels stockés dans le fichier datas/reals.dat.
 * 
 * @return la moyenne des nombres réels
 */
#define FILENAME "datas/reals.dat"

float getAverage() {
    // on ouvre le ficher et on l'indentifie par un entier (int)
    int fd = open(FILENAME, O_RDONLY);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        return 0.0;
    }

    // On cree une struct stat file_stat qui permet de stocker des information sur le fichier 
    struct stat file_stat;
    if (fstat(fd, &file_stat) == -1) {
        perror("Erreur lors de la récupération des informations du fichier");
        close(fd);
        return 0.0;
    }

    
    float *data = (float *)mmap(NULL, file_stat.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) {
        perror("Erreur lors du mapping du fichier en mémoire");
        close(fd);
        return 0.0;
    }


    int num_elements = file_stat.st_size / sizeof(float);


    float sum = 0.0;
    for (int i = 0; i < num_elements; i++) {
        sum += data[i];
    }

    
    munmap(data, file_stat.st_size);
    close(fd);

    
    return sum / num_elements;
}

/**
 * Modifie la valeur d'un nombre réel stocké dans le fichier.
 * 
 * @param index l'index du nombre réel à modifier
 * @param new_value la nouvelle valeur du nombre réel
 * 
 * @return 0 si la modification a réussi, -1 sinon
 */
int changeReal(int index, float new_value) {
    // TODO
    
    return -1;
}