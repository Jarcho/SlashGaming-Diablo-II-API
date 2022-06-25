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

#ifndef SGD2MAPI_CXX_GAME_STRUCT_D2_INVENTORY_RECORD_D2_INVENTORY_RECORD_VIEW_HPP_
#define SGD2MAPI_CXX_GAME_STRUCT_D2_INVENTORY_RECORD_D2_INVENTORY_RECORD_VIEW_HPP_

#include <cstddef>
#include <variant>

#include "../d2_equipment_layout/d2_equipment_layout_view.hpp"
#include "../d2_grid_layout/d2_grid_layout_view.hpp"
#include "../d2_positional_rectangle/d2_positional_rectangle_view.hpp"
#include "d2_inventory_record_struct.hpp"

#include "../../../dllexport_define.inc"

namespace d2 {

class DLLEXPORT InventoryRecord_View {
 public:
  using ViewVariant = std::variant<const InventoryRecord_1_00*>;

  InventoryRecord_View() = delete;

  InventoryRecord_View(const InventoryRecord* inventory_record) noexcept;

  constexpr explicit InventoryRecord_View(
      ViewVariant inventory_record
  ) noexcept
      : inventory_record_(::std::move(inventory_record)) {
  }

  constexpr InventoryRecord_View(
      const InventoryRecord_View& other
  ) noexcept = default;

  constexpr InventoryRecord_View(
      InventoryRecord_View&& other
  ) noexcept = default;

  ~InventoryRecord_View() noexcept = default;

  constexpr InventoryRecord_View& operator=(
      const InventoryRecord_View& other
  ) noexcept = default;

  constexpr InventoryRecord_View& operator=(
      InventoryRecord_View&& other
  ) noexcept = default;

  constexpr InventoryRecord_View operator[](
      std::size_t index
  ) const noexcept {
    return ::std::visit(
        [index](const auto& actual_inventory_record) {
          return InventoryRecord_View(&actual_inventory_record[index]);
        },
        this->inventory_record_
    );
  }

  constexpr const InventoryRecord* Get() const noexcept {
    return std::visit(
        [](const auto& actual_inventory_record) {
          return reinterpret_cast<const InventoryRecord*>(
              actual_inventory_record
          );
        },
        this->inventory_record_
    );
  }

  constexpr PositionalRectangle_View GetPosition() const noexcept {
    return std::visit(
        [](const auto& actual_inventory_record) {
          return PositionalRectangle_View(
              &actual_inventory_record->position
          );
        },
        this->inventory_record_
    );
  }

  constexpr GridLayout_View GetGridLayout() const noexcept {
    return std::visit(
        [](const auto& actual_inventory_record) {
          return GridLayout_View(
              &actual_inventory_record->grid_layout
          );
        },
        this->inventory_record_
    );
  }

  constexpr EquipmentLayout_View GetEquipmentSlots() const noexcept {
    return std::visit(
        [](const auto& actual_inventory_record) {
          return EquipmentLayout_View(
              actual_inventory_record->equipment_slots
          );
        },
        this->inventory_record_
    );
  }

 private:
  ViewVariant inventory_record_;

  static ViewVariant CreateVariant(const InventoryRecord* inventory_record);
};

} // namespace d2

#include "../../../dllexport_undefine.inc"
#endif // SGD2MAPI_CXX_GAME_STRUCT_D2_INVENTORY_RECORD_D2_INVENTORY_RECORD_VIEW_HPP_
