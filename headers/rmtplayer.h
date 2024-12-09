/*
    rmtplayer.h : Integration of Raster Music Tracker into cc7800
    Copyleft 2023 Bruno STEUX

    This file is distributed as a companion file to cc7800 - a subset of C compiler for the Atari 7800
*/

#ifndef __RMTPLAYER_H__
#define __RMTPLAYER_H__

const char RMT = 1;
const char POKEY = 1;
#ifdef POKEY_AT_450
char *const pokeyaddress = 0x450;
#else
char *const pokeyaddress = 0x4000; 
#endif

char *p_instrstable, *p_trackslbstable, *p_trackshbstable, *p_song;
#define p_tis p_instrstable
char *_ns, *_nr, *_nt;
char rmtreg1, rmtreg2, rmtreg3, _tmp;
char frqaddcmd2;
char rtm_ispeed, rmt_intcount;

#define TRACKS 4
#define track_variables trackn_db
ramchip char trackn_db[TRACKS];
ramchip char trackn_hb[TRACKS];
ramchip char trackn_idx[TRACKS];
ramchip char trackn_pause[TRACKS];
ramchip char trackn_note[TRACKS];
ramchip char trackn_volume[TRACKS];
ramchip char trackn_distor[TRACKS];
ramchip char trackn_shiftfrq[TRACKS];

ramchip char trackn_portafrqc[TRACKS];
ramchip char trackn_portafrqa[TRACKS];
ramchip char trackn_portaspeed[TRACKS];
ramchip char trackn_portaspeeda[TRACKS];
ramchip char trackn_portadepth[TRACKS];

ramchip char trackn_instrx2[TRACKS];
ramchip char trackn_instrdb[TRACKS];
ramchip char trackn_instrhb[TRACKS];
ramchip char trackn_instridx[TRACKS];
ramchip char trackn_instrlen[TRACKS];
ramchip char trackn_instrlop[TRACKS];
ramchip char trackn_instrreachend[TRACKS];
ramchip char trackn_volumeslidedepth[TRACKS];
ramchip char trackn_volumeslidevalue[TRACKS];
ramchip char trackn_volumemin[TRACKS];
ramchip char trackn_effdelay[TRACKS];
ramchip char trackn_effvibratoa[TRACKS];
ramchip char trackn_effvibratobeg[TRACKS];
ramchip char trackn_effvibratoend[TRACKS];
ramchip char trackn_effshift[TRACKS];
ramchip char trackn_tabletypespeed[TRACKS];

ramchip char trackn_tablemode[TRACKS];

ramchip char trackn_tablenote[TRACKS];

ramchip char trackn_tablea[TRACKS];
ramchip char trackn_tableend[TRACKS];
ramchip char trackn_tablelop[TRACKS];
ramchip char trackn_tablespeeda[TRACKS];
ramchip char trackn_command[TRACKS];

ramchip char trackn_outnote[TRACKS];

ramchip char trackn_filter[TRACKS];

ramchip char trackn_audf[TRACKS];
ramchip char trackn_audc[TRACKS];

ramchip char trackn_audctl[TRACKS];

ramchip char v_audctl, v_audctl2, v_speed, v_aspeed, v_bspeed, v_instrspeed, v_ainstrspeed, v_maxtracklen, v_abeat;
ramchip char track_endvariables;

inline void pokey_init(char *song)
{
    // Init RMT music
    X = song;
    Y = song >> 8;
    load(0); // Song line in A register 
    asm("JSR rmt_init", 3);
}

inline void pokey_play()
{
    asm("JSR rmt_play", 3);
}

inline void pokey_mute()
{
    asm("JSR rmt_silence", 3);
}

#include "rmtplayer.asm"
#endif // __RMTPLAYER_H__
