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

#ifndef SGD2MAPI_CXX_GAME_STRUCT_D2_POSITIONAL_RECTANGLE_D2_POSITIONAL_RECTANGLE_API_HPP_
#define SGD2MAPI_CXX_GAME_STRUCT_D2_POSITIONAL_RECTANGLE_D2_POSITIONAL_RECTANGLE_API_HPP_

#include <variant>

#include "d2_positional_rectangle_struct.hpp"
#include "d2_positional_rectangle_view.hpp"
#include "d2_positional_rectangle_wrapper.hpp"

#include "../../../dllexport_define.inc"

namespace d2 {

class DLLEXPORT PositionalRectangle_Api {
 public:
  PositionalRectangle_Api();

  PositionalRectangle_Api(
      int left,
      int right,
      int top,
      int bottom
  );

  PositionalRectangle_Api(const PositionalRectangle_Api& other);

  PositionalRectangle_Api(PositionalRectangle_Api&& other) noexcept;

  ~PositionalRectangle_Api();

  PositionalRectangle_Api& operator=(
      const PositionalRectangle_Api& other
  );

  PositionalRectangle_Api& operator=(
      PositionalRectangle_Api&& other
  ) noexcept;

  constexpr operator PositionalRectangle_View() const noexcept {
    return ::std::visit(
        [](const auto& actual_positional_rectangle) {
          return PositionalRectangle_View(&actual_positional_rectangle);
        },
        this->positional_rectangle_
    );
  }

  constexpr operator PositionalRectangle_Wrapper() noexcept {
    return ::std::visit(
        [](auto& actual_positional_rectangle) {
          return PositionalRectangle_Wrapper(&actual_positional_rectangle);
        },
        this->positional_rectangle_
    );
  }

  constexpr PositionalRectangle* Get() noexcept {
    const auto* const_this = this;

    return const_cast<PositionalRectangle*>(const_this->Get());
  }

  constexpr const PositionalRectangle* Get() const noexcept {
    return std::visit(
        [](const auto& actual_positional_rectangle) {
          return reinterpret_cast<const PositionalRectangle*>(
              &actual_positional_rectangle
          );
        },
        this->positional_rectangle_
    );
  }

  constexpr void AssignMembers(PositionalRectangle_View src) noexcept {
    PositionalRectangle_Wrapper wrapper(*this);

    wrapper.AssignMembers(src);
  }

  constexpr int GetLeft() const noexcept {
    PositionalRectangle_View view(*this);

    return view.GetLeft();
  }

  constexpr void SetLeft(int left) noexcept {
    PositionalRectangle_Wrapper wrapper(*this);

    return wrapper.SetLeft(left);
  }

  constexpr int GetRight() const noexcept {
    PositionalRectangle_View view(*this);

    return view.GetRight();
  }

  constexpr void SetRight(int right) noexcept {
    PositionalRectangle_Wrapper wrapper(*this);

    return wrapper.SetRight(right);
  }

  constexpr int GetTop() const noexcept {
    PositionalRectangle_View view(*this);

    return view.GetTop();
  }

  constexpr void SetTop(int top) noexcept {
    PositionalRectangle_Wrapper wrapper(*this);

    return wrapper.SetTop(top);
  }

  constexpr int GetBottom() const noexcept {
    PositionalRectangle_View view(*this);

    return view.GetBottom();
  }

  constexpr void SetBottom(int bottom) noexcept {
    PositionalRectangle_Wrapper wrapper(*this);

    return wrapper.SetBottom(bottom);
  }

 private:
  using ApiVariant = std::variant<PositionalRectangle_1_00>;

  ApiVariant positional_rectangle_;

  static ApiVariant CreateVariant(int left, int right, int top, int bottom);
};

} // namespace d2

#include "../../../dllexport_undefine.inc"
#endif // SGD2MAPI_CXX_GAME_STRUCT_D2_POSITIONAL_RECTANGLE_D2_POSITIONAL_RECTANGLE_API_HPP_
