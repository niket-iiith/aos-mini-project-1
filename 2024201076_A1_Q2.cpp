#include<iostream>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
using namespace std;

#define CHUNK_SIZE 4096


int read_input_output(int &in_file_id, int &out_file_id, int start, int end)
{
    int bytes_read = 0;

    int input_file_size;
    char input_file_data[CHUNK_SIZE];
    int input_bytes = CHUNK_SIZE;

    int output_file_size;
    char output_file_data[CHUNK_SIZE];
    int output_bytes = CHUNK_SIZE;

    if(end-start > CHUNK_SIZE){
        end -= CHUNK_SIZE;
    }
    else{
        input_bytes = end-start+1;
        output_bytes = end-start+1;
        end = start;

        lseek(in_file_id, end, SEEK_SET);
        lseek(out_file_id, start, SEEK_SET);

        input_file_size = read(in_file_id, input_file_data, input_bytes);
        output_file_size = read(out_file_id, output_file_data, output_bytes);

        int j = input_bytes-1;
        for(int i = 0; i<input_bytes; i++){
            if(output_file_data[j--] == input_file_data[i])
                bytes_read++;
        }       
        
        return bytes_read;
    }

    lseek(in_file_id, end, SEEK_SET);
    lseek(out_file_id, start, SEEK_SET);

    input_file_size = read(in_file_id, input_file_data, input_bytes);
    output_file_size = read(out_file_id, output_file_data, output_bytes);
    
    while(end != start)
    {
        int j = input_bytes-1;
        for(int i = 0; i<input_bytes; i++){
            if(output_file_data[j--] == input_file_data[i])
                bytes_read++;
        }        
        

        if(end-start < CHUNK_SIZE)
        {
            input_bytes = end-start+1;
            output_bytes = end-start+1;
            end = start;

            lseek(in_file_id, end, SEEK_SET);
            lseek(out_file_id, start, SEEK_SET);

            input_file_size = read(in_file_id, input_file_data, input_bytes);
            output_file_size = read(out_file_id, output_file_data, output_bytes);

            int j = input_bytes-1;
            for(int i = 0; i<input_bytes; i++){
                if(output_file_data[j--] == input_file_data[i])
                    bytes_read++;
            } 
                
            return bytes_read;
        }
        else{
            end -= CHUNK_SIZE;
            start += CHUNK_SIZE;
            lseek(in_file_id, end, SEEK_SET);
            lseek(out_file_id, start, SEEK_SET);
        }

        input_file_size = read(in_file_id, input_file_data, input_bytes);
        output_file_size = read(out_file_id, output_file_data, output_bytes);

    }

    return bytes_read;
    
}


