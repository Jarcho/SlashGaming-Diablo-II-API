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

#ifndef SGD2MAPI_CXX_GAME_LIBRARY_HPP_
#define SGD2MAPI_CXX_GAME_LIBRARY_HPP_

#include <cstdint>
#include <filesystem>
#include <map>

namespace mapi {

/**
 * A class that corresponds to a library used by the game.
 */
class GameLibrary {
 public:
  /**
   * Creates a new instance of a GameLibrary using the library path.
   */
  explicit GameLibrary(const std::filesystem::path& file_path);

  /**
   * Creates a new instance of a GameLibrary using the library path.
   */
  explicit GameLibrary(std::filesystem::path&& file_path);

  GameLibrary(const GameLibrary& rhs) = delete;

  GameLibrary(GameLibrary&& rhs) noexcept;

  virtual ~GameLibrary();

  GameLibrary& operator=(const GameLibrary& rhs) = delete;

  GameLibrary& operator=(GameLibrary&& rhs) noexcept;

  static const GameLibrary& GetGameLibrary(
      const std::filesystem::path& file_path
  );

  /**
   * Returns the base address value of this GameLibrary.
   */
  std::intptr_t base_address() const noexcept;

  /**
   * Returns the library path of this GameLibrary.
   */
  const std::filesystem::path& file_path() const noexcept;

 private:
  std::filesystem::path file_path_;
  std::intptr_t base_address_;

  static std::map<std::filesystem::path, GameLibrary>& GetLibrariesByPaths();

  static std::intptr_t LoadGameLibraryBaseAddress(
      const std::filesystem::path& library_path
  );
};

} // namespace mapi

#endif // SGD2MAPI_CXX_GAME_LIBRARY_HPP_
