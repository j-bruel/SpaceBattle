//!
//! @file OptionsHandler.hpp
//! @brief Application options handler.
//! @author jbruel
//! @date 01/11/2018
//!

#ifndef SPACEBATTLE_SERVER_CONF_OPTIONSHANDLER_HPP
# define SPACEBATTLE_SERVER_CONF_OPTIONSHANDLER_HPP

# include <boost/program_options.hpp>

//!
//! @namespace spcbttl
//!
namespace spcbttl
{
//!
//! @namespace server
//!
namespace server
{
//!
//! @namespace conf
//!
namespace conf
{
    //!
    //! @class OptionsHandler
    //! @brief Application options handler.
    //!
    class   OptionsHandler
    {
    private:
        //!
        //! @var const unsigned int HelpMinSizeLine
        //! @brief Min description option number line.
        //!
        const unsigned int    HelpMinSizeLine = 0;
        //!
        //! @var const unsigned int HelpMaxSizeLine
        //! @brief Max description option number line.
        //!
        const unsigned int    HelpMaxSizeLine = 10;

    private:
        std::string mLogFilePath; //!< Log file path.
        size_t      mPort; //!< Host port.
        std::string mAddress; //!< Host IP address.
        bool        mVerbose; //!< Allow logging.

    private:
        boost::program_options::options_description mCmdlineOptions; //!< Boost options description.

    public:
        //!
        //! @brief Constructor
        //!
        OptionsHandler();
        //!
        //! @brief Copy constructor.
        //! @warning Not available.
        //!
        OptionsHandler(const OptionsHandler &) = delete;
        //!
        //! @brief Equal operator overload.
        //! @warning Not available.
        //!
        OptionsHandler    &operator=(const OptionsHandler &) = delete;
        //!
        //! @brief Destructor.
        //!
        ~OptionsHandler() = default;
      
    public:
        //!
        //! @brief Initialize application arguments.
        //! @param argc Number argument.
        //! @param argv Arguments.
        //!
        void    loadBinaryArguments(int argc, const char * const *argv);

    public:
        //!
        //! @brief Show application help.
        //! @param appName Application name
        //!
        void    showHelp(const char *appName) const;

    public:
        //!
        //! @brief Extract log file path.
        //! @return Log file path.
        //!
        inline const std::string    &getLogFilePath() const { return (mLogFilePath); }
        //!
        //! @brief Extract host IP address.
        //! @return IP Adress
        //!
        inline const std::string    &getHostAddress() const { return (mAddress); }
        //!
        //! @brief Extract host port.
        //! @return Port.
        //!
        inline size_t               getPort() const { return (mPort); }
        //!
        //! @brief Extract verbose mode status.
        //! @return Enable Verbose mode.
        //!
        inline bool                 getVerboseMode() const { return (mVerbose); }
    };
}
}
}

#endif //SPACEBATTLE_SERVER_CONF_OPTIONSHANDLER_HPP
