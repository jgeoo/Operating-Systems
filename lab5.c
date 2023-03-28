#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
    struct stat file_stat;
    if(argc == 1){
        printf("Not multiple cmd agr");
        return EXIT_FAILURE;
    }else{
    for( int  i = 1; i < argc ;i++){
    lstat(argv[i],&file_stat);
    if(S_ISREG(file_stat.st_mode))
    {
        char c;
        printf("The file  ' %s ' is a regular file\n",argv[i]);
        printf("\nA) Regular file\n -n (file name) \n -d (dim/size) \n -h (number of hard links \n -m (time of last modif) \n -a (acces rights) \n -l (create a symbolic link)\n\n");
        scanf("%c",&c);
        switch (c)
        {
        case 'n':printf("File name:%s\n",argv[i]);
        case 'd':printf("The size of the file is %ld\n",file_stat.st_size);
            break;
        
        default:
            break;
        }
    }
    else if(S_ISLNK(file_stat.st_mode)){
        printf("The file ' %s ' a symbolic link\n",argv[i]);
    }
    else{
        printf("The %s is not a regular/symbolic file",argv[i]);
    }
    }
    }



    return 0;
}