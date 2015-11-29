# rally-clone-game
This is a personal exercise in game development. The main goal is to produce a port of arcade game Rally.

you have to define RALLY_ROOT to point to the project root directory

export RALLY_ROOT=~/projects/rally

you have to have boost installed and variable BOOST_ROOT pointing to its root

export BOOST_ROOT=~/Boost

you have to have cxxtest 4.3 (cxxtest.org) installed in your system and point to it

export CXXTEST_ROOT=~/projects/cxxtest-4.3

The design of this application allows easy substitution of players and UI.

The main logic of the game is in game::CController

The board logic is in board::CBoard



