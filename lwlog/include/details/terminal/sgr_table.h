#pragma once

#include <cstdint>
#include <array>

namespace lwlog::details::terminal
{
    struct sgr_entry
    {
        char seq[6];
        std::uint8_t size;
    };

    constexpr sgr_entry make_sgr_sequence(std::uint8_t code)
    {
        sgr_entry entry{};
        std::uint8_t n{ 2 };

        entry.seq[0] = '\x1b';
        entry.seq[1] = '[';

        if (code >= 100)
        {
            entry.seq[n++] = char('0' + (code / 100));
            entry.seq[n++] = char('0' + ((code / 10) % 10));
            entry.seq[n++] = char('0' + (code % 10));
        }
        else if (code >= 10)
        {
            entry.seq[n++] = char('0' + (code / 10));
            entry.seq[n++] = char('0' + (code % 10));
        }
        else
        {
            entry.seq[n++] = char('0' + code);
        }

        entry.seq[n++] = 'm';
        entry.size = n;

        return entry;
    }

    constexpr std::array<sgr_entry, 256> generate_sgr_table()
    {
        std::array<sgr_entry, 256> table{};

        for (std::uint32_t i = 0; i < 256; ++i)
        {
            table[i] = make_sgr_sequence(i);
        }

        return table;
    }

    inline constexpr auto sgr_table = generate_sgr_table();
}