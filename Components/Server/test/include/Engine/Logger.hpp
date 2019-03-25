//
// Created by grosso_a on 25/11/18.
//

#ifndef T_CPP_SPACEBATTLE_2018_LOGGER_HPP
#define T_CPP_SPACEBATTLE_2018_LOGGER_HPP

//!
//! @static
//! @bref Init logger.
//!
static void initLogger()
{
    static bool isInit = false;

    if (!isInit)
    {
        spcbttl::commun::tool::log::initialize(std::string(UTWorkDirectory) + "/utLog/RoomManager", plog::debug, plog::debug);
        isInit = true;
    }
}


#endif //T_CPP_SPACEBATTLE_2018_LOGGER_HPP
