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

#ifndef SGD2MAPI_CXX_GAME_STRUCT_D2_MPQ_ARCHIVE_HANDLE_D2_MPQ_ARCHIVE_HANDLE_VIEW_HPP_
#define SGD2MAPI_CXX_GAME_STRUCT_D2_MPQ_ARCHIVE_HANDLE_D2_MPQ_ARCHIVE_HANDLE_VIEW_HPP_

#include <cstddef>
#include <variant>

#include "../d2_mpq_archive/d2_mpq_archive_view.hpp"
#include "d2_mpq_archive_handle_struct.hpp"

#include "../../../dllexport_define.inc"

namespace d2 {

class DLLEXPORT MpqArchiveHandle_View {
 public:
  using ViewVariant = std::variant<
      const MpqArchiveHandle_1_00*
  >;

  MpqArchiveHandle_View() = delete;

  MpqArchiveHandle_View(
      const MpqArchiveHandle* mpq_archive_handle
  ) noexcept;

  constexpr explicit MpqArchiveHandle_View(
      ViewVariant mpq_archive_handle
  ) noexcept
      : mpq_archive_handle_(::std::move(mpq_archive_handle)) {
  }

  constexpr MpqArchiveHandle_View(
      const MpqArchiveHandle_View& other
  ) noexcept = default;

  constexpr MpqArchiveHandle_View(
      MpqArchiveHandle_View&& other
  ) noexcept = default;

  ~MpqArchiveHandle_View() noexcept = default;

  constexpr MpqArchiveHandle_View& operator=(
      const MpqArchiveHandle_View& other
  ) noexcept = default;

  constexpr MpqArchiveHandle_View& operator=(
      MpqArchiveHandle_View&& other
  ) noexcept = default;

  constexpr MpqArchiveHandle_View operator[](
      std::size_t index
  ) const noexcept {
    return std::visit(
        [index](const auto& actual_mpq_archive_handle) {
          return MpqArchiveHandle_View(
              &actual_mpq_archive_handle[index]
          );
        },
        this->mpq_archive_handle_
    );
  }

  constexpr const MpqArchiveHandle* Get() const noexcept {
    return std::visit(
        [](const auto& actual_positional_rectangle) {
          return reinterpret_cast<const MpqArchiveHandle*>(
              actual_positional_rectangle
          );
        },
        this->mpq_archive_handle_
    );
  }

  constexpr MpqArchive_View GetMpqArchive() const noexcept {
    return std::visit(
        [](const auto& actual_mpq_archive_handle) {
          return MpqArchive_View(
              actual_mpq_archive_handle->mpq_archive
          );
        },
        this->mpq_archive_handle_
    );
  }

  constexpr const char* GetMpqArchivePath() const noexcept {
    return std::visit(
        [](const auto& actual_mpq_archive_handle) {
          return actual_mpq_archive_handle->mpq_archive_path;
        },
        this->mpq_archive_handle_
    );
  }

 private:
  ViewVariant mpq_archive_handle_;

  static ViewVariant CreateVariant(
      const MpqArchiveHandle* mpq_archive_handle
  );
};

} // namespace d2

#include "../../../dllexport_undefine.inc"
#endif // SGD2MAPI_CXX_GAME_STRUCT_D2_MPQ_ARCHIVE_HANDLE_D2_MPQ_ARCHIVE_HANDLE_VIEW_HPP_
