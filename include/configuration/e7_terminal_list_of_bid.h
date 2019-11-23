#pragma once

// source: nexo-FAST v.3.2 section 13.3.135
// size: at least 50
// configuration: Terminal
// presence: C

struct TerminalListOfBid {
    struct Bid Bid;

    struct MatchingPattern {
        enum {
            MATCH_PREFIX
          , MATCH_RANGE
        } type;
        union {
            struct Prefix prefix;
            struct PrefixRange prefixRange;
        };
        struct MatchingPattern* next;
    } matchingPattern;

    struct TerminalListOfBid* next;
};
