#!/bin/bash
fd --exclude external "\.[hc]pp" | xargs -d '\n' clang-format -i
fd --exclude external "\.[hc]pp" | xargs -d '\n' sed -i 's/ \* /\*/g'
fd --exclude external "\.[hc]pp" | xargs -d '\n' sed -i 's/ \/ /\//g'
fd --exclude external "\.[hc]pp" | xargs -d '\n' sed -i 's/ \% /%/g'
fd --exclude external "\.[hc]pp" | xargs -d '\n' sed -i 's/ \^ /^/g'
