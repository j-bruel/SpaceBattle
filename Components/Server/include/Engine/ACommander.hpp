//
// Created by grosso_a on 12/11/18.
//

#ifndef T_CPP_SPACEBATTLE_2018_COMMANDER_HPP
#define T_CPP_SPACEBATTLE_2018_COMMANDER_HPP

#include <functional>
#include <boost/thread/thread.hpp>
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
            /**
             * @brief This abstract class associate member function to id;
             * @tparam NB_COMMANDS
             * @tparam CLASS
             * @tparam PARAM
             */
            template <unsigned int NB_COMMANDS, typename CLASS, typename PARAM>
            class ACommander
            {
            public:
                typedef ACommander<NB_COMMANDS, CLASS, PARAM>                           TCommander;
                typedef std::function<void (CLASS &, TCommander&, PARAM)>               TCommand;

            private:
                std::array<TCommand*, NB_COMMANDS>                      _commands;
                boost::shared_mutex                                     _command_lock;
                CLASS                                                   &_cls;

            protected:
                /**
                 * @brief This function is the default function called is id is invalid or function not set.
                 * This function as to be defined in children classes.
                 * @param id : The command identifier.
                 * @param param : The parameter passed in exec_command call.
                 */
                virtual void notExist(unsigned int id, PARAM param) = 0;

            public:
                ACommander(CLASS &cls): _cls(cls)
                {
                    boost::unique_lock<boost::shared_mutex> lock{this->_command_lock};
                    for (unsigned int it=0; it < NB_COMMANDS; it++) {
                        _commands[it] = nullptr;
                    }
                }

                virtual ~ACommander()
                {
                    boost::unique_lock<boost::shared_mutex> lock{this->_command_lock};
                    for (unsigned int it=0; it < NB_COMMANDS; it++) {
                        if (_commands[it] != nullptr) {
                            delete _commands[it];
                            _commands[it] = nullptr;
                        }
                    }
                }

            protected:
                /**
                 * @brief This function associate a TCommand (function pointer) to a free id.
                 * @param id : The id used in association.
                 * @param cls : The function class member used in association.
                 */
                void set_command(unsigned int id, TCommand *cls)
                {
                    boost::unique_lock<boost::shared_mutex> lock{this->_command_lock};
                    if (id >= NB_COMMANDS) {
                        LOG_(commun::tool::log::IN_CONSOLE, plog::error)
                            << "ACommander: command id:" << int(id) << " is invalid.";
                    } else if (_commands[id] != nullptr) {
                        LOG_(commun::tool::log::IN_CONSOLE, plog::warning)
                            << "ACommander: command id:" << int(id) << " is already set.";
                    } else {
                        _commands[id] = cls;
                    }
                }

                /**
                 * @brief This function exec the TCommand attached to id.
                 * @param id : The id used in association.
                 * @param param : The parameter passed to function.
                 */
                void exec_command(unsigned int id, PARAM param)
                {
                    boost::shared_lock<boost::shared_mutex> lock{this->_command_lock};
                    if (id < NB_COMMANDS && _commands[id] != nullptr) {
                        (*this->_commands[id])(_cls, *this, param);
                    } else {
                        notExist(id, param);
                    }
                }
            };
        }
    }
}

#endif //T_CPP_SPACEBATTLE_2018_COMMANDER_HPP
