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

#include "../../../../include/cxx/game_struct/d2_cel_file/d2_cel_file_api.hpp"

#include "../../../../include/cxx/game_function/d2win/d2win_load_cel_file.hpp"
#include "../../../../include/cxx/game_function/d2win/d2win_unload_cel_file.hpp"

namespace d2 {

CelFile_Api::CelFile_Api() :
    cel_file_(nullptr),
    is_open_(false) {
}

CelFile_Api::CelFile_Api(
    const char* cel_file_path,
    bool is_dcc_else_dc6
) : cel_file_(nullptr),
    is_open_(false) {
  this->Open(cel_file_path, is_dcc_else_dc6);
}

CelFile_Api::CelFile_Api(CelFile_Api&& other) noexcept :
    cel_file_(std::move(other.cel_file_)),
    is_open_(std::move(other.is_open_)) {
  other.cel_file_ = nullptr;
  other.is_open_ = false;
}

CelFile_Api::~CelFile_Api() {
  this->Close();
}

CelFile_Api& CelFile_Api::operator=(CelFile_Api&& other) noexcept {
  this->cel_file_ = std::move(other.cel_file_);
  this->is_open_ = std::move(other.is_open_);

  other.cel_file_ = nullptr;
  other.is_open_ = false;

  return *this;
}

CelFile_Api::operator CelFile_View() const noexcept {
  return CelFile_View(this->Get());
}

CelFile* CelFile_Api::Get_() noexcept {
  const auto* const_this = this;

  return const_cast<CelFile*>(const_this->Get());
}

const CelFile* CelFile_Api::Get() const noexcept {
  return std::visit(
      [](const auto& actual_cel_file) {
        return reinterpret_cast<const CelFile*>(actual_cel_file);
      },
      this->cel_file_
  );
}

void CelFile_Api::Close() {
  if (!this->IsOpen()) {
    return;
  }

  d2win::UnloadCelFile(this->Get_());
  this->cel_file_ = nullptr;
  this->is_open_ = false;
}

bool CelFile_Api::DrawFrame(
    int position_x,
    int position_y,
    unsigned int direction,
    unsigned int frame
) {
  CelFile_Wrapper wrapper(this->Get_());

  return wrapper.DrawFrame(
      position_x,
      position_y,
      direction,
      frame
  );
}

bool CelFile_Api::DrawFrame(
    int position_x,
    int position_y,
    unsigned int direction,
    unsigned int frame,
    const DrawCelFileFrameOptions& frame_options
) {
  CelFile_Wrapper wrapper(this->Get_());

  return wrapper.DrawFrame(
      position_x,
      position_y,
      direction,
      frame,
      frame_options
  );
}

bool CelFile_Api::DrawAllFrames(
    int position_x,
    int position_y,
    unsigned int columns,
    unsigned int rows
) {
  CelFile_Wrapper wrapper(this->Get_());

  return wrapper.DrawAllFrames(
      position_x,
      position_y,
      columns,
      rows
  );
}

bool CelFile_Api::DrawAllFrames(
    int position_x,
    int position_y,
    unsigned int columns,
    unsigned int rows,
    const DrawAllCelFileFramesOptions& all_frames_options
) {
  CelFile_Wrapper wrapper(this->Get_());

  return wrapper.DrawAllFrames(
      position_x,
      position_y,
      columns,
      rows,
      all_frames_options
  );
}

Cel_View CelFile_Api::GetCel(unsigned int direction, unsigned int frame) {
  CelFile_Wrapper wrapper(this->Get_());

  return wrapper.GetCel(direction, frame);
}

bool CelFile_Api::IsOpen() const {
  return this->is_open_;
}

void CelFile_Api::Open(
    const char* cel_file_path,
    bool is_dcc_else_dc6
) {
  this->Close();

  this->cel_file_ = CreateVariant(
      cel_file_path,
      is_dcc_else_dc6
  );

  this->is_open_ = (this->Get_() != nullptr);
}

CelFile_Api::ApiVariant CelFile_Api::CreateVariant(
    const char* cel_file_path,
    bool is_dcc_else_dc6
) {
  CelFile* cel_file = d2win::LoadCelFile(
      cel_file_path,
      is_dcc_else_dc6
  );

  return reinterpret_cast<CelFile_1_00*>(cel_file);
}

} // namespace d2
