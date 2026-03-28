#ifndef CONFIG_H
#define CONFIG_H

// String used to delimit block outputs in the status.
#define DELIMITER " "

// Maximum number of Unicode characters that a block can output.
#define MAX_BLOCK_OUTPUT_LENGTH 45

// Control whether blocks are clickable.
#define CLICKABLE_BLOCKS 1

// Control whether a leading delimiter should be prepended to the status.
#define LEADING_DELIMITER 0

// Control whether a trailing delimiter should be appended to the status.
#define TRAILING_DELIMITER 1

// Define blocks for the status feed as X(icon, cmd, interval, signal).
#define BLOCKS(X)             \
    X("", "status-ffmpeg-record", 1, 1) \
    X("", "status-music", 1, 2) \
    X("", "status-rss", 0, 10) \
    X("", "status-mail", 0, 12) \
    X("", "status-audio output", 1, 3) \
    X("", "status-audio input", 1, 4) \
    X("", "status-network", 5, 5) \
    X("", "status-bluetooth", 5, 6)  \
    X("", "status-keyboard", 1, 7)  \
    X("", "status-pomodoro", 1, 11) \
    X("", "status-date", 5, 9)

#endif  // CONFIG_H
