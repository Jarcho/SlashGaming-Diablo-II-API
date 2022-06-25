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

/**
 * Latest supported version: 1.14D
 */

#include "../../../../include/cxx/game_function/d2common/d2common_get_global_inventory_position.hpp"

#include "../../../../include/cxx/default_game_library.hpp"
#include "../../../../include/cxx/game_version.hpp"
#include "../../../asm_x86_macro.h"
#include "../../backend/game_address_table.hpp"
#include "../../backend/game_function/stdcall_function.hpp"

namespace d2::d2common {
namespace {

static const mapi::GameAddress& GetGameAddress() {
  static const mapi::GameAddress game_address = mapi::LoadGameAddress(
      ::d2::DefaultLibrary::kD2Common,
      "GetGlobalInventoryPosition"
  );

  return game_address;
}

} // namespace

void GetGlobalInventoryPosition(
    unsigned int inventory_record_index,
    unsigned int inventory_arrange_mode,
    PositionalRectangle* out_position
) {
  GameVersion running_game_version = ::d2::game_version::GetRunning();

  if (running_game_version <= GameVersion::k1_06B) {
    GetGlobalInventoryPosition_1_00(
        inventory_record_index,
        reinterpret_cast<PositionalRectangle_1_00*>(out_position)
    );
  } else /* if (running_game_version >= GameVersion::k1_07Beta) */ {
    GetGlobalInventoryPosition_1_07(
        inventory_record_index,
        inventory_arrange_mode,
        reinterpret_cast<PositionalRectangle_1_00*>(out_position)
    );
  }
}

void GetGlobalInventoryPosition_1_00(
    std::uint32_t inventory_record_index,
    PositionalRectangle_1_00* out_position
) {
  mapi::CallStdcallFunction(
      GetGameAddress().raw_address(),
      inventory_record_index,
      out_position
  );
}

void GetGlobalInventoryPosition_1_07(
    std::uint32_t inventory_record_index,
    std::uint32_t inventory_arrange_mode,
    PositionalRectangle_1_00* out_position
) {
  mapi::CallStdcallFunction(
      GetGameAddress().raw_address(),
      inventory_record_index,
      inventory_arrange_mode,
      out_position
  );
}

} // namespace d2::d2common
