/*
 * mciapi.h
 *
 * This file is part of the ReactOS CRT package.
 *
 * Contributors:
 *   Timo Kreuzer(timo.kreuzer@reactos.org)
 *
 * THIS SOFTWARE IS NOT COPYRIGHTED
 *
 * This source code is offered for use in the public domain.You may
 * use, modify or distribute it freely.
 *
 * This code is distributed in the hope that it will be useful but
 * WITHOUT ANY WARRANTY.ALL WARRANTIES, EXPRESS OR IMPLIED ARE HEREBY
 * DISCLAIMED.This includes but is not limited to warranties of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#pragma once

#define _MCIAPI_H_

//#include <apiset.h>
//#include <apisetcconv.h>
#include <mmsyscom.h>

#ifdef __cplusplus
//extern "C" {
#endif

#define MCIERR_INVALID_DEVICE_ID       (MCIERR_BASE+1)
#define MCIERR_UNRECOGNIZED_KEYWORD    (MCIERR_BASE+3)
#define MCIERR_UNRECOGNIZED_COMMAND    (MCIERR_BASE+5)
#define MCIERR_HARDWARE                (MCIERR_BASE+6)
#define MCIERR_INVALID_DEVICE_NAME     (MCIERR_BASE+7)
#define MCIERR_OUT_OF_MEMORY           (MCIERR_BASE+8)
#define MCIERR_DEVICE_OPEN             (MCIERR_BASE+9)
#define MCIERR_CANNOT_LOAD_DRIVER      (MCIERR_BASE+10)
#define MCIERR_MISSING_COMMAND_STRING  (MCIERR_BASE+11)
#define MCIERR_PARAM_OVERFLOW          (MCIERR_BASE+12)
#define MCIERR_MISSING_STRING_ARGUMENT (MCIERR_BASE+13)
#define MCIERR_BAD_INTEGER             (MCIERR_BASE+14)
#define MCIERR_PARSER_INTERNAL         (MCIERR_BASE+15)
#define MCIERR_DRIVER_INTERNAL         (MCIERR_BASE+16)
#define MCIERR_MISSING_PARAMETER       (MCIERR_BASE+17)
#define MCIERR_UNSUPPORTED_FUNCTION    (MCIERR_BASE+18)
#define MCIERR_FILE_NOT_FOUND          (MCIERR_BASE+19)
#define MCIERR_DEVICE_NOT_READY        (MCIERR_BASE+20)
#define MCIERR_INTERNAL                (MCIERR_BASE+21)
#define MCIERR_DRIVER                  (MCIERR_BASE+22)
#define MCIERR_CANNOT_USE_ALL          (MCIERR_BASE+23)
#define MCIERR_MULTIPLE                (MCIERR_BASE+24)
#define MCIERR_EXTENSION_NOT_FOUND     (MCIERR_BASE+25)
#define MCIERR_OUTOFRANGE              (MCIERR_BASE+26)
#define MCIERR_FLAGS_NOT_COMPATIBLE    (MCIERR_BASE+28)
#define MCIERR_FILE_NOT_SAVED          (MCIERR_BASE+30)
#define MCIERR_DEVICE_TYPE_REQUIRED    (MCIERR_BASE+31)
#define MCIERR_DEVICE_LOCKED           (MCIERR_BASE+32)
#define MCIERR_DUPLICATE_ALIAS         (MCIERR_BASE+33)
#define MCIERR_BAD_CONSTANT            (MCIERR_BASE+34)
#define MCIERR_MUST_USE_SHAREABLE      (MCIERR_BASE+35)
#define MCIERR_MISSING_DEVICE_NAME     (MCIERR_BASE+36)
#define MCIERR_BAD_TIME_FORMAT         (MCIERR_BASE+37)
#define MCIERR_NO_CLOSING_QUOTE        (MCIERR_BASE+38)
#define MCIERR_DUPLICATE_FLAGS         (MCIERR_BASE+39)
#define MCIERR_INVALID_FILE            (MCIERR_BASE+40)
#define MCIERR_NULL_PARAMETER_BLOCK    (MCIERR_BASE+41)
#define MCIERR_UNNAMED_RESOURCE        (MCIERR_BASE+42)
#define MCIERR_NEW_REQUIRES_ALIAS      (MCIERR_BASE+43)
#define MCIERR_NOTIFY_ON_AUTO_OPEN     (MCIERR_BASE+44)
#define MCIERR_NO_ELEMENT_ALLOWED      (MCIERR_BASE+45)
#define MCIERR_NONAPPLICABLE_FUNCTION  (MCIERR_BASE+46)
#define MCIERR_ILLEGAL_FOR_AUTO_OPEN   (MCIERR_BASE+47)
#define MCIERR_FILENAME_REQUIRED       (MCIERR_BASE+48)
#define MCIERR_EXTRA_CHARACTERS        (MCIERR_BASE+49)
#define MCIERR_DEVICE_NOT_INSTALLED    (MCIERR_BASE+50)
#define MCIERR_GET_CD                  (MCIERR_BASE+51)
#define MCIERR_SET_CD                  (MCIERR_BASE+52)
#define MCIERR_SET_DRIVE               (MCIERR_BASE+53)
#define MCIERR_DEVICE_LENGTH           (MCIERR_BASE+54)
#define MCIERR_DEVICE_ORD_LENGTH       (MCIERR_BASE+55)
#define MCIERR_NO_INTEGER              (MCIERR_BASE+56)
#define MCIERR_WAVE_OUTPUTSINUSE       (MCIERR_BASE+64)
#define MCIERR_WAVE_SETOUTPUTINUSE     (MCIERR_BASE+65)
#define MCIERR_WAVE_INPUTSINUSE        (MCIERR_BASE+66)
#define MCIERR_WAVE_SETINPUTINUSE      (MCIERR_BASE+67)
#define MCIERR_WAVE_OUTPUTUNSPECIFIED  (MCIERR_BASE+68)
#define MCIERR_WAVE_INPUTUNSPECIFIED   (MCIERR_BASE+69)
#define MCIERR_WAVE_OUTPUTSUNSUITABLE  (MCIERR_BASE+70)
#define MCIERR_WAVE_SETOUTPUTUNSUITABLE (MCIERR_BASE+71)
#define MCIERR_WAVE_INPUTSUNSUITABLE   (MCIERR_BASE+72)
#define MCIERR_WAVE_SETINPUTUNSUITABLE (MCIERR_BASE+73)
#define MCIERR_SEQ_DIV_INCOMPATIBLE    (MCIERR_BASE+80)
#define MCIERR_SEQ_PORT_INUSE          (MCIERR_BASE+81)
#define MCIERR_SEQ_PORT_NONEXISTENT    (MCIERR_BASE+82)
#define MCIERR_SEQ_PORT_MAPNODEVICE    (MCIERR_BASE+83)
#define MCIERR_SEQ_PORT_MISCERROR      (MCIERR_BASE+84)
#define MCIERR_SEQ_TIMER               (MCIERR_BASE+85)
#define MCIERR_SEQ_PORTUNSPECIFIED     (MCIERR_BASE+86)
#define MCIERR_SEQ_NOMIDIPRESENT       (MCIERR_BASE+87)
#define MCIERR_NO_WINDOW               (MCIERR_BASE+90)
#define MCIERR_CREATEWINDOW            (MCIERR_BASE+91)
#define MCIERR_FILE_READ               (MCIERR_BASE+92)
#define MCIERR_FILE_WRITE              (MCIERR_BASE+93)
#define MCIERR_NO_IDENTITY             (MCIERR_BASE+94)
#define MCIERR_CUSTOM_DRIVER_BASE      (MCIERR_BASE+256)

#define MCI_FIRST         DRV_MCI_FIRST
#define MCI_OPEN          0x803
#define MCI_CLOSE         0x804
#define MCI_ESCAPE        0x805
#define MCI_PLAY          0x806
#define MCI_SEEK          0x807
#define MCI_STOP          0x808
#define MCI_PAUSE         0x809
#define MCI_INFO          0x80A
#define MCI_GETDEVCAPS    0x80B
#define MCI_SPIN          0x80C
#define MCI_SET           0x80D
#define MCI_STEP          0x80E
#define MCI_RECORD        0x80F
#define MCI_SYSINFO       0x810
#define MCI_BREAK         0x811
#define MCI_SAVE          0x813
#define MCI_STATUS        0x814
#define MCI_CUE           0x830
#define MCI_REALIZE       0x840
#define MCI_WINDOW        0x841
#define MCI_PUT           0x842
#define MCI_WHERE         0x843
#define MCI_FREEZE        0x844
#define MCI_UNFREEZE      0x845
#define MCI_LOAD          0x850
#define MCI_CUT           0x851
#define MCI_COPY          0x852
#define MCI_PASTE         0x853
#define MCI_UPDATE        0x854
#define MCI_RESUME        0x855
#define MCI_DELETE        0x856
#define MCI_USER_MESSAGES (DRV_MCI_FIRST+0x400)
#define MCI_LAST          0xFFF

#define MCI_ALL_DEVICE_ID ((MCIDEVICEID)-1)
#define MCI_DEVTYPE_VCR            513
#define MCI_DEVTYPE_VIDEODISC      514
#define MCI_DEVTYPE_OVERLAY        515
#define MCI_DEVTYPE_CD_AUDIO       516
#define MCI_DEVTYPE_DAT            517
#define MCI_DEVTYPE_SCANNER        518
#define MCI_DEVTYPE_ANIMATION      519
#define MCI_DEVTYPE_DIGITAL_VIDEO  520
#define MCI_DEVTYPE_OTHER          521
#define MCI_DEVTYPE_WAVEFORM_AUDIO 522
#define MCI_DEVTYPE_SEQUENCER      523
#define MCI_DEVTYPE_FIRST          MCI_DEVTYPE_VCR
#define MCI_DEVTYPE_LAST           MCI_DEVTYPE_SEQUENCER
#define MCI_DEVTYPE_FIRST_USER     0x1000
#define MCI_MODE_NOT_READY         (MCI_STRING_OFFSET+12)
#define MCI_MODE_STOP              (MCI_STRING_OFFSET+13)
#define MCI_MODE_PLAY              (MCI_STRING_OFFSET+14)
#define MCI_MODE_RECORD            (MCI_STRING_OFFSET+15)
#define MCI_MODE_SEEK              (MCI_STRING_OFFSET+16)
#define MCI_MODE_PAUSE             (MCI_STRING_OFFSET+17)
#define MCI_MODE_OPEN              (MCI_STRING_OFFSET+18)
#define MCI_FORMAT_MILLISECONDS    0
#define MCI_FORMAT_HMS             1
#define MCI_FORMAT_MSF             2
#define MCI_FORMAT_FRAMES          3
#define MCI_FORMAT_SMPTE_24        4
#define MCI_FORMAT_SMPTE_25        5
#define MCI_FORMAT_SMPTE_30        6
#define MCI_FORMAT_SMPTE_30DROP    7
#define MCI_FORMAT_BYTES           8
#define MCI_FORMAT_SAMPLES         9
#define MCI_FORMAT_TMSF            10
#define MCI_MSF_MINUTE(t)        ((BYTE)(t))
#define MCI_MSF_SECOND(t)        ((BYTE)(((WORD)(t))>>8))
#define MCI_MSF_FRAME(t)         ((BYTE)((t)>>16))
#define MCI_MAKE_MSF(m,s,f)      ((DWORD)(((BYTE)(m)|((WORD)(s)<<8))|(((DWORD)(BYTE)(f))<<16)))
#define MCI_TMSF_TRACK(t)        ((BYTE)(t))
#define MCI_TMSF_MINUTE(t)       ((BYTE)(((WORD)(t))>>8))
#define MCI_TMSF_SECOND(t)       ((BYTE)((t)>>16))
#define MCI_TMSF_FRAME(t)        ((BYTE)((t)>>24))
#define MCI_MAKE_TMSF(t,m,s,f)   ((DWORD)(((BYTE)(t)|((WORD)(m)<<8))|(((DWORD)(BYTE)(s)|((WORD)(f)<<8))<<16)))
#define MCI_HMS_HOUR(t)          ((BYTE)(t))
#define MCI_HMS_MINUTE(t)        ((BYTE)(((WORD)(t))>>8))
#define MCI_HMS_SECOND(t)        ((BYTE)((t)>>16))
#define MCI_MAKE_HMS(h,m,s)      ((DWORD)(((BYTE)(h)|((WORD)(m)<<8))|(((DWORD)(BYTE)(s))<<16)))
#define MCI_NOTIFY_SUCCESSFUL             1
#define MCI_NOTIFY_SUPERSEDED             2
#define MCI_NOTIFY_ABORTED                4
#define MCI_NOTIFY_FAILURE                8
#define MCI_NOTIFY                        1
#define MCI_WAIT                          2
#define MCI_FROM                          4
#define MCI_TO                            8
#define MCI_TRACK                         16
#define MCI_OPEN_SHAREABLE                256
#define MCI_OPEN_ELEMENT                  512
#define MCI_OPEN_ALIAS                    1024
#define MCI_OPEN_ELEMENT_ID               2048
#define MCI_OPEN_TYPE_ID                  0x1000
#define MCI_OPEN_TYPE                     0x2000
#define MCI_SEEK_TO_START                 256
#define MCI_SEEK_TO_END                   512
#define MCI_STATUS_ITEM                   256
#define MCI_STATUS_START                  512
#define MCI_STATUS_LENGTH                 1
#define MCI_STATUS_POSITION               2
#define MCI_STATUS_NUMBER_OF_TRACKS       3
#define MCI_STATUS_MODE                   4
#define MCI_STATUS_MEDIA_PRESENT          5
#define MCI_STATUS_TIME_FORMAT            6
#define MCI_STATUS_READY                  7
#define MCI_STATUS_CURRENT_TRACK          8
#define MCI_INFO_PRODUCT                  256
#define MCI_INFO_FILE                     512
#define MCI_INFO_MEDIA_UPC                1024
#define MCI_INFO_MEDIA_IDENTITY           2048
#define MCI_INFO_NAME                     0x1000
#define MCI_INFO_COPYRIGHT                0x2000
#define MCI_GETDEVCAPS_ITEM               256
#define MCI_GETDEVCAPS_CAN_RECORD         1
#define MCI_GETDEVCAPS_HAS_AUDIO          2
#define MCI_GETDEVCAPS_HAS_VIDEO          3
#define MCI_GETDEVCAPS_DEVICE_TYPE        4
#define MCI_GETDEVCAPS_USES_FILES         5
#define MCI_GETDEVCAPS_COMPOUND_DEVICE    6
#define MCI_GETDEVCAPS_CAN_EJECT          7
#define MCI_GETDEVCAPS_CAN_PLAY           8
#define MCI_GETDEVCAPS_CAN_SAVE           9
#define MCI_SYSINFO_QUANTITY              256
#define MCI_SYSINFO_OPEN                  512
#define MCI_SYSINFO_NAME                  1024
#define MCI_SYSINFO_INSTALLNAME           2048
#define MCI_SET_DOOR_OPEN                 256
#define MCI_SET_DOOR_CLOSED               512
#define MCI_SET_TIME_FORMAT               1024
#define MCI_SET_AUDIO                     2048
#define MCI_SET_VIDEO                     0x1000
#define MCI_SET_ON                        0x2000
#define MCI_SET_OFF                       0x4000
#define MCI_SET_AUDIO_ALL                 0
#define MCI_SET_AUDIO_LEFT                1
#define MCI_SET_AUDIO_RIGHT               2
#define MCI_BREAK_KEY                     256
#define MCI_BREAK_HWND                    512
#define MCI_BREAK_OFF                     1024
#define MCI_RECORD_INSERT                 256
#define MCI_RECORD_OVERWRITE              512
#define MCI_SAVE_FILE                     256
#define MCI_LOAD_FILE                     256
#define MCI_VD_MODE_PARK                  (MCI_VD_OFFSET+1)
#define MCI_VD_MEDIA_CLV                  (MCI_VD_OFFSET+2)
#define MCI_VD_MEDIA_CAV                  (MCI_VD_OFFSET+3)
#define MCI_VD_MEDIA_OTHER                (MCI_VD_OFFSET+4)
#define MCI_VD_FORMAT_TRACK               0x4001
#define MCI_VD_PLAY_REVERSE               0x10000
#define MCI_VD_PLAY_FAST                  0x20000
#define MCI_VD_PLAY_SPEED                 0x40000
#define MCI_VD_PLAY_SCAN                  0x80000
#define MCI_VD_PLAY_SLOW                  0x100000
#define MCI_VD_SEEK_REVERSE               0x10000
#define MCI_VD_STATUS_SPEED               0x4002
#define MCI_VD_STATUS_FORWARD             0x4003
#define MCI_VD_STATUS_MEDIA_TYPE          0x4004
#define MCI_VD_STATUS_SIDE                0x4005
#define MCI_VD_STATUS_DISC_SIZE           0x4006
#define MCI_VD_GETDEVCAPS_CLV             0x10000
#define MCI_VD_GETDEVCAPS_CAV             0x20000
#define MCI_VD_SPIN_UP                    0x10000
#define MCI_VD_SPIN_DOWN                  0x20000
#define MCI_VD_GETDEVCAPS_CAN_REVERSE     0x4002
#define MCI_VD_GETDEVCAPS_FAST_RATE       0x4003
#define MCI_VD_GETDEVCAPS_SLOW_RATE       0x4004
#define MCI_VD_GETDEVCAPS_NORMAL_RATE     0x4005
#define MCI_VD_STEP_FRAMES                0x10000
#define MCI_VD_STEP_REVERSE               0x20000
#define MCI_VD_ESCAPE_STRING              256
#define MCI_CDA_STATUS_TYPE_TRACK         0x4001
#define MCI_CDA_TRACK_AUDIO               MCI_CD_OFFSET
#define MCI_CDA_TRACK_OTHER               (MCI_CD_OFFSET+1)
#define MCI_WAVE_PCM                      MCI_WAVE_OFFSET
#define MCI_WAVE_MAPPER                   (MCI_WAVE_OFFSET+1)

#define MCI_WAVE_OPEN_BUFFER              0x10000
#define MCI_WAVE_SET_FORMATTAG            0x10000
#define MCI_WAVE_SET_CHANNELS             0x20000
#define MCI_WAVE_SET_SAMPLESPERSEC        0x40000
#define MCI_WAVE_SET_AVGBYTESPERSEC       0x80000
#define MCI_WAVE_SET_BLOCKALIGN           0x100000
#define MCI_WAVE_SET_BITSPERSAMPLE        0x200000
#define MCI_WAVE_INPUT                    0x400000
#define MCI_WAVE_OUTPUT                   0x800000
#define MCI_WAVE_STATUS_FORMATTAG         0x4001
#define MCI_WAVE_STATUS_CHANNELS          0x4002
#define MCI_WAVE_STATUS_SAMPLESPERSEC     0x4003
#define MCI_WAVE_STATUS_AVGBYTESPERSEC    0x4004
#define MCI_WAVE_STATUS_BLOCKALIGN        0x4005
#define MCI_WAVE_STATUS_BITSPERSAMPLE     0x4006
#define MCI_WAVE_STATUS_LEVEL             0x4007
#define MCI_WAVE_SET_ANYINPUT             0x4000000
#define MCI_WAVE_SET_ANYOUTPUT            0x8000000
#define MCI_WAVE_GETDEVCAPS_INPUTS        0x4001
#define MCI_WAVE_GETDEVCAPS_OUTPUTS       0x4002
#define MCI_SEQ_DIV_PPQN                  MCI_SEQ_OFFSET
#define MCI_SEQ_DIV_SMPTE_24              (MCI_SEQ_OFFSET+1)
#define MCI_SEQ_DIV_SMPTE_25              (MCI_SEQ_OFFSET+2)
#define MCI_SEQ_DIV_SMPTE_30DROP          (MCI_SEQ_OFFSET+3)
#define MCI_SEQ_DIV_SMPTE_30              (MCI_SEQ_OFFSET+4)
#define MCI_SEQ_FORMAT_SONGPTR            0x4001
#define MCI_SEQ_FILE                      0x4002
#define MCI_SEQ_MIDI                      0x4003
#define MCI_SEQ_SMPTE                     0x4004
#define MCI_SEQ_NONE                      65533
#define MCI_SEQ_MAPPER                    65535
#define MCI_SEQ_STATUS_TEMPO              0x4002
#define MCI_SEQ_STATUS_PORT               0x4003
#define MCI_SEQ_STATUS_SLAVE              0x4007
#define MCI_SEQ_STATUS_MASTER             0x4008
#define MCI_SEQ_STATUS_OFFSET             0x4009
#define MCI_SEQ_STATUS_DIVTYPE            0x400A
#define MCI_SEQ_STATUS_NAME               0x400B
#define MCI_SEQ_STATUS_COPYRIGHT          0x400C
#define MCI_SEQ_SET_TEMPO                 0x10000
#define MCI_SEQ_SET_PORT                  0x20000
#define MCI_SEQ_SET_SLAVE                 0x40000
#define MCI_SEQ_SET_MASTER                0x80000
#define MCI_SEQ_SET_OFFSET                0x1000000
#define MCI_ANIM_OPEN_WS                  0x10000
#define MCI_ANIM_OPEN_PARENT              0x20000
#define MCI_ANIM_OPEN_NOSTATIC            0x40000
#define MCI_ANIM_PLAY_SPEED               0x10000
#define MCI_ANIM_PLAY_REVERSE             0x20000
#define MCI_ANIM_PLAY_FAST                0x40000
#define MCI_ANIM_PLAY_SLOW                0x80000
#define MCI_ANIM_PLAY_SCAN                0x100000
#define MCI_ANIM_STEP_REVERSE             0x10000
#define MCI_ANIM_STEP_FRAMES              0x20000
#define MCI_ANIM_STATUS_SPEED             0x4001
#define MCI_ANIM_STATUS_FORWARD           0x4002
#define MCI_ANIM_STATUS_HWND              0x4003
#define MCI_ANIM_STATUS_HPAL              0x4004
#define MCI_ANIM_STATUS_STRETCH           0x4005
#define MCI_ANIM_INFO_TEXT                0x10000
#define MCI_ANIM_GETDEVCAPS_CAN_REVERSE   0x4001
#define MCI_ANIM_GETDEVCAPS_FAST_RATE     0x4002
#define MCI_ANIM_GETDEVCAPS_SLOW_RATE     0x4003
#define MCI_ANIM_GETDEVCAPS_NORMAL_RATE   0x4004
#define MCI_ANIM_GETDEVCAPS_PALETTES      0x4006
#define MCI_ANIM_GETDEVCAPS_CAN_STRETCH   0x4007
#define MCI_ANIM_GETDEVCAPS_MAX_WINDOWS   0x4008
#define MCI_ANIM_REALIZE_NORM             0x10000
#define MCI_ANIM_REALIZE_BKGD             0x20000
#define MCI_ANIM_WINDOW_HWND              0x10000
#define MCI_ANIM_WINDOW_STATE             0x40000
#define MCI_ANIM_WINDOW_TEXT              0x80000
#define MCI_ANIM_WINDOW_ENABLE_STRETCH    0x100000
#define MCI_ANIM_WINDOW_DISABLE_STRETCH   0x200000
#define MCI_ANIM_WINDOW_DEFAULT           0xL
#define MCI_ANIM_RECT                     0x10000
#define MCI_ANIM_PUT_SOURCE               0x20000
#define MCI_ANIM_PUT_DESTINATION          0x40000
#define MCI_ANIM_WHERE_SOURCE             0x20000
#define MCI_ANIM_WHERE_DESTINATION        0x40000
#define MCI_ANIM_UPDATE_HDC               0x20000
#define MCI_OVLY_OPEN_WS                  0x10000
#define MCI_OVLY_OPEN_PARENT              0x20000
#define MCI_OVLY_STATUS_HWND              0x4001
#define MCI_OVLY_STATUS_STRETCH           0x4002
#define MCI_OVLY_INFO_TEXT                0x10000
#define MCI_OVLY_GETDEVCAPS_CAN_STRETCH   0x4001
#define MCI_OVLY_GETDEVCAPS_CAN_FREEZE    0x4002
#define MCI_OVLY_GETDEVCAPS_MAX_WINDOWS   0x4003
#define MCI_OVLY_WINDOW_HWND              0x10000
#define MCI_OVLY_WINDOW_STATE             0x40000
#define MCI_OVLY_WINDOW_TEXT              0x80000
#define MCI_OVLY_WINDOW_ENABLE_STRETCH    0x100000
#define MCI_OVLY_WINDOW_DISABLE_STRETCH   0x200000
#define MCI_OVLY_WINDOW_DEFAULT           0xL
#define MCI_OVLY_RECT                     0x10000
#define MCI_OVLY_PUT_SOURCE               0x20000
#define MCI_OVLY_PUT_DESTINATION          0x40000
#define MCI_OVLY_PUT_FRAME                0x80000
#define MCI_OVLY_PUT_VIDEO                0x100000
#define MCI_OVLY_WHERE_SOURCE             0x20000
#define MCI_OVLY_WHERE_DESTINATION        0x40000
#define MCI_OVLY_WHERE_FRAME              0x80000
#define MCI_OVLY_WHERE_VIDEO              0x100000
#ifdef _WINE
#define MCI_SOUND                         0x0812
#define MCI_SOUND_NAME                    0x00000100L
#endif

#ifndef _MCIERROR_
#define _MCIERROR_
typedef DWORD MCIERROR;
#endif

#ifndef _MCIDEVICEID_
#define _MCIDEVICEID_
typedef UINT MCIDEVICEID;
#endif

typedef UINT(CALLBACK* YIELDPROC)(MCIDEVICEID, DWORD);

typedef struct tagMCI_GENERIC_PARMS {
    DWORD_PTR dwCallback;
} MCI_GENERIC_PARMS, * PMCI_GENERIC_PARMS, * LPMCI_GENERIC_PARMS;

typedef struct tagMCI_OPEN_PARMSA {
    DWORD_PTR dwCallback;
    MCIDEVICEID wDeviceID;
    LPCSTR lpstrDeviceType;
    LPCSTR lpstrElementName;
    LPCSTR lpstrAlias;
} MCI_OPEN_PARMSA, * PMCI_OPEN_PARMSA, * LPMCI_OPEN_PARMSA;

typedef struct tagMCI_OPEN_PARMSW {
    DWORD_PTR dwCallback;
    MCIDEVICEID wDeviceID;
    LPCWSTR lpstrDeviceType;
    LPCWSTR lpstrElementName;
    LPCWSTR lpstrAlias;
} MCI_OPEN_PARMSW, * PMCI_OPEN_PARMSW, * LPMCI_OPEN_PARMSW;

typedef struct tagMCI_PLAY_PARMS {
    DWORD_PTR dwCallback;
    DWORD dwFrom;
    DWORD dwTo;
} MCI_PLAY_PARMS, * PMCI_PLAY_PARMS, * LPMCI_PLAY_PARMS;

typedef struct tagMCI_SEEK_PARMS {
    DWORD_PTR dwCallback;
    DWORD dwTo;
} MCI_SEEK_PARMS, * PMCI_SEEK_PARMS, * LPMCI_SEEK_PARMS;

#ifdef _WINE
typedef struct tagMCI_SOUND_PARMSA {
    DWORD_PTR   dwCallback;
    LPCSTR      lpstrSoundName;
} MCI_SOUND_PARMSA, * LPMCI_SOUND_PARMSA;

typedef struct tagMCI_SOUND_PARMSW {
    DWORD_PTR   dwCallback;
    LPCWSTR     lpstrSoundName;
} MCI_SOUND_PARMSW, * LPMCI_SOUND_PARMSW;

#ifdef UNICODE
typedef MCI_SOUND_PARMSW MCI_SOUND_PARMS;
#else
typedef MCI_SOUND_PARMSA MCI_SOUND_PARMS;
#endif
#endif

typedef struct tagMCI_STATUS_PARMS {
    DWORD_PTR dwCallback;
    DWORD_PTR dwReturn;
    DWORD dwItem;
    DWORD dwTrack;
} MCI_STATUS_PARMS, * PMCI_STATUS_PARMS, * LPMCI_STATUS_PARMS;

typedef struct tagMCI_INFO_PARMSA {
    DWORD_PTR dwCallback;
    LPSTR lpstrReturn;
    DWORD dwRetSize;
} MCI_INFO_PARMSA, * LPMCI_INFO_PARMSA;

typedef struct tagMCI_INFO_PARMSW {
    DWORD_PTR dwCallback;
    LPWSTR lpstrReturn;
    DWORD dwRetSize;
} MCI_INFO_PARMSW, * LPMCI_INFO_PARMSW;

typedef struct tagMCI_GETDEVCAPS_PARMS {
    DWORD_PTR dwCallback;
    DWORD dwReturn;
    DWORD dwItem;
} MCI_GETDEVCAPS_PARMS, * PMCI_GETDEVCAPS_PARMS, * LPMCI_GETDEVCAPS_PARMS;

typedef struct tagMCI_SYSINFO_PARMSA {
    DWORD_PTR dwCallback;
    LPSTR lpstrReturn;
    DWORD dwRetSize;
    DWORD dwNumber;
    UINT wDeviceType;
} MCI_SYSINFO_PARMSA, * PMCI_SYSINFO_PARMSA, * LPMCI_SYSINFO_PARMSA;

typedef struct tagMCI_SYSINFO_PARMSW {
    DWORD_PTR dwCallback;
    LPWSTR lpstrReturn;
    DWORD dwRetSize;
    DWORD dwNumber;
    UINT wDeviceType;
} MCI_SYSINFO_PARMSW, * PMCI_SYSINFO_PARMSW, * LPMCI_SYSINFO_PARMSW;

typedef struct tagMCI_SET_PARMS {
    DWORD_PTR dwCallback;
    DWORD dwTimeFormat;
    DWORD dwAudio;
} MCI_SET_PARMS, * PMCI_SET_PARMS, * LPMCI_SET_PARMS;

typedef struct tagMCI_BREAK_PARMS {
    DWORD_PTR dwCallback;
    int nVirtKey;
    HWND hwndBreak;
} MCI_BREAK_PARMS, * PMCI_BREAK_PARMS, * LPMCI_BREAK_PARMS;

typedef struct tagMCI_SAVE_PARMSA {
    DWORD_PTR dwCallback;
    LPCSTR lpfilename;
} MCI_SAVE_PARMSA, * PMCI_SAVE_PARMSA, * LPMCI_SAVE_PARMSA;

typedef struct tagMCI_SAVE_PARMSW {
    DWORD_PTR dwCallback;
    LPCWSTR lpfilename;
} MCI_SAVE_PARMSW, * PMCI_SAVE_PARMSW, * LPMCI_SAVE_PARMSW;

typedef struct tagMCI_LOAD_PARMSA {
    DWORD_PTR dwCallback;
    LPCSTR lpfilename;
} MCI_LOAD_PARMSA, * PMCI_LOAD_PARMSA, * LPMCI_LOAD_PARMSA;

typedef struct tagMCI_LOAD_PARMSW {
    DWORD_PTR dwCallback;
    LPCWSTR lpfilename;
} MCI_LOAD_PARMSW, * PMCI_LOAD_PARMSW, * LPMCI_LOAD_PARMSW;

typedef struct tagMCI_RECORD_PARMS {
    DWORD_PTR dwCallback;
    DWORD dwFrom;
    DWORD dwTo;
} MCI_RECORD_PARMS, * LPMCI_RECORD_PARMS;

typedef struct tagMCI_VD_PLAY_PARMS {
    DWORD_PTR dwCallback;
    DWORD dwFrom;
    DWORD dwTo;
    DWORD dwSpeed;
} MCI_VD_PLAY_PARMS, * PMCI_VD_PLAY_PARMS, * LPMCI_VD_PLAY_PARMS;

typedef struct tagMCI_VD_STEP_PARMS {
    DWORD_PTR dwCallback;
    DWORD dwFrames;
} MCI_VD_STEP_PARMS, * PMCI_VD_STEP_PARMS, * LPMCI_VD_STEP_PARMS;

typedef struct tagMCI_VD_ESCAPE_PARMSA {
    DWORD_PTR dwCallback;
    LPCSTR lpstrCommand;
} MCI_VD_ESCAPE_PARMSA, * PMCI_VD_ESCAPE_PARMSA, * LPMCI_VD_ESCAPE_PARMSA;

typedef struct tagMCI_VD_ESCAPE_PARMSW {
    DWORD_PTR dwCallback;
    LPCWSTR lpstrCommand;
} MCI_VD_ESCAPE_PARMSW, * PMCI_VD_ESCAPE_PARMSW, * LPMCI_VD_ESCAPE_PARMSW;

typedef struct tagMCI_WAVE_OPEN_PARMSA {
    DWORD_PTR dwCallback;
    MCIDEVICEID wDeviceID;
    LPCSTR lpstrDeviceType;
    LPCSTR lpstrElementName;
    LPCSTR lpstrAlias;
    DWORD dwBufferSeconds;
} MCI_WAVE_OPEN_PARMSA, * PMCI_WAVE_OPEN_PARMSA, * LPMCI_WAVE_OPEN_PARMSA;

typedef struct tagMCI_WAVE_OPEN_PARMSW {
    DWORD_PTR dwCallback;
    MCIDEVICEID wDeviceID;
    LPCWSTR lpstrDeviceType;
    LPCWSTR lpstrElementName;
    LPCWSTR lpstrAlias;
    DWORD dwBufferSeconds;
} MCI_WAVE_OPEN_PARMSW, * PMCI_WAVE_OPEN_PARMSW, * LPMCI_WAVE_OPEN_PARMSW;

typedef struct tagMCI_WAVE_DELETE_PARMS {
    DWORD_PTR dwCallback;
    DWORD dwFrom;
    DWORD dwTo;
} MCI_WAVE_DELETE_PARMS, * PMCI_WAVE_DELETE_PARMS, * LPMCI_WAVE_DELETE_PARMS;

typedef struct tagMCI_WAVE_SET_PARMS {
    DWORD_PTR dwCallback;
    DWORD dwTimeFormat;
    DWORD dwAudio;
    UINT wInput;
    UINT wOutput;
#ifdef _WIN64
    DWORD wFormatTag;
    DWORD nChannels;
#else
    WORD wFormatTag;
    WORD wReserved2;
    WORD nChannels;
    WORD wReserved3;
#endif
    DWORD nSamplesPerSec;
    DWORD nAvgBytesPerSec;
#ifdef _WIN64
    DWORD nBlockAlign;
    DWORD wBitsPerSample;
#else
    WORD nBlockAlign;
    WORD wReserved4;
    WORD wBitsPerSample;
    WORD wReserved5;
#endif
} MCI_WAVE_SET_PARMS, * PMCI_WAVE_SET_PARMS, * LPMCI_WAVE_SET_PARMS;

MCIERROR
WINAPI
mciSendCommandA(
    _In_ MCIDEVICEID,
    _In_ UINT,
    _In_opt_ DWORD_PTR,
    _In_opt_ DWORD_PTR);

MCIERROR
WINAPI
mciSendCommandW(
    _In_ MCIDEVICEID,
    _In_ UINT,
    _In_opt_ DWORD_PTR,
    _In_opt_ DWORD_PTR);

MCIERROR
WINAPI
mciSendStringA(
    _In_ LPCSTR lpstrCommand,
    _Out_writes_opt_(uReturnLength) LPSTR lpstrReturnString,
    _In_ UINT uReturnLength,
    _In_opt_ HWND hwndCallback);

MCIERROR
WINAPI
mciSendStringW(
    _In_ LPCWSTR lpstrCommand,
    _Out_writes_opt_(uReturnLength) LPWSTR lpstrReturnString,
    _In_ UINT uReturnLength,
    _In_opt_ HWND hwndCallback);

MCIDEVICEID WINAPI mciGetDeviceIDA(_In_ LPCSTR);
MCIDEVICEID WINAPI mciGetDeviceIDW(_In_ LPCWSTR);
MCIDEVICEID WINAPI mciGetDeviceIDFromElementIDA(_In_ DWORD, _In_ LPCSTR);
MCIDEVICEID WINAPI mciGetDeviceIDFromElementIDW(_In_ DWORD, _In_ LPCWSTR);

BOOL
WINAPI
mciGetErrorStringA(
    _In_ MCIERROR mcierr,
    _Out_writes_(cchText) LPSTR pszText,
    _In_ UINT cchText);

BOOL
WINAPI
mciGetErrorStringW(
    _In_ MCIERROR mcierr,
    _Out_writes_(cchText) LPWSTR pszText,
    _In_ UINT cchText);

BOOL WINAPI mciSetYieldProc(_In_ MCIDEVICEID, _In_opt_ YIELDPROC, _In_ DWORD);
HTASK WINAPI mciGetCreatorTask(_In_ MCIDEVICEID);
YIELDPROC WINAPI mciGetYieldProc(_In_ MCIDEVICEID, _In_ PDWORD);

