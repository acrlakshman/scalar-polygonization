///////////////////////////////////////////////////////////////////////////////
// Copyright 2019 Lakshman Anumolu.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors
// may be used to endorse or promote products derived from this software without
// specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math.h>
#include <string.h>
#include <type_traits>

namespace SCALAR_POLYGONIZATION
{
static double VSMALL = 1e-10;
static const double one_third = 1. / 3.;

/*! Check for equality within a tolerance.
 *
 * Tolerance is by default 1e-10.
 *
 * \param a first argument
 * \param b second argument
 *
 * \return number of elements.
 */
template <typename T, typename std::enable_if<std::is_floating_point<T>::value, T>::type* = nullptr>
static bool is_equal(const T a, const T b)
{
  return (static_cast<T>(fabs(a - b)) <= VSMALL);
}

template <typename T, typename std::enable_if<std::is_integral<T>::value, T>::type* = nullptr>
static bool is_equal(const T a, const T b)
{
  return a == b;
}
}  // namespace SCALAR_POLYGONIZATION
