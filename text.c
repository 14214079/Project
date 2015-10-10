/* My text editor will write, read, append, undo, replace it will have function to perform above operartion and it will specify line no, no of data in line. 


*/







#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


typedef struct text{
	
	int lineno;
	char *linedata;
	struct text *next;
	
}text;
typedef struct list {
	text *head, *tail;

}list;
void init(list *l)
{
	int no_of_line = 0;
	l->head = NULL;
	l->tail = NULL;
	
}

int main(int argc, char *argv[])
{
	
	
// Read file	
	int fd;
	int x, i;
	char a[4];
	fd = open(argv[1], O_RDONLY); 
	if(fd == -1) {
		printf("open failed\n");
		return 1;
	}
	while((x = read(fd, a, 4)))
		for(i = 0; i < x; i++)
			putchar(a[i]);
	close(fd);
	//write in a file
	
	
	return 0;


}
