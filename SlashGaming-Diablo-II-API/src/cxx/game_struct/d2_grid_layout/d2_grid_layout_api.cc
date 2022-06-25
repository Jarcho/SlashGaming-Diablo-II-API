/**
 * SlashGaming Diablo II Modding API for C++
 * Copyright (C) 2018-2022  Mir Drualga
 *
 * This file is part of SlashGaming Diablo II Modding API for C++.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published
 *  by the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Additional permissions under GNU Affero General Public License version 3
 *  section 7
 *
 *  If you modify this Program, or any covered work, by linking or combining
 *  it with Diablo II (or a modified version of that game and its
 *  libraries), containing parts covered by the terms of Blizzard End User
 *  License Agreement, the licensors of this Program grant you additional
 *  permission to convey the resulting work. This additional permission is
 *  also extended to any combination of expansions, mods, and remasters of
 *  the game.
 *
 *  If you modify this Program, or any covered work, by linking or combining
 *  it with any Graphics Device Interface (GDI), DirectDraw, Direct3D,
 *  Glide, OpenGL, or Rave wrapper (or modified versions of those
 *  libraries), containing parts not covered by a compatible license, the
 *  licensors of this Program grant you additional permission to convey the
 *  resulting work.
 *
 *  If you modify this Program, or any covered work, by linking or combining
 *  it with any library (or a modified version of that library) that links
 *  to Diablo II (or a modified version of that game and its libraries),
 *  containing parts not covered by a compatible license, the licensors of
 *  this Program grant you additional permission to convey the resulting
 *  work.
 */

#include "../../../../include/cxx/game_struct/d2_grid_layout/d2_grid_layout_api.hpp"

#include "../../../../include/cxx/game_struct/d2_positional_rectangle/d2_positional_rectangle_wrapper.hpp"
#include "../../../../include/cxx/game_version.hpp"

namespace d2 {

GridLayout_Api::GridLayout_Api(
    unsigned char num_columns,
    unsigned char num_rows,
    PositionalRectangle_View position,
    unsigned char width,
    unsigned char height
) : grid_layout_(CreateVariant(
        num_columns,
        num_rows,
        position.Get(),
        width,
        height
    )) {
}

GridLayout_Api::ApiVariant GridLayout_Api::CreateVariant(
    unsigned char num_columns,
    unsigned char num_rows,
    const PositionalRectangle* position,
    unsigned char width,
    unsigned char height
) {
  ApiVariant grid_layout;

  grid_layout = GridLayout_1_00();

  std::visit(
      [=](auto& actual_grid_layout) {
        actual_grid_layout.num_columns = num_columns;
        actual_grid_layout.num_rows = num_rows;

        PositionalRectangle_Wrapper position_wrapper(
            reinterpret_cast<PositionalRectangle*>(
                &actual_grid_layout.position
            )
        );
        position_wrapper.AssignMembers(position);

        actual_grid_layout.width = width;
        actual_grid_layout.height = height;
      },
      grid_layout
  );

  return grid_layout;
}

} // namespace d2
