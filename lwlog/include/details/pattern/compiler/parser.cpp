#include "parser.h"

#include "details/flag_data.h"

namespace lwlog::details::pattern_compiler
{
    void parser::init(const char* src, std::size_t size, bool enable_color)
    {
        m_src = src;
        m_size = size;

        m_pos = 0;
        m_pending_literal_begin = 0;

        m_enable_color = enable_color;
    }

    bool parser::parse_sequence(pattern_bytecode::instruction_list& out, char until, bool allow_color)
    {
        while(m_pos < m_size)
        {
            const char current_char{ m_src[m_pos] };
            if (until != '\0' && current_char == until)
            {
                this->flush_pending_literal(out, m_pos);
                ++m_pos;
                m_pending_literal_begin = m_pos;
                return true;
            }

            if (current_char == '\\')
            {
                this->flush_pending_literal(out, m_pos);
                this->emit_literal_instruction(out, m_pos + 1, 1);

                m_pos += 2;
                m_pending_literal_begin = m_pos;

                continue;
            }
            else if (current_char == '%')
            {
                this->flush_pending_literal(out, m_pos);

                pattern_bytecode::field_id id{};
                const std::size_t start{ m_pos };
                if (this->parse_short_token(id) == token_type::builtin)
                {
                    this->emit_field_instruction(out, id, {});
                }
                else
                {
                    const std::size_t len{ static_cast<std::size_t>((start + 1 < m_size) ? 2 : 1) };
                    this->emit_literal_instruction(out, start, len);

                    m_pos = start + len;
                    m_pending_literal_begin = m_pos;
                }

                continue;
            }
            else if (current_char == '{')
            {
                this->flush_pending_literal(out, m_pos);

                if (!this->parse_field(out))
                {
                    return false;
                }

                continue;
            }
            else if (current_char == '.')
            {
                this->flush_pending_literal(out, m_pos);

                if (allow_color && this->parse_color(out))
                {
                    continue;
                }

                this->emit_literal_instruction(out, m_pos, 1);
                ++m_pos;
                m_pending_literal_begin = m_pos;

                continue;
            }

            ++m_pos;
        }

        this->flush_pending_literal(out, m_pos);

        return (until == '\0');
    }

    void parser::emit_literal_instruction(pattern_bytecode::instruction_list& out,
        std::uint16_t offset, std::uint16_t size)
    {
        out.push_back(pattern_bytecode::instruction::make_literal(offset, size));
    }

    void parser::emit_field_instruction(pattern_bytecode::instruction_list& out,
        pattern_bytecode::field_id id, const pattern_bytecode::alignment_info& alignment)
    {
        m_pending_literal_begin = m_pos;

        if (alignment.width == 0)
        {
            out.push_back(pattern_bytecode::instruction::make_field_noalign(id));
            return;
        }

        switch (alignment.side_char)
        {
            case '<': out.push_back(pattern_bytecode::instruction::make_field_left(id, alignment)); return;
            case '>': out.push_back(pattern_bytecode::instruction::make_field_right(id, alignment)); return;
            case '^': out.push_back(pattern_bytecode::instruction::make_field_center(id, alignment)); return;
        }
    }

    void parser::emit_custom_instruction(pattern_bytecode::instruction_list& out, std::uint16_t token_offset, 
        std::uint16_t token_size, std::uint16_t name_offset, std::uint8_t name_size, 
        const pattern_bytecode::alignment_info& alignment)
    {
        m_pending_literal_begin = m_pos;

        if (alignment.width == 0)
        {
            out.push_back(pattern_bytecode::instruction::make_custom_field_noalign(
                token_offset, token_size, name_offset, name_size));
            return;
        }

        switch (alignment.side_char)
        {
        case '<': out.push_back(pattern_bytecode::instruction::make_custom_field_left(
            token_offset, token_size, name_offset, name_size, alignment)); return;
        case '>': out.push_back(pattern_bytecode::instruction::make_custom_field_right(
            token_offset, token_size, name_offset, name_size, alignment)); return;
        case '^': out.push_back(pattern_bytecode::instruction::make_custom_field_center(
            token_offset, token_size, name_offset, name_size, alignment)); return;
        }
    }

    void parser::emit_sgr_begin_instruction(pattern_bytecode::instruction_list& out, std::uint8_t code)
    {
        out.push_back(pattern_bytecode::instruction::make_sgr_begin(code));
    }

    void parser::emit_sgr_end_instruction(pattern_bytecode::instruction_list& out)
    {
        out.push_back(pattern_bytecode::instruction::make_sgr_end());
    }

