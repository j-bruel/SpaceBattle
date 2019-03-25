//
// Created by grosso_a on 13/11/18.
//


#include <gtest/gtest.h>
#include "Engine/Room/Ship.hpp"

//!
//! @test Check the ship initialisation
//!
TEST (Ship, LoadParts)
{
    spcbttl::server::engine::Ship   ship1({10});
    spcbttl::server::engine::Ship   ship4({0,1,2,3});
    spcbttl::server::engine::Ship   ship5({0,9,18,27,36});
}

//!
//! @test Validate the ship coherency
//!
TEST (Ship, Validate)
{
    spcbttl::server::engine::Ship   ship_one({99});
    spcbttl::server::engine::Ship   ship_double({42,42});
    spcbttl::server::engine::Ship   ship_horizontal({0,1,2,3});
    spcbttl::server::engine::Ship   ship_vertical({0,10,20,30,40});
    spcbttl::server::engine::Ship   ship_out({97,107});
    spcbttl::server::engine::Ship   ship_discontinue_horizontal({0,1,3});
    spcbttl::server::engine::Ship   ship_discontinue_vertical({23,43,53,63});
    spcbttl::server::engine::Ship   ship_diagonal({0,11,22,33});

    ASSERT_TRUE(ship_one.validate());
    ASSERT_TRUE(ship_horizontal.validate());
    ASSERT_TRUE(ship_vertical.validate());
    ASSERT_FALSE(ship_out.validate());
    ASSERT_FALSE(ship_double.validate());
    ASSERT_FALSE(ship_discontinue_horizontal.validate());
    ASSERT_FALSE(ship_discontinue_vertical.validate());
    ASSERT_FALSE(ship_diagonal.validate());
}

//!
//! @test Check ship part status change on shoot and detect ship destroyed
//!
TEST (Ship, Shoot_Destroy)
{
    spcbttl::server::engine::Ship       ship_one({10});
    spcbttl::server::engine::Ship       ship_horizontal({0,1,2,3});

    ASSERT_EQ((*std::next(ship_one.parts().begin(), 0))->coordinate(), 10);
    ASSERT_EQ((*std::next(ship_one.parts().begin(), 0))->status(), spcbttl::server::engine::Ship::GOOD);
    (*std::next(ship_one.parts().begin(), 0))->shoot();
    ASSERT_EQ((*std::next(ship_one.parts().begin(), 0))->status(), spcbttl::server::engine::Ship::DESTROYED);
    ASSERT_TRUE(ship_one.destroyed());
    ASSERT_EQ((*std::next(ship_horizontal.parts().begin(), 2))->coordinate(), 2);
    ASSERT_EQ((*std::next(ship_horizontal.parts().begin(), 2))->status(), spcbttl::server::engine::Ship::GOOD);
    (*std::next(ship_horizontal.parts().begin(), 2))->shoot();
    ASSERT_EQ((*std::next(ship_horizontal.parts().begin(), 2))->status(), spcbttl::server::engine::Ship::DESTROYED);
    ASSERT_FALSE(ship_horizontal.destroyed());
    (*std::next(ship_horizontal.parts().begin(), 0))->shoot();
    (*std::next(ship_horizontal.parts().begin(), 1))->shoot();
    (*std::next(ship_horizontal.parts().begin(), 3))->shoot();
    ASSERT_TRUE(ship_horizontal.destroyed());
}
