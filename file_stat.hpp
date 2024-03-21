/// @file   file_stat.hpp
/// @brief  File statistics accumulator class: accumulates statistics for files and text lines.
/// @author D.R.Kuvshinov kuvshinovdr at yandex.ru
#ifndef SRCSTATS_FILE_STAT_HPP_INCLUDED
#define SRCSTATS_FILE_STAT_HPP_INCLUDED

#include "stat_accum.hpp"

#include <string_view>


namespace srcstats
{

  /// @brief Files (their lengths in text lines) and lines (their lengths in characters) statistics.
  class File_statistics
  {
  public:
    // Getters

    /// @brief Access read-only files accumulated statistics. File "value" is this file size in text lines.
    [[nodiscard]] constexpr Statistics_accumulator const& files() const noexcept
    {
      return _files;
    }

    /// @brief Access read-only lines accumulated statistics. Line "value" is this line size in characters.
    [[nodiscard]] constexpr Statistics_accumulator const& lines() const noexcept
    {
      return _lines;
    }


    /// @brief       Print files and lines statistics.
    /// @param os    the destination output stream
    /// @param title a text to be output to os before the statistics
    /// @return      os
    std::ostream& print(std::ostream& os, std::string_view title) const
    {
      os << title << '\n';
      _files.print(os, "files", "lines");

      os << '\n';
      _lines.print(os, "lines", "characters");
      
      return os << '\n';
    }

    
    // Mutators

    /// @brief Accumulate a file presented by a preconditioned string_view (lines are delimited with LF characters).
    File_statistics& operator()(String_view file_data) noexcept;

    /// @brief Update with data from another statistics accumulator. 
    constexpr File_statistics& operator()(File_statistics const& stats) noexcept
    {
      _files(stats.files());
      _lines(stats.lines());
      return *this;
    }

  private:
    Statistics_accumulator _files, _lines;
  };

}

#endif//SRCSTATS_FILE_STAT_HPP_INCLUDED
