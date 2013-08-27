/*

The MIT License (MIT)

Copyright (c) 2013 glframebuffer glframebuffer@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.



*/




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
