#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define SIZE 4096
// Data
int global_init = 10;  
// BSS
int global_bss;        

void afficher_segments() {
     // Stack
    int local_var = 5; 
      // Str
    char *str = "Bonjour";  
    // Heap
    int *heap = malloc(sizeof(int)); 

    void *mmap_zone = mmap(NULL, SIZE,
                           PROT_READ | PROT_WRITE,
                           MAP_PRIVATE | MAP_ANONYMOUS,
                           -1, 0);

    printf("Data           : %p\n", &global_init);
    printf("BSS            : %p\n", &global_bss);
    printf("Str            : %p\n", str);
    printf("Heap           : %p\n", heap);
    printf("Stack          : %p\n", &local_var);
    printf("Main Function  : %p\n", afficher_segments);
    printf("LibC Function  : %p\n", printf);
    printf("Mmap           : %p\n", mmap_zone);

    free(heap);
    munmap(mmap_zone, SIZE);
}

int main() {
    afficher_segments();
    pid_t pid = fork();

    if (pid == 0) {
        // processus enfant
        char pid_str[20];
        sprintf(pid_str, "%d", getppid());

        execlp("pmap", "pmap", "-X", pid_str, NULL);

        perror("execlp"); 
        exit(1);
    } else {
        // processus parent
        wait(NULL);
    }

    return 0;
}















