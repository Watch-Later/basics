// Copyright - xxxx-2019 - Jan Christoph Uhde <Jan@UhdeJC.com>
#pragma once
#ifndef OBI_UTIL_LOGGING_DEFINITIONS_HEADER
#define OBI_UTIL_LOGGING_DEFINITIONS_HEADER


#ifndef OBI_LOGGING_DEFAULT_LEVEL
#define OBI_LOGGING_DEFAULT_LEVEL info
#endif

#include <obi/macros/compiler.hpp>
#include <string>
#include <map>
#include <mutex>

namespace obi { namespace logging {
    namespace _detail {
        struct logtopic;
        OBI_EXPORT_VC extern std::mutex logmutex;
        OBI_EXPORT_VC extern std::map<int,logtopic*> topics_map;
    }

    enum class level : int {
        fatal = 0,
        error = 20,
        warn  = 40,
        info  = 60,
        debug = 80,
        trace = 100
    };

    namespace _detail {
        inline std::string const level_to_str(level level_){
            using namespace std::literals::string_literals;
            switch (level_) {
                case level::fatal:
                    return "fatal"s;
                case level::error:
                    return "error"s;
                case level::warn:
                    return "warning"s;
                case level::info:
                    return "info"s;
                case level::debug:
                    return "debug"s;
                case level::trace:
                    return "trace"s;
                default:
                    return "unknown"s;
            }
        }

        struct logtopic {
            logtopic(int id_, std::string&& name_, level activation_level_)
                :id(id_)
                ,activation_level(activation_level_)
                ,name(std::move(name_))
                {
                    topics_map[id]=this;
                }

            logtopic(logtopic&& other) = default;
            logtopic(logtopic const& other) = default;

            int id;
            static const level default_level = level::OBI_LOGGING_DEFAULT_LEVEL;
            // using info is the default
            level activation_level;
            std::string name;

        };

    } // _detail

    namespace configuration {
        extern std::map<int,_detail::logtopic*> topics;
        // logging is configured globally via these variables
        // configure logging before you start logging!!!
        OBI_EXPORT_VC extern bool prefix_newline;
        OBI_EXPORT_VC extern bool append_newline;
        OBI_EXPORT_VC extern bool prefix_newline;
        OBI_EXPORT_VC extern bool append_newline;
        OBI_EXPORT_VC extern bool threads;
        OBI_EXPORT_VC extern bool filename;
        OBI_EXPORT_VC extern bool function;
        OBI_EXPORT_VC extern bool vim;
        OBI_EXPORT_VC extern bool gdb;
    }

    namespace topic {
        // can not be inline as they shall be mutable
        OBI_EXPORT_VC extern _detail::logtopic no_topic;
        OBI_EXPORT_VC extern _detail::logtopic dev;
        OBI_EXPORT_VC extern _detail::logtopic network;
        OBI_EXPORT_VC extern _detail::logtopic engine;
    }

}} // obi::util::logging
#endif // OBI_UTIL_LOGGING_DEFINITIONS_HEADER
