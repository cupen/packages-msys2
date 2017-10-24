#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG  0

// bool, you're worth it.
#define bool   char
#define True   1
#define False  0

void print_help(){
    char* help_text[] = {
        "help:",
        "  It's just a fake sudo.",
        "  And it doesn't working as sudo at all, but just execute you command."
    };
    size_t arr_size = 3;
    for (int i = 0, length = arr_size; i < length; i++){
        printf("%s\n", help_text[i]);
    }
}


char* create_command(const int argc, char** argv, const size_t max_size){
    char* cmd = (char*)malloc(max_size);
    memset(cmd, ' ', max_size);
    int offset = 0;
    char* cmd_idx = NULL;
    bool is_skipping = True;
    for(int i=1; i < argc; i++){
        char* arg = argv[i];
        size_t arg_size = strlen(arg);

        // skipping args of sudo.
        if (arg[0] == '-' && is_skipping){
            continue;
        }
        // end skipping.
        is_skipping = False;

        cmd_idx = cmd + offset;
        offset += arg_size + 1;
        size_t cp_size =  (offset <= max_size) ? (arg_size) : (arg_size - (max_size - offset));
        memcpy(cmd_idx, arg, cp_size);
        if (DEBUG) printf("i=%d offset=%d arg=%s arg_size=%d cp_size=%d tmp_cmd=%s\n", i, offset, arg, arg_size, cp_size, cmd);
    }
    return cmd;
}


int main(int argc, char** argv){
    if (argc == 1){
        print_help();
        return 0;
    }
    
    char* cmd = create_command(argc, argv, 512);
    if (DEBUG) printf("cmd=%s\n", cmd);
    return system(cmd);
}
