//!
//! @file SpaceBattle.hpp
//! @author jbruel
//! @date 01/11/18
//!

#ifndef SPACEBATTLE_SERVER_SPACEBATTLE_HPP
# define SPACEBATTLE_SERVER_SPACEBATTLE_HPP

# include "Conf/OptionsHandler.hpp"
# include "Engine/PacketDispatcher.hpp"

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
//! @namespace core
//!
namespace core
{

    //!
    //! @class SpaceBattle
    //! @brief SpaceBattle game main class.
    //!
    class   SpaceBattle
    {
    private:
        conf::OptionsHandler    mOptionsHandler; //!< Options handler.
        engine::PacketDispatcher::TRoomManager mRoomManager; //!< Room manager.
        spcbttl::server::engine::PacketDispatcher mPacketDispatcher; //!< PacketDispatcher.

    public:
        //!
        //! @brief Constructor
        //!
        SpaceBattle();
        //!
        //! @brief Copy constructor.
        //! @warning Not available.
        //!
        SpaceBattle(const SpaceBattle &) = delete;
        //!
        //! @brief Equal operator overload.
        //! @warning Not available.
        //!
        SpaceBattle &operator=(const SpaceBattle &) = delete;
        //!
        //! @brief Destructor.
        //!
        ~SpaceBattle() = default;

    public:
        //!
        //! @brief Initialize spacebattle server
        //! @param argc Number arguments.
        //! @param argv Arguments.
        //!
        void    init(int argc, const char * const *argv);
        //!
        //! @brief Launch spacebattle server.
        //!
        void    run();

    private:
        //!
        //! @brief Initialize application options.
        //! @param argc Number arguments.
        //! @param argv Arguments.
        //!
        void    initOptionsApp(int argc, const char * const *argv);
        //!
        //! @brief Initialize logs
        //!
        void    initLog();
    };

}
}
}

#endif //SPACEBATTLE_SERVER_SPACEBATTLE_HPP
