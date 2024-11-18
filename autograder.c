#include "include/utility.h"

void print_status() {

     //TODO: write the status of each executable file to autograder.out. Your output should align with expected.out 
    FILE *file;
    file = fopen("autograder.out", "w");

    if (!file) { // if file is null or there is some problem this is an error check!
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAX_EXE; i++) {
        fprintf(file, "%s ", strrchr(os.paths[i], '/') + 1);
        for (int j = 0; j < MAX_PI; j++){
            if (os.pi[i][j] != 0) {
                if(os.status[i][j] == 0) {
                    fprintf(file, "%d(correct) ", os.pi[i][j]); // pi is input paramaters when running ./autograder
                    
                }
                else if (os.status[i][j] == 1) {
                    fprintf(file, "%d(incorrect) ", os.pi[i][j]);
                }
                else {
                    fprintf(file, "%d(crash) ", os.pi[i][j]);
                }

            }
        }
        fprintf(file, "\n");
    }
    fclose(file);
}


int main(int argc, char *argv[]) {
    // the path stores each executable file (submissions. txt)
    // status has correct, etlc.

    if (argc < 2) {
        printf("Usage: %s <batch> <p1> <p2> ... <pn>\n", argv[0]);
        return 1;
    }

    // Convert the first command-line argument to an integer to determine the batch size
    int batch_size = atoi(argv[1]);


    // write the file paths from the "solutions" directory into the submissions.txt file
    write_filepath_to_submissions("solutions", "submissions.txt");

    FILE *file;
    file = fopen("submissions.txt", "r");
    if (!file) { // file null error check
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < MAX_EXE; i++){ // sets os.pi
        for(int j = 0; j < argc - 2; ++j){
            os.pi[i][j] = atoi(argv[2 + j]);
        }
    }
    for(int i = 0; i < MAX_EXE; ++i) { // sets each executable name
        fgets(os.paths[i], 256, file);
        size_t len = strlen(os.paths[i]);
        if (os.paths[i][len - 1] == '\n') {  // Check if the last character is '\n'
            os.paths[i][len - 1] = '\0';  // Replace it with the null terminator
        } 
    }

    int L = argc - 2; //L = length of [p1,p2,...,pn]
    pid_t pid_list[batch_size];  // store child pids
    for (int i = 0; i < L; ++i) {
        int complete_executables = 0;
        while (complete_executables < MAX_EXE) { // intermediate is fixed batch size
            for (int j = 0; j < batch_size; ++j) { 
                pid_t pid = fork();
                if (pid < 0) { // error case
                    perror("Fork Failed");
                    exit(EXIT_FAILURE); 
                } else if (pid == 0) { // child case
                    char* slash = strrchr(os.paths[complete_executables+j], '/');
                    char* filename = slash+1;
                    if (execl(os.paths[complete_executables+j], filename, argv[i+2], NULL) == -1) {
                        perror("execv failed");  
                        exit(1); 
                    }
                } else { // parent process
                    pid_list[j] = pid;
                }
            }
            
            int finished = 0;
            while (finished < batch_size) {
                int status;
                for (int j = 0; j < batch_size; ++j) {
                    // wait for the excecutables to finish and determine the cases
                    pid_t pid = waitpid(-1, &status, 0);
                    int index;
                    for(int b = 0; b<batch_size; b++){
                        if (pid == pid_list[b]){
                            index = complete_executables+b;
                            break;
                        }
                    }
                    if (WIFEXITED(status)){
                        os.status[index][i] = WEXITSTATUS(status);
                    } else if (WIFSIGNALED(status)){
                        os.status[index][i] = WTERMSIG(status);
                    } 
                    os.pi[index][i] = atoi(argv[i+2]);
                    }
                finished++;
            }
            complete_executables += batch_size;
        }
    }
    print_status();    
    fclose(file);
    return 0;
}     