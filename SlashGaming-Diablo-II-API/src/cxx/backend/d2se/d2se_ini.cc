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

#include "d2se_ini.hpp"

#include <windows.h>

#include <array>

#include <mdc/wchar_t/filew.h>
#include <mdc/error/exit_on_error.hpp>
#include "d2se_game_version.hpp"

namespace d2::d2se::intern::d2se_ini {

GameVersion GetGameVersion() {
  static constexpr ::std::size_t kVersionStringCapacity =
      game_version::kVersionStringCapacity;

  ::std::array<wchar_t, kVersionStringCapacity> version_c_str;

  // Read the string from the INI file.
  DWORD get_private_profile_string_result = GetPrivateProfileStringW(
      L"Protected",
      L"D2Core",
      L"",
      version_c_str.data(),
      kVersionStringCapacity,
      kFileName
  );

  if (get_private_profile_string_result == kVersionStringCapacity - 1) {
    ::mdc::error::ExitOnGeneralError(
        L"Error",
        L"D2SE_SETUP.ini Diablo II version string is invalid.",
        __FILEW__,
        __LINE__
    );

    return static_cast<::d2::GameVersion>(-1);
  }

  // Determine the game version that corresponds to the version string.
  return game_version::GuessGameVersion(version_c_str.data());
}

::d2::VideoMode GetVideoMode() {
  int renderer_value = GetPrivateProfileIntW(
      L"USERSETTINGS",
      L"Renderer",
      -1,
      kFileName
  );

  switch (renderer_value) {
    case 0: {
      int window_mode_value = GetPrivateProfileIntW(
          L"USERSETTINGS",
          L"WindowMode",
          -1,
          kFileName
      );

      return (window_mode_value == 1)
          ? ::d2::VideoMode::kGdi
          : ::d2::VideoMode::kDirectDraw;
    }

    case 1: {
      return ::d2::VideoMode::kDirect3D;
    }

    case 3: {
      return ::d2::VideoMode::kGlide;
    }

    default: {
      ::mdc::error::ExitOnConstantMappingError(
          __FILEW__,
          __LINE__,
          renderer_value
      );

      return static_cast<::d2::VideoMode>(-1);
    }
  }
}

} // namespace d2::d2se::intern::d2se_ini
