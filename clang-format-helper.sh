#!/bin/bash
fd "\.[hc]pp" | xargs -d '\n' clang-format -i
fd "\.[hc]pp" | xargs -d '\n' sed -i 's/ \* /\*/g'
fd "\.[hc]pp" | xargs -d '\n' sed -i 's/ \/ /\//g'
fd "\.[hc]pp" | xargs -d '\n' sed -i 's/ \% /%/g'
fd "\.[hc]pp" | xargs -d '\n' sed -i 's/ \^ /^/g'
