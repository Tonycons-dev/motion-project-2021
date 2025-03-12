/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -PauseMenu.cpp-
 */

#include "Game/Player/PauseMenu.hpp"
#include "Game/Player/PlayerActor.hpp"
#include "Engine/System/GameSystem.hpp"
#include "Engine/System/ScreenPrint.hpp"


void game::act::PauseMenu::onEnter()
{
    using InputType = MainPlayer::InputType;

    mPlayerInputBindings[InputType::INPUT_DIRECTION_F] = KEY_W;
    mPlayerInputBindings[InputType::INPUT_DIRECTION_B] = KEY_S;
    mPlayerInputBindings[InputType::INPUT_DIRECTION_U] = KEY_SPACE;
    mPlayerInputBindings[InputType::INPUT_DIRECTION_D] = KEY_LEFT_SHIFT;
    mPlayerInputBindings[InputType::INPUT_DIRECTION_R] = KEY_D;
    mPlayerInputBindings[InputType::INPUT_DIRECTION_L] = KEY_A;
}

void game::act::PauseMenu::onUpdate()
{
    if (this->isOpen()) {
        this->updateWhenOpen();
        anim::screenPrintf({96, 16}, 32, FGCOL_OPLEAFY, "Paused.");
    }
    else {
        this->updateWhenClosed();
        anim::screenPrintf({96, 16}, 32, FGCOL_OPLEAFY, "Running.");
    }

    if (IsKeyPressed(KEY_E)) {
        mPauseToggleState = !mPauseToggleState;

        if (mPauseToggleState)
            this->onToggleToOpen();
        else
            this->onToggleToClosed();
    }

}

void game::act::PauseMenu::onLeave()
{

}

void game::act::PauseMenu::updateWhenOpen()
{

}

void game::act::PauseMenu::updateWhenClosed()
{

}

void game::act::PauseMenu::onToggleToClosed()
{

}

void game::act::PauseMenu::onToggleToOpen()
{

}