#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include <linux/input.h>

#define MOUSEFILE "/dev/input/mice"
#define IDLE_COUNT 30
int main()
{
    int fd;
    struct input_event ie;
	int read_out;
	int time_out = 0;
	int HDMI_ON = 1;
	

        if((fd = open(MOUSEFILE, O_RDONLY)) == -1) {
                perror(" ERROR: opening device failed\n");
                exit(EXIT_FAILURE);
        }
		int flags = fcntl(fd, F_GETFL, 0);
		fcntl(fd, F_SETFL, flags | O_NONBLOCK);

        while(1) {
		
		read_out = read(fd, &ie, sizeof(struct input_event));
		
		if(read_out == 3)
		{
		
                printf("time %ld.%06ld\ttype %d\tcode %d\tvalue %d\n",
                       ie.time.tv_sec, ie.time.tv_usec, ie.type,
			ie.code, ie.value);
			//set timeout to 0
			time_out = 0;
			
				if(HDMI_ON == 0)
				{
					system ("/opt/vc/bin/tvservice -p");
				}
			HDMI_ON = 1;
			
		}
		else
		{
			time_out++;
			if(time_out> IDLE_COUNT)
			{
				printf("sleep now..\n");
				//turn HDMI off				
				printf("power down  HDMI \n");
				system ("/opt/vc/bin/tvservice -o");
				HDMI_ON = 0;
				
			}
		
			
		}
		
		sleep(1);

        }

        return 0;
}
