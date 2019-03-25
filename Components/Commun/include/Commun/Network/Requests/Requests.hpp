//!
//! @file Requests.hpp
//! @author jbruel
//! @date 12/11/18
//!

#ifndef SPACEBATTLE_CLIENT_REQUESTS_HPP
# define SPACEBATTLE_CLIENT_REQUESTS_HPP

# include "Commun/Network/Requests/KeepAliveReq.hpp"
# include "Commun/Network/Requests/AuthenticateReq.hpp"
# include "Commun/Network/Requests/AuthenticateResp.hpp"
# include "Commun/Network/Requests/GetRoomListReq.hpp"
# include "Commun/Network/Requests/GetRoomListResp.hpp"
# include "Commun/Network/Requests/CreateRoomReq.hpp"
# include "Commun/Network/Requests/CreateRoomResp.hpp"
# include "Commun/Network/Requests/JoinRoomReq.hpp"
# include "Commun/Network/Requests/JoinRoomResp.hpp"
# include "Commun/Network/Requests/ViewRoomReq.hpp"
# include "Commun/Network/Requests/ViewRoomResp.hpp"
# include "Commun/Network/Requests/ExitRoomReq.hpp"
# include "Commun/Network/Requests/LaunchGameReq.hpp"
# include "Commun/Network/Requests/LaunchGameResp.hpp"
# include "Commun/Network/Requests/LobbyStateUpdateResp.hpp"
# include "Commun/Network/Requests/SetUserBattleshipReq.hpp"
# include "Commun/Network/Requests/SetUserBattleshipResp.hpp"
# include "Commun/Network/Requests/SendChatMsgReq.hpp"
# include "Commun/Network/Requests/BroadcastChatMsgResp.hpp"
# include "Commun/Network/Requests/ShootShipReq.hpp"
# include "Commun/Network/Requests/ShootShipResp.hpp"
# include "Commun/Network/Requests/EndGameStatusReq.hpp"
# include "Commun/Network/Requests/GameReadyToLaunchReq.hpp"
# include "Commun/Network/Requests/YourTurnToPlayReq.hpp"

#endif //SPACEBATTLE_CLIENT_REQUESTS_HPP
