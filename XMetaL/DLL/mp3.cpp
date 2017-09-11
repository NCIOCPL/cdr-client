/*
 * Code to calculate MP3 seconds.  Adapted from mp3info package
 * (http://www.ibiblio.org/mp3info/).
 *
 * See also http://www.mpgedit.org/mpgedit/mpeg_format/mpeghdr.htm.
 *
 * BZIssue::4848
 */
#include "stdafx.h"
#include "mp3.h"
#include <string.h>
#include <ctype.h>

#define FRAME_HEADER_SIZE 4
#define MIN_CONSEC_GOOD_FRAMES 4
#define MIN_FRAME_SIZE 21
#define NUM_SAMPLES 4

// Local functions.
static int  getHeader(CFile* fp, MP3HEADER* h);
static bool findFirstHeader(MP3INFO* mp3);
static int  getNextHeader(MP3INFO* mp3);
static int  frameLength(const MP3HEADER* h);
static int  headerBitrate(const MP3HEADER* h);
static int  headerFrequency(const MP3HEADER* h);
static bool readTag(MP3INFO* mp3);
static void strip(char* s);
static bool sameConstant(const MP3HEADER* h1, const MP3HEADER* h2);

#ifdef TESTMAIN
    int main(int ac, char** av) {
        MP3INFO mp3;
        for (int i = 1; i < ac; ++i) {
            CFile file;
            file.Open(av[i], CFile::modeRead);
            if (getMp3Info(&mp3, file))
                printf("%-30s %8d %s\n", mp3.tag.title, mp3.seconds, av[i]);
            else
                printf("%-30s %8d %s\n", "***INVALID MP3***", 0, av[i]);
        }
        return 0;
    }
#endif

/*
 * Populate the MP3INFO structure whose address is provided by the caller.
 * Returns a flag indicating whether we were successful (we won't be if
 * it's not a valid MP3 file).
 */
bool getMp3Info(MP3INFO* mp3, CFile& file) {
    memset(mp3, 0, sizeof(*mp3));
    mp3->fp = &file;
    mp3->dataSize = (long)file.GetLength();
    readTag(mp3);
    if (findFirstHeader(mp3)) {
#ifdef DEBUG
        fprintf(stderr, "Found first header at %ld\n", file.GetPosition());
#endif
        int bitrate, nFrames = 0;
        int counts[15] = { 0 };

        // Don't be misled by the name: the first time we
        // call getNextHeader() we're actually getting the
        // header for the first frame.
        while ((bitrate = getNextHeader(mp3)) >= 0) {
            counts[bitrate]++;
            nFrames++;
#ifdef DEBUG
            fprintf(stderr, "bitrate=%d\n", bitrate);
#endif
        }
#ifdef DEBUG
        fprintf(stderr, "scanned %d frames\n", nFrames);
#endif
        // At this point we've loaded the counts for frames
        // with each bitrate value.  Even though the other
        // values used to calculate the duration for a frame
        // (version, layer, frequency, padding) are all
        // repeated in the header for each frame, only the
        // bitrate and the padding flag can vary from frame
        // to frame.  This code calculates the duration for
        // each of the sets of frames with the same bitrate
        // all at once and fudges for the padding, which is
        // assumed (falsely) to be the same for all frames.
        // I've copied that sloppiness from the original
        // mp3info code; will eliminate it if the CDR users
        // ask me to.
        // 2010-06-03: eliminated padding bug described above,
        // after further discussion with original author, who
        // tells me that the padding byte has no effect on
        // runtime length (RMK)
        int frameTypes = 0, framesSoFar = 0, vbrMedian = -1;
        double seconds = 0.0, totalRate = 0.0;
        MP3HEADER h;
        memcpy(&h, &mp3->header, sizeof h);
        // Force padding to false, since we're not interested at this
        // point in counting bytes but in calculating runtime duration.
        h.padding = false;
        for (int i = 0; i < sizeof(counts) / sizeof(*counts); ++i) {
            if (counts[i]) {
                frameTypes++;
                h.bitrate = i;
                framesSoFar += counts[i];
                double br = headerBitrate(&h);
                double fl = frameLength(&h);
                seconds += fl * counts[i] / (br * 125);
#ifdef DEBUG
                fprintf(stderr, "counts[%d]=%d: br=%f fl=%f cum secs=%f\n",
                        i, counts[i], br, fl, seconds);
#endif
                totalRate += br * counts[i];
                if (vbrMedian == -1 && framesSoFar >= nFrames / 2)
                    vbrMedian = i;
            }
        }
        mp3->seconds = (int)(seconds + 0.5);
        mp3->header.bitrate = vbrMedian;
        mp3->vbrAverage = (int)(totalRate / nFrames);
        mp3->nFrames = nFrames;
        if (frameTypes > 1)
            mp3->variableBitrate = true;
        file.SeekToBegin();
        return true;
    }
    file.SeekToBegin();
    return false;
}