    void parser::emit_sgr_begin_level_instruction(pattern_bytecode::instruction_list& out)
    {
        out.push_back(pattern_bytecode::instruction::make_sgr_begin_level());
    }

    void parser::flush_pending_literal(pattern_bytecode::instruction_list& out, std::size_t literal_end_offset)
    {
        if (literal_end_offset > m_pending_literal_begin)
        {
            const std::size_t len{ literal_end_offset - m_pending_literal_begin };
            this->emit_literal_instruction(out, m_pending_literal_begin, len);

            m_pending_literal_begin = literal_end_offset;
        }
    }

    token_type parser::parse_short_token(pattern_bytecode::field_id& out)
    {
        if (m_pos + 1 >= m_size)
        {
            return token_type::literal;
        }

        if (!parser::resolve_short_field_id(m_src[m_pos + 1], out))
        {
            return token_type::literal;
        }

        m_pos += 2;

        return token_type::builtin;
    }

    token_type parser::parse_verbose_token(pattern_bytecode::field_id& out_id,
        std::uint16_t& out_name_offset, std::uint8_t& out_name_size)
    {
        const std::size_t name_begin{ m_pos };

        while (m_pos < m_size && m_src[m_pos] != '}')
        {
            ++m_pos;
        }

        if (m_pos >= m_size)
        {
            return token_type::error;
        }

        const std::size_t name_end{ m_pos };
        const std::size_t name_length{ name_end - name_begin };

        if (name_length == 0)
        {
            return token_type::literal;
        }

        const std::string_view name{ m_src + name_begin, name_length };

        if (parser::resolve_verbose_field_id(name, out_id))
        {
            return token_type::builtin;
        }

        out_name_offset = static_cast<std::uint16_t>(name_begin);
        out_name_size = static_cast<std::uint8_t>(name_length);

        return token_type::custom;
    }

    bool parser::parse_alignment_specs(pattern_bytecode::alignment_info& out)
    {
        if (m_pos >= m_size)
        {
            return false;
        }

        char fill_char{ ' ' };
        char side_char{};
        std::uint32_t width{};

        if (parser::is_align(m_src[m_pos]))
        {
            side_char = m_src[m_pos];
            ++m_pos;
        }
        else
        {
            if (m_pos + 1 >= m_size)
            {
                return false;
            }

            fill_char = m_src[m_pos];

            if (!parser::is_align(m_src[m_pos + 1]))
            {
                return false;
            }

            side_char = m_src[m_pos + 1];
            m_pos += 2;
        }


        if (m_pos >= m_size || !parser::is_digit(m_src[m_pos]))
        {
            return false;
        }

        while (m_pos < m_size && parser::is_digit(m_src[m_pos]))
        {
            width = width * 10U + unsigned(m_src[m_pos] - '0');

            if (width > 255u) 
            {
                return false;
            }

            ++m_pos;
        }

        out.fill_char = fill_char;
        out.side_char = side_char;
        out.width = static_cast<std::uint8_t>(width);

        return true;
    }

    bool parser::parse_color(pattern_bytecode::instruction_list& out)
    {
        const std::size_t dot_pos{ m_pos };
        const std::size_t name_begin{ dot_pos + 1 };

        std::size_t name_end{ name_begin };

        while (name_end < m_size && sgr_resolver::is_base_name_char(m_src[name_end]))
        {
            ++name_end;
        }

        if (name_end == name_begin || name_end >= m_size || m_src[name_end] != '(')
        {
            return false;
        }

        const std::string_view token{ m_src + name_begin, name_end - name_begin };

        const bool is_level_token{ (token == "level") };

        std::uint8_t sgr_code{};
        const bool is_valid_sgr{ sgr_resolver::try_resolve_code(token, sgr_code) };


        if (!is_level_token && !is_valid_sgr)
        {
            return false;
        }

        const std::size_t saved_pos{ m_pos };
        const std::size_t saved_literal_begin{ m_pending_literal_begin };
        const std::size_t saved_out_size{ out.size() };

        m_pos = name_end + 1;
        m_pending_literal_begin = m_pos;

        if (m_enable_color)
        {
            if (is_level_token)
            {
                this->emit_sgr_begin_level_instruction(out);
            }
            else
            {
                this->emit_sgr_begin_instruction(out, sgr_code);
            }
        }

        if (!this->parse_sequence(out, ')', false))
        {
            out.resize(saved_out_size);
            m_pos = saved_pos;
            m_pending_literal_begin = saved_literal_begin;
            return false;
        }

        if (m_enable_color)
        {
            this->emit_sgr_end_instruction(out);
        }

        return true;
    }

