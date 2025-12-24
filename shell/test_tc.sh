#!/bin/sh

printf "\x1b[38;2;255;100;0mTRUECOLOR TEST\x1b[0m\n"

awk 'BEGIN{
    s="          "; s=s s s s s s s s;
    for (c=0; c<77; c++) {
        r=255-(c*255/76);
        g=c*510/76;
        b=c*255/76;
        if (g>255) g=510-g;
        printf "\033[48;2;%d;%d;%dm", r,g,b;
        printf "\033[38;2;%d;%d;%dm", 255-r,255-g,255-b;
        printf "%s\033[0m", substr(s,c+1,1);
    }
    printf "\n";
}'
