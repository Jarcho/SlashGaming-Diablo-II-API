/**
 * SlashGaming Diablo II Modding API for C++
 * Copyright (C) 2018-2021  Mir Drualga
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

#ifndef SGD2MAPI_CXX_GAME_STRUCT_D2_BELT_RECORD_D2_BELT_RECORD_WRAPPER_HPP_
#define SGD2MAPI_CXX_GAME_STRUCT_D2_BELT_RECORD_D2_BELT_RECORD_WRAPPER_HPP_

#include <cstddef>

#include "../d2_positional_rectangle/d2_positional_rectangle_view.hpp"
#include "../d2_positional_rectangle/d2_positional_rectangle_wrapper.hpp"
#include "d2_belt_record_struct.hpp"
#include "d2_belt_record_view.hpp"

#include "../../../dllexport_define.inc"

namespace d2 {

class DLLEXPORT BeltRecord_Wrapper {
 public:
  using WrapperVariant = std::variant<BeltRecord_1_00*>;

  BeltRecord_Wrapper() = delete;

  BeltRecord_Wrapper(BeltRecord* belt_record) noexcept;

  constexpr BeltRecord_Wrapper(WrapperVariant belt_record) noexcept
      : belt_record_(::std::move(belt_record)) {
  }

  constexpr BeltRecord_Wrapper(
      const BeltRecord_Wrapper& other
  ) noexcept = default;

  constexpr BeltRecord_Wrapper(
      BeltRecord_Wrapper&& other
  ) noexcept = default;

  ~BeltRecord_Wrapper() noexcept = default;

  constexpr BeltRecord_Wrapper& operator=(
      const BeltRecord_Wrapper& other
  ) noexcept = default;

  constexpr BeltRecord_Wrapper& operator=(
      BeltRecord_Wrapper&& other
  ) noexcept = default;

  constexpr BeltRecord_View operator[](
      std::size_t index
  ) const noexcept {
    BeltRecord_View view(*this);

    return view[index];
  }

  constexpr BeltRecord_Wrapper operator[](
      std::size_t index
  ) noexcept {
    return std::visit(
        [index](const auto& actual_belt_record) {
          return BeltRecord_Wrapper(
              &actual_belt_record[index]
          );
        },
        this->belt_record_
    );
  }

  constexpr operator BeltRecord_View() const noexcept {
    return ::std::visit(
        [](const auto& actual_belt_record) {
          return BeltRecord_View(actual_belt_record);
        },
        this->belt_record_
    );
  }

  constexpr BeltRecord* Get() noexcept {
    const auto* const_this = this;

    return const_cast<BeltRecord*>(const_this->Get());
  }

  constexpr const BeltRecord* Get() const noexcept {
    return std::visit(
        [](const auto& actual_belt_record) {
          return reinterpret_cast<const BeltRecord*>(actual_belt_record);
        },
        this->belt_record_
    );
  }

  constexpr void AssignMembers(BeltRecord_View src) noexcept {
    std::visit(
        [&src](auto& actual_dest) {
          using Dest_T = decltype(actual_dest);
          using ActualSrc_T = const std::remove_pointer_t<
              std::remove_reference_t<Dest_T>
          >*;

          const auto* actual_src = reinterpret_cast<ActualSrc_T>(src.Get());

          *actual_dest = *actual_src;
        },
        this->belt_record_
    );
  }

  constexpr unsigned char GetNumSlots() const noexcept {
    BeltRecord_View view(*this);

    return view.GetNumSlots();
  }

  constexpr void SetNumSlots(unsigned char num_slots) noexcept {
    std::visit(
        [num_slots](auto& actual_positional_rectangle) {
          actual_positional_rectangle->num_slots = num_slots;
        },
        this->belt_record_
    );
  }

  constexpr PositionalRectangle_View GetSlotPositions() const noexcept {
    BeltRecord_View view(this->Get());

    return view.GetSlotPositions();
  }

  constexpr PositionalRectangle_Wrapper GetSlotPositions() noexcept {
    return ::std::visit(
        [](auto& actual_belt_record) {
          return PositionalRectangle_Wrapper(
              actual_belt_record->slot_positions
          );
        },
        this->belt_record_
    );
  }

 private:
  WrapperVariant belt_record_;

  static WrapperVariant CreateVariant(BeltRecord* belt_record);
};

} // namespace d2

#include "../../../dllexport_undefine.inc"
#endif // SGD2MAPI_CXX_GAME_STRUCT_D2_BELT_RECORD_D2_BELT_RECORD_WRAPPER_HPP_