/*
 * Read the MP3 tags if they are present at the end
 * of the file.  Return flag indicating whether we
 * found them.  If we did, the dataSize member of the
 * MP3INFO structure is reduced by 128 bytes (the
 * number of bytes appended to the file for the tag
 * information) and 'validTag' member is set to true.
 */
bool readTag(MP3INFO* mp3) {
    if (mp3->dataSize >= 128) {
        char buf[3];
        mp3->fp->Seek(-128, CFile::end);
        mp3->fp->Read(buf, 3);
        if (!memcmp(buf, "TAG", 3)) {
            mp3->tag.genre = 255;
            mp3->validTag = true;
            mp3->dataSize -= 128;
            mp3->fp->Read(mp3->tag.title, 30);
            mp3->fp->Read(mp3->tag.artist, 30);
            mp3->fp->Read(mp3->tag.album, 30);
            mp3->fp->Read(mp3->tag.year, 4);
            mp3->fp->Read(mp3->tag.comment, 30);
            mp3->fp->Read(&mp3->tag.genre, 1);
            strip(mp3->tag.title);
            strip(mp3->tag.artist);
            strip(mp3->tag.album);
            strip(mp3->tag.year);
            strip(mp3->tag.comment);
            if (mp3->tag.comment[28] == '\0')
                mp3->tag.track = mp3->tag.comment[29];
            return true;
        }
    }
    return false;
}

/*
 * Trim whitespace from the end of a null-terminated string.
 */
void strip(char* s) {
    int i = strlen(s);
    while (i-- && isspace(s[i]))
        s[i] = '\0';
}

/*
 * Scan to determine whether we are confident that this is
 * a valid MP3 file by finding a minimum number of valid
 * frame headers.  Return true or false depending on whether
 * we have found them.  A side effect of this function is
 * that if we do find enough valid headers we position the
 * file to the beginning of the first one we found.
 */
bool findFirstHeader(MP3INFO* mp3) {
    MP3HEADER h1, h2;
    long validStart = 0;
    mp3->fp->SeekToBegin();
    for (;;) {
        unsigned char c;
        for (;;) {
            if (mp3->fp->Read(&c, 1) != 1)
                return false;
            if (c == 0xFF)
                break;
        }
        mp3->fp->Seek(-1, CFile::current);
        validStart = (long)mp3->fp->GetPosition();
        int frameLength = getHeader(mp3->fp, &h1);
        if (frameLength) {
            mp3->fp->Seek(frameLength - FRAME_HEADER_SIZE, CFile::current);
            int n = 1;
            while (n < MIN_CONSEC_GOOD_FRAMES) {
                long bytesLeft = mp3->dataSize - (long)mp3->fp->GetPosition();
                if (bytesLeft < FRAME_HEADER_SIZE)
                    break;
                frameLength = getHeader(mp3->fp, &h2);
                if (!frameLength || !sameConstant(&h1, &h2))
                    break;
                mp3->fp->Seek(frameLength - FRAME_HEADER_SIZE, CFile::current);
                n++;
            }
            if (n == MIN_CONSEC_GOOD_FRAMES) {
                mp3->fp->Seek(validStart, CFile::begin);
                memcpy(&mp3->header, &h2, sizeof h2);
                mp3->validHeader = true;
                return true;
            }
        }
    }
    return false;
}

