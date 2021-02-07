#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

// Check validity of the URL

int checkValidity(char *url) {

    // Command params

    char command[] = "wget ";
    char options[] = "--spider ";

    // Setup the command

    int exec_len = strlen(command) + strlen(options) + strlen(url) + 1;
    char* exec = (char*)calloc(exec_len, sizeof(char));
    strcat(exec,command);
    strcat(exec,options);
    strcat(exec,url);

    // Check validity

    return system(exec) ? 0 : 1;
}

// To fetch a webpage 

void getPage(char *url, char* filename) {

    // Command params

    char command[] = "wget ";
    char options[] = "-O ";

    // Setup the command

    int exec_len = strlen(command) + strlen(options) + strlen(filename) + strlen(url) + 1;
    char* exec = (char*)calloc(exec_len, sizeof(char));
    strcat(exec, command);
    strcat(exec, options);
    strcat(exec, filename);
    strcat(exec, " ");
    strcat(exec, url);

    //Run wget

    system(exec);
    system("clear");
}

// To install any package

void installPackage(char* package) {

    // Command params

    char command[] = "apt-get install ";

     // Setup the command
     
    int exec_len = strlen(command) + strlen(package) + 1;
    char* exec = (char*)calloc(exec_len, sizeof(char));
    strcat(exec,command);
    strcat(exec,package);

    //Install package

    system(exec);
    system("clear");
}

// To calculate the size of the file

int getSize(char* filename) {

    struct stat st;
    stat(filename, &st);

    return st.st_size;
}

// Generate new file name

char* generateFileName(int file_no) {

    // File name prefix and extension

    char prefix[] = "./temp";
    char extension[] = ".txt";

    // Convert file number to string

    char s_file_no[10];
    sprintf(s_file_no, "%d", file_no);

    // Create file name

    int filename_len = strlen(prefix) + strlen(s_file_no) + strlen(extension) + 1;
    char* filename = (char*)calloc(filename_len, sizeof(char));
    strcat(filename, prefix);
    strcat(filename, s_file_no);
    strcat(filename, extension);

    return filename;

}

// To read the data to the file

char * readFile(char* filename) {

    // Contains the data read from the file

    char* res = (char*)calloc(getSize(filename), sizeof(char));

    // Open the file

    FILE *fp = fopen(filename, "r");

    // Read the file till EOF hasn't been reached.

    while(!feof(fp)) {

        char* buff = (char*)calloc(100, sizeof(char));

        fread(buff, sizeof(char), 100, fp);
        strcat(res, buff);

        free(buff);

    }

    //printf("FILE DATA:\n %s", res);

    fclose(fp);

    return res;

}

// Driver code 

int main()
{
    // Initial variables

    char seed[] = "https://mittalvaibhav1.github.io/foodelico/login.html";
    int file_no = 0;

    // To install wget

    installPackage("wget");

    // Check validity

    if(!checkValidity(seed)) {
        printf("Invalid URL");
        return 0;
    }

    // Generate the new filename

    char* filename = generateFileName(file_no);

    // Download the page

    getPage(seed, filename);

    // Display the downloaded page on terminal

    char* result = readFile(filename);

    printf("%s", result);

    return 0;
}