    bool parser::parse_field(pattern_bytecode::instruction_list& out)
    {
        const auto skip_to_close_brace_and_consume{ [&]() -> bool {
            while (m_pos < m_size && m_src[m_pos] != '}')
            {
                ++m_pos;
            }

            if (m_pos >= m_size)
            {
                return false;
            }

            ++m_pos;

            return true;
        } };

        const std::size_t start{ m_pos };
        ++m_pos;

        m_pending_literal_begin = start;

        if (m_pos >= m_size)
        {
            return false;
        }

        pattern_bytecode::alignment_info alignment{};

        if (m_src[m_pos] == ':')
        {
            ++m_pos;

            if (!this->parse_alignment_specs(alignment))
            {
                if (!skip_to_close_brace_and_consume())
                {
                    return false;
                }

                this->flush_pending_literal(out, m_pos);

                return true;
            }
        }

        pattern_bytecode::field_id id{};

        std::uint16_t name_offset{};
        std::uint8_t  name_lenght{};

        token_type type{ token_type::literal };

        if (m_pos < m_size && m_src[m_pos] == '%')
        {
            type = this->parse_short_token(id);
        }
        else
        {   
            type = this->parse_verbose_token(id, name_offset, name_lenght);
            if(type == token_type::error)
            {
                return false;
            }
        }

        if (m_pos >= m_size || m_src[m_pos] != '}')
        {
            if (!skip_to_close_brace_and_consume())
            {
                return false;
            }

            this->flush_pending_literal(out, m_pos);
            return true;
        }

        ++m_pos;

        switch (type)
        {
        case token_type::literal:
        {
            this->flush_pending_literal(out, m_pos);
            break;
        }
        case token_type::builtin:
        {
            this->emit_field_instruction(out, id, alignment);
            break;
        }
        case token_type::custom:
        {
            const std::uint16_t token_offset{ static_cast<std::uint16_t>(start) };
            const std::uint16_t token_size{ static_cast<std::uint16_t>(m_pos - start) };
            this->emit_custom_instruction(out, token_offset, token_size, name_offset, name_lenght, alignment);
            break;
        }
        default:
        {
            this->flush_pending_literal(out, m_pos);
            break;
        }
        }

        return true;
    }

    bool parser::resolve_short_field_id(char ch, pattern_bytecode::field_id& out)
    {
        switch (ch)
        {
        case flag::level.shortened:         out = pattern_bytecode::field_id::level;         return true;
        case flag::message.shortened:       out = pattern_bytecode::field_id::message;       return true;
        case flag::thread_id.shortened:     out = pattern_bytecode::field_id::thread_id;     return true;
        case flag::process_id.shortened:    out = pattern_bytecode::field_id::process_id;    return true;
        case flag::line.shortened:          out = pattern_bytecode::field_id::line;          return true;
        case flag::file.shortened:          out = pattern_bytecode::field_id::file;          return true;
        case flag::path.shortened:          out = pattern_bytecode::field_id::path;          return true;
        case flag::function.shortened:      out = pattern_bytecode::field_id::function;      return true;
        case flag::topic.shortened:         out = pattern_bytecode::field_id::topic;         return true;
        case flag::full_topic.shortened:    out = pattern_bytecode::field_id::full_topic;    return true;

        case flag::date.shortened:              out = pattern_bytecode::field_id::date;          return true;
        case flag::date_short.shortened:        out = pattern_bytecode::field_id::date_short;    return true;
        case flag::year.shortened:              out = pattern_bytecode::field_id::year;          return true;
        case flag::year_short.shortened:        out = pattern_bytecode::field_id::year_short;    return true;
        case flag::month.shortened:             out = pattern_bytecode::field_id::month;         return true;
        case flag::month_name.shortened:        out = pattern_bytecode::field_id::month_name;    return true;
        case flag::month_name_short.shortened:  out = pattern_bytecode::field_id::month_name_short; return true;
        case flag::day.shortened:               out = pattern_bytecode::field_id::day;           return true;
        case flag::weekday.shortened:           out = pattern_bytecode::field_id::weekday;       return true;
        case flag::weekday_short.shortened:     out = pattern_bytecode::field_id::weekday_short; return true;
        case flag::time.shortened:              out = pattern_bytecode::field_id::time;          return true;
        case flag::hour_clock_24.shortened:     out = pattern_bytecode::field_id::hour_clock_24; return true;
        case flag::hour_clock_12.shortened:     out = pattern_bytecode::field_id::hour_clock_12; return true;
        case flag::ampm.shortened:              out = pattern_bytecode::field_id::ampm;          return true;
        case flag::hour_24.shortened:           out = pattern_bytecode::field_id::hour_24;       return true;
        case flag::hour_12.shortened:           out = pattern_bytecode::field_id::hour_12;       return true;
        case flag::minute.shortened:            out = pattern_bytecode::field_id::minute;        return true;
        case flag::second.shortened:            out = pattern_bytecode::field_id::second;        return true;
        case flag::millisecond.shortened:       out = pattern_bytecode::field_id::millisecond;   return true;
        case flag::microsecond.shortened:       out = pattern_bytecode::field_id::microsecond;   return true;
        case flag::nanosecond.shortened:        out = pattern_bytecode::field_id::nanosecond;    return true;
        default: return false;
        }
    }

