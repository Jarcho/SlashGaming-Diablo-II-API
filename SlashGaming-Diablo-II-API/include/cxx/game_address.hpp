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

#ifndef SGMAPI_CXX_GAME_ADDRESS_HPP_
#define SGMAPI_CXX_GAME_ADDRESS_HPP_

#include <cstddef>
#include <cstdint>
#include <utility>

#include "default_game_library.hpp"

#include "../dllexport_define.inc"

namespace mapi {

/**
 * A class to store a raw address in memory.
 */
class DLLEXPORT GameAddress {
 public:
  constexpr GameAddress() noexcept
      : GameAddress(0) {
  }

  constexpr std::intptr_t raw_address() const noexcept {
    return this->raw_address_;
  }

  /**
   * Returns a game address that uses a string encoded in 7-bit ASCII to
   * specify a location in game memory.
   */
  static GameAddress FromExportedName(
      ::d2::DefaultLibrary library,
      const char* exported_name
  );

  /**
   * Returns a game address that uses a string encoded in 7-bit ASCII to
   * specify a location in game memory.
   */
  static GameAddress FromExportedName(
      const wchar_t* path,
      const char* exported_name
  );

  /**
   * Returns a game address that uses an offset value to specify a location in
   * game memory.
   */
  static GameAddress FromOffset(
      ::d2::DefaultLibrary library,
      std::ptrdiff_t offset
  );

  /**
   * Returns a game address that uses an offset value to specify a location in
   * game memory.
   */
  static GameAddress FromOffset(
      const wchar_t* path,
      std::ptrdiff_t offset
  );

  /**
   * Returns a game address that uses an ordinal value to specify a location
   * in game memory.
   */
  static GameAddress FromOrdinal(
      ::d2::DefaultLibrary library,
      std::int16_t ordinal
  );

  /**
   * Returns a game address that uses an ordinal value to specify a location
   * in game memory.
   */
  static GameAddress FromOrdinal(
      const wchar_t* path,
      std::int16_t ordinal
  );

  constexpr void swap(GameAddress& game_address) noexcept {
    ::std::swap(this->raw_address_, game_address.raw_address_);
  }

  constexpr void Swap(GameAddress& game_address) noexcept {
    ::std::swap(this->raw_address_, game_address.raw_address_);
  }

 private:
  constexpr explicit GameAddress(std::intptr_t raw_address) noexcept
      : raw_address_(raw_address) {
  }

  std::intptr_t raw_address_;
};

} // namespace mapi

#include "../dllexport_undefine.inc"

#endif // SGMAPI_CXX_GAME_ADDRESS_HPP_