/*
 * Read the header at the current position or look for the next valid
 * header if there isn't one at the current position.  Return a valid
 * bitrate index (0 - 14) if we find a good frame; otherwise return -1.
 */
int getNextHeader(MP3INFO* mp3) {
    MP3HEADER h;
    int skipBytes = 0;
    for (;;) {
        unsigned char c = 0;
        while (mp3->fp->Read(&c, 1) == 1 && c != 0xFF && 
                          (long)mp3->fp->GetPosition() < mp3->dataSize)
            skipBytes++;
        if (c == 0xFF) {
            mp3->fp->Seek(-1, CFile::current);
            int headerLength = getHeader(mp3->fp, &h);
            if (headerLength && h.bitrate < 0x0F) {
                if (skipBytes)
                    mp3->badFrames++;
                mp3->fp->Seek(headerLength - FRAME_HEADER_SIZE, CFile::current);
                return (int)h.bitrate;
            }
            else
                skipBytes += FRAME_HEADER_SIZE;
        }
        else {
            if (skipBytes)
                mp3->badFrames++;
            return -1;
        }
    }
}

/*
 * Read and parse the frame header at the current position.
 * Return the number of bytes in the frame, or 0 if valid 
 * frame header not found.
 */
int getHeader(CFile* fp, MP3HEADER* h) {
    unsigned char buf[FRAME_HEADER_SIZE];
    memset(h, 0, sizeof *h);
#ifdef DEBUG
    long pos = (long)fp->GetPosition();
#endif
    if (fp->Read(buf, FRAME_HEADER_SIZE) != FRAME_HEADER_SIZE) {
        h->sync = 0;
        return 0;
    }
    h->sync = buf[0] << 4 | (buf[1] & 0xE0) >> 4;
    if (buf[1] & 0x10)
        h->version = buf[1] >> 3 & 1;
    else
        h->version = 2;
    h->layer = buf[1] >> 1 & 3;
    h->bitrate = buf[2] >> 4 & 0x0F;
    // Original mp3info code only accepted layer III.
    if (h->sync != 0xFFE || h->layer < 1 || h->bitrate == 0x0F) {
#ifdef DEBUG
        fprintf(stderr,
                "getHeader(pos=%ld/%06lX): sync: %04x; layer: %d; "
                "bitrate: %02x\n",
                pos, pos, h->sync, h->layer, h->bitrate);
        h->sync = 0;
#endif
        return 0;
    }
    h->hasCrc        = buf[1]      & 0x01 ? true : false;
    h->freq          = buf[2] >> 2 & 0x03;
    h->padding       = buf[2] >> 1 & 0x01 ? true : false;
    h->priv          = buf[2]      & 0x01;
    h->mode          = buf[3] >> 6 & 0x03;
    h->modeExtension = buf[3] >> 4 & 0x03;
    h->copyright     = buf[3] >> 3 & 0x01 ? true : false;
    h->original      = buf[3] >> 2 & 0x01 ? true : false;
    h->emphasis      = buf[3]      & 0x03;

    // Only values 0, 1, or 2 allowed for frequency
    if (h->freq == 0x03) {
        h->sync = 0;
        return 0;
    }
    int fl = frameLength(h);
#ifdef DEBUG
    fprintf(stderr, "getHeader(pos=%ld/%06lX): frame length is %d\n",
            pos, pos, fl);
#endif
    return fl >= MIN_FRAME_SIZE ? fl : 0;
}