    bool parser::resolve_verbose_field_id(std::string_view name, pattern_bytecode::field_id& out)
    {
        if (name == flag::level.verbose)            { out = pattern_bytecode::field_id::level;             return true; }
        else if (name == flag::message.verbose)     { out = pattern_bytecode::field_id::message;           return true; }
        else if (name == flag::thread_id.verbose)   { out = pattern_bytecode::field_id::thread_id;         return true; }
        else if (name == flag::process_id.verbose)  { out = pattern_bytecode::field_id::process_id;        return true; }
        else if (name == flag::line.verbose)        { out = pattern_bytecode::field_id::line;              return true; }
        else if (name == flag::file.verbose)        { out = pattern_bytecode::field_id::file;              return true; }
        else if (name == flag::path.verbose)        { out = pattern_bytecode::field_id::path;              return true; }
        else if (name == flag::function.verbose)    { out = pattern_bytecode::field_id::function;          return true; }
        else if (name == flag::topic.verbose)       { out = pattern_bytecode::field_id::topic;             return true; }
        else if (name == flag::full_topic .verbose) { out = pattern_bytecode::field_id::full_topic;        return true; }

        else if (name == flag::date.verbose)                { out = pattern_bytecode::field_id::date;              return true; }
        else if (name == flag::date_short.verbose)          { out = pattern_bytecode::field_id::date_short;        return true; }
        else if (name == flag::year.verbose)                { out = pattern_bytecode::field_id::year;              return true; }
        else if (name == flag::year_short.verbose)          { out = pattern_bytecode::field_id::year_short;        return true; }
        else if (name == flag::month.verbose)               { out = pattern_bytecode::field_id::month;             return true; }
        else if (name == flag::month_name.verbose)          { out = pattern_bytecode::field_id::month_name;        return true; }
        else if (name == flag::month_name_short.verbose)    { out = pattern_bytecode::field_id::month_name_short;  return true; }
        else if (name == flag::day.verbose)                 { out = pattern_bytecode::field_id::day;               return true; }
        else if (name == flag::weekday.verbose)             { out = pattern_bytecode::field_id::weekday;           return true; }
        else if (name == flag::weekday_short.verbose)       { out = pattern_bytecode::field_id::weekday_short;     return true; }
        else if (name == flag::time.verbose)                { out = pattern_bytecode::field_id::time;              return true; }
        else if (name == flag::hour_clock_24.verbose)       { out = pattern_bytecode::field_id::hour_clock_24;     return true; }
        else if (name == flag::hour_clock_12.verbose)       { out = pattern_bytecode::field_id::hour_clock_12;     return true; }
        else if (name == flag::ampm.verbose)                { out = pattern_bytecode::field_id::ampm;              return true; }
        else if (name == flag::hour_24.verbose)             { out = pattern_bytecode::field_id::hour_24;           return true; }
        else if (name == flag::hour_12.verbose)             { out = pattern_bytecode::field_id::hour_12;           return true; }
        else if (name == flag::minute.verbose)              { out = pattern_bytecode::field_id::minute;            return true; }
        else if (name == flag::second.verbose)              { out = pattern_bytecode::field_id::second;            return true; }
        else if (name == flag::millisecond.verbose)         { out = pattern_bytecode::field_id::millisecond;       return true; }
        else if (name == flag::microsecond.verbose)         { out = pattern_bytecode::field_id::microsecond;       return true; }
        else if (name == flag::nanosecond.verbose)          { out = pattern_bytecode::field_id::nanosecond;        return true; }

        return false;
    }

    constexpr bool parser::is_digit(char c)
    {
        return (c >= '0' && c <= '9');
    }

    constexpr bool parser::is_align(char c)
    {
        return (c == '<' || c == '>' || c == '^');
    }
}