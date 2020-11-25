#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int check(int nr){
        if(nr % 7 == 0)
                return 1;
        while(nr != 0){
                if(nr % 10 == 7)
                        return 1;
                nr = nr / 10;
        }
        return 0;
}

int main(int argc, char** argv){
        int p2a1[2], a1a2[2], a2a3[2], a3a1[2];
        pipe(p2a1);
        pipe(a1a2);
        pipe(a2a3);
        pipe(a3a1);
        if(fork() == 0){
                // A1
                int nr;
                close(p2a1[1]);
                close(a1a2[0]);
                close(a2a3[0]);
                close(a2a3[1]);
                close(a3a1[1]);
                read(p2a1[0], &nr, sizeof(int));
                close(p2a1[0]);
                nr++;
                int i;
                for(i=0; i<5; i++){
                        if(check(nr))
                                printf("A1: Boltz\n");
                        else
                                printf("A1: %i\n", nr);
                        write(a1a2[1], &nr, sizeof(int));
                        read(a3a1[0], &nr, sizeof(int));
                        nr++;
                }
                close(a1a2[1]);
                close(a3a1[0]);
                exit(0);
        }
        if(fork() == 0){
                // A2
                close(p2a1[1]);
                close(p2a1[1]);
                close(a3a1[0]);
                close(a3a1[1]);
                close(a1a2[1]);
                close(a2a3[0]);
                int i;
                int nr;
                for(i=0; i<5; i++){
                        read(a1a2[0], &nr, sizeof(int));
                        nr++;
                        if(check(nr))
                                printf("A2: Boltz\n");
                        else
                                printf("A2: %i\n", nr);
                        write(a2a3[1], &nr, sizeof(int));
                }
                close(a1a2[0]);
                close(a2a3[1]);
                exit(0);

        }
        if(fork() == 0){
                // A3
                close(p2a1[1]);
                close(p2a1[1]);
                close(a1a2[0]);
                close(a1a2[1]);
                close(a2a3[1]);
                close(a3a1[0]);
                int i;
                int nr;
                for(i=0; i<5; i++){
                        read(a2a3[0], &nr, sizeof(int));
                        nr++;
                        if(check(nr))
                                printf("A3: Boltz\n");
                        else
                                printf("A3: %i\n", nr);
                        write(a3a1[1], &nr, sizeof(int));
                }
                close(a2a3[0]);
                close(a3a1[1]);
                exit(0);
        }
        // parent
        int number;
        close(p2a1[0]);
        close(a1a2[0]);
        close(a1a2[1]);
        close(a2a3[0]);
        close(a2a3[1]);
        close(a3a1[0]);
        close(a3a1[1]);
        scanf("%i", &number);
        printf("Parent: %i\n", number);
        write(p2a1[1], &number, sizeof(int));
        close(p2a1[1]);
        wait(0);
        wait(0);
        wait(0);
        return 0;
}