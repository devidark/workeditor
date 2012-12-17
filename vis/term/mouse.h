/*!
 *  \brief  Статус мыши.
 *
 *  \author Alex Medveschek
 *  \date   2011-11-01
 */

#pragma once

#include <stdint.h>

namespace NVis {

//! Mouse status
typedef uint32_t MouseStatus;

enum EMouseStatus {
    msNothing           = 0,
    msLeftPressed       = 0x00000001,
    msLeftReleased      = 0x00000002,
    msLeftClicked       = 0x00000004,
    msLeftDblClicked    = 0x00000008,
    msRightPressed      = 0x00000010,
    msRightReleased     = 0x00000020,
    msRightClicked      = 0x00000040,
    msRightDblClicked   = 0x00000080,
    msMiddlePressed     = 0x00000100,
    msMiddleReleased    = 0x00000200,
    msMiddleClicked     = 0x00000400,
    msMiddleDblClicked  = 0x00000800,
    msScrollDown        = 0x00001000,
    msScrollUp          = 0x00002000,
    /*! \todo ???
    msShiftPressed      = 0x00010000,
    msCtrlPressed       = 0x00020000,
    msAltPressed        = 0x00040000,
    */
    msMove              = 0x80000000
};

}   // NVis
