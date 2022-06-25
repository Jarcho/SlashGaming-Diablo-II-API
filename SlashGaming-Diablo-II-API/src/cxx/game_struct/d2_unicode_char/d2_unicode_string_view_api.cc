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

#include "../../../../include/cxx/game_struct/d2_unicode_char/d2_unicode_string_view_api.hpp"

#include <windows.h>
#include <stdexcept>

#include <mdc/error/exit_on_error.hpp>
#include <mdc/wchar_t/filew.h>
#include "../../../../include/cxx/game_function/d2lang_function.hpp"
#include "../../../../include/cxx/game_function/d2win_function.hpp"
#include "../../../../include/cxx/game_version.hpp"

namespace d2 {
namespace {

using UnicodeStringView_1_00 = std::basic_string_view<UnicodeChar_1_00>;

} // namespace

UnicodeStringView_Api::UnicodeStringView_Api() noexcept :
    view_([]() {
      return UnicodeStringView_1_00();
    }()) {
}

UnicodeStringView_Api::UnicodeStringView_Api(
    const value_type* s,
    size_type count
) : view_([s, count]() {
      const UnicodeChar_1_00* actual_s =
          reinterpret_cast<const UnicodeChar_1_00*>(s);

      return UnicodeStringView_1_00(actual_s, count);
    }()) {
}

UnicodeStringView_Api::UnicodeStringView_Api(const value_type* s)
  : view_([s]() {
      const UnicodeChar_1_00* actual_s =
          reinterpret_cast<const UnicodeChar_1_00*>(s);

      return UnicodeStringView_1_00(actual_s);
    }()) {
}

UnicodeStringView_Api UnicodeStringView_Api::substr() const {
  return UnicodeStringView_Api(
      std::visit(
          [](const auto& actual_view) {
            return actual_view.substr();
          },
          this->view_
      )
  );
}

UnicodeStringView_Api UnicodeStringView_Api::substr(size_type pos) const {
  return UnicodeStringView_Api(
      std::visit(
          [pos](const auto& actual_view) {
            return actual_view.substr(pos);
          },
          this->view_
      )
  );
}

UnicodeStringView_Api UnicodeStringView_Api::substr(
    size_type pos,
    size_type count
) const {
  return UnicodeStringView_Api(
      std::visit(
          [pos, count](const auto& actual_view) {
            return actual_view.substr(pos, count);
          },
          this->view_
      )
  );
}

int UnicodeStringView_Api::compare(UnicodeStringView_Api v) const noexcept {
  return std::visit(
      [&v](const auto& actual_src_view) {
        using UnicodeStringView_T = std::remove_const_t<
            std::remove_reference_t<decltype(actual_src_view)>
        >;

        UnicodeStringView_T actual_v = std::get<UnicodeStringView_T>(v.view_);

        return actual_src_view.compare(actual_v);
      },
      this->view_
  );
}

int UnicodeStringView_Api::compare(
    size_type pos1,
    size_type count1,
    UnicodeStringView_Api v
) const {
  return std::visit(
      [pos1, count1, &v](const auto& actual_src_view) {
        using UnicodeStringView_T = std::remove_const_t<
            std::remove_reference_t<decltype(actual_src_view)>
        >;

        UnicodeStringView_T actual_v = std::get<UnicodeStringView_T>(v.view_);

        return actual_src_view.compare(pos1, count1, actual_v);
      },
      this->view_
  );
}

int UnicodeStringView_Api::compare(
    size_type pos1,
    size_type count1,
    UnicodeStringView_Api v,
    size_type pos2,
    size_type count2
) const {
  return std::visit(
      [pos1, count1, &v, pos2, count2](const auto& actual_src_view) {
        using UnicodeStringView_T = std::remove_const_t<
            std::remove_reference_t<decltype(actual_src_view)>
        >;

        UnicodeStringView_T actual_v = std::get<UnicodeStringView_T>(v.view_);

        return actual_src_view.compare(pos1, count1, actual_v, pos2, count2);
      },
      this->view_
  );
}

bool UnicodeStringView_Api::starts_with(UnicodeStringView_Api sv) const noexcept {
  return std::visit(
      [&sv](const auto& actual_view) {
        using UnicodeStringView_T = std::remove_const_t<
            std::remove_reference_t<decltype(actual_view)>
        >;

        UnicodeStringView_T actual_sv_data =
            std::get<UnicodeStringView_T>(sv.view_);

        return actual_view.starts_with(actual_sv_data);
      },
      this->view_
  );
}

bool UnicodeStringView_Api::ends_with(UnicodeStringView_Api sv) const noexcept {
  return std::visit(
      [&sv](const auto& actual_view) {
        using UnicodeStringView_T = std::remove_const_t<
            std::remove_reference_t<decltype(actual_view)>
        >;

        UnicodeStringView_T actual_sv_data =
            std::get<UnicodeStringView_T>(sv.view_);

        return actual_view.ends_with(actual_sv_data);
      },
      this->view_
  );
}

UnicodeStringView_Api::size_type UnicodeStringView_Api::find(
    UnicodeStringView_Api v,
    size_type pos
) const noexcept {
  return std::visit(
      [&v, pos](const auto& actual_view) {
        using UnicodeStringView_T = std::remove_const_t<
            std::remove_reference_t<decltype(actual_view)>
        >;
        using UnicodeChar_T = typename UnicodeStringView_T::value_type;

        UnicodeStringView_T& actual_v =
            std::get<UnicodeStringView_T>(v.view_);

        return actual_view.find(actual_v, pos);
      },
      this->view_
  );
}

void UnicodeStringView_Api::Draw(int position_x, int position_y) const {
  DrawTextOptions options;
  options.position_x_behavior = DrawPositionXBehavior::kLeft;
  options.text_color = TextColor::kWhite;

  this->Draw(position_x, position_y, options);
}

void UnicodeStringView_Api::Draw(
    int position_x,
    int position_y,
    const DrawTextOptions& options
) const {
  int draw_width = d2win::GetUnicodeTextNDrawWidth(
      this->data(),
      this->length()
  );

  int adjusted_position_x;
  switch (options.position_x_behavior) {
    case DrawPositionXBehavior::kLeft: {
      adjusted_position_x = position_x;
      break;
    }

    case DrawPositionXBehavior::kCenter: {
      adjusted_position_x = position_x - (draw_width / 2);
      break;
    }

    case DrawPositionXBehavior::kRight: {
      adjusted_position_x = position_x - draw_width;
      break;
    }

    default: {
      ::mdc::error::ExitOnGeneralError(
          L"Error",
          L"Invalid value for DrawPositionXBehavior: %d.",
          __FILEW__,
          __LINE__,
          static_cast<int>(options.position_x_behavior)
      );

      return;
    }
  }

  d2win::DrawUnicodeText(
      this->data(),
      adjusted_position_x,
      position_y,
      options.text_color,
      false
  );
}

} // namespace d2
