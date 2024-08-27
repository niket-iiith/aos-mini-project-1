#include<fcntl.h>
#include<iostream>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<sys/stat.h>
#include<sys/types.h>
using namespace std;

#define CHUNK_SIZE 4096


//read input file from end of file to start of file, write output file in reverse manner character by character 
void read_write_reverse(int &in_file_id, int &out_file_id, int start, int end, int total)
{   

    if(end < 0 || start < 0 || end > total || start > total) {
        cout<<"Arguments Invalid: Out of Bounds"<<endl;
        exit(0);
    }

    char output_file_data[CHUNK_SIZE];

    int input_file_size;
    char input_file_data[CHUNK_SIZE];
    int input_bytes = CHUNK_SIZE;

    int progress = start;

    if(end-start > CHUNK_SIZE){
        end -= CHUNK_SIZE;
    }
    else{
        input_bytes = end-start;
        end = start;
        
        lseek(in_file_id, end, SEEK_SET);

        input_file_size = read(in_file_id, input_file_data, input_bytes);

        int j=0;
        for(int i = input_bytes-1; i>=0; i--){
            output_file_data[j++] = input_file_data[i];
        }       
            
        int output_file_size = write(out_file_id, output_file_data, input_bytes);

        progress += output_file_size;

        if(total != 0)
            cout<<"\rProgress: "<<(int)((progress / (float)total) * 100)<<flush;
        
        return;
    }

    lseek(in_file_id, end, SEEK_SET);

    input_file_size = read(in_file_id, input_file_data, input_bytes);
    
    while(end != start)
    {
        int j=0;
        for(int i = input_bytes-1; i>=0; i--){
            output_file_data[j++] = input_file_data[i];
        }       
            
        int output_file_size = write(out_file_id, output_file_data, input_bytes);
        progress += output_file_size;
        cout<<"\rProgress: "<<(int)((progress / (float)total) * 100)<<flush;
        if(end-start < CHUNK_SIZE)
        {
            input_bytes = end-start;
            end = start;

            lseek(in_file_id, end, SEEK_SET);
            input_file_size = read(in_file_id, input_file_data, input_bytes);

            int j=0;
            for(int i = input_bytes-1; i>=0; i--){
                output_file_data[j++] = input_file_data[i];
            }

            output_file_size = write(out_file_id, output_file_data, input_bytes);
            progress += output_file_size;
            cout<<"\rProgress: "<<(int)((progress / (float)total) * 100)<<flush;
            return;
        }
        else{
            end -= CHUNK_SIZE;
            lseek(in_file_id, end, SEEK_SET);
        }
        input_file_size = read(in_file_id, input_file_data, input_bytes);
    }
}   










//read input file from end of file to start of file, write output file in same manner character by character
void read_write_copy(int &in_file_id, int &out_file_id, int start, int end, int total)
{
    if(end < 0 || start < 0 || end > total || start > total) {
        cout<<"Arguments Invalid: Out of Bounds"<<endl;
        exit(0);
    }

    char output_file_data[CHUNK_SIZE];

    int input_file_size;
    char input_file_data[CHUNK_SIZE];
    int input_bytes = CHUNK_SIZE;

    int progress = start;
    if(end-start > CHUNK_SIZE){
        end -= CHUNK_SIZE;
    }
    else{
        input_bytes = end-start;
        end = start;

        lseek(in_file_id, end, SEEK_SET);

        input_file_size = read(in_file_id, input_file_data, input_bytes);

        int j=0;
        for(int i = 0; i<input_bytes; i++){
            output_file_data[j++] = input_file_data[i];
        }       
            
        int output_file_size = write(out_file_id, output_file_data, input_bytes);
        progress += output_file_size;

        if(total != 0)
            cout<<"\rProgress: "<<(int)((progress / (float)total) * 100)<<flush;

        return;
    }

    lseek(in_file_id, end, SEEK_SET);

    input_file_size = read(in_file_id, input_file_data, input_bytes);
    
    while(end != start)
    {
        int j=0;
        for(int i = 0; i<input_bytes; i++){
            output_file_data[j++] = input_file_data[i];
        }       
            
        int output_file_size = write(out_file_id, output_file_data, input_bytes);
        progress += output_file_size;
        cout<<"\rProgress: "<<(int)((progress / (float)total) * 100)<<flush;

        if(end-start < CHUNK_SIZE)
        {
            input_bytes = end-start;
            end = start;

            lseek(in_file_id, end, SEEK_SET);
            input_file_size = read(in_file_id, input_file_data, input_bytes);

            int j=0;
            for(int i = 0; i<input_bytes; i++){
                output_file_data[j++] = input_file_data[i];
            }

            output_file_size = write(out_file_id, output_file_data, input_bytes);
            progress += output_file_size;
            cout<<"\rProgress: "<<(int)((progress / (float)total) * 100)<<flush;
                
            return;
        }
        else{
            end -= CHUNK_SIZE;
            lseek(in_file_id, end, SEEK_SET);
        }

        input_file_size = read(in_file_id, input_file_data, input_bytes);
            
    }
}






int main(int argc, char* argv[])
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);


    string input_file_name_str = argv[1];
    const char* input_file_name = input_file_name_str.c_str();
    string flag = argv[2];

    int make_dir = mkdir("Assignment1", 0755);
    if(make_dir != 0 && errno != EEXIST){
        cout << "Error: unable to create directory" << endl;
        return 1;
    }

    int in_file_id;
    in_file_id = open(input_file_name, O_RDONLY);
    if (in_file_id < 0) {
        perror("in file");
        return -1;
    }

    struct stat total;
    if(stat(input_file_name, &total) == -1){
        cout<<"errno = "<<errno<<endl;
        perror("stat");
    }

    //for flag == i, create <output_file_name> = "i_<input_file_name>" 
    string output_file_name_str = "Assignment1/" + flag + "_" + input_file_name_str;
    const char* output_file_name = output_file_name_str.c_str();

    int out_file_id = open(output_file_name, O_CREAT|O_WRONLY|O_TRUNC, 0644);
    if (out_file_id < 0) {
        perror("out file");
        return -1;
    }


    if(stoi(flag) == 0)
    {
        //check whether file is empty
        if(total.st_size == 0){
            cout<<"Progress: 100";
        }

        read_write_reverse(in_file_id, out_file_id, 0, total.st_size, total.st_size);        

        if(errno != 0 && errno != 17){
            cout<<"errno"<<errno<<endl;
            perror("error description");
        }
    }

    else if(stoi(flag) == 1)
    {
        if(!argv[3] || !argv[4]){
            cout<<"Error: More arguments required for flag = 1"<<endl;
            return 1;
        }

        string first_index = argv[3];
        string second_index = argv[4];

        int first = stoi(first_index);
        int second = stoi(second_index);

        if(first > second){
            cout<<"Bad Inputs: Start Index greater than End Index"<<endl;
            return 0;
        }

        //check whether file is empty
        if(total.st_size == 0 && first == 0 && second == 0){
            cout<<"Bad Inputs"<<endl;
            return 0;
        }

        read_write_reverse(in_file_id, out_file_id, 0, first, total.st_size); 
        read_write_copy(in_file_id, out_file_id, first, second+1, total.st_size);
        read_write_reverse(in_file_id, out_file_id, second+1, total.st_size, total.st_size);

        if(errno != 0 && errno != 17){
            cout<<"errno = "<<errno<<endl;
            perror("error description =");
        }
    }

    else
    {
        cout<<"Bad Arguments: Flag not 0 or 1"<<endl;
    }

    cout<<endl;

    close(in_file_id);
    close(out_file_id);

    return 0;
}