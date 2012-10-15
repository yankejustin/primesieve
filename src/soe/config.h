//
// Copyright (c) 2012 Kim Walisch, <kim.walisch@gmail.com>.
// All rights reserved.
//
// This file is part of primesieve.
// Homepage: http://primesieve.googlecode.com
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//   * Redistributions of source code must retain the above copyright
//     notice, this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above
//     copyright notice, this list of conditions and the following
//     disclaimer in the documentation and/or other materials provided
//     with the distribution.
//   * Neither the name of the author nor the names of its
//     contributors may be used to endorse or promote products derived
//     from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.

/// @file   config.h
/// @brief  Macro definitions and compile time constants that set
///         various limits within primesieve.
///
/// The constants have been optimized for an Intel Core i7-3770K
/// 3.5GHz (32K L1 data cache) CPU from 2012.

#ifndef CONFIG_PRIMESIEVE_H
#define CONFIG_PRIMESIEVE_H

/// Enable the UINT64_C() macro from <stdint.h>
#if !defined(__STDC_CONSTANT_MACROS)
  #define __STDC_CONSTANT_MACROS
#endif
#include <stdint.h>

/// Disable assert() macro
#if !defined(DEBUG) && !defined(NDEBUG)
  #define NDEBUG
#endif

/// Disable the default copy constructor and assignment operator
#ifndef DISALLOW_COPY_AND_ASSIGN
#define DISALLOW_COPY_AND_ASSIGN(ClassName) \
  ClassName(const ClassName&); \
  void operator=(const ClassName&)
#endif

/// Default CPU L1 data cache size in kilobytes (per core)
#ifndef L1_DCACHE_SIZE
  #define L1_DCACHE_SIZE 32
#endif

namespace soe {
typedef unsigned int uint_t;

namespace config {
enum {
  /// Default sieve size in kilobytes of PrimeSieve and
  /// ParallelPrimeSieve objects. Set SIEVESIZE to your CPUs L1 data
  /// cache size to get the best performance.
  /// @pre SIEVESIZE >= 1 && <= 4096
  ///
  SIEVESIZE = L1_DCACHE_SIZE,

  /// Default pre-sieve limit of PrimeSieve and ParallelPrimeSieve
  /// objects. Multiples of small primes up to this limit are
  /// pre-sieved to speed up the sieve of Eratosthenes.
  /// @pre PRESIEVE >= 13 && <= 23.
  ///
  PRESIEVE = 19,

  /// Pre-sieve limit of PrimeNumberGenerator. Default = 13 (uses 1001 bytes),
  /// a greater value uses more memory with no speedup.
  /// @pre PRESIEVE_GENERATOR >= 13 && <= 23
  ///
  PRESIEVE_GENERATOR = 13,

  /// Number of sieving primes per Bucket in EratSmall, EratMedium and
  /// EratBig objects, affects performance by about 3%.
  ///
  /// - For x86-64 CPUs post  2010 use 1024
  /// - For x86-64 CPUs prior 2010 use 512
  /// - For PowerPC G4 CPUs (2003) use 256
  ///
  BUCKETSIZE = 1 << 10,

  /// EratBig allocates MEMORY_PER_ALLOC bytes of new memory each
  /// time it needs more buckets. Default = 4 megabytes.
  ///
  MEMORY_PER_ALLOC = (1 << 20) * 4
};

/// Sieving primes <= (sieveSize in bytes * FACTOR_ERATSMALL)
/// are processed in EratSmall objects, affects performance by about 5%.
/// @pre FACTOR_ERATSMALL >= 0 && <= 3
///
/// - For x86-64 CPUs post  2010 use 0.5 or 0.3
/// - For x86-64 CPUs prior 2010 use 0.8
/// - For PowerPC G4 CPUs (2003) use 1.0
///
const double FACTOR_ERATSMALL = 0.5;

/// Sieving primes <= (sieveSize in bytes * FACTOR_ERATMEDIUM)
/// (and > EratSmall, see above) are processed in EratMedium objects.
/// @pre FACTOR_ERATMEDIUM >= 0 && <= 6
///
const double FACTOR_ERATMEDIUM = 6;

/// In ParallelPrimeSieve each thread sieves at least an interval of size
/// MIN_THREAD_INTERVAL to reduce the initialization overhead.
/// @pre MIN_THREAD_INTERVAL >= 100
///
const uint64_t MIN_THREAD_INTERVAL = UINT64_C(10000000);

/// In ParallelPrimeSieve each thread sieves at most an interval of size
/// MAX_THREAD_INTERVAL to prevent load imbalance near 99%.
///
const uint64_t MAX_THREAD_INTERVAL = UINT64_C(20000000000);

} // namespace config
} // namespace soe

#endif
