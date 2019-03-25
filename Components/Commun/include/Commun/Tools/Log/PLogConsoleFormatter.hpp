//!
//! @file PLogConsoleFormatter.hpp
//! @author jbruel
//! @date 01/11/18
//!

#ifndef SPACEBATTLE_SERVER_TOOLS_LOG_PLOGCONSOLEFORMATTER_HPP
# define SPACEBATTLE_SERVER_TOOLS_LOG_PLOGCONSOLEFORMATTER_HPP

# include <plog/Util.h>
# include <plog/Record.h>
# include <iomanip>

//!
//! @namespace plog
//!
namespace plog
{
    //!
    //! @class PLogConsoleFormatter
    //! @brief Console log formatter.
    //!
    class   PLogConsoleFormatter
    {
    public:
        //!
        //! @static
        //! @fn static util::nstring header()
        //! @brief Create log header.
        //! @return Log header format.
        //!
        static util::nstring    header() { return util::nstring(); }

        //!
        //! @static
        //! @fn static util::nstring format(const Record &record)
        //! @brief Generate own log format.
        //! @param record Record information.
        //! @return Log format.
        //!
        static util::nstring    format(const Record &record)
        {
            tm                  t;

            util::localtime_s(&t, &record.getTime().time);
            util::nostringstream ss;
            ss << t.tm_year + 1900 << "-" << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_mon + 1 << PLOG_NSTR("-") << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_mday << PLOG_NSTR(" ");
            ss << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_hour << PLOG_NSTR(":") << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_min << PLOG_NSTR(":") << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_sec << PLOG_NSTR(".") << std::setfill(PLOG_NSTR('0')) << std::setw(3) << record.getTime().millitm << PLOG_NSTR(" ");
            ss << std::setfill(PLOG_NSTR(' ')) << std::setw(5) << std::left << severityToString(record.getSeverity()) << PLOG_NSTR(" ");
            ss << record.getMessage() << PLOG_NSTR("\n");
            return (ss.str());
        }
    };
}

#endif //SPACEBATTLE_SERVER_TOOLS_LOG_PLOGCONSOLEFORMATTER_HPP