/*
 * Calculate frame length from header information.  Returned
 * as the number of bytes in the frame (including the header).
 */
int frameLength(const MP3HEADER* h) {
    if (h->sync != 0xFFE)
        return 0;
    // Reserved, layer 3, layer 2, layer 1
    static int frameSizeIndex[] = { 0, 72000, 72000, 24000 };
#ifdef DEBUG
    int fsi = frameSizeIndex[h->layer];
    int multiplier = (h->version & 1) + 1;
    int bitrate = headerBitrate(h);
    int freq = headerFrequency(h);
    int padding = h->padding ? 1 : 0;
    int result = (fsi * multiplier * bitrate) / freq + padding;
    fprintf(stderr,
            "frameLength(): fsi=%d mult=%d br=%d fr=%d pad=%d res=%d\n",
            fsi, multiplier, bitrate, freq, padding, result);
    return result;
#else
    return (frameSizeIndex[h->layer] * ((h->version & 1) + 1) *
            headerBitrate(h)) / headerFrequency(h) + (h->padding ? 1 : 0);
#endif
}

/*
 * Look up the bitrate represented by a frame header.
 */
int headerBitrate(const MP3HEADER* h) {
    static int bitrate[2][4][15] = {
     { // MPEG 2.x, reserved row, followed by layers 3, 2 & 1
      { 0 },
      { 0, 8, 16, 24, 32, 40, 48, 56, 64, 80, 96, 112, 128, 144, 160 },
      { 0, 8, 16, 24, 32, 40, 48, 56, 64, 80, 96, 112, 128, 144, 160 },
      { 0, 32, 48, 56, 64, 80, 96, 112, 128, 144, 160, 176, 192, 224, 256 }
     },
     { // MPEG 1.0, reserved row, followed by layers 3, 2 & 1
      { 0 },
      { 0, 32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320 },
      { 0, 32, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 384 },
      { 0, 32, 64, 96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448 }
     }
    };
#ifdef DEBUG
    fprintf(stderr, "headerBitrate(): version=%d layer=%d bitrate=%d\n",
            h->version, h->layer, h->bitrate);
#endif
    return bitrate[h->version & 1][h->layer][h->bitrate];
}

/*
 * Look up a frame header's frequency.
 */
int headerFrequency(const MP3HEADER* h) {
    // The 50000 values are bogus, as freq can only have values 0, 1 or 2
    static int frequencies[3][4] = {
        { 22050, 24000, 16000, 50000 },  /* MPEG 2.0 */
        { 44100, 48000, 32000, 50000 },  /* MPEG 1.0 */
        { 11025, 12000, 8000, 50000 }    /* MPEG 2.5 */
    };
    return frequencies[h->version][h->freq];
}

/*
 * Check to see if the two headers match.  The original mp3info
 * code had a strange comparison of the first bytes of the
 * structures cast to unsigned integers.  I have written to
 * the original maintainer pointing out the portability
 * problem with this technique (not to mention the odd effect
 * on the logic in the remainder of the function).  The
 * function is used by the code which scans the beginning of
 * the file looking for enough consecutive identical headers
 * (ignoring variable bitrate values) to satisfy us that we
 * have a valid MP3 file.
 */
bool sameConstant(const MP3HEADER* h1, const MP3HEADER* h2) {
    //if (h1->sync      == h2->sync     ) return true;
    if (h1->sync      != h2->sync     ) return false;
    if (h1->version   != h2->version  ) return false;
    if (h1->layer     != h2->layer    ) return false;
    if (h1->hasCrc    != h2->hasCrc   ) return false;
    if (h1->freq      != h2->freq     ) return false;
    if (h1->mode      != h2->mode     ) return false;
    if (h1->copyright != h2->copyright) return false;
    if (h1->original  != h2->original ) return false;
    if (h1->emphasis  != h2->emphasis ) return false;
    return true;
}
