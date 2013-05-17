#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef MAC
   #include <OpenCL/cl.h>
#else
   #include <CL/cl.h>
#endif

/*
 * @param num_entries: identifies the maximum number of platforms you’re interested in detecting.
 * @param platforms: is an array where the cl_platform_id structures that will be placed. Could be null.
 * @param num_platforms: is the number of platforms detected on the host. Could be null.
 * 
 * cl_int clGetPlatformIDs(cl_uint num_entries, cl_platform_id *platforms, cl_uint *num_platforms)
 *
 * Example:

    cl_platform_id *platforms;
    cl_uint num_platforms;
    
    clGetPlatformIDs(5, NULL, &num_platforms);
    platforms = (cl_platform_id*) malloc(sizeof(cl_platform_id) * num_platforms);
    clGetPlatformIDs(num_platforms, platforms, NULL);
 *
 * cl_int clGetPlatformInfo(cl_platform_id platform, cl_platform_info param_name, size_t param_value_size,
                            void *param_value, size_t *param_value_size_ret)
    PARAM NAMES:
        CL_PLATFORM_NAME
        CL_PLATFORM_VENDOR
        CL_PLATFORM_VERSION
        CL_PLATFORM_PROFILE
        CL_PLATFORM_EXTENSIONS
 */

void success_or_die(cl_int err, char* msg) {
    if(err < 0) {
        perror(msg);
        exit(1);
     }
}


int main() {

    /* Host/device data structures */
    cl_uint num_platforms;
    cl_platform_id* cl_platforms;
    
    cl_device_id *devices;
    cl_uint num_devices;
    cl_int k, err;
 
    
 
    /* Identifying and getting all platforms available */
    err = clGetPlatformIDs(1, NULL, &num_platforms);
    success_or_die(err, "Couldn't find any platforms");
    cl_platforms = (cl_platform_id*) malloc(sizeof(cl_platform_id) * num_platforms);
    clGetPlatformIDs(num_platforms, cl_platforms, NULL);
    
    // param_value and param_value_size
    char* data;
    size_t ext_size;
    
    printf("Number of platforms: %d\n", num_platforms);
    for (k = 0; k < num_platforms; k++ ) {
        
        
        /* Dislaying platforms information */
        
        printf("Platform <%d>\n", k);
        
        // CL_PLATFORM_NAME
        err = clGetPlatformInfo(cl_platforms[k], CL_PLATFORM_NAME, 0, NULL, &ext_size);
        success_or_die(err, "Couldn't read name data.");
        data = (char*) malloc(ext_size);
        clGetPlatformInfo(cl_platforms[k], CL_PLATFORM_NAME, ext_size, data, NULL);
        printf("Platform %d name: %s\n", k, data);
        free(data);
        
        // CL_PLATFORM_VENDOR
        err = clGetPlatformInfo(cl_platforms[k], CL_PLATFORM_VENDOR, 0, NULL, &ext_size);
        success_or_die(err, "Couldn't read vendor data.");
        data = (char*) malloc(ext_size);
        clGetPlatformInfo(cl_platforms[k], CL_PLATFORM_VENDOR, ext_size, data, NULL);
        printf("Platform %d vendor: %s\n", k, data);
        free(data);
        
        // CL_PLATFORM_VERSION
        err = clGetPlatformInfo(cl_platforms[k], CL_PLATFORM_VERSION, 0, NULL, &ext_size);
        success_or_die(err, "Couldn't read version data.");
        data = (char*) malloc(ext_size);
        clGetPlatformInfo(cl_platforms[k], CL_PLATFORM_VERSION, ext_size, data, NULL);
        printf("Platform %d version: %s\n", k, data);
        free(data);
        
        // CL_PLATFORM_PROFILE
        err = clGetPlatformInfo(cl_platforms[k], CL_PLATFORM_PROFILE, 0, NULL, &ext_size);
        success_or_die(err, "Couldn't read profile data.");
        data = (char*) malloc(ext_size);
        clGetPlatformInfo(cl_platforms[k], CL_PLATFORM_PROFILE, ext_size, data, NULL);
        free(data);
        printf("Platform %d profile: %s\n", k, data);
        
        // CL_PLATFORM_EXTENSIONS
        err = clGetPlatformInfo(cl_platforms[k], CL_PLATFORM_EXTENSIONS, 0, NULL, &ext_size);
        success_or_die(err, "Couldn't read extension data.");
        data = (char*) malloc(ext_size);
        clGetPlatformInfo(cl_platforms[k], CL_PLATFORM_EXTENSIONS, ext_size, data, NULL);
        printf("Platform %d supports extensions: %s\n", k, data);
        free(data);
        
        /*
         * Determine number of connected devices to this platform
         */
        err = clGetDeviceIDs(cl_platforms[k], CL_DEVICE_TYPE_ALL, 1, NULL, &num_devices);
        success_or_die(err, "Error Couldn't find any devices");
        
        /* Access connected devices */
        devices = (cl_device_id*) malloc(sizeof(cl_device_id) * num_devices);		
        clGetDeviceIDs(cl_platforms[k], CL_DEVICE_TYPE_ALL, num_devices, devices, NULL);				
        
        printf("Number of devices: %d\n", num_devices);
        
        /* Obtain data for each connected device */
        cl_int i;
        for(i=0; i < num_devices; i++) {
            
            err = clGetDeviceInfo(devices[i], CL_DEVICE_NAME, 0, NULL, &ext_size);			
            success_or_die(err, "Couldn't read device name data");
            data = (char * ) malloc(ext_size);
            clGetDeviceInfo(devices[i], CL_DEVICE_NAME, ext_size, data, NULL);			
            printf("CL_DEVICE_NAME: %s\n", data);
            free(data);
            
            err = clGetDeviceInfo(devices[i], CL_DEVICE_ADDRESS_BITS, 0, NULL, &ext_size);			
            success_or_die(err, "Couldn't read CL_DEVICE_ADDRESS_BITS");
            data = (char * ) malloc(ext_size);
            clGetDeviceInfo(devices[i], CL_DEVICE_ADDRESS_BITS, ext_size, data, NULL);			
            printf("CL_DEVICE_ADDRESS_BITS: %s\n", data);
            free(data);
            
            err = clGetDeviceInfo(devices[i], CL_DEVICE_EXTENSIONS, 0, NULL, &ext_size);			
            success_or_die(err, "Couldn't read CL_DEVICE_EXTENSIONS data");
            data = (char * ) malloc(ext_size);
            clGetDeviceInfo(devices[i], CL_DEVICE_EXTENSIONS, ext_size, data, NULL);			
            printf("CL_DEVICE_EXTENSIONS: %s\n\n", data);
            free(data);
        }
        
        free(devices);
    }
    free(cl_platforms);
    
    return 0;
}