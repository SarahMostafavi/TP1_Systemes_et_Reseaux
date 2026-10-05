#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>


int main(){
	int fd;
	struct stat st;
	char *data;


	//Ouverture du fichier
	fd = open("test.txt", O_RDWR);
	if (fd == -1){
		perror("open");
		exit(1);
	}
	
	//Récupération de la taille du fichier
	if (fstat(fd, &st) == -1){
		perror("stat");
		exit(1);
	}
	
	//Mapp du fichier
	data = mmap(NULL, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	
	if (data == MAP_FAILED){
		perror("mmap");
		exit(1);
	}

	//Affichage avant inversion
        printf("\nFichier avant inversion :\n");
        pid_t pid = fork();
        if (pid == 0){
		execlp("cat", "cat", "test.txt", NULL);
                perror("exec");
                exit(1);
        }else{
                wait(NULL);
        }
		
	//Inversion des octets du fichier
	for (int i = 0; i < st.st_size/2; i++){
		char inter = data[i];
		data[i] = data[st.st_size - 1 - i];
		data[st.st_size - 1 - i] = inter;
	}

	//Affichage apres inversion
	printf("\nFichier apres inversion :\n");
	pid = fork();
	if (pid == 0){
		execlp("cat", "cat", "test.txt", NULL);
		perror("exec");
		exit(1);
	}else{
		wait(NULL);
	}
	
	//Fin du mapping
	close(fd);
	munmap(data, st.st_size);
	
	return  0;
}
	
