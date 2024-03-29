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

#include "scalar_polygonization/marching_cubes.h"
#include "scalar_polygonization/utilities.h"
#include "scalar_polygonization/vec3.h"

#include <gtest/gtest.h>

#include <iostream>
#include <vector>

namespace SP = SCALAR_POLYGONIZATION;

TEST(SCALAR_POLYGONIZATION, SCALAR_POLYGONIZATION)
{
  using T = float;

  SCALAR_POLYGONIZATION::MarchingCubes<T> mc;

  auto vertex_ids = std::vector<std::size_t>{0, 1, 2, 3, 4, 5, 6, 7};
  auto edge_ids_ref = std::vector<std::size_t>{0, 12, 3, 11, 4, 16, 7, 15, 22, 23, 24, 25};
  const auto edge_ids = mc.vertexToEdgeIds(10, vertex_ids);

  EXPECT_TRUE(std::equal(edge_ids.begin(), edge_ids.end(), edge_ids_ref.begin()));
  EXPECT_TRUE(SCALAR_POLYGONIZATION::is_equal(mc.edgeIntersectionWeight(0, 1, 0.5), static_cast<T>(0.5)));

  std::vector<SP::Vec3<T>> cube_vertices{SP::Vec3<T>(0, 0, 0), SP::Vec3<T>(1, 0, 0), SP::Vec3<T>(1, 1, 0),
                                         SP::Vec3<T>(0, 1, 0), SP::Vec3<T>(0, 0, 1), SP::Vec3<T>(1, 0, 1),
                                         SP::Vec3<T>(1, 1, 1), SP::Vec3<T>(0, 1, 1)};
  std::vector<T> scalars{0, 0, 1, 1, 0, 0, 1, 1};
  std::vector<SP::Vec3<T>> normals{SP::Vec3<T>(0, 0, 0), SP::Vec3<T>(0, 0, 0), SP::Vec3<T>(0, 1, 0),
                                   SP::Vec3<T>(0, 1, 0), SP::Vec3<T>(0, 0, 0), SP::Vec3<T>(0, 0, 0),
                                   SP::Vec3<T>(0, 1, 0), SP::Vec3<T>(0, 1, 0)};

  const auto triangle_vertex_tuple = mc.marchCube(cube_vertices, edge_ids, scalars, normals, 0.5);

  const auto triangles = std::get<SCALAR_POLYGONIZATION::TRIANGLES>(triangle_vertex_tuple);
  const auto vertices = std::get<SCALAR_POLYGONIZATION::VERTICES>(triangle_vertex_tuple);

  EXPECT_TRUE(triangles.size() == static_cast<size_t>(2));
  EXPECT_TRUE(vertices.size() == static_cast<size_t>(6));
}