int main(int argc, char* argv[]){
    
    if(argc != 4) 
        cout<<"Wrong Inputs: Please specify in this order $ ./a.out <newfile_path> <oldfile_path> <directory_path>";

    string newfile_path_str = argv[1];
    string oldfile_path_str = argv[2];
    string directory_path_str = argv[3];

    const char* newfile_path = newfile_path_str.c_str();
    const char* oldfile_path = oldfile_path_str.c_str();
    const char* directory_path = directory_path_str.c_str();

    
    struct stat n_info;
    if(stat(newfile_path, &n_info) < 0)
        cout<<"Cant access new file"<<endl;
    
    struct stat o_info;
    if(stat(oldfile_path, &o_info) < 0)
        cout<<"Cant access old file"<<endl;

    //to check whether directory exists or not
    struct stat d_info;
    if(stat(directory_path, &d_info) != 0)
        cout<<"Cant access directory"<<endl;
    else if(d_info.st_mode & S_IFDIR)
        cout<<"\nDirectory is created: Yes"<<endl;
    else
        cout<<"The given path is not a directory"<<endl;

    


    //to check whether the contents of the file are reversed or not
    int in_file_id = open(newfile_path, O_RDONLY);
    int out_file_id = open(oldfile_path, O_RDONLY);

    int bytes_read = read_input_output(in_file_id, out_file_id, 0, o_info.st_size-1);

    if(bytes_read == n_info.st_size)
        cout<<"Whether file contents are reversed in newfile: Yes\n";




    //to check whether both files are of same size or not
    if(n_info.st_size == o_info.st_size)
        cout<<"Both Files Sizes are Same : Yes\n\n\n";

    

    //to check directory permissions
    int d_mode = d_info.st_mode;
    if(d_mode & 0400)
        cout<<"User has read permissions on Directory: Yes"<<endl;
    else    
        cout<<"User has read permissions on Directory: No"<<endl;

    if(d_mode & 0200)
        cout<<"User has write permissions on Directory: Yes"<<endl;
    else    
        cout<<"User has write permissions on Directory: No"<<endl;

    if(d_mode & 0100)
        cout<<"User has execute permissions on Directory: Yes"<<endl;
    else    
        cout<<"User has execute permissions on Directory: No"<<endl;

    if(d_mode & 0040)
        cout<<"Group has read permissions on Directory: Yes"<<endl;
    else    
        cout<<"Group has read permissions on Directory: No"<<endl;

    if(d_mode & 0020)
        cout<<"Group has write permissions on Directory: Yes"<<endl;
    else    
        cout<<"Group has write permissions on Directory: No"<<endl;

    if(d_mode & 0100)
        cout<<"Group has execute permissions on Directory: Yes"<<endl;
    else    
        cout<<"Group has execute permissions on Directory: No"<<endl;

    if(d_mode & 0004)
        cout<<"Others has read permissions on Directory: Yes"<<endl;
    else    
        cout<<"Others has read permissions on Directory: No"<<endl;

    if(d_mode & 0002)
        cout<<"Others has write permissions on Directory: Yes"<<endl;
    else    
        cout<<"Others has write permissions on Directory: No"<<endl;

    if(d_mode & 0100)
        cout<<"Others has execute permissions on Directory: Yes"<<endl<<endl;
    else    
        cout<<"Others has execute permissions on Directory: No"<<endl<<endl;




    //to check newfile permissions
    int n_mode = n_info.st_mode;
    if(n_mode & 0400)
        cout<<"User has read permissions on newfile: Yes"<<endl;
    else    
        cout<<"User has read permissions on newfile: No"<<endl;

    if(n_mode & 0200)
        cout<<"User has write permissions on newfile: Yes"<<endl;
    else    
        cout<<"User has write permissions on newfile: No"<<endl;

    if(n_mode & 0100)
        cout<<"User has execute permissions on newfile: Yes"<<endl;
    else    
        cout<<"User has execute permissions on newfile: No"<<endl;

    if(n_mode & 0040)
        cout<<"Group has read permissions on newfile: Yes"<<endl;
    else    
        cout<<"Group has read permissions on newfile: No"<<endl;

    if(n_mode & 0020)
        cout<<"Group has write permissions on newfile: Yes"<<endl;
    else    
        cout<<"Group has write permissions on newfile: No"<<endl;

    if(n_mode & 0100)
        cout<<"Group has execute permissions on newfile: Yes"<<endl;
    else    
        cout<<"Group has execute permissions on newfile: No"<<endl;

    if(n_mode & 0004)
        cout<<"Others has read permissions on newfile: Yes"<<endl;
    else    
        cout<<"Others has read permissions on newfile: No"<<endl;

    if(n_mode & 0002)
        cout<<"Others has write permissions on newfile: Yes"<<endl;
    else    
        cout<<"Others has write permissions on newfile: No"<<endl;

    if(n_mode & 0100)
        cout<<"Others has execute permissions on newfile: Yes"<<endl<<endl;
    else    
        cout<<"Others has execute permissions on newfile: No"<<endl<<endl;




    //to check oldfile permissions
    int o_mode = n_info.st_mode;
    if(o_mode & 0400)
        cout<<"User has read permissions on oldfile: Yes"<<endl;
    else    
        cout<<"User has read permissions on oldfile: No"<<endl;

    if(o_mode & 0200)
        cout<<"User has write permissions on oldfile: Yes"<<endl;
    else    
        cout<<"User has write permissions on oldfile: No"<<endl;

    if(o_mode & 0100)
        cout<<"User has execute permissions on oldfile: Yes"<<endl;
    else    
        cout<<"User has execute permissions on oldfile: No"<<endl;

    if(o_mode & 0040)
        cout<<"Group has read permissions on oldfile: Yes"<<endl;
    else    
        cout<<"Group has read permissions on oldfile: No"<<endl;

    if(o_mode & 0020)
        cout<<"Group has write permissions on oldfile: Yes"<<endl;
    else    
        cout<<"Group has write permissions on oldfile: No"<<endl;

    if(o_mode & 0100)
        cout<<"Group has execute permissions on oldfile: Yes"<<endl;
    else    
        cout<<"Group has execute permissions on oldfile: No"<<endl;

    if(o_mode & 0004)
        cout<<"Others has read permissions on oldfile: Yes"<<endl;
    else    
        cout<<"Others has read permissions on oldfile: No"<<endl;

    if(o_mode & 0002)
        cout<<"Others has write permissions on oldfile: Yes"<<endl;
    else    
        cout<<"Others has write permissions on oldfile: No"<<endl;

    if(o_mode & 0100)
        cout<<"Others has execute permissions on oldfile: Yes"<<endl<<endl;
    else    
        cout<<"Others has execute permissions on oldfile: No"<<endl<<endl;


    
    return 0;
}