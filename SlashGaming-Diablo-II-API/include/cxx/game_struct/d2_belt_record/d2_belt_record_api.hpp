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

#ifndef SGD2MAPI_CXX_GAME_STRUCT_D2_BELT_RECORD_D2_BELT_RECORD_API_HPP_
#define SGD2MAPI_CXX_GAME_STRUCT_D2_BELT_RECORD_D2_BELT_RECORD_API_HPP_

#include <cstddef>
#include <variant>

#include "../../game_undefined.hpp"
#include "../d2_positional_rectangle/d2_positional_rectangle_view.hpp"
#include "../d2_positional_rectangle/d2_positional_rectangle_wrapper.hpp"
#include "d2_belt_record_struct.hpp"
#include "d2_belt_record_view.hpp"
#include "d2_belt_record_wrapper.hpp"

#include "../../../dllexport_define.inc"

namespace d2 {

class DLLEXPORT BeltRecord_Api {
 public:
  using ApiVariant = std::variant<BeltRecord_1_00>;

  BeltRecord_Api() = delete;

  BeltRecord_Api(
      mapi::Undefined* reserved_00__set_to_nullptr,
      unsigned char num_slots,
      const PositionalRectangle* slot_positions
  );

  BeltRecord_Api(const BeltRecord_Api& other);
  BeltRecord_Api(BeltRecord_Api&& other) noexcept;

  ~BeltRecord_Api();

  BeltRecord_Api& operator=(const BeltRecord_Api& other);
  BeltRecord_Api& operator=(BeltRecord_Api&& other) noexcept;

  constexpr operator BeltRecord_View() const noexcept {
    return ::std::visit(
        [](const auto& actual_belt_record) {
          return BeltRecord_View(&actual_belt_record);
        },
        this->belt_record_
    );
  }

  constexpr operator BeltRecord_Wrapper() noexcept {
    return ::std::visit(
        [](auto& actual_belt_record) {
          return BeltRecord_Wrapper(&actual_belt_record);
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
          return reinterpret_cast<const BeltRecord*>(&actual_belt_record);
        },
        this->belt_record_
    );
  }

  constexpr void AssignMembers(BeltRecord_View src) noexcept {
    BeltRecord_Wrapper wrapper(*this);

    wrapper.AssignMembers(src);
  }

  constexpr unsigned char GetNumSlots() const noexcept {
    BeltRecord_View view(*this);

    return view.GetNumSlots();
  }

  constexpr void SetNumSlots(unsigned char num_slots) noexcept {
    BeltRecord_Wrapper wrapper(*this);

    return wrapper.SetNumSlots(num_slots);
  }

  constexpr PositionalRectangle_View GetSlotPositions() const noexcept {
    BeltRecord_View view(*this);

    return view.GetSlotPositions();
  }

  constexpr PositionalRectangle_Wrapper GetSlotPositions() noexcept {
    BeltRecord_Wrapper wrapper(*this);

    return wrapper.GetSlotPositions();
  }

 private:
  ApiVariant belt_record_;

  static ApiVariant CreateVariant(
      mapi::Undefined* reserved_00__set_to_nullptr,
      unsigned char num_slots,
      const PositionalRectangle* slot_positions
  );
};

} // namespace d2

#include "../../../dllexport_undefine.inc"
#endif // SGD2MAPI_CXX_GAME_STRUCT_D2_BELT_RECORD_D2_BELT_RECORD_API_HPP_
