#ifndef MANTLE_H_
#define MANTLE_H_ 1

#ifdef __cplusplus
extern "C" {
#endif

#pragma once

typedef char GR_CHAR;
typedef unsigned int GR_UINT;
typedef unsigned __int32 GR_UINT32;
typedef unsigned __int64 GR_UINT64;
typedef unsigned long long GR_SIZE;
typedef unsigned long long GR_GPU_SIZE;
typedef signed int GR_ENUM;
typedef void GR_VOID;
typedef unsigned int GR_FLAGS;
typedef unsigned int GR_BOOL;

#define GR_VERSION_1_0 1

#define GR_MAKE_VERSION(major, minor, patch) \
    (((major) << 22) | ((minor) << 12) | (patch))

#define GR_API_VERSION GR_MAKE_VERSION(0, 24, 5)

#define GR_VERSION_MAJOR(version) ((GR_UINT32)(version) >> 22)
#define GR_VERSION_MINOR(version) (((GR_UINT32)(version) >> 12) & 0x3ff)
#define GR_VERSION_PATCH(version) ((GR_UINT32)(version) & 0xfff)

#define GR_NULL_HANDLE 0

#define GR_HANDLE(object) typedef struct object##_T* object;

GR_HANDLE(GR_DEVICE)
GR_HANDLE(GR_PHYSICAL_GPU)

#define GR_STDCALL __stdcall
#define GR_MAX_PHYSICAL_GPUS 4
#define GR_MAX_PHYSICAL_GPU_NAME 256

typedef enum _GR_RESULT{
	GR_SUCCESS = 0x10000,
	GR_UNSUPPORTED,
	GR_NOT_READY,
	GR_TIMEOUT,
	GR_EVENT_SET,
	GR_EVENT_RESET,
	GR_ERROR_UNKNOWN = 0x11000,
	GR_ERROR_UNAVAILABLE,
	GR_ERROR_INITIALIZATION_FAILED,
	GR_ERROR_OUT_OF_MEMORY,
	GR_ERROR_OUT_OF_GPU_MEMORY,
	GR_ERROR_DEVICE_LOST,
	GR_ERROR_INVALID_POINTER,
	GR_ERROR_INVALID_VALUE,
	GR_ERROR_INVALID_HANDLE,
	GR_ERROR_INVALID_ORDINAL,
	GR_ERROR_INVALID_MEMORY_SIZE,
	GR_ERROR_INVALID_EXTENSION,
	GR_ERROR_INVALID_FLAGS,
	GR_ERROR_INVALID_ALIGNMENT,
	GR_ERROR_INVALID_FORMAT,
	GR_ERROR_INVALID_IMAGE,
	GR_ERROR_INVALID_DESCRIPTOR_SET_DATA,
	GR_ERROR_INVALID_QUEUE_TYPE,
	GR_ERROR_INVALID_OBJECT_TYPE,
	GR_ERROR_UNSUPPORTED_SHADER_IL_VERSION,
	GR_ERROR_BAD_SHADER_CODE,
	GR_ERROR_BAD_PIPELINE_DATA,
	GR_ERROR_TOO_MANY_MEMORY_REFERENCES,
	GR_ERROR_NOT_MAPPABLE,
	GR_ERROR_MEMORY_MAP_FAILED,
	GR_ERROR_MEMORY_UNMAP_FAILED,
	GR_ERROR_INCOMPATIBLE_DEVICE,
	GR_ERROR_INCOMPATIBLE_DRIVER,
	GR_ERROR_INCOMPLETE_COMMAND_BUFFER,
	GR_ERROR_BUILDING_COMMAND_BUFFER,
	GR_ERROR_MEMORY_NOT_BOUND,
	GR_ERROR_INCOMPATIBLE_QUEUE,
	GR_WSI_WIN_PRESENT_OCCLUDED,
	GR_WSI_WIN_ERROR_FULLSCREEN_UNAVAILABLE,
	GR_WSI_WIN_ERROR_DISPLAY_REMOVED,
	GR_WSI_WIN_ERROR_INCOMPATIBLE_DISPLAY_MODE,
	GR_WSI_WIN_ERROR_MULTI_DEVICE_PRESENT_FAILED,
	GR_WSI_WIN_ERROR_BLT_PRESENT_UNAVAILABLE
}GR_RESULT;

typedef enum _GR_VALIDATION_LEVEL{
	GR_VALIDATION_LEVEL_0 = 0x8000,
	GR_VALIDATION_LEVEL_1 = 0x8001,
	GR_VALIDATION_LEVEL_2 = 0x8002,
	GR_VALIDATION_LEVEL_3 = 0x8003,
	GR_VALIDATION_LEVEL_4 = 0x8004,
} GR_VALIDATION_LEVEL;

typedef enum _GR_QUEUE_TYPE{
	GR_QUEUE_UNIVERSAL = 0x1000,
	GR_QUEUE_COMPUTE = 0x1001,
} GR_QUEUE_TYPE;

typedef enum _GR_DEVICE_CREATE_FLAGS{
	GR_DEVICE_CREATE_VALIDATION = 0x00000001,
} GR_DEVICE_CREATE_FLAGS;

typedef enum _GR_PHYSICAL_GPU_TYPE{
	GR_GPU_TYPE_OTHER = 0x3000,
	GR_GPU_TYPE_INTEGRATED = 0x3001,
	GR_GPU_TYPE_DISCRETE = 0x3002,
	GR_GPU_TYPE_VIRTUAL = 0x3003,
} GR_PHYSICAL_GPU_TYPE;

typedef enum _GR_INFO_TYPE{
	GR_INFO_TYPE_PHYSICAL_GPU_PROPERTIES = 0x6100,
	GR_INFO_TYPE_PHYSICAL_GPU_PERFORMANCE = 0x6101,
	GR_INFO_TYPE_PHYSICAL_GPU_QUEUE_PROPERTIES = 0x6102,
	GR_INFO_TYPE_PHYSICAL_GPU_MEMORY_PROPERTIES = 0x6103,
	GR_INFO_TYPE_PHYSICAL_GPU_IMAGE_PROPERTIES = 0x6104,
	GR_INFO_TYPE_MEMORY_HEAP_PROPERTIES = 0x6200,
	GR_INFO_TYPE_FORMAT_PROPERTIES = 0x6300,
	GR_INFO_TYPE_SUBRESOURCE_LAYOUT = 0x6400,
	GR_INFO_TYPE_MEMORY_REQUIREMENTS = 0x6800,
	GR_INFO_TYPE_PARENT_DEVICE = 0x6801,
	GR_INFO_TYPE_PARENT_PHYSICAL_GPU = 0x6802,
} GR_INFO_TYPE;

typedef GR_VOID* (GR_STDCALL* GR_ALLOC_FUNCTION)(
	GR_SIZE size,
	GR_SIZE alignment,
	GR_ENUM allocType);

typedef GR_VOID(GR_STDCALL* GR_FREE_FUNCTION)(
	GR_VOID* pMem);

typedef struct _GR_APPLICATION_INFO
{
	const GR_CHAR* pAppName;
	GR_UINT32 appVersion;
	const GR_CHAR* pEngineName;
	GR_UINT32 engineVersion;
	GR_UINT32 apiVersion;
} GR_APPLICATION_INFO;

typedef struct _GR_DEVICE_QUEUE_CREATE_INFO
{
	GR_ENUM queueType;
	GR_UINT queueCount;
} GR_DEVICE_QUEUE_CREATE_INFO;

typedef struct _GR_DEVICE_CREATE_INFO
{
	GR_UINT queueRecordCount;
	const GR_DEVICE_QUEUE_CREATE_INFO* pRequestedQueues;
	GR_UINT extensionCount;
	const GR_CHAR* const* ppEnabledExtensionNames;
	GR_ENUM maxValidationLevel;
	GR_FLAGS flags;
} GR_DEVICE_CREATE_INFO;

typedef struct _GR_ALLOC_CALLBACKS
{
	GR_ALLOC_FUNCTION pfnAlloc;
	GR_FREE_FUNCTION pfnFree;
} GR_ALLOC_CALLBACKS;

typedef struct _GR_PHYSICAL_GPU_PROPERTIES
{
	GR_UINT32 apiVersion;
	GR_UINT32 driverVersion;
	GR_UINT32 vendorId;
	GR_UINT32 deviceId;
	GR_ENUM gpuType;
	GR_CHAR gpuName[GR_MAX_PHYSICAL_GPU_NAME];
	GR_UINT maxMemRefsPerSubmission;
	GR_GPU_SIZE reserved;
	GR_GPU_SIZE maxInlineMemoryUpdateSize;
	GR_UINT maxBoundDescriptorSets;
	GR_UINT maxThreadGroupSize;
	GR_UINT64 timestampFrequency;
	GR_BOOL multiColorTargetClears;
} GR_PHYSICAL_GPU_PROPERTIES;

typedef GR_RESULT(GR_STDCALL* InitAndEnumerateGpus)(
	const GR_APPLICATION_INFO* pAppInfo,
	const GR_ALLOC_CALLBACKS* pAllocCb,
	GR_UINT* pGpuCount,
	GR_PHYSICAL_GPU gpus[GR_MAX_PHYSICAL_GPUS]);
InitAndEnumerateGpus grInitAndEnumerateGpus;

typedef GR_RESULT(GR_STDCALL* GetGpuInfo)(
	GR_PHYSICAL_GPU gpu,
	GR_ENUM infoType,
	GR_SIZE* pDataSize,
	GR_VOID* pData);
GetGpuInfo grGetGpuInfo;

typedef GR_RESULT(GR_STDCALL* CreateDevice)(
	GR_PHYSICAL_GPU gpu,
	const GR_DEVICE_CREATE_INFO* pCreateInfo,
	GR_DEVICE* pDevice);
CreateDevice grCreateDevice;

typedef GR_RESULT(GR_STDCALL* DestroyDevice)(
	GR_DEVICE device);
DestroyDevice grDestroyDevice;

#ifdef __cplusplus
}
#endif

#endif
