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

#include <iostream>
#include <vector>

#include "grid.h"
#include "scalar_polygonization/vec3.h"

namespace EXAMPLES
{
/*! \class Array
 *
 * Class to create Array.
 */
template <typename T_GRID, typename T_ARRAY>
class Array
{
 public:
  using value_type = T_ARRAY;

  /*! Constructor called using grid.
   *
   * \param grid object of Grid.
   */
  Array(const Grid<typename T_GRID::value_type, T_GRID::dim> &grid);

  /*! Destructor
   */
  ~Array();

  /*! Returns 1D array size of array.
   *
   * Data of array is stored in 1D vector with some padding. This function returns 1D vector size.
   *
   * \return 1D array size.
   */
  const std::size_t size() const;

  /*! Returns attached grid.
   */
  const T_GRID &grid() const;

  /*! Returns a vector of size 3 with number of cells along x, y, z directions.
   *
   * Vector of size 3: {nx, ny, nz}.
   *
   * \return vector of size 3.
   */
  const SCALAR_POLYGONIZATION::Vec3<int> numCells() const;

  /*! Get data.
   *
   * \return vector that stores data.
   */
  const std::vector<T_ARRAY> &data() const { return m_data; }

  /*! Overloaded subscript operator to return value of array at a given 1D array based index.
   *
   * \param idx 1D array based index.
   *
   * \return value at given index.
   */
  const T_ARRAY &operator[](const std::size_t idx) const;

  /*! Overloaded subscript operator to return reference to value of array at a given 1D array based index.
   *
   * \param idx 1D array based index.
   *
   * \return reference to value at given index.
   */
  T_ARRAY &operator[](const std::size_t idx);

  /*! Overloaded operator to return value of array using 3D cell indices.
   *
   * \param i zero based index along x-direction.
   * \param j zero based index along y-direction.
   * \param k zero based index along z-direction.
   *
   * \return value at given 3D cell indices.
   */
  const T_ARRAY &operator()(const int i, const int j, const int k) const;

  /*! Overloaded operator to return reference to value of array using 3D cell indices.
   *
   * \param i zero based index along x-direction.
   * \param j zero based index along y-direction.
   * \param k zero based index along z-direction.
   *
   * \return reference to value at given 3D cell indices.
   */
  T_ARRAY &operator()(const int i, const int j, const int k);

  /*! Overloaded operator to return value of array using 3D cell index.
   *
   * \param node_id node id of type SCALAR_POLYGONIZATION::Vec3<int>.
   *
   * \return value at given 3D cell index.
   */
  const T_ARRAY &operator()(const SCALAR_POLYGONIZATION::Vec3<int> node_id) const;

  /*! Overloaded operator to return value of array using 3D cell index.
   *
   * \param node_id node id of type SCALAR_POLYGONIZATION::Vec3<int>.
   *
   * \return value at given 3D cell index.
   */
  T_ARRAY &operator()(const SCALAR_POLYGONIZATION::Vec3<int> node_id);

  /*! Overloaded operator to assign values.
   *
   * \param array array from which values will be copied.
   */
  void operator=(const Array<T_GRID, T_ARRAY> &array);

  /*! Output operator overload.
   *
   * \param out output stream.
   * \param array Array object to output stream.
   *
   * \return reference to output stream.
   */
  friend std::ostream &operator<<(std::ostream &out, const Array<T_GRID, T_ARRAY> &array)
  {
    const auto &grid = array.grid();
    const auto num_cells = array.numCells();

    for (int i = 0; i < num_cells[0]; ++i)
      for (int j = 0; j < num_cells[1]; ++j)
        for (int k = 0; k < num_cells[2]; ++k) out << grid(i, j, k) << "\t" << array(i, j, k) << "\n";

    return out;
  }

 private:
  const T_GRID &m_grid;
  const int m_nx, m_ny, m_nz, m_pad;
  std::vector<T_ARRAY> m_data;
};

}  // namespace EXAMPLES
