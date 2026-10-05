#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>


// Ouverture du fichier
int open_file(const char *filename) {
    int fd = open(filename, O_RDWR);

    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    return fd;
}


// Récupération de la taille du fichier
struct stat get_file_info(int fd) {
    struct stat st;

    if (fstat(fd, &st) == -1) {
        perror("fstat");
        exit(EXIT_FAILURE);
    }

    return st;
}


// Mappage du fichier
char *map_file(int fd, off_t size) {
    char *data = mmap(NULL, size,
                      PROT_READ | PROT_WRITE,
                      MAP_SHARED, fd, 0);

    if (data == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    return data;
}


// Affichage du fichier
void display_file(const char *filename, const char *message) {
    printf("\n%s\n", message);

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        execlp("cat", "cat", filename, NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    if (waitpid(pid, NULL, 0) == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }
}


// Inversion des octets du fichier
void reverse_file(char *data, off_t size) {
    for (int i = 0; i < size / 2; i++) {
        char inter = data[i];
        data[i] = data[size - 1 - i];
        data[size - 1 - i] = inter;
    }
}


int main() {
    const char *filename = "test.txt";
    int fd;
    struct stat st;
    char *data;

    // Ouverture du fichier
    fd = open_file(filename);

    // Récupération de la taille du fichier
    st = get_file_info(fd);

    // Mappage du fichier
    data = map_file(fd, st.st_size);

    // Affichage avant inversion
    display_file(filename, "Fichier avant inversion :");

    // Inversion des octets du fichier
    reverse_file(data, st.st_size);

    // Affichage après inversion
    display_file(filename, "Fichier apres inversion :");

    // Fin du mapping
    if (munmap(data, st.st_size) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    if (close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
