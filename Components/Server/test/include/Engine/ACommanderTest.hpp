//
// Created by grosso_a on 14/11/18.
//

#ifndef T_CPP_SPACEBATTLE_2018_ACOMMANDERTEST_HPP
#define T_CPP_SPACEBATTLE_2018_ACOMMANDERTEST_HPP

#include "Engine/ACommander.hpp"
#include <plog/Log.h>
#include <Commun/Tools/Log/Idx.hpp>

namespace spcbttl
{
    //!
    //! @namespace server
    //!
    namespace server
    {
        //!
        //! @namespace engine
        //!
        namespace engine
        {
        class ACommanderTest: public ACommander<3, ACommanderTest, std::shared_ptr<int>>
            {
            private:

                virtual void notExist(unsigned int id, std::shared_ptr<int>)
                {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::error)
                        << "ACommander: command id:" << int(id) << " is invalid.";
                }

            public:
                ACommanderTest(): ACommander<3, ACommanderTest, std::shared_ptr<int>>(*this)
                {
                    TCommand *failed = new TCommand(&ACommanderTest::func1);
                    this->set_command(0, new TCommand(&ACommanderTest::func0));
                    this->set_command(1, new TCommand(&ACommanderTest::func1));
                    this->set_command(1, failed);
                    delete failed;
                }

                void execute(unsigned int command_id, std::shared_ptr<int> param)
                {
                    this->exec_command(command_id, param);
                }

                void func0(TCommander &, std::shared_ptr<int> param)
                {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::debug)
                        << "ACommanderTest: command id:0 param:" << *param;
                }

                void func1(TCommander &, std::shared_ptr<int> param)
                {
                    LOG_(commun::tool::log::IN_CONSOLE, plog::debug)
                                << "ACommanderTest: command id:1 param:" << *param;
                }
            };
        }
    }
}

#endif //T_CPP_SPACEBATTLE_2018_ACOMMANDERTEST_HPP
