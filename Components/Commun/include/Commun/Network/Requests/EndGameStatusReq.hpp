//!
//! @file EndGameStatusReq.hpp
//! @author jbruel
//! @date 19/11/18
//!

#ifndef SPACEBATTLE_SERVER_ENDGAMESTATUSREQ_HPP
# define SPACEBATTLE_SERVER_ENDGAMESTATUSREQ_HPP

# include "IRequest.hpp"
# include <string>
#include <Commun/Engine/FinalGameStatus.hpp>

//!
//! @namespace spcbttl
//!
namespace spcbttl
{
//!
//! @namespace commun
//!
namespace commun
{
//!
//! @namespace net
//!
namespace net
{
//!
//! @namespace req
//!
namespace req
{
    //!
    //! @class EndGameStatusReq
    //! @brief EndGameStatus request.
    //!
    class   EndGameStatusReq : public IRequest
    {
    private:
        engine::FinalGameStatus mFinalGameStatus; //!< Final game status.

    public:
        MSGPACK_DEFINE(mFinalGameStatus);

    public:
        //!
        //! @brief Default constructor.
        //!
        EndGameStatusReq() = default;
        //!
        //! @brief Copy constructor.
        //! @param endGameStatusReq End game status request.
        //!
        EndGameStatusReq(const EndGameStatusReq &endGameStatusReq) : IRequest(endGameStatusReq), mFinalGameStatus(endGameStatusReq.mFinalGameStatus) { }
        //!
        //! @brief Equal operator overload.
        //! @param endGameStatusReq End game status request.
        //! @return Request copy.
        //!
        EndGameStatusReq    &operator=(const EndGameStatusReq &endGameStatusReq)
        {
            mFinalGameStatus = endGameStatusReq.mFinalGameStatus;
            return ((*this));
        }
        //!
        //! @brief Destructor.
        //!
        ~EndGameStatusReq() override = default;

    public:
        //!
        //! @brief Extract request type.
        //! @return Request type.
        //!
        inline Type getType() const override { return (Type::END_GAME_STATUS_REQ); }

    public:
        //!
        //! @brief Set final game status.
        //! @param finalGameStatus Game status.
        //!
        inline void                     setFinalGameStatus(engine::FinalGameStatus finalGameStatus) { mFinalGameStatus = finalGameStatus; }
        //!
        //! @brief Extract game status.
        //! @return Game status.
        //!
        inline engine::FinalGameStatus  getFinalGameStatus() const { return (mFinalGameStatus); }
    };

}
}
}
}

#endif //SPACEBATTLE_SERVER_ENDGAMESTATUSREQ_HPP
