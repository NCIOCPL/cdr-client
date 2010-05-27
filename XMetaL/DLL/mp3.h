/*
 * $Id$
 */
// #include <stdio.h>         // For FILE definition.

typedef struct {
    unsigned sync;          // 0xFFE for valid header
    unsigned version;       // 0: MPEG 2.0; 1: MPEG 1.0; 2: MPEG 2.5 [sic!]
    unsigned layer;         // 2: layer 1, 1: layer 2, 0: layer 3 [sic!]
    bool     hasCrc;        // flag for optional checksum (on header only)
    unsigned bitrate;       // 4-bit index into bit-rate lookup table
    unsigned freq;          // 2-bit index into frequency table
    bool     padding;       // flag indicating frame has one extra slot
    unsigned priv;          // application-specific flag
    unsigned mode;          // 0-3: stereo, joint stereo, dual stereo, mono
    unsigned modeExtension; // for joint stereo, to control frequency subbands
    bool     copyright;     // flag indicating whether audio is copyrighted
    bool     original;      // false for copies of the original media
    unsigned emphasis;      // 0-3: none, 50/15ms, reserved, CCIT J.17
} MP3HEADER;

typedef struct {
    char          title[31];
    char          artist[31];
    char          album[31];
    char          year[5];
    char          comment[31];
    unsigned char track;
    unsigned char genre;
} MP3TAG;

typedef struct {
    CFile*    fp;
    long      dataSize;
    bool      validHeader;
    bool      validTag;
    MP3HEADER header;
    int       seconds;
    int       nFrames;
    int       badFrames;
    MP3TAG    tag;
    bool      variableBitrate;
    int       vbrAverage;
} MP3INFO;

extern bool getMp3Info(MP3INFO* mp3, CFile& file);
