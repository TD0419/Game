//
// Created by PC-USER on 2018/08/15.
//

#ifndef NATIVE_ROLING_GAME_PLAYER_H
#define NATIVE_ROLING_GAME_PLAYER_H

class Player
{
public:
    void SetPosition(float x, float y, float z)
    {
        m_position_x = x;
        m_position_y = y;
        m_position_z = z;
    }

private:
    float m_position_x;
    float m_position_y;
    float m_position_z;
};

#endif //NATIVE_ROLING_GAME_PLAYER_H
