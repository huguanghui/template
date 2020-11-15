#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"


int main(int argc, const char* argv[])
{
	int fd = open("/dev/drv_ctrl", 0);
	if (fd > 0)
	{
		//gpio_groupbit_info info;
		//memset(&info, 0, sizeof(gpio_groupbit_info));
		//info.groupnumber = 1;
		//info.bitnumber = 27;
		//info.value = 1;
		ioctl(fd, CTRL_TEST, (void*)NULL);
		close(fd);
	}
    printf("HGH-TEST[%s %d]\n", __FUNCTION__, __LINE__);
	return 0;
}
