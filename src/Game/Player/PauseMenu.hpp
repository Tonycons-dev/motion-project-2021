/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -PauseMenu.hpp-
 */

#pragma once
#include "Engine/Actor/actBaseActor.hpp"

namespace game::act {

class PauseMenu : public anim::act::ActorBase
{
public:
    struct Options
    {

    };

    void onEnter() override;
    void onUpdate() override;
    void onLeave() override;

    [[nodiscard]]
    inline const std::array<s32, 6>& getPlayerInputBindings() const {
        return mPlayerInputBindings;
    }
    [[nodiscard]]
    inline const bool& isOpen() const noexcept {
        return mPauseToggleState;
    }
private:;
    void(*mPfnOnUpdate)(PauseMenu*);

    void updateWhenClosed();
    void updateWhenOpen();
    void onToggleToClosed();
    void onToggleToOpen();

    std::array<s32, 6> mPlayerInputBindings;
    bool mPauseToggleState = false;
};
}