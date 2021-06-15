#pragma once

#include <cstdint>

//#define ENABLE_QUEUE_LOGING
constexpr uint32_t version_major = 1;
constexpr uint32_t version_minor = 0;

//#define ALLOW_ZERO_COMPRESSION_MODE

#define USE_COMPACTED_READS

//#define MONITOR_QUEUES
//#define MEASURE_THREADS_TIMES

using anchor_type = uint64_t;
using kmer_type = uint64_t;

constexpr uint32_t reads_queue_size = 16;
//constexpr uint32_t reads_queue_size = 64;
constexpr uint32_t quals_queue_size = 128;
constexpr uint32_t headers_queue_size = 16;

constexpr uint32_t compress_queue_size = 16;

constexpr uint32_t reads_pack_size = 2 << 21;
constexpr uint32_t headers_pack_size = 2 << 21;

constexpr uint32_t read_decompress_queue_size = 4;
constexpr uint32_t header_decompress_queue_size = 4;
constexpr uint32_t qual_decompress_queue_size = 4;

/*
* If enabled input packs of reads in graph construction are splitted in more parts than threads, after finishing each part the number of idle encoder threads is checked, if there is any new waiting encoder thread
* it is used to parallelize graph better
*/
#define USE_BETTER_PARALLELIZATION_IN_GRAPH



#if defined(_MSC_VER)  /* Visual Studio */
#define FORCE_INLINE __forceinline
#define NO_INLINE __declspec(noinline)
#elif defined(__GNUC__)
#define FORCE_INLINE __inline__ __attribute__((always_inline, unused))
#define NO_INLINE __attribute__((noinline))
#else
#define FORCE_INLINE
#define NO_INLINE
#endif

#define ESTIMATE_MEMORY_WITH_COUNTS_PER_PREFIX
