#ifndef THREAD_ID_FORMATTER
#define THREAD_ID_FORMATTER

#include <iostream>
#include <format>
#include <thread>
#include <sstream>

template <>
struct std::formatter<std::thread::id>
{
    constexpr auto parse(std::format_parse_context &ctx)
    {
        return ctx.begin();
    }

    auto format(const std::thread::id &id, std::format_context &ctx) const
    {
        std::ostringstream oss;
        oss << id;
        return std::format_to(ctx.out(), "{}", oss.str());
    }
};

#endif