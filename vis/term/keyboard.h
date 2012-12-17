/*!
 *  \brief  Статус клавиатуры.
 *
 *  \author Alex Medveschek
 *  \date   2011-11-01
 */

#pragma once

#include <stdint.h>

namespace NVis {

//! Keyboard's status (Ctrls + Key code)
typedef int32_t KbStatus;

enum EKbStatus {
    kbShiftPressed = 0x01000000,
    kbCtrlPressed  = 0x02000000,
    kbAltPressed   = 0x04000000
};

}   // NVis
