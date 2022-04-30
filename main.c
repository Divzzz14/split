//************************split function***************************************//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void bytes_split (uintmax_t n_bytes, char *buf, size_t bufsize);

char split_type[2];
char bytes[10];
int byte_size;
int main()
{
   char file_directory[100];
   char get_input[100];
   FILE *fptr; // file pointer
   
   printf("Enter the file directory of the string : ");
   scanf("%[^\n]s",file_directory); //to get the directory

   fptr = fopen("file_directory","r");

   if(fptr==NULL)
   {
     printf("Path doesn't exist ");
   }

   scanf("%[^\n]s",get_input);
  
   memcpy(split_type,&get_input[6],2);
   memcpy(bytes,&get_input[9],(strlen(get_input)-8));

   fseek(fptr, 0L, SEEK_END);
      // calculating the size of the file
   long int file_size = ftell(fptr);
   byte_size = bytes[6]+'0'-'0'; // to get integer value
   if(get_input[9]=='K') // to calculate bytes
   {
     byte_size = byte_size*1000;
   }

   if(get_input[7]=='s')
   {
     bytes_split(byte_size,fptr,file_size);
   }
   return 0;
}


static void
bytes_split (uintmax_t n_bytes, char *buf, size_t bufsize)
{
  size_t n_read;
  bool new_file_flag = true;
  size_t to_read;
  uintmax_t to_write = n_bytes;
  char *bp_out;

  do
    {
      n_read = full_read (STDIN_FILENO, buf, bufsize);
      if (n_read < bufsize && errno)
        error (EXIT_FAILURE, errno, "%s", infile);
      bp_out = buf;
      to_read = n_read;
      while (true)
        {
          if (to_read < to_write)
            {
              if (to_read)	/* do not write 0 bytes! */
                {
                  cwrite (new_file_flag, bp_out, to_read);
                  to_write -= to_read;
                  new_file_flag = false;
                }
              break;
            }
          else
            {
              size_t w = to_write;
              cwrite (new_file_flag, bp_out, w);
              bp_out += w;
              to_read -= w;
              new_file_flag = true;
              to_write = n_bytes;
            }
        }
    }
  while (n_read == bufsize);
}
